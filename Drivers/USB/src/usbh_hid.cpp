#include "usbh_hid.h"
#include <cstring>

#ifdef STM32_USE_USB_HOST

USBHCore::EStatus USBH_HID::init(USBHCore* host)
{
    debug_fn();
    m_host = host;
    USBHClass* act_class = m_host->get_active_class();
    uint8_t interface = m_host->find_interface(act_class->get_class_code(), HID_BOOT_CODE, 0xff);
    if (interface == 0xff)
    {
        USBH_DbgLog("Cannot Find the interface for %s class.", act_class->get_name());
        return USBHCore::EStatus::FAIL;
    }
    m_host->select_interface(interface);

    m_state = EState::ERROR;

    USBHCore::USBHInterfaceDesc_t* iface = m_host->get_current_interface();
    if (iface->bInterfaceProtocol == HID_KEYBRD_BOOT_CODE)
    {
        USBH_UsrLog ("KeyBoard device found!");
        m_type = EType::KEYBOARD;
    }
    else if (iface->bInterfaceProtocol == HID_MOUSE_BOOT_CODE)
    {
        USBH_UsrLog ("Mouse device found!");
        m_type = EType::MOUSE;
    }
    else
    {
        USBH_UsrLog ("Protocol not supported.");
        m_type = EType::UNKNOWN;
        return USBHCore::EStatus::FAIL;
    }

    m_state = EState::INIT;
    m_ctl_state = ECtlState::REQ_INIT;
    m_ep_addr = iface->Ep_Desc[0].bEndpointAddress;
    m_length = iface->Ep_Desc[0].wMaxPacketSize;
    m_poll = iface->Ep_Desc[0].bInterval;
    if (m_poll < HID_MIN_POLL)
        m_poll = HID_MIN_POLL;

    for (int i=0 ; i<CUSTOM_DATA_SIZE ; ++i)
        m_custom_data[i] = 0;
    uint8_t *data = m_host->get_dev_data();
    for (int i=0 ; i<(HID_QUEUE_SIZE * REPORT_DATA_SIZE) ; ++i)
        data[i] = 0;
    m_fifo.init(m_host->get_dev_data(), HID_QUEUE_SIZE * REPORT_DATA_SIZE);

    /* Check fo available number of endpoints */
    /* Find the number of EPs in the Interface Descriptor */
    /* Choose the lower number in order not to overrun the buffer allocated */
    uint8_t max_ep = (iface->bNumEndpoints <= USBH_MAX_NUM_ENDPOINTS) ? iface->bNumEndpoints : USBH_MAX_NUM_ENDPOINTS;

    for (uint8_t num=0 ; num<max_ep ; ++num)
    {
        if (iface->Ep_Desc[num].bEndpointAddress & 0x80)
        {
            m_in_ep = iface->Ep_Desc[num].bEndpointAddress;
            m_in_pipe = m_host->alloc_pipe(m_in_ep);
            m_host->open_pipe(m_in_pipe,
                              m_in_ep,
                              m_host->get_dev_addr(),
                              m_host->get_dev_speed(),
                              STM32_HCD::EEPType::INTR,
                              m_length);
            m_host->LL_set_toggle(m_in_pipe, 0);
        }
        else
        {
            m_out_ep = iface->Ep_Desc[num].bEndpointAddress;
            m_out_pipe = m_host->alloc_pipe(m_out_ep);
            m_host->open_pipe(m_out_pipe,
                              m_out_ep,
                              m_host->get_dev_addr(),
                              m_host->get_dev_speed(),
                              STM32_HCD::EEPType::INTR,
                              m_length);
            m_host->LL_set_toggle(m_out_pipe, 0);
        }
    }
    return USBHCore::EStatus::OK;
}

USBHCore::EStatus USBH_HID::deInit()
{
    if (m_in_pipe != 0)
    {
        m_host->close_pipe(m_in_pipe);
        m_host->free_pipe(m_in_pipe);
        m_in_pipe = 0;
    }
    if (m_out_pipe != 0)
    {
        m_host->close_pipe(m_out_pipe);
        m_host->free_pipe(m_out_pipe);
        m_out_pipe = 0;
    }
    return USBHCore::EStatus::OK;
}

