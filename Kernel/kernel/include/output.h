#pragma once

#include <cstdint>

namespace kernel
{
	#define VGA_ADDRESS reinterpret_cast<uint16_t*>(0xb8000)
	constexpr uint8_t VGA_WIDTH = 80;
	constexpr uint8_t VGA_HEIGHT = 25;

	class output
	{
	public:
		output();

		static output* instance;

		void putchar(char const& c);
		void scroll(uint8_t const& lines = 1);

	private:
		uint8_t cursorX = 0;
		uint8_t cursorY = 0;
	};
}
