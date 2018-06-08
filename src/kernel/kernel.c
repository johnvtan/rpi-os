#include <stddef.h>
#include <stdint.h>

#include <kernel/uart0.h>
#include <common/testing.h>

void kernel_main(void) {
    uart0_init();
    if (!test_strings()) {
        uart_puts("All tests passed\n\r");
    }
}