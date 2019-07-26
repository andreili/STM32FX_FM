#include "stm32_rcc.hpp"

namespace STM32
{

uint32_t RCC::m_system_core_clock;
uint32_t unused_reg;

#define __MCO1_CLK_ENABLE()   enable_clk_GPIOA()
#define MCO1_GPIO_PORT        gpioa
#define MCO1_PIN              STM32_GPIO::PIN_8

#if defined(STM32F4)
#define __MCO2_CLK_ENABLE()   enable_clk_GPIOC()
#define MCO2_GPIO_PORT        gpioc
#define MCO2_PIN              STM32_GPIO::PIN_9
#endif // STM32F4

#define HSI_VALUE    16000000UL
#define HSE_VALUE     8000000UL
#define F_CPU 		168000000UL

#define HSE_TIMEOUT_VALUE           100
#define HSI_TIMEOUT_VALUE           2U  /* 2 ms */
#define LSI_TIMEOUT_VALUE           2U  /* 2 ms */
#define RCC_DBP_TIMEOUT_VALUE       2U
#define PLL_TIMEOUT_VALUE           2U
#define LSE_TIMEOUT_VALUE           5000
#define CLOCKSWITCH_TIMEOUT_VALUE   5000U /* 5 s    */

#if defined(STM32F1)
    #define RCC_PLLSOURCE_HSI_DIV2           0x00000000U
    #define RCC_PLLSOURCE_HSE                RCC_CFGR_PLLSRC
#elif defined(STM32F4)
    #define RCC_PLLSOURCE_HSI                RCC_PLLCFGR_PLLSRC_HSI
    #define RCC_PLLSOURCE_HSE                RCC_PLLCFGR_PLLSRC_HSE
#endif

const uint8_t APBAHBPrescTable[16] = {0U, 0U, 0U, 0U, 1U, 2U, 3U, 4U, 1U, 2U, 3U, 4U, 6U, 7U, 8U, 9U};
const uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
const uint8_t APBPrescTable[8]  = {0, 0, 0, 0, 1, 2, 3, 4};
#if defined(RCC_CFGR2_PREDIV1SRC)
  const uint8_t aPLLMULFactorTable[14] = {0, 0, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 13};
  const uint8_t aPredivFactorTable[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
#else
    #if defined(STM32F1)
    const uint8_t aPLLMULFactorTable[16] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 16};
    #endif
#if defined(RCC_CFGR2_PREDIV1)
  const uint8_t aPredivFactorTable[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
#else
    #if defined(STM32F1)
    const uint8_t aPredivFactorTable[2] = {1, 2};
    #endif
#endif /*RCC_CFGR2_PREDIV1*/
#endif

#define PLLI2S_TIMEOUT_VALUE       2  /* Timeout value fixed to 2 ms  */
#define PLLSAI_TIMEOUT_VALUE       2  /* Timeout value fixed to 2 ms  */

void RCC::init()
{
    enable_clk_PWR();
    #if defined(STM32F4)
    STM32::PWR::set_voltage_scaling_enabled(STM32::PWR::EVoltageScale::SCALE1);
    #endif
    if (config_osc() != STM32_RESULT_OK)
        Error_Handler();
    #if defined(STM32F1)
    #if defined(STM32_FLASH_LAT)
    if (config_clock()) != STM32_RESULT_OK)
        Error_Handler();
    #else // STM32_FLASH_LAT
    if (config_clock() != STM32_RESULT_OK)
        Error_Handler();
    #endif // FLASH_ACR_LATENCY
    #else
    if (config_clock() != STM32_RESULT_OK)
        Error_Handler();
    #endif

    #ifdef STM32_RTC_ENABLE
    RCC_Periph_Clock_Source sources;
    sources.selector = EPeriphHCLK::RTC;
    sources.RTCClockSelection = STM32_RTC_CLOCK_SOURCE;
    if (periph_CLK_config(&sources) != STM32_RESULT_OK)
        Error_Handler();
    #endif

    #ifdef STM32_USE_CSS
    CSS_enable();
    #endif
}

void RCC::deinit_cold()
{
    /* Reset the RCC clock configuration to the default reset state ------------*/
    HSI_enable();
    STM32_REGS::RCC::CFGR::set(0);
    STM32_REGS::RCC::CR::clear_flags<STM32_REGS::RCC::CR::EMasks::PLLON,
            STM32_REGS::RCC::CR::EMasks::CSSON, STM32_REGS::RCC::CR::EMasks::HSEON>();
    /* Reset PLLCFGR register */
    STM32_REGS::RCC::PLLCFGR::set_PLLM(16);
    STM32_REGS::RCC::PLLCFGR::set_PLLN(192);
    STM32_REGS::RCC::PLLCFGR::set_PLLQ(4);
    STM32_REGS::RCC::CR::clear_flags<STM32_REGS::RCC::CR::EMasks::HSEBYP>();
    /* Disable all interrupts */
    STM32_REGS::RCC::CIR::set(0);
}

uint32_t RCC::deinit()
{
    m_system_core_clock = HSI_VALUE;
    #if defined (STM32F4)
    set_calibration_value_HSI(0x10);
    #endif
    HSI_enable();
    // wait till HSI is ready
    WAIT_TIMEOUT(!HSI_ready(), HSI_TIMEOUT_VALUE);
    #if defined(STM32F1)
    set_calibration_value_HSI(STM32_HSI_CALIBRATION);
    #endif

    STM32_REGS::RCC::CFGR::set(0);
    WAIT_TIMEOUT((get_source_SYSCLK() != ESystemClock::HSI), HSI_TIMEOUT_VALUE);

    m_system_core_clock = HSI_VALUE;

    #if defined (STM32F4)
    STM32_REGS::RCC::CR::clear_flags<STM32_REGS::RCC::CR::EMasks::PLLON, STM32_REGS::RCC::CR::EMasks::PLLI2SON>();
    #else
    STM32_REGS::RCC::CR::clear_flags<STM32_REGS::RCC::CR::EMasks::PLLI2SON>();
    #endif
    WAIT_TIMEOUT((PLL_ready() != RESET), PLL_TIMEOUT_VALUE);
    STM32_REGS::RCC::CFGR::set(0);

    STM32_REGS::RCC::CR::clear_flags<STM32_REGS::RCC::CR::EMasks::HSEON, STM32_REGS::RCC::CR::EMasks::CSSON>();
    WAIT_TIMEOUT((HSE_ready() != RESET), HSE_TIMEOUT_VALUE);

    #if defined (STM32F4)
    STM32_REGS::RCC::PLLCFGR::set_PLLM(16);
    STM32_REGS::RCC::PLLCFGR::set_PLLN(192);
    STM32_REGS::RCC::PLLCFGR::set_PLLQ(4);

    PLLSAI_config(0x0C0, 0x2);
    #endif // STM32F4

    HSE_BYPASS_disable();
    clear_reset_flags();
    STM32_REGS::RCC::CIR::set(0);

    m_system_core_clock = update_system_core_clock();

    return STM32_RESULT_OK;
}

void RCC::deinit_per()
{
    //Peripheral reset enable
    AHB1_reset_force();
    AHB2_reset_force();
    AHB3_reset_force();
    APB1_reset_force();
    APB2_reset_force();
    //Peripheral  reset disable
    AHB1_reset_release();
    AHB2_reset_release();
    AHB3_reset_release();
    APB1_reset_release();
    APB2_reset_release();
    //Peripheral  disable clock
    STM32_REGS::RCC::AHB1ENR::set(static_cast<uint32_t>(STM32_REGS::RCC::AHB1ENR::EMasks::CCMDATARAMEN));
    STM32_REGS::RCC::AHB2ENR::set(0);
    STM32_REGS::RCC::AHB3ENR::set(0);
    STM32_REGS::RCC::APB1ENR::set(0);
    STM32_REGS::RCC::APB2ENR::set(0);
}

void RCC::config_HSE(EHSEState state)
{
    switch (state)
    {
    case EHSEState::ON:
        HSE_enable();
        break;
    case EHSEState::BYPASS:
        HSE_BYPASS_enable();
        break;
    default:
        HSE_disable();
        break;
    }
}

void RCC::config_LSE(ELSEState state)
{
    switch (state)
    {
    case ELSEState::ON:
        LSE_enable();
        break;
    case ELSEState::BYPASS:
        LSE_BP_enable();
        break;
    default:
        LSE_disable();
        break;
    }
}

#if defined(STM32F4)
void RCC::set_prescaler_RTC(uint32_t value)
{
    STM32_REGS::RCC::CFGR::set_RTCPRE(value);
}
#endif

void RCC::set_config_RTC(uint32_t on, uint32_t value)
{
    #ifdef STM32F4
    set_prescaler_RTC(value);
    #endif
    STM32_REGS::RCC::BDCR::set_RTCSEL(on);
}

uint32_t RCC::get_PCLK1_freq()
{
    return (get_HCLK_freq() >> APBAHBPrescTable[STM32_REGS::RCC::CFGR::get_PPRE1()]);
}

uint32_t RCC::config_osc()
{
    #ifdef STM32_USE_HSE
    config_HSE(STM32_HSE_STATE);
    if (STM32_HSE_STATE != EHSEState::OFF)
    {
        WAIT_TIMEOUT(get_flag(EFlag::HSERDY) == RESET, HSE_TIMEOUT_VALUE);
    }
    else
    {
        WAIT_TIMEOUT(get_flag(EFlag::HSERDY) != RESET, HSE_TIMEOUT_VALUE);
    }
    #elif defined(STM32_USE_HSI)
    if (STM32_HSI_STATE != 0)
    {
        enable_HSI();
        WAIT_TIMEOUT(get_flag(EFlag::HSIRDY) == RESET, HSI_TIMEOUT_VALUE);
        set_calibration_value_HSI(STM32_HSI_CALIBRATION);
    }
    else
    {
        disable_HSI();
        WAIT_TIMEOUT(get_flag(EFlag::HSIRDY) != RESET, HSI_TIMEOUT_VALUE);
    }
    #endif

   #ifdef STM32_USE_LSI
    #ifdef STM32_LSI_STATE
    LSI_enable();
    WAIT_TIMEOUT(get_flag(EFlag::LSIRDY) == RESET, LSI_TIMEOUT_VALUE);
    #else
    LSI_disable();
    WAIT_TIMEOUT(get_flag(EFlag::LSIRDY) != RESET, LSI_TIMEOUT_VALUE);
    #endif //STM32_LSI_STATE
   #elif defined(STM32_USE_LSE)
    enable_clk_PWR();
    STM32_PWR::enable_backup_access();
    WAIT_TIMEOUT(STM32_PWR::is_backup_acces_RO(), RCC_DBP_TIMEOUT_VALUE);
    config_LSE(STM32_LSE_STATE);

    #ifdef STM32_LSI_STATE
    WAIT_TIMEOUT(get_flag(EFlag::LSERDY) == RESET, LSE_TIMEOUT_VALUE);
    #else
    WAIT_TIMEOUT(get_flag(EFlag::LSERDY) != RESET, LSE_TIMEOUT_VALUE);
    #endif //STM32_LSI_STATE
   #endif //STM32_USE_LSI

    #ifdef STM32_USE_PLL
    if (get_source_SYSCLK() != ESystemClock::PLL)
    {
        PLL_disable();
        WAIT_TIMEOUT(get_flag(EFlag::PLLRDY) != RESET, PLL_TIMEOUT_VALUE);
        if (STM32_PLL_STATE == EPLL::ON)
        {
            #if defined(STM32F4)
            if (STM32_PLL_SOURCE == EPLLSource::HSE)
                STM32_REGS::RCC::PLLCFGR::set_flags<STM32_REGS::RCC::PLLCFGR::EMasks::PLLSRC_HSE>();
            else
                STM32_REGS::RCC::PLLCFGR::clear_flags<STM32_REGS::RCC::PLLCFGR::EMasks::PLLSRC_HSE>();
            STM32_REGS::RCC::PLLCFGR::set_PLLM(STM32_PLLM);
            STM32_REGS::RCC::PLLCFGR::set_PLLN(STM32_PLLN);
            STM32_REGS::RCC::PLLCFGR::set_PLLP(static_cast<uint32_t>(STM32_PLLP));
            STM32_REGS::RCC::PLLCFGR::set_PLLQ(STM32_PLLQ);
            #elif defined(STM32F1)
            set_config_PLL_source(STM32_PLL_SOURCE | STM32_PLLM);
            #endif
            PLL_enable();
            WAIT_TIMEOUT(get_flag(EFlag::PLLRDY) == RESET, PLL_TIMEOUT_VALUE);
        }
    }
    else
        return STM32_RESULT_FAIL;
    #endif

    return STM32_RESULT_OK;
}

uint32_t RCC::config_clock()
{
    #if defined(STM32_FLASH_LAT)
    if (STM32_FLASH_LAT > STM32::FLASH::get_latency())
    {
        STM32::FLASH::set_latency(STM32_FLASH_LAT);
        if (STM32::FLASH::get_latency() != STM32_FLASH_LAT)
            return STM32_RESULT_FAIL;
    }
    #endif

    if ((STM32_CLOCK_TYPE & EClockType::HCLK) == EClockType::HCLK)
        STM32_REGS::RCC::CFGR::set_HPRE(static_cast<uint32_t>(STM32_CLOCK_AHB_DIV));

    if ((STM32_CLOCK_TYPE & EClockType::SYSCLK) == EClockType::SYSCLK)
    {
        if (STM32_CLOCK_SYSCLK_SOURCE == ESystemClock::HSE)
        {
            if (get_flag(EFlag::HSERDY) == RESET)
                return STM32_RESULT_FAIL;
        }
        else if (STM32_CLOCK_SYSCLK_SOURCE == ESystemClock::PLL)
        {
            if (get_flag(EFlag::PLLRDY) == RESET)
                return STM32_RESULT_FAIL;
        }
        else if (get_flag(EFlag::HSIRDY) == RESET)
            return STM32_RESULT_FAIL;

        set_config_SYSCLK(STM32_CLOCK_SYSCLK_SOURCE);
        switch (STM32_CLOCK_SYSCLK_SOURCE)
        {
        case ESystemClock::HSE:
            WAIT_TIMEOUT(get_source_SYSCLK() != ESystemClock::HSE, CLOCKSWITCH_TIMEOUT_VALUE);
            break;
        case ESystemClock::PLL:
            WAIT_TIMEOUT(get_source_SYSCLK() != ESystemClock::PLL, CLOCKSWITCH_TIMEOUT_VALUE);
            break;
        default:
            WAIT_TIMEOUT(get_source_SYSCLK() != ESystemClock::HSI, CLOCKSWITCH_TIMEOUT_VALUE);
            break;
        }
    }

    #if defined(STM32_FLASH_LAT)
    if (STM32_FLASH_LAT < STM32::FLASH::get_latency())
    {
        STM32::FLASH::set_latency(STM32_FLASH_LAT);
        if (STM32::FLASH::get_latency() != STM32_FLASH_LAT)
            return STM32_RESULT_FAIL;
    }
    #endif

    if ((STM32_CLOCK_TYPE & EClockType::PCLK1) == EClockType::PCLK1)
        STM32_REGS::RCC::CFGR::set_PPRE1(static_cast<uint32_t>(STM32_CLOCK_APB1_DIV));

    if ((STM32_CLOCK_TYPE & EClockType::PCLK2) == EClockType::PCLK2)
        STM32_REGS::RCC::CFGR::set_PPRE2(static_cast<uint32_t>(STM32_CLOCK_APB2_DIV));

    update_clock();

    return STM32_RESULT_OK;
}

bool RCC::get_flag(EFlag value)
{
    __IO uint32_t reg;
    switch (static_cast<uint32_t>(value) >> 5U)
    {
    case 0x01U:
        reg = STM32_REGS::RCC::CR::get();
        break;
    case 0x02U:
        reg = STM32_REGS::RCC::BDCR::get();
        break;
    case 0x03U:
        reg = STM32_REGS::RCC::CSR::get();
        break;
    default:
        reg = STM32_REGS::RCC::CIR::get();
        break;
    }
    return (reg & (0x01U << (static_cast<uint32_t>(value) & static_cast<uint32_t>(EFlag::MASK))));
}

uint32_t RCC::get_PCLK2_freq()
{
    return (get_HCLK_freq() >> APBAHBPrescTable[STM32_REGS::RCC::CFGR::get_PPRE2()]);
}

void RCC::config_MCO1(EMCO1Source source, EMCODivider div)
{
    __MCO1_CLK_ENABLE();
    #if defined(STM3F1)
    UNUSED(RCC_MCODiv);
    MCO1_GPIO_PORT.set_config(MCO1_PIN, STM32_GPIO::EMode::AF_PP, 0, STM32_GPIO::ESpeed::HIGH, STM32_GPIO::EPull::NOPULL);
    MODIFY_REG(RCC_->CFGR, RCC_CFGR_MCO, RCC_MCOSource);
    #elif defined(STM32F4)
    MCO1_GPIO_PORT.set_config(MCO1_PIN, STM32_GPIO::EMode::AF_PP, STM32_GPIO::EAF::AF0_MCO, STM32_GPIO::ESpeed::VERY_HIGH, STM32_GPIO::EPull::NOPULL);
    set_config_MCO1(source, div);
    #endif
}

#ifdef RCC_CFGR_MCO2
void RCC::config_MCO2(EMCO2Source source, EMCODivider div)
{
    __MCO2_CLK_ENABLE();
    MCO2_GPIO_PORT.set_config(MCO2_PIN, STM32_GPIO::EMode::AF_PP, STM32_GPIO::EAF::AF0_MCO, STM32_GPIO::ESpeed::VERY_HIGH, STM32_GPIO::EPull::NOPULL);
    STM32_REGS::RCC::CFGR::set_MCO2PRE(static_cast<uint32_t>(div));
    STM32_REGS::RCC::CFGR::set_MCO2(static_cast<uint32_t>(source));
    set_config_MCO2(source, div);
}
#endif

void RCC::NMI_IRQ_Handler()
{
    if (get_IT(EIT::CSS))
    {
        ///TODO: CSSCallback
        clear_IT(EIT::CSS);
    }
}

#if defined(STM32F4)
uint32_t RCC::periph_CLK_config(RCC_Periph_Clock_Source *sources)
{
    uint32_t tmpreg1 = 0U;

    /*----------------------- SAI/I2S Configuration (PLLI2S) -------------------*/
    if (((sources->selector & EPeriphHCLK::I2S) == EPeriphHCLK::I2S) ||
#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx)
        ((sources->selector & EPeriphHCLK::SAI_PLLI2S) == EPeriphHCLK::SAI_PLLI2S))
#else
        ((sources->selector & EPeriphHCLK::PLLI2S) == EPeriphHCLK::PLLI2S))
#endif
    {
        PLLI2S_disable();
        /* Wait till PLLI2S is disabled */
        WAIT_TIMEOUT(get_flag(EFlag::PLLI2SRDY) != RESET, PLLI2S_TIMEOUT_VALUE);
#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx)
        /*---------------------------- SAI configuration -------------------------*/
        /* In Case of SAI Clock Configuration through PLLI2S, PLLI2SQ and PLLI2S_DIVQ must
        be added only for SAI configuration */
        if ((sources->selector & EPeriphHCLK::SAI_PLLI2S) == EPeriphHCLK::SAI_PLLI2S)
        {
            /* Read PLLI2SR value from PLLI2SCFGR register (this value is not need for SAI configuration) */
            tmpreg1 = ((RCC_->PLLI2SCFGR & RCC_PLLI2SCFGR_PLLI2SR) >> POSITION_VAL(RCC_PLLI2SCFGR_PLLI2SR));
            /* Configure the PLLI2S division factors */
            /* PLLI2S_VCO Input  = PLL_SOURCE/PLLM */
            /* PLLI2S_VCO Output = PLLI2S_VCO Input * PLLI2SN */
            /* SAI_CLK(first level) = PLLI2S_VCO Output/PLLI2SQ */
            PLLI2S_SAI_config(sources->PLLI2SN, sources->PLLI2SQ , tmpreg1);
            /* SAI_CLK_x = SAI_CLK(first level)/PLLI2SDIVQ */
            PLLI2S_SAI_configQ(sources->PLLI2SDivQ);
        }
#else
        PLLSAI_config(sources->PLLI2SN, sources->PLLI2SR);
#endif

        /* Enable the PLLI2S */
        PLLI2S_enable();
        /* Wait till PLLI2S is ready */
        WAIT_TIMEOUT(get_flag(EFlag::PLLI2SRDY) == RESET, PLLI2S_TIMEOUT_VALUE);
    }

