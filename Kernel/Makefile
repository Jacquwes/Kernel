i686-elf		= /usr/local/cross/bin/i686-elf
i686-elf-g++	= $(i686-elf)-g++
i686-elf-as		= $(i686-elf)-as
prefix = /home/saucisse/projects/Kernel
cpp_flags = -Iinclude -Istl/include -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -c
ld_flags = -ffreestanding -O2 -nostdlib -lgcc

setup:
	cd $(prefix)
	mkdir -p build

boot: setup
	$(i686-elf-as) src/boot.asm -o build/boot.o

stl: setup
	$(i686-elf-g++) stl/src/char_traits.cpp -o build/stl.o $(cpp_flags)

kernel: setup stl
	$(i686-elf-g++) src/kernel.cpp -o build/kernel.o $(cpp_flags)

link: boot kernel
	$(i686-elf-g++) -T linker.ld -o build/os.bin  build/boot.o build/kernel.o $(ld_flags)

build: link
	mkdir -p build/isodir/boot/grub
	cp build/os.bin build/isodir/boot/os.bin
	cp grub.cfg build/isodir/boot/grub/grub.cfg
	grub-mkrescue -o build/os.iso build/isodir
	rm -rf bin obj

start: build
	qemu-system-i386 -cdrom build/os.iso

clean:
	rm -rf build

rebuild: clean build
