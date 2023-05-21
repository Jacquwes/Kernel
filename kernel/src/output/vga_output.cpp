#include <cstdio>
#include <cstring>

#include <logger.h>
#include <pic.h>

namespace kernel
{
	vga_output* vga_output::instance = nullptr;
	vga_colorset vga_output::colorset = { vga_color::gray, vga_color::black };

	vga_output::vga_output()
	{
		instance = this;
		logger::log(info, "Output > Initialized.");
	}

	void vga_output::move_cursor(uint8_t const& x, uint8_t const& y)
	{
		uint16_t pos = y * VGA_WIDTH + x;

		pic::outb(0x3d4, 0x0f);
		pic::outb(0x3d5, pos & 0xff);
		pic::outb(0x3d4, 0x0e);
		pic::outb(0x3d5, (pos >> 8) & 0xff);
	}

	void vga_output::putchar(char const& c)
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

	void vga_output::scroll()
	{
		wchar_t screen_copy[VGA_WIDTH * VGA_HEIGHT] = { ' ' | 7 << 8 };
		std::memcpy(screen_copy, VGA_ADDRESS + VGA_WIDTH, VGA_WIDTH * (VGA_HEIGHT - 1) * sizeof(wchar_t));
		std::memcpy(VGA_ADDRESS, screen_copy, VGA_WIDTH * VGA_HEIGHT * sizeof(wchar_t));

		cursor_y--;
		cursor_x = 0;

		move_cursor(cursor_x, cursor_y);
	}

	void vga_output::set_color(vga_colorset const& colorset_)
	{
		colorset = colorset_;
	}
}