#include "logger.h"

#include <cstdio>

namespace kernel
{
	uint8_t logger::canals = log_canal::none;

	void logger::log(const char* format, ...)
	{
		__builtin_va_list list;
		__builtin_va_start(list, format);
		log(info, format, list);
		__builtin_va_end(list);
	}

	void logger::log(log_canal canal, const char* format, ...)
	{
		if ((canals & canal) == 0)
			return;
		__builtin_va_list list;
		__builtin_va_start(list, format);
		log(canal, format, list);
		__builtin_va_end(list);
	}

	void logger::log(log_canal canal, const char* format, __builtin_va_list args)
	{
		if ((canals & canal) == 0)
			return;

		switch (canal)
		{
		case log_canal::error:
		{
			output::instance->set_color({ vga_color::black, vga_color::red });
			break;
		}
		case log_canal::warning:
		{
			output::instance->set_color({ vga_color::black, vga_color::yellow });
			break;
		}
		case log_canal::info:
		{
			output::instance->set_color({ vga_color::black, vga_color::gray });
			break;
		}
		case log_canal::debug:
		{
			output::instance->set_color({ vga_color::black, vga_color::blue });
			break;

		}
		case log_canal::success:
		{
			output::instance->set_color({ vga_color::black, vga_color::green });
			break;
		}
		default:
			break;
		}

		output::instance->putchar(' ');

		switch (canal)
		{
		case log_canal::error:
		{
			output::instance->set_color({ vga_color::red, vga_color::black });
			break;
		}
		case log_canal::warning:
		{
			output::instance->set_color({ vga_color::yellow, vga_color::black });
			break;
		}
		case log_canal::info:
		{
			output::instance->set_color({ vga_color::gray, vga_color::black });
			break;
		}
		case log_canal::debug:
		{
			output::instance->set_color({ vga_color::blue, vga_color::black });
			break;
		}
		case log_canal::success:
		{
			output::instance->set_color({ vga_color::green, vga_color::black });
			break;
		}
		default:
			break;
		}

		output::instance->putchar(' ');
		std::vprintf(format, args);
		output::instance->putchar('\n');
	}

	void logger::set_canals(uint8_t canals_)
	{
		canals = canals_;
	}
}