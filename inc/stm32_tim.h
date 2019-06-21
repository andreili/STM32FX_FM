#ifndef STM32_TIM_H
#define STM32_TIM_H

#include <inttypes.h>
#include <stm32_inc.h>

class STM32_DMA;

#define TIM_CCER_CCxE_MASK  (TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E)
#define TIM_CCER_CCxNE_MASK (TIM_CCER_CC1NE | TIM_CCER_CC2NE | TIM_CCER_CC3NE)

class STM32_TIM
{
public:
    enum class EState: uint8_t
    {
        _RESET  = 0,
        READY   = 1,
        BUSY    = 2,
        TIMEOUT = 3,
        ERROR   = 4,
    };
    enum EActiveChannel: uint8_t
    {
        ACT_CLEARED = 0,
        ACT_CH_1    = 1,
        ACT_CH_2    = 2,
        ACT_CH_3    = 4,
        ACT_CH_4    = 8,
    };
    enum EChannelPolarity: uint32_t
    {
        RISING      = 0,
        FALLING     = TIM_CCER_CC1P,
        BOTH_EDGE   = TIM_CCER_CC1P | TIM_CCER_CC1NP,
    };
    enum EETRPrescaller: uint32_t
    {
        PS_1    = 0,
        PS_2    = TIM_SMCR_ETPS_0,
        PS_4    = TIM_SMCR_ETPS_1,
        PS_8    = TIM_SMCR_ETPS,
    };
    enum ECounterMode: uint32_t
    {
        UP      = 0,
        DOWN    = TIM_CR1_DIR,
        CALIGN1 = TIM_CR1_CMS_0,
        CALIGN2 = TIM_CR1_CMS_1,
        CALIGN3 = TIM_CR1_CMS,
    };
    enum EClkDiv: uint32_t
    {
        DIV_1   = 0,
        DIV_2   = TIM_CR1_CKD_0,
        DIV_4   = TIM_CR1_CKD_1,
    };
    enum EOCMode: uint32_t
    {
        TIMING          = 0,
        ACTIVE          = TIM_CCMR1_OC1M_0,
        INACTIVE        = TIM_CCMR1_OC1M_1,
        TOGGLE          = (TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC1M_1),
        PWM1            = (TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2),
        PWM2            = TIM_CCMR1_OC1M,
        FORCED_ACTIVE   = (TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC1M_2),
        FORCED_INACTIVE = TIM_CCMR1_OC1M_2,
    };
    enum EOCFast: uint32_t
    {
        DISABLE = 0,
        ENABLE  = TIM_CCMR1_OC1FE,
    };
    enum EOCPolarity: uint32_t
    {
        OC_HIGH = 0,
        OC_LOW  = TIM_CCER_CC1P,
    };
    enum EOCNPolarity: uint32_t
    {
        OCN_HIGH    = 0,
        OCN_LOW     = TIM_CCER_CC1NP,
    };
    enum EOCIdleState: uint32_t
    {
        OC_RESET    = 0,
        OC_SET      = TIM_CR2_OIS1,
    };
    enum EOCNIdleState: uint32_t
    {
        OCN_RESET   = 0,
        OCN_SET     = TIM_CR2_OIS1N,
    };
    enum EChannel: uint32_t
    {
        CH_1    = 1,
        CH_2    = 2,
        CH_3    = 4,
        CH_4    = 8,
        CH_ALL  = 0x18,
    };
    enum EICPolarity: uint32_t
    {
        IC_RISING   = 0,
        IC_FALLING  = TIM_CCER_CC1P,
        IC_BOTHEDGE = (TIM_CCER_CC1P|TIM_CCER_CC1NP),
    };
    enum EICDiv: uint32_t
    {
        IC_DIV_1   = 0,
        IC_DIV_2   = TIM_CCMR1_IC1PSC_0,
        IC_DIV_4   = TIM_CCMR1_IC1PSC_1,
        IC_DIV_8   = TIM_CCMR1_IC1PSC,
    };
    enum EICSelection: uint32_t
    {
        IC_SEL_DIRECT_TI    = TIM_CCMR1_CC1S_0,
        IC_SEL_INDIRECT_TI  = TIM_CCMR1_CC1S_1,
        IC_SEL_TRC          = TIM_CCMR1_CC1S,
    };
    enum EIT: uint32_t
    {
        IT_UPDATE   = TIM_DIER_UIE,
        IT_CC1      = TIM_DIER_CC1IE,
        IT_CC2      = TIM_DIER_CC2IE,
        IT_CC3      = TIM_DIER_CC3IE,
        IT_CC4      = TIM_DIER_CC4IE,
        IT_COM      = TIM_DIER_COMIE,
        IT_TRIGGER  = TIM_DIER_TIE,
        IT_BREAK    = TIM_DIER_BIE,
    };
    enum ETriggerSelection: uint32_t
    {
        ITR0        = 0x00000000U,
        ITR1        = 0x00000010U,
        ITR2        = 0x00000020U,
        ITR3        = 0x00000030U,
        TI1F_ED     = 0x00000040U,
        TI1_FP1     = 0x00000050U,
        TI2_FP2     = 0x00000060U,
        ETRF        = 0x00000070U,
        NONE        = 0x0000FFFFU,
    };
    enum ESlaveMode: uint32_t
    {
        SL_DISABLE      = 0x00000000U,
        SL_RESET        = 0x00000004U,
        SL_GATED        = 0x00000005U,
        SL_TRIGGER      = 0x00000006U,
        SL_EXTERNAL1    = 0x00000007U,
    };
    enum EChannelState: uint32_t
    {
        CCx_DISABLE = 0,
        CCx_ENABLE  = 1,
        CCxN_DISABLE= 0,
        CCxN_ENABLE = 4,
    };
    enum EEncoderMode: uint32_t
    {
        ENC_TI1     = TIM_SMCR_SMS_0,
        ENC_TI2     = TIM_SMCR_SMS_1,
        ENC_TI12    = (TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0),
    };
    enum EClockSource: uint32_t
    {
        CLK_ETRMODE2    = TIM_SMCR_ETPS_1,
        CLK_INTERNAL    = TIM_SMCR_ETPS_0,
        CLK_ITR0        = 0x00000000U,
        CLK_ITR1        = TIM_SMCR_TS_0,
        CLK_ITR2        = TIM_SMCR_TS_1,
        CLK_ITR3        = (TIM_SMCR_TS_0 | TIM_SMCR_TS_1),
        CLK_TI1ED       = TIM_SMCR_TS_2,
        CLK_TI1         = (TIM_SMCR_TS_0 | TIM_SMCR_TS_2),
        CLK_TI2         = (TIM_SMCR_TS_1 | TIM_SMCR_TS_2),
        CLK_ETRMODE1    = TIM_SMCR_TS,
    };
    enum EClockPolarity: uint32_t
    {
        CLK_INVERTED        = TIM_SMCR_ETP,
        CLK_NONINVERTED     = 0,
        CLK_RISING          = 0,
        CLK_FALLING         = TIM_CCER_CC1P,
        CLK_BOTHEDGE        = (TIM_CCER_CC1P | TIM_CCER_CC1NP),
    };

