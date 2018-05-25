#ifndef __STM32_HCD_H__
#define __STM32_HCD_H__

/*
 * Based on HAL-F4 v1.21.0
 * */

#include "stm32_inc.h"

enum class EOTGDeviceMode
{
    DEVICE = 0,
    HOST = 1,
    DRD = 2,
};

enum class EURBState
{
    IDLE = 0,
    DONE,
    NOT_READY,
    NYET,
    ERROR,
    STALL,
};

enum class EHCState
{
    IDLE = 0,
    XFRC,
    HALTED,
    NAK,
    NYET,
    STALL,
    XACTERR,
    BBLERR,
    DATATGLERR,
};

enum class EOTGSpeed
{
    HIGH = 0,
    HIGH_IN_FULL = 1,
    LOW = 2,
    FULL = 3,
};

enum class EOTG_PHY
{
    ULPI = 1,
    EMBEDDED = 2,
};

#define USB_OTG_HS_MAX_PACKET_SIZE           512U
#define USB_OTG_FS_MAX_PACKET_SIZE           64U
#define USB_OTG_MAX_EP0_SIZE                 64U

#define DSTS_ENUMSPD_HS_PHY_30MHZ_OR_60MHZ     (0U << 1U)
#define DSTS_ENUMSPD_FS_PHY_30MHZ_OR_60MHZ     (1U << 1U)
#define DSTS_ENUMSPD_LS_PHY_6MHZ               (2U << 1U)
#define DSTS_ENUMSPD_FS_PHY_48MHZ              (3U << 1U)

#define DCFG_FRAME_INTERVAL_80                 0U
#define DCFG_FRAME_INTERVAL_85                 1U
#define DCFG_FRAME_INTERVAL_90                 2U
#define DCFG_FRAME_INTERVAL_95                 3U

#define DEP0CTL_MPS_64                         0U
#define DEP0CTL_MPS_32                         1U
#define DEP0CTL_MPS_16                         2U
#define DEP0CTL_MPS_8                          3U

#define EP_SPEED_LOW                           0U
#define EP_SPEED_FULL                          1U
#define EP_SPEED_HIGH                          2U

#define EP_TYPE_CTRL                           0U
#define EP_TYPE_ISOC                           1U
#define EP_TYPE_BULK                           2U
#define EP_TYPE_INTR                           3U
#define EP_TYPE_MSK                            3U

#define STS_GOUT_NAK                           1U
#define STS_DATA_UPDT                          2U
#define STS_XFER_COMP                          3U
#define STS_SETUP_COMP                         4U
#define STS_SETUP_UPDT                         6U

#define HCFG_30_60_MHZ                         0U
#define HCFG_48_MHZ                            1U
#define HCFG_6_MHZ                             2U

#define HPRT0_PRTSPD_HIGH_SPEED                0U
#define HPRT0_PRTSPD_FULL_SPEED                1U
#define HPRT0_PRTSPD_LOW_SPEED                 2U

#define HCCHAR_CTRL                            0U
#define HCCHAR_ISOC                            1U
#define HCCHAR_BULK                            2U
#define HCCHAR_INTR                            3U

#define HC_PID_DATA0                           0U
#define HC_PID_DATA2                           1U
#define HC_PID_DATA1                           2U
#define HC_PID_SETUP                           3U

#define GRXSTS_PKTSTS_IN                       2U
#define GRXSTS_PKTSTS_IN_XFER_COMP             3U
#define GRXSTS_PKTSTS_DATA_TOGGLE_ERR          5U
#define GRXSTS_PKTSTS_CH_HALTED                7U

#define USB_IN_EP_COUNT ((USB_OTG_OUT_ENDPOINT_BASE - USB_OTG_IN_ENDPOINT_BASE) / USB_OTG_EP_REG_SIZE)
#define USB_OUT_EP_COUNT ((USB_OTG_PCGCCTL_BASE - USB_OTG_OUT_ENDPOINT_BASE) / USB_OTG_EP_REG_SIZE)
#define USB_HOST_PORTS_COUNT ((USB_OTG_HOST_CHANNEL_BASE - USB_OTG_HOST_PORT_BASE) / sizeof(uint32_t))
#define USB_HOST_CHANNELS_COUNT ((USB_OTG_DEVICE_BASE - USB_OTG_HOST_CHANNEL_BASE) / USB_OTG_HOST_CHANNEL_SIZE)
#define USB_PCGCCTL_COUNT ((USB_OTG_FIFO_BASE - USB_OTG_PCGCCTL_BASE) / sizeof(uint32_t))
#define USB_DFIFO_COUNT (USB_OTG_FIFO_SIZE / sizeof(uint32_t))

