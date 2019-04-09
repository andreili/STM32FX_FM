#include "stm32_tim.h"

void STM32_TIM::init_all()
{
    #ifdef STM32_USE_TIM1
    tim1.m_inst = TIM1;
    tim1.init_cb();
    #endif
    #ifdef STM32_USE_TIM2
    tim2.m_inst = TIM2;
    tim2.init_cb();
    #endif
    #ifdef STM32_USE_TIM3
    tim3.m_inst = TIM3;
    tim3.init_cb();
    #endif
    #ifdef STM32_USE_TIM4
    tim4.m_inst = TIM4;
    tim4.init_cb();
    #endif
    #ifdef STM32_USE_TIM5
    tim5.m_inst = TIM5;
    tim5.init_cb();
    #endif
    #ifdef STM32_USE_TIM6
    tim6.m_inst = TIM6;
    tim6.init_cb();
    #endif
    #ifdef STM32_USE_TIM7
    tim7.m_inst = TIM7;
    tim7.init_cb();
    #endif
    #ifdef STM32_USE_TIM8
    tim8.m_inst = TIM8;
    tim8.init_cb();
    #endif
    #ifdef STM32_USE_TIM9
    tim9.m_inst = TIM9;
    tim9.init_cb();
    #endif
    #ifdef STM32_USE_TIM10
    tim11.m_inst = TIM10;
    tim10.init_cb();
    #endif
    #ifdef STM32_USE_TIM11
    tim10.m_inst = TIM11;
    tim11.init_cb();
    #endif
    #ifdef STM32_USE_TIM12
    tim12.m_inst = TIM12;
    tim12.init_cb();
    #endif
    #ifdef STM32_USE_TIM13
    tim13.m_inst = TIM13;
    tim13.init_cb();
    #endif
    #ifdef STM32_USE_TIM14
    tim14.m_inst = TIM14;
    tim14.init_cb();
    #endif
}

void STM32_TIM::init(TimerBaseInit_t *init)
{
    //TODO: GPIO, CLOCK, NVIC

    set_config(init);
}

void STM32_TIM::deinit()
{
    disable();
    // TODO: GPIO, CLOCK, NVIC
}

void STM32_TIM::OC_config(TimerInit_t *init, uint32_t channel)
{
    switch (channel)
    {
    case EChannel::CH_1:
        set_config_OC1(init);
        break;
    case EChannel::CH_2:
        set_config_OC2(init);
        break;
    case EChannel::CH_3:
        set_config_OC3(init);
        break;
    case EChannel::CH_4:
        set_config_OC4(init);
        break;
    }
}

void STM32_TIM::init_PWM(TimerBaseInit_t *init)
{
    //TODO: GPIO, CLOCK, NVIC

    set_config(init);
}

void STM32_TIM::deinit_PWM()
{
    disable();
    // TODO: GPIO, CLOCK, NVIC
}

void STM32_TIM::PWM_config(TimerInit_t* init, uint32_t channel)
{
    switch (channel)
    {
    case EChannel::CH_1:
        set_config_OC1(init);
        enable_preload_OC1();
        set_xC1_fast_mode(init->oc.fast_mode);
        break;
    case EChannel::CH_2:
        set_config_OC2(init);
        enable_preload_OC2();
        set_xC2_fast_mode(init->oc.fast_mode);
        break;
    case EChannel::CH_3:
        set_config_OC3(init);
        enable_preload_OC3();
        set_xC3_fast_mode(init->oc.fast_mode);
        break;
    case EChannel::CH_4:
        set_config_OC4(init);
        enable_preload_OC4();
        set_xC4_fast_mode(init->oc.fast_mode);
        break;
    }
}

void STM32_TIM::init_IC(TimerBaseInit_t *init)
{
    //TODO: GPIO, CLOCK, NVIC

    set_config(init);
}

void STM32_TIM::deinit_IC()
{
    disable();
    // TODO: GPIO, CLOCK, NVIC
}

void STM32_TIM::IC_config(TimerInit_t* init, uint32_t channel)
{
    switch (channel)
    {
    case EChannel::CH_1:
        set_config_TI1(init);
        set_xC1_prescaler(init->ic.div);
        break;
    case EChannel::CH_2:
        set_config_TI2(init);
        set_xC2_prescaler(init->ic.div);
        break;
    case EChannel::CH_3:
        set_config_TI3(init);
        set_xC3_prescaler(init->ic.div);
        break;
    case EChannel::CH_4:
        set_config_TI4(init);
        set_xC4_prescaler(init->ic.div);
        break;
    }
}

