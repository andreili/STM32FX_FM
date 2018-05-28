#include "stm32_hcd.h"

uint32_t STM32_HCD::init(USB_OTG_GlobalTypeDef* regs_addr, EOTG_PHY phy, bool use_ext_vbus, bool dma_enable,
                         EOTGSpeed speed, uint32_t host_channels)
{
    m_state = EHCDState::BUSY;
    m_regs = (OTGRegs_t*)regs_addr;
    m_dma_enable = dma_enable;
    m_host_channels = host_channels;
    m_phy = phy;
    m_speed = speed;

    init_gpio();
    disable();
    if (core_init(phy, use_ext_vbus, dma_enable) != STM32_RESULT_OK)
        return STM32_RESULT_FAIL;
    set_current_mode(EOTGDeviceMode::HOST);
    host_init(speed, host_channels, dma_enable);
    m_state = EHCDState::READY;
    return STM32_RESULT_OK;
}

void STM32_HCD::deInit()
{
    m_state = EHCDState::BUSY;
    deInit_gpio();
    disable();
    m_state = EHCDState::RESET_;
}

void STM32_HCD::set_toggle(uint8_t pipe, uint8_t toggle)
{
    if (m_HC[pipe].ep_is_in)
        m_HC[pipe].toggle_in = toggle;
    else
        m_HC[pipe].toggle_out = toggle;
}

uint8_t STM32_HCD::get_toggle(uint8_t pipe)
{
    if (m_HC[pipe].ep_is_in)
        return m_HC[pipe].toggle_in;
    else
        return m_HC[pipe].toggle_out;
}

void STM32_HCD::reset_port()
{
    uint32_t val = m_regs->ports[0];
    val &= ~(USB_OTG_HPRT_PENA | USB_OTG_HPRT_PCDET | USB_OTG_HPRT_PENCHNG | USB_OTG_HPRT_POCCHNG);
    reset_port_st1(USB_OTG_HPRT_PRST | val);
    STM32_SYSTICK::delay(10);
    reset_port_st1((~USB_OTG_HPRT_PRST) & val);
}

uint32_t STM32_HCD::start()
{
    STM32_LOCK(m_lock);
    drive_VBUS(SET);
    STM32_UNLOCK(m_lock);
    return STM32_RESULT_OK;
}

uint32_t STM32_HCD::stop()
{
    STM32_LOCK(m_lock);
    stop_host();
    STM32_UNLOCK(m_lock);
    return STM32_RESULT_OK;
}

uint32_t STM32_HCD::HC_init(uint8_t ch_num, uint8_t ep_num, uint8_t dev_address, EOTGSpeed speed, EEPType ep_type, uint16_t mps)
{
    STM32_LOCK(m_lock);

    bool is_in = ((ep_num & 0x80) == 0x80);
    ep_num = ep_num & 0x7f;

    m_HC[ch_num].dev_addr = dev_address;
    m_HC[ch_num].max_packet = mps;
    m_HC[ch_num].ch_num = ch_num;
    m_HC[ch_num].ep_type = ep_type;
    m_HC[ch_num].ep_num = ep_num;
    m_HC[ch_num].ep_is_in = is_in;
    m_HC[ch_num].speed = speed;

    clear_HC_int(ch_num, 0xffffffff);
    switch (ep_type)
    {
    case EEPType::CTRL:
    case EEPType::BULK:
        set_HC_int(ch_num, USB_OTG_HCINTMSK_XFRCM  |
                   USB_OTG_HCINTMSK_STALLM |
                   USB_OTG_HCINTMSK_TXERRM |
                   USB_OTG_HCINTMSK_DTERRM |
                   USB_OTG_HCINTMSK_AHBERR |
                   USB_OTG_HCINTMSK_NAKM);
        if (ep_num & 0x80)
            unmask_HC_int(ch_num, USB_OTG_HCINTMSK_BBERRM);
        else if (m_regs != (OTGRegs_t*)USB_OTG_FS)
            unmask_HC_int(ch_num, USB_OTG_HCINTMSK_NYET | USB_OTG_HCINTMSK_ACKM);
        break;
    case EEPType::INTR:
        set_HC_int(ch_num, USB_OTG_HCINTMSK_XFRCM  |
                   USB_OTG_HCINTMSK_STALLM |
                   USB_OTG_HCINTMSK_TXERRM |
                   USB_OTG_HCINTMSK_DTERRM |
                   USB_OTG_HCINTMSK_NAKM   |
                   USB_OTG_HCINTMSK_AHBERR |
                   USB_OTG_HCINTMSK_FRMORM);
        if (ep_num & 0x80)
            unmask_HC_int(ch_num, USB_OTG_HCINTMSK_BBERRM);
        break;
    case EEPType::ISOC:
        set_HC_int(ch_num, USB_OTG_HCINTMSK_XFRCM  |
                   USB_OTG_HCINTMSK_ACKM   |
                   USB_OTG_HCINTMSK_AHBERR |
                   USB_OTG_HCINTMSK_FRMORM);
        if (ep_num & 0x80)
            unmask_HC_int(ch_num, USB_OTG_HCINTMSK_TXERRM | USB_OTG_HCINTMSK_BBERRM);
        break;
    case EEPType::MSK:
        break;
    }
    enable_host_IT(ch_num);
    enable_IT(USB_OTG_GINTMSK_HCIM);
    HC_set_params(ch_num, ep_num, dev_address, speed, ep_type, mps);
    if (ep_type == EEPType::INTR)
        HC_enable_param(ch_num, USB_OTG_HCCHAR_ODDFRM);

    STM32_UNLOCK(m_lock);
    return STM32_RESULT_OK;
}

