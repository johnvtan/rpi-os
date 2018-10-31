#include <testing/testing.h>
#include <common/strings.h>
#include <common/stdio.h>
#include <kernel/uart0.h>
#include <kernel/mem.h>

#define ASSERT(expr, msg) { if (!(expr)) { printf("Assertion failed: "); printf(msg); while(1); } }

// all tests return 0 if they pass, -1 if they fail
int run_tests(void) {
    if (0 != test_strings()) {
        printf("test_strings() failed");
        return -1;
    }
    if (0 != test_mem()) {
        printf("test_mem() failed");
        return -1;
    }

    printf("Congrats! All tests passed.");
    return 0;
}

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

    if (6 != printf("ABC%x\n", 0xFF)) {
        printf("Oh no what did you do\n");
        ++fail_count;
    }
    return fail_count;
}

int test_mem(void) {
    void *first_ptr = allocate_page();
    printf("Value of first free page: %u\n", (uint32_t)first_ptr);
    void *second_ptr = 0;
    ASSERT(first_ptr != 0, "could not allocate page?");
    uint32_t first_ptr_address = (uint32_t)first_ptr;
    free_page(first_ptr);
    second_ptr = allocate_page();
    printf("Value of second free page: %u\n", (uint32_t)second_ptr);
    ASSERT(second_ptr != 0, "could not allocate page");
    return 0;
}

