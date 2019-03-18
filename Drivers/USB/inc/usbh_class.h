#ifndef __USBH_CLASS_H__
#define __USBH_CLASS_H__

/*
 * Based on HAL-F4 v1.21.0
 * */

#include <inttypes.h>

class USBHCore;

class USBHClass
{
public:
    virtual uint8_t get_class_code() = 0;
    virtual const char* get_name() = 0;
    virtual uint32_t init(USBHCore* host) = 0;
    virtual uint32_t deInit(USBHCore* host) = 0;
    virtual uint32_t class_request(USBHCore* host) = 0;
    virtual uint32_t process(USBHCore* host) = 0;
    virtual uint32_t SOF_process(USBHCore* host) = 0;

    inline void* get_data() { return m_data; }
    inline void set_data(void* val) { m_data = val; }
private:
    void*       m_data;
};

#endif