void STM32_HCD::HC_submit_request(uint8_t ch_num, bool is_in, EEPType ep_type, bool token, uint8_t* pbuff, uint16_t length, bool do_ping)
{
    m_HC[ch_num].ep_is_in = is_in;
    m_HC[ch_num].ep_type = ep_type;

    if (!token)
        m_HC[ch_num].data_pid = HC_PID_SETUP;
    else
        m_HC[ch_num].data_pid = HC_PID_DATA1;

    switch (ep_type)
    {
    case EEPType::CTRL:
        if (token && (!is_in)) /*send data */
        {
            if (length == 0)
                m_HC[ch_num].toggle_out = true;
            if (!m_HC[ch_num].toggle_out)
                m_HC[ch_num].data_pid = HC_PID_DATA0;
            else
                m_HC[ch_num].data_pid = HC_PID_DATA1;
            if (m_HC[ch_num].urb_state != EURBState::NOT_READY)
                m_HC[ch_num].do_ping = do_ping;
        }
        break;
    case EEPType::BULK:
        if (!is_in)
        {
            if (!m_HC[ch_num].toggle_out)
                m_HC[ch_num].data_pid = HC_PID_DATA0;
            else
                m_HC[ch_num].data_pid = HC_PID_DATA1;
            if (m_HC[ch_num].urb_state != EURBState::NOT_READY)
                m_HC[ch_num].do_ping = do_ping;
        }
        else
        {
            if (!m_HC[ch_num].toggle_in)
                m_HC[ch_num].data_pid = HC_PID_DATA0;
            else
                m_HC[ch_num].data_pid = HC_PID_DATA1;
        }
        break;
    case EEPType::INTR:
        if (!is_in)
        {
            if (!m_HC[ch_num].toggle_out)
                m_HC[ch_num].data_pid = HC_PID_DATA0;
            else
                m_HC[ch_num].data_pid = HC_PID_DATA1;
        }
        else
        {
            if (!m_HC[ch_num].toggle_in)
                m_HC[ch_num].data_pid = HC_PID_DATA0;
            else
                m_HC[ch_num].data_pid = HC_PID_DATA1;
        }
        break;
    case EEPType::ISOC:
        m_HC[ch_num].data_pid = HC_PID_DATA0;
        break;
    case EEPType::MSK:
        break;
    }

    m_HC[ch_num].xfer_buff = pbuff;
    m_HC[ch_num].xfer_len = length;
    m_HC[ch_num].urb_state = EURBState::IDLE;
    m_HC[ch_num].xfer_count = 0;
    m_HC[ch_num].ch_num = ch_num;
    m_HC[ch_num].state = EHCState::IDLE;
    HC_start_Xfer(&m_HC[ch_num], m_dma_enable);
}

uint32_t STM32_HCD::HC_halt(uint8_t hc_num)
{
    STM32_LOCK(m_lock);

    uint32_t FIFO_queue = 0;
    if (((HC_get_params(hc_num) & USB_OTG_HCCHAR_EPTYP) == HCCHAR_CTRL) ||
        ((HC_get_params(hc_num) & USB_OTG_HCCHAR_EPTYP) == HCCHAR_BULK))
        FIFO_queue = get_TX_NP_FIFO_hi_size();
    else
        FIFO_queue = get_TX_P_FIFO_size();

    HC_enable_param(hc_num, USB_OTG_HCCHAR_CHDIS);
    if (FIFO_queue == 0)
    {
        HC_disable_param(hc_num, USB_OTG_HCCHAR_CHENA);
        HC_enable_param(hc_num, USB_OTG_HCCHAR_CHENA);
        uint32_t count = 0;
        do
        {
            if (++count > 1000)
                break;
        } while ((HC_get_params(hc_num) & USB_OTG_HCCHAR_CHENA) == USB_OTG_HCCHAR_CHENA);
    }
    else
        HC_enable_param(hc_num, USB_OTG_HCCHAR_CHENA);

    STM32_UNLOCK(m_lock);
    return STM32_RESULT_OK;
}

void STM32_HCD::IRQ_handler()
{
    GPIOD->BSRR = GPIO_BSRR_BS15;
    if (get_mode() == EOTGDeviceMode::HOST)
    {
        if (is_invalid_IT())
            return;

        if (get_flag(USB_OTG_GINTSTS_PXFR_INCOMPISOOUT))
            clear_flag(USB_OTG_GINTSTS_PXFR_INCOMPISOOUT);
        if (get_flag(USB_OTG_GINTSTS_IISOIXFR))
            clear_flag(USB_OTG_GINTSTS_IISOIXFR);
        if (get_flag(USB_OTG_GINTSTS_PTXFE))
            clear_flag(USB_OTG_GINTSTS_PTXFE);
        if (get_flag(USB_OTG_GINTSTS_MMIS))
            clear_flag(USB_OTG_GINTSTS_MMIS);
        if (get_flag(USB_OTG_GINTSTS_DISCINT))
        {
            m_regs->ports[0] &= ~(USB_OTG_HPRT_PENA | USB_OTG_HPRT_PCDET | USB_OTG_HPRT_PENCHNG | USB_OTG_HPRT_POCCHNG);
            disconnect_callback(this);
            init_FSLSPClk_sel(EClockSpeed::_48_MHZ);
            clear_flag(USB_OTG_GINTSTS_DISCINT);
        }
        if (get_flag(USB_OTG_GINTSTS_HPRTINT))
            port_IRQ_handler();
        if (get_flag(USB_OTG_GINTSTS_SOF))
        {
            SOF_callback(this);
            clear_flag(USB_OTG_GINTSTS_SOF);
        }
        if (get_flag(USB_OTG_GINTSTS_HCINT))
        {
            uint32_t it = HC_read_IT();
            for (uint32_t i=0 ; i<m_host_channels ; ++i)
            {
                if (it & (1 << i))
                {
                    if (HC_get_dir(i))
                        HC_in_IRQ_handler(i);
                    else
                        HC_out_IRQ_handler(i);
                }
            }
            clear_flag(USB_OTG_GINTSTS_HCINT);
        }
        if (get_flag(USB_OTG_GINTSTS_RXFLVL))
        {
            mask_IT(USB_OTG_GINTSTS_RXFLVL);
            RXQLVL_IRQ_handler();
            unmask_IT(USB_OTG_GINTSTS_RXFLVL);
        }
    }
}