enum class EHCDState
{
    RESET_ = 0,
    READY,
    ERROR,
    BUSY,
    TIMEOUT,
};

typedef struct
{
    USB_OTG_GlobalTypeDef       global;
    USB_OTG_HostTypeDef         host;
    uint32_t                    ports[USB_HOST_PORTS_COUNT];
    USB_OTG_HostChannelTypeDef  channels[USB_HOST_CHANNELS_COUNT];
    USB_OTG_DeviceTypeDef       device;
    USB_OTG_INEndpointTypeDef   in_eps[USB_IN_EP_COUNT];
    USB_OTG_OUTEndpointTypeDef  out_eps[USB_OUT_EP_COUNT];
    uint32_t                    PCGCCTL[USB_PCGCCTL_COUNT];
    uint32_t                    DFIFO[USB_DFIFO_COUNT];
} OTGRegs_t;

typedef struct
{
  uint8_t   dev_addr ;     /*!< USB device address.
                                This parameter must be a number between Min_Data = 1 and Max_Data = 255    */
  uint8_t   ch_num;        /*!< Host channel number.
                                This parameter must be a number between Min_Data = 1 and Max_Data = 15     */
  uint8_t   ep_num;        /*!< Endpoint number.
                                This parameter must be a number between Min_Data = 1 and Max_Data = 15     */
  uint8_t   ep_is_in;      /*!< Endpoint direction
                                This parameter must be a number between Min_Data = 0 and Max_Data = 1      */
  uint8_t   speed;         /*!< USB Host speed.
                                This parameter can be any value of @ref USB_Core_Speed_                    */
  uint8_t   do_ping;       /*!< Enable or disable the use of the PING protocol for HS mode.                */
  uint8_t   process_ping;  /*!< Execute the PING protocol for HS mode.                                     */
  uint8_t   ep_type;       /*!< Endpoint Type.
                                This parameter can be any value of @ref USB_EP_Type_                       */
  uint16_t  max_packet;    /*!< Endpoint Max packet size.
                                This parameter must be a number between Min_Data = 0 and Max_Data = 64KB   */
  uint8_t   data_pid;      /*!< Initial data PID.
                                This parameter must be a number between Min_Data = 0 and Max_Data = 1      */
  uint8_t   *xfer_buff;    /*!< Pointer to transfer buffer.                                                */
  uint32_t  xfer_len;      /*!< Current transfer length.                                                   */
  uint32_t  xfer_count;    /*!< Partial transfer length in case of multi packet transfer.                  */
  uint8_t   toggle_in;     /*!< IN transfer current toggle flag.
                                This parameter must be a number between Min_Data = 0 and Max_Data = 1      */
  uint8_t   toggle_out;    /*!< OUT transfer current toggle flag
                                This parameter must be a number between Min_Data = 0 and Max_Data = 1      */
  uint32_t  dma_addr;      /*!< 32 bits aligned transfer buffer address.                                   */
  uint32_t  ErrCnt;        /*!< Host channel error count.*/
  EURBState urb_state;     /*!< URB state.
                                This parameter can be any value of @ref USB_OTG_URBStateTypeDef            */
  EHCDState state;         /*!< Host Channel state.
                                This parameter can be any value of @ref USB_OTG_HCStateTypeDef             */
} OTG_HC_t;

class STM32_HCD
{
public:
    uint32_t init(USB_OTG_GlobalTypeDef *regs_addr);
    uint32_t deInit();

    inline void enable() { enable_global_int(); }
    inline void disable() { disable_global_int(); }

    inline uint32_t get_flag(uint32_t mask) { return (read_IT() & mask) == mask; }
    inline void clear_flag(uint32_t mask) { m_regs->global.GINTSTS = mask; }
    inline bool is_invalid_IT() { return (read_IT() == 0); }

