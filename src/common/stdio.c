#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>

#include <common/stdio.h>
#include <common/strings.h>
#include <kernel/uart0.h>

void putc(const unsigned char c) {
    uart_putc(c);
}

void puts(const unsigned char *str) {
    while ('\0' != *str) {
        putc(*str++);
    }
}

int printf(const char *fmt, ...) {
    return 0;
}

// for now, we can't handle any more than 16 digit numbers
#define SNPRINTF_MAX_DIGITS 16
#define SNPRINTF_MAX_BUF_SIZE 1024
// for now, only handle %u, %c, %s
// returns size of str?
int snprintf(char *str, size_t size, const char *fmt, ...) {
    if (NULL == str) {
        return -1;
    }
    va_list args;

    /*
    const char *fmt_ptr = fmt;
    int arg_count = 0;
    while ('\0' != *fmt_ptr) {
        if ('%' == *fmt_ptr++) {
            ++arg_count;
        } 
    }
    */

    va_start(args, fmt);

    char curr = 0;
    int fmt_next = 0;
    size_t arg_len = 0;
    char replace[SNPRINTF_MAX_DIGITS];
    const char *fmt_ptr = fmt;
    while ('\0' != (curr = *fmt_ptr++) && size--) {
        if (fmt_next) {
            // curr should be u or x or some format character
            switch (curr) {
                case 'u':
                    // TODO: need to subtract the number of bytes that are copied here
                    // from the total
                    numtostr(va_arg(args, unsigned int), replace, &arg_len);
                    memcpy(str, replace, arg_len);
                    str += arg_len;
                    break;
                case 'x':
                    break;
                case 'c':
                    break;
                case 's':
                    break;
                default:
                    break;
            }
            fmt_next = 0;
        } else if ('%' == curr) {
            fmt_next = 1;
        } else {
            *str++ = curr;
        }
    }
    // need to end 
    *str = '\0';
    va_end(args);
    return 0;
}