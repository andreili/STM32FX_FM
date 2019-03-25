#ifndef USBH_MSC_H
#define USBH_MSC_H

#include "usbh_class.h"

#define USB_MSC_CLASS                                   0x08

#ifndef MAX_SUPPORTED_LUN
    #define MAX_SUPPORTED_LUN       2
#endif

#define BOT_CBW_SIGNATURE            0x43425355
#define BOT_CBW_TAG                  0x20304050
#define BOT_CSW_SIGNATURE            0x53425355
#define BOT_CBW_LENGTH               31
#define BOT_CSW_LENGTH               13

class USBH_MSC : public USBHClass
{
public:
    enum class EState: uint8_t
    {
        INIT= 0,
        IDLE,
        TEST_UNIT_READY,
        READ_CAPACITY10,
        READ_INQUIRY,
        REQUEST_SENSE,
        READ,
        WRITE,
        UNRECOVERED_ERROR,
        PERIODIC_CHECK,
    };

    enum class EError: uint8_t
    {
        OK,
        NOT_READY,
        ERROR,
    };

    enum class EReqState: uint8_t
    {
        REQ_IDLE = 0,
        REQ_RESET,
        REQ_GET_MAX_LUN,
        REQ_ERROR,
    };

    // Capacity data.
#pragma pack(push, 1)
    typedef struct
    {
        uint32_t block_nbr;
        uint16_t block_size;
    } SCSI_Capacity;
#pragma pack(pop)


    // Sense data.
    typedef struct
    {
        uint8_t key;
        uint8_t asc;
        uint8_t ascq;
    } SCSI_Sense;

    // INQUIRY data.
    typedef struct
    {
        uint8_t PeripheralQualifier;
        uint8_t DeviceType;
        uint8_t RemovableMedia;
        uint8_t vendor_id[9];
        uint8_t product_id[17];
        uint8_t revision_id[5];
    } SCSI_StdInquiryData;

    /* Structure for LUN */
    typedef struct
    {
        EState              state;
        EError              error;
        bool                state_changed;
        SCSI_Capacity       capacity;
        SCSI_Sense          sense;
        SCSI_StdInquiryData inquiry;
        uint8_t             dummy0;
        uint8_t             dummy1;
        USBHCore::EStatus   prev_ready_state;
    } MSC_LUN;

    enum class EBOTStatus: uint8_t
    {
        OK          = 0,
        FAIL        = 1,
        PHASE_ERROR = 2,
        BUSY        = 3,
    };

    enum class EBOTCMDState: uint8_t
    {
        IDLE  = 0,
        SEND,
        WAIT,
    };

    /* CSW Status Definitions */
    enum class EBOTCSWStatus: uint8_t
    {
        CMD_PASSED  = 0x00,
        CMD_FAILED  = 0x01,
        PHASE_ERROR = 0x02,
    };

    enum class EBOTState: uint8_t
    {
        SEND_CBW  = 1,
        SEND_CBW_WAIT,
        DATA_IN,
        DATA_IN_WAIT,
        DATA_OUT,
        DATA_OUT_WAIT,
        RECEIVE_CSW,
        RECEIVE_CSW_WAIT,
        ERROR_IN,
        ERROR_OUT,
        UNRECOVERED_ERROR,
    };

    enum ERequest: uint8_t
    {
        BOT_RESET       = 0xFF,
        GET_MAX_LUN     = 0xFE,
    };

    enum EBOTDir: uint8_t
    {
        IN      = 0,
        OUT     = 1,
        BOOTH   = 2,
    };

    typedef union
    {
        struct __CBW
        {
            uint32_t Signature;
            uint32_t Tag;
            uint32_t DataTransferLength;
            uint8_t  Flags;
            uint8_t  LUN;
            uint8_t  CBLength;
            uint8_t  CB[16];
        }field;
        uint8_t data[31];
    }
    BOT_CBW;

    typedef union
    {
        struct __CSW
        {
            uint32_t Signature;
            uint32_t Tag;
            uint32_t DataResidue;
            uint8_t  Status;
        }field;
        uint8_t data[13];
    }
    BOT_CSW;

