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

	std::vector<char> v2 = v;

	v2.push_back('5');
	v2.push_back('6');
	v2.push_back('7');
	v2.push_back('8');

	for (int i = 0; i < 4; i++)
		std::printf("Vector > Element %d: %c\n", i, v.at(i));

	for (int i = 0; i < 4; i++)
		std::printf("Vector > Element %d: %c\n", i, v2.at(i));

	mem.display_pages();

	for (;;)
		__asm__ volatile ("hlt");
}