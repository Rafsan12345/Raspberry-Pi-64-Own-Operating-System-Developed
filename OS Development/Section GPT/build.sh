#!/bin/bash
set -e
echo "Building minimal Raspberry Pi bare-metal image..."
aarch64-none-elf-as -o start.o start.S
aarch64-none-elf-gcc -ffreestanding -O2 -c uart.c -o uart.o
aarch64-none-elf-gcc -ffreestanding -O2 -c main.c -o main.o
aarch64-none-elf-ld -T linker.ld start.o uart.o main.o -o kernel8.elf
aarch64-none-elf-objcopy kernel8.elf -O binary kernel8.img
echo "Done: kernel8.img"