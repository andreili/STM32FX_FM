#include "stm32_dma.h"

#define TIMEOUT_DMA_ABORT    5U

typedef struct
{
    __IO uint32_t ISR;   /*!< DMA interrupt status register */
    __IO uint32_t Reserved0;
    __IO uint32_t IFCR;  /*!< DMA interrupt flag clear register */
} DMA_Base_Registers;

void STM32_DMA::init_all()
{
    #ifdef STM32_USE_DMA1_STREAM0
    dma1_channel0.m_instance = DMA1_Stream0;
    #endif
    #ifdef STM32_USE_DMA1_STREAM1
    dma1_channel1.m_instance = DMA1_Stream1;
    #endif
    #ifdef STM32_USE_DMA1_STREAM2
    dma1_channel2.m_instance = DMA1_Stream2;
    #endif
    #ifdef STM32_USE_DMA1_STREAM3
    dma1_channel3.m_instance = DMA1_Stream3;
    #endif
    #ifdef STM32_USE_DMA1_STREAM4
    dma1_channel4.m_instance = DMA1_Stream4;
    #endif
    #ifdef STM32_USE_DMA1_STREAM5
    dma1_channel5.m_instance = DMA1_Stream5;
    #endif
    #ifdef STM32_USE_DMA1_STREAM6
    dma1_channel6.m_instance = DMA1_Stream6;
    #endif
    #ifdef STM32_USE_DMA1_STREAM7
    dma1_channel7.m_instance = DMA1_Stream7;
    #endif

    #ifdef STM32_USE_DMA2_STREAM0
    dma2_channel0.m_instance = DMA2_Stream0;
    #endif
    #ifdef STM32_USE_DMA2_STREAM1
    dma2_channel1.m_instance = DMA2_Stream1;
    #endif
    #ifdef STM32_USE_DMA2_STREAM2
    dma2_channel2.m_instance = DMA2_Stream2;
    #endif
    #ifdef STM32_USE_DMA2_STREAM3
    dma2_channel3.m_instance = DMA2_Stream3;
    #endif
    #ifdef STM32_USE_DMA2_STREAM4
    dma2_channel4.m_instance = DMA2_Stream4;
    #endif
    #ifdef STM32_USE_DMA2_STREAM5
    dma2_channel5.m_instance = DMA2_Stream5;
    #endif
    #ifdef STM32_USE_DMA2_STREAM6
    dma2_channel6.m_instance = DMA2_Stream6;
    #endif
    #ifdef STM32_USE_DMA2_STREAM7
    dma2_channel7.m_instance = DMA2_Stream7;
    #endif
}

uint32_t STM32_DMA::init(DMA_Init_Typedef* init)
{
    STM32_LOCK(m_lock);
    m_state = DMA_State::BUSY;
    disable();
    WAIT_TIMEOUT(!is_disabled(), TIMEOUT_DMA_ABORT);

    uint32_t tmp = m_instance->CR;
    tmp &= ~(DMA_SxCR_CHSEL | DMA_SxCR_MBURST | DMA_SxCR_PBURST |
             DMA_SxCR_PL    | DMA_SxCR_MSIZE  | DMA_SxCR_PSIZE  |
             DMA_SxCR_MINC  | DMA_SxCR_PINC   | DMA_SxCR_CIRC   |
             DMA_SxCR_DIR   | DMA_SxCR_CT     | DMA_SxCR_DBM);
    tmp |= init->channel               | init->direction |
           init->periph_inc            | init->mem_inc |
           init->periph_data_aligment  | init->mem_data_aligment |
           init->mode                  | init->priority;

    if (init->FIFO_mode == DMA_FIFOMODE_ENABLE)
        tmp |= init->mem_burst | init->periph_burst;

    m_instance->CR = tmp;

    tmp = m_instance->FCR;
    /* Clear Direct mode and FIFO threshold bits */
    tmp &= (uint32_t)~(DMA_SxFCR_DMDIS | DMA_SxFCR_FTH);

    /* Prepare the DMA Stream FIFO configuration */
    tmp |= init->FIFO_mode;

    /* The FIFO threshold is not used when the FIFO mode is disabled */
    if (init->FIFO_mode == DMA_FIFOMODE_ENABLE)
    {
        tmp |= init->FIFO_tresshold;

        /* Check compatibility between FIFO threshold level and size of the memory burst */
        /* for INCR4, INCR8, INCR16 bursts */
        if (init->mem_burst != DMA_MBURST_SINGLE)
        {
            if (check_FIFO_param(init) != STM32_RESULT_OK)
            {
                m_error_code = DMA_ERROR_PARAM;
                m_state = DMA_State::READY;
                return STM32_RESULT_FAIL;
            }
        }
    }

    m_instance->FCR = tmp;

    /* Initialize StreamBaseAddress and StreamIndex parameters to be used to calculate
       DMA steam Base Address needed by HAL_DMA_IRQHandler() and HAL_DMA_PollForTransfer() */
    DMA_Base_Registers* regs = (DMA_Base_Registers*)calc_base_and_bit_shift();
    regs->IFCR = 0x3f << m_stream_index;

    m_error_code = DMA_ERROR_NONE;
    m_state = DMA_State::READY;

    return STM32_RESULT_OK;
}

