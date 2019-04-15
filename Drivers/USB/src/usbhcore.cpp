#include "usbhcore.h"
#include "usbh_class.h"
#include <cstring>

#ifdef STM32_USE_USB_HOST

#define USBH_ADDRESS_DEFAULT                     0
#define USBH_ADDRESS_ASSIGNED                    1
#define USBH_MPS_DEFAULT                         0x40

#if (USBH_USE_OS == 1)
#ifdef STM32_USE_USB_HS
typedef OS::process<USBH_PROCESS_HS_PRIO, USBH_PROCESS_HS_STACK_SIZE> TProcUSB_HS;
TProcUSB_HS ProcUSB_HS;
namespace OS
{
    template <>
    OS_PROCESS void TProcUSB_HS::exec()
    {
        for(;;)
        {
            if (usb_HS.wait_message())
                usb_HS.process();
        }
    }
}
#endif //STM32_USE_USB_HS

#ifdef STM32_USE_USB_FS
typedef OS::process<USBH_PROCESS_FS_PRIO, USBH_PROCESS_FS_STACK_SIZE> TProcUSB_FS;
TProcUSB_FS ProcUSB_FS;
namespace OS
{
    template <>
    OS_PROCESS void TProcUSB_FS::exec()
    {
        for(;;)
        {
            if (usb_FS.wait_message())
                usb_FS.process();
        }
    }
}
#endif //STM32_USE_USB_FS
#endif //USBH_USE_OS

uint8_t USBH_CfgDesc[512];

void USBHCore::init(void (*puser)(USBHCore *,EHostUser), uint8_t id)
{
    m_id = id;
    m_active_class = nullptr;
    m_class_number = 0;
    deInit_state_machine();
    if (puser != nullptr)
        m_user = puser;
    LL_init();
    for (int idx=0 ; idx<USBH_MAX_NUM_SUPPORTED_CLASS ; ++idx)
        m_class[idx] = nullptr;
}

void USBHCore::deInit()
{
    deInit_state_machine();
    if (m_hcd != nullptr)
    {
        LL_stop();
    }
}

uint32_t USBHCore::register_class(USBHClass *pclass)
{
    if (pclass != nullptr)
    {
        if (m_class_number <= USBH_MAX_NUM_SUPPORTED_CLASS)
        {
            m_class[m_class_number++] = pclass;
            return STM32_RESULT_OK;
        }
        else
        {
            USBH_ErrLog("Max Class Number reached");
            return STM32_RESULT_FAIL;
        }
    }
    else
    {
        USBH_ErrLog("Invalid Class Handle");
        return STM32_RESULT_FAIL;
    }
}

uint32_t USBHCore::select_interface(uint8_t interface)
{
    if (interface < m_device.CfgDesc.bNumInterfaces)
    {
        m_device.current_interface = interface;
        USBH_UsrLog("Switching to Interface (#%d)", interface);
        USBH_UsrLog("Class    : %X", m_device.CfgDesc.Itf_Desc[interface].bInterfaceClass);
        USBH_UsrLog("SubClass : %X", m_device.CfgDesc.Itf_Desc[interface].bInterfaceSubClass);
        USBH_UsrLog("Protocol : %X", m_device.CfgDesc.Itf_Desc[interface].bInterfaceProtocol);
        return STM32_RESULT_FAIL;
    }
    else
    {
        USBH_ErrLog("Cannot Select This Interface");
        return STM32_RESULT_FAIL;
    }
}

uint8_t USBHCore::find_interface(uint8_t Class, uint8_t subclass, uint8_t protocol)
{
    USBHInterfaceDesc_t* pif = nullptr;
    USBHCfgDesc_t* pcfg = &m_device.CfgDesc;

    uint8_t if_idx = 0;
    while (if_idx < USBH_MAX_NUM_INTERFACES)
    {
        pif = &pcfg->Itf_Desc[if_idx];
        if (((pif->bInterfaceClass == Class) || (Class == 0xff)) &&
            ((pif->bInterfaceSubClass == subclass) || (subclass == 0xff)) &&
            ((pif->bInterfaceProtocol == protocol) || (protocol == 0xff)))
            return if_idx;
        ++if_idx;
    }
    return 0xff;
}

