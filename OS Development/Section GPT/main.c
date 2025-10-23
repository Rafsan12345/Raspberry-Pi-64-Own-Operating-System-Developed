/* Minimal kernel_main for Raspberry Pi (UART + LED blink example)
 *
 * Notes:
 * - This code is a simple skeleton for bare-metal development.
 * - Uses simple busy-wait delays and memory-mapped I/O registers.
 * - Adjust UART_BASE for Raspberry Pi 3 vs Pi 4 as noted in README.
 *
 * Build with aarch64-none-elf toolchain (see README).
 */

#include <stdint.h>

#include "uart.h"

/* simple delay */
static void delay(volatile unsigned long t) {
    while (t--) {
        __asm__ volatile("nop");
    }
}

void kernel_main(void) {
    /* initialize UART for debug output */
    uart_init();
    uart_puts("== Mini Baremetal OS (aarch64) ==\r\n");
    uart_puts("UART initialized. Blinking LED (if configured)...\r\n");

    /* If you wired an LED to GPIO 17 and implemented gpio functions,
       you may toggle it here. For now we just print a dot periodically. */
    while (1) {
        uart_puts(".\r\n");
        delay(0x400000);
    }
}