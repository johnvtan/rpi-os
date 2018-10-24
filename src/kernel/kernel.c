#include <stddef.h>
#include <stdint.h>

#include <kernel/uart0.h>
#include <kernel/proc.h>
#include <common/stdio.h>

#ifdef TEST
#include <testing/testing.h>
#endif

void kernel_main(void) {
    uart0_init();
#ifdef TEST
    if (!test_strings()) {
        uart_puts("All tests passed\n\r");
    }
#else
    printf("Starting tasks...\n");
    proc_init();
    printf("END PROC_INIT() - ERROR SHOULDN'T GET HERE!!!");
#endif
}
