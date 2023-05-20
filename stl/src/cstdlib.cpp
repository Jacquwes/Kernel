#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cmath>

namespace std
{
	void itoa(char* string, size_t size, uint64_t n, int base)
	{
		size_t i = 0;
		do
		{
			char digit = n % base;
			string[size - i - 2] = (digit < 10) ? (digit + '0') : (digit + 'a' - 10);
			i++;
		} while (n /= base);

		string[size - 1] = 0;
	}
}