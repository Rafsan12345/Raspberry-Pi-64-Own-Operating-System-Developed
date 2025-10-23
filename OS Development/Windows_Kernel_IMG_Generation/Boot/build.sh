#!/bin/bash

# Assemble boot.s
aarch64-none-elf-gcc -c boot.s -o boot.o

# Compile main.c
aarch64-none-elf-gcc -std=c99 -ffreestanding -mgeneral-regs-only -c main.c -o main.o

# Link to create kernel ELF
aarch64-none-elf-ld -nostdlib -T link.lds -o kernel boot.o main.o

# Convert ELF to binary for Raspberry Pi
aarch64-none-elf-objcopy -O binary kernel kernel8.img

echo "Build finished: kernel8.img created."
