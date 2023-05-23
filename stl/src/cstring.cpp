#include <cstdint>
#include <cstring>

namespace std
{
	void* memcpy(void* destination, const void* source, size_t count)
	{
		for (size_t i = 0; i < count; i++)
		{
			*(uint8_t*)((uint8_t*)destination + i) = *(uint8_t*)((uint8_t*)source + i);
		}

		return destination;
	}

	void* memset(void* destination, int value, size_t count)
	{
		for (size_t i = 0; i < count; i++)
		{
			*(uint8_t*)((uint8_t*)destination + i) = (uint8_t)value;
		}

		return destination;
	}
}