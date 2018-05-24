#ifndef __USBHCORE_H__
#define __USBHCORE_H__

#include "stm32_inc.h"
#include <functional>

enum class EHostUser
{
    SELECT_CONFIGURATION = 1,
    CLASS_ACTIVE,
    CLASS_SELECTED,
    CONNECTION,
    DISCONNECTION,
    UNRECOVERED_ERROR,
};

enum class EHostState
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

enum class EUSBState
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

enum class ECMDState
{
    IDLE = 0,
    SEND,
    WAIT,
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
}
USB_Setup_TypeDef;

enum class ECTRLState
{
    IDEL = 0,
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
    COMPLETE ,
};

typedef struct
{
    uint8_t               pipe_in;
    uint8_t               pipe_out;
    uint8_t               pipe_size;
    uint8_t               *buff;
    uint16_t              length;
    uint16_t              timer;
    USB_Setup_TypeDef     setup;
    ECTRLState            state;
    uint8_t               errorcount;
} USBHCtrl;

typedef struct
{
#if (USBH_KEEP_CFG_DESCRIPTOR == 1)
    uint8_t                           CfgDesc_Raw[USBH_MAX_SIZE_CONFIGURATION];
#endif
    uint8_t                           Data[USBH_MAX_DATA_BUFFER];
    uint8_t                           address;
    uint8_t                           speed;
    __IO uint8_t                      is_connected;
    uint8_t                           current_interface;
    USBH_DevDescTypeDef               DevDesc;
    USBH_CfgDescTypeDef               CfgDesc;
} USBHDevice;

class USBHCore
{
public:
    uint32_t init(std::function(USBHCore*,uint8_t), uint8_t id);
    uint32_t deInit();

    uint32_t register_class(USBHClass *pclass);

    uint32_t select_interface(uint8_t interface);
    uint8_t find_interface(uint8_t Class, uint8_t subclass, uint8_t protocol);
    uint8_t find_interface_index(uint8_t interface_number, uint8_t alt_settings);

    uint8_t get_active_class();

    uint32_t start();
    uint32_t stop();
    uint32_t process();
    uint32_t re_enumerate();
private:
    __IO EHostState     m_gstate;
    EUSBState           m_state;
    ECMDState           m_request_state;
    USBHCtrl            m_control;
    USBHDevice          m_device;
    USBHClass*          m_class[USBH_MAX_NUM_SUPPORTED_CLASS];
    USBClass*           m_active_class;
    uint32_t            m_class_number;
    uint32_t            m_pipes[15];
    __IO uint32_t       m_timer;
    uint8_t             m_id;
    void*               m_data;
    std::function<USBHCore*,uint8_t>   m_user;
#if (USBH_USE_OS == 1)
    osMessageQId        m_event;
    osThreadId          m_thread;
#endif

    // LL Driver
    uint32_t LL_init();
    uint32_t LL_deInit();
    uint32_t LL_start();
    uint32_t LL_stop();

    uint32_t LL_connect();
    uint32_t LL_disconnect();
    uint32_t LL_get_speed();
    uint32_t LL_reset_port();
    uint32_t LL_get_last_Xfer_size(uint8_t);
    uint32_t LL_driver_VBUS(uint8_t);

    uint32_t LL_open_pipe(uint8_t, uint8_t, uint8_t, uint8_t , uint8_t, uint16_t);
    uint32_t LL_close_pipe(uint8_t);
    uint32_t LL_submit_URB(uint8_t, uint8_t,uint8_t,  uint8_t, uint8_t*, uint16_t, uint8_t);
    uint32_t LL_get_URB_state(uint8_t);

#if (USBH_USE_OS == 1)
    uint32_t LL_notify_URB_change();
#endif
    uint32_t LL_set_toggle(uint8_t, uint8_t);
    uint8_t LL_get_toggle(uint8_t);

    /* USBH Time base */
    void delay(uint32_t time);
    void LL_set_timer(uint32_t);
    void LL_inc_timer();
};

#endif __USBHCORE_H__
