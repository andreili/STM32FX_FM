#include "usbh_hid_keyb.h"
#include "stm32_inc.h"
#include <cstring>

#ifdef STM32_USE_USBH_HID_KBD

uint8_t  USBH_HID_Keyb::m_keys_current[USB_KEYBRD_KEYS_COUNT];
uint8_t  USBH_HID_Keyb::m_keys_prev[USB_KEYBRD_KEYS_COUNT];

void USBH_HID_Keyb::init()
{
    debug_fn();
    memset(m_keys_current, 0, USB_KEYBRD_KEYS_COUNT);
    memset(m_keys_prev, 0, USB_KEYBRD_KEYS_COUNT);
    /*for (int i=0 ; i<CUSTOM_DATA_SIZE ; ++i)
        m_custom_data[i] = 0;
    //memset(m_custom_data, 0, CUSTOM_DATA_SIZE);
    memset(reinterpret_cast<uint8_t*>(m_report_data), 0, REPORT_DATA_SIZE * sizeof(uint32_t));
    if (m_length > REPORT_DATA_SIZE)
        m_length = REPORT_DATA_SIZE;
    m_data = reinterpret_cast<uint8_t*>(m_report_data);
    m_fifo.init(m_host->get_dev_data(), HID_QUEUE_SIZE * REPORT_DATA_SIZE * sizeof(uint32_t));*/
}

#endif // STM32_USE_USBH_HID_KBD
