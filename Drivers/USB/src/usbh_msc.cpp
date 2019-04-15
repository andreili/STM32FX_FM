#include "usbh_msc.h"

#ifdef STM32_USE_USB_HOST

#define USB_REQ_BOT_RESET                0xFF
#define USB_REQ_GET_MAX_LUN              0xFE

#define MSC_BOT                                        0x50
#define MSC_TRANSPARENT                                0x06

#define DATA_LEN_MODE_TEST_UNIT_READY        0
#define DATA_LEN_READ_CAPACITY10             8
#define DATA_LEN_INQUIRY                    36
#define DATA_LEN_REQUEST_SENSE              14

#define CBW_CB_LENGTH                       16
#define CBW_LENGTH                          10

USBHCore::EStatus USBH_MSC::init(USBHCore* host)
{
    debug_fn();
    m_host = host;
    USBHClass* act_class = m_host->get_active_class();
    uint8_t interface = m_host->find_interface(get_class_code(), MSC_TRANSPARENT, 0xff);
    if (interface == 0xff)
    {
        USBH_DbgLog("Cannot Find the interface for %s class.", act_class->get_name());
        return USBHCore::EStatus::FAIL;
    }
    m_host->select_interface(interface);

    USBHCore::USBHInterfaceDesc_t* iface = m_host->get_current_interface();
    for (int i=0 ; i<2 ; ++i)
    {
        if (iface->Ep_Desc[i].bEndpointAddress & 0x80)
        {
            m_in_ep = iface->Ep_Desc[i].bEndpointAddress;
            m_in_ep_size = iface->Ep_Desc[i].wMaxPacketSize;
        }
        else
        {
            m_out_ep = iface->Ep_Desc[i].bEndpointAddress;
            m_out_ep_size = iface->Ep_Desc[i].wMaxPacketSize;
        }
    }

    m_current_lun = 0;
    m_rw_lun = 0;
    m_state = EState::INIT;
    m_error = EError::OK;
    m_req_state = EReqState::REQ_IDLE;
    m_out_pipe = m_host->alloc_pipe(m_out_ep);
    m_in_pipe = m_host->alloc_pipe(m_in_ep);

    m_hbot.cbw.field.Signature = BOT_CBW_SIGNATURE;
    m_hbot.cbw.field.Tag = BOT_CBW_TAG;
    m_hbot.state = EBOTState::SEND_CBW;
    m_hbot.cmd_state = EBOTCMDState::SEND;

    memset(m_unit, 0, sizeof(MSC_LUN) * MAX_SUPPORTED_LUN);

    m_host->open_pipe(m_out_pipe,
                      m_out_ep,
                      m_host->get_dev_addr(),
                      m_host->get_dev_speed(),
                      STM32_HCD::EEPType::BULK,
                      m_out_ep_size);
    m_host->open_pipe(m_in_pipe,
                      m_in_ep,
                      m_host->get_dev_addr(),
                      m_host->get_dev_speed(),
                      STM32_HCD::EEPType::BULK,
                      m_in_ep_size);

    m_host->LL_set_toggle(m_in_pipe, 0);
    m_host->LL_set_toggle(m_out_pipe, 0);

    return USBHCore::EStatus::OK;
}

USBHCore::EStatus USBH_MSC::deInit()
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
    m_host = nullptr;
    return USBHCore::EStatus::OK;
}

USBHCore::EStatus USBH_MSC::class_request()
{
    USBHCore::EStatus status = USBHCore::EStatus::BUSY;
    switch (m_req_state)
    {
    case EReqState::REQ_IDLE:
    case EReqState::REQ_GET_MAX_LUN:
        status = BOT_get_max_LUN();
        switch (status)
        {
        case USBHCore::EStatus::NOT_SUPPORTED:
            m_max_lun = 0;
            status = USBHCore::EStatus::OK;
            break;
        case USBHCore::EStatus::OK:
            ++m_max_lun;
            USBH_UsrLog("Number of supported LUN: %d", m_max_lun);
            for (uint32_t i=0 ; i<m_max_lun ; ++i)
            {
                m_unit[i].prev_ready_state = USBHCore::EStatus::FAIL;
                m_unit[i].state_changed = 0;
            }
            break;
        case USBHCore::EStatus::BUSY:
        case USBHCore::EStatus::FAIL:
        case USBHCore::EStatus::UNRECOVERED_ERROR:
        case USBHCore::EStatus::ERROR_SPEED_UNKNOWN:
            break;
        }
        break;
    case EReqState::REQ_ERROR:
        if (m_host->clr_feature(0) == USBHCore::EStatus::OK)
            m_req_state = m_prev_req_state;
        break;
    case EReqState::REQ_RESET:
        break;
    }
    return status;
}

