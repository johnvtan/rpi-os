#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>

#include <common/stdio.h>
#include <common/strings.h>
#include <kernel/uart0.h>

// for now, we can't handle any more than 16 digit numbers
#define VSNPRINTF_MAX_DIGITS 16
#define PRINTF_MAX_BUF_SIZE 1024

void putc(const unsigned char c) {
    uart_putc(c);
}

void puts(const unsigned char *str) {
    while ('\0' != *str) {
        putc(*str++);
    }
}

int printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    char buf[PRINTF_MAX_BUF_SIZE];
    vsnprintf(buf, PRINTF_MAX_BUF_SIZE, fmt, args);
    uart_puts(buf);
    
    va_end(args);
    return 0;
}

int snprintf(char *str, size_t size, const char *fmt, ...) {
    if (size > PRINTF_MAX_BUF_SIZE) {
        return -1;
    }
    va_list args;
    va_start(args, fmt);
    vsnprintf(str, size, fmt, args);
    va_end(args);
    return 0;
}

// for now, only handle %u, %c, %s
// returns size of str?
int vsnprintf(char *str, size_t size, const char *fmt, va_list args) {
    if (NULL == str) {
        return -1;
    }

    char curr = 0;
    unsigned char test = 0;
    int fmt_next = 0;
    size_t arg_len = 0;
    char replace[VSNPRINTF_MAX_DIGITS];

    const char *fmt_ptr = fmt;
    while ('\0' != (curr = *fmt_ptr++) && size--) {
        if (fmt_next) {
            // curr should be u or x or some format character
            switch (curr) {
                case 'u':
                    // TODO: need to subtract the number of bytes that are copied here
                    // from the total
                    numtostr((unsigned int)va_arg(args, unsigned int), replace, &arg_len);
                    memcpy(str, replace, arg_len);
                    str += arg_len;
                    break;
                case 'x':
                    break;
                case 'c':
                    // va_arg() needs the type passed in to be int and then cast to (char)
                    // can't, e.g., call va_arg(args, char) - otherwise it doesn't return!
                    *str++ = (char)va_arg(args, int);
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
    return 0;
}