void STM32_TIM::init_one_pulse(TimerBaseInit_t *init, uint32_t one_pulse_mode)
{
    //TODO: GPIO, CLOCK, NVIC

    set_config(init);
    disable_OPM();
    set_CR1(one_pulse_mode);
}

void STM32_TIM::deinit_one_pulse()
{
    disable();
    // TODO: GPIO, CLOCK, NVIC
}

void STM32_TIM::one_pulse_config(TimerInit_t* init, uint32_t out_ch, uint32_t in_ch)
{
    if (out_ch != in_ch)
    {
        switch (out_ch)
        {
        case EChannel::CH_1:
            set_config_OC1(init);
            break;
        case EChannel::CH_2:
            set_config_OC2(init);
            break;
        }
        switch (in_ch)
        {
        case EChannel::CH_1:
            set_config_TI1(init);
            set_xC1_prescaler(0);
            set_xC1_trigger_source(ETriggerSelection::TI1_FP1);
            set_slave_mode(ESlaveMode::SL_TRIGGER);
            break;
        case EChannel::CH_2:
            set_config_TI2(init);
            set_xC2_prescaler(0);
            set_xC1_trigger_source(ETriggerSelection::TI2_FP2);
            set_slave_mode(ESlaveMode::SL_TRIGGER);
            break;
        }
    }
}

void STM32_TIM::init_encoder(TimerBaseInit_t *init)
{
    // TODO: GPIO, CLOCK, NVIC

    disable_SMS();
    set_config(init);

    //TODO
    /*uint32_t tmp_smcr = get_SMCR();
    uint32_t tmp_ccmr1 = get_CCMR1();
    uint32_t tmp_ccer = get_CCER();

    tmp_smcr |= */
}

void STM32_TIM::deinit_encoder()
{
    disable();
    // TODO: GPIO, CLOCK, NVIC
}

void STM32_TIM::start_OC(uint32_t channel)
{
    CCx_channel_cmd(channel, EChannelState::CCx_ENABLE);
    if (IS_TIM_ADVANCED_INSTANCE(m_inst) != RESET)
        enable_MOE();
    enable();
}

void STM32_TIM::stop_OC(uint32_t channel)
{
    CCx_channel_cmd(channel, EChannelState::CCx_DISABLE);
    if (IS_TIM_ADVANCED_INSTANCE(m_inst) != RESET)
        disable_MOE();
    disable();
}

void STM32_TIM::start_OC_IT(uint32_t channel)
{
    switch (channel)
    {
    case EChannel::CH_1:
        enable_IT(EIT::IT_CC1);
        break;
    case EChannel::CH_2:
        enable_IT(EIT::IT_CC2);
        break;
    case EChannel::CH_3:
        enable_IT(EIT::IT_CC3);
        break;
    case EChannel::CH_4:
        enable_IT(EIT::IT_CC4);
        break;
    }
    start_OC(channel);
}

void STM32_TIM::stop_OC_IT(uint32_t channel)
{
    switch (channel)
    {
    case EChannel::CH_1:
        disable_IT(EIT::IT_CC1);
        break;
    case EChannel::CH_2:
        disable_IT(EIT::IT_CC2);
        break;
    case EChannel::CH_3:
        disable_IT(EIT::IT_CC3);
        break;
    case EChannel::CH_4:
        disable_IT(EIT::IT_CC4);
        break;
    }
    stop_OC(channel);
}

void STM32_TIM::start_IC(uint32_t channel)
{
    CCx_channel_cmd(channel, EChannelState::CCx_ENABLE);
    enable();
}

void STM32_TIM::stop_IC(uint32_t channel)
{
    CCx_channel_cmd(channel, EChannelState::CCx_DISABLE);
    disable();
}

void STM32_TIM::start_IC_IT(uint32_t channel)
{
    switch (channel)
    {
    case EChannel::CH_1:
        enable_IT(EIT::IT_CC1);
        break;
    case EChannel::CH_2:
        enable_IT(EIT::IT_CC2);
        break;
    case EChannel::CH_3:
        enable_IT(EIT::IT_CC3);
        break;
    case EChannel::CH_4:
        enable_IT(EIT::IT_CC4);
        break;
    }
    start_IC(channel);
}

