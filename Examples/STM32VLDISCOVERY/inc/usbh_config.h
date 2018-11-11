#ifndef __USBH_CONFIG_H__
#define __USBH_CONFIG_H__

#define USBH_MAX_NUM_ENDPOINTS          5
#define USBH_MAX_NUM_INTERFACES         10
#define USBH_MAX_NUM_CONFIGURATION      1
#define USBH_KEEP_CFG_DESCRIPTOR        1
#define USBH_MAX_NUM_SUPPORTED_CLASS    5
#define USBH_MAX_SIZE_CONFIGURATION     256
#define USBH_MAX_DATA_BUFFER            512
#define USBH_DEBUG_LEVEL                5
#define USBH_USE_OS                     0

#define HOST_HS 		0
#define HOST_FS 		1

#if (USBH_USE_OS == 1)
  #include "cmsis_os.h"
  #define USBH_PROCESS_PRIO          osPriorityNormal
  #define USBH_PROCESS_STACK_SIZE    ((uint16_t)1024)
#endif /* (USBH_USE_OS == 1) */

#define USBH_malloc         malloc
#define USBH_free           free
#define USBH_memset         memset
#define USBH_memcpy         memcpy

#if (USBH_DEBUG_LEVEL > 0)
#include "xprintf.h"
#define USBH_UsrLog(...)    xprintf(__VA_ARGS__);\
                            xprintf("\n\r");
#else
#define USBH_UsrLog(...)
#endif

#if (USBH_DEBUG_LEVEL > 1)

#define USBH_ErrLog(...)    xprintf("ERROR: " __VA_ARGS__ "\n\r");
#else
#define USBH_ErrLog(...)
#endif

#if (USBH_DEBUG_LEVEL > 2)
#define USBH_DbgLog(...)    xprintf("DEBUG : ");\
                            xprintf(__VA_ARGS__);\
                            xprintf("\n\r");
#else
#define USBH_DbgLog(...)
#endif

#endif