void STM32_HCD::init_gpio()
{
    if (m_regs == (OTGRegs_t*)USB_OTG_FS)
    {
        STM32_USB_FS_PORT.set_config(STM32_USB_FS_DM_PIN | STM32_USB_FS_DP_PIN, GPIO_MODE_AF_PP,
                                     GPIO_AF10_OTG_FS, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_NOPULL);
        STM32_RCC::STM32_USB_FS_EN_CLK();
        STM32_RCC::enable_clk_USB_FS();
        STM32_NVIC::enable_and_set_prior_IRQ(OTG_FS_IRQn, 5, 0);
    }
    else
    {
        STM32_USB_HS_PORT.set_config(STM32_USB_HS_DM_PIN | STM32_USB_HS_DP_PIN, GPIO_MODE_AF_PP,
                                     GPIO_AF10_OTG_HS, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_NOPULL);
        STM32_RCC::STM32_USB_HS_EN_CLK();
        STM32_RCC::enable_clk_USB_HS();
        STM32_NVIC::enable_and_set_prior_IRQ(OTG_HS_IRQn, 5, 0);
    }
}

void STM32_HCD::deInit_gpio()
{
    if (m_regs == (OTGRegs_t*)USB_OTG_FS)
    {
        STM32_RCC::disable_clk_OTGFS();
        STM32_USB_FS_PORT.unset_config(STM32_USB_FS_DM_PIN | STM32_USB_FS_DP_PIN);
        STM32_NVIC::disable_IRQ(OTG_FS_IRQn);
    }
    else
    {
        STM32_RCC::disable_clk_OTGHS();
        STM32_USB_HS_PORT.unset_config(STM32_USB_HS_DM_PIN | STM32_USB_HS_DP_PIN);
        STM32_NVIC::disable_IRQ(OTG_HS_IRQn);
    }
}

uint32_t STM32_HCD::core_init(EOTG_PHY phy, bool use_ext_vbus, bool dma_enable)
{
    if (phy == EOTG_PHY::ULPI)
    {
        power_down();
        init_phy_ULPI();
        reset_ULPI_VBUS();
        if (use_ext_vbus)
            set_ULPI_VBUS();
        if (core_reset() != STM32_RESULT_OK)
            return STM32_RESULT_FAIL;
    }
    else
    {
        init_phy_embedded();
        if (core_reset() != STM32_RESULT_OK)
            return STM32_RESULT_FAIL;
        power_up();
    }
    if (dma_enable)
        enable_DMA();
    return STM32_RESULT_OK;
}

void STM32_HCD::dev_init(bool vbus_sending_enable, EOTG_PHY phy, EOTGSpeed speed, uint32_t ep_count,
                         bool dma_enable, bool sof_enable)
{
    if (!vbus_sending_enable)
        disable_VBUS();
    else
        enable_VBUS_B();
    restart_phy_clock();
    mode_device_configuration();
    if (phy == EOTG_PHY::ULPI)
    {
        if (speed == EOTGSpeed::HIGH)
            set_dev_speed(EOTGSpeed::HIGH);
        else
            set_dev_speed(EOTGSpeed::HIGH_IN_FULL);
    }
    else
        set_dev_speed(EOTGSpeed::FULL);
    flush_TX_FIFO(TX_FIFO_COUNT);
    flush_RX_FIFO();
    clear_all_ITs();
    for (uint32_t i=0 ; i<ep_count ; ++i)
    {
        if (is_in_endpoint_enable(i))
            disable_NAK_in_endpoint(i);
        else
            disable_in_endpoint(i);
        in_endpoint_reset_Xfer_size(i);
        in_endpoint_reset_IT(i);
    }
    for (uint32_t i=0 ; i<ep_count ; ++i)
    {
        if (is_out_endpoint_enable(i))
            disable_NAK_out_endpoint(i);
        else
            disable_out_endpoint(i);
        out_endpoint_reset_Xfer_size(i);
        out_endpoint_reset_IT(i);
    }

    reset_FIFO_underrun_flag();

    if (dma_enable)
        set_DMA_thresshold();

    disable_all_IT();
    clear_all_IT();

    if (dma_enable)
        enable_IT(USB_OTG_GINTMSK_RXFLVLM);

    enable_IT(USB_OTG_GINTMSK_USBSUSPM | USB_OTG_GINTMSK_USBRST |
              USB_OTG_GINTMSK_ENUMDNEM | USB_OTG_GINTMSK_IEPINT |
              USB_OTG_GINTMSK_OEPINT   | USB_OTG_GINTMSK_IISOIXFRM|
              USB_OTG_GINTMSK_PXFRM_IISOOXFRM | USB_OTG_GINTMSK_WUIM);

    if (sof_enable)
        enable_IT(USB_OTG_GINTMSK_SOFM);

    if (vbus_sending_enable)
        enable_IT(USB_OTG_GINTMSK_SRQIM | USB_OTG_GINTMSK_OTGINT);
}

void STM32_HCD::set_current_mode(EOTGDeviceMode mode)
{
    reset_mode();
    if (mode == EOTGDeviceMode::HOST)
        set_mode_host();
    else if (mode == EOTGDeviceMode::DEVICE)
        set_mode_device();
    STM32_SYSTICK::delay(500);
}

EOTGSpeed STM32_HCD::get_dev_speed()
{
    uint32_t speed = get_dev_speed_RAW();
    switch (speed)
    {
    case DSTS_ENUMSPD_HS_PHY_30MHZ_OR_60MHZ:
        return EOTGSpeed::HIGH;
    case DSTS_ENUMSPD_FS_PHY_30MHZ_OR_60MHZ:
    case DSTS_ENUMSPD_FS_PHY_48MHZ:
        return EOTGSpeed::FULL;
    case DSTS_ENUMSPD_LS_PHY_6MHZ:
    default:
        return EOTGSpeed::LOW;
    }
}

uint32_t STM32_HCD::flush_RX_FIFO()
{
    m_regs->global.GRSTCTL = USB_OTG_GRSTCTL_RXFFLSH;
    uint32_t count = 0;
    do
    {
        if (++count > 200*1000)
            return STM32_RESULT_TIMEOUT;
    } while ((m_regs->global.GRSTCTL & USB_OTG_GRSTCTL_RXFFLSH) == USB_OTG_GRSTCTL_RXFFLSH);
    return STM32_RESULT_OK;
}

