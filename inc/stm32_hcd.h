#ifndef __STM32_HCD_H__
#define __STM32_HCD_H__

/*
 * Based on HAL-F4 v1.21.0
 * */

#include "stm32_inc.h"

enum class EOTGDeviceMode: uint32_t
{
    DEVICE = 0,
    HOST = 1,
    DRD = 2,
};

enum class EURBState: uint32_t
{
    IDLE = 0,
    DONE,
    NOT_READY,
    NYET,
    ERROR,
    STALL,
};

enum class EHCState: uint32_t
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

enum class EOTGSpeed: uint32_t
{
    HIGH = 0,
    HIGH_IN_FULL = 1,
    LOW = 2,
    FULL = 3,
};

enum class EOTG_PHY: uint32_t
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

enum class EEPType: uint32_t
{
    CTRL = 0,
    ISOC,
    BULK,
    INTR,
    MSK,
};

#define STS_GOUT_NAK                           1U
#define STS_DATA_UPDT                          2U
#define STS_XFER_COMP                          3U
#define STS_SETUP_COMP                         4U
#define STS_SETUP_UPDT                         6U

enum class EClockSpeed: uint32_t
{
    _30_60_MHZ = 0,
    _48_MHZ,
    _6_MHZ,
};

#define HPRT0_PRTSPD_HIGH_SPEED                0U
#define HPRT0_PRTSPD_FULL_SPEED                1U
#define HPRT0_PRTSPD_LOW_SPEED                 2U

#define HCCHAR_CTRL                            (0U << USB_OTG_HCCHAR_EPTYP_Pos)
#define HCCHAR_ISOC                            (1U << USB_OTG_HCCHAR_EPTYP_Pos)
#define HCCHAR_BULK                            (2U << USB_OTG_HCCHAR_EPTYP_Pos)
#define HCCHAR_INTR                            (3U << USB_OTG_HCCHAR_EPTYP_Pos)

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

enum class EHCDState: uint32_t
{
    RESET_ = 0,
    READY,
    ERROR,
    BUSY,
    TIMEOUT,
};

#pragma pack(push, 4)
typedef struct
{
    USB_OTG_GlobalTypeDef       global;
    uint32_t                    dummy0[176];
    USB_OTG_HostTypeDef         host;
    uint32_t                    dummy1[9];
    uint32_t                    ports[USB_HOST_PORTS_COUNT];
    USB_OTG_HostChannelTypeDef  channels[USB_HOST_CHANNELS_COUNT];
    USB_OTG_DeviceTypeDef       device;
    uint32_t                    dummy2[30];
    USB_OTG_INEndpointTypeDef   in_eps[USB_IN_EP_COUNT];
    USB_OTG_OUTEndpointTypeDef  out_eps[USB_OUT_EP_COUNT];
    uint32_t                    PCGCCTL[USB_PCGCCTL_COUNT];
    uint32_t                    DFIFO[USB_DFIFO_COUNT];
} OTGRegs_t;
#pragma pack(pop)

typedef struct
{
  uint8_t   dev_addr ;     /*!< USB device address.
                                This parameter must be a number between Min_Data = 1 and Max_Data = 255    */
  uint8_t   ch_num;        /*!< Host channel number.
                                This parameter must be a number between Min_Data = 1 and Max_Data = 15     */
  uint8_t   ep_num;        /*!< Endpoint number.
                                This parameter must be a number between Min_Data = 1 and Max_Data = 15     */
  bool      ep_is_in;      /*!< Endpoint direction
                                This parameter must be a number between Min_Data = 0 and Max_Data = 1      */
  EOTGSpeed speed;         /*!< USB Host speed.
                                This parameter can be any value of @ref USB_Core_Speed_                    */
  bool      do_ping;       /*!< Enable or disable the use of the PING protocol for HS mode.                */
  uint8_t   process_ping;  /*!< Execute the PING protocol for HS mode.                                     */
  EEPType   ep_type;       /*!< Endpoint Type.
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
  bool      toggle_out;    /*!< OUT transfer current toggle flag
                                This parameter must be a number between Min_Data = 0 and Max_Data = 1      */
  uint32_t  dma_addr;      /*!< 32 bits aligned transfer buffer address.                                   */
  uint32_t  ErrCnt;        /*!< Host channel error count.*/
  EURBState urb_state;     /*!< URB state.
                                This parameter can be any value of @ref USB_OTG_URBStateTypeDef            */
  EHCState  state;         /*!< Host Channel state.
                                This parameter can be any value of @ref USB_OTG_HCStateTypeDef             */
} OTG_HC_t;

#define TX_FIFO_COUNT 0x10

#define deactivate_dedicated_endpoint deactivate_endpoint

class STM32_HCD
{
public:
    uint32_t init(USB_OTG_GlobalTypeDef *regs_addr, EOTG_PHY phy, bool use_ext_vbus, bool dma_enable, EOTGSpeed speed, uint32_t host_channels);
    void deInit();

