#include <kernel/uart0.h>
#include <kernel/gpio.h>

int uart0_init(void) {
    volatile UART0_PERIPH * const uart0 = (volatile UART0_PERIPH *)UART0_BASE_ADDR;
    volatile GPIO_PERIPH * const gpio = (volatile GPIO_PERIPH *)GPIO_BASE_ADDR;
    
    return 0;
}