    typedef struct
    {
        EOCMode         mode;
        uint32_t        pulse;
        EOCPolarity     polarity;
        EOCNPolarity    polarity_neg;
        EOCIdleState    idle_state;
        EOCNIdleState   idle_state_neg;
        EOCFast         fast_mode;
    } OCInit_t;
    typedef struct
    {
        EOCMode         mode;
        uint32_t        pulse;
        EOCPolarity     polarity;
        EOCNPolarity    polarity_neg;
        EOCIdleState    idle_state;
        EOCNIdleState   idle_state_neg;
        EICPolarity     ic_polarity;
        EICSelection    ic_selection;
        uint32_t        ic_filter;
    } OnePulseInit_t;
    typedef struct
    {
        EICPolarity     polarity;
        EICSelection    selection;
        EICDiv          div;
        uint32_t        filter;
    } ICinit_t;
    typedef struct
    {
        EEncoderMode    mode;
        EICPolarity     ic1_polarity;
        EICSelection    ic1_selection;
        EICDiv          ic1_div;
        uint32_t        ic1_filter;
        EICPolarity     ic2_polarity;
        EICSelection    ic2_selection;
        EICDiv          ic2_div;
        uint32_t        ic2_filter;
    } EncoderInit_t;
    union TimerInit_t
    {
        OCInit_t        oc;
        OnePulseInit_t  one_pulse;
        ICinit_t        ic;
        EncoderInit_t   encoder;
    };
    typedef struct
    {
        uint32_t        prescaler;
        ECounterMode    counter_mode;
        uint32_t        period;
        EClkDiv         clk_div;
        uint32_t        repetition_counter;
    } TimerBaseInit_t;

    typedef void(*timer_callback_t)(STM32_TIM*,uint32_t);


    static void init_all();

    void init(TimerBaseInit_t* init);
    void deinit();
    void OC_config(TimerInit_t* init, uint32_t channel);

