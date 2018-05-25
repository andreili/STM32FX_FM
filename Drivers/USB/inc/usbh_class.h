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
    virtual uint32_t init(USBHCore* host) = 0;
    virtual uint32_t deInit(USBHCore* host) = 0;
    virtual uint32_t request(USBHCore* host) = 0;
    virtual uint32_t bgnd_process(USBHCore* host) = 0;
    virtual uint32_t SOF_process(USBHCore* host) = 0;

    inline const char* get_name() { return m_name; }

    inline uint8_t get_class_code() { return m_class_code; }

    inline void* get_data() { return m_data; }
    inline void set_data(void* val) { m_data = val; }
private:
    const char* m_name;
    uint8_t     m_class_code;
    void*       m_data;
};

#endif
