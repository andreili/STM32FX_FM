#ifndef SDDRIVER_H
#define SDDRIVER_H

#include "stm32_inc.h"
#include "fatfs.h"

#define SD_PRESENT      0x01
#define SD_NOT_PRESENT  0x00
#define SD_DATATIMEOUT  ((uint32_t)100000000)

class SDDriver
{
public:
    static inline void init_gpio() { STM32_RCC::STM32_FATFS_CARD_EN_CLK();
                                     STM32_FATFS_CARD_DETECT_PORT.set_config(STM32_FATFS_CARD_DETECT_PIN,
                                                                      GPIO_MODE_INPUT, 0,
                                                                      GPIO_SPEED_FREQ_LOW, GPIO_PULLUP); }

    static inline bool is_card_present() { return (STM32_FATFS_CARD_DETECT_PORT.pin_read(STM32_FATFS_CARD_DETECT_PIN) == RESET); }

    uint8_t init(uint8_t);
    uint8_t status(uint8_t);
    uint8_t read(uint8_t lun, uint8_t*buf, uint32_t sector, uint32_t count);
    #if _USE_WRITE == 1
    uint8_t write(uint8_t, uint8_t*, uint32_t, uint32_t);
    #endif
    #if _USE_IOCTL == 1
    uint8_t ioctl(uint8_t, uint8_t, void*);
    #endif
private:
    uint8_t m_state;
};

extern SDDriver sd_driver;

#endif // SDDRIVER_H
