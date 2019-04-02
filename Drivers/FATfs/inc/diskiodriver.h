#ifndef DISKIODRIVER_H
#define DISKIODRIVER_H

#include "fatfs.h"
#include <inttypes.h>

class DiskIODriver
{
public:
    virtual uint8_t init(uint8_t) = 0;
    virtual void link_data(void* pdata) = 0;
    virtual uint8_t status(uint8_t) = 0;
    virtual uint8_t read(uint8_t lun, uint8_t*buf, uint32_t sector, uint16_t count) = 0;
    #if _USE_WRITE == 1
    virtual uint8_t write(uint8_t lun, uint8_t*buf, uint32_t sector, uint16_t count) = 0;
    #endif
    #if _USE_IOCTL == 1
    virtual uint8_t ioctl(uint8_t, FAT_FS::ECTRL, void*) = 0;
    #endif
};

#endif // DISKIODRIVER_H
