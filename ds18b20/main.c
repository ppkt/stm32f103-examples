#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>

#include "common_lib/utils.h"
#include "common_lib/usart.h"

#include "device_lib/ds18b20.h"

int main(void)
{
    uint8_t i;
    one_wire_device dev;

    // Setup delay timer
    setup_delay_timer(TIM2);

    // Setup USART1 @ 115200 bps
    USART1_Init(115200);

    // Configure DS18B20 and 1-Wire on pin B12
    // Please remember about adding pull-up resistor :)
    ds18b20_init(GPIOB, GPIO_Pin_12, TIM2);

    // Scan for DS18B20 devices on 1-Wire
    ds18b20_devices devices = ds18b20_get_devices(true);

    // Iterate over found devices and print their addresses
    // Address of DS18B20 device starts from 0x28
    printf("Found %d 1-Wire device(s)\r\n", devices.size);
    for (i = 0; i < devices.size; ++i) {
        dev = devices.devices[i];
        printf(
            "[%d] 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\r\n",
            i, dev.address[0], dev.address[1], dev.address[2], dev.address[3],
            dev.address[4], dev.address[5], dev.address[6], dev.address[7]);
    }

    while(1) {
        // Side note: If there is only one DS18B20 device in bus, we can skip
        // address match
        if (devices.size == 1) {
            simple_float temperature = ds18b20_get_temperature_simple();
            if (temperature.is_valid) {
                printf("Current temp: %d.%03d C\r\n",
                       temperature.integer, temperature.fractional);
            }

        } else if (devices.size > 1) {
            // Send "Convert temperature" command to each device
            ds18b20_convert_temperature_all();

            // Wait for temperature conversion
            ds18b20_wait_for_conversion();

            // Read temperature from each device
            simple_float* temperatures = ds18b20_read_temperature_all();

            for (i = 0; i < devices.size; ++i) {
                printf("[%d] Current temp: %d.%03d C\r\n", i,
                       temperatures[i].integer, temperatures[i].fractional);
            }
            free(temperatures);
        }
    }
}