uint8_t USBHCore::find_interface_index(uint8_t interface_number, uint8_t alt_settings)
{
    USBHInterfaceDesc_t* pif = nullptr;
    USBHCfgDesc_t* pcfg = &m_device.CfgDesc;

    uint8_t if_idx = 0;
    while (if_idx < USBH_MAX_NUM_INTERFACES)
    {
        pif = &pcfg->Itf_Desc[if_idx];
        if ((pif->bInterfaceNumber == interface_number) &&
            (pif->bAlternateSetting == alt_settings))
            return if_idx;
        ++if_idx;
    }
    return 0xff;
}

void USBHCore::start()
{
    LL_start();
    LL_driver_VBUS(SET);
}

void USBHCore::stop()
{
    LL_stop();
    LL_driver_VBUS(RESET);
    free_pipe(m_control.pipe_in);
    free_pipe(m_control.pipe_out);
}

void USBHCore::re_enumerate()
{
    stop();
    STM32_SYSTICK::delay(200);
    deInit_state_machine();
    start();
#if (USBH_USE_OS == 1)
    send_message();
#endif
}

void USBHCore::process()
{
    switch (m_gstate)
    {
    case EHostState::IDLE:
        if (m_device.is_connected)
        {
            /* Wait for 200 ms after connection */
            m_gstate = EHostState::DEV_WAIT_FOR_ATTACHMENT;
            STM32_SYSTICK::delay(200);
            LL_reset_port();
#if (USBH_USE_OS == 1)
            send_message();
#endif
        }
        break;
    case EHostState::DEV_WAIT_FOR_ATTACHMENT:
        break;
    case EHostState::DEV_ATTACHED:
        USBH_UsrLog("USB Device Attached");
        /* Wait for 100 ms after Reset */
        STM32_SYSTICK::delay(100);
        m_device.speed = LL_get_speed();
        m_gstate = EHostState::ENUMERATION;

        m_control.pipe_out = alloc_pipe(0x00);
        m_control.pipe_in = alloc_pipe(0x80);

        open_pipe(m_control.pipe_in,
                  0x80,
                  m_device.address,
                  m_device.speed,
                  STM32_HCD::EEPType::CTRL,
                  m_control.pipe_size);

        open_pipe(m_control.pipe_out,
                  0x00,
                  m_device.address,
                  m_device.speed,
                  STM32_HCD::EEPType::CTRL,
                  m_control.pipe_size);
#if (USBH_USE_OS == 1)
        send_message();
#endif
        break;
    case EHostState::ENUMERATION:
        if (handle_enum() == STM32_RESULT_OK)
        {
            USBH_UsrLog("Enumeration done.");
            m_device.current_interface = 0;
            if (m_device.DevDesc.bNumConfigurations == 1)
            {
                USBH_UsrLog("This device has only 1 configuration.");
                m_gstate = EHostState::SET_CONFIGURATION;
            }
            else
                m_gstate = EHostState::INPUT;
        }
        break;
    case EHostState::INPUT:
        if (m_user != nullptr)
        {
            m_user(this, EHostUser::SELECT_CONFIGURATION);
            m_gstate = EHostState::SET_CONFIGURATION;
#if (USBH_USE_OS == 1)
            send_message();
#endif
        }
        break;
    case EHostState::SET_CONFIGURATION:
        if (set_cfg(m_device.CfgDesc.bConfigurationValue) == EStatus::OK)
        {
            m_gstate = EHostState::CHECK_CLASS;
            USBH_UsrLog("Default configuration set.");
        }
        break;
    case EHostState::CHECK_CLASS:
        if (m_class_number == 0)
        {
            USBH_UsrLog("No Class has been registered.");
        }
        else
        {
            m_active_class = nullptr;
            for (int idx=0 ; idx<USBH_MAX_NUM_SUPPORTED_CLASS ; ++idx)
            {
                if (m_class[idx] == nullptr)
                    continue;
                if (m_class[idx]->get_class_code() == m_device.CfgDesc.Itf_Desc[0].bInterfaceClass)
                {
                    m_active_class = m_class[idx];
                    break;
                }
            }
            if (m_active_class != nullptr)
            {
                if (m_active_class->init(this) ==  EStatus::OK)
                {
                    m_gstate = EHostState::CLASS_REQUEST;
                    USBH_UsrLog("%s class started.", m_active_class->get_name());
                    m_user(this, EHostUser::CLASS_SELECTED);
                }
                else
                {
                    m_gstate = EHostState::ABORT_STATE;
                    USBH_UsrLog("Device not supporting %s class.", m_active_class->get_name());
                }
            }
            else
            {
                m_gstate = EHostState::ABORT_STATE;
                USBH_UsrLog("No registered class for this device.");
            }
        }
#if (USBH_USE_OS == 1)
        send_message();
#endif
        break;
    case EHostState::CLASS_REQUEST:
        if (m_active_class != nullptr)
        {
            if (m_active_class->class_request() == EStatus::OK)
                m_gstate = EHostState::CLASS;
        }
        else
        {
            m_gstate = EHostState::ABORT_STATE;
            USBH_ErrLog("Invalid Class Driver.");
        }
#if (USBH_USE_OS == 1)
        send_message();
#endif
        break;
    case EHostState::CLASS:
        if (m_active_class != nullptr)
            m_active_class->process();
        break;
    case EHostState::DEV_DISCONNECTED:
        deInit_state_machine();
        if (m_active_class != nullptr)
        {
            m_active_class->deInit();
            m_active_class = nullptr;
        }
        break;
    case EHostState::ABORT_STATE:
    case EHostState::DETECT_DEVICE_SPEED:
    case EHostState::SUSPEND:
        break;
    }
}

