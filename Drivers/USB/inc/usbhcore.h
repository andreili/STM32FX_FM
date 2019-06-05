#ifndef USBHCORE_H
#define USBHCORE_H

/*
 * Based on HAL-F4 v1.21.0
 * */

#include "stm32_inc.h"

#ifdef STM32_USE_USB_HOST

#include "usbh_config.h"

#define USB_DEVICE_DESC_SIZE                               18
#define USB_CONFIGURATION_DESC_SIZE                        9
#define USB_HID_DESC_SIZE                                  9
#define USB_INTERFACE_DESC_SIZE                            9
#define USB_ENDPOINT_DESC_SIZE                             7

/* Descriptor Type and Descriptor Index  */
/* Use the following values when calling the function USBH_GetDescriptor  */
#define  USB_DESC_DEVICE                    ((USBHCore::EDescType::DEVICE << 8) & 0xFF00)
#define  USB_DESC_CONFIGURATION             ((USBHCore::EDescType::CONFIGURATION << 8) & 0xFF00)
#define  USB_DESC_STRING                    ((USBHCore::EDescType::STRING << 8) & 0xFF00)
#define  USB_DESC_INTERFACE                 ((USBHCore::EDescType::INTERFACE << 8) & 0xFF00)
#define  USB_DESC_ENDPOINT                  ((USBHCore::EDescType::INTERFACE << 8) & 0xFF00)
#define  USB_DESC_DEVICE_QUALIFIER          ((USBHCore::EDescType::DEVICE_QUALIFIER << 8) & 0xFF00)
#define  USB_DESC_OTHER_SPEED_CONFIGURATION ((USBHCore::EDescType::OTHER_SPEED_CONFIGURATION << 8) & 0xFF00)
#define  USB_DESC_INTERFACE_POWER           ((USBHCore::EDescType::INTERFACE_POWER << 8) & 0xFF00)
#define  USB_DESC_HID_REPORT                ((USBHCore::EDescType::HID_REPORT << 8) & 0xFF00)
#define  USB_DESC_HID                       ((USBHCore::EDescType::HID << 8) & 0xFF00)

#define  USB_EP_DIR_OUT                                 0x00
#define  USB_EP_DIR_IN                                  0x80
#define  USB_EP_DIR_MSK                                 0x80

#ifndef USBH_MAX_PIPES_NBR
 #define USBH_MAX_PIPES_NBR                             15
#endif /* USBH_MAX_PIPES_NBR */

#define USBH_DEVICE_ADDRESS_DEFAULT                     0
#define USBH_MAX_ERROR_COUNT                            2
#define USBH_DEVICE_ADDRESS                             1

#define USBH_CONFIGURATION_DESCRIPTOR_SIZE (USB_CONFIGURATION_DESC_SIZE \
                                           + USB_INTERFACE_DESC_SIZE\
                                           + (USBH_MAX_NUM_ENDPOINTS * USB_ENDPOINT_DESC_SIZE))


#define CONFIG_DESC_wTOTAL_LENGTH (ConfigurationDescriptorData.ConfigDescfield.\
                                          ConfigurationDescriptor.wTotalLength)


#define USBH_PID_SETUP                            false
#define USBH_PID_DATA                             true

#define USBH_SETUP_PKT_SIZE                       8

#define FEATURE_SELECTOR_ENDPOINT         0X00
#define FEATURE_SELECTOR_DEVICE           0X01


#define INTERFACE_DESC_TYPE               0x04
#define ENDPOINT_DESC_TYPE                0x05
#define INTERFACE_DESC_SIZE               0x09

class USBHClass;

class USBHCore
{
public:

    enum class ELen: uint8_t
    {
        DESC_HDR    = 0x02,
        DEV_DESC    = 0x12,
        CFG_DESC    = 0x09,
        IF_DESC     = 0x09,
        EP_DESC     = 0x07,
        OTG_DESC    = 0x03,
        SETUP_PKT   = 0x08,
    };

    enum EReqType: uint8_t
    {
        STANDARD    = 0x00,
        CLASS       = 0x20,
        VENDOR      = 0x40,
        RESERVED    = 0x60,
    };

    enum EReqRecipient: uint8_t
    {
        REQ_DEVICE      = 0x00,
        REQ_INTERFACE   = 0x01,
        REQ_ENDPOINT    = 0x02,
        REQ_OTHER       = 0x03,
    };

