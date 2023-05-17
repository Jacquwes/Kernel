#include <cstdio>
#include <cstring>

#include <logger.h>
#include <pic.h>

namespace kernel
{
	output* output::instance = nullptr;
	vga_colorset output::colorset = { vga_color::gray, vga_color::black };

	output::output()
	{
		instance = this;
		logger::log(info, "Output > Initialized.");
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
			cursor_x = 0;
			cursor_y++;

			move_cursor(cursor_x, cursor_y);

			return;
		}

		if (c == '\b')
		{
			if (cursor_x == 0)
			{
				cursor_x = VGA_WIDTH - 1;
				cursor_y--;
			}
			else
				cursor_x--;

			VGA_ADDRESS[(cursor_y * VGA_WIDTH) + cursor_x] = ' ' | (7 << 8);

			move_cursor(cursor_x, cursor_y);

			return;
		}

		if (c == '\t')
		{
			cursor_x += (cursor_x % 4) == 0 ? 4 : cursor_x % 4;

			if (cursor_x >= VGA_WIDTH)
			{
				cursor_x = 0;
				cursor_y++;
			}

			move_cursor(cursor_x, cursor_y);

			return;
		}

		VGA_ADDRESS[(cursor_y * VGA_WIDTH) + cursor_x] = c | (colorset.foreground << 8) | (colorset.background << 12);

		cursor_x++;

		if (cursor_x >= VGA_WIDTH)
		{
			cursor_x = 0;
			cursor_y++;
		}

		if (cursor_y >= VGA_HEIGHT)
			scroll();
		else
			move_cursor(cursor_x, cursor_y);
	}

	void output::scroll(uint8_t const& lines)
	{
		std::memcpy(VGA_ADDRESS, VGA_ADDRESS + VGA_WIDTH, VGA_WIDTH * (VGA_HEIGHT - 1));

		cursor_x = 0;
		cursor_y -= lines;

		if (cursor_y < 0)
			cursor_y = 0;

		for (uint8_t i = 0; i < lines; i++)
			VGA_ADDRESS[(VGA_HEIGHT - 1) * VGA_WIDTH + i] = ' ' | (7 << 8);

		move_cursor(cursor_x, cursor_y);
	}

	void output::set_color(vga_colorset const& colorset_)
	{
		colorset = colorset_;
	}
}