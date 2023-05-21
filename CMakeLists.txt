cmake_minimum_required(VERSION 3.16)

project(os)

add_subdirectory(kernel)
add_subdirectory(stl)

set(
	QEMU_FLAGS
	-s -drive format=raw,file=${CMAKE_CURRENT_BINARY_DIR}/disk.img,media=disk,if=none,id=disk -device ahci,id=ahci -device ide-hd,drive=disk,bus=ahci.0
)

add_custom_target(
	disk
	COMMAND rm -f ${CMAKE_CURRENT_BINARY_DIR}/disk.img
	COMMAND qemu-img create ${CMAKE_CURRENT_BINARY_DIR}/disk.img 512M
)

add_custom_target(
	iso
	COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/iso/boot/grub
	COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/kernel/grub.cfg ${CMAKE_CURRENT_BINARY_DIR}/iso/boot/grub
	COMMAND grub-mkrescue -o ${CMAKE_CURRENT_BINARY_DIR}/os.iso ${CMAKE_CURRENT_BINARY_DIR}/iso
)

add_custom_target(
	run
	COMMAND qemu-system-i386 -cdrom ${CMAKE_CURRENT_BINARY_DIR}/os.iso ${QEMU_FLAGS}
	DEPENDS iso
)