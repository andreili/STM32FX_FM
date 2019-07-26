#ifndef __STM32F407xx_H_
#define __STM32F407xx_H_

#include <stdint.h>

template <std::uint32_t... bitmask>
inline constexpr std::uint32_t SetBits()
{
    return (bitmask | ...);
}

#define __CM4_REV                     0x0001U
#define __MPU_PRESENT                 1U
#define __NVIC_PRIO_BITS              4U
#define __Vendor_SysTickConfig        0U
#define __FPU_PRESENT                 1U

namespace STM32_REGS
{
    enum class IRQn: std::int32_t
    {
        NonMaskableInt                 = -14,
        MemoryManagement               = -12,
        BusFault                       = -11,
        UsageFault                     = -10,
        SVCall                         = -5,
        DebugMonitor                   = -4,
        PendSV                         = -2,
        SysTick                        = -1,
        WWDG                           = 0,
        PVD                            = 1,
        TAMP_STAMP                     = 2,
        RTC_WKUP                       = 3,
        FLASH                          = 4,
        RCC                            = 5,
        EXTI0                          = 6,
        EXTI1                          = 7,
        EXTI2                          = 8,
        EXTI3                          = 9,
        EXTI4                          = 10,
        DMA1_Stream0                   = 11,
        DMA1_Stream1                   = 12,
        DMA1_Stream2                   = 13,
        DMA1_Stream3                   = 14,
        DMA1_Stream4                   = 15,
        DMA1_Stream5                   = 16,
        DMA1_Stream6                   = 17,
        ADC                            = 18,
        CAN1_TX                        = 19,
        CAN1_RX0                       = 20,
        CAN1_RX1                       = 21,
        CAN1_SCE                       = 22,
        EXTI9_5                        = 23,
        TIM1_BRK_TIM9                  = 24,
        TIM1_UP_TIM10                  = 25,
        TIM1_TRG_COM_TIM11             = 26,
        TIM1_CC                        = 27,
        TIM2                           = 28,
        TIM3                           = 29,
        TIM4                           = 30,
        I2C1_EV                        = 31,
        I2C1_ER                        = 32,
        I2C2_EV                        = 33,
        I2C2_ER                        = 34,
        SPI1                           = 35,
        SPI2                           = 36,
        USART1                         = 37,
        USART2                         = 38,
        USART3                         = 39,
        EXTI15_10                      = 40,
        RTC_Alarm                      = 41,
        OTG_FS_WKUP                    = 42,
        TIM8_BRK_TIM12                 = 43,
        TIM8_UP_TIM13                  = 44,
        TIM8_TRG_COM_TIM14             = 45,
        TIM8_CC                        = 46,
        DMA1_Stream7                   = 47,
        FSMC                           = 48,
        SDIO                           = 49,
        TIM5                           = 50,
        SPI3                           = 51,
        UART4                          = 52,
        UART5                          = 53,
        TIM6_DAC                       = 54,
        TIM7                           = 55,
        DMA2_Stream0                   = 56,
        DMA2_Stream1                   = 57,
        DMA2_Stream2                   = 58,
        DMA2_Stream3                   = 59,
        DMA2_Stream4                   = 60,
        ETH                            = 61,
        ETH_WKUP                       = 62,
        CAN2_TX                        = 63,
        CAN2_RX0                       = 64,
        CAN2_RX1                       = 65,
        CAN2_SCE                       = 66,
        OTG_FS                         = 67,
        DMA2_Stream5                   = 68,
        DMA2_Stream6                   = 69,
        DMA2_Stream7                   = 70,
        USART6                         = 71,
        I2C3_EV                        = 72,
        I2C3_ER                        = 73,
        OTG_HS_EP1_OUT                 = 74,
        OTG_HS_EP1_IN                  = 75,
        OTG_HS_WKUP                    = 76,
        OTG_HS                         = 77,
        DCMI                           = 78,
        RNG                            = 80,
        FPU                            = 81,
    };
}

//namespace ARM = STM32;

#ifdef __cplusplus
  #define   __I     volatile             /*!< Defines 'read only' permissions */
#else
  #define   __I     volatile const       /*!< Defines 'read only' permissions */
#endif
#define     __O     volatile             /*!< Defines 'write only' permissions */
#define     __IO    volatile             /*!< Defines 'read / write' permissions */

/* following defines should be used for structure members */
#define     __IM     volatile const      /*! Defines 'read only' structure member permissions */
#define     __OM     volatile            /*! Defines 'write only' structure member permissions */
#define     __IOM    volatile            /*! Defines 'read / write' structure member permissions */

//#include "core_cm4.hpp"
//#include "system_stm32f4xx.hpp"
//#include "stdint.hpp"

//namespace CORTEX = CM4;

namespace STM32
{
    static constexpr std::uint32_t FLASH_BASE                     = 0x08000000U;
    static constexpr std::uint32_t CCMDATARAM_BASE                = 0x10000000U;
    static constexpr std::uint32_t SRAM1_BASE                     = 0x20000000U;
    static constexpr std::uint32_t SRAM2_BASE                     = 0x2001C000U;
    static constexpr std::uint32_t PERIPH_BASE                    = 0x40000000U;
    static constexpr std::uint32_t BKPSRAM_BASE                   = 0x40024000U;
    static constexpr std::uint32_t FSMC_R_BASE                    = 0xA0000000U;
    static constexpr std::uint32_t SRAM1_BB_BASE                  = 0x22000000U;
    static constexpr std::uint32_t SRAM2_BB_BASE                  = 0x22380000U;
    static constexpr std::uint32_t PERIPH_BB_BASE                 = 0x42000000U;
    static constexpr std::uint32_t BKPSRAM_BB_BASE                = 0x42480000U;
    static constexpr std::uint32_t FLASH_END                      = 0x080FFFFFU;
    static constexpr std::uint32_t FLASH_OTP_BASE                 = 0x1FFF7800U;
    static constexpr std::uint32_t FLASH_OTP_END                  = 0x1FFF7A0FU;
    static constexpr std::uint32_t CCMDATARAM_END                 = 0x1000FFFFU;
    static constexpr std::uint32_t SRAM_BASE                      = SRAM1_BASE;
    static constexpr std::uint32_t SRAM_BB_BASE                   = SRAM1_BB_BASE;
    static constexpr std::uint32_t APB1PERIPH_BASE                = PERIPH_BASE;
    static constexpr std::uint32_t APB2PERIPH_BASE                = (PERIPH_BASE + 0x00010000U);
    static constexpr std::uint32_t AHB1PERIPH_BASE                = (PERIPH_BASE + 0x00020000U);
    static constexpr std::uint32_t AHB2PERIPH_BASE                = (PERIPH_BASE + 0x10000000U);
    static constexpr std::uint32_t TIM2_BASE                      = (APB1PERIPH_BASE + 0x0000U);
    static constexpr std::uint32_t TIM3_BASE                      = (APB1PERIPH_BASE + 0x0400U);
    static constexpr std::uint32_t TIM4_BASE                      = (APB1PERIPH_BASE + 0x0800U);
    static constexpr std::uint32_t TIM5_BASE                      = (APB1PERIPH_BASE + 0x0C00U);
    static constexpr std::uint32_t TIM6_BASE                      = (APB1PERIPH_BASE + 0x1000U);
    static constexpr std::uint32_t TIM7_BASE                      = (APB1PERIPH_BASE + 0x1400U);
    static constexpr std::uint32_t TIM12_BASE                     = (APB1PERIPH_BASE + 0x1800U);
    static constexpr std::uint32_t TIM13_BASE                     = (APB1PERIPH_BASE + 0x1C00U);
    static constexpr std::uint32_t TIM14_BASE                     = (APB1PERIPH_BASE + 0x2000U);
    static constexpr std::uint32_t RTC_BASE                       = (APB1PERIPH_BASE + 0x2800U);
    static constexpr std::uint32_t WWDG_BASE                      = (APB1PERIPH_BASE + 0x2C00U);
    static constexpr std::uint32_t IWDG_BASE                      = (APB1PERIPH_BASE + 0x3000U);
    static constexpr std::uint32_t I2S2ext_BASE                   = (APB1PERIPH_BASE + 0x3400U);
    static constexpr std::uint32_t SPI2_BASE                      = (APB1PERIPH_BASE + 0x3800U);
    static constexpr std::uint32_t SPI3_BASE                      = (APB1PERIPH_BASE + 0x3C00U);
    static constexpr std::uint32_t I2S3ext_BASE                   = (APB1PERIPH_BASE + 0x4000U);
    static constexpr std::uint32_t USART2_BASE                    = (APB1PERIPH_BASE + 0x4400U);
    static constexpr std::uint32_t USART3_BASE                    = (APB1PERIPH_BASE + 0x4800U);
    static constexpr std::uint32_t UART4_BASE                     = (APB1PERIPH_BASE + 0x4C00U);
    static constexpr std::uint32_t UART5_BASE                     = (APB1PERIPH_BASE + 0x5000U);
    static constexpr std::uint32_t I2C1_BASE                      = (APB1PERIPH_BASE + 0x5400U);
    static constexpr std::uint32_t I2C2_BASE                      = (APB1PERIPH_BASE + 0x5800U);
    static constexpr std::uint32_t I2C3_BASE                      = (APB1PERIPH_BASE + 0x5C00U);
    static constexpr std::uint32_t CAN1_BASE                      = (APB1PERIPH_BASE + 0x6400U);
    static constexpr std::uint32_t CAN2_BASE                      = (APB1PERIPH_BASE + 0x6800U);
    static constexpr std::uint32_t PWR_BASE                       = (APB1PERIPH_BASE + 0x7000U);
    static constexpr std::uint32_t DAC_BASE                       = (APB1PERIPH_BASE + 0x7400U);
    static constexpr std::uint32_t TIM1_BASE                      = (APB2PERIPH_BASE + 0x0000U);
    static constexpr std::uint32_t TIM8_BASE                      = (APB2PERIPH_BASE + 0x0400U);
    static constexpr std::uint32_t USART1_BASE                    = (APB2PERIPH_BASE + 0x1000U);
    static constexpr std::uint32_t USART6_BASE                    = (APB2PERIPH_BASE + 0x1400U);
    static constexpr std::uint32_t ADC1_BASE                      = (APB2PERIPH_BASE + 0x2000U);
    static constexpr std::uint32_t ADC2_BASE                      = (APB2PERIPH_BASE + 0x2100U);
    static constexpr std::uint32_t ADC3_BASE                      = (APB2PERIPH_BASE + 0x2200U);
    static constexpr std::uint32_t ADC123_COMMON_BASE             = (APB2PERIPH_BASE + 0x2300U);
    static constexpr std::uint32_t ADC_BASE                       = ADC123_COMMON_BASE;
    static constexpr std::uint32_t SDIO_BASE                      = (APB2PERIPH_BASE + 0x2C00U);
    static constexpr std::uint32_t SPI1_BASE                      = (APB2PERIPH_BASE + 0x3000U);
    static constexpr std::uint32_t SYSCFG_BASE                    = (APB2PERIPH_BASE + 0x3800U);
    static constexpr std::uint32_t EXTI_BASE                      = (APB2PERIPH_BASE + 0x3C00U);
    static constexpr std::uint32_t TIM9_BASE                      = (APB2PERIPH_BASE + 0x4000U);
    static constexpr std::uint32_t TIM10_BASE                     = (APB2PERIPH_BASE + 0x4400U);
    static constexpr std::uint32_t TIM11_BASE                     = (APB2PERIPH_BASE + 0x4800U);
    static constexpr std::uint32_t GPIOA_BASE                     = (AHB1PERIPH_BASE + 0x0000U);
    static constexpr std::uint32_t GPIOB_BASE                     = (AHB1PERIPH_BASE + 0x0400U);
    static constexpr std::uint32_t GPIOC_BASE                     = (AHB1PERIPH_BASE + 0x0800U);
    static constexpr std::uint32_t GPIOD_BASE                     = (AHB1PERIPH_BASE + 0x0C00U);
    static constexpr std::uint32_t GPIOE_BASE                     = (AHB1PERIPH_BASE + 0x1000U);
    static constexpr std::uint32_t GPIOF_BASE                     = (AHB1PERIPH_BASE + 0x1400U);
    static constexpr std::uint32_t GPIOG_BASE                     = (AHB1PERIPH_BASE + 0x1800U);
    static constexpr std::uint32_t GPIOH_BASE                     = (AHB1PERIPH_BASE + 0x1C00U);
    static constexpr std::uint32_t GPIOI_BASE                     = (AHB1PERIPH_BASE + 0x2000U);
    static constexpr std::uint32_t CRC_BASE                       = (AHB1PERIPH_BASE + 0x3000U);
    static constexpr std::uint32_t RCC_BASE                       = (AHB1PERIPH_BASE + 0x3800U);
    static constexpr std::uint32_t FLASH_R_BASE                   = (AHB1PERIPH_BASE + 0x3C00U);
    static constexpr std::uint32_t DMA1_BASE                      = (AHB1PERIPH_BASE + 0x6000U);
    static constexpr std::uint32_t DMA1_Stream0_BASE              = (DMA1_BASE + 0x010U);
    static constexpr std::uint32_t DMA1_Stream1_BASE              = (DMA1_BASE + 0x028U);
    static constexpr std::uint32_t DMA1_Stream2_BASE              = (DMA1_BASE + 0x040U);
    static constexpr std::uint32_t DMA1_Stream3_BASE              = (DMA1_BASE + 0x058U);
    static constexpr std::uint32_t DMA1_Stream4_BASE              = (DMA1_BASE + 0x070U);
    static constexpr std::uint32_t DMA1_Stream5_BASE              = (DMA1_BASE + 0x088U);
    static constexpr std::uint32_t DMA1_Stream6_BASE              = (DMA1_BASE + 0x0A0U);
    static constexpr std::uint32_t DMA1_Stream7_BASE              = (DMA1_BASE + 0x0B8U);
    static constexpr std::uint32_t DMA2_BASE                      = (AHB1PERIPH_BASE + 0x6400U);
    static constexpr std::uint32_t DMA2_Stream0_BASE              = (DMA2_BASE + 0x010U);
    static constexpr std::uint32_t DMA2_Stream1_BASE              = (DMA2_BASE + 0x028U);
    static constexpr std::uint32_t DMA2_Stream2_BASE              = (DMA2_BASE + 0x040U);
    static constexpr std::uint32_t DMA2_Stream3_BASE              = (DMA2_BASE + 0x058U);
    static constexpr std::uint32_t DMA2_Stream4_BASE              = (DMA2_BASE + 0x070U);
    static constexpr std::uint32_t DMA2_Stream5_BASE              = (DMA2_BASE + 0x088U);
    static constexpr std::uint32_t DMA2_Stream6_BASE              = (DMA2_BASE + 0x0A0U);
    static constexpr std::uint32_t DMA2_Stream7_BASE              = (DMA2_BASE + 0x0B8U);
    static constexpr std::uint32_t ETH_BASE                       = (AHB1PERIPH_BASE + 0x8000U);
    static constexpr std::uint32_t ETH_MAC_BASE                   = (ETH_BASE);
    static constexpr std::uint32_t ETH_MMC_BASE                   = (ETH_BASE + 0x0100U);
    static constexpr std::uint32_t ETH_PTP_BASE                   = (ETH_BASE + 0x0700U);
    static constexpr std::uint32_t ETH_DMA_BASE                   = (ETH_BASE + 0x1000U);
    static constexpr std::uint32_t DCMI_BASE                      = (AHB2PERIPH_BASE + 0x50000U);
    static constexpr std::uint32_t RNG_BASE                       = (AHB2PERIPH_BASE + 0x60800U);
    static constexpr std::uint32_t FSMC_Bank1_R_BASE              = (FSMC_R_BASE + 0x0000U);
    static constexpr std::uint32_t FSMC_Bank1E_R_BASE             = (FSMC_R_BASE + 0x0104U);
    static constexpr std::uint32_t FSMC_Bank2_3_R_BASE            = (FSMC_R_BASE + 0x0060U);
    static constexpr std::uint32_t FSMC_Bank4_R_BASE              = (FSMC_R_BASE + 0x00A0U);
    static constexpr std::uint32_t DBGMCU_BASE                    = 0xE0042000U;
    static constexpr std::uint32_t USB_OTG_HS_PERIPH_BASE         = 0x40040000U;
    static constexpr std::uint32_t USB_OTG_FS_PERIPH_BASE         = 0x50000000U;
    static constexpr std::uint32_t USB_OTG_GLOBAL_BASE            = 0x000U;
    static constexpr std::uint32_t USB_OTG_DEVICE_BASE            = 0x800U;
    static constexpr std::uint32_t USB_OTG_IN_ENDPOINT_BASE       = 0x900U;
    static constexpr std::uint32_t USB_OTG_OUT_ENDPOINT_BASE      = 0xB00U;
    static constexpr std::uint32_t USB_OTG_EP_REG_SIZE            = 0x20U;
    static constexpr std::uint32_t USB_OTG_HOST_BASE              = 0x400U;
    static constexpr std::uint32_t USB_OTG_HOST_PORT_BASE         = 0x440U;
    static constexpr std::uint32_t USB_OTG_HOST_CHANNEL_BASE      = 0x500U;
    static constexpr std::uint32_t USB_OTG_HOST_CHANNEL_SIZE      = 0x20U;
    static constexpr std::uint32_t USB_OTG_PCGCCTL_BASE           = 0xE00U;
    static constexpr std::uint32_t USB_OTG_FIFO_BASE              = 0x1000U;
    static constexpr std::uint32_t USB_OTG_FIFO_SIZE              = 0x1000U;
    static constexpr std::uint32_t UID_BASE                       = 0x1FFF7A10U;
    static constexpr std::uint32_t FLASHSIZE_BASE                 = 0x1FFF7A22U;
    static constexpr std::uint32_t PACKAGE_BASE                   = 0x1FFF7BF0U;
}

namespace STM32_REGS
{
    #define DAC_CHANNEL2_SUPPORT
    #define RCC_PLLI2S_SUPPORT
    #define RCC_AHB2_SUPPORT
    #define RCC_AHB3_SUPPORT
    #define RTC_TAMPER2_SUPPORT
    #define RTC_AF2_SUPPORT
    #define SPI_I2S_FULLDUPLEX_SUPPORT

