#include <stddef.h>
#include <kernel/uart0.h>
#include <kernel/gpio.h>

// delay function 
static inline void delay(uint32_t count) {
    asm volatile("__delay_%=: subs %[count], %[count], #1; bne __delay_%=\n" : "=r"(count): [count]"0"(count) : "cc");
}

void uart_putc(unsigned char c) {
    volatile UART0_PERIPH * const uart0 = (volatile UART0_PERIPH *)UART0_BASE_ADDR;
    while (uart0->flags.busy) { }
    uart0->data.data = c;
}

void uart_puts(const char *str) {
    for (size_t i = 0; str[i] != '\0'; i++) {
        uart_putc((unsigned char)str[i]);
    }
}

int uart0_init(void) {
    volatile UART0_PERIPH * const uart0 = (volatile UART0_PERIPH *)UART0_BASE_ADDR;
    volatile GPIO_PERIPH * const gpio = (volatile GPIO_PERIPH *)GPIO_BASE_ADDR;
    
    // test sequence - taken from osdev
    uart0->control.val = 0x0;

    // disable all pull up/down
    gpio->pin_pull_up_down_en.val = 0x0;
    delay(150);

    // disable pull up/down for pin 14, 15
    gpio->pin_pull_clock_0.val = (1 << 14) | (1 << 15);
    delay(150);

    // write 0 to pull clock to make it take effect
    gpio->pin_pull_clock_0.val = 0x0;

    // clear pending interrupts
    uart0->int_clear.val = 0x7FF;

    // setting baud rate
    uart0->int_baud_rate_div.val = 1;
    uart0->frac_baud_rate_div.val = 40;

    // enable fifo and 8 bit data transmission (1 stop bit, no parity)
    uart0->line_control.val = (1 << 4) | (1 << 5) | (1 << 6);

    // mask all interrupts
    uart0->int_mask_set_clear.val = (1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10);

    // enable UART0, receive and transfer part of UART
    uart0->control.val = (1 << 0) | (1 << 8) | (1 << 9);
    return 0;
}