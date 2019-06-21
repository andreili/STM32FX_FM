#include "usbh_hid.h"
#include <cstring>

#ifdef STM32_USE_USB_HOST

USBH_HID::USBH_HID()
    : m_iface_count (0)
    , m_type_mask (EType::NONE)
    , m_on_report (nullptr)
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
                memcpy(m_iface_current->data_in_buf, m_iface_current->data_in, m_iface_current->length);
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

uint8_t* USBH_HID::get_reports_data(uint8_t iface)
{
    debug_fn();
    if (iface >= m_iface_count)
        return nullptr;

    HIDIfaceTypeDef* pdef = &m_iface[iface];
    if (pdef->length == 0)
        return nullptr;
    switch (pdef->type)
    {
    case EType::MOUSE:
    case EType::KEYBOARD:
        return pdef->data_in_buf;
    case EType::NONE:
    case EType::UNKNOWN:
        break;
    }
    return nullptr;
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

void USBH_HID::parse_HID_report_descriptor(uint16_t size)
{
    uint8_t* data = m_host->get_dev_data();

    uint16_t pos = 0;
    AppCollectionTypeDef* collection = &m_iface_current->collection;
    collection->NbrReportFmt = 0;
    ReportDataTypeDef* report = &collection->ReportData[0];
    ReportDataTypeDef report_cur;
    bool is_collection = false;
    uint8_t start_byte[2] = {0,0};
    uint8_t start_bit[2] = {0,0};
    while (pos < size)
    {
        uint8_t b0 = data[pos++];
        uint8_t bSize = b0 & 0x03;
        bSize = (bSize == 3) ? 4 : bSize;
        uint8_t bType = (b0 >> 2) & 0x03;
        uint8_t bTag = (b0 >> 4) & 0x0f;

        if ((bType == 0x03) && (bTag == 0x0f) && (bSize == 2) && ((pos + 2) < size))
        {
            USBH_ErrLog("Long data not supported!!!\n\r");
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
                case 0x09:
                case 0x0B:
                    if (report_cur.UsagePage == EUsagePage::UNDEFINED)
                        report_cur.UsagePage = collection->UsagePage;
                    report_cur.ReportType = static_cast<EReportType>(bTag - 0x08);
                    report_cur.Flag = itemVal;

                    if (report_cur.ReportType == EReportType::INPUT)
                    {
                        report_cur.StartByte = start_byte[0];
                        start_bit[0] += report_cur.ReportSize * report_cur.ReportCnt;
                        start_byte[0] += start_bit[0] / 8;
                        start_bit[0] %= 8;
                    }
                    else
                    {
                        report_cur.StartByte = start_byte[1];
                        start_bit[1] += report_cur.ReportSize * report_cur.ReportCnt;
                        start_byte[1] += start_bit[1] >> 3;
                        start_bit[1] &= 0x07;
                    }

                    memcpy(report, &report_cur, sizeof(ReportDataTypeDef));
                    if (m_on_report != nullptr)
                        m_on_report(this, report);

                    report = &collection->ReportData[++collection->NbrReportFmt];
                    break;
                case 0x0A:
                    is_collection = true;
                    memset(&report_cur, 0, sizeof(ReportDataTypeDef));
                    report_cur.UsagePage = collection->UsagePage;
                    report_cur.Usage[0] = collection->Usage;
                    report_cur.NbrUsage = 1;
                    break;
                case 0x0C:
                    is_collection = false;
                    break;
                default:
                    break;
                }
            }
            else if (bType == 0x01)
            {
                switch (bTag)
                {
                case 0x00:
                    if (is_collection)
                        report_cur.UsagePage = static_cast<EUsagePage>(itemVal);
                    else
                        collection->UsagePage = static_cast<EUsagePage>(itemVal);
                    break;
                case 0x01:
                    report_cur.LogMin = itemVal;
                    break;
                case 0x02:
                    report_cur.LogMax = itemVal;
                    break;
                case 0x03:
                    report_cur.PhyMin = itemVal;
                    break;
                case 0x04:
                    report_cur.PhyMax = itemVal;
                    break;
                case 0x05:
                    report_cur.UnitExp = (itemVal < 8) ? itemVal : (itemVal - 16);
                    break;
                case 0x06:
                    report_cur.Unit = itemVal;
                    break;
                case 0x07:
                    report_cur.ReportSize = itemVal;
                    break;
                case 0x08:
                    report_cur.ReportID = itemVal;
                    break;
                case 0x09:
                    report_cur.ReportCnt = itemVal;
                    break;
                case 0x0A:
                    USBH_ErrLog("Push\n\r");
                    break;
                case 0x0B:
                    USBH_ErrLog("Pop\n\r");
                    break;
                default:
                    USBH_ErrLog("Unknown (Tag=0x%02X Type=0x%02X)\n\r", bTag, bType);
                    break;
                }
            }
            else if (bType == 0x02)
            {
                switch (bTag)
                {
                case 0x00:
                    if (is_collection)
                        report_cur.Usage[report_cur.NbrUsage++] = itemVal;
                    else
                        collection->Usage = itemVal;
                    break;
                case 0x01:
                    report_cur.UsageMin = itemVal;
                    break;
                case 0x02:
                    report_cur.UsageMax = itemVal;
                    break;
                case 0x03:
                    USBH_ErrLog("Designator Index=%d\n\r", itemVal);
                    break;
                case 0x04:
                    USBH_ErrLog("Designator Minimum=%d\n\r", itemVal);
                    break;
                case 0x05:
                    USBH_ErrLog("Designator Maximum=%d\n\r", itemVal);
                    break;
                case 0x07:
                    USBH_ErrLog("String Index=%d\n\r", itemVal);
                    break;
                case 0x08:
                    USBH_ErrLog("String Minimum=%d\n\r", itemVal);
                    break;
                case 0x09:
                    USBH_ErrLog("String Maximum=%d\n\r", itemVal);
                    break;
                case 0x0A:
                    USBH_ErrLog("Delimiter=%d\n\r", itemVal);
                    break;
                default:
                    USBH_ErrLog("Unknown (Tag=0x%02X Type=0x%02X)\n\r", bTag, bType);
                    break;
                }
            }
            else
            {
                USBH_ErrLog("Unknown (Tag=0x%02X Type=0x%02X)\n\r", bTag, bType);
            }
        }
    }
}

#endif //STM32_USE_USB_HOST
