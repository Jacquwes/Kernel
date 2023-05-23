#include "kernel.h"

static inline bool are_interrupts_enabled()
{
	unsigned long flags;
	asm volatile ("pushf\n\t"
				  "pop %0"
				  : "=g"(flags));
	return flags & (1 << 9);
}

#include <vector>

void main(multiboot_info_t* info, uint32_t magic)
{
	kernel::logger::set_canals(kernel::log_canal::all);
	kernel::vga_output();
	kernel::serial_output();
	auto mem = kernel::memory_manager(info, magic);
	mem.display_pages();
	kernel::global_descriptor_table();
	kernel::interrupt_descriptor_table();
	kernel::keyboard_manager();
	kernel::pci_manager();

	std::vector<char> v;

	v.push_back('1');
	v.push_back('2');
	v.push_back('3');
	v.push_back('4');

	for (auto& e : v)
		std::printf("Vector > Element %c\n", e);

	mem.display_pages();

	for (;;)
		__asm__ volatile ("hlt");
}