#include "stm32_inc.h"

#define GPIO_MODE             ((uint32_t)0x00000003U)
#define EXTI_MODE             ((uint32_t)0x10000000U)
#define GPIO_MODE_IT          ((uint32_t)0x00010000U)
#define GPIO_MODE_EVT         ((uint32_t)0x00020000U)
#define RISING_EDGE           ((uint32_t)0x00100000U)
#define FALLING_EDGE          ((uint32_t)0x00200000U)
#define GPIO_OUTPUT_TYPE      ((uint32_t)0x00000010U)

#define GPIO_NUMBER           ((uint32_t)16U)

#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx)
#define GPIO_GET_INDEX(__GPIOx__)    (uint8_t)(((__GPIOx__) == (GPIOA))? 0U :\
                                               ((__GPIOx__) == (GPIOB))? 1U :\
                                               ((__GPIOx__) == (GPIOC))? 2U :\
                                               ((__GPIOx__) == (GPIOD))? 3U :\
                                               ((__GPIOx__) == (GPIOE))? 4U :\
                                               ((__GPIOx__) == (GPIOF))? 5U :\
                                               ((__GPIOx__) == (GPIOG))? 6U :\
                                               ((__GPIOx__) == (GPIOH))? 7U : 8U)
#endif

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) ||\
    defined(STM32F469xx) || defined(STM32F479xx)
#define GPIO_GET_INDEX(__GPIOx__)    (uint8_t)(((__GPIOx__) == (GPIOA))? 0U :\
                                               ((__GPIOx__) == (GPIOB))? 1U :\
                                               ((__GPIOx__) == (GPIOC))? 2U :\
                                               ((__GPIOx__) == (GPIOD))? 3U :\
                                               ((__GPIOx__) == (GPIOE))? 4U :\
                                               ((__GPIOx__) == (GPIOF))? 5U :\
                                               ((__GPIOx__) == (GPIOG))? 6U :\
                                               ((__GPIOx__) == (GPIOH))? 7U :\
                                               ((__GPIOx__) == (GPIOI))? 8U :\
                                               ((__GPIOx__) == (GPIOJ))? 9U : 10U)
#endif

#if defined(STM32F429xx) || defined(STM32F439xx)
#define IS_GPIO_AF(AF)   (((AF) == GPIO_AF0_RTC_50Hz)   || ((AF) == GPIO_AF9_TIM14)      || \
                          ((AF) == GPIO_AF0_MCO)        || ((AF) == GPIO_AF0_TAMPER)     || \
                          ((AF) == GPIO_AF0_SWJ)        || ((AF) == GPIO_AF0_TRACE)      || \
                          ((AF) == GPIO_AF1_TIM1)       || ((AF) == GPIO_AF1_TIM2)       || \
                          ((AF) == GPIO_AF2_TIM3)       || ((AF) == GPIO_AF2_TIM4)       || \
                          ((AF) == GPIO_AF2_TIM5)       || ((AF) == GPIO_AF3_TIM8)       || \
                          ((AF) == GPIO_AF4_I2C1)       || ((AF) == GPIO_AF4_I2C2)       || \
                          ((AF) == GPIO_AF4_I2C3)       || ((AF) == GPIO_AF5_SPI1)       || \
                          ((AF) == GPIO_AF5_SPI2)       || ((AF) == GPIO_AF9_TIM13)      || \
                          ((AF) == GPIO_AF6_SPI3)       || ((AF) == GPIO_AF9_TIM12)      || \
                          ((AF) == GPIO_AF7_USART1)     || ((AF) == GPIO_AF7_USART2)     || \
                          ((AF) == GPIO_AF7_USART3)     || ((AF) == GPIO_AF8_UART4)      || \
                          ((AF) == GPIO_AF8_UART5)      || ((AF) == GPIO_AF8_USART6)     || \
                          ((AF) == GPIO_AF9_CAN1)       || ((AF) == GPIO_AF9_CAN2)       || \
                          ((AF) == GPIO_AF10_OTG_FS)    || ((AF) == GPIO_AF10_OTG_HS)    || \
                          ((AF) == GPIO_AF11_ETH)       || ((AF) == GPIO_AF12_OTG_HS_FS) || \
                          ((AF) == GPIO_AF12_SDIO)      || ((AF) == GPIO_AF13_DCMI)      || \
                          ((AF) == GPIO_AF15_EVENTOUT)  || ((AF) == GPIO_AF5_SPI4)       || \
                          ((AF) == GPIO_AF5_SPI5)       || ((AF) == GPIO_AF5_SPI6)       || \
                          ((AF) == GPIO_AF8_UART7)      || ((AF) == GPIO_AF8_UART8)      || \
                          ((AF) == GPIO_AF12_FMC)       ||  ((AF) == GPIO_AF6_SAI1)      || \
                          ((AF) == GPIO_AF14_LTDC))

