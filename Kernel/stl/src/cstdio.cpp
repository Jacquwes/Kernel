#include <cmath>
#include <cstdio>
#include <cstdlib>

#include <output.h>

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

	int vprintf(const char* format, __builtin_va_list list)
	{
		int printed = 0;

		for (const char* c = format; *c != 0; c++)
		{
			if (*c != '%')
			{
				kernel::output::instance->putchar(*c);
				printed++;
				continue;
			}

			switch (*(++c))
			{
			case 'c':
			{
				uint8_t value = __builtin_va_arg(list, int);
				
				kernel::output::instance->putchar(value);

				printed++;
				
				break;
			}
			case'x':
			{
				uint32_t value = __builtin_va_arg(list, uint32_t);

				kernel::output::instance->putchar('0');
				kernel::output::instance->putchar('x');
				printed += 2;

				if (!value)
				{
					kernel::output::instance->putchar('0');
					printed++;
					break;
				}

				size_t size = log2_binary(value) / log2_binary(16) + 2;

				char string[size];
				itoa(string, size, value, 16);

				for (size_t i = 0; i < size - 1; i++)
				{
					printed++;
					kernel::output::instance->putchar(string[i]);
				}

				break;
			}
			case 'd':
			{
				int value = __builtin_va_arg(list, int);

				if (value < 0)
				{
					kernel::output::instance->putchar('-');
					value = -value;
					printed++;
				}

				if (!value)
				{
					kernel::output::instance->putchar('0');
					printed++;
					break;
				}

				size_t size = log10_binary(value) + 2;

				char string[size];
				itoa(string, size, value);

				for (size_t i = 0; i < size - 1; i++)
				{
					kernel::output::instance->putchar(string[i]);
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