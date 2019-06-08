#include "usbh_hid.h"
#include <cstring>

#ifdef STM32_USE_USB_HOST

USBH_HID::USBH_HID()
    : m_iface_count (0)
    , m_type_mask (EType::NONE)
{
}

USBHCore::EStatus USBH_HID::init(USBHCore* host)
{
    debug_fn();
    m_host = host;


    for (int interface=0 ; interface<USBH_MAX_NUM_INTERFACES ; ++interface)
    {
        USBHCore::USBHInterfaceDesc_t* pif = m_host->get_interface(interface);
        xprintf("Iface #%d, class=%d, subclass=%d proto=%d\n\r", interface, pif->bInterfaceClass,
                pif->bInterfaceSubClass, pif->bInterfaceProtocol);

        // check only for HID interfaces
        if ((pif->bInterfaceClass != get_class_code()) ||
            (pif->bInterfaceSubClass != HID_BOOT_CODE))
            continue;

        if (m_host->get_current_interface() == nullptr)
            m_host->select_interface(interface);

        HIDIfaceTypeDef *pdif = &m_iface[m_iface_count++];
        pdif->idx = interface;
        pdif->pif = pif;
        pdif->state = EState::ERROR;
        pdif->parent = this;

        switch (pif->bInterfaceProtocol)
        {
        case HID_KEYBRD_BOOT_CODE:
            USBH_UsrLog("KeyBoard device found!");
            pdif->type = EType::KEYBOARD;
            m_type_mask |= EType::KEYBOARD;
            break;
        case HID_MOUSE_BOOT_CODE:
            USBH_UsrLog("Mouse device found!");
            pdif->type = EType::MOUSE;
            m_type_mask |= EType::MOUSE;
            break;
        default:
            USBH_UsrLog("Protocol 0x#%02X not supported.", pif->bInterfaceProtocol);
            pdif->type = EType::UNKNOWN;
            return USBHCore::EStatus::FAIL;
        }

        pdif->state = EState::INIT;
        pdif->ctl_state = ECtlState::REQ_INIT;
        pdif->ep_addr = pif->Ep_Desc[0].bEndpointAddress;
        pdif->length = pif->Ep_Desc[0].wMaxPacketSize;
        pdif->poll = pif->Ep_Desc[0].bInterval;
        pdif->interface = pif->bInterfaceNumber;
        if (pdif->poll < HID_MIN_POLL)
            pdif->poll = HID_MIN_POLL;
        memset(pdif->data_in, 0, HID_DATA_SIZE);
        memset(pdif->data_out, 0, HID_DATA_SIZE);

        if (pif->bNumEndpoints != 1)
        {
            USBH_DbgLog("Interface contain %d End Points - not supported!.", pif->bNumEndpoints);
            return USBHCore::EStatus::FAIL;
        }

        USBHCore::USBHEpDesc_t* pep = &pif->Ep_Desc[0];
        if (pep->bEndpointAddress & 0x80)
        {
            pdif->in_ep = pep->bEndpointAddress;
            pdif->in_pipe = m_host->alloc_pipe(pdif->in_ep);
            m_host->open_pipe(pdif->in_pipe,
                              pdif->in_ep,
                              m_host->get_dev_addr(),
                              m_host->get_dev_speed(),
                              STM32_HCD::EEPType::INTR,
                              pdif->length);
            m_host->LL_set_toggle(pdif->in_pipe, 0);
        }
        else
        {
            pdif->out_ep = pep->bEndpointAddress;
            pdif->out_pipe = m_host->alloc_pipe(pdif->out_ep);
            m_host->open_pipe(pdif->out_pipe,
                              pdif->out_ep,
                              m_host->get_dev_addr(),
                              m_host->get_dev_speed(),
                              STM32_HCD::EEPType::INTR,
                              pdif->length);
            m_host->LL_set_toggle(pdif->out_pipe, 0);
        }
    }

    if (m_iface_count == 0)
    {
        USBH_DbgLog("Cannot Find the interface for %s class.", get_name());
        return USBHCore::EStatus::FAIL;
    }

    m_iface_current = &m_iface[0];
    m_iface_idx = 0;

    return USBHCore::EStatus::OK;
}