uint32_t USBHCore::handle_enum()
{
    __IO uint32_t status = STM32_RESULT_BUSY;
    switch (m_enum_state)
    {
    case EUSBState::IDLE:
        if (get_dev_desc(8) == EStatus::OK)
        {
            m_control.pipe_size = m_device.DevDesc.bMaxPacketSize;
            m_enum_state = EUSBState::GET_FULL_DEV_DESC;

            open_pipe(m_control.pipe_in,
                      0x80,
                      m_device.address,
                      m_device.speed,
                      STM32_HCD::EEPType::CTRL,
                      m_control.pipe_size);

            open_pipe(m_control.pipe_out,
                      0x00,
                      m_device.address,
                      m_device.speed,
                      STM32_HCD::EEPType::CTRL,
                      m_control.pipe_size);
        }
        break;
    case EUSBState::GET_FULL_DEV_DESC:
        if (get_dev_desc(USB_DEVICE_DESC_SIZE) == EStatus::OK)
        {
            USBH_UsrLog("PID: %xh", m_device.DevDesc.idProduct );
            USBH_UsrLog("VID: %xh", m_device.DevDesc.idVendor );
            m_enum_state = EUSBState::SET_ADDR;
        }
        break;
    case EUSBState::SET_ADDR:
        if (set_address(USBH_DEVICE_ADDRESS) == EStatus::OK)
        {
            STM32_SYSTICK::delay(2);
            m_device.address = USBH_DEVICE_ADDRESS;
            USBH_UsrLog("Address (#%d) assigned.", m_device.address);
            m_enum_state = EUSBState::GET_CFG_DESC;

            open_pipe(m_control.pipe_in,
                      0x80,
                      m_device.address,
                      m_device.speed,
                      STM32_HCD::EEPType::CTRL,
                      m_control.pipe_size);

            open_pipe(m_control.pipe_out,
                      0x00,
                      m_device.address,
                      m_device.speed,
                      STM32_HCD::EEPType::CTRL,
                      m_control.pipe_size);
        }
        break;
    case EUSBState::GET_CFG_DESC:
        if (get_cfg_desc(USB_CONFIGURATION_DESC_SIZE) == EStatus::OK)
            m_enum_state = EUSBState::GET_FULL_CFG_DESC;
        break;
    case EUSBState::GET_FULL_CFG_DESC:
        if (get_cfg_desc(m_device.CfgDesc.wTotalLength) == EStatus::OK)
            m_enum_state = EUSBState::GET_MFC_STRING_DESC;
        break;
    case EUSBState::GET_MFC_STRING_DESC:
        if (m_device.DevDesc.iManufacturer != 0)
        {
            if (get_string_desc(m_device.DevDesc.iManufacturer,
                                m_device.Data, 0xff) == EStatus::OK)
            {
                USBH_UsrLog("Manufacturer : %s", m_device.Data);
                m_enum_state = EUSBState::GET_PRODUCT_STRING_DESC;
            }
        }
        else
        {
            USBH_UsrLog("Manufacturer : N/A");
            m_enum_state = EUSBState::GET_PRODUCT_STRING_DESC;
        }
#if (USBH_USE_OS == 1)
        send_message();
#endif
        break;
    case EUSBState::GET_PRODUCT_STRING_DESC:
        if (m_device.DevDesc.iProduct != 0)
        {
            if (get_string_desc(m_device.DevDesc.iProduct,
                                m_device.Data, 0xff) == EStatus::OK)
            {
                USBH_UsrLog("Product : %s", m_device.Data);
                m_enum_state = EUSBState::GET_SERIALNUM_STRING_DESC;
            }
        }
        else
        {
            USBH_UsrLog("Product : N/A");
            m_enum_state = EUSBState::GET_SERIALNUM_STRING_DESC;
        }
#if (USBH_USE_OS == 1)
        send_message();
#endif
        break;
    case EUSBState::GET_SERIALNUM_STRING_DESC:
        if (m_device.DevDesc.iSerialNumber != 0)
        {
            if (get_string_desc(m_device.DevDesc.iSerialNumber,
                                m_device.Data, 0xff) == EStatus::OK)
            {
                USBH_UsrLog("Serial Number : %s", m_device.Data);
                status = STM32_RESULT_OK;
            }
        }
        else
        {
            USBH_UsrLog("Serial Number : N/A");
            status = STM32_RESULT_OK;
        }
#if (USBH_USE_OS == 1)
        send_message();
#endif
        break;
    }
    return status;
}

