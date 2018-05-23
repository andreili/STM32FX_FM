#ifndef __STM32_DMA__
#define __STM32_DMA__

/*
 * Based on HAL-F4 v1.21.0
 * */

#include "stm32_inc.h"

enum class DMA_State
{
    RESET_,
    READY,
    BUSY,
    TIMEOUT,
    ERROR,
    ABORT,
};

enum class DMA_LevelComplete
{
    FULL_TRANSFER,
    HALF_TRANSFER,
};

enum class DMA_CallbackID
{
    XFER_COMPLETE,
    XFER_HALF_COMPLETE,
    XFER_M1_COMPLETE,
    XFER_M1_HALF_COMPLETE,
    XFER_ERROR,
    XFER_ABORT,
    XFER_ALL,
};

typedef struct
{
    uint32_t    channel;
    uint32_t    direction;
    uint32_t    periph_inc;
    uint32_t    mem_inc;
    uint32_t    periph_data_aligment;
    uint32_t    mem_data_aligment;
    uint32_t    mode;
    uint32_t    priority;
    uint32_t    FIFO_mode;
    uint32_t    FIFO_tresshold;
    uint32_t    mem_burst;
    uint32_t    periph_burst;
} DMA_Init_Typedef;

#define DMA_ERROR_NONE            0x00000000U    /*!< No error                               */
#define DMA_ERROR_TE              0x00000001U    /*!< Transfer error                         */
#define DMA_ERROR_FE              0x00000002U    /*!< FIFO error                             */
#define DMA_ERROR_DME             0x00000004U    /*!< Direct Mode error                      */
#define DMA_ERROR_TIMEOUT         0x00000020U    /*!< Timeout error                          */
#define DMA_ERROR_PARAM           0x00000040U    /*!< Parameter error                        */
#define DMA_ERROR_NO_XFER         0x00000080U    /*!< Abort requested with no Xfer ongoing   */
#define DMA_ERROR_NOT_SUPPORTED   0x00000100U    /*!< Not supported mode                     */

#define DMA_CHANNEL_0                 0x00000000U    /*!< DMA Channel 0 */
#define DMA_CHANNEL_1                 0x02000000U    /*!< DMA Channel 1 */
#define DMA_CHANNEL_2                 0x04000000U    /*!< DMA Channel 2 */
#define DMA_CHANNEL_3                 0x06000000U    /*!< DMA Channel 3 */
#define DMA_CHANNEL_4                 0x08000000U    /*!< DMA Channel 4 */
#define DMA_CHANNEL_5                 0x0A000000U    /*!< DMA Channel 5 */
#define DMA_CHANNEL_6                 0x0C000000U    /*!< DMA Channel 6 */
#define DMA_CHANNEL_7                 0x0E000000U    /*!< DMA Channel 7 */
#if defined (DMA_SxCR_CHSEL_3)
#define DMA_CHANNEL_8                 0x10000000U    /*!< DMA Channel 8 */
#define DMA_CHANNEL_9                 0x12000000U    /*!< DMA Channel 9 */
#define DMA_CHANNEL_10                0x14000000U    /*!< DMA Channel 10 */
#define DMA_CHANNEL_11                0x16000000U    /*!< DMA Channel 11 */
#define DMA_CHANNEL_12                0x18000000U    /*!< DMA Channel 12 */
#define DMA_CHANNEL_13                0x1A000000U    /*!< DMA Channel 13 */
#define DMA_CHANNEL_14                0x1C000000U    /*!< DMA Channel 14 */
#define DMA_CHANNEL_15                0x1E000000U    /*!< DMA Channel 15 */
#endif /* DMA_SxCR_CHSEL_3 */

#define DMA_PERIPH_TO_MEMORY          0x00000000U                 /*!< Peripheral to memory direction */
#define DMA_MEMORY_TO_PERIPH          ((uint32_t)DMA_SxCR_DIR_0)  /*!< Memory to peripheral direction */
#define DMA_MEMORY_TO_MEMORY          ((uint32_t)DMA_SxCR_DIR_1)  /*!< Memory to memory direction     */