uint32_t STM32_HCD::flush_TX_FIFO(uint32_t num)
{
    m_regs->global.GRSTCTL = USB_OTG_GRSTCTL_TXFFLSH | (num << USB_OTG_GRSTCTL_TXFNUM_Pos);
    uint32_t count = 0;
    do
    {
        if (++count > 200*1000)
            return STM32_RESULT_TIMEOUT;
    } while ((m_regs->global.GRSTCTL & USB_OTG_GRSTCTL_TXFFLSH) == USB_OTG_GRSTCTL_TXFFLSH);
    return STM32_RESULT_OK;
}

void STM32_HCD::activate_endpoint(bool ep_is_in, uint8_t ep_num, uint32_t ep_maxpacket, uint8_t ep_type)
{
    if (ep_is_in)
    {
        set_ep_IT_mask(USB_OTG_DAINTMSK_IEPM & (1 << ep_num));
        if (!is_ep_in_active(ep_num))
            activate_ep_in(ep_num, ep_maxpacket, ep_type);
    }
    else
    {
        set_ep_IT_mask(USB_OTG_DAINTMSK_OEPM & ((1 << ep_num) << USB_OTG_DAINTMSK_OEPM_Pos));
        if (!is_ep_out_active(ep_num))
            activate_ep_out(0, ep_maxpacket, ep_type);
    }
}

uint32_t STM32_HCD::deactivate_endpoint(bool ep_is_in, uint8_t ep_num)
{
    if (ep_is_in)
    {
        deactivate_ep_in(ep_num);
        set_NAK_ep_in(ep_num);
        disable_ep_in(ep_num);
        uint32_t count = 0;
        do
        {
            if (++count > 200*1000)
                return STM32_RESULT_TIMEOUT;
        } while (!is_ep_in_disabled(ep_num));

        flush_TX_FIFO(TX_FIFO_COUNT);
        clear_ep_IT_mask(USB_OTG_DAINTMSK_IEPM & (1 << ep_num));
    }
    else
    {
        deactivate_ep_out(ep_num);
        set_NAK_ep_out(ep_num);
        disable_ep_out(ep_num);
        uint32_t count = 0;
        do
        {
            if (++count > 200*1000)
                return STM32_RESULT_TIMEOUT;
        } while (!is_ep_out_disabled(ep_num));

        clear_global_NAK();
        clear_ep_IT_mask(USB_OTG_DAINTMSK_OEPM & ((1 << ep_num) << USB_OTG_DAINTMSK_OEPM_Pos));
    }
    return STM32_RESULT_OK;
}

void STM32_HCD::activate_dedicated_endpoint(bool ep_is_in, uint8_t ep_num, uint32_t ep_maxpacket, uint8_t ep_type)
{
    if (ep_is_in)
    {
        if (!is_ep_in_active(ep_num))
            activate_ep_in(ep_num, ep_maxpacket, ep_type);
        set_ded_ep_IT_mask(USB_OTG_DAINTMSK_IEPM & (1 << ep_num));
    }
    else
    {
        if (!is_ep_out_active(ep_num))
            activate_ep_out(ep_num, ep_maxpacket, ep_type);
        set_ded_ep_IT_mask(USB_OTG_DAINTMSK_OEPM & ((1 << ep_num) << USB_OTG_DAINTMSK_OEPM_Pos));
    }
}

void STM32_HCD::EP_start_Xfer(bool ep_is_in, uint8_t ep_num, uint32_t ep_maxpacket,
                              uint8_t* xfer_buff, uint16_t xfer_len, EEPType ep_type,
                              bool dma, uint32_t dma_addr)
{
    if (ep_is_in)
    {
        if (xfer_len == 0)
        {
            Xfer_in_pkt_start(ep_num);
            Xfer_in_pkt_size(ep_num, 1);
        }
        else
        {
            Xfer_in_pkt_start(ep_num);
            Xfer_in_pkt_size(ep_num, (xfer_len + ep_maxpacket - 1) / ep_maxpacket);
            Xfer_in_pkt_end(ep_num, xfer_len);

            if (ep_type == EEPType::ISOC)
                Xfer_in_pkt_multi(ep_num);
        }
        if (dma)
            Xfer_in_enable_DMA(ep_num, dma_addr);
        else if ((ep_type != EEPType::ISOC) && (xfer_len > 0))
            set_dev_empty_mask(ep_num);
        if (ep_type == EEPType::ISOC)
        {
            if (is_frame_odd())
                Xfer_in_set_odd_frame(ep_num);
            else
                Xfer_in_set_data0_pid(ep_num);
        }
        Xfer_in_ep_enable(ep_num);
        if (ep_type == EEPType::ISOC)
            write_packet(xfer_buff, ep_num, xfer_len, dma);
    }
    else
    {
        Xfer_out_pkt_start(ep_num);
        if (xfer_len == 0)
        {
            Xfer_out_pkt_size(ep_num, 1);
            Xfer_out_pkt_end(ep_num, ep_maxpacket);
        }
        else
        {
            uint16_t pkt_cnt = (xfer_len + ep_maxpacket - 1) / ep_maxpacket;
            Xfer_out_pkt_size(ep_num, pkt_cnt);
            Xfer_out_pkt_end(ep_num, ep_maxpacket * pkt_cnt);
        }
        if (dma)
            Xfer_out_enable_DMA(ep_num, (uint32_t)xfer_buff);
        if (ep_type == EEPType::ISOC)
        {
            if (is_frame_odd())
                Xfer_out_set_odd_frame(ep_num);
            else
                Xfer_out_set_data0_pid(ep_num);
        }
        Xfer_out_ep_enable(ep_num);
    }
}

