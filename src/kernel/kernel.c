#include <stddef.h>
#include <stdint.h>

#include <kernel/uart0.h>

void kernel_main(void) {
    uart0_init();
    uart_puts("Hello, world!");
}