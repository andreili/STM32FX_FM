#ifndef STM32_EXTI_HPP
#define STM32_EXTI_HPP

#include "stm32_inc.h"

namespace STM32
{

class EXTI
{
public:
    enum class ELine: uint32_t
    {
        LINE_00 = 0,
        LINE_01 = 1,
        LINE_02 = 2,
        LINE_03 = 3,
        LINE_04 = 4,
        LINE_05 = 5,
        LINE_06 = 6,
        LINE_07 = 7,
        LINE_08 = 8,
        LINE_09 = 9,
        LINE_10 = 10,
        LINE_11 = 11,
        LINE_12 = 12,
        LINE_13 = 13,
        LINE_14 = 14,
        LINE_15 = 15,
        LINE_16 = 16,
        LINE_17 = 17,
        LINE_18 = 18,
        LINE_19 = 19,
        LINE_20 = 20,
        LINE_21 = 21,
        LINE_22 = 22,
    };
private:
    static constexpr std::uint32_t EXTI_IMR_BASE     = (EXTI_BASE + 0x00UL);
    static constexpr std::uint32_t EXTI_EMR_BASE     = (EXTI_BASE + 0x04UL);
    static constexpr std::uint32_t EXTI_RTSR_BASE    = (EXTI_BASE + 0x08UL);
    static constexpr std::uint32_t EXTI_FTSR_BASE    = (EXTI_BASE + 0x0CUL);
    static constexpr std::uint32_t EXTI_SWIER_BASE   = (EXTI_BASE + 0x10UL);
    static constexpr std::uint32_t EXTI_PR_BASE      = (EXTI_BASE + 0x14UL);