    inline void clear_HC_int(uint8_t ch_num, uint32_t mask) { m_regs->channels[ch_num].HCINT = mask; }
    inline void mask_halt_HC_int(uint8_t ch_num) { m_regs->channels[ch_num].HCINTMSK &= ~USB_OTG_HCINTMSK_CHHM; }
    inline void unmask_halt_HC_int(uint8_t ch_num) { m_regs->channels[ch_num].HCINTMSK |= USB_OTG_HCINTMSK_CHHM; }
    inline void mask_ack_HC_int(uint8_t ch_num) { m_regs->channels[ch_num].HCINTMSK &= ~USB_OTG_HCINTMSK_ACKM; }
    inline void unmask_ack_HC_int(uint8_t ch_num) { m_regs->channels[ch_num].HCINTMSK |= USB_OTG_HCINTMSK_ACKM; }

    inline void mask_IT(uint32_t mask) { m_regs->global.GINTMSK &= ~mask; }
    inline void unmask_IT(uint32_t mask) { m_regs->global.GINTMSK |= mask; }

    inline void clear_in_ep_intr(uint8_t ep_num, uint32_t mask) { m_regs->in_eps[ep_num].DIEPINT = mask; }
    inline void clear_out_ep_intr(uint8_t ep_num, uint32_t mask) { m_regs->out_eps[ep_num].DOEPINT = mask; }

    uint32_t get_current_frame();
    EOTGSpeed get_current_speed();

    void set_toggle(uint8_t pipe, uint8_t toggle);
    uint8_t get_toggle(uint8_t pipe);

    uint32_t reset_port();
    uint32_t start();
    uint32_t stop();

    EHCDState get_state();

    uint32_t HC_init(uint8_t ch_num, uint8_t ep_num, uint8_t dev_address, EOTGSpeed speed, uint8_t ep_type, uint16_t tmp);
    uint32_t HC_submit_request(uint8_t ch_num, uint8_t direction, uint8_t ep_type, uint8_t token, uint8_t* pbuff, uint16_t length, uint8_t do_ping);
    uint32_t HC_halt(uint8_t hc_num);
    uint32_t HC_get_Xfer_count(uint8_t ch_num);
    EURBState HC_get_URB_state(uint8_t chnum);
    EHCState HC_get_state(uint8_t chnum);
private:
    OTGRegs_t*  m_regs;
    OTG_HC_t    m_HC[15];
    uint32_t    m_lock;
    EHCDState   m_state;
    void*       m_data;

    void init_gpio();
    void deInit_gpio();

    uint32_t core_init();
    uint32_t dev_init();

    uint32_t enable_global_int();
    uint32_t disable_global_int();

    uint32_t set_current_mode(EOTGDeviceMode mode);
    uint32_t sed_dev_speed(EOTGSpeed speed);

    uint32_t flush_RX_FIFO();
    uint32_t flush_TX_FIFO(uint32_t num);

    uint32_t activate_endpoint();
    uint32_t deactivate_endpoint();
    uint32_t activate_dedicated_endpoint();
    uint32_t deactivate_dedicated_endpoint();

    uint32_t EP_start_Xfer();
    uint32_t EP0_start_Xfer();

    uint32_t write_packet(uint8_t* src, uint8_t ch_ep_num, uint16_t len, uint8_t dma);
    void* read_packet(uint8_t* dest, uint16_t len);

    uint32_t EP_set_stall();
    uint32_t EP_clear_stall();

    uint32_t set_dev_address(uint8_t address);

    uint32_t dev_connect();
    uint32_t dev_disconnect();

    uint32_t stop_device();

    uint32_t activate_setup();

    uint32_t EP0_out_start(uint8_t dma, uint8_t* psetup);

    EOTGSpeed get_dev_speed();
    uint32_t get_mode();
    uint32_t read_IT();
    uint32_t read_dev_all_out_EP_IT();
    uint32_t read_dev_out_EP_IT(uint8_t ep_num);
    uint32_t read_dev_all_in_EP_ITt();
    uint32_t read_dev_in_EP_IT(uint8_t ep_num);
    void clear_IT(uint32_t interrupts);

    uint32_t host_init();
    uint32_t init_FSLSPClk_sel(uint8_t freq);
    uint32_t drive_VBUS(uint8_t state);

    uint32_t get_host_speed();

    uint32_t HC_start_Xfer();

    uint32_t do_ping(uint8_t ch_num);
    uint32_t stop_host();
};

#ifdef STM32_USE_USB_FS
extern STM32_HCD usb_fs;
#endif

#ifdef STM32_USE_USB_HS
extern STM32_HCD usb_hs;
#endif

#endif
