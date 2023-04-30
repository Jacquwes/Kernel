#include <cstdint>
#include <cstdio>
#include <memory>
#include <new>
#include <string>

#include <kernel.h>
#include <memory_manager.h>
#include <multiboot.h>
#include <output.h>


void main(multiboot_info_t* info, uint32_t magic)
{
	kernel::output();
	auto memory = kernel::memory_manager(info, magic);

	if (memory.get_error_code() != kernel::SUCCESS)
	{
		std::printf("kernel: Failed initializing memory manager. %x\n", memory.get_error_code());
		return;
	}


	char* arr1 = new char[64];
	char* arr2 = new char[64];
	char* arr3 = new char[64];
	char* arr4 = new char[64];
	char* arr5 = new char[64];

	delete[] arr1;
	delete[] arr5;
	delete[] arr3;
	delete[] arr2;
	delete[] arr4;

	// should display the same pages as before the allocations and deallocations
	memory.display_pages();
}