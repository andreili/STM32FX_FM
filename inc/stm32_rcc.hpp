#ifndef __STM32_RCC__
#define __STM32_RCC__

/*
 * Based on HAL v1.21.0(F4), v1.6.1(F1)
 * */

#include <stm32_inc.h>

#define RCC_CIR_OFFSET                   0x0c

namespace STM32
{

class RCC
{
public:
    enum class EFlag: uint8_t
    {
        MASK                    = 0x1FU,
        /* Flags in the CR register */
        HSIRDY                  = 0x21U,
        HSERDY                  = 0x31U,
        PLLRDY                  = 0x39U,
        PLLI2SRDY               = 0x3BU,
        /* Flags in the BDCR register */
        LSERDY                  = 0x41U,
        /* Flags in the CSR register */
        LSIRDY                  = 0x61U,
        BORRST                  = 0x79U,
        PINRST                  = 0x7AU,
        PORRST                  = 0x7BU,
        SFTRST                  = 0x7CU,
        IWDGRST                 = 0x7DU,
        WWDGRST                 = 0x7EU,
        LPWRRST                 = 0x7FU,
    };

    enum class EHSEState: uint8_t
    {
        ON,
        BYPASS,
        OFF,
    };

    enum class ELSEState: uint8_t
    {
        ON,
        BYPASS,
        OFF,
    };

    enum class EIT: uint32_t
    {
        LSIRDY                  = 0x01U,
        LSERDY                  = 0x02U,
        HSIRDY                  = 0x04U,
        HSERDY                  = 0x08U,
        PLLRDY                  = 0x10U,
        PLLI2SRDY               = 0x20U,
        CSS                     = 0x80U,
    };

    enum class EPLL: uint8_t
    {
        NONE,
        OFF,
        ON,
    };

    enum class EPLLP: uint32_t
    {
        DIV2                    = 0x0,
        DIV4                    = 0x1,
        DIV6                    = 0x2,
        DIV8                    = 0x3,
    };

    enum class EPLLSource: uint32_t
    {
        HSI = 0x0,
        HSE = 0x1,
    };

    enum EClockType: uint32_t
    {
        SYSCLK                  = 0x00000001U,
        HCLK                    = 0x00000002U,
        PCLK1                   = 0x00000004U,
        PCLK2                   = 0x00000008U,
    };

    enum class EAHBDivider: uint32_t
    {
        _1   = 0x0,
        _2   = 0x8,
        _4   = 0x9,
        _8   = 0xA,
        _16  = 0xB,
        _32  = 0xC,
        _64  = 0xD,
        _128 = 0xE,
        _256 = 0xF,
    };

    enum class EAPBDivider: uint32_t
    {
        _1   = 0x0,
        _2   = 0x4,
        _4   = 0x5,
        _8   = 0x6,
        _16  = 0x7,
    };

    enum class EMCODivider: uint32_t
    {
        _1   = 0x0,
        _2   = 0x4,
        _3   = 0x5,
        _4   = 0x6,
        _5   = 0x7,
    };

    enum class EMCO1Source: uint32_t
    {
        HSI  = 0x0,
        LSE  = 0x1,
        HSE  = 0x2,
        PLL  = 0x3,
    };

    enum class EMCO2Source: uint32_t
    {
        SYSCLK  = 0x0,
        PLLI2S  = 0x1,
        HSE     = 0x2,
        PLL     = 0x3,
    };

    enum class ESystemClock: uint32_t
    {
        HSI  = 0x0,
        HSE  = 0x1,
        PLL  = 0x2,
        NA   = 0x3,
    };

    enum class EI2SSource: uint32_t
    {
        PLLI2S   = 0x0,
        I2S_CKIN = 0x1,
    };

    enum class EPeriphHCLK: uint32_t
    {
    #if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx)
        I2S        = 0x01,
        SAI_PLLI2S = 0x02,
        SAI_PLLSAI = 0x04,
        LTDC       = 0x08,
        TIM        = 0x10,
        RTC        = 0x20,
        PLLI2S     = 0x40,
    #endif
    #if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx)|| defined(STM32F417xx) ||\
        defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F411xE)
        I2S        = 0x01,
        RTC        = 0x02,
        PLLI2S     = 0x04,
    #endif /* STM32F405xx || STM32F415xx || STM32F407xx || STM32F417xx || STM32F401xC || STM32F401xE || STM32F411xE */
    #if defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F411xE)
        RTC        = 0x08,
    #endif
    };
    friend EPeriphHCLK operator&(const EPeriphHCLK v1, const EPeriphHCLK v2)
    {
        return EPeriphHCLK(uint32_t(v1) & uint32_t(v2));
    }

    #if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || defined(STM32F446xx) ||\
        defined(STM32F469xx) || defined(STM32F479xx)
    enum class EPLLSAIDiv: uint32_t
    {
        R_2  = 0,
        R_4  = 1,
        R_8  = 2,
        R_16 = 3,
    }
    #endif

    #if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)
    #define RCC_SAIACLKSOURCE_PLLSAI        ((uint32_t)0x00000000U)
    #define RCC_SAIACLKSOURCE_PLLI2S        ((uint32_t)0x00100000U)
    #define RCC_SAIACLKSOURCE_EXT           ((uint32_t)0x00200000U)

    #define RCC_SAIBCLKSOURCE_PLLSAI        ((uint32_t)0x00000000U)
    #define RCC_SAIBCLKSOURCE_PLLI2S        ((uint32_t)0x00400000U)
    #define RCC_SAIBCLKSOURCE_EXT           ((uint32_t)0x00800000U)
    #endif

    typedef struct
    {
        EPeriphHCLK selector;
        uint32_t    PLLI2S;
        uint32_t    RTC_div;
        uint32_t    RTC_src;
    #if defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F411xE)
     || defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)
        uint32_t    TIMPresSelection;
    #endif
    #if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)
        uint32_t    PLLSAI;
        uint32_t    PLLI2SDivQ;
        uint32_t    PLLSAIDivQ;
        uint32_t    PLLSAIDivR;
    #if defined(STM32F469xx) || defined(STM32F479xx)
        uint32_t    Clk48ClockSelection;
        uint32_t    SdioClockSelection;
    #endif
    #endif

    #if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)
        uint32_t    PLLSAIN;
    #if defined(STM32F469xx) || defined(STM32F479xx)
        uint32_t    PLLSAIP;
    #endif
        uint32_t    PLLSAIQ;
        uint32_t    PLLSAIR;
    #endif