#endif

#if defined(STM32F407xx) || defined(STM32F417xx)
#define IS_GPIO_AF(AF)   (((AF) == GPIO_AF0_RTC_50Hz)   || ((AF) == GPIO_AF9_TIM14)      || \
                          ((AF) == GPIO_AF0_MCO)        || ((AF) == GPIO_AF0_TAMPER)     || \
                          ((AF) == GPIO_AF0_SWJ)        || ((AF) == GPIO_AF0_TRACE)      || \
                          ((AF) == GPIO_AF1_TIM1)       || ((AF) == GPIO_AF1_TIM2)       || \
                          ((AF) == GPIO_AF2_TIM3)       || ((AF) == GPIO_AF2_TIM4)       || \
                          ((AF) == GPIO_AF2_TIM5)       || ((AF) == GPIO_AF3_TIM8)       || \
                          ((AF) == GPIO_AF4_I2C1)       || ((AF) == GPIO_AF4_I2C2)       || \
                          ((AF) == GPIO_AF4_I2C3)       || ((AF) == GPIO_AF5_SPI1)       || \
                          ((AF) == GPIO_AF5_SPI2)       || ((AF) == GPIO_AF9_TIM13)      || \
                          ((AF) == GPIO_AF6_SPI3)       || ((AF) == GPIO_AF9_TIM12)      || \
                          ((AF) == GPIO_AF7_USART1)     || ((AF) == GPIO_AF7_USART2)     || \
                          ((AF) == GPIO_AF7_USART3)     || ((AF) == GPIO_AF8_UART4)      || \
                          ((AF) == GPIO_AF8_UART5)      || ((AF) == GPIO_AF8_USART6)     || \
                          ((AF) == GPIO_AF9_CAN1)       || ((AF) == GPIO_AF9_CAN2)       || \
                          ((AF) == GPIO_AF10_OTG_FS)    || ((AF) == GPIO_AF10_OTG_HS)    || \
                          ((AF) == GPIO_AF11_ETH)       || ((AF) == GPIO_AF12_OTG_HS_FS) || \
                          ((AF) == GPIO_AF12_SDIO)      || ((AF) == GPIO_AF13_DCMI)      || \
                          ((AF) == GPIO_AF12_FSMC)      || ((AF) == GPIO_AF15_EVENTOUT))

#endif

void STM32_GPIO::init_all()
{
    gpioa.init(GPIOA_BASE);
    gpiob.init(GPIOB_BASE);
    gpioc.init(GPIOC_BASE);
    gpiod.init(GPIOD_BASE);
    gpioe.init(GPIOE_BASE);
    gpiof.init(GPIOF_BASE);
    gpiog.init(GPIOG_BASE);
    gpioh.init(GPIOH_BASE);
    gpioi.init(GPIOI_BASE);
}

void STM32_GPIO::init(uint32_t base_addr)
{
    m_gpio = (GPIO_TypeDef*)base_addr;
}

