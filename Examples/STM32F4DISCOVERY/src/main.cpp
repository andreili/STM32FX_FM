#include "stm32_inc.h"
#include "my_func.h"
#include "xprintf.h"
#include "usbhcore.h"

#define LED_PORT gpiod
#define LED3_PIN STM32_GPIO::PIN_13
#define LED4_PIN STM32_GPIO::PIN_12
#define LED5_PIN STM32_GPIO::PIN_14
#define LED6_PIN STM32_GPIO::PIN_15

#define BTN_PORT gpioa
#define BTN_PIN  STM32_GPIO::PIN_0

void xfunc_out(unsigned char c)
{
    uart3.send_char(c);
}

typedef OS::process<OS::pr0, 100> TProc0;
typedef OS::process<OS::pr1, 100> TProc1;
typedef OS::process<OS::pr2, 100> TProc2;
typedef OS::process<OS::pr3, 100> TProc3;

TProc0 Proc0;
TProc1 Proc1;
TProc2 Proc2;
TProc3 Proc3;

void usb_fs_proc(USBHCore* core, USBHCore::EHostUser reason)
{
    UNUSED(core);
    switch (reason)
    {
    case USBHCore::EHostUser::SELECT_CONFIGURATION:
        debug_out("Select configuration\n\r");
        break;
    case USBHCore::EHostUser::CLASS_ACTIVE:
        debug_out("Class active\n\r");
        break;
    case USBHCore::EHostUser::CLASS_SELECTED:
        debug_out("Class selected\n\r");
        break;
    case USBHCore::EHostUser::CONNECTION:
        debug_out("Connection\n\r");
        break;
    case USBHCore::EHostUser::DISCONNECTION:
        debug_out("Disconnection\n\r");
        break;
    case USBHCore::EHostUser::UNRECOVERED_ERROR:
        debug_out("Unrecovered error\n\r");
        break;
    }
}

int main()
{
    STM32_RCC::enable_clk_GPIOA();
    STM32_RCC::enable_clk_GPIOD();

    LED_PORT.set_config(LED3_PIN | LED4_PIN | LED5_PIN | LED6_PIN, STM32_GPIO::EMode::OUTPUT_PP, 0, STM32_GPIO::ESpeed::LOW, STM32_GPIO::EPull::NOPULL);
    gpioa.pin_OFF(LED3_PIN);

    BTN_PORT.set_config(BTN_PIN, STM32_GPIO::EMode::INPUT, 0, STM32_GPIO::ESpeed::LOW, STM32_GPIO::EPull::PULLUP);

    STM32_USB_PWR_FS_PORT.set_config(STM32_USB_PWR_FS_PIN, STM32_GPIO::EMode::OUTPUT_PP, 0, STM32_GPIO::ESpeed::LOW, STM32_GPIO::EPull::NOPULL);
    STM32_USB_PWR_FS_PORT.pin_ON(STM32_USB_PWR_FS_PIN);

    uart3.init(STM32_BRATE_UART6);

    uart3.send_str("\n\rSTM32F4DISCOVERY demo project"
                   "\n\r\tBased on C++ framework\n\r", TXRX_MODE::INTERRUPT);

    usb_FS.init(usb_fs_proc, HOST_FS);
    usb_FS.start();
    OS::run();

    while (1)
    {
    }
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

void HC_notify_URB_change_callback(STM32_HCD *hcd, uint8_t ch_num, STM32_HCD::EURBState urb_state)
{
#if (USBH_USE_OS == 1)
    ((USBHCore*)hcd->get_data())->LL_notify_URB_change();
#else
    UNUSED(hcd);
#endif
    UNUSED(ch_num);
    UNUSED(urb_state);
}

namespace OS
{
    template <>
    OS_PROCESS void TProc0::exec()
    {
        for(;;)
        {
            LED_PORT.pin_toggle(LED3_PIN);
            sleep(1);
            LED_PORT.pin_toggle(LED3_PIN);
            sleep(990);
        }
    }

    template <>
    OS_PROCESS void TProc1::exec()
    {
        for(;;)
        {
            LED_PORT.pin_toggle(LED4_PIN);
            sleep(1);
            LED_PORT.pin_toggle(LED4_PIN);
            sleep(1990);
        }
    }

    template <>
    OS_PROCESS void TProc2::exec()
    {
        for(;;)
        {
            LED_PORT.pin_toggle(LED5_PIN);
            sleep(1);
            LED_PORT.pin_toggle(LED5_PIN);
            sleep(990);
        }
    }

    template <>
    OS_PROCESS void TProc3::exec()
    {
        for(;;)
        {
            usb_FS.process();
            sleep(1);
        }
    }
}

extern "C" void __init_system_timer()
{
    STM32_SYSTICK::init();
}

void ISR::SysTickTimer()
{
    OS::system_timer_isr();
    OS::raise_context_switch();
}
