#include <cstdint>
#include <cstdio>
#include <memory>
#include <new>
#include <string>

#include <kernel.h>
#include <global_descriptor_table.h>
#include <interrupt_descriptor_table.h>
#include <keyboard_manager.h>
#include <memory_manager.h>
#include <multiboot.h>
#include <output.h>
#include <pci.h>

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
	kernel::output();
	kernel::memory_manager(info, magic);
	kernel::global_descriptor_table();
	kernel::interrupt_descriptor_table();
	kernel::keyboard_manager();
	kernel::pci_manager();

	for (;;)
		__asm__ volatile ("hlt");
}