uint32_t STM32_DMA::deinit()
{
    if (m_state == DMA_State::BUSY)
        return STM32_RESULT_BUSY;

    disable();
    m_instance->CR = 0;
    m_instance->NDTR = 0;
    m_instance->PAR = 0;
    m_instance->M0AR = 0;
    m_instance->M1AR = 0;
    m_instance->FCR = 0;

    DMA_Base_Registers* regs = (DMA_Base_Registers*)calc_base_and_bit_shift();
    regs->IFCR = 0x3f << m_stream_index;

    m_error_code = DMA_ERROR_NONE;
    m_state = DMA_State::READY;

    return STM32_RESULT_OK;
}

uint32_t STM32_DMA::start(uint32_t direction, uint32_t src_addr, uint32_t dst_addr, uint32_t length)
{
    STM32_LOCK(m_lock);

    if (m_state == DMA_State::READY)
    {
        m_state = DMA_State::BUSY;
        m_error_code = DMA_ERROR_NONE;
        set_config(direction, src_addr, dst_addr, length);
        enable();
        return STM32_RESULT_OK;
    }
    else
    {
        STM32_UNLOCK(m_lock);
        return STM32_RESULT_BUSY;
    }
}

uint32_t STM32_DMA::start_IT(uint32_t direction, uint32_t src_addr, uint32_t dst_addr, uint32_t length)
{
    DMA_Base_Registers* regs = (DMA_Base_Registers*)calc_base_and_bit_shift();

    STM32_LOCK(m_lock);

    if (m_state == DMA_State::READY)
    {
        m_state = DMA_State::BUSY;
        m_error_code = DMA_ERROR_NONE;
        set_config(direction, src_addr, dst_addr, length);

        regs->IFCR = 0x3f << m_stream_index;
        /* Enable Common interrupts*/
        enable_IT(DMA_IT_TC | DMA_IT_TE | DMA_IT_DME);
        enable_IT(DMA_IT_FE);

        if (m_Xfer_half_complete_cb != nullptr)
            enable_IT(DMA_IT_HT);

        enable();
        return STM32_RESULT_OK;
    }
    else
    {
        STM32_UNLOCK(m_lock);
        return STM32_RESULT_BUSY;
    }
}

uint32_t STM32_DMA::abort()
{
    if (m_state != DMA_State::BUSY)
    {
        m_error_code = DMA_ERROR_NO_XFER;
        STM32_UNLOCK(m_lock);
        return STM32_RESULT_FAIL;
    }
    disable_IT(DMA_IT_TC | DMA_IT_TE | DMA_IT_DME);
    disable_IT(DMA_IT_FE);

    if ((m_Xfer_half_complete_cb != nullptr) || (m_Xfer_m1_half_complete_cb != nullptr))
        disable_IT(DMA_IT_HT);

    disable();

    uint32_t tick = STM32::SYSTICK::get_tick() + TIMEOUT_DMA_ABORT;
    while (!is_disabled())
    {
        if (STM32::SYSTICK::get_tick() > tick)
        {
            m_error_code = DMA_ERROR_TIMEOUT;
            STM32_UNLOCK(m_lock);
            m_state = DMA_State::TIMEOUT;
            return STM32_RESULT_TIMEOUT;
        }
    }

    DMA_Base_Registers* regs = (DMA_Base_Registers*)calc_base_and_bit_shift();
    regs->IFCR = 0x3f << m_stream_index;

    STM32_UNLOCK(m_lock);
    m_state = DMA_State::READY;

    return STM32_RESULT_OK;
}

