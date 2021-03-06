#include "stm32_uart.h"
#include <cstring>

#ifdef STM32_USE_UART

#define UART_BRR (F_CPU / BRATE)

#define UART_DISABLE() BIT_BAND_PER(m_uart->CR1, USART_CR1_UE) = 0
#define UART_ENABLE()  BIT_BAND_PER(m_uart->CR1, USART_CR1_UE) = 1

#define UART_STOPBITS_1                     ((uint32_t)0x00000000U)
#define UART_STOPBITS_2                     ((uint32_t)USART_CR2_STOP_1)

#define UART_WORDLENGTH_8B                  ((uint32_t)0x00000000U)
#define UART_WORDLENGTH_9B                  ((uint32_t)USART_CR1_M)

#define UART_PARITY_NONE                    ((uint32_t)0x00000000U)
#define UART_PARITY_EVEN                    ((uint32_t)USART_CR1_PCE)
#define UART_PARITY_ODD                     ((uint32_t)(USART_CR1_PCE | USART_CR1_PS)) 

#define UART_HWCONTROL_NONE                  ((uint32_t)0x00000000U)
#define UART_HWCONTROL_RTS                   ((uint32_t)USART_CR3_RTSE)
#define UART_HWCONTROL_CTS                   ((uint32_t)USART_CR3_CTSE)
#define UART_HWCONTROL_RTS_CTS               ((uint32_t)(USART_CR3_RTSE | USART_CR3_CTSE))

#define UART_MODE_RX                        ((uint32_t)USART_CR1_RE)
#define UART_MODE_TX                        ((uint32_t)USART_CR1_TE)
#define UART_MODE_TX_RX                     ((uint32_t)(USART_CR1_TE |USART_CR1_RE))

#define UART_OVERSAMPLING_16                    ((uint32_t)0x00000000U)
#define UART_OVERSAMPLING_8                     ((uint32_t)USART_CR1_OVER8)

void STM32_UART::init_all()
{
    #ifdef STM32_USE_UART1
    uart1.m_uart = USART1;
    uart1.m_busy = false;
    #endif
    #ifdef STM32_USE_UART2
    uart2.m_uart = USART2;
    uart2.m_busy = false;
    #endif
    #ifdef STM32_USE_UART3
    uart3.m_uart = USART3_;
    uart3.m_busy = false;
    #endif
    #ifdef STM32_USE_UART4
    uart4.m_uart = UART4;
    uart4.m_busy = false;
    #endif
    #ifdef STM32_USE_UART5
    uart5.m_uart = UART5;
    uart5.m_busy = false;
    #endif
    #ifdef STM32_USE_UART6
    uart6.m_uart = USART6;
    uart6.m_busy = false;
    #endif
    #ifdef STM32_USE_UART7
    uart7.m_uart = UART7;
    uart7.m_busy = false;
    #endif
    #ifdef STM32_USE_UART8
    uart8.m_uart = UART8;
    uart8.m_busy = false;
    #endif
}