    FORCE_INLINE void set_data(void* data) { m_data = data; }
    FORCE_INLINE void* get_data() { return m_data; }

    FORCE_INLINE void enable() { enable_global_int(); }
    FORCE_INLINE void disable() { disable_global_int(); }

    FORCE_INLINE uint32_t get_flag(uint32_t mask) { return (read_IT() & mask) == mask; }
    FORCE_INLINE void clear_flag(uint32_t mask) { m_regs->global.GINTSTS = mask; }
    FORCE_INLINE bool is_invalid_IT() { return (read_IT() == 0); }

    FORCE_INLINE bool is_HC_int(uint8_t ch_num, uint32_t mask) { return (m_regs->channels[ch_num].HCINT & mask) == mask; }
    FORCE_INLINE void clear_HC_int(uint8_t ch_num, uint32_t mask) { m_regs->channels[ch_num].HCINT = mask; }
    FORCE_INLINE void set_HC_int(uint8_t ch_num, uint32_t val) { m_regs->channels[ch_num].HCINTMSK = val; }
    FORCE_INLINE void mask_HC_int(uint8_t ch_num, uint32_t mask) { m_regs->channels[ch_num].HCINTMSK &= ~mask; }
    FORCE_INLINE void unmask_HC_int(uint8_t ch_num, uint32_t mask) { m_regs->channels[ch_num].HCINTMSK |= mask; }
    FORCE_INLINE void mask_halt_HC_int(uint8_t ch_num) { m_regs->channels[ch_num].HCINTMSK &= ~USB_OTG_HCINTMSK_CHHM; }
    FORCE_INLINE void mask_all_HC_int(uint8_t ch_num) { m_regs->channels[ch_num].HCINTMSK = 0; }
    FORCE_INLINE void unmask_halt_HC_int(uint8_t ch_num) { m_regs->channels[ch_num].HCINTMSK |= USB_OTG_HCINTMSK_CHHM; }
    FORCE_INLINE void mask_ack_HC_int(uint8_t ch_num) { m_regs->channels[ch_num].HCINTMSK &= ~USB_OTG_HCINTMSK_ACKM; }
    FORCE_INLINE void unmask_ack_HC_int(uint8_t ch_num) { m_regs->channels[ch_num].HCINTMSK |= USB_OTG_HCINTMSK_ACKM; }

    FORCE_INLINE void mask_IT(uint32_t mask) { m_regs->global.GINTMSK &= ~mask; }
    FORCE_INLINE void unmask_IT(uint32_t mask) { m_regs->global.GINTMSK |= mask; }

    FORCE_INLINE void clear_in_ep_intr(uint8_t ep_num, uint32_t mask) { m_regs->in_eps[ep_num].DIEPINT = mask; }
    FORCE_INLINE void clear_out_ep_intr(uint8_t ep_num, uint32_t mask) { m_regs->out_eps[ep_num].DOEPINT = mask; }

    FORCE_INLINE uint32_t get_current_frame() { return (m_regs->host.HFNUM & USB_OTG_HFNUM_FRNUM); }
    FORCE_INLINE EOTGSpeed get_current_speed() { return get_host_speed(); }

    void set_toggle(uint8_t pipe, uint8_t toggle);
    uint8_t get_toggle(uint8_t pipe);

    void reset_port();
    FORCE_INLINE void reset_port_st1(uint32_t val) { m_regs->ports[0] = val; }
    uint32_t start();
    uint32_t stop();

    FORCE_INLINE EHCDState get_state() { return m_state; }

    FORCE_INLINE void enable_host_IT(uint8_t ch_num) { m_regs->host.HAINTMSK |= (1 << ch_num); }
    FORCE_INLINE void set_host_IT(uint32_t val) { m_regs->host.HAINT = val; }