uint32_t STM32_DMA::abort_IT()
{
    if (m_state != DMA_State::BUSY)
    {
        m_error_code = DMA_ERROR_NO_XFER;
        return STM32_RESULT_FAIL;
    }
    m_state = DMA_State::ABORT;
    disable();
    return STM32_RESULT_OK;
}

uint32_t STM32_DMA::pool_for_transfer(DMA_LevelComplete complete_level, uint32_t timeout)
{
    if (m_state != DMA_State::BUSY)
    {
        m_error_code = DMA_ERROR_NO_XFER;
        STM32_UNLOCK(m_lock);
        return STM32_RESULT_FAIL;
    }

    if (is_circular_mode())
    {
        m_error_code = DMA_ERROR_NOT_SUPPORTED;
        return STM32_RESULT_FAIL;
    }

    uint32_t mask_cpltlevel;
    if (complete_level == DMA_LevelComplete::FULL_TRANSFER)
        mask_cpltlevel = DMA_FLAG_TCIF0_4 << m_stream_index;
    else
        mask_cpltlevel = DMA_FLAG_HTIF0_4 << m_stream_index;

    DMA_Base_Registers* regs = (DMA_Base_Registers*)calc_base_and_bit_shift();
    uint32_t tmpisr = regs->ISR;

    uint32_t tick = STM32::SYSTICK::get_tick() + timeout;
    while (((tmpisr & mask_cpltlevel) == RESET) && ((m_error_code & DMA_ERROR_TE) == RESET))
    {
        if ((timeout == 0) || (STM32::SYSTICK::get_tick() > tick))
        {
            m_error_code = DMA_ERROR_TIMEOUT;
            STM32_UNLOCK(m_lock);
            m_state = DMA_State::READY;
            return STM32_RESULT_TIMEOUT;
        }

        tmpisr = regs->ISR;

        if ((tmpisr & (DMA_FLAG_TEIF0_4 << m_stream_index)) != RESET)
        {
            m_error_code |= DMA_ERROR_TE;
            regs->IFCR = DMA_FLAG_TEIF0_4 << m_stream_index;
        }

        if ((tmpisr & (DMA_FLAG_FEIF0_4 << m_stream_index)) != RESET)
        {
            m_error_code |= DMA_ERROR_FE;
            regs->IFCR = DMA_FLAG_FEIF0_4 << m_stream_index;
        }

        if ((tmpisr & (DMA_FLAG_DMEIF0_4 << m_stream_index)) != RESET)
        {
            m_error_code |= DMA_ERROR_DME;
            regs->IFCR = DMA_FLAG_DMEIF0_4 << m_stream_index;
        }
    }

    if (m_error_code != DMA_ERROR_NONE)
    {
        if ((m_error_code & DMA_ERROR_TE) != RESET)
        {
            abort();
            regs->IFCR = (DMA_FLAG_HTIF0_4 | DMA_FLAG_TCIF0_4) << m_stream_index;
            STM32_UNLOCK(m_lock);
            m_state = DMA_State::READY;
            return STM32_RESULT_FAIL;
        }
    }

    if (complete_level == DMA_LevelComplete::FULL_TRANSFER)
    {
        regs->IFCR = (DMA_FLAG_HTIF0_4 | DMA_FLAG_TCIF0_4) << m_stream_index;
        STM32_UNLOCK(m_lock);
        m_state = DMA_State::READY;
    }
    else
        regs->IFCR = DMA_FLAG_HTIF0_4 << m_stream_index;

    return STM32_RESULT_OK;
}