void USBHCore::handle_SOF()
{
    if ((m_gstate == EHostState::CLASS) && (m_active_class != nullptr))
        m_active_class->SOF_process();
}

void USBHCore::deInit_state_machine()
{
    memset(m_pipes, 0, USBH_MAX_PIPES_NBR * sizeof(uint32_t));
    memset(m_device.Data, 0, USBH_MAX_DATA_BUFFER);

    m_gstate = EHostState::IDLE;
    m_enum_state = EUSBState::IDLE;
    m_request_state = ECMDState::SEND;
    m_timer = 0;

    m_control.state = ECTRLState::SETUP;
    m_control.pipe_size = USBH_MPS_DEFAULT;
    m_control.errorcount = 0;

    m_device.address = USBH_ADDRESS_DEFAULT;
    m_device.speed = STM32_HCD::EOTGSpeed::FULL;
}

void USBHCore::LL_connect()
{
    if (m_gstate == EHostState::IDLE)
    {
        m_device.is_connected = SET;
        if (m_user == nullptr)
            m_user(this, EHostUser::CONNECTION);
    }
    else if (m_gstate == EHostState::DEV_WAIT_FOR_ATTACHMENT)
        m_gstate = EHostState::DEV_ATTACHED;
#if (USBH_USE_OS == 1)
    send_message();
    xprintf("send_message<\n\r");
#endif
}

void USBHCore::LL_disconnect()
{
    LL_stop();
    free_pipe(m_control.pipe_in);
    free_pipe(m_control.pipe_out);
    m_device.is_connected = RESET;
    if (m_user != nullptr)
        m_user(this, EHostUser::DISCONNECTION);
    USBH_UsrLog("USB Device disconnected");
    LL_start();
    m_gstate = EHostState::DEV_DISCONNECTED;
#if (USBH_USE_OS == 1)
    send_message();
#endif
}

void USBHCore::LL_init()
{
    if (m_id == HOST_FS)
#ifdef STM32_USE_USB_FS
    {
        m_hcd = &usb_fs;
        m_hcd->set_data(static_cast<void*>(this));
        if (usb_fs.init(USB_OTG_FS, STM32_HCD::EOTG_PHY::EMBEDDED, false, false, STM32_HCD::EOTGSpeed::FULL, 8) != STM32_RESULT_OK)
            Error_Handler();
        LL_set_timer(usb_fs.get_current_frame());
    }
#else
    {}
#endif //STM32_USE_USB_FS
    else
#ifdef STM32_USE_USB_HS
    {
        m_hcd = &usb_hs;
        m_hcd->set_data(static_cast<void*>(this));
        if (usb_hs.init(USB_OTG_HS, STM32_HCD::EOTG_PHY::EMBEDDED, false, true, STM32_HCD::EOTGSpeed::FULL, 12) != STM32_RESULT_OK)
            Error_Handler();
        LL_set_timer(usb_hs.get_current_frame());
    }
#else
    {}
#endif // STM32_USE_USB_HS
}

