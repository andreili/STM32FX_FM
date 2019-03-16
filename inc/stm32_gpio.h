#ifndef __STM32_GPIO__
#define __STM32_GPIO__

/*
 * Based on HAL v1.21.0(F4), v1.6.1(F1)
 * */

#include "stm32_inc.h"

class STM32_GPIO
{
public:

    enum EPin : uint16_t
    {
        PIN_0                 = 0x0001U,  /* Pin 0 selected    */
        PIN_1                 = 0x0002U,  /* Pin 1 selected    */
        PIN_2                 = 0x0004U,  /* Pin 2 selected    */
        PIN_3                 = 0x0008U,  /* Pin 3 selected    */
        PIN_4                 = 0x0010U,  /* Pin 4 selected    */
        PIN_5                 = 0x0020U,  /* Pin 5 selected    */
        PIN_6                 = 0x0040U,  /* Pin 6 selected    */
        PIN_7                 = 0x0080U,  /* Pin 7 selected    */
        PIN_8                 = 0x0100U,  /* Pin 8 selected    */
        PIN_9                 = 0x0200U,  /* Pin 9 selected    */
        PIN_10                = 0x0400U,  /* Pin 10 selected   */
        PIN_11                = 0x0800U,  /* Pin 11 selected   */
        PIN_12                = 0x1000U,  /* Pin 12 selected   */
        PIN_13                = 0x2000U,  /* Pin 13 selected   */
        PIN_14                = 0x4000U,  /* Pin 14 selected   */
        PIN_15                = 0x8000U,  /* Pin 15 selected   */
        PIN_All               = 0xFFFFU,  /* All pins selected */
    };

    enum class EMode: uint32_t
    {
        INPUT                        = 0x00000000U,   /*!< Input Floating Mode                   */
        OUTPUT_PP                    = 0x00000001U,   /*!< Output Push Pull Mode                 */
        OUTPUT_OD                    = 0x00000011U,   /*!< Output Open Drain Mode                */
        AF_PP                        = 0x00000002U,   /*!< Alternate Function Push Pull Mode     */
        AF_OD                        = 0x00000012U,   /*!< Alternate Function Open Drain Mode    */
        ANALOG                       = 0x00000003U,   /*!< Analog Mode  */
        IT_RISING                    = 0x10110000U,   /*!< External Interrupt Mode with Rising edge trigger detection          */
        IT_FALLING                   = 0x10210000U,   /*!< External Interrupt Mode with Falling edge trigger detection         */
        IT_RISING_FALLING            = 0x10310000U,   /*!< External Interrupt Mode with Rising/Falling edge trigger detection  */
        EVT_RISING                   = 0x10120000U,   /*!< External Event Mode with Rising edge trigger detection               */
        EVT_FALLING                  = 0x10220000U,   /*!< External Event Mode with Falling edge trigger detection              */
        EVT_RISING_FALLING           = 0x10320000U,   /*!< External Event Mode with Rising/Falling edge trigger detection       */
    };

    enum class ESpeed: uint32_t
    {
    #if defined (STM32F1)
        LOW         = 0x00000001U,  /*!< IO works at 10 MHz, please refer to the product datasheet */
        MEDIUM      = 0x00000002U,  /*!< range 10 MHz to 20 MHz, please refer to the product datasheet */
        HIGH        = 0x00000003U,  /*!< range 20 MHz to 50 MHz, please refer to the product datasheet  */
    #elif defined(STM32F4)
        LOW          = 0x00000000U,  /*!< IO works at 2 MHz, please refer to the product datasheet */
        MEDIUM       = 0x00000001U,  /*!< range 12,5 MHz to 50 MHz, please refer to the product datasheet */
        HIGH         = 0x00000002U,  /*!< range 25 MHz to 100 MHz, please refer to the product datasheet  */
        VERY_HIGH    = 0x00000003U,  /*!< range 50 MHz to 200 MHz, please refer to the product datasheet  */
    #endif
    };

    enum class EPull: uint32_t
    {
        NOPULL        = 0x00000000U,   /*!< No Pull-up or Pull-down activation  */
        PULLUP        = 0x00000001U,   /*!< Pull-up activation                  */
        PULLDOWN      = 0x00000002U,   /*!< Pull-down activation                */
    };


    /** @defgroup GPIO_Alternate_function_selection GPIO Alternate Function Selection
      * @{
      */

