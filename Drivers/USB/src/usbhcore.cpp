#include "usbhcore.h"

#define USBH_ADDRESS_DEFAULT                     0
#define USBH_ADDRESS_ASSIGNED                    1
#define USBH_MPS_DEFAULT                         0x40

#if (USBH_USE_OS == 1)
static void USBH_Process_OS(void const * argument)
{
    ((USBHCore*)argument)->process_OS();
}
#endif

void USBHCore::init(void (*puser)(USBHCore *,EHostUser), uint8_t id)
{
    m_id = id;
    m_active_class = nullptr;
    m_class_number = 0;
    deInit_state_machine();
    if (puser != nullptr)
        m_user = puser;
#if (USBH_USE_OS == 1)
#error TODO
#endif
    LL_init();
}

void USBHCore::deInit()
{
    deInit_state_machine();
    if (m_hcd != nullptr)
    {
        m_active_class->set_data(nullptr);
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

    int8_t if_idx = 0;
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

    int8_t if_idx = 0;
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
    osMessagePut ( phost->os_event, USBH_PORT_EVENT, 0);
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
            osMessagePut ( phost->os_event, USBH_PORT_EVENT, 0);
#endif
            break;
        }
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
                  USBH_EP_CONTROL,
                  m_control.pipe_size);

        open_pipe(m_control.pipe_out,
                  0x00,
                  m_device.address,
                  m_device.speed,
                  USBH_EP_CONTROL,
                  m_control.pipe_size);
#if (USBH_USE_OS == 1)
        osMessagePut ( phost->os_event, USBH_PORT_EVENT, 0);
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
            osMessagePut ( phost->os_event, USBH_STATE_CHANGED_EVENT, 0);
