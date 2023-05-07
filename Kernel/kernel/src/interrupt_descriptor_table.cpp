#include "interrupt_descriptor_table.h"

namespace kernel
{
	interrupt_descriptor::interrupt_descriptor(uint32_t base, uint16_t _selector, uint8_t _flags)
	{
		base_low = base & 0xffff;
		base_high = (base >> 16) & 0xffff;
		selector = _selector;
		zero = 0;
		flags = _flags;
	}

	interrupt_descriptor_table::interrupt_descriptor_table(global_descriptor_table& gdt)
	{

	}
}