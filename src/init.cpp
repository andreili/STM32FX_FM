#include "stm32_inc.h"
#include "init.h"
#ifdef STM32_FATFS_USE
#include "sddriver.h"
#endif

int main();

/* #define VECT_TAB_SRAM */
#define VECT_TAB_OFFSET  0x00 /*!< Vector Table base offset field. 
                                   This value must be a multiple of 0x200. */
extern volatile uint32_t _FLASH_START;

// base initialization
void base_init()
{
    /* FPU settings ------------------------------------------------------------*/
    #if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  /* set CP10 and CP11 Full Access */
    #endif

    STM32_RCC::deinit_cold();

    #if defined (DATA_IN_ExtSDRAM)
    if (STM32_SDRAM::init() != STM32_RESULT_OK)
        Error_Handler();
    #endif

    /* Configure the Vector Table location add offset address ------------------*/
    #ifdef VECT_TAB_SRAM
    SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM */
    #else
    SCB->VTOR = uint32_t(&_FLASH_START) | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal FLASH */
    #endif
}

#ifndef STM32_TIMEBASE_SYSTICK
void timebase_cb(STM32_TIM* tim, uint32_t ch)
{
    UNUSED(tim);
    UNUSED(ch);
    STM32_SYSTICK::on_tick();
}
#endif //STM32_TIMEBASE_SYSTICK

void timebase_init()
{
    #ifdef STM32_TIMEBASE_SYSTICK
    STM32_SYSTICK::init();
    #else
    STM32_SYSTICK::deinit();
    STM32_TIM::TimerBaseInit_t tim14_init;
    tim14_init.period = (1000000/STM32_TIMEBASE_FREQ_HZ) - 1;
    tim14_init.prescaler = ((2 * STM32_RCC::get_PCLK1_freq()) / 1000000) - 1; // (2*PCLK1Freq/1000000 - 1) to have a 1MHz counter clock.
    tim14_init.clk_div = STM32_TIM::EClkDiv::DIV_1;
    tim14_init.counter_mode = STM32_TIM::ECounterMode::UP;

    STM32_NVIC::enable_and_set_prior_IRQ(TIM8_TRG_COM_TIM14_IRQn, 0, 0);
    STM32_RCC::enable_clk_TIM14();
    tim14.set_cb_period_elapsed(timebase_cb);

    tim14.init(&tim14_init);
    tim14.start_IT();
    #endif //STM32_TIMEBASE_SYSTICK
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
    #ifdef STM32_USE_TIM
    STM32_TIM::init_all();
    #endif
    timebase_init();
}

void SystemInit()
{
    base_init();
    // system initialization
    STM32_RCC::init();
    PeriphInit();

    /* Initialize interrupt vectors for a peripheral */
    STM32_NVIC::init_vectors();
    STM32_RCC::update_clock();

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

static inline void __initalize_classes(uint32_t* ctors_begin, uint32_t* ctors_end)
{
    for (uint32_t* ctor=ctors_begin ; ctor<ctors_end ; ++ctor)
        reinterpret_cast<void(*)(void)>(*ctor)();
}

extern uint32_t __textdata__;
extern uint32_t __data_start__;
extern uint32_t __data_end__;
extern uint32_t __bss_start__;
extern uint32_t __bss_end__;
extern uint32_t __ctors_start__;
extern uint32_t __ctors_end__;

void ISR::Reset()
{
    SystemInit();
    INIT_SP();
    __initialize_bss(&__bss_start__, &__bss_end__);
    __initialize_data(&__textdata__, &__data_start__, &__data_end__);
    __initalize_classes(&__ctors_start__, &__ctors_end__);
    PeriphInit();
    __enable_fault_irq();
    __enable_irq();
    main();
}
