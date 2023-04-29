#include <cstring>

namespace std
{
	void* memcpy(void* destination, const void* source, size_t count)
	{
		for (size_t i = 0; i < count; i++)
		{
			*(unsigned char*)(destination + i) = *(unsigned char*)(source + i);
		}
	}
}