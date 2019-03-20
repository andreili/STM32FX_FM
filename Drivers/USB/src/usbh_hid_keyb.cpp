#include "usbh_hid_keyb.h"
#include "stm32_inc.h"
#include "my_func.h"
#include "xprintf.h"

#ifdef STM32_USE_USB_HID_KBD

void USBH_HID_Keyb::kbd_init()
{
    debug_fn();
    for (int i=0 ; i<CUSTOM_DATA_SIZE ; ++i)
        m_custom_data[i] = 0;
    //memset(m_custom_data, 0, CUSTOM_DATA_SIZE);
    memset(reinterpret_cast<uint8_t*>(m_report_data), 0, REPORT_DATA_SIZE * sizeof(uint32_t));
    if (m_length > REPORT_DATA_SIZE)
        m_length = REPORT_DATA_SIZE;
    m_data = reinterpret_cast<uint8_t*>(m_report_data);
    m_fifo.init(m_host->get_dev_data(), HID_QUEUE_SIZE * REPORT_DATA_SIZE * sizeof(uint32_t));
}

USBHCore::EStatus USBH_HID_Keyb::kbd_decode()
{
    debug_fn();
    if (m_length == 0)
        return USBHCore::EStatus::FAIL;

    if (m_fifo.read(&m_report_data, m_length) == m_length)
    {
        xprintf("Report: %08X %08X\n\r", m_report_data[0], m_report_data[1]);
        return USBHCore::EStatus::OK;
    }

    return USBHCore::EStatus::FAIL;
}

#endif