    #if defined(STM32F429xx) || defined(STM32F439xx)
    /**
      * @brief   AF 0 selection
      */
    #define GPIO_AF0_RTC_50Hz      0x00U  /* RTC_50Hz Alternate Function mapping                       */
    #define GPIO_AF0_MCO           0x00U  /* MCO (MCO1 and MCO2) Alternate Function mapping            */
    #define GPIO_AF0_TAMPER        0x00U  /* TAMPER (TAMPER_1 and TAMPER_2) Alternate Function mapping */
    #define GPIO_AF0_SWJ           0x00U  /* SWJ (SWD and JTAG) Alternate Function mapping             */
    #define GPIO_AF0_TRACE         0x00U  /* TRACE Alternate Function mapping                          */

    /**
      * @brief   AF 1 selection
      */
    #define GPIO_AF1_TIM1          0x01U  /* TIM1 Alternate Function mapping */
    #define GPIO_AF1_TIM2          0x01U  /* TIM2 Alternate Function mapping */

    /**
      * @brief   AF 2 selection
      */
    #define GPIO_AF2_TIM3          0x02U  /* TIM3 Alternate Function mapping */
    #define GPIO_AF2_TIM4          0x02U  /* TIM4 Alternate Function mapping */
    #define GPIO_AF2_TIM5          0x02U  /* TIM5 Alternate Function mapping */

    /**
      * @brief   AF 3 selection
      */
    #define GPIO_AF3_TIM8          0x03U  /* TIM8 Alternate Function mapping  */
    #define GPIO_AF3_TIM9          0x03U  /* TIM9 Alternate Function mapping  */
    #define GPIO_AF3_TIM10         0x03U  /* TIM10 Alternate Function mapping */
    #define GPIO_AF3_TIM11         0x03U  /* TIM11 Alternate Function mapping */

    /**
      * @brief   AF 4 selection
      */
    #define GPIO_AF4_I2C1          0x04U  /* I2C1 Alternate Function mapping */
    #define GPIO_AF4_I2C2          0x04U  /* I2C2 Alternate Function mapping */
    #define GPIO_AF4_I2C3          0x04U  /* I2C3 Alternate Function mapping */

    /**
      * @brief   AF 5 selection
      */
    #define GPIO_AF5_SPI1          0x05U  /* SPI1 Alternate Function mapping        */
    #define GPIO_AF5_SPI2          0x05U  /* SPI2/I2S2 Alternate Function mapping   */
    #define GPIO_AF5_SPI3          0x05U  /* SPI3/I2S3 Alternate Function mapping   */
    #define GPIO_AF5_SPI4          0x05U  /* SPI4 Alternate Function mapping        */
    #define GPIO_AF5_SPI5          0x05U  /* SPI5 Alternate Function mapping        */
    #define GPIO_AF5_SPI6          0x05U  /* SPI6 Alternate Function mapping        */
    #define GPIO_AF5_I2S3ext       0x05U  /* I2S3ext_SD Alternate Function mapping  */

    /**
      * @brief   AF 6 selection
      */
    #define GPIO_AF6_SPI3          0x06U  /* SPI3/I2S3 Alternate Function mapping  */
    #define GPIO_AF6_I2S2ext       0x06U  /* I2S2ext_SD Alternate Function mapping */
    #define GPIO_AF6_SAI1          0x06U  /* SAI1 Alternate Function mapping       */

    /**
      * @brief   AF 7 selection
      */
    #define GPIO_AF7_USART1        0x07U  /* USART1 Alternate Function mapping     */
    #define GPIO_AF7_USART2        0x07U  /* USART2 Alternate Function mapping     */
    #define GPIO_AF7_USART3        0x07U  /* USART3 Alternate Function mapping     */
    #define GPIO_AF7_I2S3ext       0x07U  /* I2S3ext_SD Alternate Function mapping */

    /**
      * @brief   AF 8 selection
      */
    #define GPIO_AF8_UART4         0x08U  /* UART4 Alternate Function mapping  */
    #define GPIO_AF8_UART5         0x08U  /* UART5 Alternate Function mapping  */
    #define GPIO_AF8_USART6        0x08U  /* USART6 Alternate Function mapping */
    #define GPIO_AF8_UART7         0x08U  /* UART7 Alternate Function mapping  */
    #define GPIO_AF8_UART8         0x08U  /* UART8 Alternate Function mapping  */

