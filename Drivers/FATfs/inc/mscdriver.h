#ifndef MSCDRIVER_H
#define MSCDRIVER_H

#include "stm32_inc.h"
#include "diskiodriver.h"

#ifdef STM32_USE_USB

class USBH_MSC;

class MSCDriver: public DiskIODriver
{
public:
    virtual uint8_t init(uint8_t) { return RES_OK; }
    virtual void link_data(void* pdata) { m_msc = reinterpret_cast<USBH_MSC*>(pdata); }
    virtual uint8_t status(uint8_t);
    virtual DSTATUS read(uint8_t lun, uint8_t* buf, uint32_t sector, uint16_t count);
    #if _USE_WRITE == 1
    virtual DSTATUS write(uint8_t, uint8_t*, uint32_t, uint16_t);
    #endif
    #if _USE_IOCTL == 1
    virtual uint8_t ioctl(uint8_t, FAT_FS::ECTRL, void*);
    #endif
private:
    uint8_t     m_state;
    USBH_MSC*   m_msc;
};

#endif //STM32_USE_USB

#endif //MSCDRIVER_H
