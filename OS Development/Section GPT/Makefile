# Minimal Makefile for building kernel8.img
TOOLCHAIN_PREFIX := aarch64-none-elf-
CC := $(TOOLCHAIN_PREFIX)gcc
AS := $(TOOLCHAIN_PREFIX)as
LD := $(TOOLCHAIN_PREFIX)ld
OBJCOPY := $(TOOLCHAIN_PREFIX)objcopy
CFLAGS := -ffreestanding -O2 -Wall -nostdlib -fno-builtin
LDFLAGS := -T linker.ld

SRCS := start.S main.c uart.c
OBJS := $(SRCS:.c=.o)
OBJS := $(OBJS:.S=.o)

all: kernel8.img

start.o: start.S
\t$(AS) -o $@ $<

main.o: main.c uart.h
\t$(CC) $(CFLAGS) -c -o $@ main.c

uart.o: uart.c uart.h
\t$(CC) $(CFLAGS) -c -o $@ uart.c

kernel8.elf: $(OBJS) linker.ld
\t$(LD) $(LDFLAGS) -o $@ $(OBJS)

kernel8.img: kernel8.elf
\t$(OBJCOPY) kernel8.elf -O binary kernel8.img

clean:
\trm -f *.o *.elf *.img