USBHCore::EStatus USBH_MSC::process()
{
    switch (m_state)
    {
    case EState::INIT:
        if (m_current_lun < m_max_lun)
        {
            MSC_LUN *lun = &m_unit[m_current_lun];
            lun->error = EError::NOT_READY;
            /* Switch MSC REQ state machine */
            switch (lun->state)
            {
            case EState::INIT:
                USBH_UsrLog("LUN #%d: ", m_current_lun);
                lun->state = EState::READ_INQUIRY;
                m_timer = m_host->get_timer();
                break;
            case EState::READ_INQUIRY:
                switch (SCSI_inquiry(m_current_lun))
                {
                case USBHCore::EStatus::OK:
                    USBH_UsrLog("Inquiry Vendor  : %s", lun->inquiry.vendor_id);
                    USBH_UsrLog("Inquiry Product : %s", lun->inquiry.product_id);
                    USBH_UsrLog("Inquiry Version : %s", lun->inquiry.revision_id);
                    lun->state = EState::TEST_UNIT_READY;
                    break;
                case USBHCore::EStatus::FAIL:
                    lun->state = EState::REQUEST_SENSE;
                    break;
                case USBHCore::EStatus::UNRECOVERED_ERROR:
                    lun->state = EState::IDLE;
                    lun->error = EError::ERROR;
                    break;
                case USBHCore::EStatus::BUSY:
                case USBHCore::EStatus::NOT_SUPPORTED:
                case USBHCore::EStatus::ERROR_SPEED_UNKNOWN:
                    break;
                }
                break;
            case EState::TEST_UNIT_READY:
                switch (SCSI_test_unit_ready(m_current_lun))
                {
                case USBHCore::EStatus::OK:
                    if (lun->prev_ready_state != USBHCore::EStatus::OK)
                    {
                        lun->state_changed = true;
                        USBH_UsrLog("MSC Device ready");
                    }
                    else
                        lun->state_changed = false;
                    lun->state = EState::READ_CAPACITY10;
                    lun->error = EError::OK;
                    lun->prev_ready_state = USBHCore::EStatus::OK;
                    break;
                case USBHCore::EStatus::FAIL:
                    if (lun->prev_ready_state != USBHCore::EStatus::FAIL)
                    {
                        lun->state_changed = true;
                        USBH_UsrLog("MSC Device NOT ready");
                    }
                    else
                        lun->state_changed = false;
                    lun->state = EState::REQUEST_SENSE;
                    lun->error = EError::NOT_READY;
                    lun->prev_ready_state = USBHCore::EStatus::FAIL;
                    break;
                case USBHCore::EStatus::UNRECOVERED_ERROR:
                    lun->state = EState::IDLE;
                    lun->error = EError::ERROR;
                    break;
                case USBHCore::EStatus::BUSY:
                case USBHCore::EStatus::NOT_SUPPORTED:
                case USBHCore::EStatus::ERROR_SPEED_UNKNOWN:
                    break;
                }
                break;
            case EState::READ_CAPACITY10:
                switch (SCSI_read_capacity(m_current_lun))
                {
                case USBHCore::EStatus::OK:
                    if (lun->state_changed)
                    {
                        USBH_UsrLog("MSC Device capacity : %ld Bytes", \
                                   lun->capacity.block_nbr * lun->capacity.block_size);
                        USBH_UsrLog("Block number : %d", lun->capacity.block_nbr);
                        USBH_UsrLog("Block Size   : %d", lun->capacity.block_size);
                    }
                    lun->state = EState::IDLE;
                    lun->error = EError::OK;
                    ++m_current_lun;
                    break;
                case USBHCore::EStatus::FAIL:
                    lun->state = EState::REQUEST_SENSE;
                    break;
                case USBHCore::EStatus::UNRECOVERED_ERROR:
                    lun->state = EState::IDLE;
                    lun->error = EError::ERROR;
                    break;
                case USBHCore::EStatus::BUSY:
                case USBHCore::EStatus::NOT_SUPPORTED:
                case USBHCore::EStatus::ERROR_SPEED_UNKNOWN:
                    break;
                }
                break;
            case EState::REQUEST_SENSE:
                switch (SCSI_request_sense(m_current_lun))
                {
                case USBHCore::EStatus::OK:
                    if ((lun->sense.key == SCSI_SENSE_KEY_UNIT_ATTENTION) ||
                        (lun->sense.key == SCSI_SENSE_KEY_NOT_READY))
                    {
                        if ((m_host->get_timer() - m_timer) < 10000)
                        {
                            lun->state = EState::TEST_UNIT_READY;
                            break;
                        }
                    }
                    USBH_UsrLog("Sense Key  : %x", lun->sense.key);
                    USBH_UsrLog("Additional Sense Code : %x", lun->sense.asc);
                    USBH_UsrLog("Additional Sense Code Qualifier: %x",lun->sense.ascq);
                    lun->state = EState::IDLE;
                    m_current_lun++;
                    break;
                case USBHCore::EStatus::FAIL:
                    USBH_UsrLog("MSC Device NOT ready");
                    lun->state = EState::UNRECOVERED_ERROR;
                    break;
                case USBHCore::EStatus::UNRECOVERED_ERROR:
                    lun->state = EState::IDLE;
                    lun->error = EError::ERROR;
                    break;
                case USBHCore::EStatus::BUSY:
                case USBHCore::EStatus::NOT_SUPPORTED:
                case USBHCore::EStatus::ERROR_SPEED_UNKNOWN:
                    break;
                }
                break;
            case EState::UNRECOVERED_ERROR:
                ++m_current_lun;
                break;
            case EState::IDLE:
            case EState::READ:
            case EState::WRITE:
            case EState::PERIODIC_CHECK:
                break;
            }
#if (USBH_USE_OS == 1)
            m_host->send_message();
#endif
        }
        else
        {
            m_current_lun = 0;
            m_state = EState::IDLE;
#if (USBH_USE_OS == 1)
            m_host->send_message();
#endif
            m_host->to_user(USBHCore::EHostUser::CLASS_ACTIVE);
        }
        break;
    case EState::IDLE:
        return USBHCore::EStatus::OK;
    case EState::TEST_UNIT_READY:
    case EState::READ_CAPACITY10:
    case EState::READ_INQUIRY:
    case EState::REQUEST_SENSE:
    case EState::READ:
    case EState::WRITE:
    case EState::UNRECOVERED_ERROR:
    case EState::PERIODIC_CHECK:
        break;
    }
    return USBHCore::EStatus::BUSY;
}