    uint32_t HC_init(uint8_t ch_num, uint8_t ep_num, uint8_t dev_address, EOTGSpeed speed, EEPType ep_type, uint16_t mps);
    FORCE_INLINE void HC_set_params(uint8_t ch_num, uint8_t ep_num, uint8_t dev_address, EOTGSpeed speed, EEPType ep_type, uint16_t mps)
        {
            m_regs->channels[ch_num].HCCHAR = ((dev_address << USB_OTG_HCCHAR_DAD_Pos) & USB_OTG_HCCHAR_DAD) |
                    (((ep_num & 0x7f) << USB_OTG_HCCHAR_EPNUM_Pos) & USB_OTG_HCCHAR_EPNUM) |
                    ((((ep_num & 0x80) == 0x80) << USB_OTG_HCCHAR_EPDIR_Pos) & USB_OTG_HCCHAR_EPDIR) |
                    (((speed == EOTGSpeed::LOW) << USB_OTG_HCCHAR_LSDEV_Pos) & USB_OTG_HCCHAR_LSDEV) |
                    (((uint32_t)ep_type << USB_OTG_HCCHAR_EPTYP_Pos) & USB_OTG_HCCHAR_EPTYP) |
                    (mps & USB_OTG_HCCHAR_MPSIZ);
        }
    FORCE_INLINE bool HC_get_dir(uint8_t ch_num) { return ((m_regs->channels[ch_num].HCCHAR & USB_OTG_HCCHAR_EPDIR) == USB_OTG_HCCHAR_EPDIR); }
    FORCE_INLINE uint32_t HC_get_params(uint8_t ch_num) { return m_regs->channels[ch_num].HCCHAR; }
    FORCE_INLINE void HC_set_param_RAW(uint8_t ch_num, uint32_t val) { m_regs->channels[ch_num].HCCHAR = val; }
    FORCE_INLINE void HC_enable_param(uint8_t ch_num, uint32_t mask) { m_regs->channels[ch_num].HCCHAR |= mask; }
    FORCE_INLINE void HC_disable_param(uint8_t ch_num, uint32_t mask) { m_regs->channels[ch_num].HCCHAR &= ~mask; }
    void HC_submit_request(uint8_t ch_num, bool is_in, EEPType ep_type, bool token, uint8_t* pbuff, uint16_t length, bool do_ping);
    uint32_t HC_halt(uint8_t hc_num);
    FORCE_INLINE uint32_t HC_get_Xfer_count(uint8_t chnum) { return m_HC[chnum].xfer_count; }
    FORCE_INLINE EURBState HC_get_URB_state(uint8_t chnum) { return m_HC[chnum].urb_state; }
    FORCE_INLINE EHCState HC_get_state(uint8_t chnum) { return m_HC[chnum].state; }

    void IRQ_handler();
private:
    OTGRegs_t*  m_regs;
    OTG_HC_t    m_HC[15];
    uint32_t    m_lock;
    EHCDState   m_state;
    void*       m_data;
    bool        m_dma_enable;
    uint32_t    m_host_channels;
    EOTG_PHY    m_phy;
    EOTGSpeed   m_speed;

    void init_gpio();
    void deInit_gpio();

