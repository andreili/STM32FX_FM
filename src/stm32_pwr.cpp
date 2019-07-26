#include "stm32_inc.h"

namespace STM32
{

constexpr std::uint32_t PWR_OVERDRIVE_TIMEOUT_VALUE  = 1000U;
constexpr std::uint32_t PWR_UDERDRIVE_TIMEOUT_VALUE  = 1000U;
constexpr std::uint32_t PWR_BKPREG_TIMEOUT_VALUE     = 1000U;
constexpr std::uint32_t PWR_VOSRDY_TIMEOUT_VALUE     = 1000U;

void PWR::deinit()
{
#if defined(STM32F1)
    #error TODO
    STM32::RCC::APB1_reset_force<STM32_REGS::RCC::APB1RSTR::EMasks::PWRRST>();
    STM32::RCC::APB1_reset_release<STM32_REGS::RCC::APB1RSTR::EMasks::PWRRST>();
#else
    STM32::RCC::APB1_reset_force<STM32_REGS::RCC::APB1RSTR::EMasks::PWRRST>();
    STM32::RCC::APB1_reset_release<STM32_REGS::RCC::APB1RSTR::EMasks::PWRRST>();
#endif
}

void PWR::config_PVD()
{
    set_PVD_interrupt_enable((STM32_PVD_MODE & EPVDMode::IT) == EPVDMode::IT);
    set_PVD_event_enable((STM32_PVD_MODE & EPVDMode::EVT)== EPVDMode::EVT);
    set_PVD_rising_edge_enable((STM32_PVD_MODE & EPVDMode::RISING_EDGE) == EPVDMode::RISING_EDGE);
    set_PVD_falling_edge_enable((STM32_PVD_MODE & EPVDMode::FALLING_EDGE) == EPVDMode::FALLING_EDGE);
}

void PWR::enter_sleep_mode(EEntry entry)
{
    CORTEX::SCB::SCR::set_sleep_deep(false);
    if (entry == EEntry::WFI)
    {
        /* Request Wait For Interrupt */
        CMSIS::WFI();
    }
    else
    {
        /* Request Wait For Event */
        CMSIS::SEV();
        CMSIS::WFE();
        CMSIS::WFE();
    }
}

void PWR::enter_stop_mode(ELowPowerReg Regulator, EEntry entry)
{
    CR::set_power_down_deepsleep(false);
    CR::set_low_power_deepsleep(Regulator);
    CORTEX::SCB::SCR::set_sleep_deep(true);
    if (entry == EEntry::WFI)
        /* Request Wait For Interrupt */
        CMSIS::WFI();
    else
    {
        /* Request Wait For Event */
        CMSIS::SEV();
        CMSIS::WFE();
        CMSIS::WFE();
    }
    /* Reset SLEEPDEEP bit of Cortex System Control Register */
    CORTEX::SCB::SCR::set_sleep_deep(false);
}

void PWR::enter_standby_mode()
{
    CR::set_power_down_deepsleep(true);
    CORTEX::SCB::SCR::set_sleep_deep(true);
    CMSIS::WFI();
}

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) ||\
    defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx)
uint32_t PWR::enable_overdrive()
{
    STM32::RCC::enable_clk_PWR();

    /* Enable the Over-drive to extend the clock frequency to 180 Mhz */
    PWR_OVERDRIVE_ENABLE();

    /* Get tick */
    uint32_t tickstart = STM32_SYSTICK::get_tick();

    while ((PWR->CSR & PWR_FLAG_ODRDY) != PWR_FLAG_ODRDY)
    {
        if ((STM32_SYSTICK::get_tick() - tickstart) > PWR_OVERDRIVE_TIMEOUT_VALUE)
            return STM32_RESULT_TIMEOUT;
    }

    /* Enable the Over-drive switch */
    enable_overdrive_switching();

    /* Get tick */
    tickstart = STM32_SYSTICK::get_tick();

    while ((PWR->CSR & PWR_FLAG_ODSWRDY) != PWR_FLAG_ODSWRDY)
    {
        if ((STM32_SYSTICK::get_tick() - tickstart ) > PWR_OVERDRIVE_TIMEOUT_VALUE)
            return STM32_RESULT_TIMEOUT;
    }
    return STM32_RESULT_OK;
}

