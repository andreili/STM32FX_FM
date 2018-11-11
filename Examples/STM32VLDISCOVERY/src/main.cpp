#include "stm32_inc.h"
#include "my_func.h"
#include "xprintf.h"

#define LED_OK GPIO_PIN_11
#define LED_FAULT GPIO_PIN_8

void xfunc_out(unsigned char c)
{
    uart1.send_char(c);
}

uint32_t    val_i = 0;

int main()
{
    STM32_RCC::enable_clk_GPIOA();
    STM32_RCC::enable_clk_GPIOB();

    // inputs
    gpiob.set_config(GPIO_PIN_All, GPIO_MODE_INPUT, 0, GPIO_SPEED_FREQ_HIGH, GPIO_NOPULL);
    gpioa.set_config(GPIO_PIN_12 | GPIO_PIN_15, GPIO_MODE_INPUT, 0, GPIO_SPEED_FREQ_HIGH, GPIO_NOPULL);

    // communications
    gpioa.set_config(GPIO_PIN_3, GPIO_MODE_INPUT, 0, GPIO_SPEED_FREQ_LOW, GPIO_PULLUP); //SEL-OUT
    gpioa.set_config(GPIO_PIN_4, GPIO_MODE_OUTPUT_PP, 0, GPIO_SPEED_FREQ_LOW, GPIO_PULLUP); // SEL-IN

    // status leds
    gpioa.set_config(GPIO_PIN_8 | GPIO_PIN_11, GPIO_MODE_OUTPUT_PP, 0, GPIO_SPEED_FREQ_LOW, GPIO_PULLUP);

    uart1.init(STM32_BRATE_UART1);

    gpioa.pin_ON(LED_OK);
    uart1.send_str("\n\rSTM32F4DISCOVERY demo project"
                   "\n\r\tBased on C++ framework\n\r", TXRX_MODE::INTERRUPT);

    uint32_t ticks;
    while (1)
    {
        ticks = STM32_SYSTICK::get_tick();

        if ((ticks & 0x1ff) == 0x1ff)
        {
            xprintf("ticks=%d; iteration=%d\r", ticks, val_i++);
        }

        STM32_SYSTICK::delay_to(ticks + 1);
    }
    return 0;
}

void Error_Handler()
{
    gpioa.set_config(LED_FAULT, GPIO_MODE_OUTPUT_PP, 0, GPIO_SPEED_FREQ_LOW, GPIO_PULLUP);
    while (1)
        gpioa.pin_ON(LED_FAULT);
}
