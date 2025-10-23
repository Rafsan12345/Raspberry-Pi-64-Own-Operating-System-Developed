# Minimal Raspberry Pi Bare-metal Skeleton (aarch64)
This is a tiny starter project for Raspberry Pi bare-metal development (64-bit).
It provides a minimal UART driver and a simple `kernel_main` that prints to UART
and blinks (prints dots) in a loop.

## Files
- `start.S`   : Assembly entry, sets SP and calls `kernel_main`
- `main.c`    : Kernel entry, initializes UART and runs main loop
- `uart.c`    : Very small PL011 UART init/send driver
- `uart.h`    : UART header
- `linker.ld` : Linker script places code at 0x80000 and defines stack top
- `Makefile`  : Build helper (requires aarch64-none-elf-* toolchain)
- `build.sh`  : Simple build script (same as Makefile targets)

## Prerequisites
Install cross-toolchain on Ubuntu/Debian:

```bash
sudo apt update
sudo apt install gcc-aarch64-linux-gnu build-essential qemu-system-aarch64
```
Or install an actual bare-metal toolchain (recommended):
```bash
sudo apt-get install gcc-aarch64-none-elf binutils-aarch64-none-elf
```

Note: package names vary by distro. You can also use prebuilt toolchains.

## Build
Use either Makefile or build.sh:
```bash
make
# or
./build.sh
```
After build you should have `kernel8.img`.

## Test in QEMU
Run (QEMU must be configured with raspi machine support):
```bash
qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial stdio
```

## Deploy to SD card
1. Format an SD card and create a FAT32 boot partition.
2. Copy required Raspberry Pi firmware files to the boot partition:
   - `bootcode.bin`, `start.elf`, `fixup.dat`, plus others from the official firmware repo.
3. Copy `kernel8.img` into the boot partition and add `config.txt`:
   ```
   kernel=kernel8.img
   arm_64bit=1
   ```
4. Insert SD card into Raspberry Pi and power on. Use UART serial or HDMI monitor
   (if framebuffer code added) to see output.

## Pi 3 vs Pi 4
- Pi 3 PL011 UART base: `0x3F201000` (default in this project)
- Pi 4 PL011 UART base: `0xFE201000` (define UART_BASE=0xFE201000 when building for Pi4)
  e.g. `CFLAGS="-DUART_BASE=0xFE201000" make`

## Important
- This project is intentionally minimal for learning. Many things are simplified
  or omitted (GPIO ALT config for UART pins, proper baud rate divisors, cache/MMU setup).
- Use as a learning skeleton, not production code.