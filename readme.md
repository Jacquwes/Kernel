# Kernel

This project hosts an x86 kernel running with grub and a partial human
readable implementation of the C++ Standard Library.

## Pre-requisites

- `build-essential`
- `bison`
- `flex`
- `libgmp3-dev`
- `libmpc-dev`
- `libmpfr-dev`
- `texinfo`
- qemu-i386

## Build

Run `make build`. The kernel can be debugged using gdb on localhost:1234.

## Usage

Run `make start`, the kernel will start inside a qemu-i386 emulator.

## Memory management

The kernel uses the information provided by Grub via the multiboot header
to manage memory. Each chunk of memory contains a descriptive struct and
acts like an element of a linked list.

## Output

The kernel uses the VGA output in text mode.