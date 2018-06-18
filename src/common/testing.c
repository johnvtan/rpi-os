#include <common/testing.h>
/* Module for testing implemented functions */
#include <common/strings.h>
#include <common/stdio.h>
#include <kernel/uart0.h>

// all tests return 0 if they pass, -1 if they fail

// test functions implemented in strings
// returns number of functions that failed testing
int test_strings(void) {
    char *s1 = "Hello";
    char *s2 = "Goodbye";

    int s1_size = 5;
    int s2_size = 7;

    int fail_count = 0;
    if (strlen(s1) != s1_size) {
        uart_puts("strlen(s1) failed test\n\r");
        ++fail_count;
    }

    if (strlen(s2) != s2_size) {
        uart_puts("strlen(s2) failed test\n\r");
        ++fail_count;
    }

    char *s2_ptr = memset(s2, 0xAB, s2_size);
    for (int i = 0; i < s2_size; i++) {
        if (*s2_ptr++ != 0xAB) {
            uart_puts("memset(s2, 0xAB, s2_size) failed\n\r");
            ++fail_count;
            break;
        }
    }
    
    if (123 != strtonum("123", &s2_size)) {
        uart_puts("atoui(\"123\") failed\n\r");
        ++fail_count;
    }

    /*
    s2_ptr = numtostr(123, s2_ptr, &s2_size);
    if (s2_size < 3) {
        uart_puts("numtostr len too small.\n");
    } else if (s2_size > 3) {
        uart_puts("numtostr len too big\n");
    }
    */

    /*
    if (0xABC != strtonum("0xABC", &s2_ptr)) {
        uart_puts("atoui(0xABC) failed");
        ++fail_count;
    }
    
    if (0xFFF != strtonum("0xFFF", &s2_ptr)) {
        uart_puts("wtf\n\r");
        ++fail_count;
    }
    */

    /*
    uart_puts(numtostr(strtonum("0xABC", &s2_ptr), s2_ptr, 4));
    uart_putc('\n');
    */
    printf("%s\n", numtostr(1234, 10, s2_ptr, &s2_size));
    printf("%s\n", numtostr(0xABCD, 16, s2_ptr, &s2_size));
    printf("%s\n", "this is a test");
    printf("%s abc %u\n", "Keeping it", 100);
    printf("Hello my name is %x\n", 0xFFFF);
    return fail_count;
}

// test functions implemented in printf
int test_printf(void) {
    return 0;
}