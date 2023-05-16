#include "kernel.h"

static inline bool are_interrupts_enabled()
{
	unsigned long flags;
	asm volatile ("pushf\n\t"
				  "pop %0"
				  : "=g"(flags));
	return flags & (1 << 9);
}

void main(multiboot_info_t* info, uint32_t magic)
{
	kernel::logger::set_canals(kernel::log_canal::all);
	kernel::output();
	kernel::memory_manager(info, magic);
	kernel::global_descriptor_table();
	kernel::interrupt_descriptor_table();
	kernel::keyboard_manager();
	kernel::pci_manager();

	for (;;)
		__asm__ volatile ("hlt");
}