USBHCore::EStatus USBH_HID::class_request()
{
    switch (m_ctl_state)
    {
    case ECtlState::REQ_INIT:
    case ECtlState::REQ_GET_HID_DESC:
        if (get_HID_descriptor(USB_HID_DESC_SIZE) == USBHCore::EStatus::OK)
        {
            parse_HID_desc();
            m_ctl_state = ECtlState::REQ_GET_REPORT_DESC;
        }
        break;
    case ECtlState::REQ_GET_REPORT_DESC:
        if (get_HID_report_descriptor(m_HID_Desc.wItemLength) == USBHCore::EStatus::OK)
            m_ctl_state = ECtlState::REQ_SET_IDLE;
        break;
    case ECtlState::REQ_SET_IDLE:
        switch (set_idle(0, 0))
        {
        case USBHCore::EStatus::OK:
            m_ctl_state = ECtlState::REQ_SET_PROTOCOL;
            break;
        case USBHCore::EStatus::NOT_SUPPORTED:
            m_ctl_state = ECtlState::REQ_SET_PROTOCOL;
            break;
        default:
            break;
        }
        break;
    case ECtlState::REQ_SET_PROTOCOL:
        if (set_protocol(0) == USBHCore::EStatus::OK)
        {
            m_ctl_state = ECtlState::REQ_IDLE;
            m_host->to_user(USBHCore::EHostUser::CLASS_ACTIVE);
            return USBHCore::EStatus::OK;
        }
        break;
    case ECtlState::REQ_IDLE:
    default:
        break;
    }
    return USBHCore::EStatus::BUSY;
}

USBHCore::EStatus USBH_HID::process()
{
    debug_fn();
    switch (m_state)
    {
    case EState::INIT:
        // NOTHING
    [[clang::fallthrough]];
    case EState::IDLE:
        if (get_report(0x01, 0, m_custom_data, m_length) == USBHCore::EStatus::OK)
        {
            m_fifo.write(m_custom_data, m_length);
            m_state = EState::SYNC;
        }
        break;
    case EState::SYNC:
        /* Sync with start of Even Frame */
        if (m_host->get_timer() & 1)
            m_state = EState::GET_DATA;
#if (USBH_USE_OS == 1)
        m_host->send_message();
#endif
        break;
    case EState::GET_DATA:
        m_host->interrupt_recieve_data(m_custom_data, m_length, m_in_pipe);
        m_state = EState::POLL;
        m_timer = m_host->get_timer();
        m_data_ready = false;
        break;
    case EState::POLL:
        switch (m_host->LL_get_URB_state(m_in_pipe))
        {
        case STM32_HCD::EURBState::DONE:
            if (!m_data_ready)
            {
                m_fifo.write(m_custom_data, m_length);
                m_data_ready = true;
#if (USBH_USE_OS == 1)
                m_host->send_message();
#endif
            }
            break;
        case STM32_HCD::EURBState::STALL:
            if (m_host->clr_feature(m_ep_addr) == USBHCore::EStatus::OK)
                m_state = EState::GET_DATA;
            break;
        default:
            break;
        }
        break;
    case EState::SEND_DATA:
    case EState::BUSY:
    case EState::ERROR:
        break;
    }
    return USBHCore::EStatus::OK;
}

USBHCore::EStatus USBH_HID::SOF_process()
{
    debug_fn();
    if (m_state == EState::POLL)
        if ((m_host->get_timer() - m_timer) >= m_poll)
        {
            m_state = EState::GET_DATA;
#if (USBH_USE_OS == 1)
            m_host->send_message();
#endif
        }
    return USBHCore::EStatus::OK;
}

uint16_t USBH_HID::get_pool_interval()
{
    switch (m_host->get_state())
    {
    case USBHCore::EHostState::CLASS_REQUEST:
    case USBHCore::EHostState::INPUT:
    case USBHCore::EHostState::SET_CONFIGURATION:
    case USBHCore::EHostState::CHECK_CLASS:
    case USBHCore::EHostState::CLASS:
        return m_poll;
    default:
        return 0;
    }
}

USBHCore::EStatus USBH_HID::decode(uint8_t *data)
{
    debug_fn();
    if (m_length == 0)
        return USBHCore::EStatus::FAIL;
    switch (m_type)
    {
    case EType::MOUSE:
        break;
    case EType::KEYBOARD:
        if (m_fifo.read(data, m_length) == m_length)
            return USBHCore::EStatus::OK;
        break;
    case EType::UNKNOWN:
        break;
    }
    return USBHCore::EStatus::FAIL;
}

void USBH_HID::parse_HID_desc()
{
    memcpy(&m_HID_Desc, m_host->get_dev_data(), sizeof(DescTypeDef));
}

USBHCore::EStatus USBH_HID::get_HID_report_descriptor(uint16_t size)
{
    return m_host->get_descriptor(USBHCore::EReqRecipient::REQ_INTERFACE | USBHCore::EReqType::STANDARD,
                                  USB_DESC_HID_REPORT, m_host->get_dev_data(), size);
}

#endif //STM32_USE_USB_HOST