    /*----------------------- SAI/LTDC Configuration (PLLSAI) ------------------*/
#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx)
    if (((sources->selector & EPeriphHCLK::SAI_PLLSAI) == EPeriphHCLK::SAI_PLLSAI) ||
        ((sources->selector & EPeriphHCLK::LTDC) == EPeriphHCLK::LTDC))
    {
        /* Disable PLLSAI Clock */
        disable_PLLSAI();
        /* Wait till PLLSAI is disabled */
        WAIT_TIMEOUT(get_PLLSAI_flag() != RESET, PLLSAI_TIMEOUT_VALUE);

        /*---------------------------- SAI configuration -------------------------*/
        /* In Case of SAI Clock Configuration through PLLSAI, PLLSAIQ and PLLSAI_DIVQ must
        be added only for SAI configuration */
        if ((sources->selector & EPeriphHCLK::SAI_PLLSAI) == EPeriphHCLK::SAI_PLLSAI)
        {
            /* Read PLLSAIR value from PLLSAICFGR register (this value is not need for SAI configuration) */
            tmpreg1 = ((RCC_->PLLSAICFGR & RCC_PLLSAICFGR_PLLSAIR) >> POSITION_VAL(RCC_PLLSAICFGR_PLLSAIR));
            /* PLLSAI_VCO Input  = PLL_SOURCE/PLLM */
            /* PLLSAI_VCO Output = PLLSAI_VCO Input * PLLSAIN */
            /* SAI_CLK(first level) = PLLSAI_VCO Output/PLLSAIQ */
            PLLSAI_config(sources->PLLSAIN , sources->PLLSAIQ, tmpreg1);
            /* SAI_CLK_x = SAI_CLK(first level)/PLLSAIDIVQ */
            PLLSAI_configQ(sources->PLLSAIDivQ);
        }

        /*---------------------------- LTDC configuration ------------------------*/
        if (((sources->selector) & EPeriphHCLK::LTDC) == (EPeriphHCLK::LTDC))
        {
            /* Read PLLSAIR value from PLLSAICFGR register (this value is not need for SAI configuration) */
            tmpreg1 = ((RCC_->PLLSAICFGR & RCC_PLLSAICFGR_PLLSAIQ) >> POSITION_VAL(RCC_PLLSAICFGR_PLLSAIQ));
            /* PLLSAI_VCO Input  = PLL_SOURCE/PLLM */
            /* PLLSAI_VCO Output = PLLSAI_VCO Input * PLLSAIN */
            /* LTDC_CLK(first level) = PLLSAI_VCO Output/PLLSAIR */
            PLLSAI_config(sources->PLLSAIN , tmpreg1, sources->PLLSAIR);
            /* LTDC_CLK = LTDC_CLK(first level)/PLLSAIDIVR */
            PLLSAI_configR(sources->PLLSAIDivR);
        }
        /* Enable PLLSAI Clock */
        enable_PLLSAI();
        /* Wait till PLLSAI is ready */
        WAIT_TIMEOUT(get_PLLSAI_flag() == RESET, PLLSAI_TIMEOUT_VALUE);
    }
#endif