void STM32_UART::init(uint32_t brate)
{
    // Clock enable
    switch (reinterpret_cast<uint32_t>(m_uart))
    {
    #ifdef STM32_USE_UART1
    case USART1_BASE:
        STM32::RCC::enable_clk_USART1();
        STM32::RCC::enable_clk_GPIOA();
        #if defined(STM32F1)
        gpiob.set_config(STM32_GPIO::PIN_9, STM32_GPIO::EMode::AF_PP, STM32_GPIO::EAF::NONE, STM32_GPIO::ESpeed::HIGH, STM32_GPIO::EPull::PULLUP);
        gpiob.set_config(STM32_GPIO::PIN_10, STM32_GPIO::EMode::INPUT, STM32_GPIO::EAF::NONE, STM32_GPIO::ESpeed::HIGH, GPIO_NOPULL);
        #elif defined(STM32F4)
        gpioa.set_config(STM32_GPIO::PIN_9|STM32_GPIO::PIN_10, STM32_GPIO::EMode::AF_PP, STM32_GPIO::EAF::AF7_USART1, STM32_GPIO::ESpeed::VERY_HIGH, STM32_GPIO::EPull::PULLUP);
        #endif
        BIT_BAND_PER(RCC_->APB2ENR, RCC_APB2ENR_USART1EN) = ENABLE;
        break;
    #endif
    #ifdef STM32_USE_UART2
    case USART2_BASE:
        STM32::RCC::enable_clk_USART1();
        STM32::RCC::enable_clk_GPIOA();
        #if defined(STM32F1)
        gpiob.set_config(STM32_GPIO::PIN_2, STM32_GPIO::EMode::AF_PP, STM32_GPIO::EAF::NONE, GPIO_SPEED_FREQ_HIGH, STM32_GPIO::EPull::PULLUP);
        gpiob.set_config(STM32_GPIO::PIN_3, STM32_GPIO::EMode::INPUT, STM32_GPIO::EAF::NONE, GPIO_SPEED_FREQ_HIGH, STM32_GPIO::EPull::NOPULL);
        #elif defined(STM32F4)
        gpioa.set_config(STM32_GPIO::PIN_2|STM32_GPIO::PIN_3, STM32_GPIO::EMode::AF_PP, STM32_GPIO::EAF::AF7_USART1, STM32_GPIO::ESpeed::VERY_HIGH, STM32_GPIO::EPull::PULLUP);
        #endif
        BIT_BAND_PER(RCC_->APB1ENR, RCC_APB1ENR_USART2EN) = ENABLE;
        break;
    #endif
    #ifdef STM32_USE_UART3
    case USART3_BASE:
        STM32::RCC::enable_clk_USART3();
        STM32::RCC::enable_clk_GPIOB();
        gpiob.set_config(STM32_GPIO::PIN_10|STM32_GPIO::PIN_11, STM32_GPIO::EMode::AF_PP, STM32_GPIO::EAF::AF7_USART3, STM32_GPIO::ESpeed::VERY_HIGH, STM32_GPIO::EPull::PULLUP);
        STM32::RCC::enable_clk_USART3();
        break;
    #endif
    #ifdef STM32_USE_UART4
    case UART4_BASE:
        STM32::RCC::enable_clk_UART4();
        break;
    #endif
    #ifdef STM32_USE_UART5
    case UART5_BASE:
        STM32::RCC::enable_clk_UART5();
        break;
    #endif
    #ifdef STM32_USE_UART6
    case USART6_BASE:
        STM32::RCC::enable_clk_USART6();
        STM32::RCC::enable_clk_GPIOC();
        gpioc.set_config(STM32_GPIO::PIN_6|STM32_GPIO::PIN_7, STM32_GPIO::EMode::AF_PP, STM32_GPIO::EAF::AF8_USART6, STM32_GPIO::ESpeed::VERY_HIGH, STM32_GPIO::EPull::PULLUP);
        BIT_BAND_PER(RCC_->APB2ENR, RCC_APB2ENR_USART6EN) = ENABLE;
        break;
    #endif
    #ifdef STM32_USE_UART7
    case UART7_BASE:
        STM32::RCC::enable_clk_UART7();
        break;
    #endif
    #ifdef STM32_USE_UART8
    case UART8_BASE:
        STM32::RCC::enable_clk_UART8();
        break;
    #endif
    }

    UART_DISABLE();

    set_config();
    set_baud_rate(brate);

    // UART
    m_uart->CR2 &= ~(USART_CR2_LINEN | USART_CR2_CLKEN);
    // USART
    //m_uart->CR2 &= ~(USART_CR2_LINEN);
    m_uart->CR3 &= ~(USART_CR3_SCEN | USART_CR3_HDSEL | USART_CR3_IREN);
    UART_ENABLE();
}