uint32_t PWR::disable_overdrive()
{
    STM32::RCC::enable_clk_PWR();

    /* Disable the Over-drive switch */
    disable_overdrive_switching();

    /* Get tick */
    uint32_t tickstart = STM32_SYSTICK::get_tick();

    while ((PWR->CSR & PWR_FLAG_ODSWRDY) == PWR_FLAG_ODSWRDY)
    {
        if ((STM32_SYSTICK::get_tick() - tickstart) > PWR_OVERDRIVE_TIMEOUT_VALUE)
            return STM32_RESULT_TIMEOUT;
    }

    /* Disable the Over-drive */
    PWR_OVERDRIVE_DISABLE();

    /* Get tick */
    tickstart = STM32_SYSTICK::get_tick();

    while ((PWR->CSR & PWR_FLAG_ODRDY) == PWR_FLAG_ODRDY)
    {
        if ((STM32_SYSTICK::get_tick() - tickstart) > PWR_OVERDRIVE_TIMEOUT_VALUE)
            return STM32_RESULT_TIMEOUT;
    }

    return STM32_RESULT_OK;
}

uint32_t PWR::enter_underdrive_stop_mode(uint32_t Regulator, uint8_t STOPEntry)
{
    uint32_t tmpreg1 = 0U;
    uint32_t tickstart = 0U;

    STM32::RCC::enable_clk_PWR();
    /* Enable the Under-drive Mode ---------------------------------------------*/
    /* Clear Under-drive flag */
    clear_odrudr_flag();

    /* Enable the Under-drive */
    enable_underdrive();

    /* Get tick */
    tickstart = STM32_SYSTICK::get_tick();

    /* Wait for UnderDrive mode is ready */
    while ((PWR->CSR & PWR_FLAG_UDRDY) == PWR_FLAG_UDRDY)
    {
        if ((STM32_SYSTICK::get_tick() - tickstart) > PWR_UDERDRIVE_TIMEOUT_VALUE)
            return STM32_RESULT_TIMEOUT;
    }

    /* Select the regulator state in STOP mode ---------------------------------*/
    tmpreg1 = PWR->CR;
    /* Clear PDDS, LPDS, MRLUDS and LPLUDS bits */
    tmpreg1 &= (uint32_t)~(PWR_CR_PDDS | PWR_CR_LPDS | PWR_CR_LPUDS | PWR_CR_MRUDS);

    /* Set LPDS, MRLUDS and LPLUDS bits according to PWR_Regulator value */
    tmpreg1 |= Regulator;

    /* Store the new value */
    PWR->CR = tmpreg1;

    /* Set SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* Select STOP mode entry --------------------------------------------------*/
    if (STOPEntry == PWR_SLEEPENTRY_WFI)
        /* Request Wait For Interrupt */
        __WFI();
    else
        /* Request Wait For Event */
        __WFE();

    /* Reset SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR &= ~((uint32_t)SCB_SCR_SLEEPDEEP_Msk);

    return STM32_RESULT_OK;
}
#endif

#ifdef STM32F4
uint32_t PWR::control_voltage_scaling(EVoltageScale voltage_scaling)
{
    STM32::RCC::enable_clk_PWR();
    set_voltage_scaling_enabled(voltage_scaling);
    WAIT_TIMEOUT(!CSR::get_ready_voltage_scaling(), PWR_VOSRDY_TIMEOUT_VALUE);
    return STM32_RESULT_OK;
}

uint32_t PWR::enable_backup_regulator()
{
    CSR::set_enable_backup_regulator(true);
    WAIT_TIMEOUT(!CSR::get_enable_backup_regulator(), PWR_BKPREG_TIMEOUT_VALUE);
    return STM32_RESULT_OK;
}

uint32_t PWR::disable_backup_regulator()
{
    CSR::set_enable_backup_regulator(false);
    WAIT_TIMEOUT(CSR::get_enable_backup_regulator(), PWR_BKPREG_TIMEOUT_VALUE);
    return STM32_RESULT_OK;
}
#endif

}

void ISR::PVD_IRQ()
{
    if (STM32::PWR::get_EXTI_flag())
    {
        ///TODO: PVDCallback()
        STM32::PWR::clear_EXTI_flag();
    }
}
