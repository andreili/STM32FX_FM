#include "sddriver.h"

#ifdef STM32_USE_SD

/* Block Size in Bytes */
#define BLOCK_SIZE                512

uint8_t SDDriver::init(uint8_t)
{
    STM32_SD::ESDError sd_state = STM32_SD::ESDError::OK;
    m_state = STA_NOINIT;
    if (!is_card_present())
        return RES_ERROR;
    sd_state = STM32_SD::init();
    #ifdef STM32_FATFS_BUS_4BITS
    if (sd_state == STM32_SD::ESDError::OK)
    {
        if (STM32_SD::wide_bus_config(STM32_SDIO_BUS) != STM32_SD::ESDError::OK)
            sd_state = STM32_SD::ESDError::ERROR;
    }
    #endif
    return static_cast<uint8_t>(sd_state);
}

uint8_t SDDriver::status(uint8_t)
{
    return 0;
}

DSTATUS SDDriver::read(uint8_t lun, uint8_t* buf, uint32_t sector, uint16_t count)
{
    UNUSED(lun);
    if (STM32_SD::read_blocks(buf, sector * BLOCK_SIZE, BLOCK_SIZE, count) != STM32_SD::ESDError::OK)
        return RES_ERROR;
    return RES_OK;
}

#if _USE_WRITE == 1
DSTATUS SDDriver::write(uint8_t lun, uint8_t* buf, uint32_t sector, uint16_t count)
{
    UNUSED(lun);
    if (STM32_SD::write_blocks(buf, sector * BLOCK_SIZE, BLOCK_SIZE, count) != STM32_SD::ESDError::OK)
        return RES_ERROR;
    return RES_OK;
}

#endif
#if _USE_IOCTL == 1
uint8_t SDDriver::ioctl(uint8_t, FAT_FS::ECTRL, void*)
{
    return 0;
}
#endif

void SDDriver::init_gpio()
{
    STM32_RCC::STM32_FATFS_CARD_EN_CLK();
    STM32_FATFS_CARD_DETECT_PORT.set_config(STM32_FATFS_CARD_DETECT_PIN,
                                            STM32_GPIO::EMode::INPUT, 0,
                                            STM32_GPIO::ESpeed::LOW, STM32_GPIO::EPull::PULLUP);
}

#endif //STM32_FATFS_USE