void USBHCore::LL_driver_VBUS(uint8_t state)
{
    if (this->m_id == HOST_FS)
    {
        if (state == RESET)
            STM32_USB_PWR_FS_PORT.pin_ON(STM32_USB_PWR_FS_PIN);
        else
            STM32_USB_PWR_FS_PORT.pin_OFF(STM32_USB_PWR_FS_PIN);
    }
    else
    {
        if (state == RESET)
            STM32_USB_PWR_HS_PORT.pin_ON(STM32_USB_PWR_HS_PIN);
        else
            STM32_USB_PWR_HS_PORT.pin_OFF(STM32_USB_PWR_HS_PIN);
    }
    STM32_SYSTICK::delay(200);
}

uint8_t USBHCore::alloc_pipe(uint8_t ep_addr)
{
    uint16_t pipe = get_free_pipe();
    if (pipe != 0xffff)
        m_pipes[pipe] = 0x8000 | ep_addr;
    return static_cast<uint8_t>(pipe);
}

uint16_t USBHCore::get_free_pipe()
{
    for (uint8_t idx=0 ; idx<11 ; ++idx)
        if ((m_pipes[idx] & 0x8000) == 0)
            return idx;
    return 0xffff;
}

USBHCore::EStatus USBHCore::ctl_req(uint8_t* buff, uint16_t length)
{
    EStatus status = EStatus::BUSY;
    switch (m_request_state)
    {
    case ECMDState::SEND:
        m_control.buff = buff;
        m_control.length = length;
        m_control.state = ECTRLState::SETUP;
        m_request_state = ECMDState::WAIT;
#if (USBH_USE_OS == 1)
        send_message();
#endif
        break;
    case ECMDState::WAIT:
        status = handle_control();
        if (status == EStatus::OK)
        {
            m_request_state = ECMDState::SEND;
            m_control.state = ECTRLState::IDLE;
        }
        else if (status == EStatus::FAIL)
        {
            m_request_state = ECMDState::SEND;
        }
        break;
    case ECMDState::IDLE:
        break;
    }
    return status;
}

USBHCore::EStatus USBHCore::get_descriptor(uint8_t req_type, uint16_t value_idx, uint8_t* buff, uint16_t length)
{
    if (m_request_state == ECMDState::SEND)
    {
        m_control.setup.b.bmRequestType = static_cast<uint8_t>(EReqDir::D2H) | req_type;
        m_control.setup.b.bRequest = ERequest::GET_DESCRIPTOR;
        m_control.setup.b.wValue.w = value_idx;

        if ((value_idx & 0xff00) == USB_DESC_STRING)
            m_control.setup.b.wIndex.w = 0x0409;
        else
            m_control.setup.b.wIndex.w = 0;
        m_control.setup.b.wLength.w = length;
    }
    return ctl_req(buff, length);
}

USBHCore::EStatus USBHCore::get_dev_desc(uint16_t length)
{
    EStatus status = get_descriptor(EReqRecipient::REQ_DEVICE | EReqType::STANDARD,
                                    USB_DESC_DEVICE, m_device.Data, length);
    if (status == EStatus::OK)
        parse_dev_desc(&m_device.DevDesc, m_device.Data, length);
    return status;
}

USBHCore::EStatus USBHCore::get_string_desc(uint8_t string_index, uint8_t* buff, uint16_t length)
{
    EStatus status = get_descriptor(EReqRecipient::REQ_DEVICE | EReqType::STANDARD,
                                    USB_DESC_STRING | string_index, m_device.Data, length);
    if (status == EStatus::OK)
        parse_string_desc(m_device.Data, buff, length);
    return status;
}

USBHCore::EStatus USBHCore::set_cfg(uint16_t config_val)
{
    if (m_request_state == ECMDState::SEND)
    {
        m_control.setup.b.bmRequestType = static_cast<uint8_t>(EReqDir::H2D) | EReqRecipient::REQ_DEVICE | EReqType::STANDARD;
        m_control.setup.b.bRequest = ERequest::SET_CONFIGURATION;
        m_control.setup.b.wValue.w = config_val;
        m_control.setup.b.wIndex.w = 0;
        m_control.setup.b.wLength.w = 0;
    }
    return ctl_req(nullptr, 0);
}

