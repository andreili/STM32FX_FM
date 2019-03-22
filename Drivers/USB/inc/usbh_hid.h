#ifndef __USBH_HID_H__
#define __USBH_HID_H__

#include "usbh_class.h"
#include "fifo.h"

/* HID Class Codes */
#define USB_HID_CLASS                               0x03

/* Interface Descriptor field values for HID Boot Protocol */
#define HID_BOOT_CODE                               0x01
#define HID_KEYBRD_BOOT_CODE                        0x01
#define HID_MOUSE_BOOT_CODE                         0x02

#define HID_MIN_POLL                                10
#define HID_MAX_USAGE                               10
#define HID_MAX_NBR_REPORT_FMT                      10
#define HID_QUEUE_SIZE                              10

#define CUSTOM_DATA_SIZE                            20
#define REPORT_DATA_SIZE                            8

class USBH_HID : public USBHClass
{
public:
    enum class EState: uint8_t
    {
        INIT= 0,
        IDLE,
        SEND_DATA,
        BUSY,
        GET_DATA,
        SYNC,
        POLL,
        ERROR,
    };

    enum class ECtlState: uint8_t
    {
        REQ_INIT = 0,
        REQ_IDLE,
        REQ_GET_REPORT_DESC,
        REQ_GET_HID_DESC,
        REQ_SET_IDLE,
        REQ_SET_PROTOCOL,
        REQ_SET_REPORT,
    };

    enum class EType: uint8_t
    {
        MOUSE    = 0x01,
        KEYBOARD = 0x02,
        UNKNOWN  = 0xFF,
    };

    enum ERequest: uint8_t
    {
        GET_REPORT      = 0x01,
        GET_IDLE        = 0x02,
        GET_PROTOCOL    = 0x03,
        SET_REPORT      = 0x09,
        SET_IDLE        = 0x0A,
        SET_PROTOCOL    = 0x0B,
    };

    typedef struct
    {
        uint8_t   ReportID;
        uint8_t   ReportType;
        uint16_t  UsagePage;
        uint32_t  Usage[HID_MAX_USAGE];
        uint32_t  NbrUsage;
        uint32_t  UsageMin;
        uint32_t  UsageMax;
        int32_t   LogMin;
        int32_t   LogMax;
        int32_t   PhyMin;
        int32_t   PhyMax;
        int32_t   UnitExp;
        uint32_t  Unit;
        uint32_t  ReportSize;
        uint32_t  ReportCnt;
        uint32_t  Flag;
        uint32_t  PhyUsage;
        uint32_t  AppUsage;
        uint32_t  LogUsage;
    } ReportDataTypeDef;

    typedef struct
    {
        uint8_t  Size;         /* Report size return by the device id            */
        uint8_t  ReportID;     /* Report Id                                      */
        uint8_t  Type;         /* Report Type (INPUT/OUTPUT/FEATURE)             */
    } ReportIDTypeDef;

    typedef struct _CollectionTypeDef
    {
        uint32_t                    Usage;
        uint8_t                     Type;
        struct _CollectionTypeDef   *NextPtr;
    } CollectionTypeDef;

    typedef struct
    {
        uint32_t            Usage;
        uint8_t             Type;
        uint8_t             NbrReportFmt;
        ReportDataTypeDef   ReportData[HID_MAX_NBR_REPORT_FMT];
    } AppCollectionTypeDef;

    #pragma pack(push, 1)
    typedef struct
    {
        uint8_t   bLength;
        uint8_t   bDescriptorType;
        uint16_t  bcdHID;               /* indicates what endpoint this descriptor is describing */
        uint8_t   bCountryCode;        /* specifies the transfer type. */
        uint8_t   bNumDescriptors;     /* specifies the transfer type. */
        uint8_t   bReportDescriptorType;    /* Maximum Packet Size this endpoint is capable of sending or receiving */
        uint16_t  wItemLength;          /* is used to specify the polling interval of certain transfers. */
    } DescTypeDef;
    #pragma pack(pop)

    typedef struct
    {
        union
        {
            uint8_t alts_all;
            struct
            {
                uint8_t lctrl: 1;
                uint8_t lshift: 1;
                uint8_t lalt: 1;
                uint8_t lgui: 1;
                uint8_t rctrl: 1;
                uint8_t rshift: 1;
                uint8_t ralt: 1;
                uint8_t rgui: 1;
            } alts;
        } a;
        uint8_t keys[7];
    } KbdReport;


    virtual uint8_t get_class_code() { return USB_HID_CLASS; }
    virtual const char* get_name() { return "HID"; }
    virtual USBHCore::EStatus init(USBHCore* host);
    virtual USBHCore::EStatus deInit();
    virtual USBHCore::EStatus class_request();
    virtual USBHCore::EStatus process();
    virtual USBHCore::EStatus SOF_process();

    FORCE_INLINE EType get_type() { return m_type; }
    uint16_t get_pool_interval();
    USBHCore::EStatus decode(uint8_t *data);

protected:
    uint8_t         m_out_pipe;
    uint8_t         m_in_pipe;
    uint8_t         m_out_ep;
    uint8_t         m_in_ep;
    EState          m_state;
    ECtlState       m_ctl_state;
    uint8_t         m_ep_addr;
    bool            m_data_ready;
    EType           m_type;
    uint16_t        m_length;
    uint16_t        m_poll;
    uint32_t        m_timer;
    FIFO            m_fifo;
    DescTypeDef     m_HID_Desc;

    uint8_t         m_custom_data[CUSTOM_DATA_SIZE];

private:
    FORCE_INLINE USBHCore::EStatus get_HID_descriptor(uint16_t size)
    {
        return m_host->get_descriptor(USBHCore::EReqRecipient::REQ_INTERFACE | USBHCore::EReqType::STANDARD,
                                      USB_DESC_HID, m_host->get_dev_data(), size);
    }
    void parse_HID_desc();
    USBHCore::EStatus get_HID_report_descriptor(uint16_t size);
    FORCE_INLINE USBHCore::EStatus set_idle(uint8_t duration, uint8_t reportId)
    {
        return m_host->ctrl_req_custom(USB_H2D, USBHCore::EReqRecipient::REQ_INTERFACE | USBHCore::EReqType::CLASS,
                                       ERequest::SET_IDLE, static_cast<uint16_t>((duration << 8) | reportId), 0, nullptr);
    }
    FORCE_INLINE USBHCore::EStatus set_protocol(uint8_t protocol)
    {
        return m_host->ctrl_req_custom(USB_H2D, USBHCore::EReqRecipient::REQ_INTERFACE | USBHCore::EReqType::CLASS,
                                       ERequest::SET_PROTOCOL, (protocol != 0) ? 0 : 1, 0, nullptr);
    }
    FORCE_INLINE USBHCore::EStatus set_report(uint8_t type, uint8_t id, uint8_t *buf, uint16_t len)
    {
        return m_host->ctrl_req_custom(USB_H2D, USBHCore::EReqRecipient::REQ_INTERFACE | USBHCore::EReqType::CLASS,
                                       ERequest::SET_REPORT, static_cast<uint16_t>((type << 8) | id), len, buf);
    }
    FORCE_INLINE USBHCore::EStatus get_report(uint8_t type, uint8_t id, uint8_t *buf, uint16_t len)
    {
        return m_host->ctrl_req_custom(USB_D2H, USBHCore::EReqRecipient::REQ_INTERFACE | USBHCore::EReqType::CLASS,
                                       ERequest::GET_REPORT, static_cast<uint16_t>((type << 8) | id), len, buf);
    }
};

#endif