USBHCore::EStatus USBH_MSC::SOF_process()
{
    return USBHCore::EStatus::OK;
}

USBHCore::EStatus USBH_MSC::read(uint8_t lun, uint32_t address, uint8_t* buf, uint16_t length)
{
    if ((!m_host->is_connected()) ||
        (m_host->get_state() != USBHCore::EHostState::CLASS) ||
        (m_unit[lun].state != EState::IDLE))
        return USBHCore::EStatus::FAIL;

    m_state = EState::READ;
    m_unit[lun].state = EState::READ;
    m_rw_lun = lun;
    SCSI_read(lun, address, buf, length);
    uint32_t timeout = m_host->get_timer() + 10 * 1000 * length;
    while (rd_wr_process(lun) == USBHCore::EStatus::BUSY)
        if ((m_host->get_timer() > timeout) ||
            (!m_host->is_connected()))
        {
            m_state = EState::IDLE;
            return USBHCore::EStatus::FAIL;
        }
    m_state = EState::IDLE;
    return USBHCore::EStatus::OK;
}

USBHCore::EStatus USBH_MSC::write(uint8_t lun, uint32_t address, uint8_t* buf, uint16_t length)
{
    if ((!m_host->is_connected()) ||
        (m_host->get_state() != USBHCore::EHostState::CLASS) ||
        (m_unit[lun].state != EState::IDLE))
        return USBHCore::EStatus::FAIL;

    m_state = EState::WRITE;
    m_unit[lun].state = EState::WRITE;
    m_rw_lun = lun;
    SCSI_write(lun, address, buf, length);
    uint32_t timeout = m_host->get_timer() + 10 * 1000 * length;
    while (rd_wr_process(lun) == USBHCore::EStatus::BUSY)
        if ((m_host->get_timer() > timeout) ||
            (!m_host->is_connected()))
        {
            m_state = EState::IDLE;
            return USBHCore::EStatus::FAIL;
        }
    m_state = EState::IDLE;
    return USBHCore::EStatus::OK;
}