    enum ERequest: uint8_t
    {
        GET_STATUS          = 0x00,
        CLEAR_FEATURE       = 0x01,
        SET_FEATURE         = 0x03,
        SET_ADDRESS         = 0x05,
        GET_DESCRIPTOR      = 0x06,
        SET_DESCRIPTOR      = 0x07,
        GET_CONFIGURATION   = 0x08,
        SET_CONFIGURATION   = 0x09,
        GET_INTERFACE       = 0x0A,
        SET_INTERFACE       = 0x0B,
        SYNCH_FRAME         = 0x0C,
    };

    enum EDescType: uint16_t
    {
        DEVICE                              = 1,
        CONFIGURATION                       = 2,
        STRING                              = 3,
        INTERFACE                           = 4,
        ENDPOINT                            = 5,
        DEVICE_QUALIFIER                    = 6,
        OTHER_SPEED_CONFIGURATION           = 7,
        INTERFACE_POWER                     = 8,
        HID                                 = 0x21,
        HID_REPORT                          = 0x22,
    };

    enum class EEPType: uint8_t
    {
        CTRL    = 0x00,
        ISOC    = 0x01,
        BULK    = 0x02,
        INTR    = 0x03,
    };

    enum class EHostUser: uint8_t
    {
        SELECT_CONFIGURATION = 1,
        CLASS_ACTIVE,
        CLASS_SELECTED,
        CONNECTION,
        DISCONNECTION,
        UNRECOVERED_ERROR,
    };

    enum class EHostState: uint8_t
    {
        IDLE = 0,
        DEV_WAIT_FOR_ATTACHMENT,
        DEV_ATTACHED,
        DEV_DISCONNECTED,
        DETECT_DEVICE_SPEED,
        ENUMERATION,
        CLASS_REQUEST,
        INPUT,
        SET_CONFIGURATION,
        CHECK_CLASS,
        CLASS,
        SUSPEND,
        ABORT_STATE,
    };

    enum class EUSBState: uint8_t
    {
        IDLE = 0,
        GET_FULL_DEV_DESC,
        SET_ADDR,
        GET_CFG_DESC,
        GET_FULL_CFG_DESC,
        GET_MFC_STRING_DESC,
        GET_PRODUCT_STRING_DESC,
        GET_SERIALNUM_STRING_DESC,
    };

    enum class ECMDState: uint8_t
    {
        IDLE = 0,
        SEND,
        WAIT,
    };

    enum class EStatus: uint32_t
    {
        OK = 0,
        BUSY,
        FAIL,
        NOT_SUPPORTED,
        UNRECOVERED_ERROR,
        ERROR_SPEED_UNKNOWN,
    };

    enum class ECTRLState: uint8_t
    {
        IDLE =0,
        SETUP,
        SETUP_WAIT,
        DATA_IN,
        DATA_IN_WAIT,
        DATA_OUT,
        DATA_OUT_WAIT,
        STATUS_IN,
        STATUS_IN_WAIT,
        STATUS_OUT,
        STATUS_OUT_WAIT,
        ERROR,
        STALLED,
        COMPLETE,
    };

    enum class EOsEvent: uint32_t
    {
        PORT_EVENT = 1,
        URB_EVENT,
        CONTROL_EVENT,
        CLASS_EVENT,
        STATE_CHANGED_EVENT,
    };

    enum class EReqDir: uint8_t
    {
        DIR_MASK    = 0x80,
        H2D         = 0x00,
        D2H         = 0x80,
    };

    typedef union
    {
      uint16_t w;
      struct BW
      {
        uint8_t msb;
        uint8_t lsb;
      } bw;
    }
    uint16_t_uint8_t;

    typedef union _USB_Setup
    {
      uint32_t d8[2];

      struct _SetupPkt_Struc
      {
        uint8_t           bmRequestType;
        uint8_t           bRequest;
        uint16_t_uint8_t  wValue;
        uint16_t_uint8_t  wIndex;
        uint16_t_uint8_t  wLength;
      } b;
    } USB_Setup_t;

    typedef struct
    {
        uint8_t     pipe_in;
        uint8_t     pipe_out;
        uint8_t     pipe_size;
        uint8_t     errorcount;
        ECTRLState  state;
        uint16_t    length;
        uint16_t    timer;
        USB_Setup_t setup;
        uint8_t     *buff;
    } USBHCtrl_t;

    #pragma pack(push, 1)
    typedef struct
    {
        uint8_t  bLength;
        uint8_t  bDescriptorType;
    }
    USBHDescHeader_t;

