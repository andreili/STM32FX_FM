#include "stm32_inc.h"

namespace STM32
{

void NVIC::init()
{
    set_priority_grouping(EGroups::PRIORITYGROUP_4);
    set_priority(IRQn::MemoryManagement, 0, 0);
    set_priority(IRQn::BusFault, 0, 0);
    set_priority(IRQn::UsageFault, 0, 0);
    set_priority(IRQn::SVCall, 0, 0);
    set_priority(IRQn::DebugMonitor, 0, 0);
    set_priority(IRQn::PendSV, 15, 0);
    set_priority(IRQn::SysTick, 15, 0);
    set_priority(IRQn::FLASH, 0, 0);
    enable_IRQ(IRQn::FLASH);
}

void NVIC::deInit()
{
    CORTEX::NVIC::disable_all_IRQs();
    CORTEX::NVIC::clear_all_pending_IRQs();
}

void NVIC::init_vectors()
{
    #ifdef STM32_USE_UART1
    enable_and_set_prior_IRQ(IRQn::USART1, 0, 0);
    #endif
    #ifdef STM32_USE_UART2
    enable_and_set_prior_IRQ(IRQn::USART2, 0, 0);
    #endif
    #ifdef STM32_USE_UART3
    enable_and_set_prior_IRQ(IRQn::USART3, 0, 0);
    #endif
    #ifdef STM32_USE_UART4
    enable_and_set_prior_IRQ(IRQn::USART4, 0, 0);
    #endif
    #ifdef STM32_USE_UART5
    enable_and_set_prior_IRQ(IRQn::USART5, 0, 0);
    #endif
    #ifdef STM32_USE_UART6
    enable_and_set_prior_IRQ(IRQn::USART6, 0, 0);
    #endif
    #ifdef STM32_USE_UART7
    enable_and_set_prior_IRQ(IRQn::USART7, 0, 0);
    #endif
    #ifdef STM32_USE_UART8
    enable_and_set_prior_IRQ(IRQn::USART8, 0, 0);
    #endif
    #ifdef STM32_USE_SPI1
    enable_and_set_prior_IRQ(IRQn::SPI1, 0, 0);
    #endif
    #ifdef STM32_USE_SPI2
    enable_and_set_prior_IRQ(IRQn::SPI2, 0, 0);
    #endif
    #ifdef STM32_USE_SPI3
    enable_and_set_prior_IRQ(IRQn::SPI3, 0, 0);
    #endif
    #ifdef STM32_USE_SPI4
    enable_and_set_prior_IRQ(IRQn::SPI4, 0, 0);
    #endif
    #ifdef STM32_USE_SPI5
    enable_and_set_prior_IRQ(IRQn::SPI5, 0, 0);
    #endif
    #ifdef STM32_USE_SPI6
    enable_and_set_prior_IRQ(IRQn::SPI6, 0, 0);
    #endif
    #ifdef STM32_USE_EXTI0
    enable_and_set_prior_IRQ(IRQn::EXTI0, 4, 0);
    #endif
    #ifdef STM32_USE_EXTI1
    enable_and_set_prior_IRQ(IRQn::EXTI1, 0, 0);
    #endif
    #ifdef STM32_USE_EXTI2
    enable_and_set_prior_IRQ(IRQn::EXTI2, 0, 0);
    #endif
    #ifdef STM32_USE_EXTI3
    enable_and_set_prior_IRQ(IRQn::EXTI3, 0, 0);
    #endif
    #ifdef STM32_USE_EXTI4
    enable_and_set_prior_IRQ(IRQn::EXTI4, 0, 0);
    #endif
    #ifdef STM32_USE_EXTI9_5
    enable_and_set_prior_IRQ(IRQn::EXTI9_5, 0, 0);
    #endif
    #ifdef STM32_USE_EXTI15_10
    enable_and_set_prior_IRQ(IRQn::EXTI15_10, 0, 0);
    #endif
}

}

void ISR::NMI()
{
    //TODO
}

void ISR::MemManage()
{
    Error_Handler();
}

void ISR::BusFault()
{
    Error_Handler();
}

void ISR::UsageFault()
{
    Error_Handler();
}

void ISR::HardFault()
{
    Error_Handler();
}