void STM32_TIM::stop_IC_IT(uint32_t channel)
{
    switch (channel)
    {
    case EChannel::CH_1:
        disable_IT(EIT::IT_CC1);
        break;
    case EChannel::CH_2:
        disable_IT(EIT::IT_CC2);
        break;
    case EChannel::CH_3:
        disable_IT(EIT::IT_CC3);
        break;
    case EChannel::CH_4:
        disable_IT(EIT::IT_CC4);
        break;
    }
    stop_IC(channel);
}

void STM32_TIM::start_OP()
{
    CCx_channel_cmd(EChannel::CH_1, EChannelState::CCx_ENABLE);
    CCx_channel_cmd(EChannel::CH_2, EChannelState::CCx_ENABLE);
    if (IS_TIM_ADVANCED_INSTANCE(m_inst) != RESET)
        enable_MOE();
}

void STM32_TIM::stop_OP()
{
    CCx_channel_cmd(EChannel::CH_1, EChannelState::CCx_DISABLE);
    CCx_channel_cmd(EChannel::CH_2, EChannelState::CCx_DISABLE);
    if (IS_TIM_ADVANCED_INSTANCE(m_inst) != RESET)
        disable_MOE();
    disable();
}

void STM32_TIM::start_OP_IT()
{
    enable_IT(EIT::IT_CC1);
    enable_IT(EIT::IT_CC2);
    start_OP();
}

void STM32_TIM::stop_OP_IT()
{
    disable_IT(EIT::IT_CC1);
    disable_IT(EIT::IT_CC2);
    stop_OP();
}

void STM32_TIM::start_encoder(uint32_t channel)
{
    switch (channel)
    {
    case EChannel::CH_1:
        CCx_channel_cmd(EChannel::CH_1, EChannelState::CCx_ENABLE);
        break;
    case EChannel::CH_2:
        CCx_channel_cmd(EChannel::CH_2, EChannelState::CCx_ENABLE);
        break;
    default:
        CCx_channel_cmd(EChannel::CH_1, EChannelState::CCx_ENABLE);
        CCx_channel_cmd(EChannel::CH_2, EChannelState::CCx_ENABLE);
        break;
    }
    enable();
}

void STM32_TIM::stop_encoder(uint32_t channel)
{
    switch (channel)
    {
    case EChannel::CH_1:
        CCx_channel_cmd(EChannel::CH_1, EChannelState::CCx_DISABLE);
        break;
    case EChannel::CH_2:
        CCx_channel_cmd(EChannel::CH_2, EChannelState::CCx_DISABLE);
        break;
    default:
        CCx_channel_cmd(EChannel::CH_1, EChannelState::CCx_DISABLE);
        CCx_channel_cmd(EChannel::CH_2, EChannelState::CCx_DISABLE);
        break;
    }
    disable();
}

void STM32_TIM::start_encoder_IT(uint32_t channel)
{
    switch (channel)
    {
    case EChannel::CH_1:
        CCx_channel_cmd(EChannel::CH_1, EChannelState::CCx_ENABLE);
        enable_IT(EIT::IT_CC1);
        break;
    case EChannel::CH_2:
        CCx_channel_cmd(EChannel::CH_2, EChannelState::CCx_ENABLE);
        enable_IT(EIT::IT_CC2);
        break;
    default:
        CCx_channel_cmd(EChannel::CH_1, EChannelState::CCx_ENABLE);
        CCx_channel_cmd(EChannel::CH_2, EChannelState::CCx_ENABLE);
        enable_IT(EIT::IT_CC1);
        enable_IT(EIT::IT_CC2);
        break;
    }
    enable();
}

void STM32_TIM::stop_encoder_IT(uint32_t channel)
{
    switch (channel)
    {
    case EChannel::CH_1:
        CCx_channel_cmd(EChannel::CH_1, EChannelState::CCx_DISABLE);
        disable_IT(EIT::IT_CC1);
        break;
    case EChannel::CH_2:
        CCx_channel_cmd(EChannel::CH_2, EChannelState::CCx_DISABLE);
        disable_IT(EIT::IT_CC2);
        break;
    default:
        CCx_channel_cmd(EChannel::CH_1, EChannelState::CCx_DISABLE);
        CCx_channel_cmd(EChannel::CH_2, EChannelState::CCx_DISABLE);
        disable_IT(EIT::IT_CC1);
        disable_IT(EIT::IT_CC2);
        break;
    }
    disable();
}