void STM32_GPIO::set_config(uint32_t pin_mask, uint32_t pin_mode, uint8_t pin_alt, uint32_t pin_speed, uint32_t pin_pull)
{
    uint32_t position;
    uint32_t ioposition = 0x00U;
    uint32_t iocurrent = 0x00U;
    uint32_t temp = 0x00U;

    /* Configure the port pins */
    for (position = 0U; position < GPIO_NUMBER; position++)
    {
        /* Get the IO position */
        ioposition = ((uint32_t)0x01U) << position;
        /* Get the current IO position */
        iocurrent = pin_mask & ioposition;

        if (iocurrent == ioposition)
        {
            /*--------------------- GPIO Mode Configuration ------------------------*/
            /* In case of Alternate function mode selection */
            if ((pin_mode == GPIO_MODE_AF_PP) || (pin_mode == GPIO_MODE_AF_OD))
            {
                /* Configure Alternate function mapped with the current IO */
                temp = m_gpio->AFR[position >> 3U];
                temp &= ~((uint32_t)0xFU << ((uint32_t)(position & (uint32_t)0x07U) * 4U)) ;
                temp |= ((uint32_t)(pin_alt) << (((uint32_t)position & (uint32_t)0x07U) * 4U));
                m_gpio->AFR[position >> 3U] = temp;
            }

            /* Configure IO Direction mode (Input, Output, Alternate or Analog) */
            temp = m_gpio->MODER;
            temp &= ~(GPIO_MODER_MODER0 << (position * 2U));
            temp |= ((pin_mode & GPIO_MODE) << (position * 2U));
            m_gpio->MODER = temp;

            /* In case of Output or Alternate function mode selection */
            if ((pin_mode == GPIO_MODE_OUTPUT_PP) || (pin_mode == GPIO_MODE_AF_PP) ||
                (pin_mode == GPIO_MODE_OUTPUT_OD) || (pin_mode == GPIO_MODE_AF_OD))
            {
                /* Configure the IO Speed */
                temp = m_gpio->OSPEEDR;
                temp &= ~(GPIO_OSPEEDER_OSPEEDR0 << (position * 2U));
                temp |= (pin_speed << (position * 2U));
                m_gpio->OSPEEDR = temp;

                /* Configure the IO Output Type */
                temp = m_gpio->OTYPER;
                temp &= ~(GPIO_OTYPER_OT_0 << position) ;
                temp |= (((pin_mode & GPIO_OUTPUT_TYPE) >> 4U) << position);
                m_gpio->OTYPER = temp;
            }

            /* Activate the Pull-up or Pull down resistor for the current IO */
            temp = m_gpio->PUPDR;
            temp &= ~(GPIO_PUPDR_PUPDR0 << (position * 2U));
            temp |= (pin_pull << (position * 2U));
            m_gpio->PUPDR = temp;

            /*--------------------- EXTI Mode Configuration ------------------------*/
            /* Configure the External Interrupt or event for the current IO */
            if ((pin_mode & EXTI_MODE) == EXTI_MODE)
            {
                /* Enable SYSCFG Clock */
                STM32_RCC::enable_clk_SYSCFG();

                temp = SYSCFG->EXTICR[position >> 2U];
                temp &= ~(((uint32_t)0x0FU) << (4U * (position & 0x03U)));
                temp |= ((uint32_t)(GPIO_GET_INDEX(m_gpio)) << (4U * (position & 0x03U)));
                SYSCFG->EXTICR[position >> 2U] = temp;

                /* Clear EXTI line configuration */
                temp = EXTI->IMR;
                temp &= ~((uint32_t)iocurrent);
                if ((pin_mode & GPIO_MODE_IT) == GPIO_MODE_IT)
                    temp |= iocurrent;
                EXTI->IMR = temp;

                temp = EXTI->EMR;
                temp &= ~((uint32_t)iocurrent);
                if ((pin_mode & GPIO_MODE_EVT) == GPIO_MODE_EVT)
                    temp |= iocurrent;
                EXTI->EMR = temp;

                /* Clear Rising Falling edge configuration */
                temp = EXTI->RTSR;
                temp &= ~((uint32_t)iocurrent);
                if ((pin_mode & RISING_EDGE) == RISING_EDGE)
                    temp |= iocurrent;
                EXTI->RTSR = temp;

                temp = EXTI->FTSR;
                temp &= ~((uint32_t)iocurrent);
                if ((pin_mode & FALLING_EDGE) == FALLING_EDGE)
                    temp |= iocurrent;
                EXTI->FTSR = temp;
            }
        }
    }
}

