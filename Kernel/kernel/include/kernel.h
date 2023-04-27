#pragma once

#include <cstdint>

namespace kernel
{
	typedef uint32_t error_code;

	constexpr error_code SUCCESS = 0x00000000;

	inline void print(char c, int x = 0, int y = 0)
	{
		uint16_t* videoMemory = (uint16_t*)0xb8000;
		videoMemory[(y * 80) + x] = c | (15 << 8);
	}
}