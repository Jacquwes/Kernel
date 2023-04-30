i686-elf		= /usr/local/cross/bin/i686-elf
i686-elf-g++	= $(i686-elf)-g++
i686-elf-as		= $(i686-elf)-as

prefix			= /home/saucisse/projects/Kernel

cpp_flags		= -Iinclude -Istl/include -Ikernel/include -g -ffreestanding -Wall -Wextra -fno-exceptions -fno-rtti -c -std=c++20
ld_flags		= -ffreestanding -nostdlib -lgcc -g

stl_sources		= $(wildcard stl/src/*.cpp)
stl_objects		= $(patsubst stl/src/%.cpp, build/stl/%.o, $(stl_sources))

kernel_sources	= $(wildcard kernel/src/*.cpp)
kernel_objects	= $(patsubst kernel/src/%.cpp, build/kernel/%.o, $(kernel_sources))

boot_sources	= $(wildcard kernel/src/*.s)
boot_objects	= $(patsubst kernel/src/%.s, build/kernel/%.o, $(boot_sources))

crtbegin_object = $(shell $(i686-elf-g++) $(cpp_flags) -print-file-name=crtbegin.o)
crtend_object = $(shell $(i686-elf-g++) $(cpp_flags) -print-file-name=crtend.o)


deps:
	sudo apt install build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo qemu-system-x86


setup:
	cd $(prefix)
	mkdir -p build/kernel
	mkdir -p build/stl



build/kernel/%.o: kernel/src/%.asm
	$(i686-elf-as) $< -o $@

boot: $(boot_objects)



build/stl/%.o: stl/src/%.cpp
	$(i686-elf-g++) -c $< -o $@ $(cpp_flags)

stl: $(stl_objects)



build/kernel/%.o: kernel/src/%.cpp
	$(i686-elf-g++) -c $< -o $@ $(cpp_flags)

kernel: $(kernel_objects)

	

link: boot stl kernel
	$(i686-elf-g++) -T linker.ld -o build/os.bin $(kernel_objects) $(stl_objects) $(boot_objects) $(crtbegin_object) $(crtend_object) $(ld_flags)

build: setup link
	mkdir -p build/isodir/boot/grub
	cp build/os.bin build/isodir/boot/os.bin
	cp grub.cfg build/isodir/boot/grub/grub.cfg
	grub-mkrescue -o build/os.iso build/isodir
	rm -rf bin obj

start: build
	qemu-system-i386 -cdrom build/os.iso -s

clean:
	rm -rf build

rebuild: clean build