void STM32_TIM::IRQ_handler()
{
    uint32_t it_all = get_IT_sources();
    if (get_flag_CC1() && ((it_all & EIT::IT_CC1) != 0))
    {
        clear_IT(EIT::IT_CC1);
        if (m_cb_capture != nullptr)
            m_cb_capture(this, EActiveChannel::ACT_CH_1);
    }

    if (get_flag_CC2() && ((it_all & EIT::IT_CC2) != 0))
    {
        clear_IT(EIT::IT_CC2);
        if (m_cb_capture != nullptr)
            m_cb_capture(this, EActiveChannel::ACT_CH_2);
    }

    if (get_flag_CC3() && ((it_all & EIT::IT_CC3) != 0))
    {
        clear_IT(EIT::IT_CC3);
        if (m_cb_capture != nullptr)
            m_cb_capture(this, EActiveChannel::ACT_CH_3);
    }

    if (get_flag_CC4() && ((it_all & EIT::IT_CC4) != 0))
    {
        clear_IT(EIT::IT_CC4);
        if (m_cb_capture != nullptr)
            m_cb_capture(this, EActiveChannel::ACT_CH_4);
    }

    if (get_flag_update() && ((it_all & EIT::IT_UPDATE) != 0))
    {
        clear_IT(EIT::IT_UPDATE);
        if (m_cb_period_elapsed != nullptr)
            m_cb_period_elapsed(this, 0);
    }

    if (get_flag_break() && ((it_all & EIT::IT_BREAK) != 0))
    {
        clear_IT(EIT::IT_BREAK);
        if (m_cb_break != nullptr)
            m_cb_break(this, 0);
    }

    if (get_flag_trigger() && ((it_all & EIT::IT_TRIGGER) != 0))
    {
        clear_IT(EIT::IT_TRIGGER);
        if (m_cb_trigger != nullptr)
            m_cb_trigger(this, 0);
    }

    if (get_flag_com() && ((it_all & EIT::IT_COM) != 0))
    {
        clear_IT(EIT::IT_COM);
        if (m_cb_commutation != nullptr)
            m_cb_commutation(this, 0);
    }
}

void STM32_TIM::init_cb()
{
    m_cb_capture = nullptr;
    m_cb_period_elapsed = nullptr;
    m_cb_break = nullptr;
    m_cb_trigger = nullptr;
    m_cb_commutation = nullptr;
}

void STM32_TIM::set_config(TimerBaseInit_t *init)
{
    uint32_t tmpcr1 = get_CR1();
    if (IS_TIM_CC3_INSTANCE(m_inst))
    {
        tmpcr1 &= ~(TIM_CR1_DIR | TIM_CR1_CMS);
        tmpcr1 |= init->counter_mode;
    }
    if (IS_TIM_CC1_INSTANCE(m_inst))
    {
        tmpcr1 &= ~TIM_CR1_CKD;
        tmpcr1 |= init->clk_div;
    }
    set_CR1(tmpcr1);
    set_auto_reload(init->period);
    set_prescaler(init->prescaler);
    if (IS_TIM_ADVANCED_INSTANCE(m_inst))
        set_repetition(init->repetition_counter);
    generate_event(TIM_EGR_UG);
}

void STM32_TIM::set_config_OC1(TimerInit_t *init)
{
    disable_ch1();
    uint32_t tmpccer = get_CCER();
    uint32_t tmpcr2 = get_CR2();
    uint32_t tmpccmrx = get_CCMR1();

    /* Reset the Output Compare Mode Bits */
    tmpccmrx &= ~TIM_CCMR1_OC1M;
    tmpccmrx &= ~TIM_CCMR1_CC1S;
    /* Select the Output Compare Mode */
    tmpccmrx |= init->oc.mode;

    /* Reset the Output Polarity level */
    tmpccer &= ~TIM_CCER_CC1P;
    /* Set the Output Compare Polarity */
    tmpccer |= init->oc.polarity;


    if (IS_TIM_ADVANCED_INSTANCE(m_inst) != RESET)
    {
        /* Reset the Output N Polarity level */
        tmpccer &= ~TIM_CCER_CC1NP;
        /* Set the Output N Polarity */
        tmpccer |= init->oc.polarity_neg;
        /* Reset the Output N State */
        tmpccer &= ~TIM_CCER_CC1NE;

        /* Reset the Output Compare and Output Compare N IDLE State */
        tmpcr2 &= ~TIM_CR2_OIS1;
        tmpcr2 &= ~TIM_CR2_OIS1N;
        /* Set the Output Idle state */
        tmpcr2 |= init->oc.idle_state;
        /* Set the Output N Idle state */
        tmpcr2 |= init->oc.idle_state_neg;
    }
    set_CR2(tmpcr2);
    set_CCMR1(tmpccmrx);
    set_capture_compare_1(init->oc.pulse);
    set_CCER(tmpccer);
}