USBHCore::EStatus USBH_MSC::rd_wr_process(uint8_t lun)
{
    USBHCore::EStatus error = USBHCore::EStatus::BUSY;
    USBHCore::EStatus scsi_status = USBHCore::EStatus::BUSY;

    MSC_LUN* p_lun = &m_unit[lun];
    switch (p_lun->state)
    {
    case EState::READ:
        scsi_status = SCSI_read(lun, 0, nullptr, 0);
        switch (scsi_status)
        {
        case USBHCore::EStatus::OK:
            p_lun->state = EState::IDLE;
            error = USBHCore::EStatus::OK;
            break;
        case USBHCore::EStatus::FAIL:
            p_lun->state = EState::REQUEST_SENSE;
            break;
        case USBHCore::EStatus::UNRECOVERED_ERROR:
            p_lun->state = EState::UNRECOVERED_ERROR;
            error = USBHCore::EStatus::FAIL;
            break;
        default:
            break;
        }
#if (USBH_USE_OS == 1)
        m_host->send_message();
#endif
        break;
    case EState::WRITE:
        scsi_status = SCSI_write(lun, 0, nullptr, 0);
        switch (scsi_status)
        {
        case USBHCore::EStatus::OK:
            p_lun->state = EState::IDLE;
            error = USBHCore::EStatus::OK;
            break;
        case USBHCore::EStatus::FAIL:
            p_lun->state = EState::REQUEST_SENSE;
            break;
        case USBHCore::EStatus::UNRECOVERED_ERROR:
            p_lun->state = EState::UNRECOVERED_ERROR;
            error = USBHCore::EStatus::FAIL;
            break;
        default:
            break;
        }
#if (USBH_USE_OS == 1)
        m_host->send_message();
#endif
        break;
    case EState::REQUEST_SENSE:
        scsi_status = SCSI_request_sense(lun);
        switch (scsi_status)
        {
        case USBHCore::EStatus::OK:
            USBH_UsrLog("Sense Key  : %x", p_lun->sense.key);
            USBH_UsrLog("Additional Sense Code : %x", p_lun->sense.asc);
            USBH_UsrLog("Additional Sense Code Qualifier: %x", p_lun->sense.ascq);
            p_lun->state = EState::IDLE;
            p_lun->error = EError::ERROR;
            error = USBHCore::EStatus::FAIL;
            break;
        case USBHCore::EStatus::FAIL:
            USBH_UsrLog("MSC Device NOT ready");
            break;
        case USBHCore::EStatus::UNRECOVERED_ERROR:
            p_lun->state = EState::UNRECOVERED_ERROR;
            error = USBHCore::EStatus::FAIL;
            break;
        default:
            break;
        }
#if (USBH_USE_OS == 1)
        m_host->send_message();
#endif
        break;
    default:
        break;
    }
    return error;
}