    typedef struct
    {
        uint8_t   bLength;
        uint8_t   bDescriptorType;
        uint16_t  bcdUSB;        /* USB Specification Number which device complies too */
        uint8_t   bDeviceClass;
        uint8_t   bDeviceSubClass;
        uint8_t   bDeviceProtocol;
        /* If equal to Zero, each interface specifies its own class
        code if equal to 0xFF, the class code is vendor specified.
        Otherwise field is valid Class Code.*/
        uint8_t   bMaxPacketSize;
        uint16_t  idVendor;      /* Vendor ID (Assigned by USB Org) */
        uint16_t  idProduct;     /* Product ID (Assigned by Manufacturer) */
        uint16_t  bcdDevice;     /* Device Release Number */
        uint8_t   iManufacturer;  /* Index of Manufacturer String Descriptor */
        uint8_t   iProduct;       /* Index of Product String Descriptor */
        uint8_t   iSerialNumber;  /* Index of Serial Number String Descriptor */
        uint8_t   bNumConfigurations; /* Number of Possible Configurations */
    } USBHDevDesc_t;

    typedef struct
    {
        uint8_t   bLength;
        uint8_t   bDescriptorType;
        uint8_t   bEndpointAddress;   /* indicates what endpoint this descriptor is describing */
        uint8_t   bmAttributes;       /* specifies the transfer type. */
        uint16_t  wMaxPacketSize;    /* Maximum Packet Size this endpoint is capable of sending or receiving */
        uint8_t   bInterval;          /* is used to specify the polling interval of certain transfers. */
    } USBHEpDesc_t;

    typedef struct
    {
        uint8_t bLength;
        uint8_t bDescriptorType;
        uint8_t bInterfaceNumber;
        uint8_t bAlternateSetting;    /* Value used to select alternative setting */
        uint8_t bNumEndpoints;        /* Number of Endpoints used for this interface */
        uint8_t bInterfaceClass;      /* Class Code (Assigned by USB Org) */
        uint8_t bInterfaceSubClass;   /* Subclass Code (Assigned by USB Org) */
        uint8_t bInterfaceProtocol;   /* Protocol Code */
        uint8_t iInterface;           /* Index of String Descriptor Describing this interface */
        USBHEpDesc_t   Ep_Desc[USBH_MAX_NUM_ENDPOINTS];
    } USBHInterfaceDesc_t;


    typedef struct
    {
        uint8_t   bLength;
        uint8_t   bDescriptorType;
        uint16_t  wTotalLength;        /* Total Length of Data Returned */
        uint8_t   bNumInterfaces;       /* Number of Interfaces */
        uint8_t   bConfigurationValue;  /* Value to use as an argument to select this configuration*/
        uint8_t   iConfiguration;       /*Index of String Descriptor Describing this configuration */
        uint8_t   bmAttributes;         /* D7 Bus Powered , D6 Self Powered, D5 Remote Wakeup , D4..0 Reserved (0)*/
        uint8_t   bMaxPower;            /*Maximum Power Consumption */
        USBHInterfaceDesc_t  Itf_Desc[USBH_MAX_NUM_INTERFACES];
    } USBHCfgDesc_t;
    #pragma pack(pop)

    typedef struct
    {
    #if (USBH_KEEP_CFG_DESCRIPTOR == 1)
        uint8_t         CfgDesc_Raw[USBH_MAX_SIZE_CONFIGURATION];
    #endif
        uint8_t         Data[USBH_MAX_DATA_BUFFER] __attribute__((aligned(4)));
        uint8_t         address;
        STM32_HCD::EOTGSpeed speed;
        __IO uint8_t    is_connected;
        uint8_t         current_interface;
        USBHDevDesc_t   DevDesc;
        USBHCfgDesc_t   CfgDesc;
    } USBHDevice_t;

    void init(void (*puser)(USBHCore*,EHostUser), uint8_t id);
    void deInit();

    EHostState get_state() { return m_gstate; }

    uint32_t register_class(USBHClass *pclass);

    uint32_t select_interface(uint8_t interface);
    uint8_t find_interface(uint8_t Class, uint8_t subclass, uint8_t protocol);
    uint8_t find_interface_index(uint8_t interface_number, uint8_t alt_settings);

    //FORCE_INLINE uint8_t get_active_class() { return m_device.CfgDesc.Itf_Desc[m_device.current_interface].bInterfaceClass; }
    FORCE_INLINE USBHClass* get_active_class() { return m_active_class; }
    FORCE_INLINE USBHInterfaceDesc_t* get_current_interface() { return &m_device.CfgDesc.Itf_Desc[m_device.current_interface]; }