    #if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)
        uint32_t    PLLI2SQ;
    #endif
        uint32_t    PLLI2SN;
        uint32_t    PLLI2SR;
    } RCC_Periph_Clock_Source;

    static void init();
    static void deinit_cold();
    static uint32_t deinit();
    static void deinit_per();

    static inline void HSI_enable() { STM32_REGS::RCC::CR::set_flags<STM32_REGS::RCC::CR::EMasks::HSION>(); }
    static inline void HSI_disable() { STM32_REGS::RCC::CR::clear_flags<STM32_REGS::RCC::CR::EMasks::HSION>(); }
    static inline void set_calibration_value_HSI(uint32_t value) { STM32_REGS::RCC::CR::set_HSITRIM(value); }
    static inline bool HSI_ready() { return STM32_REGS::RCC::CR::get_flags<STM32_REGS::RCC::CR::EMasks::HSIRDY>(); }

    static inline void LSI_enable() { STM32_REGS::RCC::CSR::set_flags<STM32_REGS::RCC::CSR::EMasks::LSION>(); }
    static inline void LSI_disable() { STM32_REGS::RCC::CSR::clear_flags<STM32_REGS::RCC::CSR::EMasks::LSION>(); }

    static inline void HSE_enable() { STM32_REGS::RCC::CR::set_flags<STM32_REGS::RCC::CR::EMasks::HSEON>(); }
    static inline void HSE_disable() { STM32_REGS::RCC::CR::clear_flags<STM32_REGS::RCC::CR::EMasks::HSEON, STM32_REGS::RCC::CR::EMasks::HSEBYP>(); }
    static inline void HSE_BYPASS_enable() { STM32_REGS::RCC::CR::set_flags<STM32_REGS::RCC::CR::EMasks::HSEON, STM32_REGS::RCC::CR::EMasks::HSEBYP>(); }
    static inline void HSE_BYPASS_disable() { STM32_REGS::RCC::CR::clear_flags<STM32_REGS::RCC::CR::EMasks::HSEON, STM32_REGS::RCC::CR::EMasks::HSEBYP>(); }
    static inline bool HSE_ready() { return STM32_REGS::RCC::CR::get_flags<STM32_REGS::RCC::CR::EMasks::HSERDY>(); }
    static void config_HSE(EHSEState state);

    static inline void LSE_enable() { STM32_REGS::RCC::BDCR::set_flags<STM32_REGS::RCC::BDCR::EMasks::LSEON>(); }
    static inline void LSE_disable() { STM32_REGS::RCC::BDCR::clear_flags<STM32_REGS::RCC::BDCR::EMasks::LSEON,
                STM32_REGS::RCC::BDCR::EMasks::LSEBYP>(); }
    static inline bool LSE_enabled() { return STM32_REGS::RCC::BDCR::get_flags<STM32_REGS::RCC::BDCR::EMasks::LSEON>(); }
    static inline bool LSE_ready() { return STM32_REGS::RCC::BDCR::get_flags<STM32_REGS::RCC::BDCR::EMasks::LSERDY>(); }
    static inline void LSE_BP_enable() { STM32_REGS::RCC::BDCR::set_flags<STM32_REGS::RCC::BDCR::EMasks::LSEBYP>(); }
    static inline void LSE_BP_disable() { STM32_REGS::RCC::BDCR::clear_flags<STM32_REGS::RCC::BDCR::EMasks::LSEBYP>(); }
    static void config_LSE(ELSEState state);

    static inline void RTC_enable() { STM32_REGS::RCC::BDCR::set_flags<STM32_REGS::RCC::BDCR::EMasks::RTCEN>(); }
    static inline void RTC_disable() { STM32_REGS::RCC::BDCR::clear_flags<STM32_REGS::RCC::BDCR::EMasks::RTCEN>(); }
    static inline bool RTC_enabled() { return STM32_REGS::RCC::BDCR::get_flags<STM32_REGS::RCC::BDCR::EMasks::RTCEN>(); }
    #ifdef STM32F4
    static void set_prescaler_RTC(uint32_t value);
    static inline uint32_t get_prescaler_RTC() { return STM32_REGS::RCC::CFGR::get_RTCPRE(); }
    #endif
    static void set_config_RTC(uint32_t on, uint32_t value);
    static inline bool get_RTC_source() { return STM32_REGS::RCC::BDCR::get_flags<STM32_REGS::RCC::BDCR::EMasks::RTCSEL>(); }

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) ||\
    defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) ||\
    defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F469xx) ||\
    defined(STM32F479xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || defined(STM32F412Rx) ||\
    defined(STM32F412Cx) || defined(STM32F413xx) || defined(STM32F423xx)
    static inline void set_TIM_prescaler(uint32_t val) { MODIFY_REG(RCC_->DCKCFGR, RCC_DCKCFGR_TIMPRE_Msk, val << RCC_DCKCFGR_TIMPRE_Pos); }
#endif

    static inline void force_reset_backup() { STM32_REGS::RCC::BDCR::set_flags<STM32_REGS::RCC::BDCR::EMasks::BDRST>(); }
    static inline void release_reset_backup() { STM32_REGS::RCC::BDCR::clear_flags<STM32_REGS::RCC::BDCR::EMasks::BDRST>(); }

    static inline void PLL_enable() { STM32_REGS::RCC::CR::set_flags<STM32_REGS::RCC::CR::EMasks::PLLON>(); }
    static inline void PLL_disable() { STM32_REGS::RCC::CR::clear_flags<STM32_REGS::RCC::CR::EMasks::PLLON>(); }
    static inline bool PLL_ready() { return STM32_REGS::RCC::CR::get_flags<STM32_REGS::RCC::CR::EMasks::PLLRDY>(); }
    #if defined(STM32F1)
    static inline void set_config_PLL_source(uint32_t value) { WRITE_REG(RCC_->CFGR, value); }
    static inline uint32_t get_source_PLL_OSC() { return RCC_->CFGR & RCC_CFGR_PLLSRC; }
    static inline void set_config_PLL_PLLM(uint32_t value) { MODIFY_REG(RCC_->CFGR, RCC_CFGR_PLLMULL, value); }
    #elif defined(STM32F4)
    static inline void set_config_PLL_source(uint32_t value) { STM32_REGS::RCC::PLLCFGR::set(value); }
    static inline bool get_source_PLL_OSC() { return STM32_REGS::RCC::PLLCFGR::get_flags<STM32_REGS::RCC::PLLCFGR::EMasks::PLLSRC_HSE>(); }
    #endif

    static inline void set_config_SYSCLK(ESystemClock value) { STM32_REGS::RCC::CFGR::set_SW(static_cast<uint32_t>(value)); }
    static inline ESystemClock get_source_SYSCLK() { return static_cast<ESystemClock>(STM32_REGS::RCC::CFGR::get_SWS()); }

    #if defined(STM32F1)
    static inline void set_config_MCO1(uint32_t source, uint32_t div)
        { MODIFY_REG(RCC_->CFGR, RCC_CFGR_MCO, (source | div)); }
    #else // STM32F1
    static inline void set_config_MCO1(EMCO1Source source, EMCODivider div)
        { STM32_REGS::RCC::CFGR::set_MCO1PRE(static_cast<uint32_t>(div));
          STM32_REGS::RCC::CFGR::set_MCO1(static_cast<uint32_t>(source)); }

    static inline void set_config_MCO2(EMCO2Source source, EMCODivider div)
        {  STM32_REGS::RCC::CFGR::set_MCO2PRE(static_cast<uint32_t>(div));
           STM32_REGS::RCC::CFGR::set_MCO2(static_cast<uint32_t>(source)); }
    #endif // STM32F1

    static inline void enable_IT(EIT value) { *(reinterpret_cast<__IO uint8_t*>(STM32::RCC_BASE + RCC_CIR_OFFSET + 1)) |= static_cast<uint8_t>(value); }
    static inline void disable_IT(EIT value) { *(reinterpret_cast<__IO uint8_t*>(STM32::RCC_BASE + RCC_CIR_OFFSET + 1)) &= ~static_cast<uint8_t>(value); }
    static inline void clear_IT(EIT value) { *(reinterpret_cast<__IO uint8_t*>(STM32::RCC_BASE + RCC_CIR_OFFSET + 2)) = static_cast<uint8_t>(value); }
    static inline bool get_IT(EIT value) { return (STM32_REGS::RCC::CIR::get() & static_cast<uint32_t>(value)) == static_cast<uint32_t>(value); }

    static inline void clear_reset_flags() { STM32_REGS::RCC::CSR::set_flags<STM32_REGS::RCC::CSR::EMasks::RMVF>(); }

    static bool get_flag(EFlag value);

    static uint32_t config_osc();
    static uint32_t config_clock();
    
    static inline uint32_t get_HCLK_freq() { return m_system_core_clock; }
    static uint32_t get_PCLK1_freq();
    static uint32_t get_PCLK2_freq();

    static void config_MCO1(EMCO1Source source, EMCODivider div);
    #ifdef RCC_CFGR_MCO2
    static void config_MCO2(EMCO2Source source, EMCODivider div);
    #endif

    static inline void CSS_enable() { STM32_REGS::RCC::CR::set_flags<STM32_REGS::RCC::CR::EMasks::CSSON>(); }
    static inline void CSS_disable() { STM32_REGS::RCC::CR::clear_flags<STM32_REGS::RCC::CR::EMasks::CSSON>(); }

#if defined(STM32F1)
    CLK_ENDIS(AHB, DMA1)
    CLK_ENDIS(AHB, SRAM)
    CLK_ENDIS(AHB, FLITF)
    CLK_ENDIS(AHB, CRC)

    CLK_ENDIS(APB1, TIM2)
    CLK_ENDIS(APB1, TIM3)
    CLK_ENDIS(APB1, WWDG)
    CLK_ENDIS(APB1, USART2)
    CLK_ENDIS(APB1, I2C1)
    CLK_ENDIS(APB1, BKP)
    CLK_ENDIS(APB1, PWR)

    CLK_ENDIS(APB2, AFIO)
    CLK_ENDIS_EX(APB2, GPIOA, IOPA)
    CLK_ENDIS_EX(APB2, GPIOB, IOPB)
    CLK_ENDIS_EX(APB2, GPIOC, IOPC)
    CLK_ENDIS_EX(APB2, GPIOD, IOPD)
    CLK_ENDIS(APB2, ADC1)
    CLK_ENDIS(APB2, TIM1)
    CLK_ENDIS(APB2, SPI1)
    CLK_ENDIS(APB2, USART1)
#else // STM32F1
    static inline void enable_clk_GPIOA() { STM32_REGS::RCC::AHB1ENR::set_flags<STM32_REGS::RCC::AHB1ENR::EMasks::GPIOAEN>(); }
    static inline void disable_clk_GPIOA() { STM32_REGS::RCC::AHB1ENR::clear_flags<STM32_REGS::RCC::AHB1ENR::EMasks::GPIOAEN>(); }
    static inline void enable_clk_GPIOB() { STM32_REGS::RCC::AHB1ENR::set_flags<STM32_REGS::RCC::AHB1ENR::EMasks::GPIOBEN>(); }
    static inline void disable_clk_GPIOB() { STM32_REGS::RCC::AHB1ENR::clear_flags<STM32_REGS::RCC::AHB1ENR::EMasks::GPIOBEN>(); }
    static inline void enable_clk_GPIOC() { STM32_REGS::RCC::AHB1ENR::set_flags<STM32_REGS::RCC::AHB1ENR::EMasks::GPIOCEN>(); }
    static inline void disable_clk_GPIOC() { STM32_REGS::RCC::AHB1ENR::clear_flags<STM32_REGS::RCC::AHB1ENR::EMasks::GPIOCEN>(); }
    static inline void enable_clk_GPIOD() { STM32_REGS::RCC::AHB1ENR::set_flags<STM32_REGS::RCC::AHB1ENR::EMasks::GPIODEN>(); }
    static inline void disable_clk_GPIOD() { STM32_REGS::RCC::AHB1ENR::clear_flags<STM32_REGS::RCC::AHB1ENR::EMasks::GPIODEN>(); }
    static inline void enable_clk_GPIOE() { STM32_REGS::RCC::AHB1ENR::set_flags<STM32_REGS::RCC::AHB1ENR::EMasks::GPIOEEN>(); }
    static inline void disable_clk_GPIOE() { STM32_REGS::RCC::AHB1ENR::clear_flags<STM32_REGS::RCC::AHB1ENR::EMasks::GPIOEEN>(); }
    static inline void enable_clk_GPIOF() { STM32_REGS::RCC::AHB1ENR::set_flags<STM32_REGS::RCC::AHB1ENR::EMasks::GPIOFEN>(); }
    static inline void disable_clk_GPIOF() { STM32_REGS::RCC::AHB1ENR::clear_flags<STM32_REGS::RCC::AHB1ENR::EMasks::GPIOFEN>(); }
    static inline void enable_clk_GPIOG() { STM32_REGS::RCC::AHB1ENR::set_flags<STM32_REGS::RCC::AHB1ENR::EMasks::GPIOGEN>(); }
    static inline void disable_clk_GPIOG() { STM32_REGS::RCC::AHB1ENR::clear_flags<STM32_REGS::RCC::AHB1ENR::EMasks::GPIOGEN>(); }
    static inline void enable_clk_GPIOH() { STM32_REGS::RCC::AHB1ENR::set_flags<STM32_REGS::RCC::AHB1ENR::EMasks::GPIOHEN>(); }
    static inline void disable_clk_GPIOH() { STM32_REGS::RCC::AHB1ENR::clear_flags<STM32_REGS::RCC::AHB1ENR::EMasks::GPIOHEN>(); }
    static inline void enable_clk_GPIOI() { STM32_REGS::RCC::AHB1ENR::set_flags<STM32_REGS::RCC::AHB1ENR::EMasks::GPIOIEN>(); }
    static inline void disable_clk_GPIOI() { STM32_REGS::RCC::AHB1ENR::clear_flags<STM32_REGS::RCC::AHB1ENR::EMasks::GPIOIEN>(); }
#ifdef RCC_AHB1ENR_GPIOJEN
    CLK_ENDIS(AHB1, GPIOJ)
#endif
#ifdef RCC_AHB1ENR_GPIOKEN
    CLK_ENDIS(AHB1, GPIOK)
#endif
    static inline void enable_clk_CRC() { STM32_REGS::RCC::AHB1ENR::set_flags<STM32_REGS::RCC::AHB1ENR::EMasks::CRCEN>(); }
    static inline void disable_clk_CRC() { STM32_REGS::RCC::AHB1ENR::clear_flags<STM32_REGS::RCC::AHB1ENR::EMasks::CRCEN>(); }
    static inline void enable_clk_DMA1() { STM32_REGS::RCC::AHB1ENR::set_flags<STM32_REGS::RCC::AHB1ENR::EMasks::DMA1EN>(); }
    static inline void disable_clk_DMA1() { STM32_REGS::RCC::AHB1ENR::clear_flags<STM32_REGS::RCC::AHB1ENR::EMasks::DMA1EN>(); }
    static inline void enable_clk_DMA2() { STM32_REGS::RCC::AHB1ENR::set_flags<STM32_REGS::RCC::AHB1ENR::EMasks::DMA2EN>(); }
    static inline void disable_clk_DMA2() { STM32_REGS::RCC::AHB1ENR::clear_flags<STM32_REGS::RCC::AHB1ENR::EMasks::DMA2EN>(); }
    static inline void enable_clk_BKPSRAM() { STM32_REGS::RCC::AHB1ENR::set_flags<STM32_REGS::RCC::AHB1ENR::EMasks::BKPSRAMEN>(); }
    static inline void disable_clk_BKPSRAM() { STM32_REGS::RCC::AHB1ENR::clear_flags<STM32_REGS::RCC::AHB1ENR::EMasks::BKPSRAMEN>(); }
    static inline void enable_clk_CCMDATARAM() { STM32_REGS::RCC::AHB1ENR::set_flags<STM32_REGS::RCC::AHB1ENR::EMasks::CCMDATARAMEN>(); }
    static inline void disable_clk_CCMDATARAM() { STM32_REGS::RCC::AHB1ENR::clear_flags<STM32_REGS::RCC::AHB1ENR::EMasks::CCMDATARAMEN>(); }
    static inline void enable_clk_OTGHS() { STM32_REGS::RCC::AHB1ENR::set_flags<STM32_REGS::RCC::AHB1ENR::EMasks::OTGHSEN>(); }
    static inline void disable_clk_OTGHS() { STM32_REGS::RCC::AHB1ENR::clear_flags<STM32_REGS::RCC::AHB1ENR::EMasks::OTGHSEN>(); }
    static inline void enable_clk_OTGHSULPI() { STM32_REGS::RCC::AHB1ENR::set_flags<STM32_REGS::RCC::AHB1ENR::EMasks::OTGHSULPIEN>(); }
    static inline void disable_clk_OTGHSULPI() { STM32_REGS::RCC::AHB1ENR::clear_flags<STM32_REGS::RCC::AHB1ENR::EMasks::OTGHSULPIEN>(); }
#ifdef RCC_AHB1ENR_DMA2DEN
    static inline void enable_clk_DMA2D() { STM32_REGS::RCC::AHB1ENR::set_flags<STM32_REGS::RCC::AHB1ENR::EMasks::DMA2DEN>(); }
    static inline void disable_clk_DMA2D() { STM32_REGS::RCC::AHB1ENR::clear_flags<STM32_REGS::RCC::AHB1ENR::EMasks::DMA2DEN>(); }
#endif

    static inline void enable_clk_DCMI() { STM32_REGS::RCC::AHB2ENR::set_flags<STM32_REGS::RCC::AHB2ENR::EMasks::DCMIEN>(); }
    static inline void disable_clk_DCMI() { STM32_REGS::RCC::AHB2ENR::clear_flags<STM32_REGS::RCC::AHB2ENR::EMasks::DCMIEN>(); }
    static inline void enable_clk_RNG() { STM32_REGS::RCC::AHB2ENR::set_flags<STM32_REGS::RCC::AHB2ENR::EMasks::RNGEN>(); }
    static inline void disable_clk_RNG() { STM32_REGS::RCC::AHB2ENR::clear_flags<STM32_REGS::RCC::AHB2ENR::EMasks::RNGEN>(); }
    static inline void enable_clk_OTGFS() { STM32_REGS::RCC::AHB2ENR::set_flags<STM32_REGS::RCC::AHB2ENR::EMasks::OTGFSEN>(); }
    static inline void disable_clk_OTGFS() { STM32_REGS::RCC::AHB2ENR::clear_flags<STM32_REGS::RCC::AHB2ENR::EMasks::OTGFSEN>(); }

#ifdef STM32F4
    static inline void enable_clk_ETHMAC() { STM32_REGS::RCC::AHB1ENR::set_flags<STM32_REGS::RCC::AHB1ENR::EMasks::ETHMACEN>(); }
    static inline void disable_clk_ETHMAC() { STM32_REGS::RCC::AHB1ENR::clear_flags<STM32_REGS::RCC::AHB1ENR::EMasks::ETHMACEN>(); }
    static inline void enable_clk_ETHMACTX() { STM32_REGS::RCC::AHB1ENR::set_flags<STM32_REGS::RCC::AHB1ENR::EMasks::ETHMACTXEN>(); }
    static inline void disable_clk_ETHMACTX() { STM32_REGS::RCC::AHB1ENR::clear_flags<STM32_REGS::RCC::AHB1ENR::EMasks::ETHMACTXEN>(); }
    static inline void enable_clk_ETHMACRX() { STM32_REGS::RCC::AHB1ENR::set_flags<STM32_REGS::RCC::AHB1ENR::EMasks::ETHMACRXEN>(); }
    static inline void disable_clk_ETHMACRX() { STM32_REGS::RCC::AHB1ENR::clear_flags<STM32_REGS::RCC::AHB1ENR::EMasks::ETHMACRXEN>(); }
    static inline void enable_clk_ETHMACPTP() { STM32_REGS::RCC::AHB1ENR::set_flags<STM32_REGS::RCC::AHB1ENR::EMasks::ETHMACPTPEN>(); }
    static inline void disable_clk_ETHMACPTP() { STM32_REGS::RCC::AHB1ENR::clear_flags<STM32_REGS::RCC::AHB1ENR::EMasks::ETHMACPTPEN>(); }

    static inline void enable_clk_eth() { enable_clk_ETHMAC(); enable_clk_ETHMACTX(); enable_clk_ETHMACRX(); }
    static inline void disable_clk_eth() { disable_clk_ETHMAC(); disable_clk_ETHMACTX(); disable_clk_ETHMACRX(); }

    static inline void enable_clk_USB_FS() { enable_clk_OTGFS(); enable_clk_SYSCFG(); }
    static inline void disable_clk_USB_FS() { disable_clk_OTGFS(); }

    static inline void enable_clk_USB_HS() { enable_clk_OTGHS(); enable_clk_SYSCFG(); }
    static inline void disable_clk_USB_HS() { disable_clk_OTGHS(); }
#endif // STM32F4

#ifdef RCC_AHB3ENR_FMCEN
    CLK_ENDIS(AHB3, FMC)
#endif
#ifdef RCC_AHB3ENR_FSMCEN
    static inline void enable_clk_FSMC() { STM32_REGS::RCC::AHB3ENR::set_flags<STM32_REGS::RCC::AHB3ENR::EMasks::FSMCEN>(); }
    static inline void disable_clk_FSMC() { STM32_REGS::RCC::AHB3ENR::clear_flags<STM32_REGS::RCC::AHB3ENR::EMasks::FSMCEN>(); }
#endif
#ifdef RCC_AHB3ENR_QSPIEN
    CLK_ENDIS(AHB3, QSPI)
#endif
    static inline void enable_clk_TIM2() { STM32_REGS::RCC::APB1ENR::set_flags<STM32_REGS::RCC::APB1ENR::EMasks::TIM2EN>(); }
    static inline void disable_clk_TIM2() { STM32_REGS::RCC::APB1ENR::clear_flags<STM32_REGS::RCC::APB1ENR::EMasks::TIM2EN>(); }
    static inline void enable_clk_TIM3() { STM32_REGS::RCC::APB1ENR::set_flags<STM32_REGS::RCC::APB1ENR::EMasks::TIM3EN>(); }
    static inline void disable_clk_TIM3() { STM32_REGS::RCC::APB1ENR::clear_flags<STM32_REGS::RCC::APB1ENR::EMasks::TIM3EN>(); }
    static inline void enable_clk_TIM4() { STM32_REGS::RCC::APB1ENR::set_flags<STM32_REGS::RCC::APB1ENR::EMasks::TIM4EN>(); }
    static inline void disable_clk_TIM4() { STM32_REGS::RCC::APB1ENR::clear_flags<STM32_REGS::RCC::APB1ENR::EMasks::TIM4EN>(); }
    static inline void enable_clk_TIM5() { STM32_REGS::RCC::APB1ENR::set_flags<STM32_REGS::RCC::APB1ENR::EMasks::TIM5EN>(); }
    static inline void disable_clk_TIM5() { STM32_REGS::RCC::APB1ENR::clear_flags<STM32_REGS::RCC::APB1ENR::EMasks::TIM5EN>(); }
    static inline void enable_clk_TIM6() { STM32_REGS::RCC::APB1ENR::set_flags<STM32_REGS::RCC::APB1ENR::EMasks::TIM6EN>(); }
    static inline void disable_clk_TIM6() { STM32_REGS::RCC::APB1ENR::clear_flags<STM32_REGS::RCC::APB1ENR::EMasks::TIM6EN>(); }
    static inline void enable_clk_TIM7() { STM32_REGS::RCC::APB1ENR::set_flags<STM32_REGS::RCC::APB1ENR::EMasks::TIM7EN>(); }
    static inline void disable_clk_TIM7() { STM32_REGS::RCC::APB1ENR::clear_flags<STM32_REGS::RCC::APB1ENR::EMasks::TIM7EN>(); }
    static inline void enable_clk_TIM12() { STM32_REGS::RCC::APB1ENR::set_flags<STM32_REGS::RCC::APB1ENR::EMasks::TIM12EN>(); }
    static inline void disable_clk_TIM12() { STM32_REGS::RCC::APB1ENR::clear_flags<STM32_REGS::RCC::APB1ENR::EMasks::TIM12EN>(); }
    static inline void enable_clk_TIM13() { STM32_REGS::RCC::APB1ENR::set_flags<STM32_REGS::RCC::APB1ENR::EMasks::TIM13EN>(); }
    static inline void disable_clk_TIM13() { STM32_REGS::RCC::APB1ENR::clear_flags<STM32_REGS::RCC::APB1ENR::EMasks::TIM13EN>(); }
    static inline void enable_clk_TIM14() { STM32_REGS::RCC::APB1ENR::set_flags<STM32_REGS::RCC::APB1ENR::EMasks::TIM14EN>(); }
    static inline void disable_clk_TIM14() { STM32_REGS::RCC::APB1ENR::clear_flags<STM32_REGS::RCC::APB1ENR::EMasks::TIM14EN>(); }
    static inline void enable_clk_WWDG() { STM32_REGS::RCC::APB1ENR::set_flags<STM32_REGS::RCC::APB1ENR::EMasks::WWDGEN>(); }
    static inline void disable_clk_WWDG() { STM32_REGS::RCC::APB1ENR::clear_flags<STM32_REGS::RCC::APB1ENR::EMasks::WWDGEN>(); }
    static inline void enable_clk_SPI2() { STM32_REGS::RCC::APB1ENR::set_flags<STM32_REGS::RCC::APB1ENR::EMasks::SPI2EN>(); }
    static inline void disable_clk_SPI2() { STM32_REGS::RCC::APB1ENR::clear_flags<STM32_REGS::RCC::APB1ENR::EMasks::SPI2EN>(); }
    static inline void enable_clk_SPI3() { STM32_REGS::RCC::APB1ENR::set_flags<STM32_REGS::RCC::APB1ENR::EMasks::SPI3EN>(); }
    static inline void disable_clk_SPI3() { STM32_REGS::RCC::APB1ENR::clear_flags<STM32_REGS::RCC::APB1ENR::EMasks::SPI3EN>(); }
    static inline void enable_clk_USART2() { STM32_REGS::RCC::APB1ENR::set_flags<STM32_REGS::RCC::APB1ENR::EMasks::USART2EN>(); }
    static inline void disable_clk_USART2() { STM32_REGS::RCC::APB1ENR::clear_flags<STM32_REGS::RCC::APB1ENR::EMasks::USART2EN>(); }
    static inline void enable_clk_USART3() { STM32_REGS::RCC::APB1ENR::set_flags<STM32_REGS::RCC::APB1ENR::EMasks::USART3EN>(); }
    static inline void disable_clk_USART3() { STM32_REGS::RCC::APB1ENR::clear_flags<STM32_REGS::RCC::APB1ENR::EMasks::USART3EN>(); }
    static inline void enable_clk_UART4() { STM32_REGS::RCC::APB1ENR::set_flags<STM32_REGS::RCC::APB1ENR::EMasks::UART4EN>(); }
    static inline void disable_clk_UART4() { STM32_REGS::RCC::APB1ENR::clear_flags<STM32_REGS::RCC::APB1ENR::EMasks::UART4EN>(); }
    static inline void enable_clk_UART5() { STM32_REGS::RCC::APB1ENR::set_flags<STM32_REGS::RCC::APB1ENR::EMasks::UART5EN>(); }
    static inline void disable_clk_UART5() { STM32_REGS::RCC::APB1ENR::clear_flags<STM32_REGS::RCC::APB1ENR::EMasks::UART5EN>(); }
    static inline void enable_clk_I2C1() { STM32_REGS::RCC::APB1ENR::set_flags<STM32_REGS::RCC::APB1ENR::EMasks::I2C1EN>(); }
    static inline void disable_clk_I2C1() { STM32_REGS::RCC::APB1ENR::clear_flags<STM32_REGS::RCC::APB1ENR::EMasks::I2C1EN>(); }
    static inline void enable_clk_I2C2() { STM32_REGS::RCC::APB1ENR::set_flags<STM32_REGS::RCC::APB1ENR::EMasks::I2C2EN>(); }
    static inline void disable_clk_I2C2() { STM32_REGS::RCC::APB1ENR::clear_flags<STM32_REGS::RCC::APB1ENR::EMasks::I2C2EN>(); }
    static inline void enable_clk_I2C3() { STM32_REGS::RCC::APB1ENR::set_flags<STM32_REGS::RCC::APB1ENR::EMasks::I2C3EN>(); }
    static inline void disable_clk_I2C3() { STM32_REGS::RCC::APB1ENR::clear_flags<STM32_REGS::RCC::APB1ENR::EMasks::I2C3EN>(); }
    static inline void enable_clk_CAN1() { STM32_REGS::RCC::APB1ENR::set_flags<STM32_REGS::RCC::APB1ENR::EMasks::CAN1EN>(); }
    static inline void disable_clk_CAN1() { STM32_REGS::RCC::APB1ENR::clear_flags<STM32_REGS::RCC::APB1ENR::EMasks::CAN1EN>(); }
    static inline void enable_clk_CAN2() { STM32_REGS::RCC::APB1ENR::set_flags<STM32_REGS::RCC::APB1ENR::EMasks::CAN2EN>(); }
    static inline void disable_clk_CAN2() { STM32_REGS::RCC::APB1ENR::clear_flags<STM32_REGS::RCC::APB1ENR::EMasks::CAN2EN>(); }
    static inline void enable_clk_PWR() { STM32_REGS::RCC::APB1ENR::set_flags<STM32_REGS::RCC::APB1ENR::EMasks::PWREN>(); }
    static inline void disable_clk_PWR() { STM32_REGS::RCC::APB1ENR::clear_flags<STM32_REGS::RCC::APB1ENR::EMasks::PWREN>(); }
    static inline void enable_clk_DAC() { STM32_REGS::RCC::APB1ENR::set_flags<STM32_REGS::RCC::APB1ENR::EMasks::DACEN>(); }
    static inline void disable_clk_DAC() { STM32_REGS::RCC::APB1ENR::clear_flags<STM32_REGS::RCC::APB1ENR::EMasks::DACEN>(); }
#ifdef RCC_APB1ENR_UART7EN
    static inline void enable_clk_UART7() { STM32_REGS::RCC::APB1ENR::set_flags<STM32_REGS::RCC::APB1ENR::EMasks::UART7EN>(); }
    static inline void disable_clk_UART7() { STM32_REGS::RCC::APB1ENR::clear_flags<STM32_REGS::RCC::APB1ENR::EMasks::UART7EN>(); }
#endif
#ifdef RCC_APB1ENR_UART9EN
    static inline void enable_clk_UART8() { STM32_REGS::RCC::APB1ENR::set_flags<STM32_REGS::RCC::APB1ENR::EMasks::UART8EN>(); }
    static inline void disable_clk_UART8() { STM32_REGS::RCC::APB1ENR::clear_flags<STM32_REGS::RCC::APB1ENR::EMasks::UART8EN>(); }
#endif

    static inline void enable_clk_TIM1() { STM32_REGS::RCC::APB2ENR::set_flags<STM32_REGS::RCC::APB2ENR::EMasks::TIM1EN>(); }
    static inline void disable_clk_TIM1() { STM32_REGS::RCC::APB2ENR::clear_flags<STM32_REGS::RCC::APB2ENR::EMasks::TIM1EN>(); }
    static inline void enable_clk_TIM8() { STM32_REGS::RCC::APB2ENR::set_flags<STM32_REGS::RCC::APB2ENR::EMasks::TIM8EN>(); }
    static inline void disable_clk_TIM8() { STM32_REGS::RCC::APB2ENR::clear_flags<STM32_REGS::RCC::APB2ENR::EMasks::TIM8EN>(); }
    static inline void enable_clk_TIM9() { STM32_REGS::RCC::APB2ENR::set_flags<STM32_REGS::RCC::APB2ENR::EMasks::TIM9EN>(); }
    static inline void disable_clk_TIM9() { STM32_REGS::RCC::APB2ENR::clear_flags<STM32_REGS::RCC::APB2ENR::EMasks::TIM9EN>(); }
    static inline void enable_clk_TIM10() { STM32_REGS::RCC::APB2ENR::set_flags<STM32_REGS::RCC::APB2ENR::EMasks::TIM10EN>(); }
    static inline void disable_clk_TIM10() { STM32_REGS::RCC::APB2ENR::clear_flags<STM32_REGS::RCC::APB2ENR::EMasks::TIM10EN>(); }
    static inline void enable_clk_TIM11() { STM32_REGS::RCC::APB2ENR::set_flags<STM32_REGS::RCC::APB2ENR::EMasks::TIM11EN>(); }
    static inline void disable_clk_TIM11() { STM32_REGS::RCC::APB2ENR::clear_flags<STM32_REGS::RCC::APB2ENR::EMasks::TIM11EN>(); }
    static inline void enable_clk_USART1() { STM32_REGS::RCC::APB2ENR::set_flags<STM32_REGS::RCC::APB2ENR::EMasks::USART1EN>(); }
    static inline void disable_clk_USART1() { STM32_REGS::RCC::APB2ENR::clear_flags<STM32_REGS::RCC::APB2ENR::EMasks::USART1EN>(); }
    static inline void enable_clk_USART6() { STM32_REGS::RCC::APB2ENR::set_flags<STM32_REGS::RCC::APB2ENR::EMasks::USART6EN>(); }
    static inline void disable_clk_USART6() { STM32_REGS::RCC::APB2ENR::clear_flags<STM32_REGS::RCC::APB2ENR::EMasks::USART6EN>(); }
    static inline void enable_clk_ADC1() { STM32_REGS::RCC::APB2ENR::set_flags<STM32_REGS::RCC::APB2ENR::EMasks::ADC1EN>(); }
    static inline void disable_clk_ADC1() { STM32_REGS::RCC::APB2ENR::clear_flags<STM32_REGS::RCC::APB2ENR::EMasks::ADC1EN>(); }
    static inline void enable_clk_ADC2() { STM32_REGS::RCC::APB2ENR::set_flags<STM32_REGS::RCC::APB2ENR::EMasks::ADC2EN>(); }
    static inline void disable_clk_ADC2() { STM32_REGS::RCC::APB2ENR::clear_flags<STM32_REGS::RCC::APB2ENR::EMasks::ADC2EN>(); }
    static inline void enable_clk_ADC3() { STM32_REGS::RCC::APB2ENR::set_flags<STM32_REGS::RCC::APB2ENR::EMasks::ADC3EN>(); }
    static inline void disable_clk_ADC3() { STM32_REGS::RCC::APB2ENR::clear_flags<STM32_REGS::RCC::APB2ENR::EMasks::ADC3EN>(); }
    static inline void enable_clk_SDIO() { STM32_REGS::RCC::APB2ENR::set_flags<STM32_REGS::RCC::APB2ENR::EMasks::SDIOEN>(); }
    static inline void disable_clk_SDIO() { STM32_REGS::RCC::APB2ENR::clear_flags<STM32_REGS::RCC::APB2ENR::EMasks::SDIOEN>(); }
    static inline void enable_clk_SPI1() { STM32_REGS::RCC::APB2ENR::set_flags<STM32_REGS::RCC::APB2ENR::EMasks::SPI1EN>(); }
    static inline void disable_clk_SPI1() { STM32_REGS::RCC::APB2ENR::clear_flags<STM32_REGS::RCC::APB2ENR::EMasks::SPI1EN>(); }
#ifdef RCC_APB2ENR_SPI4EN
    static inline void enable_clk_SPI4() { STM32_REGS::RCC::APB2ENR::set_flags<STM32_REGS::RCC::APB2ENR::EMasks::SPI4EN>(); }
    static inline void disable_clk_SPI4() { STM32_REGS::RCC::APB2ENR::clear_flags<STM32_REGS::RCC::APB2ENR::EMasks::SPI4EN>(); }
#endif
    static inline void enable_clk_SYSCFG() { STM32_REGS::RCC::APB2ENR::set_flags<STM32_REGS::RCC::APB2ENR::EMasks::SYSCFGEN>(); }
    static inline void disable_clk_SYSCFG() { STM32_REGS::RCC::APB2ENR::clear_flags<STM32_REGS::RCC::APB2ENR::EMasks::SYSCFGEN>(); }
#ifdef RCC_APB2ENR_LTDCEN
    static inline void enable_clk_LTDC() { STM32_REGS::RCC::APB2ENR::set_flags<STM32_REGS::RCC::APB2ENR::EMasks::LTDCEN>(); }
    static inline void disable_clk_LTDC() { STM32_REGS::RCC::APB2ENR::clear_flags<STM32_REGS::RCC::APB2ENR::EMasks::LTDCEN>(); }
#endif
#ifdef RCC_APB2ENR_DSIEN
    static inline void enable_clk_DSI() { STM32_REGS::RCC::APB2ENR::set_flags<STM32_REGS::RCC::APB2ENR::EMasks::DSIEN>(); }
    static inline void disable_clk_DSI() { STM32_REGS::RCC::APB2ENR::clear_flags<STM32_REGS::RCC::APB2ENR::EMasks::DSIEN>(); }
#endif
#ifdef RCC_APB2ENR_SPI5EN
    static inline void enable_clk_SPI5() { STM32_REGS::RCC::APB2ENR::set_flags<STM32_REGS::RCC::APB2ENR::EMasks::SPI5EN>(); }
    static inline void disable_clk_SPI5() { STM32_REGS::RCC::APB2ENR::clear_flags<STM32_REGS::RCC::APB2ENR::EMasks::SPI5EN>(); }
#endif
#ifdef RCC_APB2ENR_SPI6EN
    static inline void enable_clk_SPI6() { STM32_REGS::RCC::APB2ENR::set_flags<STM32_REGS::RCC::APB2ENR::EMasks::SPI6EN>(); }
    static inline void disable_clk_SPI6() { STM32_REGS::RCC::APB2ENR::clear_flags<STM32_REGS::RCC::APB2ENR::EMasks::SPI6EN>(); }
#endif
#ifdef RCC_APB2ENR_SAI1EN
    static inline void enable_clk_SAI1() { STM32_REGS::RCC::APB2ENR::set_flags<STM32_REGS::RCC::APB2ENR::EMasks::SAI1EN>(); }
    static inline void disable_clk_SAI1() { STM32_REGS::RCC::APB2ENR::clear_flags<STM32_REGS::RCC::APB2ENR::EMasks::SAI1EN>(); }
#endif
#endif // STM32F1

#if defined(STM32F1)
    static inline void APB1_reset_force() { STM32_REGS::RCC::APB1RSTR::set(0xFFFFFFFFU); }
    static inline void APB1_reset_release() { STM32_REGS::RCC::APB1RSTR::set(0); }
    template <STM32_REGS::RCC::APB1RSTR::EMasks ... flags>
    static inline void APB1_reset_force()
    {
        STM32_REGS::RCC::APB1RSTR::set_flags<flags ...>();
    }
    template <STM32_REGS::RCC::APB1RSTR::EMasks ... flags>
    static inline void APB1_reset_release()
    {
        STM32_REGS::RCC::APB1RSTR::clear_flags<flags ...>();
    }

    static inline void APB2_reset_force() { STM32_REGS::RCC::APB2RSTR::set(0xFFFFFFFFU); }
    static inline void APB2_reset_release() { STM32_REGS::RCC::APB2RSTR::set(0); }
    template <STM32_REGS::RCC::APB2RSTR::EMasks ... flags>
    static inline void APB2_reset_force()
    {
        STM32_REGS::RCC::APB2RSTR::set_flags<flags ...>();
    }
    template <STM32_REGS::RCC::APB2RSTR::EMasks ... flags>
    static inline void APB2_reset_release()
    {
        STM32_REGS::RCC::APB2RSTR::clear_flags<flags ...>();
    }
#else
    static inline void AHB1_reset_force() { STM32_REGS::RCC::AHB1RSTR::set(0xFFFFFFFFU); }
    static inline void AHB1_reset_release() { STM32_REGS::RCC::AHB1RSTR::set(0); }
    template <STM32_REGS::RCC::AHB1RSTR::EMasks ... flags>
    static inline void AHB1_reset_force()
    {
        STM32_REGS::RCC::AHB1RSTR::set_flags<flags ...>();
    }
    template <STM32_REGS::RCC::AHB1RSTR::EMasks ... flags>
    static inline void AHB1_reset_release()
    {
        STM32_REGS::RCC::AHB1RSTR::clear_flags<flags ...>();
    }
    template <STM32_REGS::RCC::AHB1LPENR::EMasks ... flags>
    static inline void AHB1_sleep_enable()
    {
        STM32_REGS::RCC::AHB1LPENR::set_flags<flags ...>();
    }
    template <STM32_REGS::RCC::AHB1LPENR::EMasks ... flags>
    static inline void AHB1_sleep_disable()
    {
        STM32_REGS::RCC::AHB1LPENR::clear_flags<flags ...>();
    }

    static inline void AHB2_reset_force() { STM32_REGS::RCC::AHB2RSTR::set(0xFFFFFFFFU); }
    static inline void AHB2_reset_release() { STM32_REGS::RCC::AHB2RSTR::set(0); }
    template <STM32_REGS::RCC::AHB2RSTR::EMasks ... flags>
    static inline void AHB2_reset_force()
    {
        STM32_REGS::RCC::AHB2RSTR::set_flags<flags ...>();
    }
    template <STM32_REGS::RCC::AHB2RSTR::EMasks ... flags>
    static inline void AHB2_reset_release()
    {
        STM32_REGS::RCC::AHB2RSTR::clear_flags<flags ...>();
    }
    template <STM32_REGS::RCC::AHB2LPENR::EMasks ... flags>
    static inline void AHB2_sleep_enable()
    {
        STM32_REGS::RCC::AHB2LPENR::set_flags<flags ...>();
    }
    template <STM32_REGS::RCC::AHB2LPENR::EMasks ... flags>
    static inline void AHB2_sleep_disable()
    {
        STM32_REGS::RCC::AHB2LPENR::clear_flags<flags ...>();
    }

    static inline void AHB3_reset_force() { STM32_REGS::RCC::AHB3RSTR::set(0xFFFFFFFFU); }
    static inline void AHB3_reset_release() { STM32_REGS::RCC::AHB3RSTR::set(0); }
    template <STM32_REGS::RCC::AHB3RSTR::EMasks ... flags>
    static inline void AHB3_reset_force()
    {
        STM32_REGS::RCC::AHB3RSTR::set_flags<flags ...>();
    }
    template <STM32_REGS::RCC::AHB3RSTR::EMasks ... flags>
    static inline void AHB3_reset_release()
    {
        STM32_REGS::RCC::AHB3RSTR::clear_flags<flags ...>();
    }
    template <STM32_REGS::RCC::AHB3LPENR::EMasks ... flags>
    static inline void AHB3_sleep_enable()
    {
        STM32_REGS::RCC::AHB3LPENR::set_flags<flags ...>();
    }
    template <STM32_REGS::RCC::AHB3LPENR::EMasks ... flags>
    static inline void AHB3_sleep_disable()
    {
        STM32_REGS::RCC::AHB3LPENR::clear_flags<flags ...>();
    }

    static inline void APB1_reset_force() { STM32_REGS::RCC::APB1RSTR::set(0xFFFFFFFFU); }
    static inline void APB1_reset_release() { STM32_REGS::RCC::APB1RSTR::set(0); }
    template <STM32_REGS::RCC::APB1RSTR::EMasks ... flags>
    static inline void APB1_reset_force()
    {
        STM32_REGS::RCC::APB1RSTR::set_flags<flags ...>();
    }
    template <STM32_REGS::RCC::APB1RSTR::EMasks ... flags>
    static inline void APB1_reset_release()
    {
        STM32_REGS::RCC::APB1RSTR::clear_flags<flags ...>();
    }
    template <STM32_REGS::RCC::APB1LPENR::EMasks ... flags>
    static inline void APB1_sleep_enable()
    {
        STM32_REGS::RCC::APB1LPENR::set_flags<flags ...>();
    }
    template <STM32_REGS::RCC::APB1LPENR::EMasks ... flags>
    static inline void APB1_sleep_disable()
    {
        STM32_REGS::RCC::APB1LPENR::clear_flags<flags ...>();
    }

    static inline void APB2_reset_force() { STM32_REGS::RCC::APB2RSTR::set(0xFFFFFFFFU); }
    static inline void APB2_reset_release() { STM32_REGS::RCC::APB2RSTR::set(0); }
    template <STM32_REGS::RCC::APB2RSTR::EMasks ... flags>
    static inline void APB2_reset_force()
    {
        STM32_REGS::RCC::APB2RSTR::set_flags<flags ...>();
    }
    template <STM32_REGS::RCC::APB2RSTR::EMasks ... flags>
    static inline void APB2_reset_release()
    {
        STM32_REGS::RCC::APB2RSTR::clear_flags<flags ...>();
    }
    template <STM32_REGS::RCC::APB2LPENR::EMasks ... flags>
    static inline void APB2_sleep_enable()
    {
        STM32_REGS::RCC::APB2LPENR::set_flags<flags ...>();
    }
    template <STM32_REGS::RCC::APB2LPENR::EMasks ... flags>
    static inline void APB2_sleep_disable()
    {
        STM32_REGS::RCC::APB2LPENR::clear_flags<flags ...>();
    }
#endif // STM32F1

    static void NMI_IRQ_Handler();

    #if defined(STM32F4)
    /* RCCex */
    static uint32_t periph_CLK_config(RCC_Periph_Clock_Source *sources);
    #endif

#if defined(STM32F429xx)
    ENDIS_REG_FLAG_NAME(PLLSAI_IT, RCC_->CIR, RCC_CIR_PLLSAIRDYIE)
    static inline void clear_PLLSAI_IT() { clear_IT(RCC_CIR_PLLSAIRDYF); }
    static bool get_PLLSAI_IT() { return get_IT(RCC_CIR_PLLSAIRDYIE); }
    static bool get_PLLSAI_flag() { return ((RCC_->CR & RCC_CR_PLLSAIRDY) == RCC_CR_PLLSAIRDY); }

    static inline void PLLI2S_SAI_config(uint32_t sn, uint32_t sq, uint32_t sr)
        { RCC_->PLLI2SCFGR = (sn << RCC_PLLI2SCFGR_PLLI2SN_Pos) |
                (sq << RCC_PLLI2SCFGR_PLLI2SQ_Pos) |
                (sr << RCC_PLLI2SCFGR_PLLI2SR_Pos); }
    static inline void PLLI2S_SAI_configQ(uint32_t sq)
        { MODIFY_REG(RCC_->DCKCFGR, RCC_DCKCFGR_PLLI2SDIVQ, sq); }

    static inline void PLLSAI_configQ(uint32_t sq)
        { MODIFY_REG(RCC_->DCKCFGR, RCC_DCKCFGR_PLLSAIDIVQ, ((sq - 1) << 8)); }
    static inline void PLLSAI_configR(uint32_t sr)
        { MODIFY_REG(RCC_->DCKCFGR, RCC_DCKCFGR_PLLSAIDIVR, sr); }

    ENDIS_REG_FLAG(PLLSAI, RCC_->CR, RCC_CR_PLLSAION)
#endif
#ifdef STM32F4
    static inline void PLLI2S_enable() { STM32_REGS::RCC::CR::set_flags<STM32_REGS::RCC::CR::EMasks::PLLI2SON>(); }
    static inline void PLLI2S_disable() { STM32_REGS::RCC::CR::clear_flags<STM32_REGS::RCC::CR::EMasks::PLLI2SON>(); }
    static inline void PLLSAI_config(uint32_t sn, uint32_t sr)
        { STM32_REGS::RCC::PLLI2SCFGR::set_PLLI2SN(sn);
          STM32_REGS::RCC::PLLI2SCFGR::set_PLLI2SR(sr); }

    static inline void config_I2S(EI2SSource val)
    { if (val == EI2SSource::I2S_CKIN) STM32_REGS::RCC::CFGR::set_flags<STM32_REGS::RCC::CFGR::EMasks::I2SSRC>();
        else STM32_REGS::RCC::CFGR::clear_flags<STM32_REGS::RCC::CFGR::EMasks::I2SSRC>(); }
    static inline EI2SSource get_I2S_source() { return static_cast<EI2SSource>(STM32_REGS::RCC::CFGR::get_flags<STM32_REGS::RCC::CFGR::EMasks::I2SSRC>()); }
#endif // STM32F4

    static void update_clock();
private:
    static uint32_t m_system_core_clock;

    static uint32_t update_system_core_clock();
};

}

#endif
