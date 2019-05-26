#include "stm32_inc.h"

#define GPIO_MODE             0x00000003U
#define EXTI_MODE             0x10000000U
#define GPIO_MODE_IT          0x00010000U
#define GPIO_MODE_EVT         0x00020000U
#define RISING_EDGE           0x00100000U
#define FALLING_EDGE          0x00200000U
#define GPIO_OUTPUT_TYPE      0x00000010U

#define GPIO_NUMBER           16U

#ifdef STM32F1
/* Definitions for bit manipulation of CRL and CRH register */
#define  GPIO_CR_MODE_INPUT         0x00000000U /*!< 00: Input mode (reset state)  */
#define  GPIO_CR_CNF_ANALOG         0x00000000U /*!< 00: Analog mode  */
#define  GPIO_CR_CNF_INPUT_FLOATING 0x00000004U /*!< 01: Floating input (reset state)  */
#define  GPIO_CR_CNF_INPUT_PU_PD    0x00000008U /*!< 10: Input with pull-up / pull-down  */
#define  GPIO_CR_CNF_GP_OUTPUT_PP   0x00000000U /*!< 00: General purpose output push-pull  */
#define  GPIO_CR_CNF_GP_OUTPUT_OD   0x00000004U /*!< 01: General purpose output Open-drain  */
#define  GPIO_CR_CNF_AF_OUTPUT_PP   0x00000008U /*!< 10: Alternate function output Push-pull  */
#define  GPIO_CR_CNF_AF_OUTPUT_OD   0x0000000CU /*!< 11: Alternate function output Open-drain  */
#endif

void STM32_GPIO::init_all()
{
    gpioa.m_gpio = reinterpret_cast<GPIO_TypeDef*>(GPIOA_BASE);
    gpiob.m_gpio = reinterpret_cast<GPIO_TypeDef*>(GPIOB_BASE);
    gpioc.m_gpio = reinterpret_cast<GPIO_TypeDef*>(GPIOC_BASE);
    gpiod.m_gpio = reinterpret_cast<GPIO_TypeDef*>(GPIOD_BASE);
    gpioe.m_gpio = reinterpret_cast<GPIO_TypeDef*>(GPIOE_BASE);

    /*gpioa.set_config(STM32_GPIO::PIN_All & (~(STM32_GPIO::PIN_13 | STM32_GPIO::PIN_14)), STM32_GPIO::EMode::INPUT, EAF::NONE, STM32_GPIO::ESpeed::LOW, STM32_GPIO::EPull::NOPULL);
    gpiob.set_config(STM32_GPIO::PIN_All, STM32_GPIO::EMode::INPUT, EAF::NONE, STM32_GPIO::ESpeed::LOW, STM32_GPIO::EPull::NOPULL);
    gpioc.set_config(STM32_GPIO::PIN_All, STM32_GPIO::EMode::INPUT, EAF::NONE, STM32_GPIO::ESpeed::LOW, STM32_GPIO::EPull::NOPULL);
    gpiod.set_config(STM32_GPIO::PIN_All, STM32_GPIO::EMode::INPUT, EAF::NONE, STM32_GPIO::ESpeed::LOW, STM32_GPIO::EPull::NOPULL);
    gpioe.set_config(STM32_GPIO::PIN_All, STM32_GPIO::EMode::INPUT, EAF::NONE, STM32_GPIO::ESpeed::LOW, STM32_GPIO::EPull::NOPULL);*/
    #ifdef GPIOF_BASE
    gpiof.m_gpio = reinterpret_cast<GPIO_TypeDef*>(GPIOF_BASE);
    gpiog.m_gpio = reinterpret_cast<GPIO_TypeDef*>(GPIOG_BASE);
    gpioh.m_gpio = reinterpret_cast<GPIO_TypeDef*>(GPIOH_BASE);
    gpioi.m_gpio = reinterpret_cast<GPIO_TypeDef*>(GPIOI_BASE);
    #endif
}