void STM32_DMA::IRQ_handler()
{
    DMA_Base_Registers* regs = (DMA_Base_Registers*)calc_base_and_bit_shift();
    uint32_t tmpisr = regs->ISR;
    uint32_t timeout = STM32_RCC::get_HCLK_freq();

    /* Transfer Error Interrupt management */
    if ((tmpisr & (DMA_FLAG_TEIF0_4 << m_stream_index)) != RESET)
    {
        if (get_IT_source(DMA_IT_TE) != RESET)
        {
            disable_IT(DMA_IT_TE);
            regs->IFCR = DMA_FLAG_TEIF0_4 << m_stream_index;
            m_error_code |= DMA_ERROR_TE;
        }
    }

    /* FIFO Error Interrupt management */
    if ((tmpisr & (DMA_FLAG_FEIF0_4 << m_stream_index)) != RESET)
    {
        if (get_IT_source(DMA_IT_FE) != RESET)
        {
            regs->IFCR = DMA_FLAG_FEIF0_4 << m_stream_index;
            m_error_code |= DMA_ERROR_FE;
        }
    }

    /* Direct Mode Error Interrupt management */
    if ((tmpisr & (DMA_FLAG_DMEIF0_4 << m_stream_index)) != RESET)
    {
        if (get_IT_source(DMA_IT_DME) != RESET)
        {
            regs->IFCR = DMA_FLAG_DMEIF0_4 << m_stream_index;
            m_error_code |= DMA_ERROR_DME;
        }
    }

    /* Half Transfer Complete Interrupt management */
    if ((tmpisr & (DMA_FLAG_HTIF0_4 << m_stream_index)) != RESET)
    {
        if (get_IT_source(DMA_IT_HT) != RESET)
        {
            regs->IFCR = DMA_FLAG_DMEIF0_4 << m_stream_index;

            if (is_multi_buffering_enable())
            {
                if (is_current_memory0())
                {
                    if (m_Xfer_half_complete_cb != nullptr)
                        m_Xfer_half_complete_cb(this);
                }
                else
                {
                    /* Current memory buffer used is Memory 1 */
                    if (m_Xfer_m1_half_complete_cb != nullptr)
                        m_Xfer_m1_half_complete_cb(this);
                }
            }
            else
            {
                if (!is_circular_mode())
                    disable_IT(DMA_IT_HT);
                if (m_Xfer_half_complete_cb != nullptr)
                    m_Xfer_half_complete_cb(this);
            }
        }
    }

    /* Transfer Complete Interrupt management */
    if ((tmpisr & (DMA_FLAG_TCIF0_4 << m_stream_index)) != RESET)
    {
        if (get_IT_source(DMA_IT_TC) != RESET)
        {
            regs->IFCR = DMA_FLAG_TCIF0_4 << m_stream_index;

            if (m_state == DMA_State::ABORT)
            {
                disable_IT(DMA_IT_TC | DMA_IT_TE | DMA_IT_DME);
                disable_IT(DMA_IT_FE);

                if ((m_Xfer_half_complete_cb != nullptr) || (m_Xfer_m1_half_complete_cb != nullptr))
                    disable_IT(DMA_IT_HT);

                regs->IFCR = 0x3f << m_stream_index;

                STM32_UNLOCK(m_lock);

                m_state = DMA_State::READY;

                if (m_Xfer_abort_cb != nullptr)
                    m_Xfer_abort_cb(this);

                return;
            }

            if (is_multi_buffering_enable())
            {
                if (is_current_memory0())
                {
                    if (m_Xfer_m1_complete_cb != nullptr)
                        m_Xfer_m1_complete_cb(this);
                }
                else
                {
                    /* Current memory buffer used is Memory 1 */
                    if (m_Xfer_complete_cb != nullptr)
                        m_Xfer_complete_cb(this);
                }
            }
            else
            {
                if (!is_circular_mode())
                    disable_IT(DMA_IT_TC);
                STM32_UNLOCK(m_lock);
                m_state = DMA_State::READY;
                if (m_Xfer_complete_cb != nullptr)
                    m_Xfer_complete_cb(this);
            }
        }
    }

    /* manage error case */
    if (m_error_code != DMA_ERROR_NONE)
    {
        if ((m_error_code & DMA_ERROR_TE) != RESET)
        {
            m_state = DMA_State::ABORT;
            disable();
            uint32_t count = 0;
            do
            {
                if (++count > timeout)
                    break;
            } while (is_enabled());
            STM32_UNLOCK(m_lock);
            m_state = DMA_State::READY;
        }

        if (m_Xfer_error_cb != nullptr)
            m_Xfer_error_cb(this);
    }
}

