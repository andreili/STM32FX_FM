#include "usbhcore.h"

#define HOST_HS 		0
#define HOST_FS 		1

#ifdef STM32_USE_USB_HS
USBHCore usb_HS(HOST_HS);
#endif

#ifdef STM32_USE_USB_FS
USBHCore usb_FS(HOST_FS);
#endif