    void init_PWM(TimerBaseInit_t *init);
    void deinit_PWM();
    void PWM_config(TimerInit_t* init, uint32_t channel);

    void init_IC(TimerBaseInit_t *init);
    void deinit_IC();
    void IC_config(TimerInit_t* init, uint32_t channel);

    void init_one_pulse(TimerBaseInit_t *init, uint32_t one_pulse_mode);
    void deinit_one_pulse();
    void one_pulse_config(TimerInit_t* init, uint32_t out_ch, uint32_t in_ch);

    void init_encoder(TimerBaseInit_t *init);
    void deinit_encoder();

    inline void set_cb_capture(timer_callback_t val) { m_cb_capture = val; }
    inline void set_cb_period_elapsed(timer_callback_t val) { m_cb_period_elapsed = val; }
    inline void set_cb_break(timer_callback_t val) { m_cb_break = val; }
    inline void set_cb_trigger(timer_callback_t val) { m_cb_trigger = val; }
    inline void set_cb_commutation(timer_callback_t val) { m_cb_commutation = val; }

    inline void start() { enable(); }
    inline void stop() { disable(); }

    inline void start_IT() { enable_IT(EIT::IT_UPDATE); enable(); }
    inline void stop_IT() { disable_IT(EIT::IT_UPDATE); disable(); }

    inline void start_DMA() { /* TODO */ }
    inline void stop_DMA() { /* TODO */ }

    void start_OC(uint32_t channel);
    void stop_OC(uint32_t channel);

    void start_OC_IT(uint32_t channel);
    void stop_OC_IT(uint32_t channel);

    inline void start_OC_DMA() { /* TODO */ }
    inline void stop_OC_DMA() { /* TODO */ }

    inline void start_PWM(uint32_t channel) { start_OC(channel); }
    inline void stop_PWM(uint32_t channel) { stop_OC(channel); }

    inline void start_PWM_IT(uint32_t channel) { start_OC_IT(channel); }
    inline void stop_PWM_IT(uint32_t channel) { stop_OC_IT(channel); }

    inline void start_PWM_DMA() { /* TODO */ }
    inline void stop_PWM_DMA() { /* TODO */ }

    void start_IC(uint32_t channel);
    void stop_IC(uint32_t channel);

    void start_IC_IT(uint32_t channel);
    void stop_IC_IT(uint32_t channel);

    inline void start_IC_DMA() { /* TODO */ }
    inline void stop_IC_DMA() { /* TODO */ }

    void start_OP();
    void stop_OP();

    void start_OP_IT();
    void stop_OP_IT();

    void start_encoder(uint32_t channel);
    void stop_encoder(uint32_t channel);

    void start_encoder_IT(uint32_t channel);
    void stop_encoder_IT(uint32_t channel);

    inline void start_encoder_DMA() { /* TODO */ }
    inline void stop_encoder_DMA() { /* TODO */ }

    inline void generate_event(uint32_t source) { m_inst->EGR = source; }

    inline uint32_t get_value() { return m_inst->CNT; }
    inline void set_value(uint32_t val) { m_inst->CNT = val; }

    uint32_t get_clock();

    void IRQ_handler();

private:
    TIM_TypeDef*m_inst;
    uint32_t    m_lock;
    //STM32_DMA*  m_dma[7];
    EState      m_state;
    timer_callback_t    m_cb_capture;
    timer_callback_t    m_cb_period_elapsed;
    timer_callback_t    m_cb_break;
    timer_callback_t    m_cb_trigger;
    timer_callback_t    m_cb_commutation;
   /* // parameters
    uint32_t        m_prescaler;
    ECounterMode    m_counter_mode;
    uint32_t        m_period;
    EClkDiv         m_clk_div;
    uint32_t        m_rep_cnt;
    TimerInit_t     m_init;
    // clock
    EClockSource    m_clk_source;
    EClockPolarity  m_clk_polarity;*/

    void init_cb();
    void set_config(TimerBaseInit_t* init);

    void set_config_OC1(TimerInit_t *init);
    void set_config_OC2(TimerInit_t *init);
    void set_config_OC3(TimerInit_t *init);
    void set_config_OC4(TimerInit_t *init);

    void set_config_TI1(TimerInit_t *init);
    void set_config_TI2(TimerInit_t *init);
    void set_config_TI3(TimerInit_t *init);
    void set_config_TI4(TimerInit_t *init);

    void CCx_channel_cmd(uint32_t channel, uint32_t state);

    inline void enable_IT(uint32_t val) { m_inst->DIER |= val; }
    inline void disable_IT(uint32_t val) { m_inst->DIER &= ~val; }