    /*---------------------------- RTC configuration ---------------------------*/
    if ((sources->selector & EPeriphHCLK::RTC) == EPeriphHCLK::RTC)
    {
        /* Enable Power Clock*/
        enable_clk_PWR();

        /* Enable write access to Backup domain */
        STM32::PWR::set_backup_access(true);
        WAIT_TIMEOUT(STM32::PWR::is_backup_acces_RO(), RCC_DBP_TIMEOUT_VALUE);

        /* Reset the Backup domain only if the RTC Clock source selection is modified from reset value */
        tmpreg1 = STM32_REGS::RCC::BDCR::get_RTCSEL();
        if ((tmpreg1 != 0) &&
            (tmpreg1 != sources->RTC_src))
        {
            /* RTC Clock selection can be changed only if the Backup Domain is reset */
            force_reset_backup();
            release_reset_backup();
            /* Restore the Content of BDCR register */
            STM32_REGS::RCC::BDCR::set(tmpreg1);

            /* Wait for LSE reactivation if LSE was enable prior to Backup Domain reset */
            if (LSE_enabled())
            {
                /* Wait till LSE is ready */
                WAIT_TIMEOUT(!LSE_ready(), LSE_TIMEOUT_VALUE);
            }
        }
        set_config_RTC(sources->RTC_src, sources->RTC_div);
    }

#if defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F411xE)
 || defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || defined(STM32F469xx) || defined(STM32F479xx)
    /*---------------------------- TIM configuration ---------------------------*/
    if (((sources->selector) & EPeriphHCLK::TIM) == EPeriphHCLK::TIM)
        set_TIM_prescaler(sources->TIMPresSelection);
#endif

