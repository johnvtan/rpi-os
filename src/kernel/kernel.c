#include <stddef.h>
#include <stdint.h>

#include <kernel/uart0.h>
#include <kernel/proc.h>
#include <common/stdio.h>

void kernel_main(void) {
    uart0_init();
    /*
    if (!test_strings()) {
        uart_puts("All tests passed\n\r");
    }
    */
    printf("Starting tasks...\n");
    proc_init();
    printf("END PROC_INIT() - ERROR SHOULDN'T GET HERE!!!");
}