    /* Pipes */
    FORCE_INLINE uint32_t open_pipe(uint8_t ch_num, uint8_t epnum, uint8_t dev_addr, STM32_HCD::EOTGSpeed speed, STM32_HCD::EEPType ep_type, uint16_t mps)
        { return m_hcd->HC_init(ch_num, epnum, dev_addr, speed, ep_type, mps); }
    FORCE_INLINE uint32_t close_pipe(uint8_t pipe_num) { return m_hcd->HC_halt(pipe_num); }
    uint8_t alloc_pipe(uint8_t ep_addr);
    uint16_t get_free_pipe();
    FORCE_INLINE void free_pipe(uint8_t idx) { if (idx < 11) { m_pipes[idx] &= 0x7fff; } }

    FORCE_INLINE void interrupt_recieve_data(uint8_t* buff, uint16_t length, uint8_t ch_num)
        { m_hcd->HC_submit_request(ch_num, true, STM32_HCD::EEPType::INTR, USBH_PID_DATA, buff, length, false); }
    FORCE_INLINE void bulk_receive_data(uint8_t* buff, uint16_t length, uint8_t ch_num)
        { m_hcd->HC_submit_request(ch_num, true, STM32_HCD::EEPType::BULK, USBH_PID_DATA, buff, length, false); }
    FORCE_INLINE void bulk_send_data(uint8_t* buff, uint16_t length, uint8_t ch_num, uint8_t do_ping)
        { m_hcd->HC_submit_request(ch_num, false, STM32_HCD::EEPType::BULK, USBH_PID_DATA, buff, length, (m_device.speed != STM32_HCD::EOTGSpeed::HIGH ? 0 : do_ping)); }

    // device
    FORCE_INLINE uint8_t get_dev_addr() { return m_device.address; }
    FORCE_INLINE STM32_HCD::EOTGSpeed get_dev_speed() { return m_device.speed; }
    FORCE_INLINE uint8_t* get_dev_data() { return m_device.Data; }
    FORCE_INLINE bool is_connected() { return m_device.is_connected; }

    FORCE_INLINE void LL_set_toggle(uint8_t pipe, uint8_t toggle) { m_hcd->set_toggle(pipe, toggle); }
    FORCE_INLINE uint8_t LL_get_toggle(uint8_t pipe) { return m_hcd->get_toggle(pipe); }

    FORCE_INLINE uint32_t LL_get_last_Xfer_size(uint8_t pipe) { return m_hcd->HC_get_Xfer_count(pipe); }

    FORCE_INLINE void to_user(EHostUser reason) { m_user(this, reason); }

    void start();
    void stop();
    void re_enumerate();
    void process();

    void LL_connect();
    void LL_disconnect();

    FORCE_INLINE void LL_inc_timer() { ++m_timer; handle_SOF(); }
    FORCE_INLINE uint32_t get_timer() { return m_timer; }

    FORCE_INLINE STM32_HCD::EURBState LL_get_URB_state(uint8_t pipe) { return m_hcd->HC_get_URB_state(pipe); }

    EStatus clr_feature(uint8_t ep_num);
    EStatus get_descriptor(uint8_t req_type, uint16_t value_idx, uint8_t* buff, uint16_t length);
    FORCE_INLINE EStatus ctrl_req_custom(EReqDir dir, uint8_t req_type, uint8_t req, uint16_t value_idx, uint16_t length, uint8_t* buff)
    {
        m_control.setup.b.bmRequestType = static_cast<uint8_t>(dir) | req_type;
        m_control.setup.b.bRequest = req;
        m_control.setup.b.wValue.w = value_idx;

        m_control.setup.b.wIndex.w = 0;
        m_control.setup.b.wLength.w = length;
        return ctl_req(buff, length);
    }
#if (USBH_USE_OS == 1)
    FORCE_INLINE void LL_notify_URB_change() { send_message(); }
    FORCE_INLINE bool wait_message() { return m_events.wait(100); }
    FORCE_INLINE void send_message() { m_events.signal_isr(); }
    FORCE_INLINE uint32_t get_message_depth() { return m_events.get_size(); }
#endif
private:
    uint8_t             m_id;
    EHostState          m_gstate;
    EUSBState           m_enum_state;
    ECMDState           m_request_state;
    USBHCtrl_t          m_control;
    USBHDevice_t        m_device;
    USBHClass*          m_class[USBH_MAX_NUM_SUPPORTED_CLASS];
    USBHClass*          m_active_class;
    uint32_t            m_class_number;
    uint32_t            m_pipes[15];
    __IO uint32_t       m_timer;
    STM32_HCD*          m_hcd;
    void                (*m_user)(USBHCore*,EHostUser);
#if (USBH_USE_OS == 1)
    OS::TEventsQueue    m_events;
#endif

    uint32_t handle_enum();
    void handle_SOF();
    void deInit_state_machine();