void STM32_GPIO::set_config(uint32_t pin_mask, EMode pin_mode, EAF pin_alt, ESpeed pin_speed, EPull pin_pull)
{
    uint32_t position;
    uint32_t ioposition = 0x01U;
    uint32_t temp = 0x00U;
    #if defined(STM32F1)
    uint32_t config = 0x00U;
    __IO uint32_t *configregister;
    uint32_t registeroffset;
    #endif

    /* Configure the port pins */
    for (position = 0U; position < GPIO_NUMBER; position++)
    {
        if ((pin_mask & ioposition) != 0)
        {
            #if defined(STM32F1)
            switch (pin_mode)
            {
                case EModeOUTPUT_PP:
                    config = pin_speed | GPIO_CR_CNF_GP_OUTPUT_PP;
                    break;
                case EModeOUTPUT_OD:
                    config = pin_speed | GPIO_CR_CNF_GP_OUTPUT_OD;
                    break;
                case EModeAF_PP:
                    config = pin_speed | GPIO_CR_CNF_AF_OUTPUT_PP;
                    break;
                case EModeAF_OD:
                    config = pin_speed | GPIO_CR_CNF_AF_OUTPUT_OD;
                    break;
                case EModeINPUT:
                case EModeIT_RISING:
                case EModeIT_FALLING:
                case EModeIT_RISING_FALLING:
                case EModeEVT_RISING:
                case EModeEVT_FALLING:
                case EModeEVT_RISING_FALLING:
                    if (pin_pull == EPull::NOPULL)
                        config = GPIO_CR_MODE_INPUT | GPIO_CR_CNF_INPUT_FLOATING;
                    else if (pin_pull == EPull::PULLUP)
                    {
                        config = GPIO_CR_MODE_INPUT | GPIO_CR_CNF_INPUT_PU_PD;
                        m_gpio->BSRR = ioposition;
                    }
                    else
                    {
                        config = GPIO_CR_MODE_INPUT | GPIO_CR_CNF_INPUT_PU_PD;
                        m_gpio->BRR = ioposition;
                    }
                    break;
                case EMode::ANALOG:
                    config = GPIO_CR_MODE_INPUT | GPIO_CR_CNF_ANALOG;
                    break;
            }

            configregister = (iocurrent < GPIO_PIN_8) ? &m_gpio->CRL : &m_gpio->CRH;
            registeroffset = (iocurrent < GPIO_PIN_8) ? (position << 2U) : ((position - 8U) << 2U);

            MODIFY_REG((*configregister), ((GPIO_CRL_MODE0 | GPIO_CRL_CNF0) << registeroffset), (config << registeroffset));/*--------------------- EXTI Mode Configuration ------------------------*/
            /* Configure the External Interrupt or event for the current IO */
            #ifdef STM32_USE_EXTI
            if ((static_cast<uint32_t>(pin_mode) & EXTI_MODE) == EXTI_MODE)
            {
                /* Enable AFIO Clock */
                STM32_RCC::enable_clk_AFIO();
                temp = AFIO->EXTICR[position >> 2U];
                CLEAR_BIT(temp, (0x0FU) << (4U * (position & 0x03U)));
                SET_BIT(temp, (GPIO_GET_INDEX(m_gpio)) << (4U * (position & 0x03U)));
                AFIO->EXTICR[position >> 2U] = temp;


                /* Configure the interrupt mask */
                if ((static_cast<uint32_t>(pin_mode) & GPIO_MODE_IT) == GPIO_MODE_IT)
                    SET_BIT(EXTI->IMR, iocurrent);
                else
                    CLEAR_BIT(EXTI->IMR, iocurrent);

                /* Configure the event mask */
                if ((static_cast<uint32_t>(pin_mode) & GPIO_MODE_EVT) == GPIO_MODE_EVT)
                    SET_BIT(EXTI->EMR, iocurrent);
                else
                    CLEAR_BIT(EXTI->EMR, iocurrent);

                /* Enable or disable the rising trigger */
                if ((static_cast<uint32_t>(pin_mode) & RISING_EDGE) == RISING_EDGE)
                    SET_BIT(EXTI->RTSR, iocurrent);
                else
                    CLEAR_BIT(EXTI->RTSR, iocurrent);

                /* Enable or disable the falling trigger */
                if ((static_cast<uint32_t>(pin_mode) & FALLING_EDGE) == FALLING_EDGE)
                    SET_BIT(EXTI->FTSR, iocurrent);
                else
                    CLEAR_BIT(EXTI->FTSR, iocurrent);
            }
            #endif //STM32_USE_EXTI
            #elif defined(STM32F4)
            /*--------------------- GPIO Mode Configuration ------------------------*/
            /* In case of Alternate function mode selection */
            if ((pin_mode == EMode::AF_PP) || (pin_mode == EMode::AF_OD))
            {
                /* Configure Alternate function mapped with the current IO */
                temp = m_gpio->AFR[position >> 3U];
                temp &= ~(0xFU << ((position & 0x07U) * 4U)) ;
                temp |= (uint32_t(pin_alt) << ((position & 0x07U) * 4U));
                m_gpio->AFR[position >> 3U] = temp;
            }

            /* Configure IO Direction mode (Input, Output, Alternate or Analog) */
            temp = m_gpio->MODER;
            temp &= ~(GPIO_MODER_MODER0 << (position * 2U));
            temp |= ((static_cast<uint32_t>(pin_mode) & GPIO_MODE) << (position * 2U));
            m_gpio->MODER = temp;

            /* In case of Output or Alternate function mode selection */
            if ((pin_mode == EMode::OUTPUT_PP) || (pin_mode == EMode::AF_PP) ||
                (pin_mode == EMode::OUTPUT_OD) || (pin_mode == EMode::AF_OD))
            {
                /* Configure the IO Speed */
                temp = m_gpio->OSPEEDR;
                temp &= ~(GPIO_OSPEEDER_OSPEEDR0 << (position * 2U));
                temp |= (static_cast<uint32_t>(pin_speed) << (position * 2U));
                m_gpio->OSPEEDR = temp;

                /* Configure the IO Output Type */
                temp = m_gpio->OTYPER;
                temp &= ~(GPIO_OTYPER_OT_0 << position) ;
                temp |= (((static_cast<uint32_t>(pin_mode) & GPIO_OUTPUT_TYPE) >> 4U) << position);
                m_gpio->OTYPER = temp;
            }

            /* Activate the Pull-up or Pull down resistor for the current IO */
            temp = m_gpio->PUPDR;
            temp &= ~(GPIO_PUPDR_PUPDR0 << (position * 2U));
            temp |= (static_cast<uint32_t>(pin_pull) << (position * 2U));
            m_gpio->PUPDR = temp;

            /*--------------------- EXTI Mode Configuration ------------------------*/
            /* Configure the External Interrupt or event for the current IO */
            #ifdef STM32_USE_EXTI
            if ((static_cast<uint32_t>(pin_mode) & EXTI_MODE) == EXTI_MODE)
            {
                /* Enable SYSCFG Clock */
                STM32_RCC::enable_clk_SYSCFG();

                temp = SYSCFG->EXTICR[position >> 2U];
                temp &= ~(0x0FU << (4U * (position & 0x03U)));
                temp |= GPIO_GET_INDEX(m_gpio) << (4U * (position & 0x03U));
                SYSCFG->EXTICR[position >> 2U] = temp;

                /* Clear EXTI line configuration */
                temp = EXTI->IMR;
                temp &= ~iocurrent;
                if ((static_cast<uint32_t>(pin_mode) & GPIO_MODE_IT) == GPIO_MODE_IT)
                    temp |= iocurrent;
                EXTI->IMR = temp;

                temp = EXTI->EMR;
                temp &= ~iocurrent;
                if ((static_cast<uint32_t>(pin_mode) & GPIO_MODE_EVT) == GPIO_MODE_EVT)
                    temp |= iocurrent;
                EXTI->EMR = temp;

                /* Clear Rising Falling edge configuration */
                temp = EXTI->RTSR;
                temp &= ~iocurrent;
                if ((static_cast<uint32_t>(pin_mode) & RISING_EDGE) == RISING_EDGE)
                    temp |= iocurrent;
                EXTI->RTSR = temp;

                temp = EXTI->FTSR;
                temp &= ~iocurrent;
                if ((static_cast<uint32_t>(pin_mode) & FALLING_EDGE) == FALLING_EDGE)
                    temp |= iocurrent;
                EXTI->FTSR = temp;
            }
            #endif //STM32_USE_EXTI
            #endif //STM32F4
        }

        ioposition <<= 1;
    }
}