    class IMR
    {
        struct IMR_t
        {
            union
            {
                struct
                {
                    bool    MASK_00: 1;
                    bool    MASK_01: 1;
                    bool    MASK_02: 1;
                    bool    MASK_03: 1;
                    bool    MASK_04: 1;
                    bool    MASK_05: 1;
                    bool    MASK_06: 1;
                    bool    MASK_07: 1;
                    bool    MASK_08: 1;
                    bool    MASK_09: 1;
                    bool    MASK_10: 1;
                    bool    MASK_11: 1;
                    bool    MASK_12: 1;
                    bool    MASK_13: 1;
                    bool    MASK_14: 1;
                    bool    MASK_15: 1;
                    bool    MASK_16: 1;
                    bool    MASK_17: 1;
                    bool    MASK_18: 1;
                    bool    MASK_19: 1;
                    bool    MASK_20: 1;
                    bool    MASK_21: 1;
                    bool    MASK_22: 1;
                    uint16_t res   : 9;
                };
                uint32_t    RAW;
            };
        };
    };
    class EMR
    {
        struct EMR_t
        {
            union
            {
                struct
                {
                    bool    MASK_00: 1;
                    bool    MASK_01: 1;
                    bool    MASK_02: 1;
                    bool    MASK_03: 1;
                    bool    MASK_04: 1;
                    bool    MASK_05: 1;
                    bool    MASK_06: 1;
                    bool    MASK_07: 1;
                    bool    MASK_08: 1;
                    bool    MASK_09: 1;
                    bool    MASK_10: 1;
                    bool    MASK_11: 1;
                    bool    MASK_12: 1;
                    bool    MASK_13: 1;
                    bool    MASK_14: 1;
                    bool    MASK_15: 1;
                    bool    MASK_16: 1;
                    bool    MASK_17: 1;
                    bool    MASK_18: 1;
                    bool    MASK_19: 1;
                    bool    MASK_20: 1;
                    bool    MASK_21: 1;
                    bool    MASK_22: 1;
                    uint16_t res   : 9;
                };
                uint32_t    RAW;
            };
        };
    };
    class RTSR
    {
        struct RTSR_t
        {
            union
            {
                struct
                {
                    bool    MASK_00: 1;
                    bool    MASK_01: 1;
                    bool    MASK_02: 1;
                    bool    MASK_03: 1;
                    bool    MASK_04: 1;
                    bool    MASK_05: 1;
                    bool    MASK_06: 1;
                    bool    MASK_07: 1;
                    bool    MASK_08: 1;
                    bool    MASK_09: 1;
                    bool    MASK_10: 1;
                    bool    MASK_11: 1;
                    bool    MASK_12: 1;
                    bool    MASK_13: 1;
                    bool    MASK_14: 1;
                    bool    MASK_15: 1;
                    bool    MASK_16: 1;
                    bool    MASK_17: 1;
                    bool    MASK_18: 1;
                    bool    MASK_19: 1;
                    bool    MASK_20: 1;
                    bool    MASK_21: 1;
                    bool    MASK_22: 1;
                    uint16_t res   : 9;
                };
                uint32_t    RAW;
            };
        };
    };
    class FTSR
    {
        struct FTSR_t
        {
            union
            {
                struct
                {
                    bool    MASK_00: 1;
                    bool    MASK_01: 1;
                    bool    MASK_02: 1;
                    bool    MASK_03: 1;
                    bool    MASK_04: 1;
                    bool    MASK_05: 1;
                    bool    MASK_06: 1;
                    bool    MASK_07: 1;
                    bool    MASK_08: 1;
                    bool    MASK_09: 1;
                    bool    MASK_10: 1;
                    bool    MASK_11: 1;
                    bool    MASK_12: 1;
                    bool    MASK_13: 1;
                    bool    MASK_14: 1;
                    bool    MASK_15: 1;
                    bool    MASK_16: 1;
                    bool    MASK_17: 1;
                    bool    MASK_18: 1;
                    bool    MASK_19: 1;
                    bool    MASK_20: 1;
                    bool    MASK_21: 1;
                    bool    MASK_22: 1;
                    uint16_t res   : 9;
                };
                uint32_t    RAW;
            };
        };
    };
    class SWIER
    {
        struct SWIER_t
        {
            union
            {
                struct
                {
                    bool    MASK_00: 1;
                    bool    MASK_01: 1;
                    bool    MASK_02: 1;
                    bool    MASK_03: 1;
                    bool    MASK_04: 1;
                    bool    MASK_05: 1;
                    bool    MASK_06: 1;
                    bool    MASK_07: 1;
                    bool    MASK_08: 1;
                    bool    MASK_09: 1;
                    bool    MASK_10: 1;
                    bool    MASK_11: 1;
                    bool    MASK_12: 1;
                    bool    MASK_13: 1;
                    bool    MASK_14: 1;
                    bool    MASK_15: 1;
                    bool    MASK_16: 1;
                    bool    MASK_17: 1;
                    bool    MASK_18: 1;
                    bool    MASK_19: 1;
                    bool    MASK_20: 1;
                    bool    MASK_21: 1;
                    bool    MASK_22: 1;
                    uint16_t res   : 9;
                };
                uint32_t    RAW;
            };
        };
    };
    class PR
    {
        struct PR_t
        {
            union
            {
                struct
                {
                    bool    MASK_00: 1;
                    bool    MASK_01: 1;
                    bool    MASK_02: 1;
                    bool    MASK_03: 1;
                    bool    MASK_04: 1;
                    bool    MASK_05: 1;
                    bool    MASK_06: 1;
                    bool    MASK_07: 1;
                    bool    MASK_08: 1;
                    bool    MASK_09: 1;
                    bool    MASK_10: 1;
                    bool    MASK_11: 1;
                    bool    MASK_12: 1;
                    bool    MASK_13: 1;
                    bool    MASK_14: 1;
                    bool    MASK_15: 1;
                    bool    MASK_16: 1;
                    bool    MASK_17: 1;
                    bool    MASK_18: 1;
                    bool    MASK_19: 1;
                    bool    MASK_20: 1;
                    bool    MASK_21: 1;
                    bool    MASK_22: 1;
                    uint16_t res   : 9;
                };
                uint32_t    RAW;
            };
        };
    };
public:
    static void set_interrupt_enable(ELine line, bool val)
    {
        BBPER_WR(EXTI_IMR_BASE, static_cast<uint32_t>(line), val);
    }
    static void set_event_enable(ELine line, bool val)
    {
        BBPER_WR(EXTI_EMR_BASE, static_cast<uint32_t>(line), val);
    }
    static void set_rising_edge_enable(ELine line, bool val)
    {
        BBPER_WR(EXTI_RTSR_BASE, static_cast<uint32_t>(line), val);
    }
    static void set_falling_edge_enable(ELine line, bool val)
    {
        BBPER_WR(EXTI_RTSR_BASE, static_cast<uint32_t>(line), val);
    }
    static void clear_flag(ELine line)
    {
        BBPER_WR(EXTI_PR_BASE, static_cast<uint32_t>(line), false);
    }
    static bool get_flag(ELine line)
    {
        return BBPER_RD(EXTI_PR_BASE, static_cast<uint32_t>(line));
    }
    static void generate_SWIT(ELine line)
    {
        BBPER_WR(EXTI_SWIER_BASE, static_cast<uint32_t>(line), true);
    }
};

}

#endif // STM32_EXTI_HPP