USBHCore::EStatus USBHCore::get_cfg_desc(uint16_t length)
{
    uint8_t* pData;
#if (USBH_KEEP_CFG_DESCRIPTOR == 1)
    pData = m_device.CfgDesc_Raw;
#else
    pData = m_device.Data;
#endif
    EStatus status = get_descriptor(EReqRecipient::REQ_DEVICE | EReqType::STANDARD,
                                    USB_DESC_CONFIGURATION, pData, length);
    if (status == EStatus::OK)
        parse_cfg_desc(&m_device.CfgDesc, pData, length);
    return status;
}

USBHCore::EStatus USBHCore::set_address(uint8_t dev_address)
{
    if (m_request_state == ECMDState::SEND)
    {
        m_control.setup.b.bmRequestType = static_cast<uint8_t>(EReqDir::H2D) | EReqRecipient::REQ_DEVICE | EReqType::STANDARD;
        m_control.setup.b.bRequest = ERequest::SET_ADDRESS;
        m_control.setup.b.wValue.w = dev_address;
        m_control.setup.b.wIndex.w = 0;
        m_control.setup.b.wLength.w = 0;
    }
    return ctl_req(nullptr, 0);
}

USBHCore::EStatus USBHCore::set_interface(uint8_t ep_num, uint8_t alt_setting)
{
    if (m_request_state == ECMDState::SEND)
    {
        m_control.setup.b.bmRequestType = static_cast<uint8_t>(EReqDir::H2D) | EReqRecipient::REQ_INTERFACE | EReqType::STANDARD;
        m_control.setup.b.bRequest = ERequest::SET_INTERFACE;
        m_control.setup.b.wValue.w = alt_setting;
        m_control.setup.b.wIndex.w = ep_num;
        m_control.setup.b.wLength.w = 0;
    }
    return ctl_req(nullptr, 0);
}

USBHCore::EStatus USBHCore::clr_feature(uint8_t ep_num)
{
    if (m_request_state == ECMDState::SEND)
    {
        m_control.setup.b.bmRequestType = static_cast<uint8_t>(EReqDir::H2D) | EReqRecipient::REQ_INTERFACE | EReqType::STANDARD;
        m_control.setup.b.bRequest = ERequest::CLEAR_FEATURE;
        m_control.setup.b.wValue.w = FEATURE_SELECTOR_ENDPOINT;
        m_control.setup.b.wIndex.w = ep_num;
        m_control.setup.b.wLength.w = 0;
    }
    return ctl_req(nullptr, 0);
}

void USBHCore::parse_dev_desc(USBHDevDesc_t *pdesc, uint8_t *buf, uint16_t length)
{
    if (length > 8)
    {
        memcpy(pdesc, buf, 18);
        //pdesc->idVendor = __builtin_bswap16(pdesc->idVendor);
        //pdesc->idProduct = __builtin_bswap16(pdesc->idProduct);
        //pdesc->bcdDevice = __builtin_bswap16(pdesc->bcdDevice);
    }
    else
        memcpy(pdesc, buf, 8);
    //pdesc->bcdUSB = __builtin_bswap16(pdesc->bcdUSB);
}

void USBHCore::parse_string_desc(uint8_t *psrc, uint8_t *pdst, uint16_t length)
{
    if (psrc[1] == static_cast<uint16_t>(EDescType::STRING))
    {
        uint16_t strl = (((psrc[0] - 2) <= length) ? (psrc[0] - 2) : length);
        psrc += 2;
        for (uint16_t idx=0 ; idx<strl ; idx+=2)
        {
            *(pdst++) = psrc[idx];
        }
        *pdst = 0;
    }
}