    /**
      * @brief   AF 9 selection
      */
    #define GPIO_AF9_CAN1          0x09U  /* CAN1 Alternate Function mapping    */
    #define GPIO_AF9_CAN2          0x09U  /* CAN2 Alternate Function mapping    */
    #define GPIO_AF9_TIM12         0x09U  /* TIM12 Alternate Function mapping   */
    #define GPIO_AF9_TIM13         0x09U  /* TIM13 Alternate Function mapping   */
    #define GPIO_AF9_TIM14         0x09U  /* TIM14 Alternate Function mapping   */
    #define GPIO_AF9_LTDC          0x09U  /* LCD-TFT Alternate Function mapping */

    /**
      * @brief   AF 10 selection
      */
    #define GPIO_AF10_OTG_FS        0x0AU  /* OTG_FS Alternate Function mapping */
    #define GPIO_AF10_OTG_HS        0x0AU  /* OTG_HS Alternate Function mapping */

    /**
      * @brief   AF 11 selection
      */
    #define GPIO_AF11_ETH           0x0BU  /* ETHERNET Alternate Function mapping */

    /**
      * @brief   AF 12 selection
      */
    #define GPIO_AF12_FMC           0x0CU  /* FMC Alternate Function mapping                      */
    #define GPIO_AF12_OTG_HS_FS     0x0CU  /* OTG HS configured in FS, Alternate Function mapping */
    #define GPIO_AF12_SDIO          0x0CU  /* SDIO Alternate Function mapping                     */

    /**
      * @brief   AF 13 selection
      */
    #define GPIO_AF13_DCMI          0x0DU  /* DCMI Alternate Function mapping */

    /**
      * @brief   AF 14 selection
      */
    #define GPIO_AF14_LTDC          0x0EU  /* LCD-TFT Alternate Function mapping */

    /**
      * @brief   AF 15 selection
      */
    #define GPIO_AF15_EVENTOUT      0x0FU  /* EVENTOUT Alternate Function mapping */
    #endif

    #if defined(STM32F407xx) || defined(STM32F417xx)
    /**
      * @brief   AF 0 selection
      */
    #define GPIO_AF0_RTC_50Hz      0x00  /* RTC_50Hz Alternate Function mapping                       */
    #define GPIO_AF0_MCO           0x00  /* MCO (MCO1 and MCO2) Alternate Function mapping            */
    #define GPIO_AF0_TAMPER        0x00  /* TAMPER (TAMPER_1 and TAMPER_2) Alternate Function mapping */
    #define GPIO_AF0_SWJ           0x00  /* SWJ (SWD and JTAG) Alternate Function mapping             */
    #define GPIO_AF0_TRACE         0x00  /* TRACE Alternate Function mapping                          */

    /**
      * @brief   AF 1 selection
      */
    #define GPIO_AF1_TIM1          0x01  /* TIM1 Alternate Function mapping */
    #define GPIO_AF1_TIM2          0x01  /* TIM2 Alternate Function mapping */

    /**
      * @brief   AF 2 selection
      */
    #define GPIO_AF2_TIM3          0x02  /* TIM3 Alternate Function mapping */
    #define GPIO_AF2_TIM4          0x02  /* TIM4 Alternate Function mapping */
    #define GPIO_AF2_TIM5          0x02  /* TIM5 Alternate Function mapping */

    /**
      * @brief   AF 3 selection
      */
    #define GPIO_AF3_TIM8          0x03  /* TIM8 Alternate Function mapping  */
    #define GPIO_AF3_TIM9          0x03  /* TIM9 Alternate Function mapping  */
    #define GPIO_AF3_TIM10         0x03  /* TIM10 Alternate Function mapping */
    #define GPIO_AF3_TIM11         0x03  /* TIM11 Alternate Function mapping */

    /**
      * @brief   AF 4 selection
      */
    #define GPIO_AF4_I2C1          0x04  /* I2C1 Alternate Function mapping */
    #define GPIO_AF4_I2C2          0x04  /* I2C2 Alternate Function mapping */
    #define GPIO_AF4_I2C3          0x04  /* I2C3 Alternate Function mapping */

    /**
      * @brief   AF 5 selection
      */
    #define GPIO_AF5_SPI1          0x05  /* SPI1 Alternate Function mapping        */
    #define GPIO_AF5_SPI2          0x05  /* SPI2/I2S2 Alternate Function mapping   */
    #define GPIO_AF5_I2S3ext       0x05  /* I2S3ext_SD Alternate Function mapping  */

