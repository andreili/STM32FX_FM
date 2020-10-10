#ifndef USBH_HID_KEYB_H
#define USBH_HID_KEYB_H

#include <inttypes.h>

#define USB_KEYBRD_KEYS_COUNT 256

class USBH_HID_Keyb
{
public:
    void init();
private:
    static uint8_t  m_keys_current[USB_KEYBRD_KEYS_COUNT];
    static uint8_t  m_keys_prev[USB_KEYBRD_KEYS_COUNT];
};

#endif //USBH_HID_KEYB_H
