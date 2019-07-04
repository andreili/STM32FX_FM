#ifndef STM32_SYSTICK_H
#define STM32_SYSTICK_H

#include "stm32_inc.h"

namespace STM32
{

    class SYSTICK
    {
    public:
        enum class EClockDiv: uint32_t
        {
            HCLK_DIV8    = 0x00000000U,
            HCLK         = 0x00000004U,
        };
        static void init();
        static void deinit();
        static void update_freq();
        static void set_clock_source(EClockDiv src);

        static inline uint32_t get_tick() { return m_tick; }

        static inline void on_tick() { ++m_tick; }
        static void delay(__IO uint32_t delay_ms);
        static void delay_to(__IO uint32_t delay_ms);

        static inline void manual_trig() { CORTEX::SCB::ICSR::set_pend_ST(); }
        static inline void suspend() { CORTEX::SysTick::suspend(); }
        static inline void resume() { CORTEX::SysTick::resume(); }

        /*ENDIS_REG_FLAG(DBG_sleep_mode, DBGMCU->CR, DBGMCU_CR_DBG_SLEEP)
        ENDIS_REG_FLAG(DBG_stop_mode, DBGMCU->CR, DBGMCU_CR_DBG_SLEEP)
        ENDIS_REG_FLAG(DBG_standby_mode, DBGMCU->CR, DBGMCU_CR_DBG_SLEEP)
            #ifdef STM32F4
        ENDIS_REG_FLAG(compensation_cell, SYSCFG->CMPCR, SYSCFG_CMPCR_CMP_PD)
            #endif*/
    #ifdef SYSCFG_MEMRMP_UFB_MODE
        static inline void set_compensation_cell(bool val) { SYSCFG::MEMRMP::set_UFB_mode(val);
    #endif
    private:
        static volatile uint32_t m_tick;
    };
}

void systick_callback();

#endif
