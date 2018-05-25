#include "stm32_hcd.h"

uint32_t STM32_HCD::init(USB_OTG_GlobalTypeDef* regs_addr)
{
    m_state = EHCDState::BUSY;
    m_regs = (OTGRegs_t*)regs_addr;
    init_gpio();
    disable();
    if (core_init() != STM32_RESULT_OK)
        return STM32_RESULT_FAIL;
    if (set_current_mode(EOTGDeviceMode::HOST) != STM32_RESULT_OK)
        return STM32_RESULT_FAIL;
    if (host_init() != STM32_RESULT_OK)
            return STM32_RESULT_FAIL;
    m_state = EHCDState::READY;
    return STM32_RESULT_OK;
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

#ifdef STM32_USE_USB_FS
STM32_HCD usb_fs;
#endif

#ifdef STM32_USE_USB_HS
STM32_HCD usb_hs;
#endif