USBHCore::EStatus USBH_MSC::BOT_process(uint8_t lun)
{
    USBHCore::EStatus status = USBHCore::EStatus::BUSY;
    switch (m_hbot.state)
    {
    case EBOTState::SEND_CBW:
        m_hbot.cbw.field.LUN = lun;
        m_hbot.state = EBOTState::SEND_CBW_WAIT;
        m_host->bulk_send_data(m_hbot.cbw.data, BOT_CBW_LENGTH, m_out_pipe, 1);
        break;
    case EBOTState::SEND_CBW_WAIT:
        switch (m_host->LL_get_URB_state(m_out_pipe))
        {
        case STM32_HCD::EURBState::DONE:
            if (m_hbot.cbw.field.DataTransferLength != 0)
            {
                if (static_cast<USBHCore::EReqDir>(m_hbot.cbw.field.Flags & static_cast<uint8_t>(USBHCore::EReqDir::DIR_MASK)) == USBHCore::EReqDir::D2H)
                    m_hbot.state = EBOTState::DATA_IN;
                else
                    m_hbot.state = EBOTState::DATA_OUT;
            }
            else
                m_hbot.state = EBOTState::RECEIVE_CSW;
#if (USBH_USE_OS == 1)
            m_host->send_message();
#endif
            break;
        case STM32_HCD::EURBState::NOT_READY:
            /* Re-send CBW */
            m_hbot.state = EBOTState::SEND_CBW;
#if (USBH_USE_OS == 1)
            m_host->send_message();
#endif
            break;
        case STM32_HCD::EURBState::STALL:
            m_hbot.state = EBOTState::ERROR_OUT;
#if (USBH_USE_OS == 1)
            m_host->send_message();
#endif
            break;
        case STM32_HCD::EURBState::IDLE:
        case STM32_HCD::EURBState::NYET:
        case STM32_HCD::EURBState::ERROR:
            break;
        }
        break;
    case EBOTState::DATA_IN:
        m_host->bulk_receive_data(m_hbot.pbuf, m_in_ep_size, m_in_pipe);
        m_hbot.state = EBOTState::DATA_IN_WAIT;
        break;
    case EBOTState::DATA_IN_WAIT:
        switch (m_host->LL_get_URB_state(m_in_pipe))
        {
        case STM32_HCD::EURBState::DONE:
            /* Adjust Data pointer and data length */
            if (m_hbot.cbw.field.DataTransferLength > m_in_ep_size)
            {
                m_hbot.pbuf += m_in_ep_size;
                m_hbot.cbw.field.DataTransferLength -= m_in_ep_size;
            }
            else
                m_hbot.cbw.field.DataTransferLength = 0;
            /* More Data To be Received */
            if (m_hbot.cbw.field.DataTransferLength > 0)
                m_host->bulk_receive_data(m_hbot.pbuf, m_in_ep_size, m_in_pipe);
            else
                m_hbot.state = EBOTState::RECEIVE_CSW;
            {
#if (USBH_USE_OS == 1)
            m_host->send_message();
#endif
            }
            break;
        case STM32_HCD::EURBState::STALL:
            m_hbot.state = EBOTState::ERROR_IN;
#if (USBH_USE_OS == 1)
            m_host->send_message();
#endif
            break;
        case STM32_HCD::EURBState::NOT_READY:
        case STM32_HCD::EURBState::IDLE:
        case STM32_HCD::EURBState::NYET:
        case STM32_HCD::EURBState::ERROR:
            break;
        }
        break;
    case EBOTState::DATA_OUT:
        m_host->bulk_send_data(m_hbot.pbuf, m_out_ep_size, m_out_pipe, 1);
        m_hbot.state = EBOTState::DATA_OUT_WAIT;
        break;
    case EBOTState::DATA_OUT_WAIT:
        switch (m_host->LL_get_URB_state(m_out_pipe))
        {
        case STM32_HCD::EURBState::DONE:
            /* Adjust Data pointer and data length */
            if (m_hbot.cbw.field.DataTransferLength > m_out_ep_size)
            {
                m_hbot.pbuf += m_out_ep_size;
                m_hbot.cbw.field.DataTransferLength -= m_out_ep_size;
            }
            else
                m_hbot.cbw.field.DataTransferLength = 0;
            /* More Data To be Received */
            if (m_hbot.cbw.field.DataTransferLength > 0)
                m_host->bulk_send_data(m_hbot.pbuf, m_out_ep_size, m_out_pipe, 1);
            else
                m_hbot.state = EBOTState::RECEIVE_CSW;
            {
#if (USBH_USE_OS == 1)
            m_host->send_message();
#endif
            }
            break;
        case STM32_HCD::EURBState::NOT_READY:
            /* Resend same data */
            m_hbot.state = EBOTState::DATA_OUT;
#if (USBH_USE_OS == 1)
            m_host->send_message();
#endif
            break;
        case STM32_HCD::EURBState::STALL:
            m_hbot.state = EBOTState::ERROR_OUT;
#if (USBH_USE_OS == 1)
            m_host->send_message();
#endif
            break;
        case STM32_HCD::EURBState::IDLE:
        case STM32_HCD::EURBState::NYET:
        case STM32_HCD::EURBState::ERROR:
            break;
        }
        break;
    case EBOTState::RECEIVE_CSW:
        m_host->bulk_receive_data(m_hbot.csw.data, BOT_CSW_LENGTH, m_in_pipe);
        m_hbot.state = EBOTState::RECEIVE_CSW_WAIT;
        break;
    case EBOTState::RECEIVE_CSW_WAIT:
        switch (m_host->LL_get_URB_state(m_in_pipe))
        {
        case STM32_HCD::EURBState::DONE:
            m_hbot.state = EBOTState::SEND_CBW;
            m_hbot.cmd_state = EBOTCMDState::SEND;
            if (decode_CSW())
                status = USBHCore::EStatus::OK;
            else
                status = USBHCore::EStatus::FAIL;
#if (USBH_USE_OS == 1)
            m_host->send_message();
#endif
            break;
        case STM32_HCD::EURBState::STALL:
            m_hbot.state = EBOTState::ERROR_IN;
#if (USBH_USE_OS == 1)
            m_host->send_message();
#endif
            break;
        case STM32_HCD::EURBState::NOT_READY:
        case STM32_HCD::EURBState::IDLE:
        case STM32_HCD::EURBState::NYET:
        case STM32_HCD::EURBState::ERROR:
            break;
        }
        break;
    case EBOTState::ERROR_IN:
        switch (BOT_abort(EBOTDir::IN))
        {
        case USBHCore::EStatus::OK:
            m_hbot.state = EBOTState::RECEIVE_CSW;
            break;
        case USBHCore::EStatus::UNRECOVERED_ERROR:
            m_hbot.state = EBOTState::UNRECOVERED_ERROR;
            break;
        case USBHCore::EStatus::BUSY:
        case USBHCore::EStatus::FAIL:
        case USBHCore::EStatus::NOT_SUPPORTED:
        case USBHCore::EStatus::ERROR_SPEED_UNKNOWN:
            break;
        }
        break;
    case EBOTState::ERROR_OUT:
        switch (BOT_abort(EBOTDir::OUT))
        {
        case USBHCore::EStatus::OK:
            m_host->LL_set_toggle(m_out_pipe, 1 - m_host->LL_get_toggle(m_out_pipe));
            m_host->LL_set_toggle(m_in_pipe, 0);
            m_hbot.state = EBOTState::ERROR_IN;
            break;
        case USBHCore::EStatus::UNRECOVERED_ERROR:
            m_hbot.state = EBOTState::UNRECOVERED_ERROR;
            break;
        case USBHCore::EStatus::BUSY:
        case USBHCore::EStatus::FAIL:
        case USBHCore::EStatus::NOT_SUPPORTED:
        case USBHCore::EStatus::ERROR_SPEED_UNKNOWN:
            break;
        }
        break;
    case EBOTState::UNRECOVERED_ERROR:
        status = BOT_req_reset();
        if (status == USBHCore::EStatus::OK)
            m_hbot.state = EBOTState::SEND_CBW;
        break;
    }
    return status;
}