void STM32_GPIO::unset_config(uint32_t pin_mask)
{
    uint32_t position;
    uint32_t ioposition = 0x00U;
    uint32_t iocurrent = 0x00U;
    uint32_t tmp = 0x00U;

    /* Configure the port pins */
    for (position = 0U; position < GPIO_NUMBER; position++)
    {
        /* Get the IO position */
        ioposition = ((uint32_t)0x01U) << position;
        /* Get the current IO position */
        iocurrent = (pin_mask) & ioposition;

        if (iocurrent == ioposition)
        {
            /*------------------------- GPIO Mode Configuration --------------------*/
            /* Configure IO Direction in Input Floating Mode */
            m_gpio->MODER &= ~(GPIO_MODER_MODER0 << (position * 2U));

            /* Configure the default Alternate Function in current IO */
            m_gpio->AFR[position >> 3U] &= ~((uint32_t)0xFU << ((uint32_t)(position & (uint32_t)0x07U) * 4U)) ;

            /* Configure the default value for IO Speed */
            m_gpio->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 << (position * 2U));

            /* Configure the default value IO Output Type */
            m_gpio->OTYPER  &= ~(GPIO_OTYPER_OT_0 << position) ;

            /* Deactivate the Pull-up and Pull-down resistor for the current IO */
            m_gpio->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << (position * 2U));

            /*------------------------- EXTI Mode Configuration --------------------*/
            tmp = SYSCFG->EXTICR[position >> 2U];
            tmp &= (((uint32_t)0x0FU) << (4U * (position & 0x03U)));
            if(tmp == ((uint32_t)(GPIO_GET_INDEX(m_gpio)) << (4U * (position & 0x03U))))
            {
                /* Configure the External Interrupt or event for the current IO */
                tmp = ((uint32_t)0x0FU) << (4U * (position & 0x03U));
                SYSCFG->EXTICR[position >> 2U] &= ~tmp;

                /* Clear EXTI line configuration */
                EXTI->IMR &= ~((uint32_t)iocurrent);
                EXTI->EMR &= ~((uint32_t)iocurrent);

                /* Clear Rising Falling edge configuration */
                EXTI->RTSR &= ~((uint32_t)iocurrent);
                EXTI->FTSR &= ~((uint32_t)iocurrent);
            }
        }
    }
}

uint32_t STM32_GPIO::pin_lock(uint32_t pin)
{
    __IO uint32_t tmp = GPIO_LCKR_LCKK;
    tmp |= pin;
    m_gpio->LCKR = tmp;
    m_gpio->LCKR = pin;
    m_gpio->LCKR = tmp;
    tmp = m_gpio->LCKR;
    if ((m_gpio->LCKR & GPIO_LCKR_LCKK) != RESET)
        return STM32_RESULT_OK;
    else
        return STM32_RESULT_FAIL;
}

void STM32_GPIO::EXTI_IRQ_Handler(uint32_t pin)
{
    STM32_GPIO::EXTI_clear_IT(pin);
    EXTI_cb(pin);
}

STM32_GPIO gpioa;
STM32_GPIO gpiob;
STM32_GPIO gpioc;
STM32_GPIO gpiod;
STM32_GPIO gpioe;
STM32_GPIO gpiof;
STM32_GPIO gpiog;
STM32_GPIO gpioh;
STM32_GPIO gpioi;

__attribute__((weak)) void EXTI_cb(uint32_t pin)
{
    UNUSED(pin);
}

#ifdef STM32_USE_EXTI0
/*void ISR::EXTI0_IRQ()
{
    STM32_GPIO::EXTI_clear_IT(GPIO_PIN_0);
    EXTI_cb(GPIO_PIN_0);
}*/
#endif

#ifdef STM32_USE_EXTI1
void ISR::EXTI1_IRQ()
{
    STM32_GPIO::EXTI_clear_IT(GPIO_PIN_1);
    EXTI_cb(GPIO_PIN_1);
}
#endif

#ifdef STM32_USE_EXTI2
void ISR::EXTI2_IRQ()
{
    STM32_GPIO::EXTI_clear_IT(GPIO_PIN_2);
    EXTI_cb(GPIO_PIN_2);
}
#endif

#ifdef STM32_USE_EXTI3
void ISR::EXTI3_IRQ()
{
    STM32_GPIO::EXTI_clear_IT(GPIO_PIN_3);
    EXTI_cb(GPIO_PIN_3);
}
#endif

#ifdef STM32_USE_EXTI4
void ISR::EXTI4_IRQ()
{
    STM32_GPIO::EXTI_clear_IT(GPIO_PIN_4);
    EXTI_cb(GPIO_PIN_4);
}
#endif

#ifdef STM32_USE_EXTI9_5
void ISR::EXTI9_5_IRQ()
{
    __IO uint32_t pin_mask = STM32_GPIO::EXTI_get_IT(GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 |
                                                     GPIO_PIN_8 | GPIO_PIN_9);
    STM32_GPIO::EXTI_IRQ_Handler(pin_mask);
}
#endif

#ifdef STM32_USE_EXTI15_10
void ISR::EXTI15_10_IRQ()
{
    __IO uint32_t pin_mask = STM32_GPIO::EXTI_get_IT(GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 |
                                                     GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
    STM32_GPIO::EXTI_IRQ_Handler(pin_mask);
}
#endif
