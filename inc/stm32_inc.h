#ifndef STM32_INC_H
#define STM32_INC_H

#ifdef STM32F429xx
#include "ISRstm32f429xx.h"
#endif
#ifdef STM32F407xx
#include "ISRstm32f407xx.h"
#endif
#include "stm32_conf.h"
#include "stm32_flash.h"
#include "stm32_rcc.h"
#include "stm32_gpio.h"
#include "stm32_nvic.h"
#include "stm32_pwr.h"
#include "stm32_sdram.h"
#include "stm32_systick.h"
#include "stm32_uart.h"
#include "stm32_sd.h"
#include "stm32_spi.h"
#include "stm32_rtc.h"
#include "bitbanding.h"

#endif // STM32_INC_H