    ENDIS_REG_FLAG_NAME(MOE, m_inst->BDTR, TIM_BDTR_MOE)

    ENDIS_REG_FLAG_NAME(OPM, m_inst->CR1, TIM_CR1_OPM)
    inline uint32_t get_CR1() { return m_inst->CR1; }
    inline void set_CR1(uint32_t val) { m_inst->CR1 |= val; }
    inline void enable() { m_inst->CR1 |= TIM_CR1_CEN; }
    inline void disable()
        { if ((m_inst->CCER & (TIM_CCER_CCxE_MASK|TIM_CCER_CCxNE_MASK)) == 0)
            m_inst->CR1 &= ~TIM_CR1_CEN; }

    inline uint32_t get_CR2() { return m_inst->CR2; }
    inline void set_CR2(uint32_t val) { m_inst->CR2 = val; }

    ENDIS_REG_FLAG_NAME(SMS, m_inst->SMCR, TIM_SMCR_SMS)
    inline uint32_t get_SMCR() { return m_inst->SMCR; }
    inline void set_SMCR(uint32_t val) { m_inst->SMCR = val; }
    inline void set_xC1_trigger_source(uint32_t val)
        { m_inst->SMCR &= ~TIM_SMCR_TS; m_inst->SMCR |= val; }
    inline void set_slave_mode(uint32_t val)
        { m_inst->SMCR &= ~TIM_SMCR_SMS; m_inst->SMCR |= val; }

    inline void set_auto_reload(uint32_t val) { m_inst->ARR = val; }
    inline void set_prescaler(uint32_t val) { m_inst->PSC = val; }
    inline void set_repetition(uint32_t val) { m_inst->RCR = val; }

    inline uint32_t get_CCMR1() { return m_inst->CCMR1; }
    inline void set_CCMR1(uint32_t val) { m_inst->CCMR1 = val; }
    ENDIS_REG_FLAG_NAME(preload_OC1, m_inst->CCMR1, TIM_CCMR1_OC1PE)
    ENDIS_REG_FLAG_NAME(preload_OC2, m_inst->CCMR1, TIM_CCMR1_OC2PE)
    inline void set_xC1_fast_mode(uint32_t val)
        { m_inst->CCMR1 &= ~TIM_CCMR1_OC1FE; m_inst->CCMR1 |= val; }
    inline void set_xC2_fast_mode(uint32_t val)
        { m_inst->CCMR1 &= ~TIM_CCMR1_OC2FE; m_inst->CCMR1 |= (val << 8); }
    inline void set_xC1_prescaler(uint32_t val)
        { m_inst->CCMR1 &= ~TIM_CCMR1_IC1PSC; m_inst->CCMR1 |= val; }
    inline void set_xC2_prescaler(uint32_t val)
        { m_inst->CCMR1 &= ~TIM_CCMR1_IC2PSC; m_inst->CCMR1 |= (val << 8); }
    inline void set_IC1_filter(uint32_t val)
        { m_inst->CCMR1 &= ~TIM_CCMR1_IC1F; m_inst->CCMR1 |= ((val << 4) & TIM_CCMR1_IC1F); }
    inline void set_IC2_filter(uint32_t val)
        { m_inst->CCMR1 &= ~TIM_CCMR1_IC2F; m_inst->CCMR1 |= ((val << 12) & TIM_CCMR1_IC2F); }
    inline void set_IC3_filter(uint32_t val)
        { m_inst->CCMR1 &= ~TIM_CCMR2_IC3F; m_inst->CCMR2 |= ((val << 4) & TIM_CCMR2_IC3F); }
    inline void set_IC4_filter(uint32_t val)
        { m_inst->CCMR1 &= ~TIM_CCMR2_IC4F; m_inst->CCMR2 |= ((val << 12) & TIM_CCMR2_IC4F); }

    inline uint32_t get_CCMR2() { return m_inst->CCMR2; }
    inline void set_CCMR2(uint32_t val) { m_inst->CCMR2 = val; }
    ENDIS_REG_FLAG_NAME(preload_OC3, m_inst->CCMR2, TIM_CCMR2_OC3PE)
    ENDIS_REG_FLAG_NAME(preload_OC4, m_inst->CCMR2, TIM_CCMR2_OC4PE)
    inline void set_xC3_fast_mode(uint32_t val)
        { m_inst->CCMR1 &= ~TIM_CCMR2_OC3FE; m_inst->CCMR2 |= val; }
    inline void set_xC4_fast_mode(uint32_t val)
        { m_inst->CCMR1 &= ~TIM_CCMR2_OC4FE; m_inst->CCMR2 |= (val << 8); }
    inline void set_xC3_prescaler(uint32_t val)
        { m_inst->CCMR2 &= ~TIM_CCMR2_IC3PSC; m_inst->CCMR2 |= val; }
    inline void set_xC4_prescaler(uint32_t val)
        { m_inst->CCMR2 &= ~TIM_CCMR2_IC4PSC; m_inst->CCMR2 |= (val << 8); }

