QT -= core gui opengl

APP = f4disco_demo
TARGET = f4disco_demo

CONFIG += c++11
DEVICE = STM32F407xx

QMAKE_LFLAGS += -T$$PWD/../../cortex-m4/stm32f407xx.ld

DEFINES += $${DEVICE}

DESTDIR = ./
#win32:EXT = .exe

#LIBS += -L/usr/lib/gcc/arm-none-eabi/8.1.0/ -lstdc++ -lc

#QMAKE_CXXFLAGS += -O0
#win32:QMAKE_LFLAGS += -L/mingw32/lib/gcc/arm-none-eabi/5.4.1/
linux:QMAKE_LFLAGS += -L/usr/lib/gcc/arm-none-eabi/7.2.0/

createlist.target = all
createlist.commands += arm-none-eabi-objdump -S $${OUT_PWD}/$${APP}$${EXT} > $$join(APP,,,".lst")
createlist.commands += && arm-none-eabi-nm -nSC $${OUT_PWD}/$${APP}$${EXT} > $$join(APP,,,".map")
createlist.commands += && arm-none-eabi-objcopy -Obinary $${OUT_PWD}/$${APP}$${EXT} $${OUT_PWD}/$${APP}.bin
!win32:createlist.commands += && arm-none-eabi-nm -nalS --size-sort $${OUT_PWD}/$${APP}$${EXT} | grep " T " | tail
createlist.commands += && arm-none-eabi-size $${OUT_PWD}/$${APP}$${EXT}
QMAKE_EXTRA_TARGETS += createlist

INCLUDEPATH += ./inc/ ../../Drivers/CMSIS/Devices/ ../../Drivers/CMSIS/inc/ ../../inc/ ../../StdLib/inc/
INCLUDEPATH += ../../Drivers/FATfs/inc/ ../../Third_Party/FatFs/ ../../Drivers/USB/inc/

SOURCES += \
    src/main.cpp \
    ../../Drivers/CMSIS/Devices/ISRstm32f407xx.cpp \
    ../../src/init.cpp \
    ../../src/stm32_flash.cpp \
    ../../src/stm32_gpio.cpp \
    ../../src/stm32_nvic.cpp \
    ../../src/stm32_pwr.cpp \
    ../../src/stm32_rcc.cpp \
    ../../src/stm32_rtc.cpp \
    ../../src/stm32_sd.cpp \
    ../../src/stm32_sdram.cpp \
    ../../src/stm32_spi.cpp \
    ../../src/stm32_systick.cpp \
    ../../src/stm32_uart.cpp \
    ../../StdLib/src/my_func.cpp \
    ../../StdLib/src/xprintf.cpp \
    ../../src/stm32_dma.cpp \
    ../../Drivers/FATfs/src/fatfs.cpp \
    ../../Drivers/FATfs/src/sddriver.cpp \
    ../../Third_Party/FatFs/ff.c \
    ../../Third_Party/FatFs/option/unicode.c \
    ../../Third_Party/FatFs/option/ccsbcs.c \
    ../../Third_Party/FatFs/option/syscall.c \
    ../../Drivers/USB/src/usbhcore.cpp \
    ../../src/stm32_hcd.cpp

HEADERS += \
    inc/stm32_conf.h \
    ../../Drivers/CMSIS/Devices/ISRstm32f407xx.h \
    ../../Drivers/CMSIS/Devices/stm32f407xx.h \
    ../../Drivers/CMSIS/Devices/stm32f4xx.h \
    ../../inc/init.h \
    ../../inc/stm32_flash.h \
    ../../inc/stm32_gpio.h \
    ../../inc/stm32_inc.h \
    ../../inc/stm32_nvic.h \
    ../../inc/stm32_pwr.h \
    ../../inc/stm32_rcc.h \
    ../../inc/stm32_rtc.h \
    ../../inc/stm32_sd.h \
    ../../inc/stm32_sdram.h \
    ../../inc/stm32_spi.h \
    ../../inc/stm32_systick.h \
    ../../inc/stm32_uart.h \
    ../../StdLib/inc/bitbanding.h \
    ../../StdLib/inc/my_func.h \
    ../../StdLib/inc/xprintf.h \
    ../../inc/stm32_def.h \
    ../../inc/stm32_dma.h \
    ../../Drivers/FATfs/inc/diskio.h \
    ../../Drivers/FATfs/inc/diskiodriver.h \
    ../../Drivers/FATfs/inc/fatfs.h \
    ../../Drivers/FATfs/inc/ffconf.h \
    ../../Drivers/FATfs/inc/sddriver.h \
    ../../Third_Party/FatFs/ff.h \
    ../../Third_Party/FatFs/integer.h \
    ../../Drivers/USB/inc/usbhcore.h \
    inc/usbh_config.h \
    ../../Drivers/USB/inc/usbh_class.h \
    ../../inc/stm32_hcd.h