USBHCore::EStatus USBH_MSC::SCSI_test_unit_ready(uint8_t lun)
{
    USBHCore::EStatus error = USBHCore::EStatus::FAIL;
    switch (m_hbot.cmd_state)
    {
    case EBOTCMDState::SEND:
        /*Prepare the CBW and relevent field*/
        m_hbot.cbw.field.DataTransferLength = DATA_LEN_MODE_TEST_UNIT_READY;
        m_hbot.cbw.field.Flags = USB_EP_DIR_OUT;
        m_hbot.cbw.field.CBLength = CBW_LENGTH;
        memset(m_hbot.cbw.field.CB, 0, CBW_CB_LENGTH);
        m_hbot.cbw.field.CB[0] = static_cast<uint8_t>(EOPCode::TEST_UNIT_READY);
        m_hbot.state = EBOTState::SEND_CBW;
        m_hbot.cmd_state = EBOTCMDState::WAIT;
        error = USBHCore::EStatus::BUSY;
        break;
    case EBOTCMDState::WAIT:
        error = BOT_process(lun);
        break;
    case EBOTCMDState::IDLE:
        break;
    }
    return error;
}

USBHCore::EStatus USBH_MSC::SCSI_read_capacity(uint8_t lun)
{
    USBHCore::EStatus error = USBHCore::EStatus::BUSY;
    switch (m_hbot.cmd_state)
    {
    case EBOTCMDState::SEND:
        /*Prepare the CBW and relevent field*/
        m_hbot.cbw.field.DataTransferLength = DATA_LEN_READ_CAPACITY10;
        m_hbot.cbw.field.Flags = USB_EP_DIR_IN;
        m_hbot.cbw.field.CBLength = CBW_LENGTH;
        memset(m_hbot.cbw.field.CB, 0, CBW_CB_LENGTH);
        m_hbot.cbw.field.CB[0] = static_cast<uint8_t>(EOPCode::READ_CAPACITY10);
        m_hbot.state = EBOTState::SEND_CBW;
        m_hbot.cmd_state = EBOTCMDState::WAIT;
        m_hbot.pbuf = reinterpret_cast<uint8_t*>(m_hbot.data);
        break;
    case EBOTCMDState::WAIT:
        error = BOT_process(lun);
        if (error == USBHCore::EStatus::OK)
        {
            SCSI_Capacity* cap = &m_unit[lun].capacity;
            /*assign the capacity*/
            cap->block_nbr = __builtin_bswap32(m_hbot.data[0]);
            /*assign the page length*/
            cap->block_size = static_cast<uint16_t>(m_hbot.pbuf[7] | (m_hbot.pbuf[6] << 8));
        }
        break;
    case EBOTCMDState::IDLE:
        break;
    }
    return error;
}

