/* Minimal ARM64 entry: set SP and branch to kernel_main */
.section .text
.global _start
.balign 4
_start:
    /* Set up a simple stack. The address is chosen relative to load address.
       Linker script defines _stack_top symbol. */
    ldr x0, =_stack_top
    mov sp, x0

    /* Call kernel_main (C entry point) */
    bl kernel_main

/* If kernel_main returns, loop forever */
1: b 1b