void STM32_HCD::EP0_start_Xfer(bool ep_is_in, uint8_t ep_num, uint32_t ep_maxpacket,
                               uint8_t* xfer_buff, uint16_t xfer_len, bool dma, uint32_t dma_addr)
{
    if (ep_is_in)
    {
        if (xfer_len == 0)
        {
            Xfer_in_pkt_start(ep_num);
            Xfer_in_pkt_size(ep_num, 1);
        }
        else
        {
            Xfer_in_pkt_start(ep_num);
            if (xfer_len > ep_maxpacket)
                xfer_len = ep_maxpacket;
            Xfer_in_pkt_size(ep_num, 1);
            Xfer_in_pkt_end(ep_num, xfer_len);
        }
        Xfer_in_ep_enable(ep_num);
        if (dma)
            Xfer_in_enable_DMA(ep_num, dma_addr);
        else if (xfer_len > 0)
            set_dev_empty_mask(ep_num);
    }
    else
    {
        Xfer_out_pkt_start(ep_num);
        if (xfer_len > 0)
            xfer_len = ep_maxpacket;

        Xfer_out_pkt_size(ep_num, 1);
        Xfer_out_pkt_end(ep_num, ep_maxpacket);
        if (dma)
            Xfer_out_enable_DMA(ep_num, (uint32_t)xfer_buff);
        Xfer_out_ep_enable(ep_num);
    }
}

void STM32_HCD::write_packet(uint8_t* src, uint8_t ch_ep_num, uint16_t len, uint8_t dma)
{
    if (!dma)
    {
        uint32_t count32b = (len + 3) >> 2;
        for (uint32_t i=0 ; i<count32b ; ++i, src+=4)
            write_FIFO(ch_ep_num, *((__attribute__((__packed__))uint32_t *)src));
    }
}

void* STM32_HCD::read_packet(uint8_t* dest, uint16_t len)
{
    uint32_t count32b = (len + 3) >> 2;
    for (uint32_t i=0 ; i<count32b ; ++i, dest+=4)
        *((__attribute__((__packed__))uint32_t *)dest) = read_FIFO(0);
    return (void*)dest;
}

void STM32_HCD::EP_set_stall(bool ep_is_in, uint8_t ep_num)
{
    if (ep_is_in)
    {
        if (!is_in_endpoint_enable(ep_num))
            undisable_ep_in(ep_num);
        ep_in_set_stall(ep_num);
    }
    else
    {
        if (!is_out_endpoint_enable(ep_num))
            undisable_ep_out(ep_num);
        ep_out_set_stall(ep_num);
    }
}

void STM32_HCD::EP_clear_stall(bool ep_is_in, uint8_t ep_num, EEPType ep_type)
{
    if (ep_is_in)
    {
        ep_in_clear_stall(ep_num);
        if ((ep_type == EEPType::INTR) || (ep_type == EEPType::BULK))
            Xfer_in_set_data0_pid(ep_num);
    }
    else
    {
        ep_out_clear_stall(ep_num);
        if ((ep_type == EEPType::INTR) || (ep_type == EEPType::BULK))
            Xfer_out_set_data0_pid(ep_num);
    }
}

void STM32_HCD::set_dev_address(uint8_t address)
{
    clear_dev_address();
    set_dev_addr_RAW(address);
}

void STM32_HCD::stop_device()
{
    for (int i=0 ; i<15 ; ++i)
    {
        clear_in_ep_intr(i, 0xff);
        clear_out_ep_intr(i, 0xff);
    }
    //clear_shared_IT();
    clear_all_ITs();
    flush_RX_FIFO();
    flush_TX_FIFO(0x10);
}

void STM32_HCD::activate_setup()
{
    reset_max_pkt_size();
    if (get_dev_speed_RAW() == DSTS_ENUMSPD_LS_PHY_6MHZ)
        set_in_max_pkt_size(3);
    clear_in_global_NAK();
}

void STM32_HCD::EP0_out_start(uint8_t dma, uint8_t* psetup)
{
    out_endpoint_reset_Xfer_size(0);
    Xfer_out_pkt_size(0, 1);
    Xfer_out_pkt_end(0, 3*8);
    ep_out_setup_packet_count();
    if (dma)
    {
        Xfer_out_enable_DMA(0, (uint32_t)psetup);
        ep_out_start_enable();
    }
}

uint32_t STM32_HCD::core_reset()
{
    uint32_t count = 0;
    do
    {
        if (++count > 200*1000)
            return STM32_RESULT_TIMEOUT;
    } while (!is_master_idle());
    core_soft_reset();
    count = 0;
    do
    {
        if (++count > 200*1000)
            return STM32_RESULT_TIMEOUT;
    } while (!is_core_reseted());
    return STM32_RESULT_OK;
}

void STM32_HCD::host_init(EOTGSpeed speed, uint32_t host_channels, bool dma_enable)
{
    restart_phy_clock();
    /* Activate VBUS Sensing B */
    disable_VBUS_A();
    disable_VBUS_B();
    enable_VBUS();

    /* Disable the FS/LS support mode only */
    if ((speed == EOTGSpeed::FULL) && (m_regs != (OTGRegs_t*)USB_OTG_FS))
        enable_FS_LS_only();
    else
        disable_FS_LS_only();
    flush_TX_FIFO(0x10);
    flush_RX_FIFO();
    for (uint32_t i=0 ; i<host_channels ; ++i)
    {
        clear_HC_int(i, 0xffffffff);
        mask_all_HC_int(i);
    }
    drive_VBUS(SET);
    STM32_SYSTICK::delay(200);
    disable_all_IT();
    clear_all_IT1();
    if (m_regs == (OTGRegs_t*)USB_OTG_FS)
    {
        set_RX_FIFO_size(0x80);
        set_RX_EP0_FIFO_size(0x60, 0x80);
        set_TX_FIFO_size(0x40, 0xe0);
    }
    else
    {
        set_RX_FIFO_size(0x200);
        set_RX_EP0_FIFO_size(0x100, 0x200);
        set_TX_FIFO_size(0xe0, 0x300);
    }
    if (dma_enable)
        unmask_IT(USB_OTG_GINTMSK_RXFLVLM);
    unmask_IT(USB_OTG_GINTMSK_PRTIM            | USB_OTG_GINTMSK_HCIM |
              USB_OTG_GINTMSK_SOFM             |USB_OTG_GINTSTS_DISCINT|
              USB_OTG_GINTMSK_PXFRM_IISOOXFRM  | USB_OTG_GINTMSK_WUIM);
}

void STM32_HCD::init_FSLSPClk_sel(EClockSpeed freq)
{
    disable_FS_LS_clock_sel();
    enable_FS_LS_clock_sel();
    switch (freq)
    {
    case EClockSpeed::_30_60_MHZ:
        break;
    case EClockSpeed::_48_MHZ:
        set_FSLSPClk(48*1000);
        break;
    case EClockSpeed::_6_MHZ:
        set_FSLSPClk(6*1000);
        break;
    }
}

