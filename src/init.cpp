#include "stm32_inc.h"
#include "init.h"
#include "my_func.h"
#ifdef STM32_FATFS_USE
#include "sddriver.h"
#endif

int main();

/* #define VECT_TAB_SRAM */
#define VECT_TAB_OFFSET  0x00 /*!< Vector Table base offset field. 
                                   This value must be a multiple of 0x200. */

// base initialization
void base_init()
{
    /* FPU settings ------------------------------------------------------------*/
    #if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  /* set CP10 and CP11 Full Access */
    #endif

    //extern uint32_t _RAM_Start;
    //memset((uint8_t*)&_RAM_Start, 0, 1024*50);

    STM32_RCC::deinit();
    STM32_SYSTICK::init();

    #if defined (DATA_IN_ExtSDRAM)
    if (STM32_SDRAM::init() != STM32_RESULT_OK)
        Error_Handler();
    #endif

    /* Configure the Vector Table location add offset address ------------------*/
    #ifdef VECT_TAB_SRAM
    SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM */
    #else
    SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal FLASH */
    #endif

    #ifdef INSTRUCTION_CACHE_ENABLE
    STM32_FLASH::enable_instruction_cache();
    #endif
    #ifdef DATA_CACHE_ENABLE
    STM32_FLASH::enable_data_cache();
    #endif
    #ifdef PREFETCH_ENABLE
    STM32_FLASH::enable_prefetch_buffer();
    #endif

    STM32_NVIC::init();
}

void SystemInit()
{
    base_init();
    // system initialization
    STM32_RCC::init();
    STM32_SYSTICK::init();

    /* Initialize interrupt vectors for a peripheral */
    STM32_NVIC::init_vectors();
    __enable_fault_irq();
    __enable_irq();
}

void PeriphInit()
{
    STM32_RCC::update_clock();

    /* Other IO and peripheral initializations */
    STM32_GPIO::init_all();
    #ifdef STM32_USE_UART
    STM32_UART::init_all();
    #endif
    #ifdef STM32_USE_SPI
    STM32_SPI::init_all();
    #endif
    #ifdef STM32_USE_RTC
    STM32_RTC::init();
    #endif
    #ifdef STM32_USE_DMA
    STM32_DMA::init_all();
    #endif
    #ifdef STM32_FATFS_USE
    sd_driver.init_gpio();
    #endif
}

#define INIT_SP() \
    { \
        __ASM volatile("ldr sp, =_estack\n\r" : : ); \
    } \

static inline void __initialize_data (uint32_t* from, uint32_t* region_begin, uint32_t* region_end)
{
    // Iterate and copy word by word.
    // It is assumed that the pointers are word aligned.
    uint32_t *p = region_begin;
    while (p < region_end)
        *p++ = *from++;
}

static inline void __initialize_bss (uint32_t* region_begin, uint32_t* region_end)
{
    // Iterate and clear word by word.
    // It is assumed that the pointers are word aligned.
    uint32_t *p = region_begin;
    while (p < region_end)
        *p++ = 0;
}

extern uint32_t __textdata__;
extern uint32_t __data_start__;
extern uint32_t __data_end__;
extern uint32_t __bss_start__;
extern uint32_t __bss_end__;

void ISR::Reset()
{
    INIT_SP();
    SystemInit();
    __initialize_bss(&__bss_start__, &__bss_end__);
    __initialize_data(&__textdata__, &__data_start__, &__data_end__);
    PeriphInit();
    main();
}
