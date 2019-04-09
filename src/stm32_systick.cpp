#include "stm32_inc.h"

volatile uint32_t STM32_SYSTICK::m_tick;

void STM32_SYSTICK::init()
{
    update_freq();
    set_clock_source(SYSTICK_CLKSOURCE_HCLK);
    STM32_NVIC::set_priority(SysTick_IRQn, STM32_PRIORITY_SYSCLK, 0);
    m_tick = 0;
}

void STM32_SYSTICK::deinit()
{
    SysTick->CTRL = 0;
    SysTick->LOAD = 0;
    SysTick->VAL = 0;
}

void STM32_SYSTICK::update_freq()
{
    SysTick_Config(STM32_RCC::get_HCLK_freq() / STM32_SYSTICK_FREQ_HZ - 1);
    set_clock_source(SYSTICK_CLKSOURCE_HCLK);
}

void STM32_SYSTICK::set_clock_source(uint32_t src)
{
    if (src == SYSTICK_CLKSOURCE_HCLK)
        SysTick->CTRL |= SYSTICK_CLKSOURCE_HCLK;
    else
        SysTick->CTRL &= ~SYSTICK_CLKSOURCE_HCLK;
}

void STM32_SYSTICK::delay(__IO uint32_t delay_ms)
{
    if (m_tick == 0)
        return;
    uint32_t tick_end = m_tick + delay_ms;
    while(m_tick < tick_end) {}
}

void STM32_SYSTICK::delay_to(__IO uint32_t delay_ms)
{
    while(m_tick < delay_ms) {}
}

#ifdef STM32_TIMEBASE_SYSTICK
void ISR::SysTickTimer()
{
    STM32_SYSTICK::on_tick();
}
#endif //STM32_TIMEBASE_SYSTICK
