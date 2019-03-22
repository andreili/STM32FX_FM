#ifndef __USBH_CLASS_H__
#define __USBH_CLASS_H__

/*
 * Based on HAL-F4 v1.21.0
 * */

#include <inttypes.h>
#include "usbhcore.h"

class USBHClass
{
public:
    virtual uint8_t get_class_code() = 0;
    virtual const char* get_name() = 0;
    virtual USBHCore::EStatus init(USBHCore* host) = 0;
    virtual USBHCore::EStatus deInit() = 0;
    virtual USBHCore::EStatus class_request() = 0;
    virtual USBHCore::EStatus process() = 0;
    virtual USBHCore::EStatus SOF_process() = 0;
protected:
    USBHCore*   m_host;
};

#endif
