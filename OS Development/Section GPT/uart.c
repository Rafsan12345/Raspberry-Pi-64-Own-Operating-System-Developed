/* Simple PL011 UART driver for Raspberry Pi 3 (aarch64)
 *
 * For Raspberry Pi 3 (BCM2837) the UART0 (PL011) base is 0x3F201000.
 * For Raspberry Pi 4 the peripheral base moved to 0xFE000000 and
 * UART0 base becomes 0xFE201000.
 *
 * If you use Pi 4, change UART_BASE below or set a define during build.
 */

#include <stdint.h>
#include "uart.h"

/* Default: Raspberry Pi 3 */
#ifndef UART_BASE
#define UART_BASE 0x3F201000UL
#endif

#define UART_DR   (*(volatile uint32_t *)(UART_BASE + 0x00))
#define UART_FR   (*(volatile uint32_t *)(UART_BASE + 0x18))
#define UART_IBRD (*(volatile uint32_t *)(UART_BASE + 0x24))
#define UART_FBRD (*(volatile uint32_t *)(UART_BASE + 0x28))
#define UART_LCRH (*(volatile uint32_t *)(UART_BASE + 0x2C))
#define UART_CR   (*(volatile uint32_t *)(UART_BASE + 0x30))
#define UART_IMSC (*(volatile uint32_t *)(UART_BASE + 0x38))
#define UART_ICR  (*(volatile uint32_t *)(UART_BASE + 0x44))

void uart_init(void) {
    /* This is a very minimal init sequence intended for QEMU and simple Pi setups.
       On real hardware you might need to configure GPIO ALT functions for TX/RX pins.
       For quick testing on QEMU this is sufficient. */
    UART_CR = 0x000;       /* disable */
    UART_ICR = 0x7FF;      /* clear interrupts */
    UART_IBRD = 1;         /* integer baud rate divisor (placeholder) */
    UART_FBRD = 40;        /* fractional divisor (placeholder) */
    UART_LCRH = (1 << 4);  /* 8-bit, no parity, one stop bit */
    UART_IMSC = 0;         /* disable interrupts */
    UART_CR = (1 << 0) | (1 << 8) | (1 << 9); /* enable UART, TX, RX */
}

void uart_putc(char c) {
    /* Wait for space in FIFO (TXFF = bit 5) */
    while (UART_FR & (1 << 5)) { __asm__ volatile("nop"); }
    UART_DR = (uint32_t)c;
}

void uart_puts(const char *s) {
    while (*s) {
        if (*s == '\\n') uart_putc('\\r');
        uart_putc(*s++);
    }
}