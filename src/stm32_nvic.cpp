#include "stm32_inc.h"

void STM32_NVIC::init()
{
    set_priority_grouping(NVIC_PRIORITYGROUP_4);
    set_priority(MemoryManagement_IRQn, 0, 0);
    set_priority(BusFault_IRQn, 0, 0);
    set_priority(UsageFault_IRQn, 0, 0);
    set_priority(SVCall_IRQn, 0, 0);
    set_priority(DebugMonitor_IRQn, 0, 0);
    set_priority(PendSV_IRQn, 15, 0);
    set_priority(SysTick_IRQn, 15, 0);
    set_priority(FLASH_IRQn, 0, 0);
    enable_IRQ(FLASH_IRQn);
}

void STM32_NVIC::deInit()
{
    //disable all interrupts in NVIC
    NVIC->ICER[0] = 0xFFFFFFFF;
    NVIC->ICER[1] = 0xFFFFFFFF;
    NVIC->ICER[2] = 0xFFFFFFFF;

    //clear all pending bit
    NVIC->ICPR[0] = 0xFFFFFFFF;
    NVIC->ICPR[1] = 0xFFFFFFFF;
    NVIC->ICPR[2] = 0xFFFFFFFF;
}

void STM32_NVIC::init_vectors()
{
    #ifdef STM32_USE_UART1
    enable_and_set_prior_IRQ(USART1_IRQn, 0, 0);
    #endif
    #ifdef STM32_USE_UART2
    enable_and_set_prior_IRQ(USART2_IRQn, 0, 0);
    #endif
    #ifdef STM32_USE_UART3
    enable_and_set_prior_IRQ(USART3_IRQn, 0, 0);
    #endif
    #ifdef STM32_USE_UART4
    enable_and_set_prior_IRQ(USART4_IRQn, 0, 0);
    #endif
    #ifdef STM32_USE_UART5
    enable_and_set_prior_IRQ(USART5_IRQn, 0, 0);
    #endif
    #ifdef STM32_USE_UART6
    enable_and_set_prior_IRQ(USART6_IRQn, 0, 0);
    #endif
    #ifdef STM32_USE_UART7
    enable_and_set_prior_IRQ(USART7_IRQn, 0, 0);
    #endif
    #ifdef STM32_USE_UART8
    enable_and_set_prior_IRQ(USART8_IRQn, 0, 0);
    #endif
    #ifdef STM32_USE_SPI1
    enable_and_set_prior_IRQ(SPI1_IRQn, 0, 0);
    #endif
    #ifdef STM32_USE_SPI2
    enable_and_set_prior_IRQ(SPI2_IRQn, 0, 0);
    #endif
    #ifdef STM32_USE_SPI3
    enable_and_set_prior_IRQ(SPI3_IRQn, 0, 0);
    #endif
    #ifdef STM32_USE_SPI4
    enable_and_set_prior_IRQ(SPI4_IRQn, 0, 0);
    #endif
    #ifdef STM32_USE_SPI5
    enable_and_set_prior_IRQ(SPI5_IRQn, 0, 0);
    #endif
    #ifdef STM32_USE_SPI6
    enable_and_set_prior_IRQ(SPI6_IRQn, 0, 0);
    #endif
    #ifdef STM32_USE_EXTI0
    enable_and_set_prior_IRQ(EXTI0_IRQn, 4, 0);
    #endif
    #ifdef STM32_USE_EXTI1
    enable_and_set_prior_IRQ(EXTI1_IRQn, 0, 0);
    #endif
    #ifdef STM32_USE_EXTI2
    enable_and_set_prior_IRQ(EXTI2_IRQn, 0, 0);
    #endif
    #ifdef STM32_USE_EXTI3
    enable_and_set_prior_IRQ(EXTI3_IRQn, 0, 0);
    #endif
    #ifdef STM32_USE_EXTI4
    enable_and_set_prior_IRQ(EXTI4_IRQn, 0, 0);
    #endif
    #ifdef STM32_USE_EXTI9_5
    enable_and_set_prior_IRQ(EXTI9_5_IRQn, 0, 0);
    #endif
    #ifdef STM32_USE_EXTI15_10
    enable_and_set_prior_IRQ(EXTI15_10_IRQn, 0, 0);
    #endif
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