#define DMA_PINC_ENABLE               ((uint32_t)DMA_SxCR_PINC)   /*!< Peripheral increment mode enable  */
#define DMA_PINC_DISABLE              0x00000000U                 /*!< Peripheral increment mode disable */

#define DMA_MINC_ENABLE               ((uint32_t)DMA_SxCR_MINC)   /*!< Memory increment mode enable  */
#define DMA_MINC_DISABLE              0x00000000U                 /*!< Memory increment mode disable */

#define DMA_PDATAALIGN_BYTE           0x00000000U                  /*!< Peripheral data alignment: Byte     */
#define DMA_PDATAALIGN_HALFWORD       ((uint32_t)DMA_SxCR_PSIZE_0) /*!< Peripheral data alignment: HalfWord */
#define DMA_PDATAALIGN_WORD           ((uint32_t)DMA_SxCR_PSIZE_1) /*!< Peripheral data alignment: Word     */

#define DMA_MDATAALIGN_BYTE           0x00000000U                  /*!< Memory data alignment: Byte     */
#define DMA_MDATAALIGN_HALFWORD       ((uint32_t)DMA_SxCR_MSIZE_0) /*!< Memory data alignment: HalfWord */
#define DMA_MDATAALIGN_WORD           ((uint32_t)DMA_SxCR_MSIZE_1) /*!< Memory data alignment: Word     */

#define DMA_NORMAL                    0x00000000U                  /*!< Normal mode                  */
#define DMA_CIRCULAR                  ((uint32_t)DMA_SxCR_CIRC)    /*!< Circular mode                */
#define DMA_PFCTRL                    ((uint32_t)DMA_SxCR_PFCTRL)  /*!< Peripheral flow control mode */

#define DMA_PRIORITY_LOW              0x00000000U                 /*!< Priority level: Low       */
#define DMA_PRIORITY_MEDIUM           ((uint32_t)DMA_SxCR_PL_0)   /*!< Priority level: Medium    */
#define DMA_PRIORITY_HIGH             ((uint32_t)DMA_SxCR_PL_1)   /*!< Priority level: High      */
#define DMA_PRIORITY_VERY_HIGH        ((uint32_t)DMA_SxCR_PL)     /*!< Priority level: Very High */

#define DMA_FIFOMODE_DISABLE          0x00000000U                 /*!< FIFO mode disable */
#define DMA_FIFOMODE_ENABLE           ((uint32_t)DMA_SxFCR_DMDIS) /*!< FIFO mode enable  */

#define DMA_FIFO_THRESHOLD_1QUARTERFULL       0x00000000U                  /*!< FIFO threshold 1 quart full configuration  */
#define DMA_FIFO_THRESHOLD_HALFFULL           ((uint32_t)DMA_SxFCR_FTH_0)  /*!< FIFO threshold half full configuration     */
#define DMA_FIFO_THRESHOLD_3QUARTERSFULL      ((uint32_t)DMA_SxFCR_FTH_1)  /*!< FIFO threshold 3 quarts full configuration */
#define DMA_FIFO_THRESHOLD_FULL               ((uint32_t)DMA_SxFCR_FTH)    /*!< FIFO threshold full configuration          */

#define DMA_MBURST_SINGLE             0x00000000U
#define DMA_MBURST_INC4               ((uint32_t)DMA_SxCR_MBURST_0)
#define DMA_MBURST_INC8               ((uint32_t)DMA_SxCR_MBURST_1)
#define DMA_MBURST_INC16              ((uint32_t)DMA_SxCR_MBURST)

#define DMA_PBURST_SINGLE             0x00000000U
#define DMA_PBURST_INC4               ((uint32_t)DMA_SxCR_PBURST_0)
#define DMA_PBURST_INC8               ((uint32_t)DMA_SxCR_PBURST_1)
#define DMA_PBURST_INC16              ((uint32_t)DMA_SxCR_PBURST)

