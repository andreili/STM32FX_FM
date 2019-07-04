#ifndef STM32_NVIC_H
#define STM32_NVIC_H

#include "stm32_inc.h"

namespace STM32
{
    class NVIC
    {
    public:
        enum class EGroups: uint32_t
        {
            PRIORITYGROUP_0 = 0x07, /*!< 0 bits for pre-emption priority
                                         4 bits for subpriority */
            PRIORITYGROUP_1 = 0x06, /*!< 1 bits for pre-emption priority
                                         3 bits for subpriority */
            PRIORITYGROUP_2 = 0x05, /*!< 2 bits for pre-emption priority
                                         2 bits for subpriority */
            PRIORITYGROUP_3 = 0x04, /*!< 3 bits for pre-emption priority
                                         1 bits for subpriority */
            PRIORITYGROUP_4 = 0x03, /*!< 4 bits for pre-emption priority
                                         0 bits for subpriority */
        };

        static void init();
        static void deInit();
        static void init_vectors();

        static FORCE_INLINE uint32_t get_priority_grouping(void) { return CORTEX::SCB::AIRCR::get_prior_group(); }
        static FORCE_INLINE void set_priority_grouping(EGroups val)
            { CORTEX::NVIC::set_priority_grouping(static_cast<uint32_t>(val)); }

        static FORCE_INLINE uint32_t encode_priority(uint32_t group, uint32_t pre_prior, uint32_t sub_prior)
                { return CORTEX::NVIC::encode_priority(group, pre_prior, sub_prior); }

        static FORCE_INLINE void set_priority(STM32::IRQn irqn, uint32_t val) { CORTEX::NVIC::set_priority(irqn, val); }
        static FORCE_INLINE void set_priority(STM32::IRQn irqn, uint32_t prior, uint32_t subprior)
                { CORTEX::NVIC::set_priority(irqn,
                                   encode_priority(get_priority_grouping(),
                                                   prior, subprior)); }

        static inline void enable_IRQ(STM32::IRQn irqn) { CORTEX::NVIC::enable_IRQ(irqn); }
        static inline void disable_IRQ(STM32::IRQn irqn) { CORTEX::NVIC::disable_IRQ(irqn); }
        static inline bool is_active(STM32::IRQn irqn) { return CORTEX::NVIC::get_active_IRQ(irqn); }
        static inline void enable_and_set_prior_IRQ(STM32::IRQn irqn, uint32_t prior, uint32_t subprior)
                { set_priority(irqn, prior, subprior);
                  enable_IRQ(irqn); }
    };
}

#endif // STM32_NVIC_H