void USBHCore::parse_cfg_desc(USBHCfgDesc_t *pdesc, uint8_t *buf, uint16_t length)
{
    memcpy(pdesc, buf, 9);
    //pdesc->wTotalLength = __builtin_bswap16(pdesc->wTotalLength);
    if (length > USB_CONFIGURATION_DESC_SIZE)
    {
        int8_t if_idx = 0;
        uint16_t ptr = static_cast<uint16_t>(ELen::CFG_DESC);;
        USBHDescHeader_t* pheader;
        while ((if_idx < USBH_MAX_NUM_INTERFACES) && (ptr < pdesc->wTotalLength))
        {
            pheader = get_next_desc(buf, &ptr);
            if (pheader->bDescriptorType == EDescType::INTERFACE)
            {
                USBHInterfaceDesc_t* pif = &pdesc->Itf_Desc[if_idx];
                parse_interface_desc(pif, reinterpret_cast<uint8_t*>(pheader));

                int8_t ep_idx = 0;
                USBHEpDesc_t* pep = nullptr;
                while ((ep_idx < pif->bNumEndpoints) && (ptr < pdesc->wTotalLength))
                {
                    pheader = get_next_desc(reinterpret_cast<uint8_t*>(pheader), &ptr);
                    if (pheader->bDescriptorType == EDescType::ENDPOINT)
                    {
                        pep = &pif->Ep_Desc[ep_idx];
                        parse_ep_desc(pep, reinterpret_cast<uint8_t*>(pheader));
                        ++ep_idx;
                    }
                }
                ++if_idx;
            }
        }
    }
}

void USBHCore::parse_ep_desc(USBHEpDesc_t *ep_desc, uint8_t *buf)
{
    memcpy(ep_desc, buf, 7);
    //ep_desc->wMaxPacketSize = __builtin_bswap16(ep_desc->wMaxPacketSize);
}

void USBHCore::parse_interface_desc(USBHInterfaceDesc_t *if_desc, uint8_t *buf)
{
    memcpy(if_desc, buf, 9);
}

USBHCore::USBHDescHeader_t* USBHCore::get_next_desc(uint8_t* buff, uint16_t* ptr)
{
    USBHDescHeader_t* pnext = reinterpret_cast<USBHDescHeader_t*>(buff);
    *ptr += pnext->bLength;
    pnext = reinterpret_cast<USBHDescHeader_t*>((buff + pnext->bLength));
    return pnext;
}