    return STM32_RESULT_OK;
}
#endif // STM32F4

uint32_t RCC::update_system_core_clock()
{
    uint32_t pllvco = 0,
            pllp = 2;
            #if defined(STM32F1)
            prediv = 0;
            #endif
    uint32_t sysclockfreq = 0U;

    switch (static_cast<ESystemClock>(STM32_REGS::RCC::CFGR::get_SWS()))
    {
    case ESystemClock::HSI:
        sysclockfreq = HSI_VALUE;
        break;
    case ESystemClock::HSE:
        sysclockfreq = HSE_VALUE;
        break;
    case ESystemClock::PLL:
        #if defined(STM32F1)
        pllsource = get_source_PLL_OSC() >> 22;
        pllm = aPLLMULFactorTable[(RCC_->CFGR & RCC_CFGR_PLLMULL >> RCC_CFGR_PLLMULL_Pos)];
        if (get_source_PLL_OSC() != RCC_PLLSOURCE_HSI_DIV2)
        {
            #if defined(RCC_CFGR2_PREDIV1)
            prediv = aPredivFactorTable[(uint32_t)(RCC_->CFGR2 & RCC_CFGR2_PREDIV1) >> RCC_CFGR2_PREDIV1_Pos];
            #else
            prediv = aPredivFactorTable[(uint32_t)(RCC_->CFGR & RCC_CFGR_PLLXTPRE) >> RCC_CFGR_PLLXTPRE_Pos];
            #endif /*RCC_CFGR2_PREDIV1*/

            #if defined(RCC_CFGR2_PREDIV1SRC)
            if(HAL_IS_BIT_SET(RCC_->CFGR2, RCC_CFGR2_PREDIV1SRC))
            {
                    /* PLL2 selected as Prediv1 source */
                    /* PLLCLK = PLL2CLK / PREDIV1 * PLLMUL with PLL2CLK = HSE/PREDIV2 * PLL2MUL */
                    prediv2 = ((RCC_->CFGR2 & RCC_CFGR2_PREDIV2) >> RCC_CFGR2_PREDIV2_Pos) + 1;
                    pll2mul = ((RCC_->CFGR2 & RCC_CFGR2_PLL2MUL) >> RCC_CFGR2_PLL2MUL_Pos) + 2;
                    pllclk = (uint32_t)(((uint64_t)HSE_VALUE * (uint64_t)pll2mul * (uint64_t)pllmul) / ((uint64_t)prediv2 * (uint64_t)prediv));
            }
            else
            {
                    /* HSE used as PLL clock source : PLLCLK = HSE/PREDIV1 * PLLMUL */
                    pllclk = (uint32_t)((HSE_VALUE * pllmul) / prediv);
            }

            /* If PLLMUL was set to 13 means that it was to cover the case PLLMUL 6.5 (avoid using float) */
            /* In this case need to divide pllclk by 2 */
            if (pllmul == aPLLMULFactorTable[(uint32_t)(RCC_CFGR_PLLMULL6_5) >> RCC_CFGR_PLLMULL_Pos])
                    pllclk = pllclk / 2;
            #else
            /* HSE used as PLL clock source : PLLCLK = HSE/PREDIV1 * PLLMUL */
            sysclockfreq = (uint32_t)((HSE_VALUE  * pllm) / prediv);
            #endif /*RCC_CFGR2_PREDIV1SRC*/
        }
        else
        {
                /* HSI used as PLL clock source : PLLCLK = HSI/2 * PLLMUL */
                sysclockfreq = (uint32_t)((HSI_VALUE >> 1) * pllm);
        }
        #elif defined(STM32F4)
        if (get_source_PLL_OSC())
        {
            /* HSE used as PLL clock source */
            pllvco = (HSE_VALUE / STM32_REGS::RCC::PLLCFGR::get_PLLM()) * STM32_REGS::RCC::PLLCFGR::get_PLLN();
        }
        else
        {
            /* HSI used as PLL clock source */
            pllvco = (HSI_VALUE / STM32_REGS::RCC::PLLCFGR::get_PLLM()) * STM32_REGS::RCC::PLLCFGR::get_PLLN();
        }
        pllp = (STM32_REGS::RCC::PLLCFGR::get_PLLP() + 1 ) * 2;
        sysclockfreq = pllvco/pllp;
				#endif
        break;
    default:
        sysclockfreq = HSI_VALUE;
        break;
    }
    /* Compute HCLK frequency --------------------------------------------------*/
    /* HCLK frequency */
    sysclockfreq >>= STM32_REGS::RCC::CFGR::get_HPRE();

    return sysclockfreq;
}

void RCC::update_clock()
{
    m_system_core_clock = update_system_core_clock() >> APBAHBPrescTable[STM32_REGS::RCC::CFGR::get_HPRE()];
}

}

__attribute__((weak)) void ISR::RCC_IRQ()
{
    if (STM32::RCC::get_IT(STM32::RCC::EIT::CSS))
    {
        STM32::RCC::clear_IT(STM32::RCC::EIT::CSS);
    }
}