#pragma GCC optimize ("O0")
void STM32_HCD::HC_start_Xfer(OTG_HC_t* hc, bool dma)
{
    if ((m_regs != (OTGRegs_t*)USB_OTG_FS) && (hc->speed == EOTGSpeed::HIGH))
    {
        if ((!dma) && hc->do_ping)
        {
            do_ping(hc->ch_num);
            return;
        }
        else if (dma)
        {
            mask_HC_int(hc->ch_num, USB_OTG_HCINTMSK_NYET | USB_OTG_HCINTMSK_ACKM);
            hc->do_ping = false;
        }
    }

    uint16_t numpackets;
    if (hc->xfer_len > 0)
    {
        numpackets = (hc->xfer_len + hc->max_packet - 1) / hc->max_packet;
        if (numpackets > 256)
        {
            numpackets = 256;
            hc->xfer_len = numpackets * hc->max_packet;
        }
    }
    else
        numpackets = 1;

    if (hc->ep_is_in)
        hc->xfer_len = numpackets * hc->max_packet;

    HC_set_Xfer_size(hc->ch_num, hc->xfer_len, numpackets, hc->data_pid);

    if (dma)
        HC_set_Xfer_DMA(hc->ch_num, hc->xfer_len);

    disable_HC_odd_frame(hc->ch_num);
    if (get_current_frame() & 0x01)
        enable_HC_odd_frame(hc->ch_num);

    HC_reactivate(hc->ch_num);

    if (!dma)
    {
        if ((!hc->ep_is_in) && (hc->xfer_len > 0))
        {
            switch (hc->ep_type)
            {
            case EEPType::CTRL:
            case EEPType::BULK:
                {
                    uint16_t len_w = (hc->xfer_len + 3) / 4;
                    if (len_w > get_TX_NP_FIFO_size())
                        /* need to process data in nptxfempty interrupt */
                        unmask_IT(USB_OTG_GINTMSK_NPTXFEM);
                }
                break;
            case EEPType::INTR:
            case EEPType::ISOC:
                {
                    uint16_t len_w = (hc->xfer_len + 3) / 4;
                    if (len_w > get_TX_P_FIFO_size())
                        /* need to process data in nptxfempty interrupt */
                        unmask_IT(USB_OTG_GINTMSK_PTXFEM);
                }
                break;
            case EEPType::MSK:
                break;
            }
            write_packet(hc->xfer_buff, hc->ch_num, hc->xfer_len, false);
        }
    }
}

void STM32_HCD::drive_VBUS(uint8_t state)
{
    uint32_t val = m_regs->ports[0];
    val &= ~(USB_OTG_HPRT_PENA | USB_OTG_HPRT_PCDET | USB_OTG_HPRT_PENCHNG | USB_OTG_HPRT_POCCHNG);
    if (((val & USB_OTG_HPRT_PPWR) == 0) && (state == 0))
        reset_port_st1(USB_OTG_HPRT_PPWR | val);
    if (((val & USB_OTG_HPRT_PPWR) == USB_OTG_HPRT_PPWR) && (state == 1))
        reset_port_st1((~USB_OTG_HPRT_PPWR) & val);
}

void STM32_HCD::do_ping(uint8_t ch_num)
{
    do_ping_LL(ch_num);
    HC_reactivate(ch_num);
}

void STM32_HCD::stop_host()
{
    disable_global_int();
    flush_TX_FIFO(0x10);
    flush_RX_FIFO();
    /* Flush out any leftover queued requests. */
    for(int i=0 ; i<15 ; ++i)
    {
        uint32_t tmp = HC_get_params(i);
        tmp |= USB_OTG_HCCHAR_CHDIS;
        tmp &= ~(USB_OTG_HCCHAR_CHENA | USB_OTG_HCCHAR_EPDIR);
        HC_set_param_RAW(i, tmp);
    }
    /* Halt all channels to put them into a known state. */
    for(int i=0 ; i<15 ; ++i)
    {
        uint32_t tmp = HC_get_params(i);
        tmp |= USB_OTG_HCCHAR_CHDIS;
        tmp &= ~(USB_OTG_HCCHAR_CHENA | USB_OTG_HCCHAR_EPDIR);
        HC_set_param_RAW(i, tmp);
        tmp = 0;
        do
        {
            if (++tmp > 1000)
                break;
        } while ((HC_get_params(i) & USB_OTG_HCCHAR_CHENA) == USB_OTG_HCCHAR_CHENA);
    }
    /* Clear any pending Host interrupts */
    set_host_IT(0xffffffff);
    clear_all_IT1();
    enable_global_int();
}