    typedef struct
    {
        uint32_t        data[16];
        EBOTState       state;
        EBOTState       prev_state;
        EBOTCMDState    cmd_state;
        BOT_CBW         cbw;
        uint8_t         Reserved1;
        BOT_CSW         csw;
        uint8_t         Reserved2[3];
        uint8_t         *pbuf;
    }
    BOT_Handle;

    enum EOPCode: uint8_t
    {
        TEST_UNIT_READY     = 0x00,
        READ_CAPACITY10     = 0x25,
        READ10              = 0x28,
        WRITE10             = 0x2A,
        REQUEST_SENSE       = 0x03,
        INQUIRY             = 0x12,
    };

    virtual uint8_t get_class_code() { return USB_MSC_CLASS; }
    virtual const char* get_name() { return "MSC"; }
    virtual USBHCore::EStatus init(USBHCore* host);
    virtual USBHCore::EStatus deInit();
    virtual USBHCore::EStatus class_request();
    virtual USBHCore::EStatus process();
    virtual USBHCore::EStatus SOF_process();

protected:
    uint32_t        m_max_lun;
    uint8_t         m_in_pipe;
    uint8_t         m_out_pipe;
    uint8_t         m_out_ep;
    uint8_t         m_in_ep;
    uint8_t         m_current_lun;
    uint16_t        m_out_ep_size;
    uint16_t        m_in_ep_size;
    EState          m_state;
    EError          m_error;
    EReqState       m_req_state;
    EReqState       m_prev_req_state;
    BOT_Handle      m_hbot;
    MSC_LUN         m_unit[MAX_SUPPORTED_LUN];
    uint16_t        m_rw_lun;
    uint32_t        m_timer;

private:
    USBHCore::EStatus BOT_process(uint8_t lun);
    FORCE_INLINE USBHCore::EStatus BOT_req_reset()
    {
        return m_host->ctrl_req_custom(USBHCore::EReqDir::H2D, USBHCore::EReqRecipient::REQ_INTERFACE | USBHCore::EReqType::CLASS,
                                       ERequest::BOT_RESET, 0, 0, nullptr);
    }
    FORCE_INLINE USBHCore::EStatus BOT_get_max_LUN()
    {
        m_max_lun = 0;
        return m_host->ctrl_req_custom(USBHCore::EReqDir::D2H, USBHCore::EReqRecipient::REQ_INTERFACE | USBHCore::EReqType::CLASS,
                                       ERequest::GET_MAX_LUN, 0, 1, reinterpret_cast<uint8_t*>(&m_max_lun));
    }
    FORCE_INLINE USBHCore::EStatus BOT_abort(EBOTDir dir)
    {
        switch (dir)
        {
        case EBOTDir::IN:
            return m_host->clr_feature(m_in_ep);
        case EBOTDir::OUT:
            return m_host->clr_feature(m_out_ep);
        case EBOTDir::BOOTH:
            break;
        }
        return USBHCore::EStatus::FAIL;
    }
    FORCE_INLINE bool decode_CSW()
    {
        if ((m_host->LL_get_last_Xfer_size(m_in_pipe) == BOT_CSW_LENGTH) &&
            (m_hbot.csw.field.Signature == BOT_CSW_SIGNATURE) &&
            (m_hbot.csw.field.Tag == m_hbot.cbw.field.Tag))
        {
            switch (m_hbot.csw.field.Status)
            {
            case 0:
                return true;
            case 1:
            case 2:
                return false;
            }
        }
        return false;
    }

    USBHCore::EStatus SCSI_test_unit_ready(uint8_t lun);
    USBHCore::EStatus SCSI_read_capacity(uint8_t lun);
    USBHCore::EStatus SCSI_inquiry(uint8_t lun);
    USBHCore::EStatus SCSI_request_sense(uint8_t lun);
    USBHCore::EStatus SCSI_write(uint8_t lun, uint32_t address, uint8_t* buf, uint16_t length);
    USBHCore::EStatus SCSI_read(uint8_t lun, uint32_t address, uint8_t* buf, uint16_t length);
};

#endif //USBH_MSC_H
