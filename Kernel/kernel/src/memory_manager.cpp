#include <cstdio>

#include "memory_manager.h"

namespace kernel
{
	memory_manager* memory_manager::instance = nullptr;

	memory_manager::memory_manager(multiboot_info_t* info, uint32_t const& magic)
	{
		std::printf("kernel: Initializing memory manager.\n");
			
		instance = this;

		if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
		{
			std::printf("kernel: Error during memory manager initialization: incorrect magic number.\n");
			ec = INVALID_MULTIBOOT_MAGIC;
			return;
		}

		if (!(info->flags >> 6 & 1))
		{
			std::printf("kernel: Error during memory manager initialization: invalid multiboot flags.\n");
			ec = INVALID_MULTIBOOT_FLAGS;
			return;
		}

		std::printf("kernel: Multiboot info is OK.\n", info->mmap_length / sizeof(multiboot_memory_map_t));
		//std::printf("kernel: Allocatable memory: lower: %x, upper: %x\n", info->mem_lower, info->mem_upper);
		//
		//uint32_t heap_size = 0x00a0'0000;
		//first_page = reinterpret_cast<memory_page*>(heap_size);
		//first_page->allocated = false;
		//first_page->length = info->mem_upper - heap_size - 0x2800;
		//first_page->next = nullptr;
		//first_page->previous = nullptr;

		//std::printf("kernel: Will use %x to %x, size of %x\n", first_page, first_page + first_page->length, first_page->length);

		memory_page* last_page = nullptr;

		for (std::size_t i = 0; i < info->mmap_length; i += sizeof(multiboot_memory_map_t))
		{
			auto map_entry = reinterpret_cast<multiboot_memory_map_t*>(info->mmap_addr + i);

			if (map_entry->type != MULTIBOOT_MEMORY_AVAILABLE)
				continue;

			if (!first_page)
			{
				if (!map_entry->addr)
					first_page = reinterpret_cast<memory_page*>(1);
				else
					first_page = reinterpret_cast<memory_page*>(map_entry->addr);
				first_page->allocated = false;
				first_page->length = map_entry->len;
				first_page->previous = nullptr;
				first_page->next = nullptr;
				last_page = first_page;

				std::printf("        first page: address: %x, length: %x\n", first_page, first_page->length);
				continue;
			}

			last_page->next = reinterpret_cast<memory_page*>(map_entry->addr);
			memory_page* previous_page = last_page;

			last_page = (memory_page*)map_entry->addr;
			last_page->allocated = false;
			last_page->length = map_entry->len;
			last_page->previous = previous_page;
			last_page->next = nullptr;
			
			std::printf("        next page: address: %x, length: %x\n", last_page, last_page->length);
		}
	}

	memory_manager::~memory_manager()
	{
		instance = nullptr;
	}

	void memory_manager::display_pages()
	{
		std::printf("kernel: Memory pages:\n");
		for (memory_page* i = first_page; i; i = i->next)
		{
			std::printf("        %x : length: %x, next: %x, previous: %x\n", i, i->length, i->next, i->previous);
	}
	}

	void* memory_manager::allocate(std::size_t size)
	{
		memory_page* result = nullptr;

		std::printf("kernel: Allocate %x bytes.\n", size);

		memory_page* i = first_page;
		do
		{			
			if (i->allocatable() >= size && !i->allocated)
			{
				std::printf("kernel: Found allocatable page at %x.\n", i);
				result = i;
			}

			if (i->next)
				i = i->next;
		} while (i->next && !result);

		memory_page* temp_next = result->next;
		std::size_t temp_length = result->length;

		result->length = size + sizeof(memory_page);
		result->allocated = true;
		result->next = (memory_page*)((char*)result + sizeof(memory_page) + size);

		result->next->allocated = false;
		result->next->length = temp_length - size - sizeof(memory_page);
		result->next->previous = result;
		result->next->next = temp_next;
		if (result->next->next)
			result->next->next->previous = result->next;

		result->length = size + sizeof(memory_page);
		result->allocated = true;
		result->next = result + result->length;

		std::printf("kernel: Allocated page:\n");
		std::printf("        address: %x, length: %x, next: %x, previous: %x\n", result, result->length, result->next, result->previous);

		return (char*)result + sizeof(memory_page);
	}

	constexpr void memory_manager::deallocate(uintptr_t ptr, std::size_t size)
	{

	}
}