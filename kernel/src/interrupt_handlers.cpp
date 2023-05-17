#include <cstdio>

#include "interrupt_descriptor_table.h"
#include "keyboard_manager.h"
#include "pic.h"

extern "C" void irq_handler(uint32_t irq)
{
	if (irq == 1)
	{
		uint8_t scancode = kernel::pic::inb(0x60);
		kernel::keyboard_manager::instance->handle_scancode(static_cast<kernel::keyboard_scancodes::keyboard_scancode>(scancode));
	}

	kernel::pic::send_eoi(irq);
}