    /* ADC DEFINITION */
    class ADC
    {
    private:
        struct ADC_t
        {
            __IO uint32_t                 SR;
            __IO uint32_t                 CR1;
            __IO uint32_t                 CR2;
            __IO uint32_t                 SMPR1;
            __IO uint32_t                 SMPR2;
            __IO uint32_t                 JOFR1;
            __IO uint32_t                 JOFR2;
            __IO uint32_t                 JOFR3;
            __IO uint32_t                 JOFR4;
            __IO uint32_t                 HTR;
            __IO uint32_t                 LTR;
            __IO uint32_t                 SQR1;
            __IO uint32_t                 SQR2;
            __IO uint32_t                 SQR3;
            __IO uint32_t                 JSQR;
            __IO uint32_t                 JDR1;
            __IO uint32_t                 JDR2;
            __IO uint32_t                 JDR3;
            __IO uint32_t                 JDR4;
            __IO uint32_t                 DR;
        };
    public:
        class SR
        {
        private:
            union SR_t
            {
                struct
                {
                    uint32_t AWD            : 1;
                    uint32_t EOC            : 1;
                    uint32_t JEOC           : 1;
                    uint32_t JSTRT          : 1;
                    uint32_t STRT           : 1;
                    uint32_t OVR            : 1;
                    uint32_t reserved6      : 26;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                AWD                    = (0x1U << 0),
                EOC                    = (0x1U << 1),
                JEOC                   = (0x1U << 2),
                JSTRT                  = (0x1U << 3),
                STRT                   = (0x1U << 4),
                OVR                    = (0x1U << 5),
            };
            static inline uint32_t get() { return reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SR; }
            static inline void set(uint32_t value) { reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class CR1
        {
        private:
            union CR1_t
            {
                struct
                {
                    uint32_t AWDCH          : 5;
                    uint32_t EOCIE          : 1;
                    uint32_t AWDIE          : 1;
                    uint32_t JEOCIE         : 1;
                    uint32_t SCAN           : 1;
                    uint32_t AWDSGL         : 1;
                    uint32_t JAUTO          : 1;
                    uint32_t DISCEN         : 1;
                    uint32_t JDISCEN        : 1;
                    uint32_t DISCNUM        : 3;
                    uint32_t reserved16     : 6;
                    uint32_t JAWDEN         : 1;
                    uint32_t AWDEN          : 1;
                    uint32_t RES            : 2;
                    uint32_t OVRIE          : 1;
                    uint32_t reserved27     : 5;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                AWDCH                  = (0x1FU << 0),
                EOCIE                  = (0x1U << 5),
                AWDIE                  = (0x1U << 6),
                JEOCIE                 = (0x1U << 7),
                SCAN                   = (0x1U << 8),
                AWDSGL                 = (0x1U << 9),
                JAUTO                  = (0x1U << 10),
                DISCEN                 = (0x1U << 11),
                JDISCEN                = (0x1U << 12),
                DISCNUM                = (0x7U << 13),
                JAWDEN                 = (0x1U << 22),
                AWDEN                  = (0x1U << 23),
                RES                    = (0x3U << 24),
                OVRIE                  = (0x1U << 26),
            };
            static inline uint32_t get() { return reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->CR1; }
            static inline void set(uint32_t value) { reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->CR1 = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->CR1 |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->CR1 &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->CR1 & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_AWDCH() { return reinterpret_cast<__IO CR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->CR1)->AWDCH; }
            static inline void set_AWDCH(uint32_t value) { reinterpret_cast<__IO CR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->CR1)->AWDCH = value; }
            static inline uint32_t get_DISCNUM() { return reinterpret_cast<__IO CR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->CR1)->DISCNUM; }
            static inline void set_DISCNUM(uint32_t value) { reinterpret_cast<__IO CR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->CR1)->DISCNUM = value; }
            static inline uint32_t get_RES() { return reinterpret_cast<__IO CR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->CR1)->RES; }
            static inline void set_RES(uint32_t value) { reinterpret_cast<__IO CR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->CR1)->RES = value; }
        };
        class CR2
        {
        private:
            union CR2_t
            {
                struct
                {
                    uint32_t ADON           : 1;
                    uint32_t CONT           : 1;
                    uint32_t reserved2      : 6;
                    uint32_t DMA            : 1;
                    uint32_t DDS            : 1;
                    uint32_t EOCS           : 1;
                    uint32_t ALIGN          : 1;
                    uint32_t reserved12     : 4;
                    uint32_t JEXTSEL        : 4;
                    uint32_t JEXTEN         : 2;
                    uint32_t JSWSTART       : 1;
                    uint32_t reserved23     : 1;
                    uint32_t EXTSEL         : 4;
                    uint32_t EXTEN          : 2;
                    uint32_t SWSTART        : 1;
                    uint32_t reserved31     : 1;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                ADON                   = (0x1U << 0),
                CONT                   = (0x1U << 1),
                DMA                    = (0x1U << 8),
                DDS                    = (0x1U << 9),
                EOCS                   = (0x1U << 10),
                ALIGN                  = (0x1U << 11),
                JEXTSEL                = (0xFU << 16),
                JEXTEN                 = (0x3U << 20),
                JSWSTART               = (0x1U << 22),
                EXTSEL                 = (0xFU << 24),
                EXTEN                  = (0x3U << 28),
                SWSTART                = (0x1U << 30),
            };
            static inline uint32_t get() { return reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->CR2; }
            static inline void set(uint32_t value) { reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->CR2 = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->CR2 |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->CR2 &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->CR2 & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_JEXTSEL() { return reinterpret_cast<__IO CR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->CR2)->JEXTSEL; }
            static inline void set_JEXTSEL(uint32_t value) { reinterpret_cast<__IO CR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->CR2)->JEXTSEL = value; }
            static inline uint32_t get_JEXTEN() { return reinterpret_cast<__IO CR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->CR2)->JEXTEN; }
            static inline void set_JEXTEN(uint32_t value) { reinterpret_cast<__IO CR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->CR2)->JEXTEN = value; }
            static inline uint32_t get_EXTSEL() { return reinterpret_cast<__IO CR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->CR2)->EXTSEL; }
            static inline void set_EXTSEL(uint32_t value) { reinterpret_cast<__IO CR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->CR2)->EXTSEL = value; }
            static inline uint32_t get_EXTEN() { return reinterpret_cast<__IO CR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->CR2)->EXTEN; }
            static inline void set_EXTEN(uint32_t value) { reinterpret_cast<__IO CR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->CR2)->EXTEN = value; }
        };
        class SMPR1
        {
        private:
            union SMPR1_t
            {
                struct
                {
                    uint32_t SMP10          : 3;
                    uint32_t SMP11          : 3;
                    uint32_t SMP12          : 3;
                    uint32_t SMP13          : 3;
                    uint32_t SMP14          : 3;
                    uint32_t SMP15          : 3;
                    uint32_t SMP16          : 3;
                    uint32_t SMP17          : 3;
                    uint32_t SMP18          : 3;
                    uint32_t reserved27     : 5;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                SMP10                  = (0x7U << 0),
                SMP11                  = (0x7U << 3),
                SMP12                  = (0x7U << 6),
                SMP13                  = (0x7U << 9),
                SMP14                  = (0x7U << 12),
                SMP15                  = (0x7U << 15),
                SMP16                  = (0x7U << 18),
                SMP17                  = (0x7U << 21),
                SMP18                  = (0x7U << 24),
            };
            static inline uint32_t get() { return reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR1; }
            static inline void set(uint32_t value) { reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR1 = value; }
            static inline uint32_t get_SMP10() { return reinterpret_cast<__IO SMPR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR1)->SMP10; }
            static inline void set_SMP10(uint32_t value) { reinterpret_cast<__IO SMPR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR1)->SMP10 = value; }
            static inline uint32_t get_SMP11() { return reinterpret_cast<__IO SMPR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR1)->SMP11; }
            static inline void set_SMP11(uint32_t value) { reinterpret_cast<__IO SMPR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR1)->SMP11 = value; }
            static inline uint32_t get_SMP12() { return reinterpret_cast<__IO SMPR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR1)->SMP12; }
            static inline void set_SMP12(uint32_t value) { reinterpret_cast<__IO SMPR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR1)->SMP12 = value; }
            static inline uint32_t get_SMP13() { return reinterpret_cast<__IO SMPR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR1)->SMP13; }
            static inline void set_SMP13(uint32_t value) { reinterpret_cast<__IO SMPR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR1)->SMP13 = value; }
            static inline uint32_t get_SMP14() { return reinterpret_cast<__IO SMPR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR1)->SMP14; }
            static inline void set_SMP14(uint32_t value) { reinterpret_cast<__IO SMPR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR1)->SMP14 = value; }
            static inline uint32_t get_SMP15() { return reinterpret_cast<__IO SMPR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR1)->SMP15; }
            static inline void set_SMP15(uint32_t value) { reinterpret_cast<__IO SMPR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR1)->SMP15 = value; }
            static inline uint32_t get_SMP16() { return reinterpret_cast<__IO SMPR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR1)->SMP16; }
            static inline void set_SMP16(uint32_t value) { reinterpret_cast<__IO SMPR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR1)->SMP16 = value; }
            static inline uint32_t get_SMP17() { return reinterpret_cast<__IO SMPR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR1)->SMP17; }
            static inline void set_SMP17(uint32_t value) { reinterpret_cast<__IO SMPR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR1)->SMP17 = value; }
            static inline uint32_t get_SMP18() { return reinterpret_cast<__IO SMPR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR1)->SMP18; }
            static inline void set_SMP18(uint32_t value) { reinterpret_cast<__IO SMPR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR1)->SMP18 = value; }
        };
        class SMPR2
        {
        private:
            union SMPR2_t
            {
                struct
                {
                    uint32_t SMP0           : 3;
                    uint32_t SMP1           : 3;
                    uint32_t SMP2           : 3;
                    uint32_t SMP3           : 3;
                    uint32_t SMP4           : 3;
                    uint32_t SMP5           : 3;
                    uint32_t SMP6           : 3;
                    uint32_t SMP7           : 3;
                    uint32_t SMP8           : 3;
                    uint32_t SMP9           : 3;
                    uint32_t reserved30     : 2;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                SMP0                   = (0x7U << 0),
                SMP1                   = (0x7U << 3),
                SMP2                   = (0x7U << 6),
                SMP3                   = (0x7U << 9),
                SMP4                   = (0x7U << 12),
                SMP5                   = (0x7U << 15),
                SMP6                   = (0x7U << 18),
                SMP7                   = (0x7U << 21),
                SMP8                   = (0x7U << 24),
                SMP9                   = (0x7U << 27),
            };
            static inline uint32_t get() { return reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR2; }
            static inline void set(uint32_t value) { reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR2 = value; }
            static inline uint32_t get_SMP0() { return reinterpret_cast<__IO SMPR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR2)->SMP0; }
            static inline void set_SMP0(uint32_t value) { reinterpret_cast<__IO SMPR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR2)->SMP0 = value; }
            static inline uint32_t get_SMP1() { return reinterpret_cast<__IO SMPR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR2)->SMP1; }
            static inline void set_SMP1(uint32_t value) { reinterpret_cast<__IO SMPR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR2)->SMP1 = value; }
            static inline uint32_t get_SMP2() { return reinterpret_cast<__IO SMPR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR2)->SMP2; }
            static inline void set_SMP2(uint32_t value) { reinterpret_cast<__IO SMPR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR2)->SMP2 = value; }
            static inline uint32_t get_SMP3() { return reinterpret_cast<__IO SMPR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR2)->SMP3; }
            static inline void set_SMP3(uint32_t value) { reinterpret_cast<__IO SMPR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR2)->SMP3 = value; }
            static inline uint32_t get_SMP4() { return reinterpret_cast<__IO SMPR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR2)->SMP4; }
            static inline void set_SMP4(uint32_t value) { reinterpret_cast<__IO SMPR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR2)->SMP4 = value; }
            static inline uint32_t get_SMP5() { return reinterpret_cast<__IO SMPR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR2)->SMP5; }
            static inline void set_SMP5(uint32_t value) { reinterpret_cast<__IO SMPR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR2)->SMP5 = value; }
            static inline uint32_t get_SMP6() { return reinterpret_cast<__IO SMPR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR2)->SMP6; }
            static inline void set_SMP6(uint32_t value) { reinterpret_cast<__IO SMPR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR2)->SMP6 = value; }
            static inline uint32_t get_SMP7() { return reinterpret_cast<__IO SMPR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR2)->SMP7; }
            static inline void set_SMP7(uint32_t value) { reinterpret_cast<__IO SMPR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR2)->SMP7 = value; }
            static inline uint32_t get_SMP8() { return reinterpret_cast<__IO SMPR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR2)->SMP8; }
            static inline void set_SMP8(uint32_t value) { reinterpret_cast<__IO SMPR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR2)->SMP8 = value; }
            static inline uint32_t get_SMP9() { return reinterpret_cast<__IO SMPR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR2)->SMP9; }
            static inline void set_SMP9(uint32_t value) { reinterpret_cast<__IO SMPR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SMPR2)->SMP9 = value; }
        };
        class JOFR1
        {
        private:
            union JOFR1_t
            {
                struct
                {
                    uint32_t JOFFSET1       : 12;
                    uint32_t reserved12     : 20;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                JOFFSET1               = (0xFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JOFR1; }
            static inline void set(uint32_t value) { reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JOFR1 = value; }
            static inline uint32_t get_JOFFSET1() { return reinterpret_cast<__IO JOFR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JOFR1)->JOFFSET1; }
            static inline void set_JOFFSET1(uint32_t value) { reinterpret_cast<__IO JOFR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JOFR1)->JOFFSET1 = value; }
        };
        class JOFR2
        {
        private:
            union JOFR2_t
            {
                struct
                {
                    uint32_t JOFFSET2       : 12;
                    uint32_t reserved12     : 20;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                JOFFSET2               = (0xFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JOFR2; }
            static inline void set(uint32_t value) { reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JOFR2 = value; }
            static inline uint32_t get_JOFFSET2() { return reinterpret_cast<__IO JOFR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JOFR2)->JOFFSET2; }
            static inline void set_JOFFSET2(uint32_t value) { reinterpret_cast<__IO JOFR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JOFR2)->JOFFSET2 = value; }
        };
        class JOFR3
        {
        private:
            union JOFR3_t
            {
                struct
                {
                    uint32_t JOFFSET3       : 12;
                    uint32_t reserved12     : 20;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                JOFFSET3               = (0xFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JOFR3; }
            static inline void set(uint32_t value) { reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JOFR3 = value; }
            static inline uint32_t get_JOFFSET3() { return reinterpret_cast<__IO JOFR3_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JOFR3)->JOFFSET3; }
            static inline void set_JOFFSET3(uint32_t value) { reinterpret_cast<__IO JOFR3_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JOFR3)->JOFFSET3 = value; }
        };
        class JOFR4
        {
        private:
            union JOFR4_t
            {
                struct
                {
                    uint32_t JOFFSET4       : 12;
                    uint32_t reserved12     : 20;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                JOFFSET4               = (0xFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JOFR4; }
            static inline void set(uint32_t value) { reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JOFR4 = value; }
            static inline uint32_t get_JOFFSET4() { return reinterpret_cast<__IO JOFR4_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JOFR4)->JOFFSET4; }
            static inline void set_JOFFSET4(uint32_t value) { reinterpret_cast<__IO JOFR4_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JOFR4)->JOFFSET4 = value; }
        };
        class HTR
        {
        private:
            union HTR_t
            {
                struct
                {
                    uint32_t HT             : 12;
                    uint32_t reserved12     : 20;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                HT                     = (0xFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->HTR; }
            static inline void set(uint32_t value) { reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->HTR = value; }
            static inline uint32_t get_HT() { return reinterpret_cast<__IO HTR_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->HTR)->HT; }
            static inline void set_HT(uint32_t value) { reinterpret_cast<__IO HTR_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->HTR)->HT = value; }
        };
        class LTR
        {
        private:
            union LTR_t
            {
                struct
                {
                    uint32_t LT             : 12;
                    uint32_t reserved12     : 20;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                LT                     = (0xFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->LTR; }
            static inline void set(uint32_t value) { reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->LTR = value; }
            static inline uint32_t get_LT() { return reinterpret_cast<__IO LTR_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->LTR)->LT; }
            static inline void set_LT(uint32_t value) { reinterpret_cast<__IO LTR_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->LTR)->LT = value; }
        };
        class SQR1
        {
        private:
            union SQR1_t
            {
                struct
                {
                    uint32_t SQ13           : 5;
                    uint32_t SQ14           : 5;
                    uint32_t SQ15           : 5;
                    uint32_t SQ16           : 5;
                    uint32_t L              : 4;
                    uint32_t reserved24     : 8;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                SQ13                   = (0x1FU << 0),
                SQ14                   = (0x1FU << 5),
                SQ15                   = (0x1FU << 10),
                SQ16                   = (0x1FU << 15),
                L                      = (0xFU << 20),
            };
            static inline uint32_t get() { return reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR1; }
            static inline void set(uint32_t value) { reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR1 = value; }
            static inline uint32_t get_SQ13() { return reinterpret_cast<__IO SQR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR1)->SQ13; }
            static inline void set_SQ13(uint32_t value) { reinterpret_cast<__IO SQR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR1)->SQ13 = value; }
            static inline uint32_t get_SQ14() { return reinterpret_cast<__IO SQR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR1)->SQ14; }
            static inline void set_SQ14(uint32_t value) { reinterpret_cast<__IO SQR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR1)->SQ14 = value; }
            static inline uint32_t get_SQ15() { return reinterpret_cast<__IO SQR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR1)->SQ15; }
            static inline void set_SQ15(uint32_t value) { reinterpret_cast<__IO SQR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR1)->SQ15 = value; }
            static inline uint32_t get_SQ16() { return reinterpret_cast<__IO SQR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR1)->SQ16; }
            static inline void set_SQ16(uint32_t value) { reinterpret_cast<__IO SQR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR1)->SQ16 = value; }
            static inline uint32_t get_L() { return reinterpret_cast<__IO SQR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR1)->L; }
            static inline void set_L(uint32_t value) { reinterpret_cast<__IO SQR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR1)->L = value; }
        };
        class SQR2
        {
        private:
            union SQR2_t
            {
                struct
                {
                    uint32_t SQ7            : 5;
                    uint32_t SQ8            : 5;
                    uint32_t SQ9            : 5;
                    uint32_t SQ10           : 5;
                    uint32_t SQ11           : 5;
                    uint32_t SQ12           : 5;
                    uint32_t reserved30     : 2;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                SQ7                    = (0x1FU << 0),
                SQ8                    = (0x1FU << 5),
                SQ9                    = (0x1FU << 10),
                SQ10                   = (0x1FU << 15),
                SQ11                   = (0x1FU << 20),
                SQ12                   = (0x1FU << 25),
            };
            static inline uint32_t get() { return reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR2; }
            static inline void set(uint32_t value) { reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR2 = value; }
            static inline uint32_t get_SQ7() { return reinterpret_cast<__IO SQR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR2)->SQ7; }
            static inline void set_SQ7(uint32_t value) { reinterpret_cast<__IO SQR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR2)->SQ7 = value; }
            static inline uint32_t get_SQ8() { return reinterpret_cast<__IO SQR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR2)->SQ8; }
            static inline void set_SQ8(uint32_t value) { reinterpret_cast<__IO SQR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR2)->SQ8 = value; }
            static inline uint32_t get_SQ9() { return reinterpret_cast<__IO SQR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR2)->SQ9; }
            static inline void set_SQ9(uint32_t value) { reinterpret_cast<__IO SQR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR2)->SQ9 = value; }
            static inline uint32_t get_SQ10() { return reinterpret_cast<__IO SQR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR2)->SQ10; }
            static inline void set_SQ10(uint32_t value) { reinterpret_cast<__IO SQR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR2)->SQ10 = value; }
            static inline uint32_t get_SQ11() { return reinterpret_cast<__IO SQR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR2)->SQ11; }
            static inline void set_SQ11(uint32_t value) { reinterpret_cast<__IO SQR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR2)->SQ11 = value; }
            static inline uint32_t get_SQ12() { return reinterpret_cast<__IO SQR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR2)->SQ12; }
            static inline void set_SQ12(uint32_t value) { reinterpret_cast<__IO SQR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR2)->SQ12 = value; }
        };
        class SQR3
        {
        private:
            union SQR3_t
            {
                struct
                {
                    uint32_t SQ1            : 5;
                    uint32_t SQ2            : 5;
                    uint32_t SQ3            : 5;
                    uint32_t SQ4            : 5;
                    uint32_t SQ5            : 5;
                    uint32_t SQ6            : 5;
                    uint32_t reserved30     : 2;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                SQ1                    = (0x1FU << 0),
                SQ2                    = (0x1FU << 5),
                SQ3                    = (0x1FU << 10),
                SQ4                    = (0x1FU << 15),
                SQ5                    = (0x1FU << 20),
                SQ6                    = (0x1FU << 25),
            };
            static inline uint32_t get() { return reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR3; }
            static inline void set(uint32_t value) { reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR3 = value; }
            static inline uint32_t get_SQ1() { return reinterpret_cast<__IO SQR3_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR3)->SQ1; }
            static inline void set_SQ1(uint32_t value) { reinterpret_cast<__IO SQR3_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR3)->SQ1 = value; }
            static inline uint32_t get_SQ2() { return reinterpret_cast<__IO SQR3_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR3)->SQ2; }
            static inline void set_SQ2(uint32_t value) { reinterpret_cast<__IO SQR3_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR3)->SQ2 = value; }
            static inline uint32_t get_SQ3() { return reinterpret_cast<__IO SQR3_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR3)->SQ3; }
            static inline void set_SQ3(uint32_t value) { reinterpret_cast<__IO SQR3_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR3)->SQ3 = value; }
            static inline uint32_t get_SQ4() { return reinterpret_cast<__IO SQR3_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR3)->SQ4; }
            static inline void set_SQ4(uint32_t value) { reinterpret_cast<__IO SQR3_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR3)->SQ4 = value; }
            static inline uint32_t get_SQ5() { return reinterpret_cast<__IO SQR3_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR3)->SQ5; }
            static inline void set_SQ5(uint32_t value) { reinterpret_cast<__IO SQR3_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR3)->SQ5 = value; }
            static inline uint32_t get_SQ6() { return reinterpret_cast<__IO SQR3_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR3)->SQ6; }
            static inline void set_SQ6(uint32_t value) { reinterpret_cast<__IO SQR3_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->SQR3)->SQ6 = value; }
        };
        class JSQR
        {
        private:
            union JSQR_t
            {
                struct
                {
                    uint32_t JSQ1           : 5;
                    uint32_t JSQ2           : 5;
                    uint32_t JSQ3           : 5;
                    uint32_t JSQ4           : 5;
                    uint32_t JL             : 2;
                    uint32_t reserved22     : 10;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                JSQ1                   = (0x1FU << 0),
                JSQ2                   = (0x1FU << 5),
                JSQ3                   = (0x1FU << 10),
                JSQ4                   = (0x1FU << 15),
                JL                     = (0x3U << 20),
            };
            static inline uint32_t get() { return reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JSQR; }
            static inline void set(uint32_t value) { reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JSQR = value; }
            static inline uint32_t get_JSQ1() { return reinterpret_cast<__IO JSQR_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JSQR)->JSQ1; }
            static inline void set_JSQ1(uint32_t value) { reinterpret_cast<__IO JSQR_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JSQR)->JSQ1 = value; }
            static inline uint32_t get_JSQ2() { return reinterpret_cast<__IO JSQR_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JSQR)->JSQ2; }
            static inline void set_JSQ2(uint32_t value) { reinterpret_cast<__IO JSQR_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JSQR)->JSQ2 = value; }
            static inline uint32_t get_JSQ3() { return reinterpret_cast<__IO JSQR_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JSQR)->JSQ3; }
            static inline void set_JSQ3(uint32_t value) { reinterpret_cast<__IO JSQR_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JSQR)->JSQ3 = value; }
            static inline uint32_t get_JSQ4() { return reinterpret_cast<__IO JSQR_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JSQR)->JSQ4; }
            static inline void set_JSQ4(uint32_t value) { reinterpret_cast<__IO JSQR_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JSQR)->JSQ4 = value; }
            static inline uint32_t get_JL() { return reinterpret_cast<__IO JSQR_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JSQR)->JL; }
            static inline void set_JL(uint32_t value) { reinterpret_cast<__IO JSQR_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JSQR)->JL = value; }
        };
        class JDR1
        {
        private:
            union JDR1_t
            {
                struct
                {
                    uint32_t JDATA          : 16;
                    uint32_t reserved16     : 16;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                JDATA                  = (0xFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JDR1; }
            static inline void set(uint32_t value) { reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JDR1 = value; }
            static inline uint32_t get_JDATA() { return reinterpret_cast<__IO JDR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JDR1)->JDATA; }
            static inline void set_JDATA(uint32_t value) { reinterpret_cast<__IO JDR1_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JDR1)->JDATA = value; }
        };
        class JDR2
        {
        private:
            union JDR2_t
            {
                struct
                {
                    uint32_t JDATA          : 16;
                    uint32_t reserved16     : 16;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                JDATA                  = (0xFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JDR2; }
            static inline void set(uint32_t value) { reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JDR2 = value; }
            static inline uint32_t get_JDATA() { return reinterpret_cast<__IO JDR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JDR2)->JDATA; }
            static inline void set_JDATA(uint32_t value) { reinterpret_cast<__IO JDR2_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JDR2)->JDATA = value; }
        };
        class JDR3
        {
        private:
            union JDR3_t
            {
                struct
                {
                    uint32_t JDATA          : 16;
                    uint32_t reserved16     : 16;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                JDATA                  = (0xFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JDR3; }
            static inline void set(uint32_t value) { reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JDR3 = value; }
            static inline uint32_t get_JDATA() { return reinterpret_cast<__IO JDR3_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JDR3)->JDATA; }
            static inline void set_JDATA(uint32_t value) { reinterpret_cast<__IO JDR3_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JDR3)->JDATA = value; }
        };
        class JDR4
        {
        private:
            union JDR4_t
            {
                struct
                {
                    uint32_t JDATA          : 16;
                    uint32_t reserved16     : 16;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                JDATA                  = (0xFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JDR4; }
            static inline void set(uint32_t value) { reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JDR4 = value; }
            static inline uint32_t get_JDATA() { return reinterpret_cast<__IO JDR4_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JDR4)->JDATA; }
            static inline void set_JDATA(uint32_t value) { reinterpret_cast<__IO JDR4_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->JDR4)->JDATA = value; }
        };
        class DR
        {
        private:
            union DR_t
            {
                struct
                {
                    uint32_t DATA           : 16;
                    uint32_t ADC2DATA       : 16;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DATA                   = (0xFFFFU << 0),
                ADC2DATA               = (0xFFFFU << 16),
            };
            static inline uint32_t get() { return reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->DR; }
            static inline void set(uint32_t value) { reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->DR = value; }
            static inline uint32_t get_DATA() { return reinterpret_cast<__IO DR_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->DR)->DATA; }
            static inline void set_DATA(uint32_t value) { reinterpret_cast<__IO DR_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->DR)->DATA = value; }
            static inline uint32_t get_ADC2DATA() { return reinterpret_cast<__IO DR_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->DR)->ADC2DATA; }
            static inline void set_ADC2DATA(uint32_t value) { reinterpret_cast<__IO DR_t*>(&reinterpret_cast<ADC_t*>(STM32::ADC_BASE)->DR)->ADC2DATA = value; }
        };
    };
    /* ADC123_Common DEFINITION */
    template <uint32_t reg_base>
    class ADC123_Common
    {
    };
    /* CAN_TxMailBox DEFINITION */
    template <uint32_t reg_base>
    class CAN_TxMailBox
    {
    };
    /* CAN_FIFOMailBox DEFINITION */
    template <uint32_t reg_base>
    class CAN_FIFOMailBox
    {
    };
    /* CAN_FilterRegister DEFINITION */
    template <uint32_t reg_base>
    class CAN_FilterRegister
    {
    };
    /* CAN DEFINITION */
    template <uint32_t reg_base>
    class CAN
    {
    };
    /* CRC DEFINITION */
    class CRC
    {
    private:
        struct CRC_t
        {
            __IO uint32_t                 DR;
            __IO uint8_t                  IDR;
            uint8_t                       RESERVED0;
            uint16_t                      RESERVED1;
            __IO uint32_t                 CR;
        };
    public:
        class DR
        {
        private:
            union DR_t
            {
                struct
                {
                    uint32_t DR             : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DR                     = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<CRC_t*>(STM32::CRC_BASE)->DR; }
            static inline void set(uint32_t value) { reinterpret_cast<CRC_t*>(STM32::CRC_BASE)->DR = value; }
            static inline uint32_t get_DR() { return reinterpret_cast<__IO DR_t*>(&reinterpret_cast<CRC_t*>(STM32::CRC_BASE)->DR)->DR; }
            static inline void set_DR(uint32_t value) { reinterpret_cast<__IO DR_t*>(&reinterpret_cast<CRC_t*>(STM32::CRC_BASE)->DR)->DR = value; }
        };
        class IDR
        {
        public:
            enum class EMasks: uint32_t
            {
                IDR                    = (0xFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<CRC_t*>(STM32::CRC_BASE)->IDR; }
            static inline void set(uint32_t value) { reinterpret_cast<CRC_t*>(STM32::CRC_BASE)->IDR = value; }
        };
        class CR
        {
        private:
            union CR_t
            {
                struct
                {
                    uint32_t RESET          : 1;
                    uint32_t reserved1      : 31;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                RESET                  = (0x1U << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<CRC_t*>(STM32::CRC_BASE)->CR; }
            static inline void set(uint32_t value) { reinterpret_cast<CRC_t*>(STM32::CRC_BASE)->CR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<CRC_t*>(STM32::CRC_BASE)->CR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<CRC_t*>(STM32::CRC_BASE)->CR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<CRC_t*>(STM32::CRC_BASE)->CR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
    };
    /* DAC DEFINITION */
    class DAC
    {
    private:
        struct DAC_t
        {
            __IO uint32_t                 CR;
            __IO uint32_t                 SWTRIGR;
            __IO uint32_t                 DHR12R1;
            __IO uint32_t                 DHR12L1;
            __IO uint32_t                 DHR8R1;
            __IO uint32_t                 DHR12R2;
            __IO uint32_t                 DHR12L2;
            __IO uint32_t                 DHR8R2;
            __IO uint32_t                 DHR12RD;
            __IO uint32_t                 DHR12LD;
            __IO uint32_t                 DHR8RD;
            __IO uint32_t                 DOR1;
            __IO uint32_t                 DOR2;
            __IO uint32_t                 SR;
        };
    public:
        class CR
        {
        private:
            union CR_t
            {
                struct
                {
                    uint32_t EN1            : 1;
                    uint32_t BOFF1          : 1;
                    uint32_t TEN1           : 1;
                    uint32_t TSEL1          : 3;
                    uint32_t WAVE1          : 2;
                    uint32_t MAMP1          : 4;
                    uint32_t DMAEN1         : 1;
                    uint32_t DMAUDRIE1      : 1;
                    uint32_t reserved14     : 2;
                    uint32_t EN2            : 1;
                    uint32_t BOFF2          : 1;
                    uint32_t TEN2           : 1;
                    uint32_t TSEL2          : 3;
                    uint32_t WAVE2          : 2;
                    uint32_t MAMP2          : 4;
                    uint32_t DMAEN2         : 1;
                    uint32_t DMAUDRIE2      : 1;
                    uint32_t reserved30     : 2;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                EN1                    = (0x1U << 0),
                BOFF1                  = (0x1U << 1),
                TEN1                   = (0x1U << 2),
                TSEL1                  = (0x7U << 3),
                WAVE1                  = (0x3U << 6),
                MAMP1                  = (0xFU << 8),
                DMAEN1                 = (0x1U << 12),
                DMAUDRIE1              = (0x1U << 13),
                EN2                    = (0x1U << 16),
                BOFF2                  = (0x1U << 17),
                TEN2                   = (0x1U << 18),
                TSEL2                  = (0x7U << 19),
                WAVE2                  = (0x3U << 22),
                MAMP2                  = (0xFU << 24),
                DMAEN2                 = (0x1U << 28),
                DMAUDRIE2              = (0x1U << 29),
            };
            static inline uint32_t get() { return reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->CR; }
            static inline void set(uint32_t value) { reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->CR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->CR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->CR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->CR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_TSEL1() { return reinterpret_cast<__IO CR_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->CR)->TSEL1; }
            static inline void set_TSEL1(uint32_t value) { reinterpret_cast<__IO CR_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->CR)->TSEL1 = value; }
            static inline uint32_t get_WAVE1() { return reinterpret_cast<__IO CR_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->CR)->WAVE1; }
            static inline void set_WAVE1(uint32_t value) { reinterpret_cast<__IO CR_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->CR)->WAVE1 = value; }
            static inline uint32_t get_MAMP1() { return reinterpret_cast<__IO CR_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->CR)->MAMP1; }
            static inline void set_MAMP1(uint32_t value) { reinterpret_cast<__IO CR_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->CR)->MAMP1 = value; }
            static inline uint32_t get_TSEL2() { return reinterpret_cast<__IO CR_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->CR)->TSEL2; }
            static inline void set_TSEL2(uint32_t value) { reinterpret_cast<__IO CR_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->CR)->TSEL2 = value; }
            static inline uint32_t get_WAVE2() { return reinterpret_cast<__IO CR_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->CR)->WAVE2; }
            static inline void set_WAVE2(uint32_t value) { reinterpret_cast<__IO CR_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->CR)->WAVE2 = value; }
            static inline uint32_t get_MAMP2() { return reinterpret_cast<__IO CR_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->CR)->MAMP2; }
            static inline void set_MAMP2(uint32_t value) { reinterpret_cast<__IO CR_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->CR)->MAMP2 = value; }
        };
        class SWTRIGR
        {
        private:
            union SWTRIGR_t
            {
                struct
                {
                    uint32_t SWTRIG1        : 1;
                    uint32_t SWTRIG2        : 1;
                    uint32_t reserved2      : 30;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                SWTRIG1                = (0x1U << 0),
                SWTRIG2                = (0x1U << 1),
            };
            static inline uint32_t get() { return reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->SWTRIGR; }
            static inline void set(uint32_t value) { reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->SWTRIGR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->SWTRIGR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->SWTRIGR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->SWTRIGR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class DHR12R1
        {
        private:
            union DHR12R1_t
            {
                struct
                {
                    uint32_t DACC1DHR       : 12;
                    uint32_t reserved12     : 20;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DACC1DHR               = (0xFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR12R1; }
            static inline void set(uint32_t value) { reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR12R1 = value; }
            static inline uint32_t get_DACC1DHR() { return reinterpret_cast<__IO DHR12R1_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR12R1)->DACC1DHR; }
            static inline void set_DACC1DHR(uint32_t value) { reinterpret_cast<__IO DHR12R1_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR12R1)->DACC1DHR = value; }
        };
        class DHR12L1
        {
        private:
            union DHR12L1_t
            {
                struct
                {
                    uint32_t reserved0      : 4;
                    uint32_t DACC1DHR       : 12;
                    uint32_t reserved16     : 16;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DACC1DHR               = (0xFFFU << 4),
            };
            static inline uint32_t get() { return reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR12L1; }
            static inline void set(uint32_t value) { reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR12L1 = value; }
            static inline uint32_t get_DACC1DHR() { return reinterpret_cast<__IO DHR12L1_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR12L1)->DACC1DHR; }
            static inline void set_DACC1DHR(uint32_t value) { reinterpret_cast<__IO DHR12L1_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR12L1)->DACC1DHR = value; }
        };
        class DHR8R1
        {
        private:
            union DHR8R1_t
            {
                struct
                {
                    uint32_t DACC1DHR       : 8;
                    uint32_t reserved8      : 24;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DACC1DHR               = (0xFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR8R1; }
            static inline void set(uint32_t value) { reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR8R1 = value; }
            static inline uint32_t get_DACC1DHR() { return reinterpret_cast<__IO DHR8R1_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR8R1)->DACC1DHR; }
            static inline void set_DACC1DHR(uint32_t value) { reinterpret_cast<__IO DHR8R1_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR8R1)->DACC1DHR = value; }
        };
        class DHR12R2
        {
        private:
            union DHR12R2_t
            {
                struct
                {
                    uint32_t DACC2DHR       : 12;
                    uint32_t reserved12     : 20;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DACC2DHR               = (0xFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR12R2; }
            static inline void set(uint32_t value) { reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR12R2 = value; }
            static inline uint32_t get_DACC2DHR() { return reinterpret_cast<__IO DHR12R2_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR12R2)->DACC2DHR; }
            static inline void set_DACC2DHR(uint32_t value) { reinterpret_cast<__IO DHR12R2_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR12R2)->DACC2DHR = value; }
        };
        class DHR12L2
        {
        private:
            union DHR12L2_t
            {
                struct
                {
                    uint32_t reserved0      : 4;
                    uint32_t DACC2DHR       : 12;
                    uint32_t reserved16     : 16;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DACC2DHR               = (0xFFFU << 4),
            };
            static inline uint32_t get() { return reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR12L2; }
            static inline void set(uint32_t value) { reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR12L2 = value; }
            static inline uint32_t get_DACC2DHR() { return reinterpret_cast<__IO DHR12L2_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR12L2)->DACC2DHR; }
            static inline void set_DACC2DHR(uint32_t value) { reinterpret_cast<__IO DHR12L2_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR12L2)->DACC2DHR = value; }
        };
        class DHR8R2
        {
        private:
            union DHR8R2_t
            {
                struct
                {
                    uint32_t DACC2DHR       : 8;
                    uint32_t reserved8      : 24;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DACC2DHR               = (0xFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR8R2; }
            static inline void set(uint32_t value) { reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR8R2 = value; }
            static inline uint32_t get_DACC2DHR() { return reinterpret_cast<__IO DHR8R2_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR8R2)->DACC2DHR; }
            static inline void set_DACC2DHR(uint32_t value) { reinterpret_cast<__IO DHR8R2_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR8R2)->DACC2DHR = value; }
        };
        class DHR12RD
        {
        private:
            union DHR12RD_t
            {
                struct
                {
                    uint32_t DACC1DHR       : 12;
                    uint32_t reserved12     : 4;
                    uint32_t DACC2DHR       : 12;
                    uint32_t reserved28     : 4;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DACC1DHR               = (0xFFFU << 0),
                DACC2DHR               = (0xFFFU << 16),
            };
            static inline uint32_t get() { return reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR12RD; }
            static inline void set(uint32_t value) { reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR12RD = value; }
            static inline uint32_t get_DACC1DHR() { return reinterpret_cast<__IO DHR12RD_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR12RD)->DACC1DHR; }
            static inline void set_DACC1DHR(uint32_t value) { reinterpret_cast<__IO DHR12RD_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR12RD)->DACC1DHR = value; }
            static inline uint32_t get_DACC2DHR() { return reinterpret_cast<__IO DHR12RD_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR12RD)->DACC2DHR; }
            static inline void set_DACC2DHR(uint32_t value) { reinterpret_cast<__IO DHR12RD_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR12RD)->DACC2DHR = value; }
        };
        class DHR12LD
        {
        private:
            union DHR12LD_t
            {
                struct
                {
                    uint32_t reserved0      : 4;
                    uint32_t DACC1DHR       : 12;
                    uint32_t reserved16     : 4;
                    uint32_t DACC2DHR       : 12;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DACC1DHR               = (0xFFFU << 4),
                DACC2DHR               = (0xFFFU << 20),
            };
            static inline uint32_t get() { return reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR12LD; }
            static inline void set(uint32_t value) { reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR12LD = value; }
            static inline uint32_t get_DACC1DHR() { return reinterpret_cast<__IO DHR12LD_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR12LD)->DACC1DHR; }
            static inline void set_DACC1DHR(uint32_t value) { reinterpret_cast<__IO DHR12LD_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR12LD)->DACC1DHR = value; }
            static inline uint32_t get_DACC2DHR() { return reinterpret_cast<__IO DHR12LD_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR12LD)->DACC2DHR; }
            static inline void set_DACC2DHR(uint32_t value) { reinterpret_cast<__IO DHR12LD_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR12LD)->DACC2DHR = value; }
        };
        class DHR8RD
        {
        private:
            union DHR8RD_t
            {
                struct
                {
                    uint32_t DACC1DHR       : 8;
                    uint32_t DACC2DHR       : 8;
                    uint32_t reserved16     : 16;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DACC1DHR               = (0xFFU << 0),
                DACC2DHR               = (0xFFU << 8),
            };
            static inline uint32_t get() { return reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR8RD; }
            static inline void set(uint32_t value) { reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR8RD = value; }
            static inline uint32_t get_DACC1DHR() { return reinterpret_cast<__IO DHR8RD_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR8RD)->DACC1DHR; }
            static inline void set_DACC1DHR(uint32_t value) { reinterpret_cast<__IO DHR8RD_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR8RD)->DACC1DHR = value; }
            static inline uint32_t get_DACC2DHR() { return reinterpret_cast<__IO DHR8RD_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR8RD)->DACC2DHR; }
            static inline void set_DACC2DHR(uint32_t value) { reinterpret_cast<__IO DHR8RD_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DHR8RD)->DACC2DHR = value; }
        };
        class DOR1
        {
        private:
            union DOR1_t
            {
                struct
                {
                    uint32_t DACC1DOR       : 12;
                    uint32_t reserved12     : 20;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DACC1DOR               = (0xFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DOR1; }
            static inline void set(uint32_t value) { reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DOR1 = value; }
            static inline uint32_t get_DACC1DOR() { return reinterpret_cast<__IO DOR1_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DOR1)->DACC1DOR; }
            static inline void set_DACC1DOR(uint32_t value) { reinterpret_cast<__IO DOR1_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DOR1)->DACC1DOR = value; }
        };
        class DOR2
        {
        private:
            union DOR2_t
            {
                struct
                {
                    uint32_t DACC2DOR       : 12;
                    uint32_t reserved12     : 20;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DACC2DOR               = (0xFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DOR2; }
            static inline void set(uint32_t value) { reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DOR2 = value; }
            static inline uint32_t get_DACC2DOR() { return reinterpret_cast<__IO DOR2_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DOR2)->DACC2DOR; }
            static inline void set_DACC2DOR(uint32_t value) { reinterpret_cast<__IO DOR2_t*>(&reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->DOR2)->DACC2DOR = value; }
        };
        class SR
        {
        private:
            union SR_t
            {
                struct
                {
                    uint32_t reserved0      : 13;
                    uint32_t DMAUDR1        : 1;
                    uint32_t reserved14     : 15;
                    uint32_t DMAUDR2        : 1;
                    uint32_t reserved30     : 2;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DMAUDR1                = (0x1U << 13),
                DMAUDR2                = (0x1U << 29),
            };
            static inline uint32_t get() { return reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->SR; }
            static inline void set(uint32_t value) { reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->SR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->SR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->SR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<DAC_t*>(STM32::DAC_BASE)->SR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
    };
    /* DBGMCU DEFINITION */
    class DBGMCU
    {
    private:
        struct DBGMCU_t
        {
            __IO uint32_t                 IDCODE;
            __IO uint32_t                 CR;
            __IO uint32_t                 APB1FZ;
            __IO uint32_t                 APB2FZ;
        };
    public:
        class IDCODE
        {
        private:
            union IDCODE_t
            {
                struct
                {
                    uint32_t DEV_ID         : 12;
                    uint32_t reserved12     : 4;
                    uint32_t REV_ID         : 16;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DEV_ID                 = (0xFFFU << 0),
                REV_ID                 = (0xFFFFU << 16),
            };
            static inline uint32_t get() { return reinterpret_cast<DBGMCU_t*>(STM32::DBGMCU_BASE)->IDCODE; }
            static inline void set(uint32_t value) { reinterpret_cast<DBGMCU_t*>(STM32::DBGMCU_BASE)->IDCODE = value; }
            static inline uint32_t get_DEV_ID() { return reinterpret_cast<__IO IDCODE_t*>(&reinterpret_cast<DBGMCU_t*>(STM32::DBGMCU_BASE)->IDCODE)->DEV_ID; }
            static inline void set_DEV_ID(uint32_t value) { reinterpret_cast<__IO IDCODE_t*>(&reinterpret_cast<DBGMCU_t*>(STM32::DBGMCU_BASE)->IDCODE)->DEV_ID = value; }
            static inline uint32_t get_REV_ID() { return reinterpret_cast<__IO IDCODE_t*>(&reinterpret_cast<DBGMCU_t*>(STM32::DBGMCU_BASE)->IDCODE)->REV_ID; }
            static inline void set_REV_ID(uint32_t value) { reinterpret_cast<__IO IDCODE_t*>(&reinterpret_cast<DBGMCU_t*>(STM32::DBGMCU_BASE)->IDCODE)->REV_ID = value; }
        };
        class CR
        {
        private:
            union CR_t
            {
                struct
                {
                    uint32_t DBG_SLEEP      : 1;
                    uint32_t DBG_STOP       : 1;
                    uint32_t DBG_STANDBY    : 1;
                    uint32_t reserved3      : 2;
                    uint32_t TRACE_IOEN     : 1;
                    uint32_t TRACE_MODE     : 2;
                    uint32_t reserved8      : 24;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DBG_SLEEP              = (0x1U << 0),
                DBG_STOP               = (0x1U << 1),
                DBG_STANDBY            = (0x1U << 2),
                TRACE_IOEN             = (0x1U << 5),
                TRACE_MODE             = (0x3U << 6),
            };
            static inline uint32_t get() { return reinterpret_cast<DBGMCU_t*>(STM32::DBGMCU_BASE)->CR; }
            static inline void set(uint32_t value) { reinterpret_cast<DBGMCU_t*>(STM32::DBGMCU_BASE)->CR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<DBGMCU_t*>(STM32::DBGMCU_BASE)->CR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<DBGMCU_t*>(STM32::DBGMCU_BASE)->CR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<DBGMCU_t*>(STM32::DBGMCU_BASE)->CR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_TRACE_MODE() { return reinterpret_cast<__IO CR_t*>(&reinterpret_cast<DBGMCU_t*>(STM32::DBGMCU_BASE)->CR)->TRACE_MODE; }
            static inline void set_TRACE_MODE(uint32_t value) { reinterpret_cast<__IO CR_t*>(&reinterpret_cast<DBGMCU_t*>(STM32::DBGMCU_BASE)->CR)->TRACE_MODE = value; }
        };
        class APB1FZ
        {
        private:
            union APB1FZ_t
            {
                struct
                {
                    uint32_t FZ_DBG_TIM2_STOP: 1;
                    uint32_t FZ_DBG_TIM3_STOP: 1;
                    uint32_t FZ_DBG_TIM4_STOP: 1;
                    uint32_t FZ_DBG_TIM5_STOP: 1;
                    uint32_t FZ_DBG_TIM6_STOP: 1;
                    uint32_t FZ_DBG_TIM7_STOP: 1;
                    uint32_t FZ_DBG_TIM12_STOP: 1;
                    uint32_t FZ_DBG_TIM13_STOP: 1;
                    uint32_t FZ_DBG_TIM14_STOP: 1;
                    uint32_t reserved9      : 1;
                    uint32_t FZ_DBG_RTC_STOP: 1;
                    uint32_t FZ_DBG_WWDG_STOP: 1;
                    uint32_t FZ_DBG_IWDG_STOP: 1;
                    uint32_t reserved13     : 8;
                    uint32_t FZ_DBG_I2C1_SMBUS_TIMEOUT: 1;
                    uint32_t FZ_DBG_I2C2_SMBUS_TIMEOUT: 1;
                    uint32_t FZ_DBG_I2C3_SMBUS_TIMEOUT: 1;
                    uint32_t reserved24     : 1;
                    uint32_t FZ_DBG_CAN1_STOP: 1;
                    uint32_t FZ_DBG_CAN2_STOP: 1;
                    uint32_t reserved27     : 5;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                FZ_DBG_TIM2_STOP       = (0x1U << 0),
                FZ_DBG_TIM3_STOP       = (0x1U << 1),
                FZ_DBG_TIM4_STOP       = (0x1U << 2),
                FZ_DBG_TIM5_STOP       = (0x1U << 3),
                FZ_DBG_TIM6_STOP       = (0x1U << 4),
                FZ_DBG_TIM7_STOP       = (0x1U << 5),
                FZ_DBG_TIM12_STOP      = (0x1U << 6),
                FZ_DBG_TIM13_STOP      = (0x1U << 7),
                FZ_DBG_TIM14_STOP      = (0x1U << 8),
                FZ_DBG_RTC_STOP        = (0x1U << 10),
                FZ_DBG_WWDG_STOP       = (0x1U << 11),
                FZ_DBG_IWDG_STOP       = (0x1U << 12),
                FZ_DBG_I2C1_SMBUS_TIMEOUT = (0x1U << 21),
                FZ_DBG_I2C2_SMBUS_TIMEOUT = (0x1U << 22),
                FZ_DBG_I2C3_SMBUS_TIMEOUT = (0x1U << 23),
                FZ_DBG_CAN1_STOP       = (0x1U << 25),
                FZ_DBG_CAN2_STOP       = (0x1U << 26),
            };
            static inline uint32_t get() { return reinterpret_cast<DBGMCU_t*>(STM32::DBGMCU_BASE)->APB1FZ; }
            static inline void set(uint32_t value) { reinterpret_cast<DBGMCU_t*>(STM32::DBGMCU_BASE)->APB1FZ = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<DBGMCU_t*>(STM32::DBGMCU_BASE)->APB1FZ |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<DBGMCU_t*>(STM32::DBGMCU_BASE)->APB1FZ &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<DBGMCU_t*>(STM32::DBGMCU_BASE)->APB1FZ & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class APB2FZ
        {
        private:
            union APB2FZ_t
            {
                struct
                {
                    uint32_t FZ_DBG_TIM1_STOP: 1;
                    uint32_t FZ_DBG_TIM8_STOP: 1;
                    uint32_t reserved2      : 14;
                    uint32_t FZ_DBG_TIM9_STOP: 1;
                    uint32_t FZ_DBG_TIM10_STOP: 1;
                    uint32_t FZ_DBG_TIM11_STOP: 1;
                    uint32_t reserved19     : 13;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                FZ_DBG_TIM1_STOP       = (0x1U << 0),
                FZ_DBG_TIM8_STOP       = (0x1U << 1),
                FZ_DBG_TIM9_STOP       = (0x1U << 16),
                FZ_DBG_TIM10_STOP      = (0x1U << 17),
                FZ_DBG_TIM11_STOP      = (0x1U << 18),
            };
            static inline uint32_t get() { return reinterpret_cast<DBGMCU_t*>(STM32::DBGMCU_BASE)->APB2FZ; }
            static inline void set(uint32_t value) { reinterpret_cast<DBGMCU_t*>(STM32::DBGMCU_BASE)->APB2FZ = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<DBGMCU_t*>(STM32::DBGMCU_BASE)->APB2FZ |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<DBGMCU_t*>(STM32::DBGMCU_BASE)->APB2FZ &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<DBGMCU_t*>(STM32::DBGMCU_BASE)->APB2FZ & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
    };
    /* DCMI DEFINITION */
    class DCMI
    {
    private:
        struct DCMI_t
        {
            __IO uint32_t                 CR;
            __IO uint32_t                 SR;
            __IO uint32_t                 RISR;
            __IO uint32_t                 IER;
            __IO uint32_t                 MISR;
            __IO uint32_t                 ICR;
            __IO uint32_t                 ESCR;
            __IO uint32_t                 ESUR;
            __IO uint32_t                 CWSTRTR;
            __IO uint32_t                 CWSIZER;
            __IO uint32_t                 DR;
        };
    public:
        class CR
        {
        private:
            union CR_t
            {
                struct
                {
                    uint32_t CAPTURE        : 1;
                    uint32_t CM             : 1;
                    uint32_t CROP           : 1;
                    uint32_t JPEG           : 1;
                    uint32_t ESS            : 1;
                    uint32_t PCKPOL         : 1;
                    uint32_t HSPOL          : 1;
                    uint32_t VSPOL          : 1;
                    uint32_t reserved8      : 4;
                    uint32_t CRE            : 1;
                    uint32_t reserved13     : 1;
                    uint32_t ENABLE         : 1;
                    uint32_t reserved15     : 17;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                CAPTURE                = (0x1U << 0),
                CM                     = (0x1U << 1),
                CROP                   = (0x1U << 2),
                JPEG                   = (0x1U << 3),
                ESS                    = (0x1U << 4),
                PCKPOL                 = (0x1U << 5),
                HSPOL                  = (0x1U << 6),
                VSPOL                  = (0x1U << 7),
                CRE                    = (0x1U << 12),
                ENABLE                 = (0x1U << 14),
            };
            static inline uint32_t get() { return reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->CR; }
            static inline void set(uint32_t value) { reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->CR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->CR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->CR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->CR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class SR
        {
        private:
            union SR_t
            {
                struct
                {
                    uint32_t HSYNC          : 1;
                    uint32_t VSYNC          : 1;
                    uint32_t FNE            : 1;
                    uint32_t reserved3      : 29;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                HSYNC                  = (0x1U << 0),
                VSYNC                  = (0x1U << 1),
                FNE                    = (0x1U << 2),
            };
            static inline uint32_t get() { return reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->SR; }
            static inline void set(uint32_t value) { reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->SR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->SR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->SR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->SR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class RISR
        {
        private:
            union RISR_t
            {
                struct
                {
                    uint32_t FRAME_RIS      : 1;
                    uint32_t OVR_RIS        : 1;
                    uint32_t ERR_RIS        : 1;
                    uint32_t VSYNC_RIS      : 1;
                    uint32_t LINE_RIS       : 1;
                    uint32_t reserved5      : 27;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                FRAME_RIS              = (0x1U << 0),
                OVR_RIS                = (0x1U << 1),
                ERR_RIS                = (0x1U << 2),
                VSYNC_RIS              = (0x1U << 3),
                LINE_RIS               = (0x1U << 4),
            };
            static inline uint32_t get() { return reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->RISR; }
            static inline void set(uint32_t value) { reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->RISR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->RISR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->RISR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->RISR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class IER
        {
        private:
            union IER_t
            {
                struct
                {
                    uint32_t FRAME_IE       : 1;
                    uint32_t OVR_IE         : 1;
                    uint32_t ERR_IE         : 1;
                    uint32_t VSYNC_IE       : 1;
                    uint32_t LINE_IE        : 1;
                    uint32_t reserved5      : 27;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                FRAME_IE               = (0x1U << 0),
                OVR_IE                 = (0x1U << 1),
                ERR_IE                 = (0x1U << 2),
                VSYNC_IE               = (0x1U << 3),
                LINE_IE                = (0x1U << 4),
            };
            static inline uint32_t get() { return reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->IER; }
            static inline void set(uint32_t value) { reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->IER = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->IER |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->IER &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->IER & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class MISR
        {
        private:
            union MISR_t
            {
                struct
                {
                    uint32_t FRAME_MIS      : 1;
                    uint32_t OVR_MIS        : 1;
                    uint32_t ERR_MIS        : 1;
                    uint32_t VSYNC_MIS      : 1;
                    uint32_t LINE_MIS       : 1;
                    uint32_t reserved5      : 27;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                FRAME_MIS              = (0x1U << 0),
                OVR_MIS                = (0x1U << 1),
                ERR_MIS                = (0x1U << 2),
                VSYNC_MIS              = (0x1U << 3),
                LINE_MIS               = (0x1U << 4),
            };
            static inline uint32_t get() { return reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->MISR; }
            static inline void set(uint32_t value) { reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->MISR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->MISR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->MISR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->MISR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class ICR
        {
        private:
            union ICR_t
            {
                struct
                {
                    uint32_t FRAME_ISC      : 1;
                    uint32_t OVR_ISC        : 1;
                    uint32_t ERR_ISC        : 1;
                    uint32_t VSYNC_ISC      : 1;
                    uint32_t LINE_ISC       : 1;
                    uint32_t reserved5      : 27;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                FRAME_ISC              = (0x1U << 0),
                OVR_ISC                = (0x1U << 1),
                ERR_ISC                = (0x1U << 2),
                VSYNC_ISC              = (0x1U << 3),
                LINE_ISC               = (0x1U << 4),
            };
            static inline uint32_t get() { return reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->ICR; }
            static inline void set(uint32_t value) { reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->ICR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->ICR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->ICR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->ICR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class ESCR
        {
        private:
            union ESCR_t
            {
                struct
                {
                    uint32_t FSC            : 8;
                    uint32_t LSC            : 8;
                    uint32_t LEC            : 8;
                    uint32_t FEC            : 8;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                FSC                    = (0xFFU << 0),
                LSC                    = (0xFFU << 8),
                LEC                    = (0xFFU << 16),
                FEC                    = (0xFFU << 24),
            };
            static inline uint32_t get() { return reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->ESCR; }
            static inline void set(uint32_t value) { reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->ESCR = value; }
            static inline uint32_t get_FSC() { return reinterpret_cast<__IO ESCR_t*>(&reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->ESCR)->FSC; }
            static inline void set_FSC(uint32_t value) { reinterpret_cast<__IO ESCR_t*>(&reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->ESCR)->FSC = value; }
            static inline uint32_t get_LSC() { return reinterpret_cast<__IO ESCR_t*>(&reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->ESCR)->LSC; }
            static inline void set_LSC(uint32_t value) { reinterpret_cast<__IO ESCR_t*>(&reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->ESCR)->LSC = value; }
            static inline uint32_t get_LEC() { return reinterpret_cast<__IO ESCR_t*>(&reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->ESCR)->LEC; }
            static inline void set_LEC(uint32_t value) { reinterpret_cast<__IO ESCR_t*>(&reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->ESCR)->LEC = value; }
            static inline uint32_t get_FEC() { return reinterpret_cast<__IO ESCR_t*>(&reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->ESCR)->FEC; }
            static inline void set_FEC(uint32_t value) { reinterpret_cast<__IO ESCR_t*>(&reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->ESCR)->FEC = value; }
        };
        class ESUR
        {
        private:
            union ESUR_t
            {
                struct
                {
                    uint32_t FSU            : 8;
                    uint32_t LSU            : 8;
                    uint32_t LEU            : 8;
                    uint32_t FEU            : 8;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                FSU                    = (0xFFU << 0),
                LSU                    = (0xFFU << 8),
                LEU                    = (0xFFU << 16),
                FEU                    = (0xFFU << 24),
            };
            static inline uint32_t get() { return reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->ESUR; }
            static inline void set(uint32_t value) { reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->ESUR = value; }
            static inline uint32_t get_FSU() { return reinterpret_cast<__IO ESUR_t*>(&reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->ESUR)->FSU; }
            static inline void set_FSU(uint32_t value) { reinterpret_cast<__IO ESUR_t*>(&reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->ESUR)->FSU = value; }
            static inline uint32_t get_LSU() { return reinterpret_cast<__IO ESUR_t*>(&reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->ESUR)->LSU; }
            static inline void set_LSU(uint32_t value) { reinterpret_cast<__IO ESUR_t*>(&reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->ESUR)->LSU = value; }
            static inline uint32_t get_LEU() { return reinterpret_cast<__IO ESUR_t*>(&reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->ESUR)->LEU; }
            static inline void set_LEU(uint32_t value) { reinterpret_cast<__IO ESUR_t*>(&reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->ESUR)->LEU = value; }
            static inline uint32_t get_FEU() { return reinterpret_cast<__IO ESUR_t*>(&reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->ESUR)->FEU; }
            static inline void set_FEU(uint32_t value) { reinterpret_cast<__IO ESUR_t*>(&reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->ESUR)->FEU = value; }
        };
        class CWSTRTR
        {
        private:
            union CWSTRTR_t
            {
                struct
                {
                    uint32_t HOFFCNT        : 14;
                    uint32_t reserved14     : 2;
                    uint32_t VST            : 13;
                    uint32_t reserved29     : 3;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                HOFFCNT                = (0x3FFFU << 0),
                VST                    = (0x1FFFU << 16),
            };
            static inline uint32_t get() { return reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->CWSTRTR; }
            static inline void set(uint32_t value) { reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->CWSTRTR = value; }
            static inline uint32_t get_HOFFCNT() { return reinterpret_cast<__IO CWSTRTR_t*>(&reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->CWSTRTR)->HOFFCNT; }
            static inline void set_HOFFCNT(uint32_t value) { reinterpret_cast<__IO CWSTRTR_t*>(&reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->CWSTRTR)->HOFFCNT = value; }
            static inline uint32_t get_VST() { return reinterpret_cast<__IO CWSTRTR_t*>(&reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->CWSTRTR)->VST; }
            static inline void set_VST(uint32_t value) { reinterpret_cast<__IO CWSTRTR_t*>(&reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->CWSTRTR)->VST = value; }
        };
        class CWSIZER
        {
        private:
            union CWSIZER_t
            {
                struct
                {
                    uint32_t CAPCNT         : 14;
                    uint32_t reserved14     : 2;
                    uint32_t VLINE          : 14;
                    uint32_t reserved30     : 2;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                CAPCNT                 = (0x3FFFU << 0),
                VLINE                  = (0x3FFFU << 16),
            };
            static inline uint32_t get() { return reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->CWSIZER; }
            static inline void set(uint32_t value) { reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->CWSIZER = value; }
            static inline uint32_t get_CAPCNT() { return reinterpret_cast<__IO CWSIZER_t*>(&reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->CWSIZER)->CAPCNT; }
            static inline void set_CAPCNT(uint32_t value) { reinterpret_cast<__IO CWSIZER_t*>(&reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->CWSIZER)->CAPCNT = value; }
            static inline uint32_t get_VLINE() { return reinterpret_cast<__IO CWSIZER_t*>(&reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->CWSIZER)->VLINE; }
            static inline void set_VLINE(uint32_t value) { reinterpret_cast<__IO CWSIZER_t*>(&reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->CWSIZER)->VLINE = value; }
        };
        class DR
        {
        private:
            union DR_t
            {
                struct
                {
                    uint32_t BYTE0          : 8;
                    uint32_t BYTE1          : 8;
                    uint32_t BYTE2          : 8;
                    uint32_t BYTE3          : 8;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                BYTE0                  = (0xFFU << 0),
                BYTE1                  = (0xFFU << 8),
                BYTE2                  = (0xFFU << 16),
                BYTE3                  = (0xFFU << 24),
            };
            static inline uint32_t get() { return reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->DR; }
            static inline void set(uint32_t value) { reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->DR = value; }
            static inline uint32_t get_BYTE0() { return reinterpret_cast<__IO DR_t*>(&reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->DR)->BYTE0; }
            static inline void set_BYTE0(uint32_t value) { reinterpret_cast<__IO DR_t*>(&reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->DR)->BYTE0 = value; }
            static inline uint32_t get_BYTE1() { return reinterpret_cast<__IO DR_t*>(&reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->DR)->BYTE1; }
            static inline void set_BYTE1(uint32_t value) { reinterpret_cast<__IO DR_t*>(&reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->DR)->BYTE1 = value; }
            static inline uint32_t get_BYTE2() { return reinterpret_cast<__IO DR_t*>(&reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->DR)->BYTE2; }
            static inline void set_BYTE2(uint32_t value) { reinterpret_cast<__IO DR_t*>(&reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->DR)->BYTE2 = value; }
            static inline uint32_t get_BYTE3() { return reinterpret_cast<__IO DR_t*>(&reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->DR)->BYTE3; }
            static inline void set_BYTE3(uint32_t value) { reinterpret_cast<__IO DR_t*>(&reinterpret_cast<DCMI_t*>(STM32::DCMI_BASE)->DR)->BYTE3 = value; }
        };
    };
    /* DMA_Stream DEFINITION */
    template <uint32_t reg_base>
    class DMA_Stream
    {
    };
    /* DMA DEFINITION */
    template <uint32_t reg_base>
    class DMA
    {
    };
    /* ETH DEFINITION */
    class ETH
    {
    private:
        struct ETH_t
        {
            __IO uint32_t                 MACCR;
            __IO uint32_t                 MACFFR;
            __IO uint32_t                 MACHTHR;
            __IO uint32_t                 MACHTLR;
            __IO uint32_t                 MACMIIAR;
            __IO uint32_t                 MACMIIDR;
            __IO uint32_t                 MACFCR;
            __IO uint32_t                 MACVLANTR;
            uint32_t                      RESERVED0[2];
            __IO uint32_t                 MACRWUFFR;
            __IO uint32_t                 MACPMTCSR;
            uint32_t                      RESERVED1;
            __IO uint32_t                 MACDBGR;
            __IO uint32_t                 MACSR;
            __IO uint32_t                 MACIMR;
            __IO uint32_t                 MACA0HR;
            __IO uint32_t                 MACA0LR;
            __IO uint32_t                 MACA1HR;
            __IO uint32_t                 MACA1LR;
            __IO uint32_t                 MACA2HR;
            __IO uint32_t                 MACA2LR;
            __IO uint32_t                 MACA3HR;
            __IO uint32_t                 MACA3LR;
            uint32_t                      RESERVED2[40];
            __IO uint32_t                 MMCCR;
            __IO uint32_t                 MMCRIR;
            __IO uint32_t                 MMCTIR;
            __IO uint32_t                 MMCRIMR;
            __IO uint32_t                 MMCTIMR;
            uint32_t                      RESERVED3[14];
            __IO uint32_t                 MMCTGFSCCR;
            __IO uint32_t                 MMCTGFMSCCR;
            uint32_t                      RESERVED4[5];
            __IO uint32_t                 MMCTGFCR;
            uint32_t                      RESERVED5[10];
            __IO uint32_t                 MMCRFCECR;
            __IO uint32_t                 MMCRFAECR;
            uint32_t                      RESERVED6[10];
            __IO uint32_t                 MMCRGUFCR;
            uint32_t                      RESERVED7[334];
            __IO uint32_t                 PTPTSCR;
            __IO uint32_t                 PTPSSIR;
            __IO uint32_t                 PTPTSHR;
            __IO uint32_t                 PTPTSLR;
            __IO uint32_t                 PTPTSHUR;
            __IO uint32_t                 PTPTSLUR;
            __IO uint32_t                 PTPTSAR;
            __IO uint32_t                 PTPTTHR;
            __IO uint32_t                 PTPTTLR;
            __IO uint32_t                 RESERVED8;
            __IO uint32_t                 PTPTSSR;
            uint32_t                      RESERVED9[565];
            __IO uint32_t                 DMABMR;
            __IO uint32_t                 DMATPDR;
            __IO uint32_t                 DMARPDR;
            __IO uint32_t                 DMARDLAR;
            __IO uint32_t                 DMATDLAR;
            __IO uint32_t                 DMASR;
            __IO uint32_t                 DMAOMR;
            __IO uint32_t                 DMAIER;
            __IO uint32_t                 DMAMFBOCR;
            __IO uint32_t                 DMARSWTR;
            uint32_t                      RESERVED10[8];
            __IO uint32_t                 DMACHTDR;
            __IO uint32_t                 DMACHRDR;
            __IO uint32_t                 DMACHTBAR;
            __IO uint32_t                 DMACHRBAR;
        };
    public:
        class MACCR
        {
        private:
            union MACCR_t
            {
                struct
                {
                    uint32_t reserved0      : 23;
                    uint32_t WD             : 1;
                    uint32_t JD             : 1;
                    uint32_t IFG            : 3;
                    uint32_t CSD            : 1;
                    uint32_t FES            : 1;
                    uint32_t ROD            : 1;
                    uint32_t LM             : 1;
                    uint32_t DM             : 1;
                    uint32_t IPCO           : 1;
                    uint32_t RD             : 1;
                    uint32_t APCS           : 1;
                    uint32_t BL             : 2;
                    uint32_t DC             : 1;
                    uint32_t TE             : 1;
                    uint32_t RE             : 1;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                WD                     = (0x1U << 23),
                JD                     = (0x1U << 22),
                IFG                    = (0x7U << 17),
                CSD                    = (0x1U << 16),
                FES                    = (0x1U << 14),
                ROD                    = (0x1U << 13),
                LM                     = (0x1U << 12),
                DM                     = (0x1U << 11),
                IPCO                   = (0x1U << 10),
                RD                     = (0x1U << 9),
                APCS                   = (0x1U << 7),
                BL                     = (0x3U << 5),
                DC                     = (0x1U << 4),
                TE                     = (0x1U << 3),
                RE                     = (0x1U << 2),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACCR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACCR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACCR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACCR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACCR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_IFG() { return reinterpret_cast<__IO MACCR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACCR)->IFG; }
            static inline void set_IFG(uint32_t value) { reinterpret_cast<__IO MACCR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACCR)->IFG = value; }
            static inline uint32_t get_BL() { return reinterpret_cast<__IO MACCR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACCR)->BL; }
            static inline void set_BL(uint32_t value) { reinterpret_cast<__IO MACCR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACCR)->BL = value; }
        };
        class MACFFR
        {
        private:
            union MACFFR_t
            {
                struct
                {
                    uint32_t reserved0      : 31;
                    uint32_t RA             : 1;
                    uint32_t HPF            : 1;
                    uint32_t SAF            : 1;
                    uint32_t SAIF           : 1;
                    uint32_t PCF            : 2;
                    uint32_t PCF_BlockAll   : 1;
                    uint32_t PCF_ForwardAll : 1;
                    uint32_t PCF_ForwardPassedAddrFilter: 2;
                    uint32_t BFD            : 1;
                    uint32_t PAM            : 1;
                    uint32_t DAIF           : 1;
                    uint32_t HM             : 1;
                    uint32_t HU             : 1;
                    uint32_t PM             : 1;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                RA                     = (0x1U << 31),
                HPF                    = (0x1U << 10),
                SAF                    = (0x1U << 9),
                SAIF                   = (0x1U << 8),
                PCF                    = (0x3U << 6),
                PCF_BlockAll           = (0x1U << 6),
                PCF_ForwardAll         = (0x1U << 7),
                PCF_ForwardPassedAddrFilter = (0x3U << 6),
                BFD                    = (0x1U << 5),
                PAM                    = (0x1U << 4),
                DAIF                   = (0x1U << 3),
                HM                     = (0x1U << 2),
                HU                     = (0x1U << 1),
                PM                     = (0x1U << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACFFR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACFFR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACFFR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACFFR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACFFR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_PCF() { return reinterpret_cast<__IO MACFFR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACFFR)->PCF; }
            static inline void set_PCF(uint32_t value) { reinterpret_cast<__IO MACFFR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACFFR)->PCF = value; }
            static inline uint32_t get_PCF_ForwardPassedAddrFilter() { return reinterpret_cast<__IO MACFFR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACFFR)->PCF_ForwardPassedAddrFilter; }
            static inline void set_PCF_ForwardPassedAddrFilter(uint32_t value) { reinterpret_cast<__IO MACFFR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACFFR)->PCF_ForwardPassedAddrFilter = value; }
        };
        class MACHTHR
        {
        private:
            union MACHTHR_t
            {
                struct
                {
                    uint32_t HTH            : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                HTH                    = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACHTHR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACHTHR = value; }
            static inline uint32_t get_HTH() { return reinterpret_cast<__IO MACHTHR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACHTHR)->HTH; }
            static inline void set_HTH(uint32_t value) { reinterpret_cast<__IO MACHTHR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACHTHR)->HTH = value; }
        };
        class MACHTLR
        {
        private:
            union MACHTLR_t
            {
                struct
                {
                    uint32_t HTL            : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                HTL                    = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACHTLR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACHTLR = value; }
            static inline uint32_t get_HTL() { return reinterpret_cast<__IO MACHTLR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACHTLR)->HTL; }
            static inline void set_HTL(uint32_t value) { reinterpret_cast<__IO MACHTLR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACHTLR)->HTL = value; }
        };
        class MACMIIAR
        {
        private:
            union MACMIIAR_t
            {
                struct
                {
                    uint32_t reserved0      : 11;
                    uint32_t PA             : 5;
                    uint32_t MR             : 5;
                    uint32_t CR             : 3;
                    uint32_t CR_Div62       : 1;
                    uint32_t CR_Div16       : 1;
                    uint32_t CR_Div26       : 2;
                    uint32_t CR_Div102      : 1;
                    uint32_t MW             : 1;
                    uint32_t MB             : 1;
                    uint32_t reserved31     : 1;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                PA                     = (0x1FU << 11),
                MR                     = (0x1FU << 6),
                CR                     = (0x7U << 2),
                CR_Div62               = (0x1U << 2),
                CR_Div16               = (0x1U << 3),
                CR_Div26               = (0x3U << 2),
                CR_Div102              = (0x1U << 4),
                MW                     = (0x1U << 1),
                MB                     = (0x1U << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACMIIAR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACMIIAR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACMIIAR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACMIIAR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACMIIAR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_PA() { return reinterpret_cast<__IO MACMIIAR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACMIIAR)->PA; }
            static inline void set_PA(uint32_t value) { reinterpret_cast<__IO MACMIIAR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACMIIAR)->PA = value; }
            static inline uint32_t get_MR() { return reinterpret_cast<__IO MACMIIAR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACMIIAR)->MR; }
            static inline void set_MR(uint32_t value) { reinterpret_cast<__IO MACMIIAR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACMIIAR)->MR = value; }
            static inline uint32_t get_CR() { return reinterpret_cast<__IO MACMIIAR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACMIIAR)->CR; }
            static inline void set_CR(uint32_t value) { reinterpret_cast<__IO MACMIIAR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACMIIAR)->CR = value; }
            static inline uint32_t get_CR_Div26() { return reinterpret_cast<__IO MACMIIAR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACMIIAR)->CR_Div26; }
            static inline void set_CR_Div26(uint32_t value) { reinterpret_cast<__IO MACMIIAR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACMIIAR)->CR_Div26 = value; }
        };
        class MACMIIDR
        {
        private:
            union MACMIIDR_t
            {
                struct
                {
                    uint32_t MD             : 16;
                    uint32_t reserved16     : 16;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                MD                     = (0xFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACMIIDR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACMIIDR = value; }
            static inline uint32_t get_MD() { return reinterpret_cast<__IO MACMIIDR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACMIIDR)->MD; }
            static inline void set_MD(uint32_t value) { reinterpret_cast<__IO MACMIIDR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACMIIDR)->MD = value; }
        };
        class MACFCR
        {
        private:
            union MACFCR_t
            {
                struct
                {
                    uint32_t reserved0      : 16;
                    uint32_t PT             : 16;
                    uint32_t ZQPD           : 1;
                    uint32_t PLT            : 2;
                    uint32_t PLT_Minus28    : 1;
                    uint32_t PLT_Minus144   : 1;
                    uint32_t PLT_Minus256   : 2;
                    uint32_t UPFD           : 1;
                    uint32_t RFCE           : 1;
                    uint32_t TFCE           : 1;
                    uint32_t FCBBPA         : 1;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                PT                     = (0xFFFFU << 16),
                ZQPD                   = (0x1U << 7),
                PLT                    = (0x3U << 4),
                PLT_Minus28            = (0x1U << 4),
                PLT_Minus144           = (0x1U << 5),
                PLT_Minus256           = (0x3U << 4),
                UPFD                   = (0x1U << 3),
                RFCE                   = (0x1U << 2),
                TFCE                   = (0x1U << 1),
                FCBBPA                 = (0x1U << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACFCR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACFCR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACFCR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACFCR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACFCR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_PT() { return reinterpret_cast<__IO MACFCR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACFCR)->PT; }
            static inline void set_PT(uint32_t value) { reinterpret_cast<__IO MACFCR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACFCR)->PT = value; }
            static inline uint32_t get_PLT() { return reinterpret_cast<__IO MACFCR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACFCR)->PLT; }
            static inline void set_PLT(uint32_t value) { reinterpret_cast<__IO MACFCR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACFCR)->PLT = value; }
            static inline uint32_t get_PLT_Minus256() { return reinterpret_cast<__IO MACFCR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACFCR)->PLT_Minus256; }
            static inline void set_PLT_Minus256(uint32_t value) { reinterpret_cast<__IO MACFCR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACFCR)->PLT_Minus256 = value; }
        };
        class MACVLANTR
        {
        private:
            union MACVLANTR_t
            {
                struct
                {
                    uint32_t reserved0      : 16;
                    uint32_t VLANTC         : 1;
                    uint32_t VLANTI         : 16;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                VLANTC                 = (0x1U << 16),
                VLANTI                 = (0xFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACVLANTR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACVLANTR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACVLANTR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACVLANTR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACVLANTR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_VLANTI() { return reinterpret_cast<__IO MACVLANTR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACVLANTR)->VLANTI; }
            static inline void set_VLANTI(uint32_t value) { reinterpret_cast<__IO MACVLANTR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACVLANTR)->VLANTI = value; }
        };
        class MACRWUFFR
        {
        private:
            union MACRWUFFR_t
            {
                struct
                {
                    uint32_t D              : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                D                      = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACRWUFFR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACRWUFFR = value; }
            static inline uint32_t get_D() { return reinterpret_cast<__IO MACRWUFFR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACRWUFFR)->D; }
            static inline void set_D(uint32_t value) { reinterpret_cast<__IO MACRWUFFR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACRWUFFR)->D = value; }
        };
        class MACPMTCSR
        {
        private:
            union MACPMTCSR_t
            {
                struct
                {
                    uint32_t reserved0      : 31;
                    uint32_t WFFRPR         : 1;
                    uint32_t GU             : 1;
                    uint32_t WFR            : 1;
                    uint32_t MPR            : 1;
                    uint32_t WFE            : 1;
                    uint32_t MPE            : 1;
                    uint32_t PD             : 1;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                WFFRPR                 = (0x1U << 31),
                GU                     = (0x1U << 9),
                WFR                    = (0x1U << 6),
                MPR                    = (0x1U << 5),
                WFE                    = (0x1U << 2),
                MPE                    = (0x1U << 1),
                PD                     = (0x1U << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACPMTCSR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACPMTCSR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACPMTCSR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACPMTCSR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACPMTCSR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class MACDBGR
        {
        private:
            union MACDBGR_t
            {
                struct
                {
                    uint32_t reserved0      : 25;
                    uint32_t TFF            : 1;
                    uint32_t TFNE           : 1;
                    uint32_t TFWA           : 1;
                    uint32_t TFRS           : 2;
                    uint32_t TFRS_WRITING   : 2;
                    uint32_t TFRS_WAITING   : 1;
                    uint32_t TFRS_READ      : 1;
                    uint32_t MTP            : 1;
                    uint32_t MTFCS          : 2;
                    uint32_t MTFCS_TRANSFERRING: 2;
                    uint32_t MTFCS_GENERATINGPCF: 1;
                    uint32_t MTFCS_WAITING  : 1;
                    uint32_t MMTEA          : 1;
                    uint32_t RFFL           : 2;
                    uint32_t RFFL_FULL      : 2;
                    uint32_t RFFL_ABOVEFCT  : 1;
                    uint32_t RFFL_BELOWFCT  : 1;
                    uint32_t RFRCS          : 2;
                    uint32_t RFRCS_FLUSHING : 2;
                    uint32_t RFRCS_STATUSREADING: 1;
                    uint32_t RFRCS_DATAREADING: 1;
                    uint32_t RFWRA          : 1;
                    uint32_t MSFRWCS        : 2;
                    uint32_t MMRPEA         : 1;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                TFF                    = (0x1U << 25),
                TFNE                   = (0x1U << 24),
                TFWA                   = (0x1U << 22),
                TFRS                   = (0x3U << 20),
                TFRS_WRITING           = (0x3U << 20),
                TFRS_WAITING           = (0x1U << 21),
                TFRS_READ              = (0x1U << 20),
                MTP                    = (0x1U << 19),
                MTFCS                  = (0x3U << 17),
                MTFCS_TRANSFERRING     = (0x3U << 17),
                MTFCS_GENERATINGPCF    = (0x1U << 18),
                MTFCS_WAITING          = (0x1U << 17),
                MMTEA                  = (0x1U << 16),
                RFFL                   = (0x3U << 8),
                RFFL_FULL              = (0x3U << 8),
                RFFL_ABOVEFCT          = (0x1U << 9),
                RFFL_BELOWFCT          = (0x1U << 8),
                RFRCS                  = (0x3U << 5),
                RFRCS_FLUSHING         = (0x3U << 5),
                RFRCS_STATUSREADING    = (0x1U << 6),
                RFRCS_DATAREADING      = (0x1U << 5),
                RFWRA                  = (0x1U << 4),
                MSFRWCS                = (0x3U << 1),
                MMRPEA                 = (0x1U << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACDBGR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACDBGR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACDBGR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACDBGR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACDBGR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_TFRS() { return reinterpret_cast<__IO MACDBGR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACDBGR)->TFRS; }
            static inline void set_TFRS(uint32_t value) { reinterpret_cast<__IO MACDBGR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACDBGR)->TFRS = value; }
            static inline uint32_t get_TFRS_WRITING() { return reinterpret_cast<__IO MACDBGR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACDBGR)->TFRS_WRITING; }
            static inline void set_TFRS_WRITING(uint32_t value) { reinterpret_cast<__IO MACDBGR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACDBGR)->TFRS_WRITING = value; }
            static inline uint32_t get_MTFCS() { return reinterpret_cast<__IO MACDBGR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACDBGR)->MTFCS; }
            static inline void set_MTFCS(uint32_t value) { reinterpret_cast<__IO MACDBGR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACDBGR)->MTFCS = value; }
            static inline uint32_t get_MTFCS_TRANSFERRING() { return reinterpret_cast<__IO MACDBGR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACDBGR)->MTFCS_TRANSFERRING; }
            static inline void set_MTFCS_TRANSFERRING(uint32_t value) { reinterpret_cast<__IO MACDBGR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACDBGR)->MTFCS_TRANSFERRING = value; }
            static inline uint32_t get_RFFL() { return reinterpret_cast<__IO MACDBGR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACDBGR)->RFFL; }
            static inline void set_RFFL(uint32_t value) { reinterpret_cast<__IO MACDBGR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACDBGR)->RFFL = value; }
            static inline uint32_t get_RFFL_FULL() { return reinterpret_cast<__IO MACDBGR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACDBGR)->RFFL_FULL; }
            static inline void set_RFFL_FULL(uint32_t value) { reinterpret_cast<__IO MACDBGR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACDBGR)->RFFL_FULL = value; }
            static inline uint32_t get_RFRCS() { return reinterpret_cast<__IO MACDBGR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACDBGR)->RFRCS; }
            static inline void set_RFRCS(uint32_t value) { reinterpret_cast<__IO MACDBGR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACDBGR)->RFRCS = value; }
            static inline uint32_t get_RFRCS_FLUSHING() { return reinterpret_cast<__IO MACDBGR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACDBGR)->RFRCS_FLUSHING; }
            static inline void set_RFRCS_FLUSHING(uint32_t value) { reinterpret_cast<__IO MACDBGR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACDBGR)->RFRCS_FLUSHING = value; }
            static inline uint32_t get_MSFRWCS() { return reinterpret_cast<__IO MACDBGR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACDBGR)->MSFRWCS; }
            static inline void set_MSFRWCS(uint32_t value) { reinterpret_cast<__IO MACDBGR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACDBGR)->MSFRWCS = value; }
        };
        class MACSR
        {
        private:
            union MACSR_t
            {
                struct
                {
                    uint32_t reserved0      : 9;
                    uint32_t TSTS           : 1;
                    uint32_t MMCTS          : 1;
                    uint32_t MMMCRS         : 1;
                    uint32_t MMCS           : 1;
                    uint32_t PMTS           : 1;
                    uint32_t reserved14     : 18;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                TSTS                   = (0x1U << 9),
                MMCTS                  = (0x1U << 6),
                MMMCRS                 = (0x1U << 5),
                MMCS                   = (0x1U << 4),
                PMTS                   = (0x1U << 3),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACSR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACSR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACSR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACSR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACSR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class MACIMR
        {
        private:
            union MACIMR_t
            {
                struct
                {
                    uint32_t reserved0      : 9;
                    uint32_t TSTIM          : 1;
                    uint32_t PMTIM          : 1;
                    uint32_t reserved11     : 21;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                TSTIM                  = (0x1U << 9),
                PMTIM                  = (0x1U << 3),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACIMR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACIMR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACIMR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACIMR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACIMR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class MACA0HR
        {
        private:
            union MACA0HR_t
            {
                struct
                {
                    uint32_t MACA0H         : 16;
                    uint32_t reserved16     : 16;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                MACA0H                 = (0xFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA0HR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA0HR = value; }
            static inline uint32_t get_MACA0H() { return reinterpret_cast<__IO MACA0HR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA0HR)->MACA0H; }
            static inline void set_MACA0H(uint32_t value) { reinterpret_cast<__IO MACA0HR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA0HR)->MACA0H = value; }
        };
        class MACA0LR
        {
        private:
            union MACA0LR_t
            {
                struct
                {
                    uint32_t MACA0L         : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                MACA0L                 = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA0LR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA0LR = value; }
            static inline uint32_t get_MACA0L() { return reinterpret_cast<__IO MACA0LR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA0LR)->MACA0L; }
            static inline void set_MACA0L(uint32_t value) { reinterpret_cast<__IO MACA0LR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA0LR)->MACA0L = value; }
        };
        class MACA1HR
        {
        private:
            union MACA1HR_t
            {
                struct
                {
                    uint32_t reserved0      : 31;
                    uint32_t AE             : 1;
                    uint32_t SA             : 1;
                    uint32_t MBC            : 6;
                    uint32_t MACA1H         : 16;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                AE                     = (0x1U << 31),
                SA                     = (0x1U << 30),
                MBC                    = (0x3FU << 24),
                MACA1H                 = (0xFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA1HR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA1HR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA1HR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA1HR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA1HR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_MBC() { return reinterpret_cast<__IO MACA1HR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA1HR)->MBC; }
            static inline void set_MBC(uint32_t value) { reinterpret_cast<__IO MACA1HR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA1HR)->MBC = value; }
            static inline uint32_t get_MACA1H() { return reinterpret_cast<__IO MACA1HR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA1HR)->MACA1H; }
            static inline void set_MACA1H(uint32_t value) { reinterpret_cast<__IO MACA1HR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA1HR)->MACA1H = value; }
        };
        class MACA1LR
        {
        private:
            union MACA1LR_t
            {
                struct
                {
                    uint32_t MACA1L         : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                MACA1L                 = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA1LR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA1LR = value; }
            static inline uint32_t get_MACA1L() { return reinterpret_cast<__IO MACA1LR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA1LR)->MACA1L; }
            static inline void set_MACA1L(uint32_t value) { reinterpret_cast<__IO MACA1LR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA1LR)->MACA1L = value; }
        };
        class MACA2HR
        {
        private:
            union MACA2HR_t
            {
                struct
                {
                    uint32_t reserved0      : 31;
                    uint32_t AE             : 1;
                    uint32_t SA             : 1;
                    uint32_t MBC            : 6;
                    uint32_t MACA2H         : 16;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                AE                     = (0x1U << 31),
                SA                     = (0x1U << 30),
                MBC                    = (0x3FU << 24),
                MACA2H                 = (0xFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA2HR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA2HR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA2HR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA2HR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA2HR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_MBC() { return reinterpret_cast<__IO MACA2HR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA2HR)->MBC; }
            static inline void set_MBC(uint32_t value) { reinterpret_cast<__IO MACA2HR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA2HR)->MBC = value; }
            static inline uint32_t get_MACA2H() { return reinterpret_cast<__IO MACA2HR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA2HR)->MACA2H; }
            static inline void set_MACA2H(uint32_t value) { reinterpret_cast<__IO MACA2HR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA2HR)->MACA2H = value; }
        };
        class MACA2LR
        {
        private:
            union MACA2LR_t
            {
                struct
                {
                    uint32_t MACA2L         : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                MACA2L                 = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA2LR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA2LR = value; }
            static inline uint32_t get_MACA2L() { return reinterpret_cast<__IO MACA2LR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA2LR)->MACA2L; }
            static inline void set_MACA2L(uint32_t value) { reinterpret_cast<__IO MACA2LR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA2LR)->MACA2L = value; }
        };
        class MACA3HR
        {
        private:
            union MACA3HR_t
            {
                struct
                {
                    uint32_t reserved0      : 31;
                    uint32_t AE             : 1;
                    uint32_t SA             : 1;
                    uint32_t MBC            : 6;
                    uint32_t MACA3H         : 16;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                AE                     = (0x1U << 31),
                SA                     = (0x1U << 30),
                MBC                    = (0x3FU << 24),
                MACA3H                 = (0xFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA3HR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA3HR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA3HR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA3HR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA3HR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_MBC() { return reinterpret_cast<__IO MACA3HR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA3HR)->MBC; }
            static inline void set_MBC(uint32_t value) { reinterpret_cast<__IO MACA3HR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA3HR)->MBC = value; }
            static inline uint32_t get_MACA3H() { return reinterpret_cast<__IO MACA3HR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA3HR)->MACA3H; }
            static inline void set_MACA3H(uint32_t value) { reinterpret_cast<__IO MACA3HR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA3HR)->MACA3H = value; }
        };
        class MACA3LR
        {
        private:
            union MACA3LR_t
            {
                struct
                {
                    uint32_t MACA3L         : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                MACA3L                 = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA3LR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA3LR = value; }
            static inline uint32_t get_MACA3L() { return reinterpret_cast<__IO MACA3LR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA3LR)->MACA3L; }
            static inline void set_MACA3L(uint32_t value) { reinterpret_cast<__IO MACA3LR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MACA3LR)->MACA3L = value; }
        };
        class MMCCR
        {
        private:
            union MMCCR_t
            {
                struct
                {
                    uint32_t reserved0      : 5;
                    uint32_t MCFHP          : 1;
                    uint32_t MCP            : 1;
                    uint32_t MCF            : 1;
                    uint32_t ROR            : 1;
                    uint32_t CSR            : 1;
                    uint32_t CR             : 1;
                    uint32_t reserved11     : 21;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                MCFHP                  = (0x1U << 5),
                MCP                    = (0x1U << 4),
                MCF                    = (0x1U << 3),
                ROR                    = (0x1U << 2),
                CSR                    = (0x1U << 1),
                CR                     = (0x1U << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCCR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCCR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCCR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCCR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCCR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class MMCRIR
        {
        private:
            union MMCRIR_t
            {
                struct
                {
                    uint32_t reserved0      : 17;
                    uint32_t RGUFS          : 1;
                    uint32_t RFAES          : 1;
                    uint32_t RFCES          : 1;
                    uint32_t reserved20     : 12;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                RGUFS                  = (0x1U << 17),
                RFAES                  = (0x1U << 6),
                RFCES                  = (0x1U << 5),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCRIR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCRIR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCRIR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCRIR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCRIR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class MMCTIR
        {
        private:
            union MMCTIR_t
            {
                struct
                {
                    uint32_t reserved0      : 21;
                    uint32_t TGFS           : 1;
                    uint32_t TGFMSCS        : 1;
                    uint32_t TGFSCS         : 1;
                    uint32_t reserved24     : 8;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                TGFS                   = (0x1U << 21),
                TGFMSCS                = (0x1U << 15),
                TGFSCS                 = (0x1U << 14),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCTIR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCTIR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCTIR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCTIR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCTIR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class MMCRIMR
        {
        private:
            union MMCRIMR_t
            {
                struct
                {
                    uint32_t reserved0      : 17;
                    uint32_t RGUFM          : 1;
                    uint32_t RFAEM          : 1;
                    uint32_t RFCEM          : 1;
                    uint32_t reserved20     : 12;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                RGUFM                  = (0x1U << 17),
                RFAEM                  = (0x1U << 6),
                RFCEM                  = (0x1U << 5),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCRIMR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCRIMR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCRIMR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCRIMR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCRIMR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class MMCTIMR
        {
        private:
            union MMCTIMR_t
            {
                struct
                {
                    uint32_t reserved0      : 21;
                    uint32_t TGFM           : 1;
                    uint32_t TGFMSCM        : 1;
                    uint32_t TGFSCM         : 1;
                    uint32_t reserved24     : 8;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                TGFM                   = (0x1U << 21),
                TGFMSCM                = (0x1U << 15),
                TGFSCM                 = (0x1U << 14),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCTIMR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCTIMR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCTIMR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCTIMR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCTIMR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class MMCTGFSCCR
        {
        private:
            union MMCTGFSCCR_t
            {
                struct
                {
                    uint32_t TGFSCC         : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                TGFSCC                 = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCTGFSCCR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCTGFSCCR = value; }
            static inline uint32_t get_TGFSCC() { return reinterpret_cast<__IO MMCTGFSCCR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCTGFSCCR)->TGFSCC; }
            static inline void set_TGFSCC(uint32_t value) { reinterpret_cast<__IO MMCTGFSCCR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCTGFSCCR)->TGFSCC = value; }
        };
        class MMCTGFMSCCR
        {
        private:
            union MMCTGFMSCCR_t
            {
                struct
                {
                    uint32_t TGFMSCC        : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                TGFMSCC                = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCTGFMSCCR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCTGFMSCCR = value; }
            static inline uint32_t get_TGFMSCC() { return reinterpret_cast<__IO MMCTGFMSCCR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCTGFMSCCR)->TGFMSCC; }
            static inline void set_TGFMSCC(uint32_t value) { reinterpret_cast<__IO MMCTGFMSCCR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCTGFMSCCR)->TGFMSCC = value; }
        };
        class MMCTGFCR
        {
        private:
            union MMCTGFCR_t
            {
                struct
                {
                    uint32_t TGFC           : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                TGFC                   = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCTGFCR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCTGFCR = value; }
            static inline uint32_t get_TGFC() { return reinterpret_cast<__IO MMCTGFCR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCTGFCR)->TGFC; }
            static inline void set_TGFC(uint32_t value) { reinterpret_cast<__IO MMCTGFCR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCTGFCR)->TGFC = value; }
        };
        class MMCRFCECR
        {
        private:
            union MMCRFCECR_t
            {
                struct
                {
                    uint32_t RFCEC          : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                RFCEC                  = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCRFCECR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCRFCECR = value; }
            static inline uint32_t get_RFCEC() { return reinterpret_cast<__IO MMCRFCECR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCRFCECR)->RFCEC; }
            static inline void set_RFCEC(uint32_t value) { reinterpret_cast<__IO MMCRFCECR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCRFCECR)->RFCEC = value; }
        };
        class MMCRFAECR
        {
        private:
            union MMCRFAECR_t
            {
                struct
                {
                    uint32_t RFAEC          : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                RFAEC                  = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCRFAECR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCRFAECR = value; }
            static inline uint32_t get_RFAEC() { return reinterpret_cast<__IO MMCRFAECR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCRFAECR)->RFAEC; }
            static inline void set_RFAEC(uint32_t value) { reinterpret_cast<__IO MMCRFAECR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCRFAECR)->RFAEC = value; }
        };
        class MMCRGUFCR
        {
        private:
            union MMCRGUFCR_t
            {
                struct
                {
                    uint32_t RGUFC          : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                RGUFC                  = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCRGUFCR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCRGUFCR = value; }
            static inline uint32_t get_RGUFC() { return reinterpret_cast<__IO MMCRGUFCR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCRGUFCR)->RGUFC; }
            static inline void set_RGUFC(uint32_t value) { reinterpret_cast<__IO MMCRGUFCR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->MMCRGUFCR)->RGUFC = value; }
        };
        class PTPTSCR
        {
        private:
            union PTPTSCR_t
            {
                struct
                {
                    uint32_t reserved0      : 16;
                    uint32_t TSCNT          : 2;
                    uint32_t TSARU          : 1;
                    uint32_t TSITE          : 1;
                    uint32_t TSSTU          : 1;
                    uint32_t TSSTI          : 1;
                    uint32_t TSFCU          : 1;
                    uint32_t TSE            : 1;
                    uint32_t reserved24     : 8;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                TSCNT                  = (0x3U << 16),
                TSARU                  = (0x1U << 5),
                TSITE                  = (0x1U << 4),
                TSSTU                  = (0x1U << 3),
                TSSTI                  = (0x1U << 2),
                TSFCU                  = (0x1U << 1),
                TSE                    = (0x1U << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSCR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSCR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSCR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSCR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSCR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_TSCNT() { return reinterpret_cast<__IO PTPTSCR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSCR)->TSCNT; }
            static inline void set_TSCNT(uint32_t value) { reinterpret_cast<__IO PTPTSCR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSCR)->TSCNT = value; }
        };
        class PTPSSIR
        {
        private:
            union PTPSSIR_t
            {
                struct
                {
                    uint32_t STSSI          : 8;
                    uint32_t reserved8      : 24;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                STSSI                  = (0xFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPSSIR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPSSIR = value; }
            static inline uint32_t get_STSSI() { return reinterpret_cast<__IO PTPSSIR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPSSIR)->STSSI; }
            static inline void set_STSSI(uint32_t value) { reinterpret_cast<__IO PTPSSIR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPSSIR)->STSSI = value; }
        };
        class PTPTSHR
        {
        private:
            union PTPTSHR_t
            {
                struct
                {
                    uint32_t STS            : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                STS                    = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSHR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSHR = value; }
            static inline uint32_t get_STS() { return reinterpret_cast<__IO PTPTSHR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSHR)->STS; }
            static inline void set_STS(uint32_t value) { reinterpret_cast<__IO PTPTSHR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSHR)->STS = value; }
        };
        class PTPTSLR
        {
        private:
            union PTPTSLR_t
            {
                struct
                {
                    uint32_t reserved0      : 31;
                    uint32_t STPNS          : 1;
                    uint32_t STSS           : 31;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                STPNS                  = (0x1U << 31),
                STSS                   = (0x7FFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSLR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSLR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSLR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSLR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSLR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_STSS() { return reinterpret_cast<__IO PTPTSLR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSLR)->STSS; }
            static inline void set_STSS(uint32_t value) { reinterpret_cast<__IO PTPTSLR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSLR)->STSS = value; }
        };
        class PTPTSHUR
        {
        private:
            union PTPTSHUR_t
            {
                struct
                {
                    uint32_t TSUS           : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                TSUS                   = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSHUR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSHUR = value; }
            static inline uint32_t get_TSUS() { return reinterpret_cast<__IO PTPTSHUR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSHUR)->TSUS; }
            static inline void set_TSUS(uint32_t value) { reinterpret_cast<__IO PTPTSHUR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSHUR)->TSUS = value; }
        };
        class PTPTSLUR
        {
        private:
            union PTPTSLUR_t
            {
                struct
                {
                    uint32_t reserved0      : 31;
                    uint32_t TSUPNS         : 1;
                    uint32_t TSUSS          : 31;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                TSUPNS                 = (0x1U << 31),
                TSUSS                  = (0x7FFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSLUR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSLUR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSLUR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSLUR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSLUR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_TSUSS() { return reinterpret_cast<__IO PTPTSLUR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSLUR)->TSUSS; }
            static inline void set_TSUSS(uint32_t value) { reinterpret_cast<__IO PTPTSLUR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSLUR)->TSUSS = value; }
        };
        class PTPTSAR
        {
        private:
            union PTPTSAR_t
            {
                struct
                {
                    uint32_t TSA            : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                TSA                    = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSAR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSAR = value; }
            static inline uint32_t get_TSA() { return reinterpret_cast<__IO PTPTSAR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSAR)->TSA; }
            static inline void set_TSA(uint32_t value) { reinterpret_cast<__IO PTPTSAR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSAR)->TSA = value; }
        };
        class PTPTTHR
        {
        private:
            union PTPTTHR_t
            {
                struct
                {
                    uint32_t TTSH           : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                TTSH                   = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTTHR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTTHR = value; }
            static inline uint32_t get_TTSH() { return reinterpret_cast<__IO PTPTTHR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTTHR)->TTSH; }
            static inline void set_TTSH(uint32_t value) { reinterpret_cast<__IO PTPTTHR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTTHR)->TTSH = value; }
        };
        class PTPTTLR
        {
        private:
            union PTPTTLR_t
            {
                struct
                {
                    uint32_t TTSL           : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                TTSL                   = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTTLR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTTLR = value; }
            static inline uint32_t get_TTSL() { return reinterpret_cast<__IO PTPTTLR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTTLR)->TTSL; }
            static inline void set_TTSL(uint32_t value) { reinterpret_cast<__IO PTPTTLR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTTLR)->TTSL = value; }
        };
        class PTPTSSR
        {
        private:
            union PTPTSSR_t
            {
                struct
                {
                    uint32_t reserved0      : 15;
                    uint32_t TSSMRME        : 1;
                    uint32_t TSSEME         : 1;
                    uint32_t TSSIPV4FE      : 1;
                    uint32_t TSSIPV6FE      : 1;
                    uint32_t TSSPTPOEFE     : 1;
                    uint32_t TSPTPPSV2E     : 1;
                    uint32_t TSSSR          : 1;
                    uint32_t TSSARFE        : 1;
                    uint32_t TSTTR          : 1;
                    uint32_t TSSO           : 1;
                    uint32_t reserved25     : 7;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                TSSMRME                = (0x1U << 15),
                TSSEME                 = (0x1U << 14),
                TSSIPV4FE              = (0x1U << 13),
                TSSIPV6FE              = (0x1U << 12),
                TSSPTPOEFE             = (0x1U << 11),
                TSPTPPSV2E             = (0x1U << 10),
                TSSSR                  = (0x1U << 9),
                TSSARFE                = (0x1U << 8),
                TSTTR                  = (0x1U << 5),
                TSSO                   = (0x1U << 4),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSSR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSSR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSSR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSSR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->PTPTSSR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class DMABMR
        {
        private:
            union DMABMR_t
            {
                struct
                {
                    uint32_t reserved0      : 25;
                    uint32_t AAB            : 1;
                    uint32_t FPM            : 1;
                    uint32_t USP            : 1;
                    uint32_t RDP            : 6;
                    uint32_t FB             : 1;
                    uint32_t RTPR           : 2;
                    uint32_t PBL            : 6;
                    uint32_t EDE            : 1;
                    uint32_t DSL            : 5;
                    uint32_t DA             : 1;
                    uint32_t SR             : 1;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                AAB                    = (0x1U << 25),
                FPM                    = (0x1U << 24),
                USP                    = (0x1U << 23),
                RDP                    = (0x3FU << 17),
                FB                     = (0x1U << 16),
                RTPR                   = (0x3U << 14),
                PBL                    = (0x3FU << 8),
                EDE                    = (0x1U << 7),
                DSL                    = (0x1FU << 2),
                DA                     = (0x1U << 1),
                SR                     = (0x1U << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMABMR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMABMR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMABMR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMABMR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMABMR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_RDP() { return reinterpret_cast<__IO DMABMR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMABMR)->RDP; }
            static inline void set_RDP(uint32_t value) { reinterpret_cast<__IO DMABMR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMABMR)->RDP = value; }
            static inline uint32_t get_RTPR() { return reinterpret_cast<__IO DMABMR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMABMR)->RTPR; }
            static inline void set_RTPR(uint32_t value) { reinterpret_cast<__IO DMABMR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMABMR)->RTPR = value; }
            static inline uint32_t get_PBL() { return reinterpret_cast<__IO DMABMR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMABMR)->PBL; }
            static inline void set_PBL(uint32_t value) { reinterpret_cast<__IO DMABMR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMABMR)->PBL = value; }
            static inline uint32_t get_DSL() { return reinterpret_cast<__IO DMABMR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMABMR)->DSL; }
            static inline void set_DSL(uint32_t value) { reinterpret_cast<__IO DMABMR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMABMR)->DSL = value; }
        };
        class DMATPDR
        {
        private:
            union DMATPDR_t
            {
                struct
                {
                    uint32_t TPD            : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                TPD                    = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMATPDR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMATPDR = value; }
            static inline uint32_t get_TPD() { return reinterpret_cast<__IO DMATPDR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMATPDR)->TPD; }
            static inline void set_TPD(uint32_t value) { reinterpret_cast<__IO DMATPDR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMATPDR)->TPD = value; }
        };
        class DMARPDR
        {
        private:
            union DMARPDR_t
            {
                struct
                {
                    uint32_t RPD            : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                RPD                    = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMARPDR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMARPDR = value; }
            static inline uint32_t get_RPD() { return reinterpret_cast<__IO DMARPDR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMARPDR)->RPD; }
            static inline void set_RPD(uint32_t value) { reinterpret_cast<__IO DMARPDR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMARPDR)->RPD = value; }
        };
        class DMARDLAR
        {
        private:
            union DMARDLAR_t
            {
                struct
                {
                    uint32_t SRL            : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                SRL                    = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMARDLAR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMARDLAR = value; }
            static inline uint32_t get_SRL() { return reinterpret_cast<__IO DMARDLAR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMARDLAR)->SRL; }
            static inline void set_SRL(uint32_t value) { reinterpret_cast<__IO DMARDLAR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMARDLAR)->SRL = value; }
        };
        class DMATDLAR
        {
        private:
            union DMATDLAR_t
            {
                struct
                {
                    uint32_t STL            : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                STL                    = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMATDLAR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMATDLAR = value; }
            static inline uint32_t get_STL() { return reinterpret_cast<__IO DMATDLAR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMATDLAR)->STL; }
            static inline void set_STL(uint32_t value) { reinterpret_cast<__IO DMATDLAR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMATDLAR)->STL = value; }
        };
        class DMASR
        {
        private:
            union DMASR_t
            {
                struct
                {
                    uint32_t reserved0      : 29;
                    uint32_t TSTS           : 1;
                    uint32_t PMTS           : 1;
                    uint32_t MMCS           : 1;
                    uint32_t EBS            : 3;
                    uint32_t EBS_DescAccess : 1;
                    uint32_t EBS_ReadTransf : 1;
                    uint32_t EBS_DataTransfTx: 1;
                    uint32_t TPS            : 3;
                    uint32_t TPS_Fetching   : 1;
                    uint32_t TPS_Waiting    : 1;
                    uint32_t TPS_Reading    : 2;
                    uint32_t TPS_Suspended  : 2;
                    uint32_t TPS_Closing    : 3;
                    uint32_t RPS            : 3;
                    uint32_t RPS_Fetching   : 1;
                    uint32_t RPS_Waiting    : 2;
                    uint32_t RPS_Suspended  : 1;
                    uint32_t RPS_Closing    : 1;
                    uint32_t RPS_Queuing    : 3;
                    uint32_t NIS            : 1;
                    uint32_t AIS            : 1;
                    uint32_t ERS            : 1;
                    uint32_t FBES           : 1;
                    uint32_t ETS            : 1;
                    uint32_t RWTS           : 1;
                    uint32_t RPSS           : 1;
                    uint32_t RBUS           : 1;
                    uint32_t RS             : 1;
                    uint32_t TUS            : 1;
                    uint32_t ROS            : 1;
                    uint32_t TJTS           : 1;
                    uint32_t TBUS           : 1;
                    uint32_t TPSS           : 1;
                    uint32_t TS             : 1;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                TSTS                   = (0x1U << 29),
                PMTS                   = (0x1U << 28),
                MMCS                   = (0x1U << 27),
                EBS                    = (0x7U << 23),
                EBS_DescAccess         = (0x1U << 25),
                EBS_ReadTransf         = (0x1U << 24),
                EBS_DataTransfTx       = (0x1U << 23),
                TPS                    = (0x7U << 20),
                TPS_Fetching           = (0x1U << 20),
                TPS_Waiting            = (0x1U << 21),
                TPS_Reading            = (0x3U << 20),
                TPS_Suspended          = (0x3U << 21),
                TPS_Closing            = (0x7U << 20),
                RPS                    = (0x7U << 17),
                RPS_Fetching           = (0x1U << 17),
                RPS_Waiting            = (0x3U << 17),
                RPS_Suspended          = (0x1U << 19),
                RPS_Closing            = (0x5U << 17),
                RPS_Queuing            = (0x7U << 17),
                NIS                    = (0x1U << 16),
                AIS                    = (0x1U << 15),
                ERS                    = (0x1U << 14),
                FBES                   = (0x1U << 13),
                ETS                    = (0x1U << 10),
                RWTS                   = (0x1U << 9),
                RPSS                   = (0x1U << 8),
                RBUS                   = (0x1U << 7),
                RS                     = (0x1U << 6),
                TUS                    = (0x1U << 5),
                ROS                    = (0x1U << 4),
                TJTS                   = (0x1U << 3),
                TBUS                   = (0x1U << 2),
                TPSS                   = (0x1U << 1),
                TS                     = (0x1U << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMASR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMASR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMASR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMASR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMASR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_EBS() { return reinterpret_cast<__IO DMASR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMASR)->EBS; }
            static inline void set_EBS(uint32_t value) { reinterpret_cast<__IO DMASR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMASR)->EBS = value; }
            static inline uint32_t get_TPS() { return reinterpret_cast<__IO DMASR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMASR)->TPS; }
            static inline void set_TPS(uint32_t value) { reinterpret_cast<__IO DMASR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMASR)->TPS = value; }
            static inline uint32_t get_TPS_Reading() { return reinterpret_cast<__IO DMASR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMASR)->TPS_Reading; }
            static inline void set_TPS_Reading(uint32_t value) { reinterpret_cast<__IO DMASR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMASR)->TPS_Reading = value; }
            static inline uint32_t get_TPS_Suspended() { return reinterpret_cast<__IO DMASR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMASR)->TPS_Suspended; }
            static inline void set_TPS_Suspended(uint32_t value) { reinterpret_cast<__IO DMASR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMASR)->TPS_Suspended = value; }
            static inline uint32_t get_TPS_Closing() { return reinterpret_cast<__IO DMASR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMASR)->TPS_Closing; }
            static inline void set_TPS_Closing(uint32_t value) { reinterpret_cast<__IO DMASR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMASR)->TPS_Closing = value; }
            static inline uint32_t get_RPS() { return reinterpret_cast<__IO DMASR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMASR)->RPS; }
            static inline void set_RPS(uint32_t value) { reinterpret_cast<__IO DMASR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMASR)->RPS = value; }
            static inline uint32_t get_RPS_Waiting() { return reinterpret_cast<__IO DMASR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMASR)->RPS_Waiting; }
            static inline void set_RPS_Waiting(uint32_t value) { reinterpret_cast<__IO DMASR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMASR)->RPS_Waiting = value; }
            static inline uint32_t get_RPS_Queuing() { return reinterpret_cast<__IO DMASR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMASR)->RPS_Queuing; }
            static inline void set_RPS_Queuing(uint32_t value) { reinterpret_cast<__IO DMASR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMASR)->RPS_Queuing = value; }
        };
        class DMAOMR
        {
        private:
            union DMAOMR_t
            {
                struct
                {
                    uint32_t reserved0      : 26;
                    uint32_t DTCEFD         : 1;
                    uint32_t RSF            : 1;
                    uint32_t DFRF           : 1;
                    uint32_t TSF            : 1;
                    uint32_t FTF            : 1;
                    uint32_t TTC            : 3;
                    uint32_t ST             : 1;
                    uint32_t FEF            : 1;
                    uint32_t FUGF           : 1;
                    uint32_t RTC            : 2;
                    uint32_t OSF            : 1;
                    uint32_t SR             : 1;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DTCEFD                 = (0x1U << 26),
                RSF                    = (0x1U << 25),
                DFRF                   = (0x1U << 24),
                TSF                    = (0x1U << 21),
                FTF                    = (0x1U << 20),
                TTC                    = (0x7U << 14),
                ST                     = (0x1U << 13),
                FEF                    = (0x1U << 7),
                FUGF                   = (0x1U << 6),
                RTC                    = (0x3U << 3),
                OSF                    = (0x1U << 2),
                SR                     = (0x1U << 1),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMAOMR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMAOMR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMAOMR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMAOMR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMAOMR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_TTC() { return reinterpret_cast<__IO DMAOMR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMAOMR)->TTC; }
            static inline void set_TTC(uint32_t value) { reinterpret_cast<__IO DMAOMR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMAOMR)->TTC = value; }
            static inline uint32_t get_RTC() { return reinterpret_cast<__IO DMAOMR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMAOMR)->RTC; }
            static inline void set_RTC(uint32_t value) { reinterpret_cast<__IO DMAOMR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMAOMR)->RTC = value; }
        };
        class DMAIER
        {
        private:
            union DMAIER_t
            {
                struct
                {
                    uint32_t reserved0      : 16;
                    uint32_t NISE           : 1;
                    uint32_t AISE           : 1;
                    uint32_t ERIE           : 1;
                    uint32_t FBEIE          : 1;
                    uint32_t ETIE           : 1;
                    uint32_t RWTIE          : 1;
                    uint32_t RPSIE          : 1;
                    uint32_t RBUIE          : 1;
                    uint32_t RIE            : 1;
                    uint32_t TUIE           : 1;
                    uint32_t ROIE           : 1;
                    uint32_t TJTIE          : 1;
                    uint32_t TBUIE          : 1;
                    uint32_t TPSIE          : 1;
                    uint32_t TIE            : 1;
                    uint32_t reserved31     : 1;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                NISE                   = (0x1U << 16),
                AISE                   = (0x1U << 15),
                ERIE                   = (0x1U << 14),
                FBEIE                  = (0x1U << 13),
                ETIE                   = (0x1U << 10),
                RWTIE                  = (0x1U << 9),
                RPSIE                  = (0x1U << 8),
                RBUIE                  = (0x1U << 7),
                RIE                    = (0x1U << 6),
                TUIE                   = (0x1U << 5),
                ROIE                   = (0x1U << 4),
                TJTIE                  = (0x1U << 3),
                TBUIE                  = (0x1U << 2),
                TPSIE                  = (0x1U << 1),
                TIE                    = (0x1U << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMAIER; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMAIER = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMAIER |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMAIER &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMAIER & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class DMAMFBOCR
        {
        private:
            union DMAMFBOCR_t
            {
                struct
                {
                    uint32_t reserved0      : 28;
                    uint32_t OFOC           : 1;
                    uint32_t MFA            : 11;
                    uint32_t OMFC           : 1;
                    uint32_t MFC            : 16;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                OFOC                   = (0x1U << 28),
                MFA                    = (0x7FFU << 17),
                OMFC                   = (0x1U << 16),
                MFC                    = (0xFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMAMFBOCR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMAMFBOCR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMAMFBOCR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMAMFBOCR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMAMFBOCR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_MFA() { return reinterpret_cast<__IO DMAMFBOCR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMAMFBOCR)->MFA; }
            static inline void set_MFA(uint32_t value) { reinterpret_cast<__IO DMAMFBOCR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMAMFBOCR)->MFA = value; }
            static inline uint32_t get_MFC() { return reinterpret_cast<__IO DMAMFBOCR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMAMFBOCR)->MFC; }
            static inline void set_MFC(uint32_t value) { reinterpret_cast<__IO DMAMFBOCR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMAMFBOCR)->MFC = value; }
        };
        class DMARSWTR
        {
        private:
            union DMARSWTR_t
            {
                struct
                {
                    uint32_t reserved0      : 32;
                };
                uint32_t RAW;
            };
        public:
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMARSWTR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMARSWTR = value; }
        };
        class DMACHTDR
        {
        private:
            union DMACHTDR_t
            {
                struct
                {
                    uint32_t HTDAP          : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                HTDAP                  = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMACHTDR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMACHTDR = value; }
            static inline uint32_t get_HTDAP() { return reinterpret_cast<__IO DMACHTDR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMACHTDR)->HTDAP; }
            static inline void set_HTDAP(uint32_t value) { reinterpret_cast<__IO DMACHTDR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMACHTDR)->HTDAP = value; }
        };
        class DMACHRDR
        {
        private:
            union DMACHRDR_t
            {
                struct
                {
                    uint32_t HRDAP          : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                HRDAP                  = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMACHRDR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMACHRDR = value; }
            static inline uint32_t get_HRDAP() { return reinterpret_cast<__IO DMACHRDR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMACHRDR)->HRDAP; }
            static inline void set_HRDAP(uint32_t value) { reinterpret_cast<__IO DMACHRDR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMACHRDR)->HRDAP = value; }
        };
        class DMACHTBAR
        {
        private:
            union DMACHTBAR_t
            {
                struct
                {
                    uint32_t HTBAP          : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                HTBAP                  = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMACHTBAR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMACHTBAR = value; }
            static inline uint32_t get_HTBAP() { return reinterpret_cast<__IO DMACHTBAR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMACHTBAR)->HTBAP; }
            static inline void set_HTBAP(uint32_t value) { reinterpret_cast<__IO DMACHTBAR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMACHTBAR)->HTBAP = value; }
        };
        class DMACHRBAR
        {
        private:
            union DMACHRBAR_t
            {
                struct
                {
                    uint32_t HRBAP          : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                HRBAP                  = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMACHRBAR; }
            static inline void set(uint32_t value) { reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMACHRBAR = value; }
            static inline uint32_t get_HRBAP() { return reinterpret_cast<__IO DMACHRBAR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMACHRBAR)->HRBAP; }
            static inline void set_HRBAP(uint32_t value) { reinterpret_cast<__IO DMACHRBAR_t*>(&reinterpret_cast<ETH_t*>(STM32::ETH_BASE)->DMACHRBAR)->HRBAP = value; }
        };
    };
    /* EXTI DEFINITION */
    class EXTI
    {
    private:
        struct EXTI_t
        {
            __IO uint32_t                 IMR;
            __IO uint32_t                 EMR;
            __IO uint32_t                 RTSR;
            __IO uint32_t                 FTSR;
            __IO uint32_t                 SWIER;
            __IO uint32_t                 PR;
        };
    public:
        class IMR
        {
        private:
            union IMR_t
            {
                struct
                {
                    uint32_t MR0            : 1;
                    uint32_t MR1            : 1;
                    uint32_t MR2            : 1;
                    uint32_t MR3            : 1;
                    uint32_t MR4            : 1;
                    uint32_t MR5            : 1;
                    uint32_t MR6            : 1;
                    uint32_t MR7            : 1;
                    uint32_t MR8            : 1;
                    uint32_t MR9            : 1;
                    uint32_t MR10           : 1;
                    uint32_t MR11           : 1;
                    uint32_t MR12           : 1;
                    uint32_t MR13           : 1;
                    uint32_t MR14           : 1;
                    uint32_t MR15           : 1;
                    uint32_t MR16           : 1;
                    uint32_t MR17           : 1;
                    uint32_t MR18           : 1;
                    uint32_t MR19           : 1;
                    uint32_t MR20           : 1;
                    uint32_t MR21           : 1;
                    uint32_t MR22           : 1;
                    uint32_t IM             : 23;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                MR0                    = (0x1U << 0),
                MR1                    = (0x1U << 1),
                MR2                    = (0x1U << 2),
                MR3                    = (0x1U << 3),
                MR4                    = (0x1U << 4),
                MR5                    = (0x1U << 5),
                MR6                    = (0x1U << 6),
                MR7                    = (0x1U << 7),
                MR8                    = (0x1U << 8),
                MR9                    = (0x1U << 9),
                MR10                   = (0x1U << 10),
                MR11                   = (0x1U << 11),
                MR12                   = (0x1U << 12),
                MR13                   = (0x1U << 13),
                MR14                   = (0x1U << 14),
                MR15                   = (0x1U << 15),
                MR16                   = (0x1U << 16),
                MR17                   = (0x1U << 17),
                MR18                   = (0x1U << 18),
                MR19                   = (0x1U << 19),
                MR20                   = (0x1U << 20),
                MR21                   = (0x1U << 21),
                MR22                   = (0x1U << 22),
                IM                     = (0x7FFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<EXTI_t*>(STM32::EXTI_BASE)->IMR; }
            static inline void set(uint32_t value) { reinterpret_cast<EXTI_t*>(STM32::EXTI_BASE)->IMR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<EXTI_t*>(STM32::EXTI_BASE)->IMR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<EXTI_t*>(STM32::EXTI_BASE)->IMR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<EXTI_t*>(STM32::EXTI_BASE)->IMR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_IM() { return reinterpret_cast<__IO IMR_t*>(&reinterpret_cast<EXTI_t*>(STM32::EXTI_BASE)->IMR)->IM; }
            static inline void set_IM(uint32_t value) { reinterpret_cast<__IO IMR_t*>(&reinterpret_cast<EXTI_t*>(STM32::EXTI_BASE)->IMR)->IM = value; }
        };
        class EMR
        {
        private:
            union EMR_t
            {
                struct
                {
                    uint32_t MR0            : 1;
                    uint32_t MR1            : 1;
                    uint32_t MR2            : 1;
                    uint32_t MR3            : 1;
                    uint32_t MR4            : 1;
                    uint32_t MR5            : 1;
                    uint32_t MR6            : 1;
                    uint32_t MR7            : 1;
                    uint32_t MR8            : 1;
                    uint32_t MR9            : 1;
                    uint32_t MR10           : 1;
                    uint32_t MR11           : 1;
                    uint32_t MR12           : 1;
                    uint32_t MR13           : 1;
                    uint32_t MR14           : 1;
                    uint32_t MR15           : 1;
                    uint32_t MR16           : 1;
                    uint32_t MR17           : 1;
                    uint32_t MR18           : 1;
                    uint32_t MR19           : 1;
                    uint32_t MR20           : 1;
                    uint32_t MR21           : 1;
                    uint32_t MR22           : 1;
                    uint32_t reserved23     : 9;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                MR0                    = (0x1U << 0),
                MR1                    = (0x1U << 1),
                MR2                    = (0x1U << 2),
                MR3                    = (0x1U << 3),
                MR4                    = (0x1U << 4),
                MR5                    = (0x1U << 5),
                MR6                    = (0x1U << 6),
                MR7                    = (0x1U << 7),
                MR8                    = (0x1U << 8),
                MR9                    = (0x1U << 9),
                MR10                   = (0x1U << 10),
                MR11                   = (0x1U << 11),
                MR12                   = (0x1U << 12),
                MR13                   = (0x1U << 13),
                MR14                   = (0x1U << 14),
                MR15                   = (0x1U << 15),
                MR16                   = (0x1U << 16),
                MR17                   = (0x1U << 17),
                MR18                   = (0x1U << 18),
                MR19                   = (0x1U << 19),
                MR20                   = (0x1U << 20),
                MR21                   = (0x1U << 21),
                MR22                   = (0x1U << 22),
            };
            static inline uint32_t get() { return reinterpret_cast<EXTI_t*>(STM32::EXTI_BASE)->EMR; }
            static inline void set(uint32_t value) { reinterpret_cast<EXTI_t*>(STM32::EXTI_BASE)->EMR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<EXTI_t*>(STM32::EXTI_BASE)->EMR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<EXTI_t*>(STM32::EXTI_BASE)->EMR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<EXTI_t*>(STM32::EXTI_BASE)->EMR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class RTSR
        {
        private:
            union RTSR_t
            {
                struct
                {
                    uint32_t TR0            : 1;
                    uint32_t TR1            : 1;
                    uint32_t TR2            : 1;
                    uint32_t TR3            : 1;
                    uint32_t TR4            : 1;
                    uint32_t TR5            : 1;
                    uint32_t TR6            : 1;
                    uint32_t TR7            : 1;
                    uint32_t TR8            : 1;
                    uint32_t TR9            : 1;
                    uint32_t TR10           : 1;
                    uint32_t TR11           : 1;
                    uint32_t TR12           : 1;
                    uint32_t TR13           : 1;
                    uint32_t TR14           : 1;
                    uint32_t TR15           : 1;
                    uint32_t TR16           : 1;
                    uint32_t TR17           : 1;
                    uint32_t TR18           : 1;
                    uint32_t TR19           : 1;
                    uint32_t TR20           : 1;
                    uint32_t TR21           : 1;
                    uint32_t TR22           : 1;
                    uint32_t reserved23     : 9;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                TR0                    = (0x1U << 0),
                TR1                    = (0x1U << 1),
                TR2                    = (0x1U << 2),
                TR3                    = (0x1U << 3),
                TR4                    = (0x1U << 4),
                TR5                    = (0x1U << 5),
                TR6                    = (0x1U << 6),
                TR7                    = (0x1U << 7),
                TR8                    = (0x1U << 8),
                TR9                    = (0x1U << 9),
                TR10                   = (0x1U << 10),
                TR11                   = (0x1U << 11),
                TR12                   = (0x1U << 12),
                TR13                   = (0x1U << 13),
                TR14                   = (0x1U << 14),
                TR15                   = (0x1U << 15),
                TR16                   = (0x1U << 16),
                TR17                   = (0x1U << 17),
                TR18                   = (0x1U << 18),
                TR19                   = (0x1U << 19),
                TR20                   = (0x1U << 20),
                TR21                   = (0x1U << 21),
                TR22                   = (0x1U << 22),
            };
            static inline uint32_t get() { return reinterpret_cast<EXTI_t*>(STM32::EXTI_BASE)->RTSR; }
            static inline void set(uint32_t value) { reinterpret_cast<EXTI_t*>(STM32::EXTI_BASE)->RTSR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<EXTI_t*>(STM32::EXTI_BASE)->RTSR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<EXTI_t*>(STM32::EXTI_BASE)->RTSR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<EXTI_t*>(STM32::EXTI_BASE)->RTSR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class FTSR
        {
        private:
            union FTSR_t
            {
                struct
                {
                    uint32_t TR0            : 1;
                    uint32_t TR1            : 1;
                    uint32_t TR2            : 1;
                    uint32_t TR3            : 1;
                    uint32_t TR4            : 1;
                    uint32_t TR5            : 1;
                    uint32_t TR6            : 1;
                    uint32_t TR7            : 1;
                    uint32_t TR8            : 1;
                    uint32_t TR9            : 1;
                    uint32_t TR10           : 1;
                    uint32_t TR11           : 1;
                    uint32_t TR12           : 1;
                    uint32_t TR13           : 1;
                    uint32_t TR14           : 1;
                    uint32_t TR15           : 1;
                    uint32_t TR16           : 1;
                    uint32_t TR17           : 1;
                    uint32_t TR18           : 1;
                    uint32_t TR19           : 1;
                    uint32_t TR20           : 1;
                    uint32_t TR21           : 1;
                    uint32_t TR22           : 1;
                    uint32_t reserved23     : 9;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                TR0                    = (0x1U << 0),
                TR1                    = (0x1U << 1),
                TR2                    = (0x1U << 2),
                TR3                    = (0x1U << 3),
                TR4                    = (0x1U << 4),
                TR5                    = (0x1U << 5),
                TR6                    = (0x1U << 6),
                TR7                    = (0x1U << 7),
                TR8                    = (0x1U << 8),
                TR9                    = (0x1U << 9),
                TR10                   = (0x1U << 10),
                TR11                   = (0x1U << 11),
                TR12                   = (0x1U << 12),
                TR13                   = (0x1U << 13),
                TR14                   = (0x1U << 14),
                TR15                   = (0x1U << 15),
                TR16                   = (0x1U << 16),
                TR17                   = (0x1U << 17),
                TR18                   = (0x1U << 18),
                TR19                   = (0x1U << 19),
                TR20                   = (0x1U << 20),
                TR21                   = (0x1U << 21),
                TR22                   = (0x1U << 22),
            };
            static inline uint32_t get() { return reinterpret_cast<EXTI_t*>(STM32::EXTI_BASE)->FTSR; }
            static inline void set(uint32_t value) { reinterpret_cast<EXTI_t*>(STM32::EXTI_BASE)->FTSR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<EXTI_t*>(STM32::EXTI_BASE)->FTSR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<EXTI_t*>(STM32::EXTI_BASE)->FTSR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<EXTI_t*>(STM32::EXTI_BASE)->FTSR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class SWIER
        {
        private:
            union SWIER_t
            {
                struct
                {
                    uint32_t SWIER0         : 1;
                    uint32_t SWIER1         : 1;
                    uint32_t SWIER2         : 1;
                    uint32_t SWIER3         : 1;
                    uint32_t SWIER4         : 1;
                    uint32_t SWIER5         : 1;
                    uint32_t SWIER6         : 1;
                    uint32_t SWIER7         : 1;
                    uint32_t SWIER8         : 1;
                    uint32_t SWIER9         : 1;
                    uint32_t SWIER10        : 1;
                    uint32_t SWIER11        : 1;
                    uint32_t SWIER12        : 1;
                    uint32_t SWIER13        : 1;
                    uint32_t SWIER14        : 1;
                    uint32_t SWIER15        : 1;
                    uint32_t SWIER16        : 1;
                    uint32_t SWIER17        : 1;
                    uint32_t SWIER18        : 1;
                    uint32_t SWIER19        : 1;
                    uint32_t SWIER20        : 1;
                    uint32_t SWIER21        : 1;
                    uint32_t SWIER22        : 1;
                    uint32_t reserved23     : 9;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                SWIER0                 = (0x1U << 0),
                SWIER1                 = (0x1U << 1),
                SWIER2                 = (0x1U << 2),
                SWIER3                 = (0x1U << 3),
                SWIER4                 = (0x1U << 4),
                SWIER5                 = (0x1U << 5),
                SWIER6                 = (0x1U << 6),
                SWIER7                 = (0x1U << 7),
                SWIER8                 = (0x1U << 8),
                SWIER9                 = (0x1U << 9),
                SWIER10                = (0x1U << 10),
                SWIER11                = (0x1U << 11),
                SWIER12                = (0x1U << 12),
                SWIER13                = (0x1U << 13),
                SWIER14                = (0x1U << 14),
                SWIER15                = (0x1U << 15),
                SWIER16                = (0x1U << 16),
                SWIER17                = (0x1U << 17),
                SWIER18                = (0x1U << 18),
                SWIER19                = (0x1U << 19),
                SWIER20                = (0x1U << 20),
                SWIER21                = (0x1U << 21),
                SWIER22                = (0x1U << 22),
            };
            static inline uint32_t get() { return reinterpret_cast<EXTI_t*>(STM32::EXTI_BASE)->SWIER; }
            static inline void set(uint32_t value) { reinterpret_cast<EXTI_t*>(STM32::EXTI_BASE)->SWIER = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<EXTI_t*>(STM32::EXTI_BASE)->SWIER |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<EXTI_t*>(STM32::EXTI_BASE)->SWIER &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<EXTI_t*>(STM32::EXTI_BASE)->SWIER & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class PR
        {
        private:
            union PR_t
            {
                struct
                {
                    uint32_t PR0            : 1;
                    uint32_t PR1            : 1;
                    uint32_t PR2            : 1;
                    uint32_t PR3            : 1;
                    uint32_t PR4            : 1;
                    uint32_t PR5            : 1;
                    uint32_t PR6            : 1;
                    uint32_t PR7            : 1;
                    uint32_t PR8            : 1;
                    uint32_t PR9            : 1;
                    uint32_t PR10           : 1;
                    uint32_t PR11           : 1;
                    uint32_t PR12           : 1;
                    uint32_t PR13           : 1;
                    uint32_t PR14           : 1;
                    uint32_t PR15           : 1;
                    uint32_t PR16           : 1;
                    uint32_t PR17           : 1;
                    uint32_t PR18           : 1;
                    uint32_t PR19           : 1;
                    uint32_t PR20           : 1;
                    uint32_t PR21           : 1;
                    uint32_t PR22           : 1;
                    uint32_t reserved23     : 9;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                PR0                    = (0x1U << 0),
                PR1                    = (0x1U << 1),
                PR2                    = (0x1U << 2),
                PR3                    = (0x1U << 3),
                PR4                    = (0x1U << 4),
                PR5                    = (0x1U << 5),
                PR6                    = (0x1U << 6),
                PR7                    = (0x1U << 7),
                PR8                    = (0x1U << 8),
                PR9                    = (0x1U << 9),
                PR10                   = (0x1U << 10),
                PR11                   = (0x1U << 11),
                PR12                   = (0x1U << 12),
                PR13                   = (0x1U << 13),
                PR14                   = (0x1U << 14),
                PR15                   = (0x1U << 15),
                PR16                   = (0x1U << 16),
                PR17                   = (0x1U << 17),
                PR18                   = (0x1U << 18),
                PR19                   = (0x1U << 19),
                PR20                   = (0x1U << 20),
                PR21                   = (0x1U << 21),
                PR22                   = (0x1U << 22),
            };
            static inline uint32_t get() { return reinterpret_cast<EXTI_t*>(STM32::EXTI_BASE)->PR; }
            static inline void set(uint32_t value) { reinterpret_cast<EXTI_t*>(STM32::EXTI_BASE)->PR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<EXTI_t*>(STM32::EXTI_BASE)->PR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<EXTI_t*>(STM32::EXTI_BASE)->PR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<EXTI_t*>(STM32::EXTI_BASE)->PR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
    };
    /* FLASH DEFINITION */
    class FLASH
    {
    private:
        struct FLASH_t
        {
            __IO uint32_t                 ACR;
            __IO uint32_t                 KEYR;
            __IO uint32_t                 OPTKEYR;
            __IO uint32_t                 SR;
            __IO uint32_t                 CR;
            __IO uint32_t                 OPTCR;
            __IO uint32_t                 OPTCR1;
        };
    public:
        class ACR
        {
        private:
            union ACR_t
            {
                struct
                {
                    uint32_t LATENCY        : 4;
                    uint32_t reserved4      : 4;
                    uint32_t PRFTEN         : 1;
                    uint32_t ICEN           : 1;
                    uint32_t DCEN           : 1;
                    uint32_t ICRST          : 1;
                    uint32_t DCRST          : 1;
                    uint32_t BYTE0_ADDRESS  : 5;
                    uint32_t BYTE2_ADDRESS  : 4;
                    uint32_t reserved22     : 10;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                LATENCY                = (0xFU << 0),
                PRFTEN                 = (0x1U << 8),
                ICEN                   = (0x1U << 9),
                DCEN                   = (0x1U << 10),
                ICRST                  = (0x1U << 11),
                DCRST                  = (0x1U << 12),
                BYTE0_ADDRESS          = (0x10008FU << 10),
                BYTE2_ADDRESS          = (0x40023C03U << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->ACR; }
            static inline void set(uint32_t value) { reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->ACR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->ACR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->ACR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->ACR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_LATENCY() { return reinterpret_cast<__IO ACR_t*>(&reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->ACR)->LATENCY; }
            static inline void set_LATENCY(uint32_t value) { reinterpret_cast<__IO ACR_t*>(&reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->ACR)->LATENCY = value; }
            static inline uint32_t get_BYTE0_ADDRESS() { return reinterpret_cast<__IO ACR_t*>(&reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->ACR)->BYTE0_ADDRESS; }
            static inline void set_BYTE0_ADDRESS(uint32_t value) { reinterpret_cast<__IO ACR_t*>(&reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->ACR)->BYTE0_ADDRESS = value; }
            static inline uint32_t get_BYTE2_ADDRESS() { return reinterpret_cast<__IO ACR_t*>(&reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->ACR)->BYTE2_ADDRESS; }
            static inline void set_BYTE2_ADDRESS(uint32_t value) { reinterpret_cast<__IO ACR_t*>(&reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->ACR)->BYTE2_ADDRESS = value; }
        };
        class KEYR
        {
        private:
            union KEYR_t
            {
                struct
                {
                    uint32_t reserved0      : 32;
                };
                uint32_t RAW;
            };
        public:
            static inline uint32_t get() { return reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->KEYR; }
            static inline void set(uint32_t value) { reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->KEYR = value; }
        };
        class OPTKEYR
        {
        private:
            union OPTKEYR_t
            {
                struct
                {
                    uint32_t reserved0      : 32;
                };
                uint32_t RAW;
            };
        public:
            static inline uint32_t get() { return reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->OPTKEYR; }
            static inline void set(uint32_t value) { reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->OPTKEYR = value; }
        };
        class SR
        {
        private:
            union SR_t
            {
                struct
                {
                    uint32_t EOP            : 1;
                    uint32_t SOP            : 1;
                    uint32_t reserved2      : 2;
                    uint32_t WRPERR         : 1;
                    uint32_t PGAERR         : 1;
                    uint32_t PGPERR         : 1;
                    uint32_t PGSERR         : 1;
                    uint32_t reserved8      : 8;
                    uint32_t BSY            : 1;
                    uint32_t reserved17     : 15;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                EOP                    = (0x1U << 0),
                SOP                    = (0x1U << 1),
                WRPERR                 = (0x1U << 4),
                PGAERR                 = (0x1U << 5),
                PGPERR                 = (0x1U << 6),
                PGSERR                 = (0x1U << 7),
                BSY                    = (0x1U << 16),
            };
            static inline uint32_t get() { return reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->SR; }
            static inline void set(uint32_t value) { reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->SR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->SR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->SR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->SR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class CR
        {
        private:
            union CR_t
            {
                struct
                {
                    uint32_t PG             : 1;
                    uint32_t SER            : 1;
                    uint32_t MER            : 1;
                    uint32_t SNB            : 5;
                    uint32_t PSIZE          : 2;
                    uint32_t reserved10     : 6;
                    uint32_t STRT           : 1;
                    uint32_t reserved17     : 7;
                    uint32_t EOPIE          : 1;
                    uint32_t reserved25     : 6;
                    uint32_t LOCK           : 1;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                PG                     = (0x1U << 0),
                SER                    = (0x1U << 1),
                MER                    = (0x1U << 2),
                SNB                    = (0x1FU << 3),
                PSIZE                  = (0x3U << 8),
                STRT                   = (0x1U << 16),
                EOPIE                  = (0x1U << 24),
                LOCK                   = (0x1U << 31),
            };
            static inline uint32_t get() { return reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->CR; }
            static inline void set(uint32_t value) { reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->CR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->CR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->CR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->CR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_SNB() { return reinterpret_cast<__IO CR_t*>(&reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->CR)->SNB; }
            static inline void set_SNB(uint32_t value) { reinterpret_cast<__IO CR_t*>(&reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->CR)->SNB = value; }
            static inline uint32_t get_PSIZE() { return reinterpret_cast<__IO CR_t*>(&reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->CR)->PSIZE; }
            static inline void set_PSIZE(uint32_t value) { reinterpret_cast<__IO CR_t*>(&reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->CR)->PSIZE = value; }
        };
        class OPTCR
        {
        private:
            union OPTCR_t
            {
                struct
                {
                    uint32_t OPTLOCK        : 1;
                    uint32_t OPTSTRT        : 1;
                    uint32_t BOR_LEV        : 2;
                    uint32_t reserved4      : 1;
                    uint32_t WDG_SW         : 1;
                    uint32_t nRST_STOP      : 1;
                    uint32_t nRST_STDBY     : 1;
                    uint32_t RDP            : 8;
                    uint32_t nWRP           : 12;
                    uint32_t reserved28     : 4;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                OPTLOCK                = (0x1U << 0),
                OPTSTRT                = (0x1U << 1),
                BOR_LEV                = (0x3U << 2),
                WDG_SW                 = (0x1U << 5),
                nRST_STOP              = (0x1U << 6),
                nRST_STDBY             = (0x1U << 7),
                RDP                    = (0xFFU << 8),
                nWRP                   = (0xFFFU << 16),
            };
            static inline uint32_t get() { return reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->OPTCR; }
            static inline void set(uint32_t value) { reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->OPTCR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->OPTCR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->OPTCR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->OPTCR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_BOR_LEV() { return reinterpret_cast<__IO OPTCR_t*>(&reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->OPTCR)->BOR_LEV; }
            static inline void set_BOR_LEV(uint32_t value) { reinterpret_cast<__IO OPTCR_t*>(&reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->OPTCR)->BOR_LEV = value; }
            static inline uint32_t get_RDP() { return reinterpret_cast<__IO OPTCR_t*>(&reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->OPTCR)->RDP; }
            static inline void set_RDP(uint32_t value) { reinterpret_cast<__IO OPTCR_t*>(&reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->OPTCR)->RDP = value; }
            static inline uint32_t get_nWRP() { return reinterpret_cast<__IO OPTCR_t*>(&reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->OPTCR)->nWRP; }
            static inline void set_nWRP(uint32_t value) { reinterpret_cast<__IO OPTCR_t*>(&reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->OPTCR)->nWRP = value; }
        };
        class OPTCR1
        {
        private:
            union OPTCR1_t
            {
                struct
                {
                    uint32_t reserved0      : 16;
                    uint32_t nWRP           : 12;
                    uint32_t reserved28     : 4;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                nWRP                   = (0xFFFU << 16),
            };
            static inline uint32_t get() { return reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->OPTCR1; }
            static inline void set(uint32_t value) { reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->OPTCR1 = value; }
            static inline uint32_t get_nWRP() { return reinterpret_cast<__IO OPTCR1_t*>(&reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->OPTCR1)->nWRP; }
            static inline void set_nWRP(uint32_t value) { reinterpret_cast<__IO OPTCR1_t*>(&reinterpret_cast<FLASH_t*>(STM32::FLASH_BASE)->OPTCR1)->nWRP = value; }
        };
    };
    /* FSMC_Bank1 DEFINITION */
    template <uint32_t reg_base>
    class FSMC_Bank1
    {
    };
    /* FSMC_Bank1E DEFINITION */
    template <uint32_t reg_base>
    class FSMC_Bank1E
    {
    };
    /* FSMC_Bank4 DEFINITION */
    template <uint32_t reg_base>
    class FSMC_Bank4
    {
    };
    /* GPIO DEFINITION */
    template <uint32_t reg_base>
    class GPIO
    {
    };
    /* SYSCFG DEFINITION */
    class SYSCFG
    {
    private:
        struct SYSCFG_t
        {
            __IO uint32_t                 MEMRMP;
            __IO uint32_t                 PMC;
            __IO uint32_t                 EXTICR[4];
            uint32_t                      RESERVED[2];
            __IO uint32_t                 CMPCR;
        };
    public:
        class MEMRMP
        {
        private:
            union MEMRMP_t
            {
                struct
                {
                    uint32_t MEM_MODE       : 2;
                    uint32_t reserved2      : 30;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                MEM_MODE               = (0x3U << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->MEMRMP; }
            static inline void set(uint32_t value) { reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->MEMRMP = value; }
            static inline uint32_t get_MEM_MODE() { return reinterpret_cast<__IO MEMRMP_t*>(&reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->MEMRMP)->MEM_MODE; }
            static inline void set_MEM_MODE(uint32_t value) { reinterpret_cast<__IO MEMRMP_t*>(&reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->MEMRMP)->MEM_MODE = value; }
        };
        class PMC
        {
        private:
            union PMC_t
            {
                struct
                {
                    uint32_t reserved0      : 23;
                    uint32_t MII_RMII_SEL   : 1;
                    uint32_t reserved24     : 8;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                MII_RMII_SEL           = (0x1U << 23),
            };
            static inline uint32_t get() { return reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->PMC; }
            static inline void set(uint32_t value) { reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->PMC = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->PMC |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->PMC &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->PMC & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class EXTICR
        {
        private:
            union EXTICR_t
            {
                struct
                {
                    uint32_t EXTI0          : 4;
                    uint32_t EXTI1          : 4;
                    uint32_t EXTI2          : 4;
                    uint32_t EXTI3          : 4;
                    uint32_t EXTI4          : 4;
                    uint32_t EXTI5          : 4;
                    uint32_t EXTI6          : 4;
                    uint32_t EXTI7          : 4;
                    uint32_t EXTI8          : 4;
                    uint32_t EXTI9          : 4;
                    uint32_t EXTI10         : 4;
                    uint32_t EXTI11         : 4;
                    uint32_t EXTI12         : 4;
                    uint32_t EXTI13         : 4;
                    uint32_t EXTI14         : 4;
                    uint32_t EXTI15         : 4;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                EXTI0                  = (0xFU << 0),
                EXTI1                  = (0xFU << 4),
                EXTI2                  = (0xFU << 8),
                EXTI3                  = (0xFU << 12),
                EXTI4                  = (0xFU << 0),
                EXTI5                  = (0xFU << 4),
                EXTI6                  = (0xFU << 8),
                EXTI7                  = (0xFU << 12),
                EXTI8                  = (0xFU << 0),
                EXTI9                  = (0xFU << 4),
                EXTI10                 = (0xFU << 8),
                EXTI11                 = (0xFU << 12),
                EXTI12                 = (0xFU << 0),
                EXTI13                 = (0xFU << 4),
                EXTI14                 = (0xFU << 8),
                EXTI15                 = (0xFU << 12),
            };
            static inline uint32_t get(uint32_t idx) { return reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->EXTICR[idx]; }
            static inline void set(uint32_t idx, uint32_t value) { reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->EXTICR[idx] = value; }
            static inline uint32_t get_EXTI0(uint32_t idx) { return reinterpret_cast<__IO EXTICR_t*>(&reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->EXTICR[idx])->EXTI0; }
            static inline void set_EXTI0(uint32_t idx, uint32_t value) { reinterpret_cast<__IO EXTICR_t*>(&reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->EXTICR[idx])->EXTI0 = value; }
            static inline uint32_t get_EXTI1(uint32_t idx) { return reinterpret_cast<__IO EXTICR_t*>(&reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->EXTICR[idx])->EXTI1; }
            static inline void set_EXTI1(uint32_t idx, uint32_t value) { reinterpret_cast<__IO EXTICR_t*>(&reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->EXTICR[idx])->EXTI1 = value; }
            static inline uint32_t get_EXTI2(uint32_t idx) { return reinterpret_cast<__IO EXTICR_t*>(&reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->EXTICR[idx])->EXTI2; }
            static inline void set_EXTI2(uint32_t idx, uint32_t value) { reinterpret_cast<__IO EXTICR_t*>(&reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->EXTICR[idx])->EXTI2 = value; }
            static inline uint32_t get_EXTI3(uint32_t idx) { return reinterpret_cast<__IO EXTICR_t*>(&reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->EXTICR[idx])->EXTI3; }
            static inline void set_EXTI3(uint32_t idx, uint32_t value) { reinterpret_cast<__IO EXTICR_t*>(&reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->EXTICR[idx])->EXTI3 = value; }
            static inline uint32_t get_EXTI4(uint32_t idx) { return reinterpret_cast<__IO EXTICR_t*>(&reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->EXTICR[idx])->EXTI4; }
            static inline void set_EXTI4(uint32_t idx, uint32_t value) { reinterpret_cast<__IO EXTICR_t*>(&reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->EXTICR[idx])->EXTI4 = value; }
            static inline uint32_t get_EXTI5(uint32_t idx) { return reinterpret_cast<__IO EXTICR_t*>(&reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->EXTICR[idx])->EXTI5; }
            static inline void set_EXTI5(uint32_t idx, uint32_t value) { reinterpret_cast<__IO EXTICR_t*>(&reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->EXTICR[idx])->EXTI5 = value; }
            static inline uint32_t get_EXTI6(uint32_t idx) { return reinterpret_cast<__IO EXTICR_t*>(&reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->EXTICR[idx])->EXTI6; }
            static inline void set_EXTI6(uint32_t idx, uint32_t value) { reinterpret_cast<__IO EXTICR_t*>(&reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->EXTICR[idx])->EXTI6 = value; }
            static inline uint32_t get_EXTI7(uint32_t idx) { return reinterpret_cast<__IO EXTICR_t*>(&reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->EXTICR[idx])->EXTI7; }
            static inline void set_EXTI7(uint32_t idx, uint32_t value) { reinterpret_cast<__IO EXTICR_t*>(&reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->EXTICR[idx])->EXTI7 = value; }
            static inline uint32_t get_EXTI8(uint32_t idx) { return reinterpret_cast<__IO EXTICR_t*>(&reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->EXTICR[idx])->EXTI8; }
            static inline void set_EXTI8(uint32_t idx, uint32_t value) { reinterpret_cast<__IO EXTICR_t*>(&reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->EXTICR[idx])->EXTI8 = value; }
            static inline uint32_t get_EXTI9(uint32_t idx) { return reinterpret_cast<__IO EXTICR_t*>(&reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->EXTICR[idx])->EXTI9; }
            static inline void set_EXTI9(uint32_t idx, uint32_t value) { reinterpret_cast<__IO EXTICR_t*>(&reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->EXTICR[idx])->EXTI9 = value; }
            static inline uint32_t get_EXTI10(uint32_t idx) { return reinterpret_cast<__IO EXTICR_t*>(&reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->EXTICR[idx])->EXTI10; }
            static inline void set_EXTI10(uint32_t idx, uint32_t value) { reinterpret_cast<__IO EXTICR_t*>(&reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->EXTICR[idx])->EXTI10 = value; }
            static inline uint32_t get_EXTI11(uint32_t idx) { return reinterpret_cast<__IO EXTICR_t*>(&reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->EXTICR[idx])->EXTI11; }
            static inline void set_EXTI11(uint32_t idx, uint32_t value) { reinterpret_cast<__IO EXTICR_t*>(&reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->EXTICR[idx])->EXTI11 = value; }
            static inline uint32_t get_EXTI12(uint32_t idx) { return reinterpret_cast<__IO EXTICR_t*>(&reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->EXTICR[idx])->EXTI12; }
            static inline void set_EXTI12(uint32_t idx, uint32_t value) { reinterpret_cast<__IO EXTICR_t*>(&reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->EXTICR[idx])->EXTI12 = value; }
            static inline uint32_t get_EXTI13(uint32_t idx) { return reinterpret_cast<__IO EXTICR_t*>(&reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->EXTICR[idx])->EXTI13; }
            static inline void set_EXTI13(uint32_t idx, uint32_t value) { reinterpret_cast<__IO EXTICR_t*>(&reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->EXTICR[idx])->EXTI13 = value; }
            static inline uint32_t get_EXTI14(uint32_t idx) { return reinterpret_cast<__IO EXTICR_t*>(&reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->EXTICR[idx])->EXTI14; }
            static inline void set_EXTI14(uint32_t idx, uint32_t value) { reinterpret_cast<__IO EXTICR_t*>(&reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->EXTICR[idx])->EXTI14 = value; }
            static inline uint32_t get_EXTI15(uint32_t idx) { return reinterpret_cast<__IO EXTICR_t*>(&reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->EXTICR[idx])->EXTI15; }
            static inline void set_EXTI15(uint32_t idx, uint32_t value) { reinterpret_cast<__IO EXTICR_t*>(&reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->EXTICR[idx])->EXTI15 = value; }
        };
        class CMPCR
        {
        private:
            union CMPCR_t
            {
                struct
                {
                    uint32_t CMP_PD         : 1;
                    uint32_t reserved1      : 7;
                    uint32_t READY          : 1;
                    uint32_t reserved9      : 23;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                CMP_PD                 = (0x1U << 0),
                READY                  = (0x1U << 8),
            };
            static inline uint32_t get() { return reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->CMPCR; }
            static inline void set(uint32_t value) { reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->CMPCR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->CMPCR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->CMPCR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<SYSCFG_t*>(STM32::SYSCFG_BASE)->CMPCR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
    };
    /* I2C DEFINITION */
    template <uint32_t reg_base>
    class I2C
    {
    };
    /* IWDG DEFINITION */
    class IWDG
    {
    private:
        struct IWDG_t
        {
            __IO uint32_t                 KR;
            __IO uint32_t                 PR;
            __IO uint32_t                 RLR;
            __IO uint32_t                 SR;
        };
    public:
        class KR
        {
        private:
            union KR_t
            {
                struct
                {
                    uint32_t KEY            : 16;
                    uint32_t reserved16     : 16;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                KEY                    = (0xFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<IWDG_t*>(STM32::IWDG_BASE)->KR; }
            static inline void set(uint32_t value) { reinterpret_cast<IWDG_t*>(STM32::IWDG_BASE)->KR = value; }
            static inline uint32_t get_KEY() { return reinterpret_cast<__IO KR_t*>(&reinterpret_cast<IWDG_t*>(STM32::IWDG_BASE)->KR)->KEY; }
            static inline void set_KEY(uint32_t value) { reinterpret_cast<__IO KR_t*>(&reinterpret_cast<IWDG_t*>(STM32::IWDG_BASE)->KR)->KEY = value; }
        };
        class PR
        {
        private:
            union PR_t
            {
                struct
                {
                    uint32_t PR             : 3;
                    uint32_t reserved3      : 29;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                PR                     = (0x7U << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<IWDG_t*>(STM32::IWDG_BASE)->PR; }
            static inline void set(uint32_t value) { reinterpret_cast<IWDG_t*>(STM32::IWDG_BASE)->PR = value; }
            static inline uint32_t get_PR() { return reinterpret_cast<__IO PR_t*>(&reinterpret_cast<IWDG_t*>(STM32::IWDG_BASE)->PR)->PR; }
            static inline void set_PR(uint32_t value) { reinterpret_cast<__IO PR_t*>(&reinterpret_cast<IWDG_t*>(STM32::IWDG_BASE)->PR)->PR = value; }
        };
        class RLR
        {
        private:
            union RLR_t
            {
                struct
                {
                    uint32_t RL             : 12;
                    uint32_t reserved12     : 20;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                RL                     = (0xFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<IWDG_t*>(STM32::IWDG_BASE)->RLR; }
            static inline void set(uint32_t value) { reinterpret_cast<IWDG_t*>(STM32::IWDG_BASE)->RLR = value; }
            static inline uint32_t get_RL() { return reinterpret_cast<__IO RLR_t*>(&reinterpret_cast<IWDG_t*>(STM32::IWDG_BASE)->RLR)->RL; }
            static inline void set_RL(uint32_t value) { reinterpret_cast<__IO RLR_t*>(&reinterpret_cast<IWDG_t*>(STM32::IWDG_BASE)->RLR)->RL = value; }
        };
        class SR
        {
        private:
            union SR_t
            {
                struct
                {
                    uint32_t PVU            : 1;
                    uint32_t RVU            : 1;
                    uint32_t reserved2      : 30;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                PVU                    = (0x1U << 0),
                RVU                    = (0x1U << 1),
            };
            static inline uint32_t get() { return reinterpret_cast<IWDG_t*>(STM32::IWDG_BASE)->SR; }
            static inline void set(uint32_t value) { reinterpret_cast<IWDG_t*>(STM32::IWDG_BASE)->SR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<IWDG_t*>(STM32::IWDG_BASE)->SR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<IWDG_t*>(STM32::IWDG_BASE)->SR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<IWDG_t*>(STM32::IWDG_BASE)->SR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
    };
    /* PWR DEFINITION */
    class PWR
    {
    private:
        struct PWR_t
        {
            __IO uint32_t                 CR;
            __IO uint32_t                 CSR;
        };
    public:
        class CR
        {
        private:
            union CR_t
            {
                struct
                {
                    uint32_t LPDS           : 1;
                    uint32_t PDDS           : 1;
                    uint32_t CWUF           : 1;
                    uint32_t CSBF           : 1;
                    uint32_t PVDE           : 1;
                    uint32_t PLS            : 3;
                    uint32_t DBP            : 1;
                    uint32_t FPDS           : 1;
                    uint32_t reserved10     : 4;
                    uint32_t VOS            : 1;
                    uint32_t reserved15     : 17;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                LPDS                   = (0x1U << 0),
                PDDS                   = (0x1U << 1),
                CWUF                   = (0x1U << 2),
                CSBF                   = (0x1U << 3),
                PVDE                   = (0x1U << 4),
                PLS                    = (0x7U << 5),
                DBP                    = (0x1U << 8),
                FPDS                   = (0x1U << 9),
                VOS                    = (0x1U << 14),
            };
            static inline uint32_t get() { return reinterpret_cast<PWR_t*>(STM32::PWR_BASE)->CR; }
            static inline void set(uint32_t value) { reinterpret_cast<PWR_t*>(STM32::PWR_BASE)->CR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<PWR_t*>(STM32::PWR_BASE)->CR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<PWR_t*>(STM32::PWR_BASE)->CR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<PWR_t*>(STM32::PWR_BASE)->CR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_PLS() { return reinterpret_cast<__IO CR_t*>(&reinterpret_cast<PWR_t*>(STM32::PWR_BASE)->CR)->PLS; }
            static inline void set_PLS(uint32_t value) { reinterpret_cast<__IO CR_t*>(&reinterpret_cast<PWR_t*>(STM32::PWR_BASE)->CR)->PLS = value; }
        };
        class CSR
        {
        private:
            union CSR_t
            {
                struct
                {
                    uint32_t WUF            : 1;
                    uint32_t SBF            : 1;
                    uint32_t PVDO           : 1;
                    uint32_t BRR            : 1;
                    uint32_t reserved4      : 4;
                    uint32_t EWUP           : 1;
                    uint32_t BRE            : 1;
                    uint32_t reserved10     : 4;
                    uint32_t VOSRDY         : 1;
                    uint32_t reserved15     : 17;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                WUF                    = (0x1U << 0),
                SBF                    = (0x1U << 1),
                PVDO                   = (0x1U << 2),
                BRR                    = (0x1U << 3),
                EWUP                   = (0x1U << 8),
                BRE                    = (0x1U << 9),
                VOSRDY                 = (0x1U << 14),
            };
            static inline uint32_t get() { return reinterpret_cast<PWR_t*>(STM32::PWR_BASE)->CSR; }
            static inline void set(uint32_t value) { reinterpret_cast<PWR_t*>(STM32::PWR_BASE)->CSR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<PWR_t*>(STM32::PWR_BASE)->CSR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<PWR_t*>(STM32::PWR_BASE)->CSR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<PWR_t*>(STM32::PWR_BASE)->CSR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
    };
    /* RCC DEFINITION */
    class RCC
    {
    private:
        struct RCC_t
        {
            __IO uint32_t                 CR;
            __IO uint32_t                 PLLCFGR;
            __IO uint32_t                 CFGR;
            __IO uint32_t                 CIR;
            __IO uint32_t                 AHB1RSTR;
            __IO uint32_t                 AHB2RSTR;
            __IO uint32_t                 AHB3RSTR;
            uint32_t                      RESERVED0;
            __IO uint32_t                 APB1RSTR;
            __IO uint32_t                 APB2RSTR;
            uint32_t                      RESERVED1[2];
            __IO uint32_t                 AHB1ENR;
            __IO uint32_t                 AHB2ENR;
            __IO uint32_t                 AHB3ENR;
            uint32_t                      RESERVED2;
            __IO uint32_t                 APB1ENR;
            __IO uint32_t                 APB2ENR;
            uint32_t                      RESERVED3[2];
            __IO uint32_t                 AHB1LPENR;
            __IO uint32_t                 AHB2LPENR;
            __IO uint32_t                 AHB3LPENR;
            uint32_t                      RESERVED4;
            __IO uint32_t                 APB1LPENR;
            __IO uint32_t                 APB2LPENR;
            uint32_t                      RESERVED5[2];
            __IO uint32_t                 BDCR;
            __IO uint32_t                 CSR;
            uint32_t                      RESERVED6[2];
            __IO uint32_t                 SSCGR;
            __IO uint32_t                 PLLI2SCFGR;
        };
    public:
        class CR
        {
        private:
            union CR_t
            {
                struct
                {
                    uint32_t HSION          : 1;
                    uint32_t HSIRDY         : 1;
                    uint32_t reserved2      : 1;
                    uint32_t HSITRIM        : 5;
                    uint32_t HSICAL         : 8;
                    uint32_t HSEON          : 1;
                    uint32_t HSERDY         : 1;
                    uint32_t HSEBYP         : 1;
                    uint32_t CSSON          : 1;
                    uint32_t reserved20     : 4;
                    uint32_t PLLON          : 1;
                    uint32_t PLLRDY         : 1;
                    uint32_t PLLI2SON       : 1;
                    uint32_t PLLI2SRDY      : 1;
                    uint32_t reserved28     : 4;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                HSION                  = (0x1U << 0),
                HSIRDY                 = (0x1U << 1),
                HSITRIM                = (0x1FU << 3),
                HSICAL                 = (0xFFU << 8),
                HSEON                  = (0x1U << 16),
                HSERDY                 = (0x1U << 17),
                HSEBYP                 = (0x1U << 18),
                CSSON                  = (0x1U << 19),
                PLLON                  = (0x1U << 24),
                PLLRDY                 = (0x1U << 25),
                PLLI2SON               = (0x1U << 26),
                PLLI2SRDY              = (0x1U << 27),
            };
            static inline uint32_t get() { return reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CR; }
            static inline void set(uint32_t value) { reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_HSITRIM() { return reinterpret_cast<__IO CR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CR)->HSITRIM; }
            static inline void set_HSITRIM(uint32_t value) { reinterpret_cast<__IO CR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CR)->HSITRIM = value; }
            static inline uint32_t get_HSICAL() { return reinterpret_cast<__IO CR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CR)->HSICAL; }
            static inline void set_HSICAL(uint32_t value) { reinterpret_cast<__IO CR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CR)->HSICAL = value; }
        };
        class PLLCFGR
        {
        private:
            union PLLCFGR_t
            {
                struct
                {
                    uint32_t PLLM           : 6;
                    uint32_t PLLN           : 9;
                    uint32_t reserved15     : 1;
                    uint32_t PLLP           : 2;
                    uint32_t reserved18     : 4;
                    uint32_t PLLSRC         : 1;
                    uint32_t PLLSRC_HSE     : 1;
                    uint32_t PLLQ           : 4;
                    uint32_t reserved28     : 4;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                PLLM                   = (0x3FU << 0),
                PLLN                   = (0x1FFU << 6),
                PLLP                   = (0x3U << 16),
                PLLSRC                 = (0x1U << 22),
                PLLSRC_HSE             = (0x1U << 22),
                PLLQ                   = (0xFU << 24),
            };
            static inline uint32_t get() { return reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->PLLCFGR; }
            static inline void set(uint32_t value) { reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->PLLCFGR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->PLLCFGR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->PLLCFGR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->PLLCFGR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_PLLM() { return reinterpret_cast<__IO PLLCFGR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->PLLCFGR)->PLLM; }
            static inline void set_PLLM(uint32_t value) { reinterpret_cast<__IO PLLCFGR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->PLLCFGR)->PLLM = value; }
            static inline uint32_t get_PLLN() { return reinterpret_cast<__IO PLLCFGR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->PLLCFGR)->PLLN; }
            static inline void set_PLLN(uint32_t value) { reinterpret_cast<__IO PLLCFGR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->PLLCFGR)->PLLN = value; }
            static inline uint32_t get_PLLP() { return reinterpret_cast<__IO PLLCFGR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->PLLCFGR)->PLLP; }
            static inline void set_PLLP(uint32_t value) { reinterpret_cast<__IO PLLCFGR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->PLLCFGR)->PLLP = value; }
            static inline uint32_t get_PLLQ() { return reinterpret_cast<__IO PLLCFGR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->PLLCFGR)->PLLQ; }
            static inline void set_PLLQ(uint32_t value) { reinterpret_cast<__IO PLLCFGR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->PLLCFGR)->PLLQ = value; }
        };
        class CFGR
        {
        private:
            union CFGR_t
            {
                struct
                {
                    uint32_t SW             : 2;
                    uint32_t SWS            : 2;
                    uint32_t HPRE           : 4;
                    uint32_t reserved8      : 2;
                    uint32_t PPRE1          : 3;
                    uint32_t PPRE2          : 3;
                    uint32_t RTCPRE         : 5;
                    uint32_t MCO1           : 2;
                    uint32_t I2SSRC         : 1;
                    uint32_t MCO1PRE        : 3;
                    uint32_t MCO2PRE        : 3;
                    uint32_t MCO2           : 2;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                SW                     = (0x3U << 0),
                SWS                    = (0x3U << 2),
                HPRE                   = (0xFU << 4),
                PPRE1                  = (0x7U << 10),
                PPRE2                  = (0x7U << 13),
                RTCPRE                 = (0x1FU << 16),
                MCO1                   = (0x3U << 21),
                I2SSRC                 = (0x1U << 23),
                MCO1PRE                = (0x7U << 24),
                MCO2PRE                = (0x7U << 27),
                MCO2                   = (0x3U << 30),
            };
            static inline uint32_t get() { return reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CFGR; }
            static inline void set(uint32_t value) { reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CFGR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CFGR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CFGR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CFGR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_SW() { return reinterpret_cast<__IO CFGR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CFGR)->SW; }
            static inline void set_SW(uint32_t value) { reinterpret_cast<__IO CFGR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CFGR)->SW = value; }
            static inline uint32_t get_SWS() { return reinterpret_cast<__IO CFGR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CFGR)->SWS; }
            static inline void set_SWS(uint32_t value) { reinterpret_cast<__IO CFGR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CFGR)->SWS = value; }
            static inline uint32_t get_HPRE() { return reinterpret_cast<__IO CFGR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CFGR)->HPRE; }
            static inline void set_HPRE(uint32_t value) { reinterpret_cast<__IO CFGR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CFGR)->HPRE = value; }
            static inline uint32_t get_PPRE1() { return reinterpret_cast<__IO CFGR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CFGR)->PPRE1; }
            static inline void set_PPRE1(uint32_t value) { reinterpret_cast<__IO CFGR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CFGR)->PPRE1 = value; }
            static inline uint32_t get_PPRE2() { return reinterpret_cast<__IO CFGR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CFGR)->PPRE2; }
            static inline void set_PPRE2(uint32_t value) { reinterpret_cast<__IO CFGR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CFGR)->PPRE2 = value; }
            static inline uint32_t get_RTCPRE() { return reinterpret_cast<__IO CFGR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CFGR)->RTCPRE; }
            static inline void set_RTCPRE(uint32_t value) { reinterpret_cast<__IO CFGR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CFGR)->RTCPRE = value; }
            static inline uint32_t get_MCO1() { return reinterpret_cast<__IO CFGR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CFGR)->MCO1; }
            static inline void set_MCO1(uint32_t value) { reinterpret_cast<__IO CFGR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CFGR)->MCO1 = value; }
            static inline uint32_t get_MCO1PRE() { return reinterpret_cast<__IO CFGR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CFGR)->MCO1PRE; }
            static inline void set_MCO1PRE(uint32_t value) { reinterpret_cast<__IO CFGR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CFGR)->MCO1PRE = value; }
            static inline uint32_t get_MCO2PRE() { return reinterpret_cast<__IO CFGR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CFGR)->MCO2PRE; }
            static inline void set_MCO2PRE(uint32_t value) { reinterpret_cast<__IO CFGR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CFGR)->MCO2PRE = value; }
            static inline uint32_t get_MCO2() { return reinterpret_cast<__IO CFGR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CFGR)->MCO2; }
            static inline void set_MCO2(uint32_t value) { reinterpret_cast<__IO CFGR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CFGR)->MCO2 = value; }
        };
        class CIR
        {
        private:
            union CIR_t
            {
                struct
                {
                    uint32_t LSIRDYF        : 1;
                    uint32_t LSERDYF        : 1;
                    uint32_t HSIRDYF        : 1;
                    uint32_t HSERDYF        : 1;
                    uint32_t PLLRDYF        : 1;
                    uint32_t PLLI2SRDYF     : 1;
                    uint32_t reserved6      : 1;
                    uint32_t CSSF           : 1;
                    uint32_t LSIRDYIE       : 1;
                    uint32_t LSERDYIE       : 1;
                    uint32_t HSIRDYIE       : 1;
                    uint32_t HSERDYIE       : 1;
                    uint32_t PLLRDYIE       : 1;
                    uint32_t PLLI2SRDYIE    : 1;
                    uint32_t reserved14     : 2;
                    uint32_t LSIRDYC        : 1;
                    uint32_t LSERDYC        : 1;
                    uint32_t HSIRDYC        : 1;
                    uint32_t HSERDYC        : 1;
                    uint32_t PLLRDYC        : 1;
                    uint32_t PLLI2SRDYC     : 1;
                    uint32_t reserved22     : 1;
                    uint32_t CSSC           : 1;
                    uint32_t reserved24     : 8;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                LSIRDYF                = (0x1U << 0),
                LSERDYF                = (0x1U << 1),
                HSIRDYF                = (0x1U << 2),
                HSERDYF                = (0x1U << 3),
                PLLRDYF                = (0x1U << 4),
                PLLI2SRDYF             = (0x1U << 5),
                CSSF                   = (0x1U << 7),
                LSIRDYIE               = (0x1U << 8),
                LSERDYIE               = (0x1U << 9),
                HSIRDYIE               = (0x1U << 10),
                HSERDYIE               = (0x1U << 11),
                PLLRDYIE               = (0x1U << 12),
                PLLI2SRDYIE            = (0x1U << 13),
                LSIRDYC                = (0x1U << 16),
                LSERDYC                = (0x1U << 17),
                HSIRDYC                = (0x1U << 18),
                HSERDYC                = (0x1U << 19),
                PLLRDYC                = (0x1U << 20),
                PLLI2SRDYC             = (0x1U << 21),
                CSSC                   = (0x1U << 23),
            };
            static inline uint32_t get() { return reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CIR; }
            static inline void set(uint32_t value) { reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CIR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CIR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CIR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CIR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class AHB1RSTR
        {
        private:
            union AHB1RSTR_t
            {
                struct
                {
                    uint32_t GPIOARST       : 1;
                    uint32_t GPIOBRST       : 1;
                    uint32_t GPIOCRST       : 1;
                    uint32_t GPIODRST       : 1;
                    uint32_t GPIOERST       : 1;
                    uint32_t GPIOFRST       : 1;
                    uint32_t GPIOGRST       : 1;
                    uint32_t GPIOHRST       : 1;
                    uint32_t GPIOIRST       : 1;
                    uint32_t reserved9      : 3;
                    uint32_t CRCRST         : 1;
                    uint32_t reserved13     : 8;
                    uint32_t DMA1RST        : 1;
                    uint32_t DMA2RST        : 1;
                    uint32_t reserved23     : 2;
                    uint32_t ETHMACRST      : 1;
                    uint32_t reserved26     : 3;
                    uint32_t OTGHRST        : 1;
                    uint32_t reserved30     : 2;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                GPIOARST               = (0x1U << 0),
                GPIOBRST               = (0x1U << 1),
                GPIOCRST               = (0x1U << 2),
                GPIODRST               = (0x1U << 3),
                GPIOERST               = (0x1U << 4),
                GPIOFRST               = (0x1U << 5),
                GPIOGRST               = (0x1U << 6),
                GPIOHRST               = (0x1U << 7),
                GPIOIRST               = (0x1U << 8),
                CRCRST                 = (0x1U << 12),
                DMA1RST                = (0x1U << 21),
                DMA2RST                = (0x1U << 22),
                ETHMACRST              = (0x1U << 25),
                OTGHRST                = (0x1U << 29),
            };
            static inline uint32_t get() { return reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB1RSTR; }
            static inline void set(uint32_t value) { reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB1RSTR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB1RSTR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB1RSTR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB1RSTR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class AHB2RSTR
        {
        private:
            union AHB2RSTR_t
            {
                struct
                {
                    uint32_t DCMIRST        : 1;
                    uint32_t reserved1      : 5;
                    uint32_t RNGRST         : 1;
                    uint32_t OTGFSRST       : 1;
                    uint32_t reserved8      : 24;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DCMIRST                = (0x1U << 0),
                RNGRST                 = (0x1U << 6),
                OTGFSRST               = (0x1U << 7),
            };
            static inline uint32_t get() { return reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB2RSTR; }
            static inline void set(uint32_t value) { reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB2RSTR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB2RSTR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB2RSTR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB2RSTR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class AHB3RSTR
        {
        private:
            union AHB3RSTR_t
            {
                struct
                {
                    uint32_t FSMCRST        : 1;
                    uint32_t reserved1      : 31;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                FSMCRST                = (0x1U << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB3RSTR; }
            static inline void set(uint32_t value) { reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB3RSTR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB3RSTR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB3RSTR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB3RSTR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class APB1RSTR
        {
        private:
            union APB1RSTR_t
            {
                struct
                {
                    uint32_t TIM2RST        : 1;
                    uint32_t TIM3RST        : 1;
                    uint32_t TIM4RST        : 1;
                    uint32_t TIM5RST        : 1;
                    uint32_t TIM6RST        : 1;
                    uint32_t TIM7RST        : 1;
                    uint32_t TIM12RST       : 1;
                    uint32_t TIM13RST       : 1;
                    uint32_t TIM14RST       : 1;
                    uint32_t reserved9      : 2;
                    uint32_t WWDGRST        : 1;
                    uint32_t reserved12     : 2;
                    uint32_t SPI2RST        : 1;
                    uint32_t SPI3RST        : 1;
                    uint32_t reserved16     : 1;
                    uint32_t USART2RST      : 1;
                    uint32_t USART3RST      : 1;
                    uint32_t UART4RST       : 1;
                    uint32_t UART5RST       : 1;
                    uint32_t I2C1RST        : 1;
                    uint32_t I2C2RST        : 1;
                    uint32_t I2C3RST        : 1;
                    uint32_t reserved24     : 1;
                    uint32_t CAN1RST        : 1;
                    uint32_t CAN2RST        : 1;
                    uint32_t reserved27     : 1;
                    uint32_t PWRRST         : 1;
                    uint32_t DACRST         : 1;
                    uint32_t reserved30     : 2;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                TIM2RST                = (0x1U << 0),
                TIM3RST                = (0x1U << 1),
                TIM4RST                = (0x1U << 2),
                TIM5RST                = (0x1U << 3),
                TIM6RST                = (0x1U << 4),
                TIM7RST                = (0x1U << 5),
                TIM12RST               = (0x1U << 6),
                TIM13RST               = (0x1U << 7),
                TIM14RST               = (0x1U << 8),
                WWDGRST                = (0x1U << 11),
                SPI2RST                = (0x1U << 14),
                SPI3RST                = (0x1U << 15),
                USART2RST              = (0x1U << 17),
                USART3RST              = (0x1U << 18),
                UART4RST               = (0x1U << 19),
                UART5RST               = (0x1U << 20),
                I2C1RST                = (0x1U << 21),
                I2C2RST                = (0x1U << 22),
                I2C3RST                = (0x1U << 23),
                CAN1RST                = (0x1U << 25),
                CAN2RST                = (0x1U << 26),
                PWRRST                 = (0x1U << 28),
                DACRST                 = (0x1U << 29),
            };
            static inline uint32_t get() { return reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->APB1RSTR; }
            static inline void set(uint32_t value) { reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->APB1RSTR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->APB1RSTR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->APB1RSTR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->APB1RSTR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class APB2RSTR
        {
        private:
            union APB2RSTR_t
            {
                struct
                {
                    uint32_t TIM1RST        : 1;
                    uint32_t TIM8RST        : 1;
                    uint32_t reserved2      : 2;
                    uint32_t USART1RST      : 1;
                    uint32_t USART6RST      : 1;
                    uint32_t reserved6      : 2;
                    uint32_t ADCRST         : 1;
                    uint32_t reserved9      : 2;
                    uint32_t SDIORST        : 1;
                    uint32_t SPI1RST        : 1;
                    uint32_t reserved13     : 1;
                    uint32_t SYSCFGRST      : 1;
                    uint32_t reserved15     : 1;
                    uint32_t TIM9RST        : 1;
                    uint32_t TIM10RST       : 1;
                    uint32_t TIM11RST       : 1;
                    uint32_t reserved19     : 13;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                TIM1RST                = (0x1U << 0),
                TIM8RST                = (0x1U << 1),
                USART1RST              = (0x1U << 4),
                USART6RST              = (0x1U << 5),
                ADCRST                 = (0x1U << 8),
                SDIORST                = (0x1U << 11),
                SPI1RST                = (0x1U << 12),
                SYSCFGRST              = (0x1U << 14),
                TIM9RST                = (0x1U << 16),
                TIM10RST               = (0x1U << 17),
                TIM11RST               = (0x1U << 18),
            };
            static inline uint32_t get() { return reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->APB2RSTR; }
            static inline void set(uint32_t value) { reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->APB2RSTR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->APB2RSTR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->APB2RSTR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->APB2RSTR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class AHB1ENR
        {
        private:
            union AHB1ENR_t
            {
                struct
                {
                    uint32_t GPIOAEN        : 1;
                    uint32_t GPIOBEN        : 1;
                    uint32_t GPIOCEN        : 1;
                    uint32_t GPIODEN        : 1;
                    uint32_t GPIOEEN        : 1;
                    uint32_t GPIOFEN        : 1;
                    uint32_t GPIOGEN        : 1;
                    uint32_t GPIOHEN        : 1;
                    uint32_t GPIOIEN        : 1;
                    uint32_t reserved9      : 3;
                    uint32_t CRCEN          : 1;
                    uint32_t reserved13     : 5;
                    uint32_t BKPSRAMEN      : 1;
                    uint32_t reserved19     : 1;
                    uint32_t CCMDATARAMEN   : 1;
                    uint32_t DMA1EN         : 1;
                    uint32_t DMA2EN         : 1;
                    uint32_t reserved23     : 2;
                    uint32_t ETHMACEN       : 1;
                    uint32_t ETHMACTXEN     : 1;
                    uint32_t ETHMACRXEN     : 1;
                    uint32_t ETHMACPTPEN    : 1;
                    uint32_t OTGHSEN        : 1;
                    uint32_t OTGHSULPIEN    : 1;
                    uint32_t reserved31     : 1;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                GPIOAEN                = (0x1U << 0),
                GPIOBEN                = (0x1U << 1),
                GPIOCEN                = (0x1U << 2),
                GPIODEN                = (0x1U << 3),
                GPIOEEN                = (0x1U << 4),
                GPIOFEN                = (0x1U << 5),
                GPIOGEN                = (0x1U << 6),
                GPIOHEN                = (0x1U << 7),
                GPIOIEN                = (0x1U << 8),
                CRCEN                  = (0x1U << 12),
                BKPSRAMEN              = (0x1U << 18),
                CCMDATARAMEN           = (0x1U << 20),
                DMA1EN                 = (0x1U << 21),
                DMA2EN                 = (0x1U << 22),
                ETHMACEN               = (0x1U << 25),
                ETHMACTXEN             = (0x1U << 26),
                ETHMACRXEN             = (0x1U << 27),
                ETHMACPTPEN            = (0x1U << 28),
                OTGHSEN                = (0x1U << 29),
                OTGHSULPIEN            = (0x1U << 30),
            };
            static inline uint32_t get() { return reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB1ENR; }
            static inline void set(uint32_t value) { reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB1ENR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB1ENR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB1ENR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB1ENR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class AHB2ENR
        {
        private:
            union AHB2ENR_t
            {
                struct
                {
                    uint32_t DCMIEN         : 1;
                    uint32_t reserved1      : 5;
                    uint32_t RNGEN          : 1;
                    uint32_t OTGFSEN        : 1;
                    uint32_t reserved8      : 24;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DCMIEN                 = (0x1U << 0),
                RNGEN                  = (0x1U << 6),
                OTGFSEN                = (0x1U << 7),
            };
            static inline uint32_t get() { return reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB2ENR; }
            static inline void set(uint32_t value) { reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB2ENR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB2ENR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB2ENR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB2ENR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class AHB3ENR
        {
        private:
            union AHB3ENR_t
            {
                struct
                {
                    uint32_t FSMCEN         : 1;
                    uint32_t reserved1      : 31;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                FSMCEN                 = (0x1U << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB3ENR; }
            static inline void set(uint32_t value) { reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB3ENR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB3ENR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB3ENR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB3ENR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class APB1ENR
        {
        private:
            union APB1ENR_t
            {
                struct
                {
                    uint32_t TIM2EN         : 1;
                    uint32_t TIM3EN         : 1;
                    uint32_t TIM4EN         : 1;
                    uint32_t TIM5EN         : 1;
                    uint32_t TIM6EN         : 1;
                    uint32_t TIM7EN         : 1;
                    uint32_t TIM12EN        : 1;
                    uint32_t TIM13EN        : 1;
                    uint32_t TIM14EN        : 1;
                    uint32_t reserved9      : 2;
                    uint32_t WWDGEN         : 1;
                    uint32_t reserved12     : 2;
                    uint32_t SPI2EN         : 1;
                    uint32_t SPI3EN         : 1;
                    uint32_t reserved16     : 1;
                    uint32_t USART2EN       : 1;
                    uint32_t USART3EN       : 1;
                    uint32_t UART4EN        : 1;
                    uint32_t UART5EN        : 1;
                    uint32_t I2C1EN         : 1;
                    uint32_t I2C2EN         : 1;
                    uint32_t I2C3EN         : 1;
                    uint32_t reserved24     : 1;
                    uint32_t CAN1EN         : 1;
                    uint32_t CAN2EN         : 1;
                    uint32_t reserved27     : 1;
                    uint32_t PWREN          : 1;
                    uint32_t DACEN          : 1;
                    uint32_t reserved30     : 2;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                TIM2EN                 = (0x1U << 0),
                TIM3EN                 = (0x1U << 1),
                TIM4EN                 = (0x1U << 2),
                TIM5EN                 = (0x1U << 3),
                TIM6EN                 = (0x1U << 4),
                TIM7EN                 = (0x1U << 5),
                TIM12EN                = (0x1U << 6),
                TIM13EN                = (0x1U << 7),
                TIM14EN                = (0x1U << 8),
                WWDGEN                 = (0x1U << 11),
                SPI2EN                 = (0x1U << 14),
                SPI3EN                 = (0x1U << 15),
                USART2EN               = (0x1U << 17),
                USART3EN               = (0x1U << 18),
                UART4EN                = (0x1U << 19),
                UART5EN                = (0x1U << 20),
                I2C1EN                 = (0x1U << 21),
                I2C2EN                 = (0x1U << 22),
                I2C3EN                 = (0x1U << 23),
                CAN1EN                 = (0x1U << 25),
                CAN2EN                 = (0x1U << 26),
                PWREN                  = (0x1U << 28),
                DACEN                  = (0x1U << 29),
            };
            static inline uint32_t get() { return reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->APB1ENR; }
            static inline void set(uint32_t value) { reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->APB1ENR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->APB1ENR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->APB1ENR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->APB1ENR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class APB2ENR
        {
        private:
            union APB2ENR_t
            {
                struct
                {
                    uint32_t TIM1EN         : 1;
                    uint32_t TIM8EN         : 1;
                    uint32_t reserved2      : 2;
                    uint32_t USART1EN       : 1;
                    uint32_t USART6EN       : 1;
                    uint32_t reserved6      : 2;
                    uint32_t ADC1EN         : 1;
                    uint32_t ADC2EN         : 1;
                    uint32_t ADC3EN         : 1;
                    uint32_t SDIOEN         : 1;
                    uint32_t SPI1EN         : 1;
                    uint32_t reserved13     : 1;
                    uint32_t SYSCFGEN       : 1;
                    uint32_t reserved15     : 1;
                    uint32_t TIM9EN         : 1;
                    uint32_t TIM10EN        : 1;
                    uint32_t TIM11EN        : 1;
                    uint32_t reserved19     : 13;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                TIM1EN                 = (0x1U << 0),
                TIM8EN                 = (0x1U << 1),
                USART1EN               = (0x1U << 4),
                USART6EN               = (0x1U << 5),
                ADC1EN                 = (0x1U << 8),
                ADC2EN                 = (0x1U << 9),
                ADC3EN                 = (0x1U << 10),
                SDIOEN                 = (0x1U << 11),
                SPI1EN                 = (0x1U << 12),
                SYSCFGEN               = (0x1U << 14),
                TIM9EN                 = (0x1U << 16),
                TIM10EN                = (0x1U << 17),
                TIM11EN                = (0x1U << 18),
            };
            static inline uint32_t get() { return reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->APB2ENR; }
            static inline void set(uint32_t value) { reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->APB2ENR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->APB2ENR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->APB2ENR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->APB2ENR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class AHB1LPENR
        {
        private:
            union AHB1LPENR_t
            {
                struct
                {
                    uint32_t GPIOALPEN      : 1;
                    uint32_t GPIOBLPEN      : 1;
                    uint32_t GPIOCLPEN      : 1;
                    uint32_t GPIODLPEN      : 1;
                    uint32_t GPIOELPEN      : 1;
                    uint32_t GPIOFLPEN      : 1;
                    uint32_t GPIOGLPEN      : 1;
                    uint32_t GPIOHLPEN      : 1;
                    uint32_t GPIOILPEN      : 1;
                    uint32_t reserved9      : 3;
                    uint32_t CRCLPEN        : 1;
                    uint32_t reserved13     : 2;
                    uint32_t FLITFLPEN      : 1;
                    uint32_t SRAM1LPEN      : 1;
                    uint32_t SRAM2LPEN      : 1;
                    uint32_t BKPSRAMLPEN    : 1;
                    uint32_t reserved19     : 2;
                    uint32_t DMA1LPEN       : 1;
                    uint32_t DMA2LPEN       : 1;
                    uint32_t reserved23     : 2;
                    uint32_t ETHMACLPEN     : 1;
                    uint32_t ETHMACTXLPEN   : 1;
                    uint32_t ETHMACRXLPEN   : 1;
                    uint32_t ETHMACPTPLPEN  : 1;
                    uint32_t OTGHSLPEN      : 1;
                    uint32_t OTGHSULPILPEN  : 1;
                    uint32_t reserved31     : 1;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                GPIOALPEN              = (0x1U << 0),
                GPIOBLPEN              = (0x1U << 1),
                GPIOCLPEN              = (0x1U << 2),
                GPIODLPEN              = (0x1U << 3),
                GPIOELPEN              = (0x1U << 4),
                GPIOFLPEN              = (0x1U << 5),
                GPIOGLPEN              = (0x1U << 6),
                GPIOHLPEN              = (0x1U << 7),
                GPIOILPEN              = (0x1U << 8),
                CRCLPEN                = (0x1U << 12),
                FLITFLPEN              = (0x1U << 15),
                SRAM1LPEN              = (0x1U << 16),
                SRAM2LPEN              = (0x1U << 17),
                BKPSRAMLPEN            = (0x1U << 18),
                DMA1LPEN               = (0x1U << 21),
                DMA2LPEN               = (0x1U << 22),
                ETHMACLPEN             = (0x1U << 25),
                ETHMACTXLPEN           = (0x1U << 26),
                ETHMACRXLPEN           = (0x1U << 27),
                ETHMACPTPLPEN          = (0x1U << 28),
                OTGHSLPEN              = (0x1U << 29),
                OTGHSULPILPEN          = (0x1U << 30),
            };
            static inline uint32_t get() { return reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB1LPENR; }
            static inline void set(uint32_t value) { reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB1LPENR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB1LPENR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB1LPENR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB1LPENR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class AHB2LPENR
        {
        private:
            union AHB2LPENR_t
            {
                struct
                {
                    uint32_t DCMILPEN       : 1;
                    uint32_t reserved1      : 5;
                    uint32_t RNGLPEN        : 1;
                    uint32_t OTGFSLPEN      : 1;
                    uint32_t reserved8      : 24;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DCMILPEN               = (0x1U << 0),
                RNGLPEN                = (0x1U << 6),
                OTGFSLPEN              = (0x1U << 7),
            };
            static inline uint32_t get() { return reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB2LPENR; }
            static inline void set(uint32_t value) { reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB2LPENR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB2LPENR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB2LPENR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB2LPENR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class AHB3LPENR
        {
        private:
            union AHB3LPENR_t
            {
                struct
                {
                    uint32_t FSMCLPEN       : 1;
                    uint32_t reserved1      : 31;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                FSMCLPEN               = (0x1U << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB3LPENR; }
            static inline void set(uint32_t value) { reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB3LPENR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB3LPENR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB3LPENR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->AHB3LPENR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class APB1LPENR
        {
        private:
            union APB1LPENR_t
            {
                struct
                {
                    uint32_t TIM2LPEN       : 1;
                    uint32_t TIM3LPEN       : 1;
                    uint32_t TIM4LPEN       : 1;
                    uint32_t TIM5LPEN       : 1;
                    uint32_t TIM6LPEN       : 1;
                    uint32_t TIM7LPEN       : 1;
                    uint32_t TIM12LPEN      : 1;
                    uint32_t TIM13LPEN      : 1;
                    uint32_t TIM14LPEN      : 1;
                    uint32_t reserved9      : 2;
                    uint32_t WWDGLPEN       : 1;
                    uint32_t reserved12     : 2;
                    uint32_t SPI2LPEN       : 1;
                    uint32_t SPI3LPEN       : 1;
                    uint32_t reserved16     : 1;
                    uint32_t USART2LPEN     : 1;
                    uint32_t USART3LPEN     : 1;
                    uint32_t UART4LPEN      : 1;
                    uint32_t UART5LPEN      : 1;
                    uint32_t I2C1LPEN       : 1;
                    uint32_t I2C2LPEN       : 1;
                    uint32_t I2C3LPEN       : 1;
                    uint32_t reserved24     : 1;
                    uint32_t CAN1LPEN       : 1;
                    uint32_t CAN2LPEN       : 1;
                    uint32_t reserved27     : 1;
                    uint32_t PWRLPEN        : 1;
                    uint32_t DACLPEN        : 1;
                    uint32_t reserved30     : 2;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                TIM2LPEN               = (0x1U << 0),
                TIM3LPEN               = (0x1U << 1),
                TIM4LPEN               = (0x1U << 2),
                TIM5LPEN               = (0x1U << 3),
                TIM6LPEN               = (0x1U << 4),
                TIM7LPEN               = (0x1U << 5),
                TIM12LPEN              = (0x1U << 6),
                TIM13LPEN              = (0x1U << 7),
                TIM14LPEN              = (0x1U << 8),
                WWDGLPEN               = (0x1U << 11),
                SPI2LPEN               = (0x1U << 14),
                SPI3LPEN               = (0x1U << 15),
                USART2LPEN             = (0x1U << 17),
                USART3LPEN             = (0x1U << 18),
                UART4LPEN              = (0x1U << 19),
                UART5LPEN              = (0x1U << 20),
                I2C1LPEN               = (0x1U << 21),
                I2C2LPEN               = (0x1U << 22),
                I2C3LPEN               = (0x1U << 23),
                CAN1LPEN               = (0x1U << 25),
                CAN2LPEN               = (0x1U << 26),
                PWRLPEN                = (0x1U << 28),
                DACLPEN                = (0x1U << 29),
            };
            static inline uint32_t get() { return reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->APB1LPENR; }
            static inline void set(uint32_t value) { reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->APB1LPENR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->APB1LPENR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->APB1LPENR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->APB1LPENR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class APB2LPENR
        {
        private:
            union APB2LPENR_t
            {
                struct
                {
                    uint32_t TIM1LPEN       : 1;
                    uint32_t TIM8LPEN       : 1;
                    uint32_t reserved2      : 2;
                    uint32_t USART1LPEN     : 1;
                    uint32_t USART6LPEN     : 1;
                    uint32_t reserved6      : 2;
                    uint32_t ADC1LPEN       : 1;
                    uint32_t ADC2LPEN       : 1;
                    uint32_t ADC3LPEN       : 1;
                    uint32_t SDIOLPEN       : 1;
                    uint32_t SPI1LPEN       : 1;
                    uint32_t reserved13     : 1;
                    uint32_t SYSCFGLPEN     : 1;
                    uint32_t reserved15     : 1;
                    uint32_t TIM9LPEN       : 1;
                    uint32_t TIM10LPEN      : 1;
                    uint32_t TIM11LPEN      : 1;
                    uint32_t reserved19     : 13;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                TIM1LPEN               = (0x1U << 0),
                TIM8LPEN               = (0x1U << 1),
                USART1LPEN             = (0x1U << 4),
                USART6LPEN             = (0x1U << 5),
                ADC1LPEN               = (0x1U << 8),
                ADC2LPEN               = (0x1U << 9),
                ADC3LPEN               = (0x1U << 10),
                SDIOLPEN               = (0x1U << 11),
                SPI1LPEN               = (0x1U << 12),
                SYSCFGLPEN             = (0x1U << 14),
                TIM9LPEN               = (0x1U << 16),
                TIM10LPEN              = (0x1U << 17),
                TIM11LPEN              = (0x1U << 18),
            };
            static inline uint32_t get() { return reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->APB2LPENR; }
            static inline void set(uint32_t value) { reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->APB2LPENR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->APB2LPENR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->APB2LPENR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->APB2LPENR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class BDCR
        {
        private:
            union BDCR_t
            {
                struct
                {
                    uint32_t LSEON          : 1;
                    uint32_t LSERDY         : 1;
                    uint32_t LSEBYP         : 1;
                    uint32_t reserved3      : 5;
                    uint32_t RTCSEL         : 2;
                    uint32_t reserved10     : 5;
                    uint32_t RTCEN          : 1;
                    uint32_t BDRST          : 1;
                    uint32_t reserved17     : 15;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                LSEON                  = (0x1U << 0),
                LSERDY                 = (0x1U << 1),
                LSEBYP                 = (0x1U << 2),
                RTCSEL                 = (0x3U << 8),
                RTCEN                  = (0x1U << 15),
                BDRST                  = (0x1U << 16),
            };
            static inline uint32_t get() { return reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->BDCR; }
            static inline void set(uint32_t value) { reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->BDCR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->BDCR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->BDCR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->BDCR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_RTCSEL() { return reinterpret_cast<__IO BDCR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->BDCR)->RTCSEL; }
            static inline void set_RTCSEL(uint32_t value) { reinterpret_cast<__IO BDCR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->BDCR)->RTCSEL = value; }
        };
        class CSR
        {
        private:
            union CSR_t
            {
                struct
                {
                    uint32_t LSION          : 1;
                    uint32_t LSIRDY         : 1;
                    uint32_t reserved2      : 22;
                    uint32_t RMVF           : 1;
                    uint32_t BORRSTF        : 1;
                    uint32_t PINRSTF        : 1;
                    uint32_t PORRSTF        : 1;
                    uint32_t SFTRSTF        : 1;
                    uint32_t IWDGRSTF       : 1;
                    uint32_t WWDGRSTF       : 1;
                    uint32_t LPWRRSTF       : 1;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                LSION                  = (0x1U << 0),
                LSIRDY                 = (0x1U << 1),
                RMVF                   = (0x1U << 24),
                BORRSTF                = (0x1U << 25),
                PINRSTF                = (0x1U << 26),
                PORRSTF                = (0x1U << 27),
                SFTRSTF                = (0x1U << 28),
                IWDGRSTF               = (0x1U << 29),
                WWDGRSTF               = (0x1U << 30),
                LPWRRSTF               = (0x1U << 31),
            };
            static inline uint32_t get() { return reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CSR; }
            static inline void set(uint32_t value) { reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CSR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CSR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CSR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->CSR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class SSCGR
        {
        private:
            union SSCGR_t
            {
                struct
                {
                    uint32_t MODPER         : 13;
                    uint32_t INCSTEP        : 15;
                    uint32_t reserved28     : 2;
                    uint32_t SPREADSEL      : 1;
                    uint32_t SSCGEN         : 1;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                MODPER                 = (0x1FFFU << 0),
                INCSTEP                = (0x7FFFU << 13),
                SPREADSEL              = (0x1U << 30),
                SSCGEN                 = (0x1U << 31),
            };
            static inline uint32_t get() { return reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->SSCGR; }
            static inline void set(uint32_t value) { reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->SSCGR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->SSCGR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->SSCGR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->SSCGR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_MODPER() { return reinterpret_cast<__IO SSCGR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->SSCGR)->MODPER; }
            static inline void set_MODPER(uint32_t value) { reinterpret_cast<__IO SSCGR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->SSCGR)->MODPER = value; }
            static inline uint32_t get_INCSTEP() { return reinterpret_cast<__IO SSCGR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->SSCGR)->INCSTEP; }
            static inline void set_INCSTEP(uint32_t value) { reinterpret_cast<__IO SSCGR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->SSCGR)->INCSTEP = value; }
        };
        class PLLI2SCFGR
        {
        private:
            union PLLI2SCFGR_t
            {
                struct
                {
                    uint32_t reserved0      : 6;
                    uint32_t PLLI2SN        : 9;
                    uint32_t reserved15     : 13;
                    uint32_t PLLI2SR        : 3;
                    uint32_t reserved31     : 1;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                PLLI2SN                = (0x1FFU << 6),
                PLLI2SR                = (0x7U << 28),
            };
            static inline uint32_t get() { return reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->PLLI2SCFGR; }
            static inline void set(uint32_t value) { reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->PLLI2SCFGR = value; }
            static inline uint32_t get_PLLI2SN() { return reinterpret_cast<__IO PLLI2SCFGR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->PLLI2SCFGR)->PLLI2SN; }
            static inline void set_PLLI2SN(uint32_t value) { reinterpret_cast<__IO PLLI2SCFGR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->PLLI2SCFGR)->PLLI2SN = value; }
            static inline uint32_t get_PLLI2SR() { return reinterpret_cast<__IO PLLI2SCFGR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->PLLI2SCFGR)->PLLI2SR; }
            static inline void set_PLLI2SR(uint32_t value) { reinterpret_cast<__IO PLLI2SCFGR_t*>(&reinterpret_cast<RCC_t*>(STM32::RCC_BASE)->PLLI2SCFGR)->PLLI2SR = value; }
        };
    };
    /* RTC DEFINITION */
    class RTC
    {
    private:
        struct RTC_t
        {
            __IO uint32_t                 TR;
            __IO uint32_t                 DR;
            __IO uint32_t                 CR;
            __IO uint32_t                 ISR;
            __IO uint32_t                 PRER;
            __IO uint32_t                 WUTR;
            __IO uint32_t                 CALIBR;
            __IO uint32_t                 ALRMAR;
            __IO uint32_t                 ALRMBR;
            __IO uint32_t                 WPR;
            __IO uint32_t                 SSR;
            __IO uint32_t                 SHIFTR;
            __IO uint32_t                 TSTR;
            __IO uint32_t                 TSDR;
            __IO uint32_t                 TSSSR;
            __IO uint32_t                 CALR;
            __IO uint32_t                 TAFCR;
            __IO uint32_t                 ALRMASSR;
            __IO uint32_t                 ALRMBSSR;
            uint32_t                      RESERVED7;
            __IO uint32_t                 BKP0R;
            __IO uint32_t                 BKP1R;
            __IO uint32_t                 BKP2R;
            __IO uint32_t                 BKP3R;
            __IO uint32_t                 BKP4R;
            __IO uint32_t                 BKP5R;
            __IO uint32_t                 BKP6R;
            __IO uint32_t                 BKP7R;
            __IO uint32_t                 BKP8R;
            __IO uint32_t                 BKP9R;
            __IO uint32_t                 BKP10R;
            __IO uint32_t                 BKP11R;
            __IO uint32_t                 BKP12R;
            __IO uint32_t                 BKP13R;
            __IO uint32_t                 BKP14R;
            __IO uint32_t                 BKP15R;
            __IO uint32_t                 BKP16R;
            __IO uint32_t                 BKP17R;
            __IO uint32_t                 BKP18R;
            __IO uint32_t                 BKP19R;
        };
    public:
        class TR
        {
        private:
            union TR_t
            {
                struct
                {
                    uint32_t reserved0      : 22;
                    uint32_t PM             : 1;
                    uint32_t HT             : 2;
                    uint32_t HU             : 4;
                    uint32_t MNT            : 3;
                    uint32_t MNU            : 4;
                    uint32_t ST             : 3;
                    uint32_t SU             : 4;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                PM                     = (0x1U << 22),
                HT                     = (0x3U << 20),
                HU                     = (0xFU << 16),
                MNT                    = (0x7U << 12),
                MNU                    = (0xFU << 8),
                ST                     = (0x7U << 4),
                SU                     = (0xFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TR; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_HT() { return reinterpret_cast<__IO TR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TR)->HT; }
            static inline void set_HT(uint32_t value) { reinterpret_cast<__IO TR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TR)->HT = value; }
            static inline uint32_t get_HU() { return reinterpret_cast<__IO TR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TR)->HU; }
            static inline void set_HU(uint32_t value) { reinterpret_cast<__IO TR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TR)->HU = value; }
            static inline uint32_t get_MNT() { return reinterpret_cast<__IO TR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TR)->MNT; }
            static inline void set_MNT(uint32_t value) { reinterpret_cast<__IO TR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TR)->MNT = value; }
            static inline uint32_t get_MNU() { return reinterpret_cast<__IO TR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TR)->MNU; }
            static inline void set_MNU(uint32_t value) { reinterpret_cast<__IO TR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TR)->MNU = value; }
            static inline uint32_t get_ST() { return reinterpret_cast<__IO TR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TR)->ST; }
            static inline void set_ST(uint32_t value) { reinterpret_cast<__IO TR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TR)->ST = value; }
            static inline uint32_t get_SU() { return reinterpret_cast<__IO TR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TR)->SU; }
            static inline void set_SU(uint32_t value) { reinterpret_cast<__IO TR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TR)->SU = value; }
        };
        class DR
        {
        private:
            union DR_t
            {
                struct
                {
                    uint32_t reserved0      : 20;
                    uint32_t YT             : 4;
                    uint32_t YU             : 4;
                    uint32_t WDU            : 3;
                    uint32_t MT             : 1;
                    uint32_t MU             : 4;
                    uint32_t DT             : 2;
                    uint32_t DU             : 4;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                YT                     = (0xFU << 20),
                YU                     = (0xFU << 16),
                WDU                    = (0x7U << 13),
                MT                     = (0x1U << 12),
                MU                     = (0xFU << 8),
                DT                     = (0x3U << 4),
                DU                     = (0xFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->DR; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->DR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->DR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->DR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->DR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_YT() { return reinterpret_cast<__IO DR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->DR)->YT; }
            static inline void set_YT(uint32_t value) { reinterpret_cast<__IO DR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->DR)->YT = value; }
            static inline uint32_t get_YU() { return reinterpret_cast<__IO DR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->DR)->YU; }
            static inline void set_YU(uint32_t value) { reinterpret_cast<__IO DR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->DR)->YU = value; }
            static inline uint32_t get_WDU() { return reinterpret_cast<__IO DR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->DR)->WDU; }
            static inline void set_WDU(uint32_t value) { reinterpret_cast<__IO DR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->DR)->WDU = value; }
            static inline uint32_t get_MU() { return reinterpret_cast<__IO DR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->DR)->MU; }
            static inline void set_MU(uint32_t value) { reinterpret_cast<__IO DR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->DR)->MU = value; }
            static inline uint32_t get_DT() { return reinterpret_cast<__IO DR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->DR)->DT; }
            static inline void set_DT(uint32_t value) { reinterpret_cast<__IO DR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->DR)->DT = value; }
            static inline uint32_t get_DU() { return reinterpret_cast<__IO DR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->DR)->DU; }
            static inline void set_DU(uint32_t value) { reinterpret_cast<__IO DR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->DR)->DU = value; }
        };
        class CR
        {
        private:
            union CR_t
            {
                struct
                {
                    uint32_t reserved0      : 23;
                    uint32_t COE            : 1;
                    uint32_t OSEL           : 2;
                    uint32_t POL            : 1;
                    uint32_t COSEL          : 1;
                    uint32_t BKP            : 1;
                    uint32_t SUB1H          : 1;
                    uint32_t ADD1H          : 1;
                    uint32_t TSIE           : 1;
                    uint32_t WUTIE          : 1;
                    uint32_t ALRBIE         : 1;
                    uint32_t ALRAIE         : 1;
                    uint32_t TSE            : 1;
                    uint32_t WUTE           : 1;
                    uint32_t ALRBE          : 1;
                    uint32_t ALRAE          : 1;
                    uint32_t DCE            : 1;
                    uint32_t FMT            : 1;
                    uint32_t BYPSHAD        : 1;
                    uint32_t REFCKON        : 1;
                    uint32_t TSEDGE         : 1;
                    uint32_t WUCKSEL        : 3;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                COE                    = (0x1U << 23),
                OSEL                   = (0x3U << 21),
                POL                    = (0x1U << 20),
                COSEL                  = (0x1U << 19),
                BKP                    = (0x1U << 18),
                SUB1H                  = (0x1U << 17),
                ADD1H                  = (0x1U << 16),
                TSIE                   = (0x1U << 15),
                WUTIE                  = (0x1U << 14),
                ALRBIE                 = (0x1U << 13),
                ALRAIE                 = (0x1U << 12),
                TSE                    = (0x1U << 11),
                WUTE                   = (0x1U << 10),
                ALRBE                  = (0x1U << 9),
                ALRAE                  = (0x1U << 8),
                DCE                    = (0x1U << 7),
                FMT                    = (0x1U << 6),
                BYPSHAD                = (0x1U << 5),
                REFCKON                = (0x1U << 4),
                TSEDGE                 = (0x1U << 3),
                WUCKSEL                = (0x7U << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->CR; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->CR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->CR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->CR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->CR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_OSEL() { return reinterpret_cast<__IO CR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->CR)->OSEL; }
            static inline void set_OSEL(uint32_t value) { reinterpret_cast<__IO CR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->CR)->OSEL = value; }
            static inline uint32_t get_WUCKSEL() { return reinterpret_cast<__IO CR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->CR)->WUCKSEL; }
            static inline void set_WUCKSEL(uint32_t value) { reinterpret_cast<__IO CR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->CR)->WUCKSEL = value; }
        };
        class ISR
        {
        private:
            union ISR_t
            {
                struct
                {
                    uint32_t reserved0      : 16;
                    uint32_t RECALPF        : 1;
                    uint32_t TAMP1F         : 1;
                    uint32_t TAMP2F         : 1;
                    uint32_t TSOVF          : 1;
                    uint32_t TSF            : 1;
                    uint32_t WUTF           : 1;
                    uint32_t ALRBF          : 1;
                    uint32_t ALRAF          : 1;
                    uint32_t INIT           : 1;
                    uint32_t INITF          : 1;
                    uint32_t RSF            : 1;
                    uint32_t INITS          : 1;
                    uint32_t SHPF           : 1;
                    uint32_t WUTWF          : 1;
                    uint32_t ALRBWF         : 1;
                    uint32_t ALRAWF         : 1;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                RECALPF                = (0x1U << 16),
                TAMP1F                 = (0x1U << 13),
                TAMP2F                 = (0x1U << 14),
                TSOVF                  = (0x1U << 12),
                TSF                    = (0x1U << 11),
                WUTF                   = (0x1U << 10),
                ALRBF                  = (0x1U << 9),
                ALRAF                  = (0x1U << 8),
                INIT                   = (0x1U << 7),
                INITF                  = (0x1U << 6),
                RSF                    = (0x1U << 5),
                INITS                  = (0x1U << 4),
                SHPF                   = (0x1U << 3),
                WUTWF                  = (0x1U << 2),
                ALRBWF                 = (0x1U << 1),
                ALRAWF                 = (0x1U << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ISR; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ISR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ISR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ISR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ISR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class PRER
        {
        private:
            union PRER_t
            {
                struct
                {
                    uint32_t reserved0      : 16;
                    uint32_t PREDIV_A       : 7;
                    uint32_t PREDIV_S       : 15;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                PREDIV_A               = (0x7FU << 16),
                PREDIV_S               = (0x7FFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->PRER; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->PRER = value; }
            static inline uint32_t get_PREDIV_A() { return reinterpret_cast<__IO PRER_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->PRER)->PREDIV_A; }
            static inline void set_PREDIV_A(uint32_t value) { reinterpret_cast<__IO PRER_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->PRER)->PREDIV_A = value; }
            static inline uint32_t get_PREDIV_S() { return reinterpret_cast<__IO PRER_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->PRER)->PREDIV_S; }
            static inline void set_PREDIV_S(uint32_t value) { reinterpret_cast<__IO PRER_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->PRER)->PREDIV_S = value; }
        };
        class WUTR
        {
        private:
            union WUTR_t
            {
                struct
                {
                    uint32_t WUT            : 16;
                    uint32_t reserved16     : 16;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                WUT                    = (0xFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->WUTR; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->WUTR = value; }
            static inline uint32_t get_WUT() { return reinterpret_cast<__IO WUTR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->WUTR)->WUT; }
            static inline void set_WUT(uint32_t value) { reinterpret_cast<__IO WUTR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->WUTR)->WUT = value; }
        };
        class CALIBR
        {
        private:
            union CALIBR_t
            {
                struct
                {
                    uint32_t reserved0      : 7;
                    uint32_t DCS            : 1;
                    uint32_t DC             : 5;
                    uint32_t reserved13     : 19;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DCS                    = (0x1U << 7),
                DC                     = (0x1FU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->CALIBR; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->CALIBR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->CALIBR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->CALIBR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->CALIBR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_DC() { return reinterpret_cast<__IO CALIBR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->CALIBR)->DC; }
            static inline void set_DC(uint32_t value) { reinterpret_cast<__IO CALIBR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->CALIBR)->DC = value; }
        };
        class ALRMAR
        {
        private:
            union ALRMAR_t
            {
                struct
                {
                    uint32_t reserved0      : 31;
                    uint32_t MSK4           : 1;
                    uint32_t WDSEL          : 1;
                    uint32_t DT             : 2;
                    uint32_t DU             : 4;
                    uint32_t MSK3           : 1;
                    uint32_t PM             : 1;
                    uint32_t HT             : 2;
                    uint32_t HU             : 4;
                    uint32_t MSK2           : 1;
                    uint32_t MNT            : 3;
                    uint32_t MNU            : 4;
                    uint32_t MSK1           : 1;
                    uint32_t ST             : 3;
                    uint32_t SU             : 4;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                MSK4                   = (0x1U << 31),
                WDSEL                  = (0x1U << 30),
                DT                     = (0x3U << 28),
                DU                     = (0xFU << 24),
                MSK3                   = (0x1U << 23),
                PM                     = (0x1U << 22),
                HT                     = (0x3U << 20),
                HU                     = (0xFU << 16),
                MSK2                   = (0x1U << 15),
                MNT                    = (0x7U << 12),
                MNU                    = (0xFU << 8),
                MSK1                   = (0x1U << 7),
                ST                     = (0x7U << 4),
                SU                     = (0xFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMAR; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMAR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMAR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMAR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMAR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_DT() { return reinterpret_cast<__IO ALRMAR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMAR)->DT; }
            static inline void set_DT(uint32_t value) { reinterpret_cast<__IO ALRMAR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMAR)->DT = value; }
            static inline uint32_t get_DU() { return reinterpret_cast<__IO ALRMAR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMAR)->DU; }
            static inline void set_DU(uint32_t value) { reinterpret_cast<__IO ALRMAR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMAR)->DU = value; }
            static inline uint32_t get_HT() { return reinterpret_cast<__IO ALRMAR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMAR)->HT; }
            static inline void set_HT(uint32_t value) { reinterpret_cast<__IO ALRMAR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMAR)->HT = value; }
            static inline uint32_t get_HU() { return reinterpret_cast<__IO ALRMAR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMAR)->HU; }
            static inline void set_HU(uint32_t value) { reinterpret_cast<__IO ALRMAR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMAR)->HU = value; }
            static inline uint32_t get_MNT() { return reinterpret_cast<__IO ALRMAR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMAR)->MNT; }
            static inline void set_MNT(uint32_t value) { reinterpret_cast<__IO ALRMAR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMAR)->MNT = value; }
            static inline uint32_t get_MNU() { return reinterpret_cast<__IO ALRMAR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMAR)->MNU; }
            static inline void set_MNU(uint32_t value) { reinterpret_cast<__IO ALRMAR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMAR)->MNU = value; }
            static inline uint32_t get_ST() { return reinterpret_cast<__IO ALRMAR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMAR)->ST; }
            static inline void set_ST(uint32_t value) { reinterpret_cast<__IO ALRMAR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMAR)->ST = value; }
            static inline uint32_t get_SU() { return reinterpret_cast<__IO ALRMAR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMAR)->SU; }
            static inline void set_SU(uint32_t value) { reinterpret_cast<__IO ALRMAR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMAR)->SU = value; }
        };
        class ALRMBR
        {
        private:
            union ALRMBR_t
            {
                struct
                {
                    uint32_t reserved0      : 31;
                    uint32_t MSK4           : 1;
                    uint32_t WDSEL          : 1;
                    uint32_t DT             : 2;
                    uint32_t DU             : 4;
                    uint32_t MSK3           : 1;
                    uint32_t PM             : 1;
                    uint32_t HT             : 2;
                    uint32_t HU             : 4;
                    uint32_t MSK2           : 1;
                    uint32_t MNT            : 3;
                    uint32_t MNU            : 4;
                    uint32_t MSK1           : 1;
                    uint32_t ST             : 3;
                    uint32_t SU             : 4;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                MSK4                   = (0x1U << 31),
                WDSEL                  = (0x1U << 30),
                DT                     = (0x3U << 28),
                DU                     = (0xFU << 24),
                MSK3                   = (0x1U << 23),
                PM                     = (0x1U << 22),
                HT                     = (0x3U << 20),
                HU                     = (0xFU << 16),
                MSK2                   = (0x1U << 15),
                MNT                    = (0x7U << 12),
                MNU                    = (0xFU << 8),
                MSK1                   = (0x1U << 7),
                ST                     = (0x7U << 4),
                SU                     = (0xFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMBR; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMBR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMBR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMBR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMBR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_DT() { return reinterpret_cast<__IO ALRMBR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMBR)->DT; }
            static inline void set_DT(uint32_t value) { reinterpret_cast<__IO ALRMBR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMBR)->DT = value; }
            static inline uint32_t get_DU() { return reinterpret_cast<__IO ALRMBR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMBR)->DU; }
            static inline void set_DU(uint32_t value) { reinterpret_cast<__IO ALRMBR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMBR)->DU = value; }
            static inline uint32_t get_HT() { return reinterpret_cast<__IO ALRMBR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMBR)->HT; }
            static inline void set_HT(uint32_t value) { reinterpret_cast<__IO ALRMBR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMBR)->HT = value; }
            static inline uint32_t get_HU() { return reinterpret_cast<__IO ALRMBR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMBR)->HU; }
            static inline void set_HU(uint32_t value) { reinterpret_cast<__IO ALRMBR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMBR)->HU = value; }
            static inline uint32_t get_MNT() { return reinterpret_cast<__IO ALRMBR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMBR)->MNT; }
            static inline void set_MNT(uint32_t value) { reinterpret_cast<__IO ALRMBR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMBR)->MNT = value; }
            static inline uint32_t get_MNU() { return reinterpret_cast<__IO ALRMBR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMBR)->MNU; }
            static inline void set_MNU(uint32_t value) { reinterpret_cast<__IO ALRMBR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMBR)->MNU = value; }
            static inline uint32_t get_ST() { return reinterpret_cast<__IO ALRMBR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMBR)->ST; }
            static inline void set_ST(uint32_t value) { reinterpret_cast<__IO ALRMBR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMBR)->ST = value; }
            static inline uint32_t get_SU() { return reinterpret_cast<__IO ALRMBR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMBR)->SU; }
            static inline void set_SU(uint32_t value) { reinterpret_cast<__IO ALRMBR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMBR)->SU = value; }
        };
        class WPR
        {
        private:
            union WPR_t
            {
                struct
                {
                    uint32_t KEY            : 8;
                    uint32_t reserved8      : 24;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                KEY                    = (0xFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->WPR; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->WPR = value; }
            static inline uint32_t get_KEY() { return reinterpret_cast<__IO WPR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->WPR)->KEY; }
            static inline void set_KEY(uint32_t value) { reinterpret_cast<__IO WPR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->WPR)->KEY = value; }
        };
        class SSR
        {
        private:
            union SSR_t
            {
                struct
                {
                    uint32_t SS             : 16;
                    uint32_t reserved16     : 16;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                SS                     = (0xFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->SSR; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->SSR = value; }
            static inline uint32_t get_SS() { return reinterpret_cast<__IO SSR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->SSR)->SS; }
            static inline void set_SS(uint32_t value) { reinterpret_cast<__IO SSR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->SSR)->SS = value; }
        };
        class SHIFTR
        {
        private:
            union SHIFTR_t
            {
                struct
                {
                    uint32_t SUBFS          : 15;
                    uint32_t reserved15     : 16;
                    uint32_t ADD1S          : 1;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                SUBFS                  = (0x7FFFU << 0),
                ADD1S                  = (0x1U << 31),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->SHIFTR; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->SHIFTR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->SHIFTR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->SHIFTR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->SHIFTR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_SUBFS() { return reinterpret_cast<__IO SHIFTR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->SHIFTR)->SUBFS; }
            static inline void set_SUBFS(uint32_t value) { reinterpret_cast<__IO SHIFTR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->SHIFTR)->SUBFS = value; }
        };
        class TSTR
        {
        private:
            union TSTR_t
            {
                struct
                {
                    uint32_t reserved0      : 22;
                    uint32_t PM             : 1;
                    uint32_t HT             : 2;
                    uint32_t HU             : 4;
                    uint32_t MNT            : 3;
                    uint32_t MNU            : 4;
                    uint32_t ST             : 3;
                    uint32_t SU             : 4;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                PM                     = (0x1U << 22),
                HT                     = (0x3U << 20),
                HU                     = (0xFU << 16),
                MNT                    = (0x7U << 12),
                MNU                    = (0xFU << 8),
                ST                     = (0x7U << 4),
                SU                     = (0xFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TSTR; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TSTR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TSTR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TSTR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TSTR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_HT() { return reinterpret_cast<__IO TSTR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TSTR)->HT; }
            static inline void set_HT(uint32_t value) { reinterpret_cast<__IO TSTR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TSTR)->HT = value; }
            static inline uint32_t get_HU() { return reinterpret_cast<__IO TSTR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TSTR)->HU; }
            static inline void set_HU(uint32_t value) { reinterpret_cast<__IO TSTR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TSTR)->HU = value; }
            static inline uint32_t get_MNT() { return reinterpret_cast<__IO TSTR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TSTR)->MNT; }
            static inline void set_MNT(uint32_t value) { reinterpret_cast<__IO TSTR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TSTR)->MNT = value; }
            static inline uint32_t get_MNU() { return reinterpret_cast<__IO TSTR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TSTR)->MNU; }
            static inline void set_MNU(uint32_t value) { reinterpret_cast<__IO TSTR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TSTR)->MNU = value; }
            static inline uint32_t get_ST() { return reinterpret_cast<__IO TSTR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TSTR)->ST; }
            static inline void set_ST(uint32_t value) { reinterpret_cast<__IO TSTR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TSTR)->ST = value; }
            static inline uint32_t get_SU() { return reinterpret_cast<__IO TSTR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TSTR)->SU; }
            static inline void set_SU(uint32_t value) { reinterpret_cast<__IO TSTR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TSTR)->SU = value; }
        };
        class TSDR
        {
        private:
            union TSDR_t
            {
                struct
                {
                    uint32_t reserved0      : 13;
                    uint32_t WDU            : 3;
                    uint32_t MT             : 1;
                    uint32_t MU             : 4;
                    uint32_t DT             : 2;
                    uint32_t DU             : 4;
                    uint32_t reserved27     : 5;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                WDU                    = (0x7U << 13),
                MT                     = (0x1U << 12),
                MU                     = (0xFU << 8),
                DT                     = (0x3U << 4),
                DU                     = (0xFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TSDR; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TSDR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TSDR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TSDR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TSDR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_WDU() { return reinterpret_cast<__IO TSDR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TSDR)->WDU; }
            static inline void set_WDU(uint32_t value) { reinterpret_cast<__IO TSDR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TSDR)->WDU = value; }
            static inline uint32_t get_MU() { return reinterpret_cast<__IO TSDR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TSDR)->MU; }
            static inline void set_MU(uint32_t value) { reinterpret_cast<__IO TSDR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TSDR)->MU = value; }
            static inline uint32_t get_DT() { return reinterpret_cast<__IO TSDR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TSDR)->DT; }
            static inline void set_DT(uint32_t value) { reinterpret_cast<__IO TSDR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TSDR)->DT = value; }
            static inline uint32_t get_DU() { return reinterpret_cast<__IO TSDR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TSDR)->DU; }
            static inline void set_DU(uint32_t value) { reinterpret_cast<__IO TSDR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TSDR)->DU = value; }
        };
        class TSSSR
        {
        private:
            union TSSSR_t
            {
                struct
                {
                    uint32_t SS             : 16;
                    uint32_t reserved16     : 16;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                SS                     = (0xFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TSSSR; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TSSSR = value; }
            static inline uint32_t get_SS() { return reinterpret_cast<__IO TSSSR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TSSSR)->SS; }
            static inline void set_SS(uint32_t value) { reinterpret_cast<__IO TSSSR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TSSSR)->SS = value; }
        };
        class CALR
        {
        private:
            union CALR_t
            {
                struct
                {
                    uint32_t reserved0      : 15;
                    uint32_t CALP           : 1;
                    uint32_t CALW8          : 1;
                    uint32_t CALW16         : 1;
                    uint32_t CALM           : 9;
                    uint32_t reserved27     : 5;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                CALP                   = (0x1U << 15),
                CALW8                  = (0x1U << 14),
                CALW16                 = (0x1U << 13),
                CALM                   = (0x1FFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->CALR; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->CALR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->CALR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->CALR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->CALR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_CALM() { return reinterpret_cast<__IO CALR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->CALR)->CALM; }
            static inline void set_CALM(uint32_t value) { reinterpret_cast<__IO CALR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->CALR)->CALM = value; }
        };
        class TAFCR
        {
        private:
            union TAFCR_t
            {
                struct
                {
                    uint32_t reserved0      : 18;
                    uint32_t ALARMOUTTYPE   : 1;
                    uint32_t TSINSEL        : 1;
                    uint32_t TAMP1INSEL     : 1;
                    uint32_t TAMPPUDIS      : 1;
                    uint32_t TAMPPRCH       : 2;
                    uint32_t TAMPFLT        : 2;
                    uint32_t TAMPFREQ       : 3;
                    uint32_t TAMPTS         : 1;
                    uint32_t TAMP2TRG       : 1;
                    uint32_t TAMP2E         : 1;
                    uint32_t TAMPIE         : 1;
                    uint32_t TAMP1TRG       : 1;
                    uint32_t TAMP1E         : 1;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                ALARMOUTTYPE           = (0x1U << 18),
                TSINSEL                = (0x1U << 17),
                TAMP1INSEL             = (0x1U << 16),
                TAMPPUDIS              = (0x1U << 15),
                TAMPPRCH               = (0x3U << 13),
                TAMPFLT                = (0x3U << 11),
                TAMPFREQ               = (0x7U << 8),
                TAMPTS                 = (0x1U << 7),
                TAMP2TRG               = (0x1U << 4),
                TAMP2E                 = (0x1U << 3),
                TAMPIE                 = (0x1U << 2),
                TAMP1TRG               = (0x1U << 1),
                TAMP1E                 = (0x1U << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TAFCR; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TAFCR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TAFCR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TAFCR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TAFCR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_TAMPPRCH() { return reinterpret_cast<__IO TAFCR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TAFCR)->TAMPPRCH; }
            static inline void set_TAMPPRCH(uint32_t value) { reinterpret_cast<__IO TAFCR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TAFCR)->TAMPPRCH = value; }
            static inline uint32_t get_TAMPFLT() { return reinterpret_cast<__IO TAFCR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TAFCR)->TAMPFLT; }
            static inline void set_TAMPFLT(uint32_t value) { reinterpret_cast<__IO TAFCR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TAFCR)->TAMPFLT = value; }
            static inline uint32_t get_TAMPFREQ() { return reinterpret_cast<__IO TAFCR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TAFCR)->TAMPFREQ; }
            static inline void set_TAMPFREQ(uint32_t value) { reinterpret_cast<__IO TAFCR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->TAFCR)->TAMPFREQ = value; }
        };
        class ALRMASSR
        {
        private:
            union ALRMASSR_t
            {
                struct
                {
                    uint32_t reserved0      : 24;
                    uint32_t MASKSS         : 4;
                    uint32_t SS             : 15;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                MASKSS                 = (0xFU << 24),
                SS                     = (0x7FFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMASSR; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMASSR = value; }
            static inline uint32_t get_MASKSS() { return reinterpret_cast<__IO ALRMASSR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMASSR)->MASKSS; }
            static inline void set_MASKSS(uint32_t value) { reinterpret_cast<__IO ALRMASSR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMASSR)->MASKSS = value; }
            static inline uint32_t get_SS() { return reinterpret_cast<__IO ALRMASSR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMASSR)->SS; }
            static inline void set_SS(uint32_t value) { reinterpret_cast<__IO ALRMASSR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMASSR)->SS = value; }
        };
        class ALRMBSSR
        {
        private:
            union ALRMBSSR_t
            {
                struct
                {
                    uint32_t reserved0      : 24;
                    uint32_t MASKSS         : 4;
                    uint32_t SS             : 15;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                MASKSS                 = (0xFU << 24),
                SS                     = (0x7FFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMBSSR; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMBSSR = value; }
            static inline uint32_t get_MASKSS() { return reinterpret_cast<__IO ALRMBSSR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMBSSR)->MASKSS; }
            static inline void set_MASKSS(uint32_t value) { reinterpret_cast<__IO ALRMBSSR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMBSSR)->MASKSS = value; }
            static inline uint32_t get_SS() { return reinterpret_cast<__IO ALRMBSSR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMBSSR)->SS; }
            static inline void set_SS(uint32_t value) { reinterpret_cast<__IO ALRMBSSR_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->ALRMBSSR)->SS = value; }
        };
        class BKP0R
        {
        private:
            union BKP0R_t
            {
                struct
                {
                    uint32_t DATA           : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DATA                   = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP0R; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP0R = value; }
            static inline uint32_t get_DATA() { return reinterpret_cast<__IO BKP0R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP0R)->DATA; }
            static inline void set_DATA(uint32_t value) { reinterpret_cast<__IO BKP0R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP0R)->DATA = value; }
        };
        class BKP1R
        {
        private:
            union BKP1R_t
            {
                struct
                {
                    uint32_t DATA           : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DATA                   = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP1R; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP1R = value; }
            static inline uint32_t get_DATA() { return reinterpret_cast<__IO BKP1R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP1R)->DATA; }
            static inline void set_DATA(uint32_t value) { reinterpret_cast<__IO BKP1R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP1R)->DATA = value; }
        };
        class BKP2R
        {
        private:
            union BKP2R_t
            {
                struct
                {
                    uint32_t DATA           : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DATA                   = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP2R; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP2R = value; }
            static inline uint32_t get_DATA() { return reinterpret_cast<__IO BKP2R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP2R)->DATA; }
            static inline void set_DATA(uint32_t value) { reinterpret_cast<__IO BKP2R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP2R)->DATA = value; }
        };
        class BKP3R
        {
        private:
            union BKP3R_t
            {
                struct
                {
                    uint32_t DATA           : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DATA                   = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP3R; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP3R = value; }
            static inline uint32_t get_DATA() { return reinterpret_cast<__IO BKP3R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP3R)->DATA; }
            static inline void set_DATA(uint32_t value) { reinterpret_cast<__IO BKP3R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP3R)->DATA = value; }
        };
        class BKP4R
        {
        private:
            union BKP4R_t
            {
                struct
                {
                    uint32_t DATA           : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DATA                   = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP4R; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP4R = value; }
            static inline uint32_t get_DATA() { return reinterpret_cast<__IO BKP4R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP4R)->DATA; }
            static inline void set_DATA(uint32_t value) { reinterpret_cast<__IO BKP4R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP4R)->DATA = value; }
        };
        class BKP5R
        {
        private:
            union BKP5R_t
            {
                struct
                {
                    uint32_t DATA           : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DATA                   = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP5R; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP5R = value; }
            static inline uint32_t get_DATA() { return reinterpret_cast<__IO BKP5R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP5R)->DATA; }
            static inline void set_DATA(uint32_t value) { reinterpret_cast<__IO BKP5R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP5R)->DATA = value; }
        };
        class BKP6R
        {
        private:
            union BKP6R_t
            {
                struct
                {
                    uint32_t DATA           : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DATA                   = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP6R; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP6R = value; }
            static inline uint32_t get_DATA() { return reinterpret_cast<__IO BKP6R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP6R)->DATA; }
            static inline void set_DATA(uint32_t value) { reinterpret_cast<__IO BKP6R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP6R)->DATA = value; }
        };
        class BKP7R
        {
        private:
            union BKP7R_t
            {
                struct
                {
                    uint32_t DATA           : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DATA                   = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP7R; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP7R = value; }
            static inline uint32_t get_DATA() { return reinterpret_cast<__IO BKP7R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP7R)->DATA; }
            static inline void set_DATA(uint32_t value) { reinterpret_cast<__IO BKP7R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP7R)->DATA = value; }
        };
        class BKP8R
        {
        private:
            union BKP8R_t
            {
                struct
                {
                    uint32_t DATA           : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DATA                   = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP8R; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP8R = value; }
            static inline uint32_t get_DATA() { return reinterpret_cast<__IO BKP8R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP8R)->DATA; }
            static inline void set_DATA(uint32_t value) { reinterpret_cast<__IO BKP8R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP8R)->DATA = value; }
        };
        class BKP9R
        {
        private:
            union BKP9R_t
            {
                struct
                {
                    uint32_t DATA           : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DATA                   = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP9R; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP9R = value; }
            static inline uint32_t get_DATA() { return reinterpret_cast<__IO BKP9R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP9R)->DATA; }
            static inline void set_DATA(uint32_t value) { reinterpret_cast<__IO BKP9R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP9R)->DATA = value; }
        };
        class BKP10R
        {
        private:
            union BKP10R_t
            {
                struct
                {
                    uint32_t DATA           : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DATA                   = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP10R; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP10R = value; }
            static inline uint32_t get_DATA() { return reinterpret_cast<__IO BKP10R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP10R)->DATA; }
            static inline void set_DATA(uint32_t value) { reinterpret_cast<__IO BKP10R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP10R)->DATA = value; }
        };
        class BKP11R
        {
        private:
            union BKP11R_t
            {
                struct
                {
                    uint32_t DATA           : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DATA                   = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP11R; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP11R = value; }
            static inline uint32_t get_DATA() { return reinterpret_cast<__IO BKP11R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP11R)->DATA; }
            static inline void set_DATA(uint32_t value) { reinterpret_cast<__IO BKP11R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP11R)->DATA = value; }
        };
        class BKP12R
        {
        private:
            union BKP12R_t
            {
                struct
                {
                    uint32_t DATA           : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DATA                   = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP12R; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP12R = value; }
            static inline uint32_t get_DATA() { return reinterpret_cast<__IO BKP12R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP12R)->DATA; }
            static inline void set_DATA(uint32_t value) { reinterpret_cast<__IO BKP12R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP12R)->DATA = value; }
        };
        class BKP13R
        {
        private:
            union BKP13R_t
            {
                struct
                {
                    uint32_t DATA           : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DATA                   = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP13R; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP13R = value; }
            static inline uint32_t get_DATA() { return reinterpret_cast<__IO BKP13R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP13R)->DATA; }
            static inline void set_DATA(uint32_t value) { reinterpret_cast<__IO BKP13R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP13R)->DATA = value; }
        };
        class BKP14R
        {
        private:
            union BKP14R_t
            {
                struct
                {
                    uint32_t DATA           : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DATA                   = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP14R; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP14R = value; }
            static inline uint32_t get_DATA() { return reinterpret_cast<__IO BKP14R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP14R)->DATA; }
            static inline void set_DATA(uint32_t value) { reinterpret_cast<__IO BKP14R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP14R)->DATA = value; }
        };
        class BKP15R
        {
        private:
            union BKP15R_t
            {
                struct
                {
                    uint32_t DATA           : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DATA                   = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP15R; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP15R = value; }
            static inline uint32_t get_DATA() { return reinterpret_cast<__IO BKP15R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP15R)->DATA; }
            static inline void set_DATA(uint32_t value) { reinterpret_cast<__IO BKP15R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP15R)->DATA = value; }
        };
        class BKP16R
        {
        private:
            union BKP16R_t
            {
                struct
                {
                    uint32_t DATA           : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DATA                   = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP16R; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP16R = value; }
            static inline uint32_t get_DATA() { return reinterpret_cast<__IO BKP16R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP16R)->DATA; }
            static inline void set_DATA(uint32_t value) { reinterpret_cast<__IO BKP16R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP16R)->DATA = value; }
        };
        class BKP17R
        {
        private:
            union BKP17R_t
            {
                struct
                {
                    uint32_t DATA           : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DATA                   = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP17R; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP17R = value; }
            static inline uint32_t get_DATA() { return reinterpret_cast<__IO BKP17R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP17R)->DATA; }
            static inline void set_DATA(uint32_t value) { reinterpret_cast<__IO BKP17R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP17R)->DATA = value; }
        };
        class BKP18R
        {
        private:
            union BKP18R_t
            {
                struct
                {
                    uint32_t DATA           : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DATA                   = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP18R; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP18R = value; }
            static inline uint32_t get_DATA() { return reinterpret_cast<__IO BKP18R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP18R)->DATA; }
            static inline void set_DATA(uint32_t value) { reinterpret_cast<__IO BKP18R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP18R)->DATA = value; }
        };
        class BKP19R
        {
        private:
            union BKP19R_t
            {
                struct
                {
                    uint32_t DATA           : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DATA                   = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP19R; }
            static inline void set(uint32_t value) { reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP19R = value; }
            static inline uint32_t get_DATA() { return reinterpret_cast<__IO BKP19R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP19R)->DATA; }
            static inline void set_DATA(uint32_t value) { reinterpret_cast<__IO BKP19R_t*>(&reinterpret_cast<RTC_t*>(STM32::RTC_BASE)->BKP19R)->DATA = value; }
        };
    };
    /* SDIO DEFINITION */
    class SDIO
    {
    private:
        struct SDIO_t
        {
            __IO uint32_t                 POWER;
            __IO uint32_t                 CLKCR;
            __IO uint32_t                 ARG;
            __IO uint32_t                 CMD;
            const uint32_t                RESPCMD;
            const uint32_t                RESP1;
            const uint32_t                RESP2;
            const uint32_t                RESP3;
            const uint32_t                RESP4;
            __IO uint32_t                 DTIMER;
            __IO uint32_t                 DLEN;
            __IO uint32_t                 DCTRL;
            const uint32_t                DCOUNT;
            const uint32_t                STA;
            __IO uint32_t                 ICR;
            __IO uint32_t                 MASK;
            uint32_t                      RESERVED0[2];
            const uint32_t                FIFOCNT;
            uint32_t                      RESERVED1[13];
            __IO uint32_t                 FIFO;
        };
    public:
        class POWER
        {
        private:
            union POWER_t
            {
                struct
                {
                    uint32_t PWRCTRL        : 2;
                    uint32_t reserved2      : 30;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                PWRCTRL                = (0x3U << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->POWER; }
            static inline void set(uint32_t value) { reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->POWER = value; }
            static inline uint32_t get_PWRCTRL() { return reinterpret_cast<__IO POWER_t*>(&reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->POWER)->PWRCTRL; }
            static inline void set_PWRCTRL(uint32_t value) { reinterpret_cast<__IO POWER_t*>(&reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->POWER)->PWRCTRL = value; }
        };
        class CLKCR
        {
        private:
            union CLKCR_t
            {
                struct
                {
                    uint32_t CLKDIV         : 8;
                    uint32_t CLKEN          : 1;
                    uint32_t PWRSAV         : 1;
                    uint32_t BYPASS         : 1;
                    uint32_t WIDBUS         : 2;
                    uint32_t NEGEDGE        : 1;
                    uint32_t HWFC_EN        : 1;
                    uint32_t reserved15     : 17;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                CLKDIV                 = (0xFFU << 0),
                CLKEN                  = (0x1U << 8),
                PWRSAV                 = (0x1U << 9),
                BYPASS                 = (0x1U << 10),
                WIDBUS                 = (0x3U << 11),
                NEGEDGE                = (0x1U << 13),
                HWFC_EN                = (0x1U << 14),
            };
            static inline uint32_t get() { return reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->CLKCR; }
            static inline void set(uint32_t value) { reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->CLKCR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->CLKCR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->CLKCR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->CLKCR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_CLKDIV() { return reinterpret_cast<__IO CLKCR_t*>(&reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->CLKCR)->CLKDIV; }
            static inline void set_CLKDIV(uint32_t value) { reinterpret_cast<__IO CLKCR_t*>(&reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->CLKCR)->CLKDIV = value; }
            static inline uint32_t get_WIDBUS() { return reinterpret_cast<__IO CLKCR_t*>(&reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->CLKCR)->WIDBUS; }
            static inline void set_WIDBUS(uint32_t value) { reinterpret_cast<__IO CLKCR_t*>(&reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->CLKCR)->WIDBUS = value; }
        };
        class ARG
        {
        private:
            union ARG_t
            {
                struct
                {
                    uint32_t CMDARG         : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                CMDARG                 = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->ARG; }
            static inline void set(uint32_t value) { reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->ARG = value; }
            static inline uint32_t get_CMDARG() { return reinterpret_cast<__IO ARG_t*>(&reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->ARG)->CMDARG; }
            static inline void set_CMDARG(uint32_t value) { reinterpret_cast<__IO ARG_t*>(&reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->ARG)->CMDARG = value; }
        };
        class CMD
        {
        private:
            union CMD_t
            {
                struct
                {
                    uint32_t CMDINDEX       : 6;
                    uint32_t WAITRESP       : 2;
                    uint32_t WAITINT        : 1;
                    uint32_t WAITPEND       : 1;
                    uint32_t CPSMEN         : 1;
                    uint32_t SDIOSUSPEND    : 1;
                    uint32_t ENCMDCOMPL     : 1;
                    uint32_t NIEN           : 1;
                    uint32_t CEATACMD       : 1;
                    uint32_t reserved15     : 17;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                CMDINDEX               = (0x3FU << 0),
                WAITRESP               = (0x3U << 6),
                WAITINT                = (0x1U << 8),
                WAITPEND               = (0x1U << 9),
                CPSMEN                 = (0x1U << 10),
                SDIOSUSPEND            = (0x1U << 11),
                ENCMDCOMPL             = (0x1U << 12),
                NIEN                   = (0x1U << 13),
                CEATACMD               = (0x1U << 14),
            };
            static inline uint32_t get() { return reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->CMD; }
            static inline void set(uint32_t value) { reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->CMD = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->CMD |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->CMD &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->CMD & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_CMDINDEX() { return reinterpret_cast<__IO CMD_t*>(&reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->CMD)->CMDINDEX; }
            static inline void set_CMDINDEX(uint32_t value) { reinterpret_cast<__IO CMD_t*>(&reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->CMD)->CMDINDEX = value; }
            static inline uint32_t get_WAITRESP() { return reinterpret_cast<__IO CMD_t*>(&reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->CMD)->WAITRESP; }
            static inline void set_WAITRESP(uint32_t value) { reinterpret_cast<__IO CMD_t*>(&reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->CMD)->WAITRESP = value; }
        };
        class RESPCMD
        {
        private:
            union RESPCMD_t
            {
                struct
                {
                    uint32_t RESPCMD        : 6;
                    uint32_t CARDSTATUS0    : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                RESPCMD                = (0x3FU << 0),
                CARDSTATUS0            = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->RESPCMD; }
            static inline uint32_t get_RESPCMD() { return reinterpret_cast<const RESPCMD_t*>(&reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->RESPCMD)->RESPCMD; }
            static inline uint32_t get_CARDSTATUS0() { return reinterpret_cast<const RESPCMD_t*>(&reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->RESPCMD)->CARDSTATUS0; }
        };
        class RESP1
        {
        private:
            union RESP1_t
            {
                struct
                {
                    uint32_t CARDSTATUS1    : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                CARDSTATUS1            = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->RESP1; }
            static inline uint32_t get_CARDSTATUS1() { return reinterpret_cast<const RESP1_t*>(&reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->RESP1)->CARDSTATUS1; }
        };
        class RESP2
        {
        private:
            union RESP2_t
            {
                struct
                {
                    uint32_t CARDSTATUS2    : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                CARDSTATUS2            = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->RESP2; }
            static inline uint32_t get_CARDSTATUS2() { return reinterpret_cast<const RESP2_t*>(&reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->RESP2)->CARDSTATUS2; }
        };
        class RESP3
        {
        private:
            union RESP3_t
            {
                struct
                {
                    uint32_t CARDSTATUS3    : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                CARDSTATUS3            = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->RESP3; }
            static inline uint32_t get_CARDSTATUS3() { return reinterpret_cast<const RESP3_t*>(&reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->RESP3)->CARDSTATUS3; }
        };
        class RESP4
        {
        private:
            union RESP4_t
            {
                struct
                {
                    uint32_t CARDSTATUS4    : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                CARDSTATUS4            = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->RESP4; }
            static inline uint32_t get_CARDSTATUS4() { return reinterpret_cast<const RESP4_t*>(&reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->RESP4)->CARDSTATUS4; }
        };
        class DTIMER
        {
        private:
            union DTIMER_t
            {
                struct
                {
                    uint32_t DATATIME       : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DATATIME               = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->DTIMER; }
            static inline void set(uint32_t value) { reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->DTIMER = value; }
            static inline uint32_t get_DATATIME() { return reinterpret_cast<__IO DTIMER_t*>(&reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->DTIMER)->DATATIME; }
            static inline void set_DATATIME(uint32_t value) { reinterpret_cast<__IO DTIMER_t*>(&reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->DTIMER)->DATATIME = value; }
        };
        class DLEN
        {
        private:
            union DLEN_t
            {
                struct
                {
                    uint32_t DATALENGTH     : 25;
                    uint32_t reserved25     : 7;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DATALENGTH             = (0x1FFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->DLEN; }
            static inline void set(uint32_t value) { reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->DLEN = value; }
            static inline uint32_t get_DATALENGTH() { return reinterpret_cast<__IO DLEN_t*>(&reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->DLEN)->DATALENGTH; }
            static inline void set_DATALENGTH(uint32_t value) { reinterpret_cast<__IO DLEN_t*>(&reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->DLEN)->DATALENGTH = value; }
        };
        class DCTRL
        {
        private:
            union DCTRL_t
            {
                struct
                {
                    uint32_t DTEN           : 1;
                    uint32_t DTDIR          : 1;
                    uint32_t DTMODE         : 1;
                    uint32_t DMAEN          : 1;
                    uint32_t DBLOCKSIZE     : 4;
                    uint32_t RWSTART        : 1;
                    uint32_t RWSTOP         : 1;
                    uint32_t RWMOD          : 1;
                    uint32_t SDIOEN         : 1;
                    uint32_t reserved12     : 20;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DTEN                   = (0x1U << 0),
                DTDIR                  = (0x1U << 1),
                DTMODE                 = (0x1U << 2),
                DMAEN                  = (0x1U << 3),
                DBLOCKSIZE             = (0xFU << 4),
                RWSTART                = (0x1U << 8),
                RWSTOP                 = (0x1U << 9),
                RWMOD                  = (0x1U << 10),
                SDIOEN                 = (0x1U << 11),
            };
            static inline uint32_t get() { return reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->DCTRL; }
            static inline void set(uint32_t value) { reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->DCTRL = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->DCTRL |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->DCTRL &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->DCTRL & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_DBLOCKSIZE() { return reinterpret_cast<__IO DCTRL_t*>(&reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->DCTRL)->DBLOCKSIZE; }
            static inline void set_DBLOCKSIZE(uint32_t value) { reinterpret_cast<__IO DCTRL_t*>(&reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->DCTRL)->DBLOCKSIZE = value; }
        };
        class DCOUNT
        {
        private:
            union DCOUNT_t
            {
                struct
                {
                    uint32_t DATACOUNT      : 25;
                    uint32_t reserved25     : 7;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DATACOUNT              = (0x1FFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->DCOUNT; }
            static inline uint32_t get_DATACOUNT() { return reinterpret_cast<const DCOUNT_t*>(&reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->DCOUNT)->DATACOUNT; }
        };
        class STA
        {
        private:
            union STA_t
            {
                struct
                {
                    uint32_t CCRCFAIL       : 1;
                    uint32_t DCRCFAIL       : 1;
                    uint32_t CTIMEOUT       : 1;
                    uint32_t DTIMEOUT       : 1;
                    uint32_t TXUNDERR       : 1;
                    uint32_t RXOVERR        : 1;
                    uint32_t CMDREND        : 1;
                    uint32_t CMDSENT        : 1;
                    uint32_t DATAEND        : 1;
                    uint32_t STBITERR       : 1;
                    uint32_t DBCKEND        : 1;
                    uint32_t CMDACT         : 1;
                    uint32_t TXACT          : 1;
                    uint32_t RXACT          : 1;
                    uint32_t TXFIFOHE       : 1;
                    uint32_t RXFIFOHF       : 1;
                    uint32_t TXFIFOF        : 1;
                    uint32_t RXFIFOF        : 1;
                    uint32_t TXFIFOE        : 1;
                    uint32_t RXFIFOE        : 1;
                    uint32_t TXDAVL         : 1;
                    uint32_t RXDAVL         : 1;
                    uint32_t SDIOIT         : 1;
                    uint32_t CEATAEND       : 1;
                    uint32_t reserved24     : 8;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                CCRCFAIL               = (0x1U << 0),
                DCRCFAIL               = (0x1U << 1),
                CTIMEOUT               = (0x1U << 2),
                DTIMEOUT               = (0x1U << 3),
                TXUNDERR               = (0x1U << 4),
                RXOVERR                = (0x1U << 5),
                CMDREND                = (0x1U << 6),
                CMDSENT                = (0x1U << 7),
                DATAEND                = (0x1U << 8),
                STBITERR               = (0x1U << 9),
                DBCKEND                = (0x1U << 10),
                CMDACT                 = (0x1U << 11),
                TXACT                  = (0x1U << 12),
                RXACT                  = (0x1U << 13),
                TXFIFOHE               = (0x1U << 14),
                RXFIFOHF               = (0x1U << 15),
                TXFIFOF                = (0x1U << 16),
                RXFIFOF                = (0x1U << 17),
                TXFIFOE                = (0x1U << 18),
                RXFIFOE                = (0x1U << 19),
                TXDAVL                 = (0x1U << 20),
                RXDAVL                 = (0x1U << 21),
                SDIOIT                 = (0x1U << 22),
                CEATAEND               = (0x1U << 23),
            };
            static inline uint32_t get() { return reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->STA; }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->STA & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class ICR
        {
        private:
            union ICR_t
            {
                struct
                {
                    uint32_t CCRCFAILC      : 1;
                    uint32_t DCRCFAILC      : 1;
                    uint32_t CTIMEOUTC      : 1;
                    uint32_t DTIMEOUTC      : 1;
                    uint32_t TXUNDERRC      : 1;
                    uint32_t RXOVERRC       : 1;
                    uint32_t CMDRENDC       : 1;
                    uint32_t CMDSENTC       : 1;
                    uint32_t DATAENDC       : 1;
                    uint32_t STBITERRC      : 1;
                    uint32_t DBCKENDC       : 1;
                    uint32_t reserved11     : 11;
                    uint32_t SDIOITC        : 1;
                    uint32_t CEATAENDC      : 1;
                    uint32_t reserved24     : 8;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                CCRCFAILC              = (0x1U << 0),
                DCRCFAILC              = (0x1U << 1),
                CTIMEOUTC              = (0x1U << 2),
                DTIMEOUTC              = (0x1U << 3),
                TXUNDERRC              = (0x1U << 4),
                RXOVERRC               = (0x1U << 5),
                CMDRENDC               = (0x1U << 6),
                CMDSENTC               = (0x1U << 7),
                DATAENDC               = (0x1U << 8),
                STBITERRC              = (0x1U << 9),
                DBCKENDC               = (0x1U << 10),
                SDIOITC                = (0x1U << 22),
                CEATAENDC              = (0x1U << 23),
            };
            static inline uint32_t get() { return reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->ICR; }
            static inline void set(uint32_t value) { reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->ICR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->ICR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->ICR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->ICR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class MASK
        {
        private:
            union MASK_t
            {
                struct
                {
                    uint32_t CCRCFAILIE     : 1;
                    uint32_t DCRCFAILIE     : 1;
                    uint32_t CTIMEOUTIE     : 1;
                    uint32_t DTIMEOUTIE     : 1;
                    uint32_t TXUNDERRIE     : 1;
                    uint32_t RXOVERRIE      : 1;
                    uint32_t CMDRENDIE      : 1;
                    uint32_t CMDSENTIE      : 1;
                    uint32_t DATAENDIE      : 1;
                    uint32_t STBITERRIE     : 1;
                    uint32_t DBCKENDIE      : 1;
                    uint32_t CMDACTIE       : 1;
                    uint32_t TXACTIE        : 1;
                    uint32_t RXACTIE        : 1;
                    uint32_t TXFIFOHEIE     : 1;
                    uint32_t RXFIFOHFIE     : 1;
                    uint32_t TXFIFOFIE      : 1;
                    uint32_t RXFIFOFIE      : 1;
                    uint32_t TXFIFOEIE      : 1;
                    uint32_t RXFIFOEIE      : 1;
                    uint32_t TXDAVLIE       : 1;
                    uint32_t RXDAVLIE       : 1;
                    uint32_t SDIOITIE       : 1;
                    uint32_t CEATAENDIE     : 1;
                    uint32_t reserved24     : 8;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                CCRCFAILIE             = (0x1U << 0),
                DCRCFAILIE             = (0x1U << 1),
                CTIMEOUTIE             = (0x1U << 2),
                DTIMEOUTIE             = (0x1U << 3),
                TXUNDERRIE             = (0x1U << 4),
                RXOVERRIE              = (0x1U << 5),
                CMDRENDIE              = (0x1U << 6),
                CMDSENTIE              = (0x1U << 7),
                DATAENDIE              = (0x1U << 8),
                STBITERRIE             = (0x1U << 9),
                DBCKENDIE              = (0x1U << 10),
                CMDACTIE               = (0x1U << 11),
                TXACTIE                = (0x1U << 12),
                RXACTIE                = (0x1U << 13),
                TXFIFOHEIE             = (0x1U << 14),
                RXFIFOHFIE             = (0x1U << 15),
                TXFIFOFIE              = (0x1U << 16),
                RXFIFOFIE              = (0x1U << 17),
                TXFIFOEIE              = (0x1U << 18),
                RXFIFOEIE              = (0x1U << 19),
                TXDAVLIE               = (0x1U << 20),
                RXDAVLIE               = (0x1U << 21),
                SDIOITIE               = (0x1U << 22),
                CEATAENDIE             = (0x1U << 23),
            };
            static inline uint32_t get() { return reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->MASK; }
            static inline void set(uint32_t value) { reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->MASK = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->MASK |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->MASK &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->MASK & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class FIFOCNT
        {
        private:
            union FIFOCNT_t
            {
                struct
                {
                    uint32_t FIFOCOUNT      : 24;
                    uint32_t reserved24     : 8;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                FIFOCOUNT              = (0xFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->FIFOCNT; }
            static inline uint32_t get_FIFOCOUNT() { return reinterpret_cast<const FIFOCNT_t*>(&reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->FIFOCNT)->FIFOCOUNT; }
        };
        class FIFO
        {
        private:
            union FIFO_t
            {
                struct
                {
                    uint32_t FIFODATA       : 32;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                FIFODATA               = (0xFFFFFFFFU << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->FIFO; }
            static inline void set(uint32_t value) { reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->FIFO = value; }
            static inline uint32_t get_FIFODATA() { return reinterpret_cast<__IO FIFO_t*>(&reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->FIFO)->FIFODATA; }
            static inline void set_FIFODATA(uint32_t value) { reinterpret_cast<__IO FIFO_t*>(&reinterpret_cast<SDIO_t*>(STM32::SDIO_BASE)->FIFO)->FIFODATA = value; }
        };
    };
    /* SPI DEFINITION */
    template <uint32_t reg_base>
    class SPI
    {
    };
    /* TIM DEFINITION */
    template <uint32_t reg_base>
    class TIM
    {
    };
    /* USART DEFINITION */
    template <uint32_t reg_base>
    class USART
    {
    };
    /* WWDG DEFINITION */
    class WWDG
    {
    private:
        struct WWDG_t
        {
            __IO uint32_t                 CR;
            __IO uint32_t                 CFR;
            __IO uint32_t                 SR;
        };
    public:
        class CR
        {
        private:
            union CR_t
            {
                struct
                {
                    uint32_t T              : 7;
                    uint32_t WDGA           : 1;
                    uint32_t reserved8      : 24;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                T                      = (0x7FU << 0),
                WDGA                   = (0x1U << 7),
            };
            static inline uint32_t get() { return reinterpret_cast<WWDG_t*>(STM32::WWDG_BASE)->CR; }
            static inline void set(uint32_t value) { reinterpret_cast<WWDG_t*>(STM32::WWDG_BASE)->CR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<WWDG_t*>(STM32::WWDG_BASE)->CR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<WWDG_t*>(STM32::WWDG_BASE)->CR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<WWDG_t*>(STM32::WWDG_BASE)->CR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_T() { return reinterpret_cast<__IO CR_t*>(&reinterpret_cast<WWDG_t*>(STM32::WWDG_BASE)->CR)->T; }
            static inline void set_T(uint32_t value) { reinterpret_cast<__IO CR_t*>(&reinterpret_cast<WWDG_t*>(STM32::WWDG_BASE)->CR)->T = value; }
        };
        class CFR
        {
        private:
            union CFR_t
            {
                struct
                {
                    uint32_t W              : 7;
                    uint32_t WDGTB          : 2;
                    uint32_t EWI            : 1;
                    uint32_t reserved10     : 22;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                W                      = (0x7FU << 0),
                WDGTB                  = (0x3U << 7),
                EWI                    = (0x1U << 9),
            };
            static inline uint32_t get() { return reinterpret_cast<WWDG_t*>(STM32::WWDG_BASE)->CFR; }
            static inline void set(uint32_t value) { reinterpret_cast<WWDG_t*>(STM32::WWDG_BASE)->CFR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<WWDG_t*>(STM32::WWDG_BASE)->CFR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<WWDG_t*>(STM32::WWDG_BASE)->CFR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<WWDG_t*>(STM32::WWDG_BASE)->CFR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
            static inline uint32_t get_W() { return reinterpret_cast<__IO CFR_t*>(&reinterpret_cast<WWDG_t*>(STM32::WWDG_BASE)->CFR)->W; }
            static inline void set_W(uint32_t value) { reinterpret_cast<__IO CFR_t*>(&reinterpret_cast<WWDG_t*>(STM32::WWDG_BASE)->CFR)->W = value; }
            static inline uint32_t get_WDGTB() { return reinterpret_cast<__IO CFR_t*>(&reinterpret_cast<WWDG_t*>(STM32::WWDG_BASE)->CFR)->WDGTB; }
            static inline void set_WDGTB(uint32_t value) { reinterpret_cast<__IO CFR_t*>(&reinterpret_cast<WWDG_t*>(STM32::WWDG_BASE)->CFR)->WDGTB = value; }
        };
        class SR
        {
        private:
            union SR_t
            {
                struct
                {
                    uint32_t EWIF           : 1;
                    uint32_t reserved1      : 31;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                EWIF                   = (0x1U << 0),
            };
            static inline uint32_t get() { return reinterpret_cast<WWDG_t*>(STM32::WWDG_BASE)->SR; }
            static inline void set(uint32_t value) { reinterpret_cast<WWDG_t*>(STM32::WWDG_BASE)->SR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<WWDG_t*>(STM32::WWDG_BASE)->SR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<WWDG_t*>(STM32::WWDG_BASE)->SR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<WWDG_t*>(STM32::WWDG_BASE)->SR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
    };
    /* RNG DEFINITION */
    class RNG
    {
    private:
        struct RNG_t
        {
            __IO uint32_t                 CR;
            __IO uint32_t                 SR;
            __IO uint32_t                 DR;
        };
    public:
        class CR
        {
        private:
            union CR_t
            {
                struct
                {
                    uint32_t reserved0      : 2;
                    uint32_t RNGEN          : 1;
                    uint32_t IE             : 1;
                    uint32_t reserved4      : 28;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                RNGEN                  = (0x1U << 2),
                IE                     = (0x1U << 3),
            };
            static inline uint32_t get() { return reinterpret_cast<RNG_t*>(STM32::RNG_BASE)->CR; }
            static inline void set(uint32_t value) { reinterpret_cast<RNG_t*>(STM32::RNG_BASE)->CR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<RNG_t*>(STM32::RNG_BASE)->CR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<RNG_t*>(STM32::RNG_BASE)->CR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<RNG_t*>(STM32::RNG_BASE)->CR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class SR
        {
        private:
            union SR_t
            {
                struct
                {
                    uint32_t DRDY           : 1;
                    uint32_t CECS           : 1;
                    uint32_t SECS           : 1;
                    uint32_t reserved3      : 2;
                    uint32_t CEIS           : 1;
                    uint32_t SEIS           : 1;
                    uint32_t reserved7      : 25;
                };
                uint32_t RAW;
            };
        public:
            enum class EMasks: uint32_t
            {
                DRDY                   = (0x1U << 0),
                CECS                   = (0x1U << 1),
                SECS                   = (0x1U << 2),
                CEIS                   = (0x1U << 5),
                SEIS                   = (0x1U << 6),
            };
            static inline uint32_t get() { return reinterpret_cast<RNG_t*>(STM32::RNG_BASE)->SR; }
            static inline void set(uint32_t value) { reinterpret_cast<RNG_t*>(STM32::RNG_BASE)->SR = value; }
            template <EMasks ... flags>
            static inline void set_flags()
            {
                reinterpret_cast<RNG_t*>(STM32::RNG_BASE)->SR |= SetBits<(std::uint32_t)flags...>();
            }
            template <EMasks ... flags>
            static inline void clear_flags()
            {
                reinterpret_cast<RNG_t*>(STM32::RNG_BASE)->SR &= ~(SetBits<(std::uint32_t)flags...>());
            }
            template <EMasks ... flags>
            static inline bool get_flags()
            {
                return ((reinterpret_cast<RNG_t*>(STM32::RNG_BASE)->SR & SetBits<(std::uint32_t)flags...>()) == SetBits<(std::uint32_t)flags...>());
            }
        };
        class DR
        {
        private:
            union DR_t
            {
                struct
                {
                    uint32_t reserved0      : 32;
                };
                uint32_t RAW;
            };
        public:
            static inline uint32_t get() { return reinterpret_cast<RNG_t*>(STM32::RNG_BASE)->DR; }
            static inline void set(uint32_t value) { reinterpret_cast<RNG_t*>(STM32::RNG_BASE)->DR = value; }
        };
    };
    /* USB_OTG_Global DEFINITION */
    template <uint32_t reg_base>
    class USB_OTG_Global
    {
    };
    /* USB_OTG_Device DEFINITION */
    template <uint32_t reg_base>
    class USB_OTG_Device
    {
    };
    /* USB_OTG_INEndpoint DEFINITION */
    template <uint32_t reg_base>
    class USB_OTG_INEndpoint
    {
    };
    /* USB_OTG_OUTEndpoint DEFINITION */
    template <uint32_t reg_base>
    class USB_OTG_OUTEndpoint
    {
    };
    /* USB_OTG_Host DEFINITION */
    template <uint32_t reg_base>
    class USB_OTG_Host
    {
    };
    /* USB_OTG_HostChannel DEFINITION */
    template <uint32_t reg_base>
    class USB_OTG_HostChannel
    {
    };
}

#endif /* __STM32F407xx_H */