#endif
        }
        break;
    case EHostState::SET_CONFIGURATION:
        if (set_cfg(m_device.CfgDesc.bConfigurationValue) == STM32_RESULT_OK)
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
                if (m_class[idx]->get_class_code() == m_device.CfgDesc.Itf_Desc[m_device.current_interface].bInterfaceClass)
                {
                    m_active_class = m_class[idx];
                    break;
                }
            if (m_active_class != nullptr)
            {
                if (m_active_class->init(this) ==  STM32_RESULT_OK)
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
        osMessagePut ( phost->os_event, USBH_STATE_CHANGED_EVENT, 0);
#endif
        break;
    case EHostState::CLASS_REQUEST:
        if (m_active_class != nullptr)
        {
            if (m_active_class->request(this) == STM32_RESULT_OK)
                m_gstate = EHostState::CLASS;
        }
        else
        {
            m_gstate = EHostState::ABORT_STATE;
            USBH_ErrLog("Invalid Class Driver.");
        }
#if (USBH_USE_OS == 1)
        osMessagePut ( phost->os_event, USBH_STATE_CHANGED_EVENT, 0);
#endif
        break;
    case EHostState::CLASS:
        if (m_active_class != nullptr)
            m_active_class->bgnd_process(this);
        break;
    case EHostState::DEV_DISCONNECTED:
        deInit_state_machine();
        if (m_active_class != nullptr)
        {
            m_active_class->deInit(this);
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
    switch (m_state)
    {
    case EUSBState::IDLE:
        if (get_dev_desc(8) == STM32_RESULT_OK)
        {
            m_control.pipe_size = m_device.DevDesc.bMaxPacketSize;
            m_state = EUSBState::GET_FULL_DEV_DESC;

            open_pipe(m_control.pipe_in,
                      0x80,
                      m_device.address,
                      m_device.speed,
                      USBH_EP_CONTROL,
                      m_control.pipe_size);

            open_pipe(m_control.pipe_out,
                      0x00,
                      m_device.address,
                      m_device.speed,
                      USBH_EP_CONTROL,
                      m_control.pipe_size);
        }
        break;
    case EUSBState::GET_FULL_DEV_DESC:
        if (get_dev_desc(USB_DEVICE_DESC_SIZE) == STM32_RESULT_OK)
        {
            USBH_UsrLog("PID: %xh", m_device.DevDesc.idProduct );
            USBH_UsrLog("VID: %xh", m_device.DevDesc.idVendor );
            m_state = EUSBState::SET_ADDR;
        }
        break;
    case EUSBState::SET_ADDR:
        if (set_address(USBH_DEVICE_ADDRESS) == STM32_RESULT_OK)
        {
            STM32_SYSTICK::delay(2);
            m_device.address = USBH_DEVICE_ADDRESS;
            USBH_UsrLog("Address (#%d) assigned.", m_device.address);
            m_state = EUSBState::GET_CFG_DESC;

            open_pipe(m_control.pipe_in,
                      0x80,
                      m_device.address,
                      m_device.speed,
                      USBH_EP_CONTROL,
                      m_control.pipe_size);

            open_pipe(m_control.pipe_out,
                      0x00,
                      m_device.address,
                      m_device.speed,
                      USBH_EP_CONTROL,
                      m_control.pipe_size);
        }
        break;
    case EUSBState::GET_CFG_DESC:
        if (get_cfg_desc(m_device.CfgDesc.wTotalLength) == STM32_RESULT_OK)
            m_state = EUSBState::GET_FULL_CFG_DESC;
        break;
    case EUSBState::GET_FULL_CFG_DESC:
        if (get_cfg_desc(USB_CONFIGURATION_DESC_SIZE) == STM32_RESULT_OK)
            m_state = EUSBState::GET_MFC_STRING_DESC;
        break;
    case EUSBState::GET_MFC_STRING_DESC:
        if (m_device.DevDesc.iManufacturer != 0)
        {
            if (get_string_desc(m_device.DevDesc.iManufacturer,
                                m_device.Data, 0xff) == STM32_RESULT_OK)
            {
                USBH_UsrLog("Manufacturer : %s", (char *)m_device.Data);
            }
        }
        else
        {
            USBH_UsrLog("Manufacturer : N/A");
        }
        m_state = EUSBState::GET_PRODUCT_STRING_DESC;
#if (USBH_USE_OS == 1)
        osMessagePut( phost->os_event, USBH_STATE_CHANGED_EVENT, 0);
#endif
        break;
    case EUSBState::GET_PRODUCT_STRING_DESC:
        if (m_device.DevDesc.iProduct != 0)
        {
            if (get_string_desc(m_device.DevDesc.iProduct,
                                m_device.Data, 0xff) == STM32_RESULT_OK)
            {
                USBH_UsrLog("Product : %s", (char *)m_device.Data);
            }
        }
        else
        {
            USBH_UsrLog("Product : N/A");
        }
        m_state = EUSBState::GET_SERIALNUM_STRING_DESC;
#if (USBH_USE_OS == 1)
        osMessagePut ( phost->os_event, USBH_STATE_CHANGED_EVENT, 0);
#endif
        break;
    case EUSBState::GET_SERIALNUM_STRING_DESC:
        if (m_device.DevDesc.iSerialNumber != 0)
        {
            if (get_string_desc(m_device.DevDesc.iSerialNumber,
                                m_device.Data, 0xff) == STM32_RESULT_OK)
            {
                USBH_UsrLog("Serial Number : %s", (char *)m_device.Data);
                status = STM32_RESULT_OK;
            }
        }
        else
        {
            USBH_UsrLog("Serial Number : N/A");
            status = STM32_RESULT_OK;
        }
#if (USBH_USE_OS == 1)
        osMessagePut ( phost->os_event, USBH_STATE_CHANGED_EVENT, 0);
#endif
        break;
    }
    return status;
}

void USBHCore::handle_SOF()
{
    if ((m_gstate == EHostState::CLASS) && (m_active_class != nullptr))
        m_active_class->SOF_process(this);
}

void USBHCore::deInit_state_machine()
{
    for (int i=0 ; i<USBH_MAX_PIPES_NBR ; ++i)
        m_pipes[i] = 0;
    for (int i=0 ; i<USBH_MAX_DATA_BUFFER ; ++i)
        m_device.Data[i] = 0;
    m_gstate = EHostState::IDLE;
    m_state = EUSBState::IDLE;
    m_request_state = ECMDState::SEND;
    m_timer = 0;

    m_control.state = ECTRLState::SETUP;
    m_control.pipe_size = USBH_MPS_DEFAULT;
    m_control.errorcount = 0;

    m_device.address = USBH_ADDRESS_DEFAULT;
    m_device.speed = EOTGSpeed::FULL;
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
    osMessagePut ( phost->os_event, USBH_PORT_EVENT, 0);
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
    osMessagePut ( phost->os_event, USBH_PORT_EVENT, 0);
#endif
}

void USBHCore::LL_init()
{
    if (m_id == HOST_FS)
    {
        m_hcd = &usb_fs;
        if (usb_fs.init(USB_OTG_FS, EOTG_PHY::EMBEDDED, false, true, EOTGSpeed::FULL, 8) != STM32_RESULT_OK)
            Error_Handler();
        LL_set_timer(usb_fs.get_current_frame());
    }
    else
    {
        m_hcd = &usb_hs;
        if (usb_hs.init(USB_OTG_HS, EOTG_PHY::EMBEDDED, false, true, EOTGSpeed::FULL, 12) != STM32_RESULT_OK)
            Error_Handler();
        LL_set_timer(usb_hs.get_current_frame());
    }
}

void USBHCore::LL_driver_VBUS(uint8_t state)
{
    if (this->m_id == HOST_FS)
    {
        if (state == RESET)
        {
#warning disable FS power
        }
        else
        {
#warning enable FS power
        }
    }
    else
    {
        if (state == RESET)
        {
#warning disable HS power
        }
        else
        {
#warning enable HS power
        }
    }
    STM32_SYSTICK::delay(200);
}

#if (USBH_USE_OS == 1)
void USBHCore::process_OS()
{
    osEvent event;
    for(;;)
    {
        event = osMessageGet(m_event, osWaitForever);
        if(event.status == osEventMessage)
            process();
    }
}
#endif

#ifdef STM32_USE_USB_HS
USBHCore usb_HS;
#endif

#ifdef STM32_USE_USB_FS
USBHCore usb_FS;
#endif