#define DMA_IT_TC                     ((uint32_t)DMA_SxCR_TCIE)
#define DMA_IT_HT                     ((uint32_t)DMA_SxCR_HTIE)
#define DMA_IT_TE                     ((uint32_t)DMA_SxCR_TEIE)
#define DMA_IT_DME                    ((uint32_t)DMA_SxCR_DMEIE)
#define DMA_IT_FE                     0x00000080U

#define DMA_FLAG_FEIF0_4              0x00000001U
#define DMA_FLAG_DMEIF0_4             0x00000004U
#define DMA_FLAG_TEIF0_4              0x00000008U
#define DMA_FLAG_HTIF0_4              0x00000010U
#define DMA_FLAG_TCIF0_4              0x00000020U
#define DMA_FLAG_FEIF1_5              0x00000040U
#define DMA_FLAG_DMEIF1_5             0x00000100U
#define DMA_FLAG_TEIF1_5              0x00000200U
#define DMA_FLAG_HTIF1_5              0x00000400U
#define DMA_FLAG_TCIF1_5              0x00000800U
#define DMA_FLAG_FEIF2_6              0x00010000U
#define DMA_FLAG_DMEIF2_6             0x00040000U
#define DMA_FLAG_TEIF2_6              0x00080000U
#define DMA_FLAG_HTIF2_6              0x00100000U
#define DMA_FLAG_TCIF2_6              0x00200000U
#define DMA_FLAG_FEIF3_7              0x00400000U
#define DMA_FLAG_DMEIF3_7             0x01000000U
#define DMA_FLAG_TEIF3_7              0x02000000U
#define DMA_FLAG_HTIF3_7              0x04000000U
#define DMA_FLAG_TCIF3_7              0x08000000U

enum class DMA_Memory
{
    MEMORY_0 = 0,
    MEMORY_1 = 1,
};



class STM32_DMA
{
public:
    static void init_all();

    inline void reset_handle_state() { m_state = DMA_State::RESET_; }
    inline uint32_t get_fs() { return m_instance->FCR & DMA_SxFCR_FS; }

    inline void enable() { m_instance->CR |= DMA_SxCR_EN; }
    inline void disable() { m_instance->CR &= ~DMA_SxCR_EN; }
    inline bool is_enabled() { return ((m_instance->CR & DMA_SxCR_EN) != RESET); }
    inline bool is_disabled() { return ((m_instance->CR & DMA_SxCR_EN) == RESET); }

    inline bool is_circular_mode() { return ((m_instance->CR & DMA_SxCR_CIRC) != RESET); }

    inline void enable_multi_buffering() { m_instance->CR |= DMA_SxCR_DBM; }
    inline void disable_multi_buffering() { m_instance->CR &= ~DMA_SxCR_DBM; }
    inline bool is_multi_buffering_enable() { return ((m_instance->CR & DMA_SxCR_DBM) != RESET); }

    inline bool is_current_memory0() { return ((m_instance->CR & DMA_SxCR_CT) == RESET); }

