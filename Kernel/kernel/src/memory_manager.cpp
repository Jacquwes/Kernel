#include <cstdio>

#include "kernel.h"
#include "memory_manager.h"

namespace kernel
{
	memory_manager* memory_manager::instance = nullptr;

	memory_manager::memory_manager(multiboot_info_t* info, uint32_t const& magic)
	{
		std::printf("Memory manager > Initializing.\n");

		instance = this;

		if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
		{
			std::printf("Memory manager > Error during initialization: incorrect magic number.\n");
			ec = INVALID_MULTIBOOT_MAGIC;
			return;
		}

		if (!(info->flags >> 6 & 1))
		{
			std::printf("Memory manager > Error during initialization: invalid multiboot flags.\n");
			ec = INVALID_MULTIBOOT_FLAGS;
			return;
		}

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

				continue;
			}

			last_page->next = reinterpret_cast<memory_page*>(map_entry->addr);
			memory_page* previous_page = last_page;

			last_page = (memory_page*)map_entry->addr;
			last_page->allocated = false;
			last_page->length = map_entry->len;
			last_page->previous = previous_page;
			last_page->next = nullptr;
		}

		std::printf("Memory manager > Initialized.\n");
	}

	memory_manager::~memory_manager()
	{
		instance = nullptr;
	}

	void memory_manager::display_pages() const
	{
		std::printf("Memory manager > Pages:\n");
		for (memory_page* i = first_page; i; i = i->next)
		{
			std::printf("        %x : length: %x, next: %x, previous: %x, %s\n", i, i->length, i->next, i->previous, i->allocated ? "allocated" : "");
		}
	}

	void* memory_manager::allocate(std::size_t size)
	{
		memory_page* result = nullptr;

		memory_page* i = first_page;
		do
		{
			if (i->allocatable() >= size && !i->allocated)
			{
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

		return (char*)result + sizeof(memory_page);
	}

	void memory_manager::deallocate(void* ptr)
	{
		memory_page* i = first_page;

		while (i && ptr - sizeof(memory_page) != i)
			i = i->next;

		if (!i)
		{
			std::printf("Memory manager > Trying to deallocate unallocated memory at %x.\n", ptr);
			return;
		}

		if (i->next && !i->next->allocated)
		{
			i->length += i->next->length;
			i->next = i->next->next;
			if (i->next->next)
				i->next->next->previous = i;
		}

		if (i->previous && !i->previous->allocated)
		{
			i->previous->length += i->length;
			i->previous->next = i->next;
			if (i->next)
				i->next->previous = i->previous;

			i = i->previous;
		}

		i->allocated = false;
	}
}