void STM32_TIM::set_config_OC2(TimerInit_t *init)
{
    disable_ch2();
    uint32_t tmpccer = get_CCER();
    uint32_t tmpcr2 = get_CR2();
    uint32_t tmpccmrx = get_CCMR1();

    /* Reset the Output Compare Mode Bits */
    tmpccmrx &= ~TIM_CCMR1_OC2M;
    tmpccmrx &= ~TIM_CCMR1_CC2S;
    /* Select the Output Compare Mode */
    tmpccmrx |= (init->oc.mode << 8);

    /* Reset the Output Polarity level */
    tmpccer &= ~TIM_CCER_CC2P;
    /* Set the Output Compare Polarity */
    tmpccer |= (init->oc.polarity << 4);


    if (IS_TIM_ADVANCED_INSTANCE(m_inst) != RESET)
    {
        /* Reset the Output N Polarity level */
        tmpccer &= ~TIM_CCER_CC2NP;
        /* Set the Output N Polarity */
        tmpccer |= (init->oc.polarity_neg << 4);
        /* Reset the Output N State */
        tmpccer &= ~TIM_CCER_CC2NE;

        /* Reset the Output Compare and Output Compare N IDLE State */
        tmpcr2 &= ~TIM_CR2_OIS2;
        tmpcr2 &= ~TIM_CR2_OIS2N;
        /* Set the Output Idle state */
        tmpcr2 |= (init->oc.idle_state << 2);
        /* Set the Output N Idle state */
        tmpcr2 |= (init->oc.idle_state_neg << 2);
    }
    set_CR2(tmpcr2);
    set_CCMR1(tmpccmrx);
    set_capture_compare_2(init->oc.pulse);
    set_CCER(tmpccer);
}

void STM32_TIM::set_config_OC3(TimerInit_t *init)
{
    disable_ch3();
    uint32_t tmpccer = get_CCER();
    uint32_t tmpcr2 = get_CR2();
    uint32_t tmpccmrx = get_CCMR2();

    /* Reset the Output Compare Mode Bits */
    tmpccmrx &= ~TIM_CCMR2_OC3M;
    tmpccmrx &= ~TIM_CCMR2_CC3S;
    /* Select the Output Compare Mode */
    tmpccmrx |= init->oc.mode;

    /* Reset the Output Polarity level */
    tmpccer &= ~TIM_CCER_CC1P;
    /* Set the Output Compare Polarity */
    tmpccer |= (init->oc.polarity << 8);


    if (IS_TIM_ADVANCED_INSTANCE(m_inst) != RESET)
    {
        /* Reset the Output N Polarity level */
        tmpccer &= ~TIM_CCER_CC3NP;
        /* Set the Output N Polarity */
        tmpccer |= (init->oc.polarity_neg << 8);
        /* Reset the Output N State */
        tmpccer &= ~TIM_CCER_CC3NE;

        /* Reset the Output Compare and Output Compare N IDLE State */
        tmpcr2 &= ~TIM_CR2_OIS3;
        tmpcr2 &= ~TIM_CR2_OIS3N;
        /* Set the Output Idle state */
        tmpcr2 |= (init->oc.idle_state << 4);
        /* Set the Output N Idle state */
        tmpcr2 |= (init->oc.idle_state_neg << 4);
    }
    set_CR2(tmpcr2);
    set_CCMR2(tmpccmrx);
    set_capture_compare_3(init->oc.pulse);
    set_CCER(tmpccer);
}

void STM32_TIM::set_config_OC4(TimerInit_t *init)
{
    disable_ch4();
    uint32_t tmpccer = get_CCER();
    uint32_t tmpcr2 = get_CR2();
    uint32_t tmpccmrx = get_CCMR2();

    /* Reset the Output Compare Mode Bits */
    tmpccmrx &= ~TIM_CCMR2_OC4M;
    tmpccmrx &= ~TIM_CCMR2_CC4S;
    /* Select the Output Compare Mode */
    tmpccmrx |= (init->oc.mode << 8);

    /* Reset the Output Polarity level */
    tmpccer &= ~TIM_CCER_CC4P;
    /* Set the Output Compare Polarity */
    tmpccer |= (init->oc.polarity << 12);


    if (IS_TIM_ADVANCED_INSTANCE(m_inst) != RESET)
    {
        /* Reset the Output Compare IDLE State */
        tmpcr2 &= ~TIM_CR2_OIS4;
        /* Set the Output Idle state */
        tmpcr2 |= (init->oc.idle_state << 6);
    }
    set_CR2(tmpcr2);
    set_CCMR2(tmpccmrx);
    set_capture_compare_4(init->oc.pulse);
    set_CCER(tmpccer);
}