    inline uint32_t get_TC_flag_index()
        {
            return (((uint32_t)m_instance == ((uint32_t)DMA1_Stream0))? DMA_FLAG_TCIF0_4 :
             ((uint32_t)m_instance == ((uint32_t)DMA2_Stream0))? DMA_FLAG_TCIF0_4 :
             ((uint32_t)m_instance == ((uint32_t)DMA1_Stream4))? DMA_FLAG_TCIF0_4 :
             ((uint32_t)m_instance == ((uint32_t)DMA2_Stream4))? DMA_FLAG_TCIF0_4 :
             ((uint32_t)m_instance == ((uint32_t)DMA1_Stream1))? DMA_FLAG_TCIF1_5 :
             ((uint32_t)m_instance == ((uint32_t)DMA2_Stream1))? DMA_FLAG_TCIF1_5 :
             ((uint32_t)m_instance == ((uint32_t)DMA1_Stream5))? DMA_FLAG_TCIF1_5 :
             ((uint32_t)m_instance == ((uint32_t)DMA2_Stream5))? DMA_FLAG_TCIF1_5 :
             ((uint32_t)m_instance == ((uint32_t)DMA1_Stream2))? DMA_FLAG_TCIF2_6 :
             ((uint32_t)m_instance == ((uint32_t)DMA2_Stream2))? DMA_FLAG_TCIF2_6 :
             ((uint32_t)m_instance == ((uint32_t)DMA1_Stream6))? DMA_FLAG_TCIF2_6 :
             ((uint32_t)m_instance == ((uint32_t)DMA2_Stream6))? DMA_FLAG_TCIF2_6 :
               DMA_FLAG_TCIF3_7);
        }
    inline uint32_t get_HT_flag_index()
        {
            return (((uint32_t)m_instance == ((uint32_t)DMA1_Stream0))? DMA_FLAG_HTIF0_4 :
             ((uint32_t)m_instance == ((uint32_t)DMA2_Stream0))? DMA_FLAG_HTIF0_4 :
             ((uint32_t)m_instance == ((uint32_t)DMA1_Stream4))? DMA_FLAG_HTIF0_4 :
             ((uint32_t)m_instance == ((uint32_t)DMA2_Stream4))? DMA_FLAG_HTIF0_4 :
             ((uint32_t)m_instance == ((uint32_t)DMA1_Stream1))? DMA_FLAG_HTIF1_5 :
             ((uint32_t)m_instance == ((uint32_t)DMA2_Stream1))? DMA_FLAG_HTIF1_5 :
             ((uint32_t)m_instance == ((uint32_t)DMA1_Stream5))? DMA_FLAG_HTIF1_5 :
             ((uint32_t)m_instance == ((uint32_t)DMA2_Stream5))? DMA_FLAG_HTIF1_5 :
             ((uint32_t)m_instance == ((uint32_t)DMA1_Stream2))? DMA_FLAG_HTIF2_6 :
             ((uint32_t)m_instance == ((uint32_t)DMA2_Stream2))? DMA_FLAG_HTIF2_6 :
             ((uint32_t)m_instance == ((uint32_t)DMA1_Stream6))? DMA_FLAG_HTIF2_6 :
             ((uint32_t)m_instance == ((uint32_t)DMA2_Stream6))? DMA_FLAG_HTIF2_6 :
               DMA_FLAG_HTIF3_7);
        }
    inline uint32_t get_TE_flag_index()
        {
            return (((uint32_t)m_instance == ((uint32_t)DMA1_Stream0))? DMA_FLAG_TEIF0_4 :
             ((uint32_t)m_instance == ((uint32_t)DMA2_Stream0))? DMA_FLAG_TEIF0_4 :
             ((uint32_t)m_instance == ((uint32_t)DMA1_Stream4))? DMA_FLAG_TEIF0_4 :
             ((uint32_t)m_instance == ((uint32_t)DMA2_Stream4))? DMA_FLAG_TEIF0_4 :
             ((uint32_t)m_instance == ((uint32_t)DMA1_Stream1))? DMA_FLAG_TEIF1_5 :
             ((uint32_t)m_instance == ((uint32_t)DMA2_Stream1))? DMA_FLAG_TEIF1_5 :
             ((uint32_t)m_instance == ((uint32_t)DMA1_Stream5))? DMA_FLAG_TEIF1_5 :
             ((uint32_t)m_instance == ((uint32_t)DMA2_Stream5))? DMA_FLAG_TEIF1_5 :
             ((uint32_t)m_instance == ((uint32_t)DMA1_Stream2))? DMA_FLAG_TEIF2_6 :
             ((uint32_t)m_instance == ((uint32_t)DMA2_Stream2))? DMA_FLAG_TEIF2_6 :
             ((uint32_t)m_instance == ((uint32_t)DMA1_Stream6))? DMA_FLAG_TEIF2_6 :
             ((uint32_t)m_instance == ((uint32_t)DMA2_Stream6))? DMA_FLAG_TEIF2_6 :
               DMA_FLAG_TEIF3_7);
        }
    inline uint32_t get_FE_flag_index()
        {
            return (((uint32_t)m_instance == ((uint32_t)DMA1_Stream0))? DMA_FLAG_FEIF0_4 :
             ((uint32_t)m_instance == ((uint32_t)DMA2_Stream0))? DMA_FLAG_FEIF0_4 :
             ((uint32_t)m_instance == ((uint32_t)DMA1_Stream4))? DMA_FLAG_FEIF0_4 :
             ((uint32_t)m_instance == ((uint32_t)DMA2_Stream4))? DMA_FLAG_FEIF0_4 :
             ((uint32_t)m_instance == ((uint32_t)DMA1_Stream1))? DMA_FLAG_FEIF1_5 :
             ((uint32_t)m_instance == ((uint32_t)DMA2_Stream1))? DMA_FLAG_FEIF1_5 :
             ((uint32_t)m_instance == ((uint32_t)DMA1_Stream5))? DMA_FLAG_FEIF1_5 :
             ((uint32_t)m_instance == ((uint32_t)DMA2_Stream5))? DMA_FLAG_FEIF1_5 :
             ((uint32_t)m_instance == ((uint32_t)DMA1_Stream2))? DMA_FLAG_FEIF2_6 :
             ((uint32_t)m_instance == ((uint32_t)DMA2_Stream2))? DMA_FLAG_FEIF2_6 :
             ((uint32_t)m_instance == ((uint32_t)DMA1_Stream6))? DMA_FLAG_FEIF2_6 :
             ((uint32_t)m_instance == ((uint32_t)DMA2_Stream6))? DMA_FLAG_FEIF2_6 :
               DMA_FLAG_FEIF3_7);
        }
    inline uint32_t get_DME_flag_index()
        {
            return (((uint32_t)m_instance == ((uint32_t)DMA1_Stream0))? DMA_FLAG_DMEIF0_4 :
             ((uint32_t)m_instance == ((uint32_t)DMA2_Stream0))? DMA_FLAG_DMEIF0_4 :
             ((uint32_t)m_instance == ((uint32_t)DMA1_Stream4))? DMA_FLAG_DMEIF0_4 :
             ((uint32_t)m_instance == ((uint32_t)DMA2_Stream4))? DMA_FLAG_DMEIF0_4 :
             ((uint32_t)m_instance == ((uint32_t)DMA1_Stream1))? DMA_FLAG_DMEIF1_5 :
             ((uint32_t)m_instance == ((uint32_t)DMA2_Stream1))? DMA_FLAG_DMEIF1_5 :
             ((uint32_t)m_instance == ((uint32_t)DMA1_Stream5))? DMA_FLAG_DMEIF1_5 :
             ((uint32_t)m_instance == ((uint32_t)DMA2_Stream5))? DMA_FLAG_DMEIF1_5 :
             ((uint32_t)m_instance == ((uint32_t)DMA1_Stream2))? DMA_FLAG_DMEIF2_6 :
             ((uint32_t)m_instance == ((uint32_t)DMA2_Stream2))? DMA_FLAG_DMEIF2_6 :
             ((uint32_t)m_instance == ((uint32_t)DMA1_Stream6))? DMA_FLAG_DMEIF2_6 :
             ((uint32_t)m_instance == ((uint32_t)DMA2_Stream6))? DMA_FLAG_DMEIF2_6 :
               DMA_FLAG_DMEIF3_7);
        }