    uint32_t core_init(EOTG_PHY phy, bool use_ext_vbus, bool dma_enable);
    FORCE_INLINE void power_down() { m_regs->global.GCCFG &= ~USB_OTG_GCCFG_PWRDWN; }
    FORCE_INLINE void power_up() { m_regs->global.GCCFG = USB_OTG_GCCFG_PWRDWN; }
    FORCE_INLINE void init_phy_ULPI() { m_regs->global.GUSBCFG &= ~(USB_OTG_GUSBCFG_TSDPS | USB_OTG_GUSBCFG_ULPIFSLS | USB_OTG_GUSBCFG_PHYSEL); }
    FORCE_INLINE void init_phy_embedded() { m_regs->global.GUSBCFG |= USB_OTG_GUSBCFG_PHYSEL; }
    FORCE_INLINE void reset_ULPI_VBUS() { m_regs->global.GUSBCFG &= ~(USB_OTG_GUSBCFG_ULPIEVBUSD | USB_OTG_GUSBCFG_ULPIEVBUSI); }
    FORCE_INLINE void set_ULPI_VBUS() { m_regs->global.GUSBCFG |= USB_OTG_GUSBCFG_ULPIEVBUSD; }
    FORCE_INLINE void enable_DMA() { m_regs->global.GAHBCFG |= (USB_OTG_GAHBCFG_HBSTLEN_2 | USB_OTG_GAHBCFG_DMAEN); }
    void dev_init(bool vbus_sending_enable, EOTG_PHY phy, EOTGSpeed speed, uint32_t ep_count, bool dma_enable, bool sof_enable);
    ENDIS_REG_FLAG_NAME_SL(VBUS_A, m_regs->global.GCCFG, USB_OTG_GCCFG_VBUSASEN)
    ENDIS_REG_FLAG_NAME_SL(VBUS_B, m_regs->global.GCCFG, USB_OTG_GCCFG_VBUSBSEN)
    ENDIS_REG_FLAG_NAME_SL(VBUS, m_regs->global.GCCFG, USB_OTG_GCCFG_NOVBUSSENS)
    FORCE_INLINE void restart_phy_clock() { m_regs->PCGCCTL[0] = 0; }
    FORCE_INLINE void mode_device_configuration() { m_regs->device.DCFG |= DCFG_FRAME_INTERVAL_80; }
    FORCE_INLINE void clear_all_ITs() { clear_in_IT();       clear_out_IT();
                                  clear_shared_IT();   m_regs->device.DAINTMSK = 0; }
    FORCE_INLINE bool is_in_endpoint_enable(uint32_t ep_idx) { return (m_regs->in_eps[ep_idx].DIEPCTL & USB_OTG_DIEPCTL_EPENA) == USB_OTG_DIEPCTL_EPENA; }
    FORCE_INLINE void disable_NAK_in_endpoint(uint32_t ep_idx) { m_regs->in_eps[ep_idx].DIEPCTL = (USB_OTG_DIEPCTL_EPDIS | USB_OTG_DIEPCTL_SNAK); }
    FORCE_INLINE void disable_in_endpoint(uint32_t ep_idx) { m_regs->in_eps[ep_idx].DIEPCTL = 0; }
    FORCE_INLINE void in_endpoint_reset_Xfer_size(uint32_t ep_idx) { m_regs->in_eps[ep_idx].DIEPTSIZ = 0; }
    FORCE_INLINE void in_endpoint_reset_IT(uint32_t ep_idx) { m_regs->in_eps[ep_idx].DIEPINT = 0xff; }
    FORCE_INLINE bool is_out_endpoint_enable(uint32_t ep_idx) { return (m_regs->out_eps[ep_idx].DOEPCTL & USB_OTG_DOEPCTL_EPENA) == USB_OTG_DOEPCTL_EPENA; }
    FORCE_INLINE void disable_NAK_out_endpoint(uint32_t ep_idx) { m_regs->out_eps[ep_idx].DOEPCTL = (USB_OTG_DOEPCTL_EPDIS | USB_OTG_DOEPCTL_SNAK); }
    FORCE_INLINE void disable_out_endpoint(uint32_t ep_idx) { m_regs->out_eps[ep_idx].DOEPCTL = 0; }
    FORCE_INLINE void out_endpoint_reset_Xfer_size(uint32_t ep_idx) { m_regs->out_eps[ep_idx].DOEPTSIZ = 0; }
    FORCE_INLINE void out_endpoint_reset_IT(uint32_t ep_idx) { m_regs->out_eps[ep_idx].DOEPINT = 0xff; }
    FORCE_INLINE void reset_FIFO_underrun_flag() { m_regs->device.DIEPMSK &= ~USB_OTG_DIEPMSK_TXFURM; }
    FORCE_INLINE void set_DMA_thresshold() {  m_regs->device.DTHRCTL = (USB_OTG_DTHRCTL_TXTHRLEN_6 | USB_OTG_DTHRCTL_RXTHRLEN_6 |
                                                                  USB_OTG_DTHRCTL_RXTHREN | USB_OTG_DTHRCTL_ISOTHREN | USB_OTG_DTHRCTL_NONISOTHREN);
                                        __IO uint32_t tmp = m_regs->device.DTHRCTL;
                                        UNUSED(tmp);
                                     }
    FORCE_INLINE void disable_all_IT() { m_regs->global.GINTMSK = 0; }
    FORCE_INLINE void clear_all_IT() { m_regs->global.GINTSTS = 0xbfffffff; }
    FORCE_INLINE void clear_all_IT1() { m_regs->global.GINTSTS = 0xffffffff; }
    FORCE_INLINE void enable_IT(uint32_t mask) { m_regs->global.GINTMSK |= mask; }

    FORCE_INLINE void enable_global_int() { m_regs->global.GAHBCFG |= USB_OTG_GAHBCFG_GINT; }
    FORCE_INLINE void disable_global_int() { m_regs->global.GAHBCFG &= ~USB_OTG_GAHBCFG_GINT; }

    void set_current_mode(EOTGDeviceMode mode);
    FORCE_INLINE void reset_mode() { m_regs->global.GUSBCFG &= ~(USB_OTG_GUSBCFG_FHMOD | USB_OTG_GUSBCFG_FDMOD); }
    FORCE_INLINE void set_mode_host() { m_regs->global.GUSBCFG |= USB_OTG_GUSBCFG_FHMOD; }
    FORCE_INLINE void set_mode_device() { m_regs->global.GUSBCFG |= USB_OTG_GUSBCFG_FDMOD; }

    FORCE_INLINE void set_dev_speed(EOTGSpeed speed) { m_regs->device.DCFG |= (uint32_t)speed; }
    FORCE_INLINE uint32_t get_dev_speed_RAW() { return (m_regs->device.DSTS & USB_OTG_DSTS_ENUMSPD); }
    EOTGSpeed get_dev_speed();

    uint32_t flush_RX_FIFO();
    uint32_t flush_TX_FIFO(uint32_t num);

    FORCE_INLINE bool is_frame_odd() { return (m_regs->device.DSTS & (1 << USB_OTG_DSTS_FNSOF_Pos)) == 0; }

    void activate_endpoint(bool ep_is_in, uint8_t ep_num, uint32_t ep_maxpacket, uint8_t ep_type);
    uint32_t deactivate_endpoint(bool ep_is_in, uint8_t ep_num);
    void activate_dedicated_endpoint(bool ep_is_in, uint8_t ep_num, uint32_t ep_maxpacket, uint8_t ep_type);

