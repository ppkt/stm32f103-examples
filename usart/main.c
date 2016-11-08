#include <stdio.h>

#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>

#include "common_lib/utils.h"
#include "common_lib/usart.h"

int main(void)
{
    // Configure USART1 peripheral (PA9 Tx, PA10 Rx) with speed 9600 bps
    USART1_Init(9600);

    // Print simple text
    printf("Hello, World!\r\n");

    // More advanced formatting
    printf("A number: %d\r\n", 123);

    while(1) {}
}