    inline uint32_t get_flag(uint32_t flag_mask)
        {
            return (((uint32_t)m_instance > (uint32_t)DMA2_Stream3)? (DMA2->HISR & flag_mask) :
                    ((uint32_t)m_instance > (uint32_t)DMA1_Stream7)? (DMA2->LISR & flag_mask) :
                    ((uint32_t)m_instance > (uint32_t)DMA1_Stream3)? (DMA1->HISR & flag_mask) :
                                                                           (DMA1->LISR & flag_mask));
        }
    inline uint32_t clear_flag(uint32_t flag_mask)
        {
            return (((uint32_t)m_instance > (uint32_t)DMA2_Stream3)? (DMA2->HISR = flag_mask) :
                    ((uint32_t)m_instance > (uint32_t)DMA1_Stream7)? (DMA2->LISR = flag_mask) :
                    ((uint32_t)m_instance > (uint32_t)DMA1_Stream3)? (DMA1->HISR = flag_mask) :
                                                                           (DMA1->LISR = flag_mask));
        }

    inline void enable_IT(uint32_t interrupt)
        { (interrupt != DMA_IT_FE) ? (m_instance->CR |= interrupt) : (m_instance->FCR |= interrupt); }
    inline void disable_IT(uint32_t interrupt)
        { (interrupt != DMA_IT_FE) ? (m_instance->CR &= ~interrupt) : (m_instance->FCR &= ~interrupt); }
    inline uint32_t get_IT_source(uint32_t interrupt)
        { return ((interrupt != DMA_IT_FE) ? (m_instance->CR & interrupt) : (m_instance->FCR & interrupt)); }