uint32_t STM32_DMA::register_callback(DMA_CallbackID ID, void (*pCalback)(STM32_DMA *_hdma))
{
    STM32_LOCK(m_lock);
    if (m_state == DMA_State::READY)
    {
        switch (ID)
        {
        case DMA_CallbackID::XFER_COMPLETE:
            m_Xfer_complete_cb = pCalback;
            break;
        case DMA_CallbackID::XFER_HALF_COMPLETE:
            m_Xfer_half_complete_cb = pCalback;
            break;
        case DMA_CallbackID::XFER_M1_COMPLETE:
            m_Xfer_m1_complete_cb = pCalback;
            break;
        case DMA_CallbackID::XFER_M1_HALF_COMPLETE:
            m_Xfer_m1_half_complete_cb = pCalback;
            break;
        case DMA_CallbackID::XFER_ERROR:
            m_Xfer_error_cb = pCalback;
            break;
        case DMA_CallbackID::XFER_ABORT:
            m_Xfer_abort_cb = pCalback;
            break;
        case DMA_CallbackID::XFER_ALL:
            break;
        }

        STM32_UNLOCK(m_lock);
        return STM32_RESULT_OK;
    }
    else
    {
        STM32_UNLOCK(m_lock);
        return STM32_RESULT_FAIL;
    }
}

uint32_t STM32_DMA::unregister_callback(DMA_CallbackID ID)
{
    STM32_LOCK(m_lock);
    if (m_state == DMA_State::READY)
    {
        switch (ID)
        {
        case DMA_CallbackID::XFER_COMPLETE:
            m_Xfer_complete_cb = nullptr;
            break;
        case DMA_CallbackID::XFER_HALF_COMPLETE:
            m_Xfer_half_complete_cb = nullptr;
            break;
        case DMA_CallbackID::XFER_M1_COMPLETE:
            m_Xfer_m1_complete_cb = nullptr;
            break;
        case DMA_CallbackID::XFER_M1_HALF_COMPLETE:
            m_Xfer_m1_half_complete_cb = nullptr;
            break;
        case DMA_CallbackID::XFER_ERROR:
            m_Xfer_error_cb = nullptr;
            break;
        case DMA_CallbackID::XFER_ABORT:
            m_Xfer_abort_cb = nullptr;
            break;
        case DMA_CallbackID::XFER_ALL:
            m_Xfer_complete_cb = nullptr;
            m_Xfer_half_complete_cb = nullptr;
            m_Xfer_m1_complete_cb = nullptr;
            m_Xfer_m1_half_complete_cb = nullptr;
            m_Xfer_error_cb = nullptr;
            m_Xfer_abort_cb = nullptr;
            break;
        }

        STM32_UNLOCK(m_lock);
        return STM32_RESULT_OK;
    }
    else
    {
        STM32_UNLOCK(m_lock);
        return STM32_RESULT_FAIL;
    }
}

void STM32_DMA::set_config(uint32_t direction, uint32_t src_addr, uint32_t dst_addr, uint32_t length)
{
    disable_multi_buffering();
    m_instance->NDTR = length;
    if (direction == DMA_MEMORY_TO_PERIPH)
    {
        m_instance->PAR = dst_addr;
        m_instance->M0AR = src_addr;
    }
    else
    {
        m_instance->PAR = src_addr;
        m_instance->M0AR = dst_addr;
    }
}

uint32_t STM32_DMA::calc_base_and_bit_shift()
{
    uint32_t stream_number = (((uint32_t)m_instance & 0xFF) - 16) / 24;

    /* lookup table for necessary bitshift of flags within status registers */
    static const uint8_t flagBitshiftOffset[8U] = {0U, 6U, 16U, 22U, 0U, 6U, 16U, 22U};
    m_stream_index = flagBitshiftOffset[stream_number];

    if (stream_number > 3U)
        /* return pointer to HISR and HIFCR */
        m_stream_base_address = (((uint32_t)m_instance & (uint32_t)(~0x3FFU)) + 4U);
    else
        /* return pointer to LISR and LIFCR */
        m_stream_base_address = ((uint32_t)m_instance & (uint32_t)(~0x3FFU));

    return m_stream_base_address;
}