    FORCE_INLINE void set_ep_IT_mask(uint32_t mask) { m_regs->device.DAINTMSK |= mask; }
    FORCE_INLINE void set_ded_ep_IT_mask(uint32_t mask) { m_regs->device.DEACHMSK |= mask; }
    FORCE_INLINE void clear_ep_IT_mask(uint32_t mask) { m_regs->device.DAINTMSK &= ~mask; }

    FORCE_INLINE bool is_ep_in_active(uint8_t ep_num) { return (m_regs->in_eps[ep_num].DIEPCTL & USB_OTG_DIEPCTL_USBAEP) == USB_OTG_DIEPCTL_USBAEP; }
    FORCE_INLINE void deactivate_ep_in(uint8_t ep_num) { m_regs->in_eps[ep_num].DIEPCTL &= ~USB_OTG_DIEPCTL_USBAEP; }
    FORCE_INLINE void set_NAK_ep_in(uint8_t ep_num) { m_regs->in_eps[ep_num].DIEPCTL = USB_OTG_DIEPCTL_SNAK; }
    FORCE_INLINE bool is_ep_in_disabled(uint8_t ep_num) { return (m_regs->in_eps[ep_num].DIEPINT & USB_OTG_DIEPCTL_EPDIS) == USB_OTG_DIEPCTL_EPDIS; }
    FORCE_INLINE void disable_ep_in(uint8_t ep_num) { m_regs->in_eps[ep_num].DIEPCTL = USB_OTG_DIEPCTL_EPDIS; }
    FORCE_INLINE void undisable_ep_in(uint8_t ep_num) { m_regs->in_eps[ep_num].DIEPCTL &= ~USB_OTG_DIEPCTL_EPDIS; }
    FORCE_INLINE void activate_ep_in(uint8_t ep_num, uint32_t ep_maxpacket, uint8_t ep_type)
        { m_regs->in_eps[ep_num].DIEPCTL |= (ep_maxpacket & USB_OTG_DIEPCTL_MPSIZ) |
                                            (ep_type << USB_OTG_DIEPCTL_EPTYP_Pos) |
                                            (ep_num << USB_OTG_DIEPCTL_TXFNUM_Pos) |
                                            USB_OTG_DIEPCTL_SD0PID_SEVNFRM | USB_OTG_DIEPCTL_USBAEP; }

    FORCE_INLINE bool is_ep_out_active(uint8_t ep_num) { return (m_regs->out_eps[ep_num].DOEPCTL & USB_OTG_DOEPCTL_USBAEP) == USB_OTG_DOEPCTL_USBAEP; }
    FORCE_INLINE void deactivate_ep_out(uint8_t ep_num) { m_regs->out_eps[ep_num].DOEPCTL &= ~USB_OTG_DOEPCTL_USBAEP; }
    FORCE_INLINE void set_NAK_ep_out(uint8_t ep_num) { m_regs->out_eps[ep_num].DOEPCTL = USB_OTG_DOEPCTL_SNAK; }
    FORCE_INLINE bool is_ep_out_disabled(uint8_t ep_num) { return (m_regs->out_eps[ep_num].DOEPINT & USB_OTG_DOEPINT_OTEPDIS) == USB_OTG_DOEPINT_OTEPDIS; }
    FORCE_INLINE void disable_ep_out(uint8_t ep_num) { m_regs->out_eps[ep_num].DOEPCTL = USB_OTG_DOEPCTL_EPDIS; }
    FORCE_INLINE void undisable_ep_out(uint8_t ep_num) { m_regs->out_eps[ep_num].DOEPCTL &= ~USB_OTG_DOEPCTL_EPDIS; }
    FORCE_INLINE void clear_global_NAK() { m_regs->device.DCTL |= USB_OTG_DCTL_CGONAK; }
    FORCE_INLINE void activate_ep_out(uint8_t ep_num, uint32_t ep_maxpacket, uint8_t ep_type)
        { m_regs->out_eps[ep_num].DOEPCTL |= (ep_maxpacket & USB_OTG_DOEPCTL_MPSIZ) |
                                             (ep_type << USB_OTG_DOEPCTL_EPTYP_Pos) |
                                             (ep_num << 22) |
                                             USB_OTG_DIEPCTL_SD0PID_SEVNFRM | USB_OTG_DOEPCTL_USBAEP; }

    void EP_start_Xfer(bool ep_is_in, uint8_t ep_num, uint32_t ep_maxpacket,
                       uint8_t* xfer_buff, uint16_t xfer_len, EEPType ep_type,
                       bool dma, uint32_t dma_addr);
    void EP0_start_Xfer(bool ep_is_in, uint8_t ep_num, uint32_t ep_maxpacket,
                        uint8_t* xfer_buff, uint16_t xfer_len,
                        bool dma, uint32_t dma_addr);
    FORCE_INLINE void set_dev_empty_mask(uint32_t ep_num) { m_regs->device.DIEPEMPMSK |= (1 << ep_num); }

