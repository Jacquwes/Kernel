cmake_minimum_required(VERSION 3.16)

project(kernel LANGUAGES C CXX ASM)

set(CMAKE_CXX_STANDARD 20)

file(
	GLOB_RECURSE KERNEL_CXX_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

file(
	GLOB_RECURSE KERNEL_ASM_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.s
)

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/asm.o
	COMMAND ${CMAKE_ASM_COMPILER} ${KERNEL_ASM_SOURCES} -o ${CMAKE_CURRENT_BINARY_DIR}/asm.o
	DEPENDS ${KERNEL_ASM_SOURCES}
	COMMENT "Assembling ${KERNEL_ASM_SOURCES}"
)



execute_process(
	COMMAND ${CMAKE_CXX_COMPILER} ${CMAKE_CXX_FLAGS} -print-file-name=crtbegin.o
	OUTPUT_VARIABLE CRTBEGIN
	OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
	COMMAND ${CMAKE_CXX_COMPILER} ${CMAKE_CXX_FLAGS} -print-file-name=crtend.o
	OUTPUT_VARIABLE CRTEND
	OUTPUT_STRIP_TRAILING_WHITESPACE
)

add_library(
	kernel
	${KERNEL_CXX_SOURCES}
	${CMAKE_CURRENT_BINARY_DIR}/asm.o
)

target_include_directories(
	kernel
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/../stl/include
)

target_link_libraries(kernel stl)
target_link_options(kernel PRIVATE -ffreestanding -nostdlib -lgcc -g)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffreestanding -Wall -Wextra -Wunknown-pragmas -fno-exceptions -fno-rtti -std=c++20")

add_executable(
	kernel.elf
	${KERNEL_CXX_SOURCES}
	${CMAKE_CURRENT_BINARY_DIR}/asm.o
)

target_include_directories(
	kernel.elf
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/../stl/include
)

target_link_libraries(kernel.elf kernel stl)

add_custom_command(
	TARGET kernel.elf POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
			${CMAKE_CURRENT_BINARY_DIR}/../a.out
			${CMAKE_CURRENT_BINARY_DIR}/kernel.elf
	COMMENT "Copying kernel.elf to kernel directory"
)

install(
	TARGETS kernel.elf
	RUNTIME DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/../iso/boot/
)
