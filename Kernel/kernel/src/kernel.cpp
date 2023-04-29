#include <cstdint>
#include <cstdio>
#include <memory>
#include <new>
#include <string>

#include <kernel.h>
#include <memory_manager.h>
#include <multiboot.h>
#include <output.h>

#define LOG

void main(multiboot_info_t* info, uint32_t magic)
{
	kernel::output();
	auto memory = kernel::memory_manager(info, magic);

	if (memory.get_error_code() != kernel::SUCCESS)
	{
		std::printf("kernel: Failed initializing memory manager. %x\n", memory.get_error_code());
		return;
	}

	char* arr = new char[64];
	
	memory.display_pages();
	
	delete[] arr;

	memory.display_pages();
}