USBHCore::EStatus USBH_HID::deInit()
{
    for (int interface=0 ; interface<m_iface_count ; ++interface)
    {
        HIDIfaceTypeDef *pdif = &m_iface[interface];
        if (pdif->in_pipe != 0)
        {
            m_host->close_pipe(pdif->in_pipe);
            m_host->free_pipe(pdif->in_pipe);
            pdif->in_pipe = 0;
        }
        if (pdif->out_pipe != 0)
        {
            m_host->close_pipe(pdif->out_pipe);
            m_host->free_pipe(pdif->out_pipe);
            pdif->out_pipe = 0;
        }
    }
    return USBHCore::EStatus::OK;
}

USBHCore::EStatus USBH_HID::class_request()
{
    switch (m_iface_current->ctl_state)
    {
    case ECtlState::REQ_INIT:
        [[clang::fallthrough]];
    case ECtlState::REQ_GET_HID_DESC:
        if (get_HID_descriptor(USB_HID_DESC_SIZE) == USBHCore::EStatus::OK)
        {
            parse_HID_desc();
            m_iface_current->ctl_state = ECtlState::REQ_GET_REPORT_DESC;
        }
        break;
    case ECtlState::REQ_GET_REPORT_DESC:
        if (get_HID_report_descriptor(m_iface_current->pif->HID_desc.wDescriptorLength, m_iface_current->interface) == USBHCore::EStatus::OK)
        {
            parse_HID_report_descriptor(m_iface_current->pif->HID_desc.wDescriptorLength);
            m_iface_current->ctl_state = ECtlState::REQ_NEXT_IFACE;
        }
        break;
    case ECtlState::REQ_NEXT_IFACE:
        m_iface_current->ctl_state = ECtlState::REQ_SET_IDLE;
        if (switch_to_next_interface())
            m_iface_current->ctl_state = ECtlState::REQ_GET_REPORT_DESC;
        break;
    case ECtlState::REQ_SET_IDLE:
        switch (set_idle(0, 0))
        {
        case USBHCore::EStatus::OK:
            m_iface_current->ctl_state = ECtlState::REQ_SET_PROTOCOL;
            break;
        case USBHCore::EStatus::NOT_SUPPORTED:
            m_iface_current->ctl_state = ECtlState::REQ_SET_PROTOCOL;
            break;
        default:
            break;
        }
        break;
    case ECtlState::REQ_SET_PROTOCOL:
        if (set_protocol(0) == USBHCore::EStatus::OK)
        {
            m_iface_current->ctl_state = ECtlState::REQ_IDLE;
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
    switch (m_iface_current->state)
    {
    case EState::INIT:
        // NOTHING
    [[clang::fallthrough]];
    case EState::IDLE:
        if (get_report(0x01, m_iface_current->interface, m_iface_current->data_in,
                       m_iface_current->length) == USBHCore::EStatus::OK)
        {
            m_iface_current->state = EState::SYNC;
            if (switch_to_next_interface())
                return USBHCore::EStatus::OK;
        }
        break;
    case EState::SYNC:
        /* Sync with start of Even Frame */
        if (m_host->get_timer() & 1)
            m_iface_current->state = EState::GET_DATA;
#if (USBH_USE_OS == 1)
        m_host->send_message();
#endif
        break;
    case EState::GET_DATA:
        m_host->interrupt_recieve_data(m_iface_current->data_in, m_iface_current->length, m_iface_current->in_pipe);
        m_iface_current->state = EState::POLL;
        m_iface_current->timer = m_host->get_timer();
        m_iface_current->data_ready = false;
        if (switch_to_next_interface())
            return USBHCore::EStatus::OK;
        break;
    case EState::POLL:
        switch (m_host->LL_get_URB_state(m_iface_current->in_pipe))
        {
        case STM32_HCD::EURBState::DONE:
            if (!m_iface_current->data_ready)
            {
                m_iface_current->data_ready = true;
#if (USBH_USE_OS == 1)
                m_host->send_message();
#endif
            }
            break;
        case STM32_HCD::EURBState::STALL:
            if (m_host->clr_feature(m_iface_current->ep_addr) == USBHCore::EStatus::OK)
            {
                m_iface_current->state = EState::GET_DATA;
                switch_to_next_interface();
            }
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
    if (m_iface_current->state == EState::POLL)
        if ((m_host->get_timer() - m_iface_current->timer) >= m_iface_current->poll)
        {
            m_iface_current->state = EState::GET_DATA;
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
        return m_iface[0].poll;
    default:
        return 0;
    }
}

USBH_HID::HIDIfaceTypeDef* USBH_HID::get_iface_for_type(EType type)
{
    for (int interface=0 ; interface<m_iface_count ; ++interface)
    {
        HIDIfaceTypeDef *pdif = &m_iface[interface];
        if (pdif->type == type)
            return pdif;
    }
    return nullptr;
}

USBHCore::EStatus USBH_HID::get_reports_data(uint8_t iface, uint8_t *data)
{
    debug_fn();
    if (iface >= m_iface_count)
        return USBHCore::EStatus::FAIL;

    HIDIfaceTypeDef* pdef = &m_iface[iface];
    if (pdef->length == 0)
        return USBHCore::EStatus::FAIL;
    switch (pdef->type)
    {
    case EType::MOUSE:
    case EType::KEYBOARD:
        memcpy(data, pdef->data_in, pdef->length);
        return USBHCore::EStatus::OK;
    case EType::NONE:
    case EType::UNKNOWN:
        break;
    }
    return USBHCore::EStatus::FAIL;
}

bool USBH_HID::switch_to_next_interface()
{
    if (++m_iface_idx >= m_iface_count)
    {
        m_iface_idx = 0;
        m_iface_current = &m_iface[0];
        return false;
    }
    else
    {
        m_iface_current = &m_iface[m_iface_idx];
        return true;
    }
}

void USBH_HID::parse_HID_desc()
{
    memcpy(&m_HID_Desc, m_host->get_dev_data(), sizeof(DescTypeDef));
}

USBHCore::EStatus USBH_HID::get_HID_report_descriptor(uint16_t size, uint8_t iface_idx)
{
    return m_host->get_descriptor(USBHCore::EReqRecipient::REQ_INTERFACE | USBHCore::EReqType::STANDARD,
                                  USB_DESC_HID_REPORT, iface_idx, m_host->get_dev_data(), size);
}

const char* get_collection_descr(uint8_t col)
{
    switch (col)
    {
    case 0:
        return "Physical";
    case 1:
        return "Application";
    case 2:
        return "Logical";
    case 3:
        return "Report";
    case 4:
        return "Named Array";
    case 5:
        return "Usage Switch";
    case 6:
        return "Usage Modifier";
    case 0x80 ... 0xFF:
        return "Vendor Defined";
    case 0x07 ... 0x7F:
        return "Reserved";
    }
}

const char* get_usage_page(uint16_t page)
{
    switch (page)
    {
    case 0x00:
        return "Undefined";
    case 0x01:
        return "Generic Desktop Ctrls";
    case 0x02:
        return "Sim Ctrls";
    case 0x03:
        return "VR Ctrls";
    case 0x04:
        return "Sport Ctrls";
    case 0x05:
        return "Game Ctrls";
    case 0x06:
        return "Generic Dev Ctrls";
    case 0x07:
        return "Kbrd/Keypad";
    case 0x08:
        return "LEDs";
    case 0x09:
        return "Button";
    case 0x0A:
        return "Ordinal";
    case 0x0B:
        return "Telephony";
    case 0x0C:
        return "Consumer";
    case 0x0D:
        return "Digitizer";
    case 0x0E:
        return "Reserved 0x0E";
    case 0x0F:
        return "PID Page";
    case 0x10:
        return "Unicode";
    case 0x11:
        return "Reserved 0x11";
    case 0x12:
        return "Reserved 0x12";
    case 0x13:
        return "Reserved 0x13";
    case 0x14:
        return "Alphanumeric Display";
    case 0x40:
        return "Medical Instruments";
    case 0x80:
    case 0x81:
    case 0x82:
    case 0x83:
        return "Monitor Pages";
    case 0x84:
    case 0x85:
    case 0x86:
    case 0x87:
        return "Power Pages";
    case 0x8C:
        return "Bar Code Scanner Page";
    case 0x8D:
        return "Scale Page";
    case 0x8E:
        return "MagStripe Reading Devices";
    case 0x8F:
        return "Rsv'ed Point-of-Sale Pages";
    case 0x90:
        return "Camera Control Page";
    case 0x91:
        return "Arcade Page";
    case 0x0092 ... 0xFEFF:
        return "Reserved";
    case 0xFF00 ... 0xFFFF:
        return "Vendor Defined";
    default:
        return "-NONE-";
    }
}

const char* get_usage(uint8_t page, uint16_t usage)
{
    switch (page)
    {
    case 0x00:
        return "Undefined";
        break;
    case 0x01: // generic desktop
        switch (usage)
        {
        case 0x00:
            return "Undefined";
        case 0x01:
            return "Pointer";
        case 0x02:
            return "Mouse";
        case 0x03:
            return "Reserved";
        case 0x04:
            return "Joystick";
        case 0x05:
            return "Game Pad";
        case 0x06:
            return "Keyboard";
        case 0x07:
            return "Keypad";
        case 0x08:
            return "Multi-axis Controller";
        case 0x09 ... 0x2F:
            return "Reserved";
        case 0x30:
            return "X";
        case 0x31:
            return "Y";
        case 0x32:
            return "Z";
        case 0x33:
            return "Rx";
        case 0x34:
            return "Ry";
        case 0x35:
            return "Rz";
        case 0x36:
            return "Slider";
        case 0x37:
            return "Dial";
        case 0x38:
            return "Wheel";
        case 0x39:
            return "Hat switch";
        case 0x3A:
            return "Counted Buffer";
        case 0x3B:
            return "Byte Count";
        case 0x3C:
            return "Motion Wakeup";
        case 0x3D:
            return "Start";
        case 0x3E:
            return "Select";
        case 0x3F:
            return "Reserved";
        case 0x40:
            return "Vx";
        case 0x41:
            return "Vy";
        case 0x42:
            return "Vz";
        case 0x43:
            return "Vbrx";
        case 0x44:
            return "Vbry";
        case 0x45:
            return "Vbrz";
        case 0x46:
            return "Vno";
        case 0x47:
            return "Feature Notification";
        case 0x48:
            return "Resolution Multiplier";
        case 0x49 ... 0x7F:
            return "Reserved";
        case 0x80 ... 0xFF:
            return "-NONE-LAZY-";
        }
        break;
    case 0x07:
        return "-KEYBOARD-";
    case 0x08:
        switch (usage)
        {
        case 0x00:
            return "Undefined";
        case 0x01:
            return "Num Lock";
        case 0x02:
            return "Caps Lock";
        case 0x03:
            return "Scroll Lock";
        case 0x04:
            return "Compose";
        case 0x05:
            return "Kana";
        case 0x06:
            return "Power";
        case 0x07:
            return "Shift";
        case 0x08:
            return "Do Not Disturb";
        case 0x09:
            return "Mute";
        default:
            return "-LAZY-";
        }
        break;
    case 0x09:
    case 0x0A:
    case 0x10:
    default:
        return "-NONE-";
    }
    return "-NONE-";
}

void USBH_HID::parse_HID_report_descriptor(uint16_t size)
{
    uint8_t* data = m_host->get_dev_data();

    uint16_t pos = 0;
    while (pos < size)
    {
        uint8_t b0 = data[pos++];
        uint8_t bSize = b0 & 0x03;
        bSize = (bSize == 3) ? 4 : bSize;
        uint8_t bType = (b0 >> 2) & 0x03;
        uint8_t bTag = (b0 >> 4) & 0x0f;

        if ((bType == 0x03) && (bTag == 0x0f) && (bSize == 2) && ((pos + 2) < size))
        {
            xprintf("Long data not supported!!!\n\r");
        }
        else
        {
            uint8_t bSizeActual = 0;
            uint32_t itemVal = 0;
            for (uint8_t j=0 ; j<bSize ; ++j)
            {
                if ((pos + j) < size)
                {
                    itemVal += data[pos++] << (8 * j);
                    ++bSizeActual;
                }
            }

            if (bType == 0x00)
            {
                switch (bTag)
                {
                case 0x08:
                    xprintf("Input\n\r");
                    break;
                case 0x09:
                    xprintf("Output\n\r");
                    break;
                case 0x0B:
                    xprintf("Feature\n\r");
                    break;
                case 0x0A:
                    xprintf("Collection (%s)\n\r", get_collection_descr(itemVal));
                    break;
                case 0x0C:
                    xprintf("End Collection\n\r");
                    break;
                default:
                    xprintf("Unknown (Tag=0x%02X Type=0x%02X)\n\r", bTag, bType);
                    break;
                }
            }
            else if (bType == 0x01)
            {
                switch (bTag)
                {
                case 0x00:
                    xprintf("Usage Page(%s)\n\r", get_usage_page(itemVal));
                    m_report_desc.usage_page = itemVal;
                    break;
                case 0x01:
                    xprintf("Logical Minimum=%d\n\r", itemVal);
                    break;
                case 0x02:
                    xprintf("Logical Maximum=%d\n\r", itemVal);
                    break;
                case 0x03:
                    xprintf("Physical Minimum=%d\n\r", itemVal);
                    break;
                case 0x04:
                    xprintf("Physical Maximum=%d\n\r", itemVal);
                    break;
                case 0x05:
                    xprintf("Unit Exponent=%d\n\r", (itemVal < 8) ? itemVal : (itemVal - 16));
                    break;
                case 0x06:
                    xprintf("Unit=UNSUPPORTED\n\r");
                    break;
                case 0x07:
                    xprintf("Report Size=%d\n\r", itemVal);
                    break;
                case 0x08:
                    xprintf("Report ID=%d\n\r", itemVal);
                    break;
                case 0x09:
                    xprintf("Report Count=%d\n\r", itemVal);
                    break;
                case 0x0A:
                    xprintf("Push\n\r");
                    break;
                case 0x0B:
                    xprintf("Pop\n\r");
                    break;
                default:
                    xprintf("Unknown (Tag=0x%02X Type=0x%02X)\n\r", bTag, bType);
                    break;
                }
            }
            else if (bType == 0x02)
            {
                switch (bTag)
                {
                case 0x00:
                    xprintf("Usage (%s)\n\r", get_usage(m_report_desc.usage_page, itemVal));
                    break;
                case 0x01:
                    xprintf("Usage Minimum (%s)\n\r", get_usage(m_report_desc.usage_page, itemVal));
                    break;
                case 0x02:
                    xprintf("Usage Maximum (%s)\n\r", get_usage(m_report_desc.usage_page, itemVal));
                    break;
                case 0x03:
                    xprintf("Designator Index=%d\n\r", itemVal);
                    break;
                case 0x04:
                    xprintf("Designator Minimum=%d\n\r", itemVal);
                    break;
                case 0x05:
                    xprintf("Designator Maximum=%d\n\r", itemVal);
                    break;
                case 0x07:
                    xprintf("String Index=%d\n\r", itemVal);
                    break;
                case 0x08:
                    xprintf("String Minimum=%d\n\r", itemVal);
                    break;
                case 0x09:
                    xprintf("String Maximum=%d\n\r", itemVal);
                    break;
                case 0x0A:
                    xprintf("Delimiter=%d\n\r", itemVal);
                    break;
                default:
                    xprintf("Unknown (Tag=0x%02X Type=0x%02X)\n\r", bTag, bType);
                    break;
                }
            }
            else
            {
                xprintf("Unknown (Tag=0x%02X Type=0x%02X)\n\r", bTag, bType);
            }
        }
    }
}

#endif //STM32_USE_USB_HOST