    // LL Driver
    void LL_init();
    FORCE_INLINE void LL_deInit() { m_hcd->deInit(); }
    FORCE_INLINE uint32_t LL_start() { return m_hcd->start(); }
    FORCE_INLINE uint32_t LL_stop() { return m_hcd->stop(); }

    FORCE_INLINE STM32_HCD::EOTGSpeed LL_get_speed() { return m_hcd->get_current_speed(); }
    FORCE_INLINE void LL_reset_port() { m_hcd->reset_port(); }
    void LL_driver_VBUS(uint8_t state);

    FORCE_INLINE uint32_t LL_open_pipe(uint8_t pipe_num, uint8_t ep_num, uint8_t dev_address, STM32_HCD::EOTGSpeed speed, STM32_HCD::EEPType ep_type, uint16_t mps)
        { return m_hcd->HC_init(pipe_num, ep_num, dev_address, speed, ep_type, mps); }
    FORCE_INLINE uint32_t LL_close_pipe(uint8_t pipe) { return m_hcd->HC_halt(pipe); }
    FORCE_INLINE void LL_submit_URB(uint8_t pipe, bool is_in, STM32_HCD::EEPType ep_type, bool token, uint8_t* pbuff, uint16_t length, uint8_t do_ping)
        { m_hcd->HC_submit_request(pipe, is_in, ep_type, token, pbuff, length, do_ping); }

    /* USBH Time base */
    FORCE_INLINE void LL_set_timer(uint32_t time) { m_timer = time; }

    /* IOreq */
    FORCE_INLINE void ctrl_send_setup(uint8_t* buff, uint8_t ch_num)
        { m_hcd->HC_submit_request(ch_num, false, STM32_HCD::EEPType::CTRL, USBH_PID_SETUP, buff, USBH_SETUP_PKT_SIZE, false); }
    FORCE_INLINE void ctrl_send_data(uint8_t* buff, uint16_t length, uint8_t ch_num, bool do_ping)
        { m_hcd->HC_submit_request(ch_num, false, STM32_HCD::EEPType::CTRL, USBH_PID_DATA, buff, length, (m_device.speed == STM32_HCD::EOTGSpeed::HIGH) ? do_ping : false); }
    FORCE_INLINE void ctrl_recieve_data(uint8_t* buff, uint16_t length, uint8_t ch_num)
        { m_hcd->HC_submit_request(ch_num, true, STM32_HCD::EEPType::CTRL, USBH_PID_DATA, buff, length, false); }
    FORCE_INLINE void interrupt_send_data(uint8_t* buff, uint16_t length, uint8_t ch_num)
        { m_hcd->HC_submit_request(ch_num, false, STM32_HCD::EEPType::INTR, USBH_PID_DATA, buff, length, false); }
    FORCE_INLINE void isoc_recieve_data(uint8_t* buff, uint16_t length, uint8_t ch_num)
        { m_hcd->HC_submit_request(ch_num, true, STM32_HCD::EEPType::ISOC, USBH_PID_DATA, buff, length, false); }
    FORCE_INLINE void isoc_send_data(uint8_t* buff, uint16_t length, uint8_t ch_num)
        { m_hcd->HC_submit_request(ch_num, false, STM32_HCD::EEPType::ISOC, USBH_PID_DATA, buff, length, false); }

    /* CtrlReq */
    EStatus ctl_req(uint8_t* buff, uint16_t length);
    EStatus get_dev_desc(uint16_t length);
    EStatus get_string_desc(uint8_t string_index, uint8_t* buff, uint16_t length);
    EStatus set_cfg(uint16_t config_val);
    EStatus get_cfg_desc(uint16_t length);
    EStatus set_address(uint8_t dev_address);
    EStatus set_interface(uint8_t ep_num, uint8_t alt_setting);
    USBHDescHeader_t* get_next_desc(uint8_t* buff, uint16_t* ptr);

    void parse_dev_desc(USBHDevDesc_t* pdesc, uint8_t *buf, uint16_t length);
    void parse_string_desc(uint8_t *psrc, uint8_t *pdst, uint16_t length);
    void parse_cfg_desc(USBHCfgDesc_t* pdesc, uint8_t *buf, uint16_t length);
    void parse_ep_desc(USBHEpDesc_t *ep_desc, uint8_t *buf);
    void parse_interface_desc(USBHInterfaceDesc_t *if_desc, uint8_t *buf);

    EStatus handle_control();
};

#ifdef STM32_USE_USB_HS
extern USBHCore usb_HS;
#endif

#ifdef STM32_USE_USB_FS
extern USBHCore usb_FS;
#endif

extern uint8_t USBH_CfgDesc[512];

#endif //STM32_USE_USB_HOST

#endif