USBHCore::EStatus USBH_MSC::SCSI_inquiry(uint8_t lun)
{
    USBHCore::EStatus error = USBHCore::EStatus::FAIL;
    switch (m_hbot.cmd_state)
    {
    case EBOTCMDState::SEND:
        /*Prepare the CBW and relevent field*/
        m_hbot.cbw.field.DataTransferLength = DATA_LEN_INQUIRY;
        m_hbot.cbw.field.Flags = USB_EP_DIR_IN;
        m_hbot.cbw.field.CBLength = CBW_LENGTH;

        memset(m_hbot.cbw.field.CB, 0, CBW_CB_LENGTH);
        m_hbot.cbw.field.CB[0] = static_cast<uint8_t>(EOPCode::INQUIRY);
        m_hbot.cbw.field.CB[1] = static_cast<uint8_t>(lun << 5);
        m_hbot.cbw.field.CB[4] = 0x24;

        m_hbot.state = EBOTState::SEND_CBW;
        m_hbot.cmd_state = EBOTCMDState::WAIT;
        m_hbot.pbuf = reinterpret_cast<uint8_t*>(m_hbot.data);
        error = USBHCore::EStatus::BUSY;
        break;
    case EBOTCMDState::WAIT:
        error = BOT_process(lun);
        if (error == USBHCore::EStatus::OK)
        {
            SCSI_StdInquiryData* inq = &m_unit[lun].inquiry;
            memset(inq, 0, sizeof(SCSI_StdInquiryData));
            /*assign Inquiry Data */
            inq->DeviceType = m_hbot.pbuf[0] & 0x1f;
            inq->PeripheralQualifier = m_hbot.pbuf[0] >> 5;
            inq->RemovableMedia = ((m_hbot.pbuf[1] & 0x80) == 0x80);
            memcpy(inq->vendor_id, &m_hbot.pbuf[8], 8);
            memcpy(inq->product_id, &m_hbot.pbuf[16], 16);
            memcpy(inq->revision_id, &m_hbot.pbuf[32], 4);
        }
        break;
    case EBOTCMDState::IDLE:
        break;
    }
    return error;
}

USBHCore::EStatus USBH_MSC::SCSI_request_sense(uint8_t lun)
{
    USBHCore::EStatus error = USBHCore::EStatus::FAIL;
    switch (m_hbot.cmd_state)
    {
    case EBOTCMDState::SEND:
        /*Prepare the CBW and relevent field*/
        m_hbot.cbw.field.DataTransferLength = DATA_LEN_REQUEST_SENSE;
        m_hbot.cbw.field.Flags = USB_EP_DIR_IN;
        m_hbot.cbw.field.CBLength = CBW_LENGTH;

        memset(m_hbot.cbw.field.CB, 0, CBW_CB_LENGTH);
        m_hbot.cbw.field.CB[0] = static_cast<uint8_t>(EOPCode::REQUEST_SENSE);
        m_hbot.cbw.field.CB[1] = static_cast<uint8_t>(lun << 5);
        m_hbot.cbw.field.CB[4] = DATA_LEN_REQUEST_SENSE;

        m_hbot.state = EBOTState::SEND_CBW;
        m_hbot.cmd_state = EBOTCMDState::WAIT;
        m_hbot.pbuf = reinterpret_cast<uint8_t*>(m_hbot.data);
        error = USBHCore::EStatus::BUSY;
        break;
    case EBOTCMDState::WAIT:
        error = BOT_process(lun);
        if (error == USBHCore::EStatus::OK)
        {
            SCSI_Sense* sen = &m_unit[lun].sense;
            sen->key = m_hbot.pbuf[2] & 0x0f;
            sen->asc = m_hbot.pbuf[12];
            sen->ascq = m_hbot.pbuf[13];
        }
        break;
    case EBOTCMDState::IDLE:
        break;
    }
    return error;
}

