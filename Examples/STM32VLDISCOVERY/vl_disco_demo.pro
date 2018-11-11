QT -= core gui opengl

APP = vl_disco_demo
TARGET = vl_disco_demo

CONFIG += c++11
DEVICE = STM32F100xB

QMAKE_LFLAGS += -T$$PWD/../../cortex-m3/stm32f103_md.ld

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
    ../../Drivers/CMSIS/Devices/ISRstm32f10x_md.cpp \
    ../../src/init.cpp \
    ../../src/stm32_flash.cpp \
    ../../src/stm32_gpio.cpp \
    ../../src/stm32_nvic.cpp \
    ../../src/stm32_pwr.cpp \
    ../../src/stm32_rcc.cpp \
    ../../src/stm32_rtc.cpp \
    ../../src/stm32_spi.cpp \
    ../../src/stm32_systick.cpp \
    ../../src/stm32_uart.cpp \
    ../../StdLib/src/my_func.cpp \
    ../../StdLib/src/xprintf.cpp

HEADERS += \
    inc/stm32_conf.h \
    ../../Drivers/CMSIS/Devices/ISRstm32f10x_md.h \
    ../../Drivers/CMSIS/Devices/stm32f103xb.h \
    ../../Drivers/CMSIS/Devices/stm32f1xx.h \
    ../../inc/init.h \
    ../../inc/stm32_flash.h \
    ../../inc/stm32_gpio.h \
    ../../inc/stm32_inc.h \
    ../../inc/stm32_nvic.h \
    ../../inc/stm32_pwr.h \
    ../../inc/stm32_rcc.h \
    ../../inc/stm32_rtc.h \
    ../../inc/stm32_spi.h \
    ../../inc/stm32_systick.h \
    ../../inc/stm32_uart.h \
    ../../StdLib/inc/bitbanding.h \
    ../../StdLib/inc/my_func.h \
    ../../StdLib/inc/xprintf.h \
    ../../inc/stm32_def.h