void STM32_UART::deinit()
{
    UART_DISABLE();
    // Clock disable
    switch (reinterpret_cast<uint32_t>(m_uart))
    {
    case USART1_BASE:
        STM32::RCC::disable_clk_USART1();
        break;
    case USART2_BASE:
        STM32::RCC::disable_clk_USART2();;
        break;
    case USART3_BASE:
        STM32::RCC::disable_clk_USART3();
        break;
        #ifdef UART4_BASE
    case UART4_BASE:
        STM32::RCC::disable_clk_UART4();
        break;
        #endif
        #ifdef UART5_BASE
    case UART5_BASE:
        STM32::RCC::disable_clk_UART5();
        break;
        #endif
        #ifdef UART6_BASE
    case USART6_BASE:
        STM32::RCC::disable_clk_USART6();
        break;
        #endif
#ifdef UART7_BASE
    case UART7_BASE:
        STM32::RCC::disable_clk_UART7();
        break;
#endif
#ifdef UART8_BASE
    case UART8_BASE:
        STM32::RCC::disable_clk_UART8();
        break;
#endif
    }

    m_uart->CR1 = 0;
    m_uart->CR2 = 0;
    m_uart->CR3 = 0;
}

#define UART_DIV_SAMPLING16(_PCLK_, _BAUD_)            (((_PCLK_)*25U)/(4U*(_BAUD_)))
#define UART_DIVMANT_SAMPLING16(_PCLK_, _BAUD_)        (UART_DIV_SAMPLING16((_PCLK_), (_BAUD_))/100U)
#define UART_DIVFRAQ_SAMPLING16(_PCLK_, _BAUD_)        (((UART_DIV_SAMPLING16((_PCLK_), (_BAUD_)) - (UART_DIVMANT_SAMPLING16((_PCLK_), (_BAUD_)) * 100U)) * 16U + 50U) / 100U)
#define UART_BRR_SAMPLING16(_PCLK_, _BAUD_)            (((UART_DIVMANT_SAMPLING16((_PCLK_), (_BAUD_)) << 4U) + \
                                                        (UART_DIVFRAQ_SAMPLING16((_PCLK_), (_BAUD_)) & 0xF0U)) + \
                                                        (UART_DIVFRAQ_SAMPLING16((_PCLK_), (_BAUD_)) & 0x0FU))

void STM32_UART::set_baud_rate(uint32_t brate)
{
    m_brate = brate;
    uint32_t freq;
    if((m_uart == USART1)
    #ifdef UART6_BASE
            || (m_uart == USART6))
    #elif USART6_BASE
            || (m_uart == USART6))
    #else
			)
    #endif
        freq = STM32::RCC::get_PCLK2_freq();
    else
        freq = STM32::RCC::get_PCLK1_freq();
    m_uart->BRR = UART_BRR_SAMPLING16(freq, brate);
}

void STM32_UART::send_char(char ch)
{
    while (m_busy)
    {
        OS::sleep(1);
    }
    m_busy = true;
    while ((m_uart->SR & USART_SR_TXE) != USART_SR_TXE);
    m_uart->DR = ch;
    m_busy = false;
}

void STM32_UART::send_str(const char *str, TXRX_MODE mode)
{
    while (m_busy)
    {
        OS::sleep(1);
    }
    send_buf(str, strlen(str) + 1, mode);
}

void STM32_UART::send_buf(const char *buf, int size, TXRX_MODE mode)
{
	m_tx_size = size;
    m_tx_pos = 0;

    switch (mode)
    {
    case TXRX_MODE::DIRECT:
        m_busy = true;
        while (m_tx_pos < m_tx_size)
        {
            while ((m_uart->SR & USART_SR_TXE) != USART_SR_TXE);
            m_uart->DR = buf[m_tx_pos++];
        }
        m_busy = false;
        break;
    case TXRX_MODE::INTERRUPT:
        #ifdef STM32_UART_MODE_IT_ENABLE
        m_busy = true;
        memcpy(m_tx_buf, buf, size);
        m_uart->CR1 |= USART_CR1_TXEIE;
        BIT_BAND_PER(m_uart->CR1, USART_CR1_TXEIE) = 1;
        #endif
        break;
    case TXRX_MODE::DMA:
        ///TODO
        #ifdef STM32_UART_MODE_DMA_ENABLE
        #endif
        break;
    }

}

void inline STM32_UART::irq_proc()
{
    if (m_uart->SR & USART_SR_RXNE)
        recv_data();
    else if (m_uart->SR & USART_SR_TXE)
        send_data();
}