USBHCore::EStatus USBH_MSC::SCSI_write(uint8_t lun, uint32_t address, uint8_t* buf, uint16_t length)
{
    USBHCore::EStatus error = USBHCore::EStatus::FAIL;
    switch (m_hbot.cmd_state)
    {
    case EBOTCMDState::SEND:
        /*Prepare the CBW and relevent field*/
        m_hbot.cbw.field.DataTransferLength = length * 512;
        m_hbot.cbw.field.Flags = USB_EP_DIR_OUT;
        m_hbot.cbw.field.CBLength = CBW_LENGTH;

        memset(m_hbot.cbw.field.CB, 0, CBW_CB_LENGTH);
        m_hbot.cbw.field.CB[0] = static_cast<uint8_t>(EOPCode::WRITE10);
        //m_hbot.cbw.field.CB[1] = static_cast<uint8_t>(lun << 5);
        /*logical block address*/
        m_hbot.cbw.field.CB[2] = reinterpret_cast<uint8_t*>(&address)[3];
        m_hbot.cbw.field.CB[3] = reinterpret_cast<uint8_t*>(&address)[2];
        m_hbot.cbw.field.CB[4] = reinterpret_cast<uint8_t*>(&address)[1];
        m_hbot.cbw.field.CB[5] = reinterpret_cast<uint8_t*>(&address)[0];
        /*Transfer length */
        m_hbot.cbw.field.CB[7] = reinterpret_cast<uint8_t*>(&length)[1];
        m_hbot.cbw.field.CB[8] = reinterpret_cast<uint8_t*>(&length)[0];

        m_hbot.state = EBOTState::SEND_CBW;
        m_hbot.cmd_state = EBOTCMDState::WAIT;
        m_hbot.pbuf = buf;
        error = USBHCore::EStatus::BUSY;
        break;
    case EBOTCMDState::WAIT:
        error = BOT_process(lun);
        break;
    case EBOTCMDState::IDLE:
        break;
    }
    return error;
}

USBHCore::EStatus USBH_MSC::SCSI_read(uint8_t lun, uint32_t address, uint8_t* buf, uint16_t length)
{
    USBHCore::EStatus error = USBHCore::EStatus::FAIL;
    switch (m_hbot.cmd_state)
    {
    case EBOTCMDState::SEND:
        /*Prepare the CBW and relevent field*/
        m_hbot.cbw.field.DataTransferLength = length * 512;
        m_hbot.cbw.field.Flags = USB_EP_DIR_IN;
        m_hbot.cbw.field.CBLength = CBW_LENGTH;

        memset(m_hbot.cbw.field.CB, 0, CBW_CB_LENGTH);
        m_hbot.cbw.field.CB[0] = static_cast<uint8_t>(EOPCode::READ10);
        //m_hbot.cbw.field.CB[1] = static_cast<uint8_t>(lun << 5);
        /*logical block address*/
        m_hbot.cbw.field.CB[2] = reinterpret_cast<uint8_t*>(&address)[3];
        m_hbot.cbw.field.CB[3] = reinterpret_cast<uint8_t*>(&address)[2];
        m_hbot.cbw.field.CB[4] = reinterpret_cast<uint8_t*>(&address)[1];
        m_hbot.cbw.field.CB[5] = reinterpret_cast<uint8_t*>(&address)[0];
        /*Transfer length */
        m_hbot.cbw.field.CB[7] = reinterpret_cast<uint8_t*>(&length)[1];
        m_hbot.cbw.field.CB[8] = reinterpret_cast<uint8_t*>(&length)[0];

        m_hbot.state = EBOTState::SEND_CBW;
        m_hbot.cmd_state = EBOTCMDState::WAIT;
        m_hbot.pbuf = buf;
        error = USBHCore::EStatus::BUSY;
        break;
    case EBOTCMDState::WAIT:
        error = BOT_process(lun);
        break;
    case EBOTCMDState::IDLE:
        break;
    }
    return error;
}

#endif // STM32_USE_USB_HOST
