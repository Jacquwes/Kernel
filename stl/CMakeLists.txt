cmake_minimum_required(VERSION 3.16)

project(stl CXX)

set(CMAKE_CXX_STANDARD 20)

file(
	GLOB_RECURSE
	SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -ffreestanding -Wall -Wextra -fno-exceptions -fno-rtti -std=c++20")

add_library(stl ${SOURCES})

target_include_directories(
	stl
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/../kernel/include
)

target_link_libraries(
	stl
	PRIVATE
	kernel
)