    inline uint32_t get_CCER() { return m_inst->CCER; }
    inline void set_CCER(uint32_t val) { m_inst->CCER = val; }
    ENDIS_REG_FLAG_NAME(ch1, m_inst->CCER, TIM_CCER_CC1E)
    ENDIS_REG_FLAG_NAME(ch2, m_inst->CCER, TIM_CCER_CC2E)
    ENDIS_REG_FLAG_NAME(ch3, m_inst->CCER, TIM_CCER_CC3E)
    ENDIS_REG_FLAG_NAME(ch4, m_inst->CCER, TIM_CCER_CC4E)
    inline void reset_IC1_polarity() { m_inst->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC1NP); }
    inline void reset_IC2_polarity() { m_inst->CCER &= ~(TIM_CCER_CC2P | TIM_CCER_CC2NP); }
    inline void reset_IC3_polarity() { m_inst->CCER &= ~(TIM_CCER_CC3P | TIM_CCER_CC3NP); }
    inline void reset_IC4_polarity() { m_inst->CCER &= ~(TIM_CCER_CC4P | TIM_CCER_CC4NP); }
    inline void set_IC1_polarity(uint32_t val) { m_inst->CCER |= val; }
    inline void set_IC2_polarity(uint32_t val) { m_inst->CCER |= (val << 4); }
    inline void set_IC3_polarity(uint32_t val) { m_inst->CCER |= (val << 8); }
    inline void set_IC4_polarity(uint32_t val) { m_inst->CCER |= (val << 12); }

    inline void set_capture_compare_1(uint32_t val) { m_inst->CCR1 = val; }
    inline void set_capture_compare_2(uint32_t val) { m_inst->CCR2 = val; }
    inline void set_capture_compare_3(uint32_t val) { m_inst->CCR3 = val; }
    inline void set_capture_compare_4(uint32_t val) { m_inst->CCR4 = val; }

    inline uint32_t get_IT_sources() { return m_inst->DIER; }
    inline bool is_IT_source(uint32_t mask) { return ((m_inst->DIER & mask) == mask) ? true : false; }

    inline void clear_IT(uint32_t mask) { m_inst->SR = ~mask; }
    inline uint32_t get_flags() { return m_inst->SR; }

    inline bool get_flag_update() { return (m_inst->SR & TIM_SR_UIF) != RESET; }
    inline bool get_flag_CC1() { return (m_inst->SR & TIM_SR_CC1IF) != RESET; }
    inline bool get_flag_CC2() { return (m_inst->SR & TIM_SR_CC2IF) != RESET; }
    inline bool get_flag_CC3() { return (m_inst->SR & TIM_SR_CC3IF) != RESET; }
    inline bool get_flag_CC4() { return (m_inst->SR & TIM_SR_CC4IF) != RESET; }
    inline bool get_flag_com() { return (m_inst->SR & TIM_SR_COMIF) != RESET; }
    inline bool get_flag_trigger() { return (m_inst->SR & TIM_SR_TIF) != RESET; }
    inline bool get_flag_break() { return (m_inst->SR & TIM_SR_BIF) != RESET; }
    inline bool get_flag_CC1OF() { return (m_inst->SR & TIM_SR_CC1OF) != RESET; }
    inline bool get_flag_CC2OF() { return (m_inst->SR & TIM_SR_CC1OF) != RESET; }
    inline bool get_flag_CC3OF() { return (m_inst->SR & TIM_SR_CC1OF) != RESET; }
    inline bool get_flag_CC4OF() { return (m_inst->SR & TIM_SR_CC1OF) != RESET; }
};

extern STM32_TIM tim1;
extern STM32_TIM tim2;
extern STM32_TIM tim3;
extern STM32_TIM tim4;
extern STM32_TIM tim5;
extern STM32_TIM tim6;
extern STM32_TIM tim7;
extern STM32_TIM tim8;
extern STM32_TIM tim9;
extern STM32_TIM tim10;
extern STM32_TIM tim11;
extern STM32_TIM tim12;
extern STM32_TIM tim13;
extern STM32_TIM tim14;

#endif //STM32_TIM_H