    inline void set_counter(uint32_t counter)
        { m_instance->NDTR = counter; }
    inline uint32_t get_counter()
        { return m_instance->NDTR; }

    uint32_t init(DMA_Init_Typedef *init);
    uint32_t deinit();

    uint32_t start(uint32_t direction, uint32_t src_addr, uint32_t dst_addr, uint32_t length);
    uint32_t start_IT(uint32_t direction, uint32_t src_addr, uint32_t dst_addr, uint32_t length);
    uint32_t abort();
    uint32_t abort_IT();
    uint32_t pool_for_transfer(DMA_LevelComplete complete_level, uint32_t timeout);
    uint32_t register_callback(DMA_CallbackID ID, void (*pCalback)(STM32_DMA *_hdma));
    uint32_t unregister_callback(DMA_CallbackID ID);

    inline DMA_State get_state() { return m_state; }
    inline uint32_t get_error() { return m_error_code; }

    uint32_t multi_buffer_start(uint32_t direction, uint32_t src_addr, uint32_t dst_addr, uint32_t second_mem_address, uint32_t length);
    uint32_t multi_buffer_start_IT(uint32_t direction, uint32_t src_addr, uint32_t dst_addr, uint32_t second_mem_address, uint32_t length);
    void change_memory(uint32_t address, DMA_Memory memory);

    void IRQ_handler();
private:
    DMA_Stream_TypeDef* m_instance;
    uint32_t            m_lock;
    DMA_State           m_state;
    uint32_t            m_error_code;
    uint32_t            m_stream_base_address;
    uint32_t            m_stream_index;
    void                (*m_Xfer_complete_cb)(STM32_DMA *hdma);
    void                (*m_Xfer_half_complete_cb)(STM32_DMA *hdma);
    void                (*m_Xfer_m1_complete_cb)(STM32_DMA *hdma);
    void                (*m_Xfer_m1_half_complete_cb)(STM32_DMA *hdma);
    void                (*m_Xfer_error_cb)(STM32_DMA *hdma);
    void                (*m_Xfer_abort_cb)(STM32_DMA *hdma);

    void set_config(uint32_t direction, uint32_t src_addr, uint32_t dst_addr, uint32_t length);
    uint32_t calc_base_and_bit_shift();
    uint32_t check_FIFO_param(DMA_Init_Typedef *init);
    void multi_buffer_set_config(uint32_t direction, uint32_t src_addr, uint32_t dst_addr, uint32_t length);
};

extern STM32_DMA dma1_channel0;
extern STM32_DMA dma1_channel1;
extern STM32_DMA dma1_channel2;
extern STM32_DMA dma1_channel3;
extern STM32_DMA dma1_channel4;
extern STM32_DMA dma1_channel5;
extern STM32_DMA dma1_channel6;
extern STM32_DMA dma1_channel7;

extern STM32_DMA dma2_channel0;
extern STM32_DMA dma2_channel1;
extern STM32_DMA dma2_channel2;
extern STM32_DMA dma2_channel3;
extern STM32_DMA dma2_channel4;
extern STM32_DMA dma2_channel5;
extern STM32_DMA dma2_channel6;
extern STM32_DMA dma2_channel7;

#endif