    FORCE_INLINE void Xfer_in_pkt_start(uint8_t ep_num)
        {
            m_regs->in_eps[ep_num].DIEPTSIZ &= ~USB_OTG_DIEPTSIZ_XFRSIZ;
            m_regs->in_eps[ep_num].DIEPTSIZ &= ~USB_OTG_DIEPTSIZ_PKTCNT;
        }
    FORCE_INLINE void Xfer_in_pkt_size(uint8_t ep_num, uint32_t len) {  m_regs->in_eps[ep_num].DIEPTSIZ |= (USB_OTG_DIEPTSIZ_PKTCNT & (len << USB_OTG_DIEPTSIZ_PKTCNT_Pos)); }
    FORCE_INLINE void Xfer_in_pkt_end(uint8_t ep_num, uint32_t len) { m_regs->in_eps[ep_num].DIEPTSIZ |= (USB_OTG_DIEPTSIZ_XFRSIZ & len); }
    FORCE_INLINE void Xfer_in_pkt_multi(uint8_t ep_num)
        {
            m_regs->in_eps[ep_num].DIEPTSIZ &= ~USB_OTG_DIEPTSIZ_MULCNT;
            m_regs->in_eps[ep_num].DIEPTSIZ |= (USB_OTG_DIEPTSIZ_MULCNT & (1 <USB_OTG_DIEPTSIZ_MULCNT_Pos));
        }
    FORCE_INLINE void Xfer_in_enable_DMA(uint8_t ep_num, uint32_t dma_addr) { m_regs->in_eps[ep_num].DIEPDMA = dma_addr; }
    FORCE_INLINE void Xfer_in_set_odd_frame(uint8_t ep_num) { m_regs->in_eps[ep_num].DIEPCTL |= USB_OTG_DIEPCTL_SODDFRM; }
    FORCE_INLINE void Xfer_in_set_data0_pid(uint8_t ep_num) { m_regs->in_eps[ep_num].DIEPCTL |= USB_OTG_DIEPCTL_SD0PID_SEVNFRM; }
    FORCE_INLINE void Xfer_in_ep_enable(uint8_t ep_num) { m_regs->in_eps[ep_num].DIEPCTL |= (USB_OTG_DIEPCTL_CNAK | USB_OTG_DIEPCTL_EPENA); }

    FORCE_INLINE void Xfer_out_pkt_start(uint8_t ep_num)
        {
            m_regs->out_eps[ep_num].DOEPTSIZ &= ~USB_OTG_DIEPTSIZ_XFRSIZ;
            m_regs->out_eps[ep_num].DOEPTSIZ &= ~USB_OTG_DOEPTSIZ_PKTCNT;
        }
    FORCE_INLINE void Xfer_out_pkt_size(uint8_t ep_num, uint32_t len) { m_regs->out_eps[ep_num].DOEPTSIZ |= (USB_OTG_DOEPTSIZ_PKTCNT & (len << USB_OTG_DOEPTSIZ_PKTCNT_Pos)); }
    FORCE_INLINE void Xfer_out_pkt_end(uint8_t ep_num, uint32_t len) { m_regs->out_eps[ep_num].DOEPTSIZ |= (USB_OTG_DOEPTSIZ_XFRSIZ & len); }
    FORCE_INLINE void Xfer_out_enable_DMA(uint8_t ep_num, uint32_t dma_addr) { m_regs->out_eps[ep_num].DOEPDMA = dma_addr; }
    FORCE_INLINE void Xfer_out_set_odd_frame(uint8_t ep_num) { m_regs->out_eps[ep_num].DOEPCTL |= USB_OTG_DOEPCTL_SODDFRM; }
    FORCE_INLINE void Xfer_out_set_data0_pid(uint8_t ep_num) { m_regs->out_eps[ep_num].DOEPCTL |= USB_OTG_DOEPCTL_SD0PID_SEVNFRM; }
    FORCE_INLINE void Xfer_out_ep_enable(uint8_t ep_num) { m_regs->out_eps[ep_num].DOEPCTL |= (USB_OTG_DOEPCTL_CNAK | USB_OTG_DOEPCTL_EPENA); }

    void write_packet(uint8_t* src, uint8_t ch_ep_num, uint16_t len, uint8_t dma);
    void* read_packet(uint8_t* dest, uint16_t len);
    FORCE_INLINE void write_FIFO(uint8_t cp_ep_num, uint32_t data) { m_regs->DFIFO[cp_ep_num] = data; }
    FORCE_INLINE uint32_t read_FIFO(uint8_t cp_ep_num) { return m_regs->DFIFO[cp_ep_num]; }