void STM32_HCD::HC_in_IRQ_handler(uint8_t chnum)
{
    if (is_HC_int(chnum, USB_OTG_HCINT_AHBERR))
    {
        clear_HC_int(chnum, USB_OTG_HCINT_AHBERR);
        unmask_halt_HC_int(chnum);
    }
    else if (is_HC_int(chnum, USB_OTG_HCINT_ACK))
        clear_HC_int(chnum, USB_OTG_HCINT_ACK);
    else if (is_HC_int(chnum, USB_OTG_HCINT_STALL))
    {
        unmask_halt_HC_int(chnum);
        m_HC[chnum].state = EHCState::STALL;
        clear_HC_int(chnum, USB_OTG_HCINT_NAK | USB_OTG_HCINT_STALL);
        HC_halt(chnum);
    }
    else if (is_HC_int(chnum, USB_OTG_HCINT_DTERR))
    {
        unmask_halt_HC_int(chnum);
        HC_halt(chnum);
        clear_HC_int(chnum, USB_OTG_HCINT_NAK | USB_OTG_HCINT_DTERR);
        m_HC[chnum].state = EHCState::DATATGLERR;
    }
    else if (is_HC_int(chnum, USB_OTG_HCINT_FRMOR))
    {
        unmask_halt_HC_int(chnum);
        HC_halt(chnum);
        clear_HC_int(chnum, USB_OTG_HCINT_FRMOR);
    }
    else if (is_HC_int(chnum, USB_OTG_HCINT_XFRC))
    {
        if (m_dma_enable)
            m_HC[chnum].xfer_count = m_HC[chnum].xfer_len - (HC_get_Xfer_size(chnum) & USB_OTG_HCTSIZ_XFRSIZ);
        m_HC[chnum].state = EHCState::XFRC;
        m_HC[chnum].ErrCnt = 0;
        clear_HC_int(chnum, USB_OTG_HCINT_XFRC);
        if ((m_HC[chnum].ep_type == EEPType::CTRL) ||
            (m_HC[chnum].ep_type == EEPType::BULK))
        {
            unmask_halt_HC_int(chnum);
            HC_halt(chnum);
            clear_HC_int(chnum, USB_OTG_HCINT_NAK);
        }
        else if (m_HC[chnum].ep_type == EEPType::INTR)
        {
            enable_HC_odd_frame(chnum);
            m_HC[chnum].urb_state = EURBState::DONE;
            HC_notify_URB_change_callback(this, chnum, m_HC[chnum].urb_state);
        }
        m_HC[chnum].toggle_in ^= 1;
    }
    else if (is_HC_int(chnum, USB_OTG_HCINT_CHH))
    {
        mask_halt_HC_int(chnum);
        if (m_HC[chnum].state == EHCState::XFRC)
            m_HC[chnum].urb_state = EURBState::DONE;
        else if (m_HC[chnum].state == EHCState::STALL)
            m_HC[chnum].urb_state = EURBState::STALL;
        else if ((m_HC[chnum].state == EHCState::XACTERR) ||
                 (m_HC[chnum].state == EHCState::DATATGLERR))
        {
            if (m_HC[chnum].ErrCnt++ > 3)
            {
                m_HC[chnum].ErrCnt = 0;
                m_HC[chnum].urb_state = EURBState::ERROR;
            }
            else
                m_HC[chnum].urb_state = EURBState::NOT_READY;
            HC_reactivate(chnum);
        }
        clear_HC_int(chnum, USB_OTG_HCINT_CHH);
        HC_notify_URB_change_callback(this, chnum, m_HC[chnum].urb_state);
    }
    else if (is_HC_int(chnum, USB_OTG_HCINT_TXERR))
    {
        unmask_halt_HC_int(chnum);
        ++m_HC[chnum].ErrCnt;
        m_HC[chnum].state = EHCState::XACTERR;
        HC_halt(chnum);
        clear_HC_int(chnum, USB_OTG_HCINT_TXERR);
    }
    else if (is_HC_int(chnum, USB_OTG_HCINT_NAK))
    {
        if (m_HC[chnum].ep_type == EEPType::INTR)
        {
            unmask_halt_HC_int(chnum);
            HC_halt(chnum);
        }
        m_HC[chnum].state = EHCState::NAK;
        clear_HC_int(chnum, USB_OTG_HCINT_NAK);
        if ((m_HC[chnum].ep_type == EEPType::CTRL) ||
            (m_HC[chnum].ep_type == EEPType::BULK))
            HC_reactivate(chnum);
    }
}

void STM32_HCD::HC_out_IRQ_handler(uint8_t chnum)
{
    if (is_HC_int(chnum, USB_OTG_HCINT_AHBERR))
    {
        clear_HC_int(chnum, USB_OTG_HCINT_AHBERR);
        unmask_halt_HC_int(chnum);
    }
    else if (is_HC_int(chnum, USB_OTG_HCINT_ACK))
    {
        clear_HC_int(chnum, USB_OTG_HCINT_ACK);
        if (m_HC[chnum].do_ping)
        {
            m_HC[chnum].state = EHCState::NYET;
            unmask_halt_HC_int(chnum);
            HC_halt(chnum);
            m_HC[chnum].urb_state = EURBState::NOT_READY;
        }
    }
    else if (is_HC_int(chnum, USB_OTG_HCINT_NYET))
    {
        m_HC[chnum].state = EHCState::NYET;
        m_HC[chnum].ErrCnt = 0;
        unmask_halt_HC_int(chnum);
        HC_halt(chnum);
        clear_HC_int(chnum, USB_OTG_HCINT_NYET);
    }
    else if (is_HC_int(chnum, USB_OTG_HCINT_FRMOR))
    {
        unmask_halt_HC_int(chnum);
        HC_halt(chnum);
        clear_HC_int(chnum, USB_OTG_HCINT_FRMOR);
    }
    else if (is_HC_int(chnum, USB_OTG_HCINT_XFRC))
    {
        m_HC[chnum].ErrCnt = 0;
        unmask_halt_HC_int(chnum);
        HC_halt(chnum);
        clear_HC_int(chnum, USB_OTG_HCINT_XFRC);
        m_HC[chnum].state = EHCState::XFRC;
    }
    else if (is_HC_int(chnum, USB_OTG_HCINT_STALL))
    {
        clear_HC_int(chnum, USB_OTG_HCINT_STALL);
        unmask_halt_HC_int(chnum);
        HC_halt(chnum);
        m_HC[chnum].state = EHCState::STALL;
    }
    else if (is_HC_int(chnum, USB_OTG_HCINT_NAK))
    {
        m_HC[chnum].ErrCnt = 0;
        unmask_halt_HC_int(chnum);
        HC_halt(chnum);
        m_HC[chnum].state = EHCState::NAK;
        clear_HC_int(chnum, USB_OTG_HCINT_NAK);
    }
    else if (is_HC_int(chnum, USB_OTG_HCINT_TXERR))
    {
        unmask_halt_HC_int(chnum);
        HC_halt(chnum);
        m_HC[chnum].state = EHCState::XACTERR;
        clear_HC_int(chnum, USB_OTG_HCINT_TXERR);
    }
    else if (is_HC_int(chnum, USB_OTG_HCINT_DTERR))
    {
        unmask_halt_HC_int(chnum);
        HC_halt(chnum);
        m_HC[chnum].state = EHCState::DATATGLERR;
        clear_HC_int(chnum, USB_OTG_HCINT_DTERR | USB_OTG_HCINT_NAK);
    }
    else if (is_HC_int(chnum, USB_OTG_HCINT_CHH))
    {
        mask_halt_HC_int(chnum);
        switch (m_HC[chnum].state)
        {
        case EHCState::XFRC:
            m_HC[chnum].urb_state = EURBState::DONE;
            if (m_HC[chnum].ep_type == EEPType::BULK)
                m_HC[chnum].toggle_out ^= 1;
            break;
        case EHCState::NAK:
            m_HC[chnum].urb_state = EURBState::NOT_READY;
            break;
        case EHCState::NYET:
            m_HC[chnum].urb_state = EURBState::NOT_READY;
            m_HC[chnum].do_ping = false;
            break;
        case EHCState::STALL:
            m_HC[chnum].urb_state = EURBState::STALL;
            break;
        case EHCState::XACTERR:
        case EHCState::DATATGLERR:
            if (m_HC[chnum].ErrCnt++ > 3)
            {
                m_HC[chnum].ErrCnt = 0;
                m_HC[chnum].urb_state = EURBState::ERROR;
            }
            else
                m_HC[chnum].urb_state = EURBState::NOT_READY;
            break;
        case EHCState::IDLE:
        case EHCState::HALTED:
        case EHCState::BBLERR:
            break;
        }

        clear_HC_int(chnum, USB_OTG_HCINT_CHH);
        HC_notify_URB_change_callback(this, chnum, m_HC[chnum].urb_state);
    }
}