void STM32_UART::set_config()
{
    uint32_t tmpreg;
    
    /*-------------------------- USART CR2 Configuration -----------------------*/
    tmpreg = m_uart->CR2;

    /* Clear STOP[13:12] bits */
    tmpreg &= (uint32_t)~((uint32_t)USART_CR2_STOP);

    /* Configure the UART Stop Bits: Set STOP[13:12] bits according to huart->Init.StopBits value */
    tmpreg |= STM32_UART_STOPBITS;

    /* Write to USART CR2 */
    m_uart->CR2 = tmpreg;

    /*-------------------------- USART CR1 Configuration -----------------------*/
    tmpreg = m_uart->CR1;

    /* Clear M, PCE, PS, TE and RE bits */
    tmpreg &= (uint32_t)~((uint32_t)(USART_CR1_M | USART_CR1_PCE | USART_CR1_PS | USART_CR1_TE | \
                            USART_CR1_RE | USART_CR1_OVER8));

    /* Configure the UART Word Length, Parity and mode: 
    Set the M bits according to huart->Init.WordLength value 
    Set PCE and PS bits according to huart->Init.Parity value
    Set TE and RE bits according to huart->Init.Mode value
    Set OVER8 bit according to huart->Init.OverSampling value */
    tmpreg |= STM32_UART_WORDLENGTH | STM32_UART_PARITY | UART_MODE_TX_RX | UART_OVERSAMPLING_16;

    #ifdef STM32_UART_MODE_IT_ENABLE
    tmpreg |= USART_CR1_RXNEIE;
    #endif

    /* Write to USART CR1 */
    m_uart->CR1 = tmpreg;

    /*-------------------------- USART CR3 Configuration -----------------------*/  
    tmpreg = m_uart->CR3;

    /* Clear CTSE and RTSE bits */
    tmpreg &= (uint32_t)~((uint32_t)(USART_CR3_RTSE | USART_CR3_CTSE));

    /* Configure the UART HFC: Set CTSE and RTSE bits according to huart->Init.HwFlowCtl value */
    tmpreg |= UART_HWCONTROL_NONE;

    /* Write to USART CR3 */
    m_uart->CR3 = tmpreg;
}

void STM32_UART::recv_data()
{
    m_rx_buf[m_rx_pos++] = m_uart->DR;
	m_rx_size = m_rx_pos;
}

void STM32_UART::send_data()
{
    m_uart->DR = m_tx_buf[m_tx_pos++];
	if (m_tx_pos >= m_tx_size)
    {
        BIT_BAND_PER(m_uart->CR1, USART_CR1_TXEIE) = 0;
        m_busy = false;
    }
}


#ifdef STM32_UART_MODE_IT_ENABLE
#ifdef STM32_USE_UART1
STM32_UART uart1;

void ISR::USART1_IRQ()
{
	uart1.irq_proc();
}
#endif

#ifdef STM32_USE_UART2
STM32_UART uart2;

void ISR::USART2_IRQ()
{
	uart2.irq_proc();
}
#endif

#ifdef STM32_USE_UART3
STM32_UART uart3;

void ISR::USART3_IRQ()
{
    uart3.irq_proc();
}
#endif

#ifdef STM32_USE_UART4
STM32_UART uart4;

void ISR::UART4_IRQ()
{
	uart4.irq_proc();
}
#endif

#ifdef STM32_USE_UART5
STM32_UART uart5;

void ISR::UART5_IRQ()
{
	uart5.irq_proc();
}
#endif

#ifdef STM32_USE_UART6
STM32_UART uart6;

void ISR::USART6_IRQ()
{
	uart6.irq_proc();
}
#endif

#ifdef STM32_USE_UART7
STM32_UART uart7;

void ISR::UART7_IRQ()
{
	uart7.irq_proc();
}
#endif

#ifdef STM32_USE_UART8
STM32_UART uart8;

void ISR::UART8_IRQ()
{
	uart8.irq_proc();
}
#endif
#endif

#endif //STM32_USE_UART
