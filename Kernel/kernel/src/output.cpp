#include <cstdio>

#include <output.h>

namespace kernel
{
	output* output::instance = nullptr;

	output::output()
	{
		instance = this;
		std::printf("kernel: Output initialized.\n");
	}

	void output::putchar(char const& c)
	{
		if (c == '\n')
		{
			cursorX = 0;
			cursorY++;
			return;
		}

		VGA_ADDRESS[(cursorY * VGA_WIDTH) + cursorX] = c | (7 << 8);

		cursorX++;

		if (cursorX >= VGA_WIDTH)
		{
			cursorX = 0;
			cursorY++;
		}

		if (cursorY >= VGA_HEIGHT)
			;//scroll();
	}

	void output::scroll(uint8_t const& lines)
	{
		for (std::size_t i = 0; i < lines; i++)
		{
			cursorX = cursorY = 0;
			for (uint16_t cursor = 0; cursor < VGA_WIDTH * (VGA_HEIGHT - 1); cursor++)
				putchar(VGA_ADDRESS[(cursorY + 1) * VGA_WIDTH + cursorX]);
			for (uint16_t cursor = 0; cursor < VGA_WIDTH; cursor++)
				VGA_ADDRESS[(cursorY * VGA_WIDTH) + cursorX] = ' ' | (7 << 8);
		}
	}
}