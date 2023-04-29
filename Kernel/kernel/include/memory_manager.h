#pragma once

#include <cstdint>
#include <kernel.h>
#include <multiboot.h>

namespace kernel
{
	constexpr error_code INVALID_MULTIBOOT_MAGIC = 0x10000000;
	constexpr error_code INVALID_MULTIBOOT_FLAGS = 0x10000001;

	struct memory_page
	{
		memory_page* previous;
		bool allocated;
		std::size_t length;
		constexpr std::size_t allocatable() { return length - sizeof(memory_page); }
		memory_page* next;
	};

	class memory_manager
	{
	public:
		memory_manager(multiboot_info_t* info, uint32_t const& magic);
		~memory_manager();

		static memory_manager* instance;

		inline constexpr error_code const& get_error_code() const { return ec; }
		void display_pages();

		void* allocate(std::size_t size);
		void deallocate(void* ptr);

	private:
		error_code ec = SUCCESS;
		memory_page* first_page = nullptr;
	};
}