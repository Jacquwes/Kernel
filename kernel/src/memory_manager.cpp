#include "logger.h"
#include "kernel.h"
#include "memory_manager.h"

namespace kernel
{
	memory_manager* memory_manager::instance = nullptr;

	memory_manager::memory_manager(multiboot_info_t* info, uint32_t const& magic)
	{
		logger::log(kernel::info, "Memory manager > Initializing.");

		instance = this;

		if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
		{
			logger::log(error, "Memory manager > Error during initialization: incorrect magic number.");
			ec = INVALID_MULTIBOOT_MAGIC;
			return;
		}

		if (!(info->flags >> 6 & 1))
		{
			logger::log(error, "Memory manager > Error during initialization: invalid multiboot flags.");
			ec = INVALID_MULTIBOOT_FLAGS;
			return;
		}

		memory_page* last_page = nullptr;

		for (std::size_t i = 0; i < info->mmap_length; i += sizeof(multiboot_memory_map_t))
		{
			auto map_entry = reinterpret_cast<multiboot_memory_map_t*>(info->mmap_addr + i);

			logger::log(kernel::debug, "Memory manager > Memory map entry > Address: %x, Length: %x, Type: %x", map_entry->addr, map_entry->len, map_entry->type);

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

		logger::log(kernel::info, "Memory manager > Initialized.");
	}

	memory_manager::~memory_manager()
	{
		instance = nullptr;
	}

	void memory_manager::display_pages() const
	{
		logger::log(info, "Memory manager > Pages:");
		for (memory_page* i = first_page; i; i = i->next)
		{
			logger::log(info, "        %x : length: %x, next: %x, previous: %x, %s", i, i->length, i->next, i->previous, i->allocated ? "allocated" : "");
		}
	}

	void* memory_manager::allocate(std::size_t size)
	{
		logger::log(debug, "Memory manager > Allocating %x bytes.", size);

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

		if (!result)
		{
			logger::log(error, "Memory manager > Error during allocation: not enough memory.");
			return nullptr;
		}

		logger::log(debug, "Memory manager > Found page at %x.", result);

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

		display_pages();

		logger::log(debug, "Memory manager > Allocated %x bytes at %x.", size, result);

		return (char*)result + sizeof(memory_page);
	}

	void memory_manager::deallocate(void* ptr)
	{
		logger::log(debug, "Memory manager > Deallocating %x.", ptr);

		memory_page* i = first_page;

		while (i && (uint8_t*)ptr - sizeof(memory_page) != (uint8_t*)i)
			i = i->next;

		if (!i)
		{
			logger::log(error, "Memory manager > Trying to deallocate unallocated memory at %x.", ptr);
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

		display_pages();

		logger::log(debug, "Memory manager > Deallocated %x.", ptr);
	}
}