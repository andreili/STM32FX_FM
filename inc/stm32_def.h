#ifndef STM32_DEF_H
#define STM32_DEF_H

#include <stdint.h>
#include "stm32f4xx.h"
#include "bitbanding.h"

extern uint32_t unused_reg;
#define UNUSED(x) (void)(x)

#define STM32_RESULT_OK         0
#define STM32_RESULT_FAIL       1
#define STM32_RESULT_TIMEOUT    2
#define STM32_RESULT_BUSY       3

#define STM32_UNLOCKED 0
#define STM32_LOCKED   1

#define STM32_USB_FS_PORT gpioa
#define STM32_USB_FS_EN_CLK enable_clk_GPIOA
#define STM32_USB_FS_DM_PIN GPIO_PIN_11
#define STM32_USB_FS_DP_PIN GPIO_PIN_12

#define STM32_USB_HS_PORT gpiob
#define STM32_USB_HS_EN_CLK enable_clk_GPIOB
#define STM32_USB_HS_DM_PIN GPIO_PIN_14
#define STM32_USB_HS_DP_PIN GPIO_PIN_15

#define FORCE_INLINE __attribute__((always_inline))

#define ENDIS_REG_FLAG(name, reg, mask) \
    static inline void enable_ ## name() { BIT_BAND_PER(reg, mask) = ENABLE; unused_reg = reg & mask; } \
    static inline void disable_ ## name() { BIT_BAND_PER(reg, mask) = DISABLE; unused_reg = reg & mask; }

#define ENDIS_REG_FLAG_(reg, mask) \
    inline void enable() { BIT_BAND_PER(reg, mask) = ENABLE; } \
    inline void disable() { BIT_BAND_PER(reg, mask) = DISABLE; }
#define ENDIS_REG_FLAG_NAME(name, reg, mask) \
    inline void enable_ ## name() { BIT_BAND_PER(reg, mask) = ENABLE; } \
    inline void disable_ ## name() { BIT_BAND_PER(reg, mask) = DISABLE; }

#define CLK_ENDIS(enr, name) \
    ENDIS_REG_FLAG(clk_ ## name, RCC->enr ## ENR, RCC_ ## enr ## ENR_ ## name ## EN) \
    static inline bool check_enable_clk_ ## name() { return BIT_BAND_PER(RCC->enr ## ENR, RCC_ ## enr ## ENR_ ## name ## EN); }

#define PER_RESET_SLEEP(enr, name) \
    static inline void force_reset_ ## name() { BIT_BAND_PER(RCC-> enr ## RSTR, RCC_ ## enr ## RSTR_ ## name ## RST) = ENABLE; } \
    static inline void release_reset_ ## name() { BIT_BAND_PER(RCC-> enr ## RSTR, RCC_ ## enr ## RSTR_ ## name ## RST) = DISABLE; } \
    static inline void sleep_enable_ ## name() { BIT_BAND_PER(RCC-> enr ## LPENR, RCC_ ## enr ## LPENR_ ## name ## LPEN) = ENABLE; }

#define WAIT_TIMEOUT(condition, timeout) \
    { \
        uint32_t tout_ex = STM32_SYSTICK::get_tick() + timeout; \
        while (condition) \
        { \
            if ((STM32_SYSTICK::get_tick()) > tout_ex) \
                return STM32_RESULT_TIMEOUT; \
        } \
    }

#define WAIT_TIMEOUT_EX(condition, timeout, ret) \
    { \
        uint32_t tout_ex = STM32_SYSTICK::get_tick() + timeout; \
        while (condition) \
        { \
            if ((STM32_SYSTICK::get_tick()) > tout_ex) \
                return ret; \
        } \
    }

void Error_Handler();

class STM32_SDRAM;
extern STM32_SDRAM sdram;

enum class TXRX_MODE
{
    DIRECT,
    INTERRUPT,
    DMA,
};

#ifdef STM32_DEBUG
#include "xprintf.h"
#define debug_out(s) uart6.send_str(s, TXRX_MODE::DIRECT)
#define debug_printf(s, ...) xprintf(s, __VA_ARGS__)
#else
#define debug_out(s) UNUSED(s)
#define debug_printf(s, ...) UNUSED(s); UNUSED(__VA_ARGS__)
#endif

#endif
