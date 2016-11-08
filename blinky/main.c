#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>

#include "common_lib/utils.h"

int main(void)
{
    // Setup LED on dev board (PC13)
    LED_Init1();

    // Prepare delay timer (so it can be used in `delay_ms` below)
    setup_delay_timer(TIM2);

    while(1) {
        // Toggle led state (i.e 0->1 or 1->0 depeding on current state)
        LED_toggle(1);
        // Wait 1 second
        delay_ms(TIM2, 1000);
        // Toggle again
        LED_toggle(1);
        // Wait 100 ms
        delay_ms(TIM2, 100);
    }
}