void STM32_GPIO::unset_config(uint32_t pin_mask)
{
    uint32_t position;
    uint32_t ioposition = 0x00U;
    uint32_t iocurrent = 0x00U;
    #if defined(STM32F1)
    uint32_t tmp = 0x00U;
    uint32_t config = 0x00U;
    __IO uint32_t *configregister;
    uint32_t registeroffset;
    #endif

    /* Configure the port pins */
    for (position = 0U; position < GPIO_NUMBER; position++)
    {
        /* Get the IO position */
        ioposition = 0x01U << position;
        /* Get the current IO position */
        iocurrent = (pin_mask) & ioposition;

        if (iocurrent == ioposition)
        {
            #if defined(STM32F1)
            /*------------------------- GPIO Mode Configuration --------------------*/
            /* Check if the current bit belongs to first half or last half of the pin count number
             in order to address CRH or CRL register */
            configregister = (iocurrent < GPIO_PIN_8) ? &m_gpio->CRL     : &m_gpio->CRH;
            registeroffset = (iocurrent < GPIO_PIN_8) ? (position << 2U) : ((position - 8U) << 2U);

            /* CRL/CRH default value is floating input(0x04) shifted to correct position */
            MODIFY_REG(*configregister, ((GPIO_CRL_MODE0 | GPIO_CRL_CNF0) << registeroffset), GPIO_CRL_CNF0_0 << registeroffset);

            /* ODR default value is 0 */
            CLEAR_BIT(m_gpio->ODR, iocurrent);

            /*------------------------- EXTI Mode Configuration --------------------*/
            /* Clear the External Interrupt or Event for the current IO */

            #ifdef STM32_USE_EXTI
            tmp = AFIO->EXTICR[position >> 2U];
            tmp &= 0x0FU << (4U * (position & 0x03U));
            if (tmp == (GPIO_GET_INDEX(m_gpio) << (4U * (position & 0x03U))))
            {
                tmp = 0x0FU << (4U * (position & 0x03U));
                CLEAR_BIT(AFIO->EXTICR[position >> 2U], tmp);

                /* Clear EXTI line configuration */
                CLEAR_BIT(EXTI->IMR, (uint32_t)iocurrent);
                CLEAR_BIT(EXTI->EMR, (uint32_t)iocurrent);

                /* Clear Rising Falling edge configuration */
                CLEAR_BIT(EXTI->RTSR, (uint32_t)iocurrent);
                CLEAR_BIT(EXTI->FTSR, (uint32_t)iocurrent);
            }
            #endif //STM32_USE_EXTI
            #elif defined(STM32F4)
            /*------------------------- GPIO Mode Configuration --------------------*/
            /* Configure IO Direction in Input Floating Mode */
            m_gpio->MODER &= ~(GPIO_MODER_MODER0 << (position * 2U));

            /* Configure the default Alternate Function in current IO */
            m_gpio->AFR[position >> 3U] &= ~(0xFU << ((position & 0x07U) * 4U)) ;

            /* Configure the default value for IO Speed */
            m_gpio->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 << (position * 2U));

            /* Configure the default value IO Output Type */
            m_gpio->OTYPER  &= ~(GPIO_OTYPER_OT_0 << position) ;

            /* Deactivate the Pull-up and Pull-down resistor for the current IO */
            m_gpio->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << (position * 2U));

            /*------------------------- EXTI Mode Configuration --------------------*/
            #ifdef STM32_USE_EXTI
            tmp = SYSCFG->EXTICR[position >> 2U];
            tmp &= (0x0FU << (4U * (position & 0x03U)));
            if (tmp == GPIO_GET_INDEX(m_gpio) << (4U * (position & 0x03U)))
            {
                /* Configure the External Interrupt or event for the current IO */
                tmp = 0x0FU << (4U * (position & 0x03U));
                SYSCFG->EXTICR[position >> 2U] &= ~tmp;

                /* Clear EXTI line configuration */
                EXTI->IMR &= ~iocurrent;
                EXTI->EMR &= ~iocurrent;

                /* Clear Rising Falling edge configuration */
                EXTI->RTSR &= ~iocurrent;
                EXTI->FTSR &= ~iocurrent;
            }
            #endif //STM32_USE_EXTI
            #endif //STM32F4
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
void ISR::EXTI0_IRQ()
{
    STM32_GPIO::EXTI_clear_IT(GPIO_PIN_0);
    EXTI_cb(GPIO_PIN_0);
}
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
