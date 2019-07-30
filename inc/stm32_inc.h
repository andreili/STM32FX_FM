#ifndef STM32_INC_H
#define STM32_INC_H

#include "stm32_conf.h"
#include "stm32_def.h"

#if defined(STM32F429xx)
#include "ISRstm32f429xx.h"
#elif defined(STM32F407xx)
#include "ISRstm32f407xx.h"
#elif defined(STM32F100xB)
#include "ISRstm32f10x_md.h"
#endif

#include "stm32_exti.hpp"
#include "stm32_flash.hpp"
#include "stm32_rcc.hpp"
#include "stm32_gpio.hpp"
#include "stm32_nvic.hpp"
#include "stm32_pwr.hpp"
#ifdef STM32_USE_DMA
    #include "stm32_dma.h"
#endif
#ifdef STM32_USE_SDRAM
    #include "stm32_sdram.h"
#endif
#include "stm32_systick.hpp"
#ifdef STM32_USE_UART
    #include "stm32_uart.h"
#endif
#ifdef STM32_USE_SD
    #include "stm32_sd.hpp"
    #ifdef STM32_FATFS_USE
        #include STM32_FATFS_SD_DRIVER_INC
    #endif //STM32_FATFS_USE
#endif //STM32_USE_SD
#ifdef STM32_USE_SPI
    #include "stm32_spi.h"
#endif //STM32_USE_SPI
#ifdef STM32_USE_RTC
    #include "stm32_rtc.h"
#endif //STM32_USE_RTC
#ifdef STM32_USE_USB
    #ifdef STM32_USE_USB_HOST
        #include "stm32_hcd.h"
        #ifdef STM32_USE_USBH_HID_KBD
            #include "usbh_hid_keyb.h"
        #endif //STM32_USE_USBH_HID_KBD
    #endif // STM32_USE_USB_HOST
#endif //STM32_USE_USB
#ifdef STM32_USE_TIM
    #include "stm32_tim.h"
#endif //STM32_USE_TIM
#ifdef STM32_USE_RTOS
    #include "scmRTOS.h"
#endif //STM32_USE_RTOS
#ifdef STM32_PROFILER
#include "profiler.hpp"
#endif //STM32_PROFILER
#include "bitbanding.h"

#define STM32_LOCK(HN) \
    { \
        if (HN == STM32_LOCKED) \
            return STM32_RESULT_BUSY; \
        else \
            HN = STM32_LOCKED; \
    }

#define STM32_UNLOCK(HN) \
    HN = STM32_UNLOCKED;

#endif // STM32_INC_H