uint32_t STM32_DMA::check_FIFO_param(DMA_Init_Typedef *init)
{
    /* Memory Data size equal to Byte */
    if(init->mem_data_aligment == DMA_MDATAALIGN_BYTE)
    {
        switch (init->FIFO_tresshold)
        {
            case DMA_FIFO_THRESHOLD_1QUARTERFULL:
            case DMA_FIFO_THRESHOLD_3QUARTERSFULL:
                if ((init->mem_burst & DMA_SxCR_MBURST_1) == DMA_SxCR_MBURST_1)
                    return STM32_RESULT_FAIL;
                break;
            case DMA_FIFO_THRESHOLD_HALFFULL:
                if (init->mem_burst == DMA_MBURST_INC16)
                    return STM32_RESULT_FAIL;
                break;
            case DMA_FIFO_THRESHOLD_FULL:
                break;
            default:
                break;
        }
    }
    /* Memory Data size equal to Half-Word */
    else if (init->mem_data_aligment == DMA_MDATAALIGN_HALFWORD)
    {
        switch (init->FIFO_tresshold)
        {
            case DMA_FIFO_THRESHOLD_1QUARTERFULL:
            case DMA_FIFO_THRESHOLD_3QUARTERSFULL:
                return STM32_RESULT_FAIL;
                break;
            case DMA_FIFO_THRESHOLD_HALFFULL:
                if ((init->mem_burst & DMA_SxCR_MBURST_1) == DMA_SxCR_MBURST_1)
                    return STM32_RESULT_FAIL;
                break;
            case DMA_FIFO_THRESHOLD_FULL:
                if (init->mem_burst == DMA_MBURST_INC16)
                    return STM32_RESULT_FAIL;
            break;
            default:
                break;
        }
    }
    /* Memory Data size equal to Word */
    else
    {
        switch (init->FIFO_tresshold)
        {
            case DMA_FIFO_THRESHOLD_1QUARTERFULL:
            case DMA_FIFO_THRESHOLD_HALFFULL:
            case DMA_FIFO_THRESHOLD_3QUARTERSFULL:
                return STM32_RESULT_FAIL;
                break;
            case DMA_FIFO_THRESHOLD_FULL:
                if ((init->mem_burst & DMA_SxCR_MBURST_1) == DMA_SxCR_MBURST_1)
                    return STM32_RESULT_FAIL;
                break;
            default:
                break;
        }
    }

    return STM32_RESULT_OK;
}

uint32_t STM32_DMA::multi_buffer_start(uint32_t direction, uint32_t src_addr, uint32_t dst_addr, uint32_t second_mem_address, uint32_t length)
{
    if (direction == DMA_MEMORY_TO_MEMORY)
    {
        m_error_code = DMA_ERROR_NOT_SUPPORTED;
        return STM32_RESULT_FAIL;
    }

    STM32_LOCK(m_lock);

    if (m_state == DMA_State::READY)
    {
        m_state = DMA_State::BUSY;
        enable_multi_buffering();
        m_instance->M1AR = second_mem_address;
        multi_buffer_set_config(direction, src_addr, dst_addr, length);
        enable();

        return STM32_RESULT_OK;
    }
    else
        return STM32_RESULT_BUSY;
}

uint32_t STM32_DMA::multi_buffer_start_IT(uint32_t direction, uint32_t src_addr, uint32_t dst_addr, uint32_t second_mem_address, uint32_t length)
{
    if (direction == DMA_MEMORY_TO_MEMORY)
    {
        m_error_code = DMA_ERROR_NOT_SUPPORTED;
        return STM32_RESULT_FAIL;
    }

    if ((m_Xfer_complete_cb == nullptr) ||
        (m_Xfer_m1_complete_cb == nullptr) ||
        (m_Xfer_error_cb == nullptr))
    {
        m_error_code = DMA_ERROR_PARAM;
        return STM32_RESULT_FAIL;
    }

    STM32_LOCK(m_lock);

    if (m_state == DMA_State::READY)
    {
        m_state = DMA_State::BUSY;
        m_error_code = DMA_ERROR_NONE;
        enable_multi_buffering();

        m_instance->M1AR = second_mem_address;
        multi_buffer_set_config(direction, src_addr, dst_addr, length);

        clear_flag(get_TC_flag_index() |
                   get_HT_flag_index() |
                   get_TE_flag_index() |
                   get_DME_flag_index() |
                   get_FE_flag_index());
        enable_IT(DMA_IT_TC | DMA_IT_TE | DMA_IT_DME);
        enable_IT(DMA_IT_FE);

        if ((m_Xfer_half_complete_cb != nullptr) || (m_Xfer_m1_half_complete_cb != nullptr))
            enable_IT(DMA_IT_HT);

        enable();

        return STM32_RESULT_OK;
    }
    else
    {
        STM32_UNLOCK(m_lock);
        return STM32_RESULT_BUSY;
    }
}