void STM32_TIM::set_config_TI1(TimerInit_t *init)
{
    disable_ch1();
    uint32_t tmpccer = get_CCER();
    uint32_t tmpccmrx = get_CCMR1();

    tmpccmrx &= ~TIM_CCMR1_CC1S;
    if (IS_TIM_CC2_INSTANCE(m_inst))
        tmpccmrx |= init->ic.selection;
    else
        tmpccmrx |= EICSelection::IC_SEL_DIRECT_TI;

    set_IC1_filter(init->ic.filter);
    reset_IC1_polarity();
    set_IC1_polarity(init->ic.polarity);
    set_CCMR1(tmpccmrx);
    set_CCER(tmpccer);
}

void STM32_TIM::set_config_TI2(TimerInit_t *init)
{
    disable_ch2();
    uint32_t tmpccer = get_CCER();
    uint32_t tmpccmrx = get_CCMR1();

    tmpccmrx &= ~TIM_CCMR1_CC2S;
    tmpccmrx |= (init->ic.selection << 8);

    set_IC2_filter(init->ic.filter);
    reset_IC2_polarity();
    set_IC2_polarity(init->ic.polarity);
    set_CCMR1(tmpccmrx);
    set_CCER(tmpccer);
}

void STM32_TIM::set_config_TI3(TimerInit_t *init)
{
    disable_ch3();
    uint32_t tmpccer = get_CCER();
    uint32_t tmpccmrx = get_CCMR2();

    tmpccmrx &= ~TIM_CCMR2_CC3S;
    tmpccmrx |= init->ic.selection;

    set_IC3_filter(init->ic.filter);
    reset_IC3_polarity();
    set_IC3_polarity(init->ic.polarity);
    set_CCMR2(tmpccmrx);
    set_CCER(tmpccer);
}

void STM32_TIM::set_config_TI4(TimerInit_t *init)
{
    disable_ch4();
    uint32_t tmpccer = get_CCER();
    uint32_t tmpccmrx = get_CCMR2();

    tmpccmrx &= ~TIM_CCMR2_CC4S;
    tmpccmrx |= (init->ic.selection << 8);

    set_IC4_filter(init->ic.filter);
    reset_IC4_polarity();
    set_IC4_polarity(init->ic.polarity);
    set_CCMR2(tmpccmrx);
    set_CCER(tmpccer);
}

void STM32_TIM::CCx_channel_cmd(uint32_t channel, uint32_t state)
{
    m_inst->CCER &= ~(TIM_CCER_CC1E << channel);
    m_inst->CCER |= (state << channel);
}

#ifdef STM32_USE_TIM1
STM32_TIM tim1;
#endif
#ifdef STM32_USE_TIM2
STM32_TIM tim2;
#endif
#ifdef STM32_USE_TIM3
STM32_TIM tim3;
#endif
#ifdef STM32_USE_TIM4
STM32_TIM tim4;
#endif
#ifdef STM32_USE_TIM5
STM32_TIM tim5;
#endif
#ifdef STM32_USE_TIM6
STM32_TIM tim6;
#endif
#ifdef STM32_USE_TIM7
STM32_TIM tim7;
#endif
#ifdef STM32_USE_TIM8
STM32_TIM tim8;
#endif
#ifdef STM32_USE_TIM9
STM32_TIM tim9;
#endif
#ifdef STM32_USE_TIM10
STM32_TIM tim10;
#endif
#ifdef STM32_USE_TIM11
STM32_TIM tim11;
#endif
#ifdef STM32_USE_TIM12
STM32_TIM tim12;
#endif
#ifdef STM32_USE_TIM13
STM32_TIM tim13;
#endif

#ifdef STM32_USE_TIM14
STM32_TIM tim14;

void ISR::TIM8_TRG_COM_TIM14_IRQ()
{
    tim14.IRQ_handler();
}
#endif
