#include "profiler.hpp"

uint32_t        Profiler::m_cells;
uint32_t        Profiler::m_ev_start[PROFILER_CELLS_COUNT];
uint32_t        Profiler::m_ev_end[PROFILER_CELLS_COUNT];
uint32_t        Profiler::m_ticks[PROFILER_CELLS_COUNT];
uint32_t        Profiler::m_evs[PROFILER_CELLS_COUNT];
const char*     Profiler::m_names[PROFILER_CELLS_COUNT];

Profiler::Profiler()
{
    m_cells = 0;
}

void Profiler::init()
{
    STM32_TIM::TimerBaseInit_t init = {1, STM32_TIM::ECounterMode::UP, 0x7fff,
                                       STM32_TIM::EClkDiv::DIV_1, 0};
    PROFILER_TIMER.init(&init);
    STM32_RCC::enable_clk_TIM2();
    STM32_NVIC::enable_and_set_prior_IRQ(TIM2_IRQn, 0, 0);
}

void Profiler::start()
{
    PROFILER_TIMER.set_value(0);
    for (uint32_t i=0 ; i<PROFILER_CELLS_COUNT; ++i)
    {
        m_ev_start[i] = 0;
        m_ev_end[i] = 0;
        m_ticks[i] = 0;
        m_evs[i] = 0;
    }
    PROFILER_TIMER.start();
}

void Profiler::stop()
{
    PROFILER_TIMER.stop();
}

int Profiler::add_cell(const char *name)
{
    m_names[m_cells] = name;
    m_ticks[m_cells] = 0;
    return m_cells++;
}

void Profiler::start_ev(int idx)
{
    m_ev_start[idx] = PROFILER_TIMER.get_value();
}

void Profiler::end_ev(int idx)
{
    m_ev_end[idx] = PROFILER_TIMER.get_value();
    m_ticks[idx] += m_ev_end[idx] - m_ev_start[idx];
    ++m_evs[idx];
}