void STM32_DMA::change_memory(uint32_t address, DMA_Memory memory)
{
    if (memory == DMA_Memory::MEMORY_0)
        m_instance->M0AR = address;
    else
        m_instance->M1AR = address;
}

void STM32_DMA::multi_buffer_set_config(uint32_t direction, uint32_t src_addr, uint32_t dst_addr, uint32_t length)
{
    m_instance->NDTR = length;
    if (direction == DMA_MEMORY_TO_PERIPH)
    {
        m_instance->PAR = dst_addr;
        m_instance->M0AR = src_addr;
    }
    else
    {
        m_instance->PAR = src_addr;
        m_instance->M0AR = dst_addr;
    }
}

STM32_DMA dma1_channel0;
STM32_DMA dma1_channel1;
STM32_DMA dma1_channel2;
STM32_DMA dma1_channel3;
STM32_DMA dma1_channel4;
STM32_DMA dma1_channel5;
STM32_DMA dma1_channel6;
STM32_DMA dma1_channel7;

STM32_DMA dma2_channel0;
STM32_DMA dma2_channel1;
STM32_DMA dma2_channel2;
STM32_DMA dma2_channel3;
STM32_DMA dma2_channel4;
STM32_DMA dma2_channel5;
STM32_DMA dma2_channel6;
STM32_DMA dma2_channel7;

#ifdef STM32_USE_DMA1_STREAM0
void ISR::DMA1_Stream0_IRQ()
{
    dma1_channel0.IRQ_handler();
}
#endif

#ifdef STM32_USE_DMA1_STREAM1
void ISR::DMA1_Stream1_IRQ()
{
    dma1_channel1.IRQ_handler();
}
#endif

#ifdef STM32_USE_DMA1_STREAM2
void ISR::DMA1_Stream2_IRQ()
{
    dma1_channel2.IRQ_handler();
}
#endif

#ifdef STM32_USE_DMA1_STREAM3
void ISR::DMA1_Stream3_IRQ()
{
    dma1_channel3.IRQ_handler();
}
#endif

#ifdef STM32_USE_DMA1_STREAM4
void ISR::DMA1_Stream4_IRQ()
{
    dma1_channel4.IRQ_handler();
}
#endif

#ifdef STM32_USE_DMA1_STREAM5
void ISR::DMA1_Stream5_IRQ()
{
    dma1_channel5.IRQ_handler();
}
#endif

#ifdef STM32_USE_DMA1_STREAM6
void ISR::DMA1_Stream6_IRQ()
{
    dma1_channel6.IRQ_handler();
}
#endif

#ifdef STM32_USE_DMA1_STREAM7
void ISR::DMA1_Stream7_IRQ()
{
    dma1_channel7.IRQ_handler();
}
#endif

#ifdef STM32_USE_DMA2_STREAM0
void ISR::DMA2_Stream0_IRQ()
{
    dma2_channel0.IRQ_handler();
}
#endif

#ifdef STM32_USE_DMA2_STREAM1
void ISR::DMA2_Stream1_IRQ()
{
    dma2_channel1.IRQ_handler();
}
#endif

#ifdef STM32_USE_DMA2_STREAM2
void ISR::DMA2_Stream2_IRQ()
{
    dma2_channel2.IRQ_handler();
}
#endif

#ifdef STM32_USE_DMA2_STREAM3
void ISR::DMA2_Stream3_IRQ()
{
    dma2_channel3.IRQ_handler();
}
#endif

#ifdef STM32_USE_DMA2_STREAM4
void ISR::DMA2_Stream4_IRQ()
{
    dma2_channel4.IRQ_handler();
}
#endif

#ifdef STM32_USE_DMA2_STREAM5
void ISR::DMA2_Stream5_IRQ()
{
    dma2_channel5.IRQ_handler();
}
#endif

#ifdef STM32_USE_DMA2_STREAM6
void ISR::DMA2_Stream6_IRQ()
{
    dma2_channel6.IRQ_handler();
}
#endif

#ifdef STM32_USE_DMA2_STREAM7
void ISR::DMA2_Stream7_IRQ()
{
    dma2_channel7.IRQ_handler();
}
#endif