    void EP_set_stall(bool ep_is_in, uint8_t ep_num);
    void EP_clear_stall(bool ep_is_in, uint8_t ep_num, EEPType ep_type);
    FORCE_INLINE void ep_in_set_stall(uint8_t ep_num) { m_regs->in_eps[ep_num].DIEPCTL |= USB_OTG_DIEPCTL_STALL; }
    FORCE_INLINE void ep_in_clear_stall(uint8_t ep_num) { m_regs->in_eps[ep_num].DIEPCTL &= ~USB_OTG_DIEPCTL_STALL; }
    FORCE_INLINE void ep_out_set_stall(uint8_t ep_num) { m_regs->out_eps[ep_num].DOEPCTL |= USB_OTG_DOEPCTL_STALL; }
    FORCE_INLINE void ep_out_clear_stall(uint8_t ep_num) { m_regs->out_eps[ep_num].DOEPCTL &= ~USB_OTG_DOEPCTL_STALL; }

    void set_dev_address(uint8_t address);
    FORCE_INLINE void clear_dev_address() { m_regs->device.DCFG &= ~USB_OTG_DCFG_DAD; }
    FORCE_INLINE void set_dev_addr_RAW(uint8_t addr) { m_regs->device.DCFG |= (addr << 4) & USB_OTG_DCFG_DAD; }

    FORCE_INLINE void dev_connect() { m_regs->device.DCTL &= ~USB_OTG_DCTL_SDIS; STM32_SYSTICK::delay(3); }
    FORCE_INLINE void dev_disconnect() { m_regs->device.DCTL |= USB_OTG_DCTL_SDIS; STM32_SYSTICK::delay(3); }

    void stop_device();
    FORCE_INLINE void clear_shared_IT() { m_regs->device.DAINT = 0xffffffff; }
    FORCE_INLINE void clear_in_IT() { m_regs->device.DIEPMSK = 0; }
    FORCE_INLINE void clear_out_IT() { m_regs->device.DOEPMSK = 0; }

    void activate_setup();
    FORCE_INLINE void reset_max_pkt_size() { m_regs->in_eps[0].DIEPCTL &= ~USB_OTG_DIEPCTL_MPSIZ; }
    FORCE_INLINE void set_in_max_pkt_size(uint32_t max_size) { m_regs->in_eps[0].DIEPCTL |= max_size; }
    FORCE_INLINE void clear_in_global_NAK() { m_regs->device.DCTL |= USB_OTG_DCTL_CGINAK; }

    void EP0_out_start(uint8_t dma, uint8_t* psetup);
    FORCE_INLINE void ep_out_setup_packet_count() { m_regs->out_eps[0].DOEPTSIZ |= USB_OTG_DOEPTSIZ_STUPCNT; }
    FORCE_INLINE void ep_out_start_enable() { m_regs->out_eps[0].DOEPCTL |= (USB_OTG_DOEPCTL_USBAEP | USB_OTG_DOEPCTL_EPENA); }

    FORCE_INLINE EOTGDeviceMode get_mode() { return (EOTGDeviceMode)(m_regs->global.GINTSTS & 0x1); }
    FORCE_INLINE uint32_t read_IT() { return m_regs->global.GINTSTS & m_regs->global.GINTMSK; }
    FORCE_INLINE uint32_t read_dev_all_out_EP_IT() { return (((m_regs->device.DAINT & m_regs->device.DAINTMSK) & 0xffff0000) >> 16); }
    FORCE_INLINE uint32_t read_dev_out_EP_IT(uint8_t ep_num) { return (m_regs->out_eps[ep_num].DOEPINT & m_regs->device.DOEPMSK); }
    FORCE_INLINE uint32_t read_dev_all_in_EP_ITt() { return ((m_regs->device.DAINT & m_regs->device.DAINTMSK) & 0x0000ffff); }
    FORCE_INLINE uint32_t read_dev_in_EP_IT(uint8_t ep_num) { return (m_regs->in_eps[ep_num].DIEPINT &
                                                                ((((m_regs->device.DIEPEMPMSK >> ep_num) & 1) << 7) |
                                                                 m_regs->device.DIEPMSK)); }
    FORCE_INLINE void clear_IT(uint32_t interrupts) { m_regs->global.GINTSTS |= interrupts; }

    uint32_t core_reset();
    FORCE_INLINE bool is_master_idle() { return ((m_regs->global.GRSTCTL & USB_OTG_GRSTCTL_AHBIDL) == USB_OTG_GRSTCTL_AHBIDL); }
    FORCE_INLINE void core_soft_reset() { m_regs->global.GRSTCTL |= USB_OTG_GRSTCTL_CSRST; }
    FORCE_INLINE bool is_core_reseted() { return ((m_regs->global.GRSTCTL & USB_OTG_GRSTCTL_CSRST) != USB_OTG_GRSTCTL_CSRST); }