    /**
      * @brief   AF 6 selection
      */
    #define GPIO_AF6_SPI3          0x06  /* SPI3/I2S3 Alternate Function mapping  */
    #define GPIO_AF6_I2S2ext       0x06  /* I2S2ext_SD Alternate Function mapping */

    /**
      * @brief   AF 7 selection
      */
    #define GPIO_AF7_USART1        0x07  /* USART1 Alternate Function mapping     */
    #define GPIO_AF7_USART2        0x07  /* USART2 Alternate Function mapping     */
    #define GPIO_AF7_USART3        0x07  /* USART3 Alternate Function mapping     */
    #define GPIO_AF7_I2S3ext       0x07  /* I2S3ext_SD Alternate Function mapping */

    /**
      * @brief   AF 8 selection
      */
    #define GPIO_AF8_UART4         0x08  /* UART4 Alternate Function mapping  */
    #define GPIO_AF8_UART5         0x08  /* UART5 Alternate Function mapping  */
    #define GPIO_AF8_USART6        0x08  /* USART6 Alternate Function mapping */

    /**
      * @brief   AF 9 selection
      */
    #define GPIO_AF9_CAN1          0x09  /* CAN1 Alternate Function mapping  */
    #define GPIO_AF9_CAN2          0x09  /* CAN2 Alternate Function mapping  */
    #define GPIO_AF9_TIM12         0x09  /* TIM12 Alternate Function mapping */
    #define GPIO_AF9_TIM13         0x09  /* TIM13 Alternate Function mapping */
    #define GPIO_AF9_TIM14         0x09  /* TIM14 Alternate Function mapping */

    /**
      * @brief   AF 10 selection
      */
    #define GPIO_AF10_OTG_FS        0x0A  /* OTG_FS Alternate Function mapping */
    #define GPIO_AF10_OTG_HS        0x0A  /* OTG_HS Alternate Function mapping */

    /**
      * @brief   AF 11 selection
      */
    #define GPIO_AF11_ETH           0x0B  /* ETHERNET Alternate Function mapping */

    /**
      * @brief   AF 12 selection
      */
    #define GPIO_AF12_FSMC          0x0C  /* FSMC Alternate Function mapping                     */
    #define GPIO_AF12_OTG_HS_FS     0x0C  /* OTG HS configured in FS, Alternate Function mapping */
    #define GPIO_AF12_SDIO          0x0C  /* SDIO Alternate Function mapping                     */

    /**
      * @brief   AF 13 selection
      */
    #define GPIO_AF13_DCMI          0x0D  /* DCMI Alternate Function mapping */

    /**
      * @brief   AF 15 selection
      */
    #define GPIO_AF15_EVENTOUT      0x0F  /* EVENTOUT Alternate Function mapping */
    #endif

    static void init_all();

    void set_config(uint32_t pin_mask, EMode pin_mode, uint32_t pin_alt, ESpeed pin_speed, EPull pin_pull);
    void unset_config(uint32_t pin_mask);

    inline void pin_ON(uint32_t pin_mask) { m_gpio->BSRR = pin_mask; }
    inline void pin_OFF(uint32_t pin_mask) { m_gpio->BSRR = (pin_mask << GPIO_BSRR_BR0_Pos); }

    inline bool pin_read(uint32_t pin) { return ((m_gpio->IDR & pin) == pin); }
    inline uint32_t pins_read(uint32_t pin) { return (m_gpio->IDR & pin); }
    inline void pins_write(uint32_t data) { m_gpio->ODR = data; }
    inline void pin_toggle(uint32_t pin) { m_gpio->ODR ^= pin; }
    uint32_t pin_lock(uint32_t pin);

    static inline bool EXTI_get_IT(uint32_t line) { return EXTI->PR & line; }
    static inline void EXTI_clear_IT(uint32_t line) { EXTI->PR = line; }
    static inline void EXTI_generate_swit(uint32_t line) { EXTI->SWIER |= line; }
    static inline void EXTI_IRQ_Handler(uint32_t pin);
private:
    GPIO_TypeDef*   m_gpio;

    inline void init(uint32_t base_addr);
};

void EXTI_cb(uint32_t pin);

extern STM32_GPIO gpioa;
extern STM32_GPIO gpiob;
extern STM32_GPIO gpioc;
extern STM32_GPIO gpiod;
extern STM32_GPIO gpioe;
extern STM32_GPIO gpiof;
extern STM32_GPIO gpiog;
extern STM32_GPIO gpioh;
extern STM32_GPIO gpioi;

#endif
