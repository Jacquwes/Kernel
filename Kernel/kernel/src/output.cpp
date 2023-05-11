#include <cstdio>
#include <cstring>

#include <output.h>
#include <pic.h>

namespace kernel
{
	output* output::instance = nullptr;

	output::output()
	{
		instance = this;
		std::printf("Output > Initialized.\n");
	}

	void output::move_cursor(uint8_t const& x, uint8_t const& y)
	{
		uint16_t pos = y * VGA_WIDTH + x;

		pic::outb(0x3d4, 0x0f);
		pic::outb(0x3d5, pos & 0xff);
		pic::outb(0x3d4, 0x0e);
		pic::outb(0x3d5, (pos >> 8) & 0xff);
	}

	void output::putchar(char const& c)
	{
		if (c == '\n')
		{
			cursorX = 0;
			cursorY++;

			move_cursor(cursorX, cursorY);

			return;
		}

		if (c == '\b')
		{
			if (cursorX == 0)
			{
				cursorX = VGA_WIDTH - 1;
				cursorY--;
			}
			else
				cursorX--;

			VGA_ADDRESS[(cursorY * VGA_WIDTH) + cursorX] = ' ' | (7 << 8);

			move_cursor(cursorX, cursorY);

			return;
		}

		if (c == '\t')
		{
			cursorX += (cursorX % 4) == 0 ? 4 : cursorX % 4;

			if (cursorX >= VGA_WIDTH)
			{
				cursorX = 0;
				cursorY++;
			}

			move_cursor(cursorX, cursorY);

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
			scroll();
		else
			move_cursor(cursorX, cursorY);
	}

	void output::scroll(uint8_t const& lines)
	{
		std::memcpy(VGA_ADDRESS, VGA_ADDRESS + VGA_WIDTH, VGA_WIDTH * (VGA_HEIGHT - 1));

		cursorX = 0;
		cursorY -= lines;

		if (cursorY < 0)
			cursorY = 0;

		for (uint8_t i = 0; i < lines; i++)
			VGA_ADDRESS[(VGA_HEIGHT - 1) * VGA_WIDTH + i] = ' ' | (7 << 8);

		move_cursor(cursorX, cursorY);
	}
}