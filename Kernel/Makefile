i686-elf		= /usr/local/cross/bin/i686-elf
i686-elf-g++	= $(i686-elf)-g++
i686-elf-as		= $(i686-elf)-as

prefix			= /home/saucisse/projects/Kernel

cpp_flags		= -Iinclude -Istl/include -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -c
ld_flags		= -ffreestanding -O2 -nostdlib -lgcc

stl_sources		= $(wildcard stl/src/*.cpp)
stl_objects		= $(patsubst stl/src/%.cpp, build/stl/%.o, $(stl_sources))

kernel_sources	= $(wildcard kernel/src/*.cpp)
kernel_objects	= $(patsubst kernel/src/%.cpp, build/kernel/%.o, $(kernel_sources))


setup:
	cd $(prefix)
	mkdir -p build/kernel
	mkdir -p build/stl



boot: setup
	$(i686-elf-as) kernel/src/boot.asm -o build/kernel/boot.o



build/stl/%.o: stl/src/%.cpp
	$(i686-elf-g++) -c $< -o $@ $(cpp_flags)

stl: $(stl_objects)



build/kernel/%.o: kernel/src/%.cpp
	$(i686-elf-g++) -c $< -o $@ $(cpp_flags)

kernel: $(kernel_objects)

	

link: boot stl kernel
	$(i686-elf-g++) -T linker.ld -o build/os.bin build/kernel/*.o build/stl/*.o $(ld_flags)

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
