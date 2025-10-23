/* Simple linker script for a flat kernel image
 * places code at 0x80000 (typical for Raspberry Pi kernel8.img load address)
 */
ENTRY(_start)

SECTIONS
{
  . = 0x80000;
  .text : { *(.text*) }
  .rodata : { *(.rodata*) }
  .data : { *(.data*) }
  .bss : { *(.bss*) }
  /* reserve stack space after sections */
  . = ALIGN(8);
  _stack_top = . + 0x20000; /* 128KB stack */
}