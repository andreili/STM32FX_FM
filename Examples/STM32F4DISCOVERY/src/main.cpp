#include "stm32_inc.h"
#include "my_func.h"
#include "xprintf.h"
#include "usbhcore.h"

#define LED_PORT gpiod
#define LED3_PIN GPIO_PIN_13
#define LED4_PIN GPIO_PIN_12
#define LED5_PIN GPIO_PIN_14
#define LED6_PIN GPIO_PIN_15

#define SYS_PULSE_PORT gpiod
#define SYS_PULSE_PIN  GPIO_PIN_1

#define BTN_PORT gpioa
#define BTN_PIN  GPIO_PIN_0

void xfunc_out(unsigned char c)
{
    uart6.send_char(c);
}

uint32_t    val_i = 0;

void usb_fs_proc(USBHCore* core, EHostUser reason)
{
    UNUSED(core);
    switch (reason)
    {
    case EHostUser::SELECT_CONFIGURATION:
        debug_out("Select configuration\n\r");
        break;
    case EHostUser::CLASS_ACTIVE:
        debug_out("Class active\n\r");
        break;
    case EHostUser::CLASS_SELECTED:
        debug_out("Class selected\n\r");
        break;
    case EHostUser::CONNECTION:
        debug_out("Connection\n\r");
        break;
    case EHostUser::DISCONNECTION:
        debug_out("Disconnection\n\r");
        break;
    case EHostUser::UNRECOVERED_ERROR:
        debug_out("Unrecovered error\n\r");
        break;
    }
}

int main()
{
    STM32_RCC::enable_clk_GPIOA();
    STM32_RCC::enable_clk_GPIOD();

    LED_PORT.set_config(LED3_PIN | LED4_PIN | LED5_PIN | LED6_PIN, GPIO_MODE_OUTPUT_PP, 0, GPIO_SPEED_FREQ_LOW, GPIO_NOPULL);
    gpioa.pin_OFF(LED3_PIN);

    SYS_PULSE_PORT.set_config(SYS_PULSE_PIN, GPIO_MODE_OUTPUT_PP, 0, GPIO_SPEED_FREQ_LOW, GPIO_NOPULL);
    BTN_PORT.set_config(BTN_PIN, GPIO_MODE_INPUT, 0, GPIO_SPEED_FREQ_LOW, GPIO_PULLDOWN);

    STM32_USB_PWR_FS_PORT.set_config(STM32_USB_PWR_FS_PIN, GPIO_MODE_OUTPUT_PP, 0, GPIO_SPEED_FREQ_LOW, GPIO_NOPULL);
    STM32_USB_PWR_FS_PORT.pin_ON(STM32_USB_PWR_FS_PIN);

    uart6.init(STM32_BRATE_UART6);

    uart6.send_str("\n\rSTM32F4DISCOVERY demo project"
                   "\n\r\tBased on C++ framework\n\r", TXRX_MODE::INTERRUPT);

    usb_FS.init(usb_fs_proc, HOST_FS);
    usb_FS.start();

    uint32_t ticks;
    while (1)
    {
        SYS_PULSE_PORT.pin_ON(GPIO_PIN_1);
        ticks = STM32_SYSTICK::get_tick();

        if ((ticks & 0x1ff) == 0x1ff)
        {
            xprintf("ticks=%d; iteration=%d\r", ticks, val_i++);
            LED_PORT.pin_toggle(LED5_PIN);
        }

        if (BTN_PORT.pin_read(BTN_PIN))
            LED_PORT.pin_ON(LED4_PIN);
        else
            LED_PORT.pin_OFF(LED4_PIN);

        SYS_PULSE_PORT.pin_OFF(GPIO_PIN_1);

        STM32_SYSTICK::delay_to(ticks + 1);

        usb_FS.process();
    }
    return 0;
}

void Error_Handler()
{
    while (1)
        gpioa.pin_ON(LED6_PIN);
}

void disconnect_callback(STM32_HCD *hcd)
{
    ((USBHCore*)hcd->get_data())->LL_disconnect();
    debug_out("USB disconnected\n\r");
}

void connect_callback(STM32_HCD *hcd)
{
    ((USBHCore*)hcd->get_data())->LL_connect();
    debug_out("USB connected\n\r");
}

void SOF_callback(STM32_HCD *hcd)
{
    ((USBHCore*)hcd->get_data())->LL_inc_timer();
}

void HC_notify_URB_change_callback(STM32_HCD *hcd, uint8_t ch_num, EURBState urb_state)
{
#if (USBH_USE_OS == 1)
    ((USBHCore*)hcd->get_data())->LL_notify_URB_change();
#else
    UNUSED(hcd);
#endif
    UNUSED(ch_num);
    UNUSED(urb_state);
}