void STM32_HCD::RXQLVL_IRQ_handler()
{
    uint32_t tmp = m_regs->global.GRXSTSP;
    uint8_t ch_num = tmp & USB_OTG_GRXSTSP_EPNUM;
    uint32_t pktsts = (tmp & USB_OTG_GRXSTSP_PKTSTS) >> USB_OTG_GRXSTSP_PKTSTS_Pos;
    uint32_t pktcnt = (tmp & USB_OTG_GRXSTSP_BCNT) >> USB_OTG_GRXSTSP_BCNT_Pos;

    switch (pktsts)
    {
    case GRXSTS_PKTSTS_IN:
        if ((pktcnt > 0) && (m_HC[ch_num].xfer_buff != nullptr))
        {
            read_packet(m_HC[ch_num].xfer_buff, pktcnt);
            m_HC[ch_num].xfer_buff += pktcnt;
            m_HC[ch_num].xfer_count += pktcnt;
            if ((HC_get_Xfer_size(ch_num) & USB_OTG_HCTSIZ_PKTCNT) > 0)
            {
                HC_reactivate(ch_num);
                m_HC[ch_num].toggle_in ^= 1;
            }
        }
        break;
    case GRXSTS_PKTSTS_DATA_TOGGLE_ERR:
    case GRXSTS_PKTSTS_IN_XFER_COMP:
    case GRXSTS_PKTSTS_CH_HALTED:
    default:
        break;
    }
}

void STM32_HCD::port_IRQ_handler()
{
    uint32_t hprt0, hprt0_dup;
    hprt0 = hprt0_dup = m_regs->ports[0];

    hprt0_dup &= ~(USB_OTG_HPRT_PENA | USB_OTG_HPRT_PCDET |
                   USB_OTG_HPRT_PENCHNG | USB_OTG_HPRT_POCCHNG);
    if ((hprt0 & USB_OTG_HPRT_PCDET) == USB_OTG_HPRT_PCDET)
    {
        if ((hprt0 & USB_OTG_HPRT_PCSTS) == USB_OTG_HPRT_PCSTS)
        {
            mask_IT(USB_OTG_GINTSTS_DISCINT);
            connect_callback(this);
        }
        hprt0_dup |= USB_OTG_HPRT_PCDET;
    }
    if ((hprt0 & USB_OTG_HPRT_PENCHNG) == USB_OTG_HPRT_PENCHNG)
    {
        hprt0_dup |= USB_OTG_HPRT_PENCHNG;
        if ((hprt0 & USB_OTG_HPRT_PENA) == USB_OTG_HPRT_PENA)
        {
            if (m_phy == EOTG_PHY::EMBEDDED)
            {
                if ((hprt0 & USB_OTG_HPRT_PSPD) == USB_OTG_HPRT_PSPD)
                    init_FSLSPClk_sel(EClockSpeed::_6_MHZ);
                else
                    init_FSLSPClk_sel(EClockSpeed::_48_MHZ);
            }
            else if (m_speed == EOTGSpeed::FULL)
                set_FSLSPClk(60*1000);
            connect_callback(this);
        }
        else
        {
            m_regs->ports[0] &= ~(USB_OTG_HPRT_PENA | USB_OTG_HPRT_PCDET | USB_OTG_HPRT_PENCHNG | USB_OTG_HPRT_POCCHNG);
            unmask_IT(USB_OTG_GINTSTS_DISCINT);
        }
    }

    if ((hprt0 & USB_OTG_HPRT_POCCHNG) == USB_OTG_HPRT_POCCHNG)
        hprt0_dup |= USB_OTG_HPRT_POCCHNG;
    reset_port_st1(hprt0_dup);
}

#ifdef STM32_USE_USB_FS
STM32_HCD usb_fs;
#endif

//#ifdef STM32_USE_USB_HS
STM32_HCD usb_hs;
//#endif

#ifdef STM32_USE_USB_FS
void ISR::OTG_FS_IRQ()
{
    GPIOD->BSRR = GPIO_BSRR_BS15;
    usb_fs.IRQ_handler();
}
#endif

//#ifdef STM32_USE_USB_HS
void ISR::OTG_HS_IRQ()
{
    GPIOD->BSRR = GPIO_BSRR_BS15;
    usb_hs.IRQ_handler();
}
//#endif

__attribute__((weak)) void disconnect_callback(STM32_HCD *hcd)
{
    UNUSED(hcd);
}

__attribute__((weak)) void connect_callback(STM32_HCD *hcd)
{
    UNUSED(hcd);
}

__attribute__((weak)) void SOF_callback(STM32_HCD *hcd)
{
    UNUSED(hcd);
}

__attribute__((weak)) void HC_notify_URB_change_callback(STM32_HCD *hcd, uint8_t ch_num, EURBState urb_state)
{
    UNUSED(hcd);
    UNUSED(ch_num);
    UNUSED(urb_state);
}
