#include <cmath>
#include <cstdio>
#include <cstdlib>

#include <output.h>

#define print(c, stream)\
	if (stream == stdout)\
		kernel::vga_output::instance->putchar(c);\
	else if (stream == stderr)\
	{\
		kernel::vga_output::instance->set_color({ kernel::vga_color::red, kernel::vga_color::black });\
		kernel::vga_output::instance->putchar(c);\
		kernel::vga_output::instance->set_color({ kernel::vga_color::gray, kernel::vga_color::black });\
	}\
	else if (stream == stdserial)\
		kernel::serial_output::instance->putchar(c);\

namespace std
{
	int printf(const char* format, ...)
	{
		__builtin_va_list list;
		__builtin_va_start(list, format);
		int result = vprintf(format, list);
		__builtin_va_end(list);

		return result;
	}

	int fprintf(FILE* stream, const char* format, ...)
	{
		__builtin_va_list list;
		__builtin_va_start(list, format);
		int result = vfprintf(stream, format, list);
		__builtin_va_end(list);

		return result;
	}

	int vprintf(const char* format, __builtin_va_list list)
	{
		return vfprintf(stdout, format, list);
	}

	int vfprintf(FILE* stream, const char* format, __builtin_va_list list)
	{
		int printed = 0;

		for (const char* c = format; *c != 0; c++)
		{
			if (*c != '%')
			{
				print(*c, stream);
				printed++;
				continue;
			}

			switch (*(++c))
			{
			case '%':
			{
				print('%', stream);
				printed++;
				break;
			}
			case '*':
			{
				uint16_t color = __builtin_va_arg(list, int);

				kernel::vga_output::instance->set_color({ (kernel::vga_color)(color & 0xf), (kernel::vga_color)(color >> 8) });

				break;
			}
			case 's':
			{
				char* string = (char*)__builtin_va_arg(list, int);

				for (size_t i = 0; string[i]; i++)
				{
					print(string[i], stream);
					printed++;
				}

				break;
			}
			case 'c':
			{
				uint8_t value = __builtin_va_arg(list, int);

				print(value, stream);

				printed++;

				break;
			}
			case'x':
			{
				uint32_t value = __builtin_va_arg(list, uint32_t);

				print('0', stream);
				print('x', stream);
				printed += 2;

				if (!value)
				{
					print('0', stream);
					printed++;
					break;
				}

				size_t size = log2_binary(value) / log2_binary(16) + 2;

				char string[size];
				itoa(string, size, value, 16);

				for (size_t i = 0; i < size - 1; i++)
				{
					printed++;
					print(string[i], stream);
				}

				break;
			}
			case 'd':
			{
				int value = __builtin_va_arg(list, int);

				if (value < 0)
				{
					print('-', stream);
					value = -value;
					printed++;
				}

				if (!value)
				{
					print('0', stream);
					printed++;
					break;
				}

				size_t size = log10_binary(value) + 2;

				char string[size];
				itoa(string, size, value);

				for (size_t i = 0; i < size - 1; i++)
				{
					print(string[i], stream);
					printed++;
				}

				break;
			}
			default:
				break;
			}
		}

		return printed;
	}
}