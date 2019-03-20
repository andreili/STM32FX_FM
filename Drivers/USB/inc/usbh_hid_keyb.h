#ifndef USBH_HID_KEYB_H
#define USBH_HID_KEYB_H

#include "usbh_hid.h"
#include "usbhcore.h"

class USBH_HID_Keyb: public USBH_HID
{
public:
    void kbd_init();
    USBHCore::EStatus kbd_decode();
private:
};

#endif //USBH_HID_KEYB_H
