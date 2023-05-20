#pragma once

#include <cstdint>

namespace kernel
{
	#define VGA_ADDRESS reinterpret_cast<uint16_t*>(0xb8000)
	constexpr uint8_t VGA_WIDTH = 80;
	constexpr uint8_t VGA_HEIGHT = 25;

	enum vga_color : uint8_t
	{
		black = 0,
		blue = 1,
		green = 2,
		cyan = 3,
		red = 4,
		purple = 5,
		brown = 6,
		gray = 7,
		dark_gray = 8,
		light_blue = 9,
		light_green = 10,
		light_cyan = 11,
		light_red = 12,
		light_purple = 13,
		yellow = 14,
		white = 15
	};

	struct vga_colorset
	{
		vga_color foreground;
		vga_color background;
	};

	class output
	{
	public:
		output();

		static output* instance;

		void move_cursor(uint8_t const& x, uint8_t const& y);
		void putchar(char const& c);
		void scroll(uint8_t const& lines = 1);

		void set_color(vga_colorset const& colorset);

	private:
		uint8_t cursor_x = 0;
		uint8_t cursor_y = 0;

		static vga_colorset colorset;
	};
}