    void host_init(EOTGSpeed speed, uint32_t host_channels, bool dma_enable);
    ENDIS_REG_FLAG_NAME_SL(FS_LS_only, m_regs->host.HCFG, USB_OTG_HCFG_FSLSS)
    FORCE_INLINE void set_RX_FIFO_size(uint32_t size) { m_regs->global.GRXFSIZ = size; }
    FORCE_INLINE void set_RX_EP0_FIFO_size(uint32_t s0, uint32_t size) { m_regs->global.DIEPTXF0_HNPTXFSIZ = (((s0 << USB_OTG_NPTXFD_Pos) & USB_OTG_NPTXFD) | size); }
    FORCE_INLINE void set_TX_FIFO_size(uint32_t s0, uint32_t s1) { m_regs->global.HPTXFSIZ = (((s0 << USB_OTG_HPTXFSIZ_PTXFD_Pos) & USB_OTG_HPTXFSIZ_PTXFD) | s1); }

    void init_FSLSPClk_sel(EClockSpeed freq);
    ENDIS_REG_FLAG_NAME_SL(FS_LS_clock_sel, m_regs->host.HCFG, USB_OTG_HCFG_FSLSPCS)
    FORCE_INLINE void set_FSLSPClk(uint32_t val) { m_regs->host.HFIR = val; }

    void drive_VBUS(uint8_t state);

    FORCE_INLINE EOTGSpeed get_host_speed() { return (EOTGSpeed)((m_regs->ports[0] & USB_OTG_HPRT_PSPD) >> USB_OTG_HPRT_PSPD_Pos); }

    void HC_start_Xfer(OTG_HC_t *hc, bool dma);
    FORCE_INLINE uint32_t HC_get_Xfer_size(uint8_t ch_num) { return m_regs->channels[ch_num].HCTSIZ; }
    FORCE_INLINE void HC_set_Xfer_size(uint8_t ch_num, uint32_t size, uint32_t numpkt, uint8_t PID)
        {
            m_regs->channels[ch_num].HCTSIZ = (size & USB_OTG_HCTSIZ_XFRSIZ) |
                    ((numpkt << USB_OTG_HCTSIZ_PKTCNT_Pos) & USB_OTG_HCTSIZ_PKTCNT) |
                    ((PID << USB_OTG_HCTSIZ_DPID_Pos) & USB_OTG_HCTSIZ_DPID);
        }
    FORCE_INLINE void HC_set_Xfer_DMA(uint8_t ch_num, uint32_t size) { m_regs->channels[ch_num].HCDMA = size; }
    FORCE_INLINE void enable_HC_odd_frame(uint8_t ch_num) { m_regs->channels[ch_num].HCCHAR |= USB_OTG_HCCHAR_ODDFRM; }
    FORCE_INLINE void disable_HC_odd_frame(uint8_t ch_num) { m_regs->channels[ch_num].HCCHAR &= ~USB_OTG_HCCHAR_ODDFRM; }
    FORCE_INLINE uint16_t get_TX_NP_FIFO_size() { return m_regs->global.HNPTXSTS & 0xffff; }
    FORCE_INLINE uint16_t get_TX_NP_FIFO_hi_size() { return m_regs->global.HNPTXSTS & 0xff0000; }
    FORCE_INLINE uint16_t get_TX_P_FIFO_size() { return m_regs->host.HPTXSTS & 0xffff; }

    FORCE_INLINE uint32_t HC_read_IT() { return m_regs->host.HAINT & 0xffff; }

    void do_ping(uint8_t ch_num);
    FORCE_INLINE void do_ping_LL(uint8_t ch_num)
        {
            m_regs->channels[ch_num].HCTSIZ = ((1 << USB_OTG_HCTSIZ_PKTCNT_Pos) & USB_OTG_HCTSIZ_PKTCNT) |
                    USB_OTG_HCTSIZ_DOPING;
        }
    void stop_host();

        FORCE_INLINE void HC_reactivate(uint8_t ch_num)
        {
            uint32_t tmp = HC_get_params(ch_num);
            tmp &= ~USB_OTG_HCCHAR_CHDIS;
            tmp |= USB_OTG_HCCHAR_CHENA;
            HC_set_param_RAW(ch_num, tmp);
        }

    void port_IRQ_handler();
    void HC_in_IRQ_handler(uint8_t chnum);
    void HC_out_IRQ_handler(uint8_t chnum);
    void RXQLVL_IRQ_handler();
};

void connect_callback(STM32_HCD *hcd);
void disconnect_callback(STM32_HCD *hcd);
void SOF_callback(STM32_HCD *hcd);
void HC_notify_URB_change_callback(STM32_HCD *hcd, uint8_t ch_num, EURBState urb_state);

#ifdef STM32_USE_USB_FS
extern STM32_HCD usb_fs;
#endif

#ifdef STM32_USE_USB_HS
extern STM32_HCD usb_hs;
#endif

#endif
