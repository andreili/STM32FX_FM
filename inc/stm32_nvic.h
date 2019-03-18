#ifndef STM32_NVIC_H
#define STM32_NVIC_H

#include "stm32_inc.h"

#define NVIC_PRIORITYGROUP_0 ((uint32_t)0x07)/*!< 0 bits for pre-emption priority
                                                  4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1 ((uint32_t)0x06)/*!< 1 bits for pre-emption priority
                                                  3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2 ((uint32_t)0x05)/*!< 2 bits for pre-emption priority
                                                  2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3 ((uint32_t)0x04)/*!< 3 bits for pre-emption priority
                                                  1 bits for subpriority */
#define NVIC_PRIORITYGROUP_4 ((uint32_t)0x03)/*!< 4 bits for pre-emption priority
                                                  0 bits for subpriority */

inline uint32_t _NVIC_EncodePriority (uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);   /* only values 0..7 are used          */
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7UL - PriorityGroupTmp) > (uint32_t)(__NVIC_PRIO_BITS)) ?
              (uint32_t)(__NVIC_PRIO_BITS) :
              (uint32_t)(7UL - PriorityGroupTmp);
  SubPriorityBits     = ((PriorityGroupTmp + (uint32_t)(__NVIC_PRIO_BITS)) < (uint32_t)7UL) ?
              (uint32_t)0UL :
              (uint32_t)((PriorityGroupTmp - 7UL) + (uint32_t)(__NVIC_PRIO_BITS));

  return (
           ((PreemptPriority & (uint32_t)((1UL << (PreemptPriorityBits)) - 1UL)) << SubPriorityBits) |
           ((SubPriority     & (uint32_t)((1UL << (SubPriorityBits    )) - 1UL)))
         );
}
inline uint32_t _NVIC_GetPriorityGrouping(void) { return ((uint32_t)((SCB->AIRCR & SCB_AIRCR_PRIGROUP_Msk) >> SCB_AIRCR_PRIGROUP_Pos)); }

class STM32_NVIC
{
public:
    static void init();
    static void init_vectors();

    static FORCE_INLINE void set_priority_grouping(uint32_t val) { NVIC_SetPriorityGrouping(val); }
    static FORCE_INLINE uint32_t get_priority_grouping() { return _NVIC_GetPriorityGrouping(); }

    static FORCE_INLINE uint32_t encode_priority(uint32_t group, uint32_t pre_prior, uint32_t sub_prior)
            { return NVIC_EncodePriority(group, pre_prior, sub_prior); }

    static FORCE_INLINE void set_priority(IRQn_Type irqn, uint32_t val) { NVIC_SetPriority(irqn, val); }
    static FORCE_INLINE void set_priority(IRQn_Type irqn, uint32_t prior, uint32_t subprior)
            { NVIC_SetPriority(irqn,
                               _NVIC_EncodePriority(get_priority_grouping(),
                                                   prior, subprior)); }

    static inline void enable_IRQ(IRQn_Type irqn) { NVIC_EnableIRQ(irqn); }
    static inline void disable_IRQ(IRQn_Type irqn) { NVIC_DisableIRQ(irqn); }
    static inline bool is_active(IRQn_Type irqn)
    { return (NVIC->IABR[(((uint32_t)(int32_t)irqn) >> 5UL)] == (uint32_t)(1UL << (((uint32_t)(int32_t)irqn) & 0x1FUL))); }
    static inline void enable_and_set_prior_IRQ(IRQn_Type irqn, uint32_t prior, uint32_t subprior)
            { set_priority(irqn, prior, subprior);
              enable_IRQ(irqn); }
};

#endif // STM32_NVIC_H
