#include "common_lib/utils.h"

int main(void)
{
    // Setup LED on dev board (PC13)
    led_init();

    // Prepare delay timer (so it can be used in `delay_ms` below)
    systick_setup(PRECISION_LOW);

    while(1) {
        // Toggle led state (i.e 0->1 or 1->0 depeding on current state)
        led_toggle();
        // Wait 1 second
        delay_ms(1000);
        // Toggle again
        led_toggle();
        // Wait 100 ms
        delay_ms(100);
    }
}
