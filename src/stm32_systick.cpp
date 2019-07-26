#include "stm32_inc.h"

namespace STM32
{

volatile uint32_t SYSTICK::m_tick;

void SYSTICK::init()
{
    update_freq();
    set_clock_source(EClockDiv::HCLK);
    NVIC::set_priority(IRQn::SysTick, static_cast<uint32_t>(STM32_PRIORITY_SYSCLK), 0);
    m_tick = 0;
}

void SYSTICK::deinit()
{
    CORTEX::SysTick::CTRL::set(0);
    CORTEX::SysTick::LOAD::set(0);
    CORTEX::SysTick::VAL::set(0);
}

void SYSTICK::update_freq()
{
    CORTEX::SysTick::config(STM32::RCC::get_HCLK_freq() / STM32_SYSTICK_FREQ_HZ - 1);
    set_clock_source(EClockDiv::HCLK);
}

void SYSTICK::set_clock_source(EClockDiv src)
{
    CORTEX::SysTick::CTRL::set_source_HCLK(src == EClockDiv::HCLK);
}

void SYSTICK::delay(__IO uint32_t delay_ms)
{
    if (m_tick == 0)
        return;
    uint32_t tick_end = m_tick + delay_ms;
    while(m_tick < tick_end) {}
}

void SYSTICK::delay_to(__IO uint32_t delay_ms)
{
    while(m_tick < delay_ms) {}
}

}

#ifdef STM32_TIMEBASE_SYSTICK
void ISR::SysTickTimer()
{
    STM32::SYSTICK::on_tick();
}
#endif //STM32_TIMEBASE_SYSTICK