USBHCore::EStatus USBHCore::handle_control()
{
    STM32_HCD::EURBState urb_state = STM32_HCD::EURBState::IDLE;
    EReqDir direction;
    EStatus status = EStatus::BUSY;
    switch (m_control.state)
    {
    case ECTRLState::SETUP:
        ctrl_send_setup(reinterpret_cast<uint8_t*>(m_control.setup.d8), m_control.pipe_out);
        m_control.state = ECTRLState::SETUP_WAIT;
        break;
    case ECTRLState::SETUP_WAIT:
        urb_state = m_hcd->HC_get_URB_state(m_control.pipe_out);
        if (urb_state == STM32_HCD::EURBState::DONE)
        {
            direction = static_cast<EReqDir>(m_control.setup.b.bmRequestType & static_cast<uint8_t>(EReqDir::DIR_MASK));
            if (m_control.setup.b.wLength.w != 0)
            {
                if (direction == EReqDir::D2H)
                    m_control.state = ECTRLState::DATA_IN;
                else
                    m_control.state = ECTRLState::DATA_OUT;
            }
            else
            {
                if (direction == EReqDir::D2H)
                    m_control.state = ECTRLState::STATUS_OUT;
                else
                    m_control.state = ECTRLState::STATUS_IN;
            }
#if (USBH_USE_OS == 1)
            send_message();
#endif
        }
        else if (urb_state == STM32_HCD::EURBState::ERROR)
        {
            m_control.state = ECTRLState::ERROR;
#if (USBH_USE_OS == 1)
            send_message();
#endif
        }
        break;
    case ECTRLState::DATA_IN:
        m_control.timer = static_cast<uint16_t>(m_timer);
        ctrl_recieve_data(m_control.buff, m_control.length, m_control.pipe_in);
        m_control.state = ECTRLState::DATA_IN_WAIT;
        break;
    case ECTRLState::DATA_IN_WAIT:
        urb_state = m_hcd->HC_get_URB_state(m_control.pipe_in);
        if (urb_state == STM32_HCD::EURBState::DONE)
        {
            m_control.state = ECTRLState::STATUS_OUT;
#if (USBH_USE_OS == 1)
            send_message();
#endif
        }
        else if (urb_state == STM32_HCD::EURBState::STALL)
        {
            status = EStatus::FAIL;
#if (USBH_USE_OS == 1)
            send_message();
#endif
        }
        else if (urb_state == STM32_HCD::EURBState::ERROR)
        {
            m_control.state = ECTRLState::ERROR;
#if (USBH_USE_OS == 1)
            send_message();
#endif
        }
        break;
    case ECTRLState::DATA_OUT:
        m_control.timer = static_cast<uint16_t>(m_timer);
        ctrl_send_data(m_control.buff, m_control.length, m_control.pipe_out, true);
        m_control.state = ECTRLState::DATA_OUT_WAIT;
        break;
    case ECTRLState::DATA_OUT_WAIT:
        urb_state = m_hcd->HC_get_URB_state(m_control.pipe_out);
        if (urb_state == STM32_HCD::EURBState::DONE)
        {
            m_control.state = ECTRLState::STATUS_IN;
#if (USBH_USE_OS == 1)
            send_message();
#endif
        }
        else if (urb_state == STM32_HCD::EURBState::STALL)
        {
            m_control.state = ECTRLState::STALLED;
            status = EStatus::FAIL;
#if (USBH_USE_OS == 1)
            send_message();
#endif
        }
        else if (urb_state == STM32_HCD::EURBState::NOT_READY)
        {
            m_control.state = ECTRLState::DATA_OUT;
#if (USBH_USE_OS == 1)
            send_message();
#endif
        }
        else if (urb_state == STM32_HCD::EURBState::ERROR)
        {
            m_control.state = ECTRLState::ERROR;
            status = EStatus::FAIL;
#if (USBH_USE_OS == 1)
            send_message();
#endif
        }
        break;
    case ECTRLState::STATUS_IN:
        m_control.timer = static_cast<uint16_t>(m_timer);
        ctrl_recieve_data(nullptr, 0, m_control.pipe_in);
        m_control.state = ECTRLState::STATUS_IN_WAIT;
        break;
    case ECTRLState::STATUS_IN_WAIT:
        urb_state = m_hcd->HC_get_URB_state(m_control.pipe_in);
        if (urb_state == STM32_HCD::EURBState::DONE)
        {
            m_control.state = ECTRLState::COMPLETE;
            status = EStatus::OK;
#if (USBH_USE_OS == 1)
            send_message();
#endif
        }
        else if (urb_state == STM32_HCD::EURBState::STALL)
        {
            status = EStatus::FAIL;
#if (USBH_USE_OS == 1)
            send_message();
#endif
        }
        else if (urb_state == STM32_HCD::EURBState::ERROR)
        {
            m_control.state = ECTRLState::ERROR;
#if (USBH_USE_OS == 1)
            send_message();
#endif
        }
        break;
    case ECTRLState::STATUS_OUT:
        m_control.timer = static_cast<uint16_t>(m_timer);
        ctrl_send_data(nullptr, 0, m_control.pipe_out, true);
        m_control.state = ECTRLState::STATUS_OUT_WAIT;
        break;
    case ECTRLState::STATUS_OUT_WAIT:
        urb_state = m_hcd->HC_get_URB_state(m_control.pipe_out);
        if (urb_state == STM32_HCD::EURBState::DONE)
        {
            m_control.state = ECTRLState::COMPLETE;
            status = EStatus::OK;
#if (USBH_USE_OS == 1)
            send_message();
#endif
        }
        else if (urb_state == STM32_HCD::EURBState::NOT_READY)
        {
            m_control.state = ECTRLState::STATUS_OUT;
#if (USBH_USE_OS == 1)
            send_message();
#endif
        }
        else if (urb_state == STM32_HCD::EURBState::ERROR)
        {
            m_control.state = ECTRLState::ERROR;
#if (USBH_USE_OS == 1)
            send_message();
#endif
        }
        break;
    case ECTRLState::ERROR:
        if (++m_control.errorcount <= USBH_MAX_ERROR_COUNT)
        {
            m_hcd->stop();
            m_control.state = ECTRLState::SETUP;
            m_request_state = ECMDState::SEND;
        }
        else
        {
            m_user(this, EHostUser::UNRECOVERED_ERROR);
            m_control.errorcount = 0;
            USBH_ErrLog("Control error");
            status = EStatus::FAIL;
        }
        break;
    case ECTRLState::IDLE:
    case ECTRLState::STALLED:
    case ECTRLState::COMPLETE:
        break;
    }
    return status;
}

#ifdef STM32_USE_USB_HS
USBHCore usb_HS;
#endif

#ifdef STM32_USE_USB_FS
USBHCore usb_FS;
#endif

#endif //STM32_USE_USB_HOST
