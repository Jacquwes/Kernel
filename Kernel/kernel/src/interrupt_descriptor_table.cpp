#include <cstring>

#include "global_descriptor_table.h"
#include "interrupt_descriptor_table.h"
#include "logger.h"
#include "pic.h"

extern void* isr_stub_table[];
extern void* irq_stub_table[];

namespace kernel
{
	interrupt_descriptor::interrupt_descriptor()
	{
		offset_low = 0;
		segment_selector = 0;
		reserved = 0;
		type_attributes = 0;
		offset_high = 0;
	}

	interrupt_descriptor::interrupt_descriptor(uint32_t offset, uint8_t _type_attributes)
	{
		offset_low = offset & 0xffff;
		segment_selector = (uint16_t)
			((uint32_t)&global_descriptor_table::instance->kernel_code_descriptor() - (uint32_t)&global_descriptor_table::instance->descriptors);
		reserved = 0;
		type_attributes = _type_attributes;
		offset_high = (offset >> 16) & 0xffff;
	}

	interrupt_descriptor_table::interrupt_descriptor_table()
	{
		logger::log(debug, "Interrupt descriptor table > Initializing.");

		pic::init();

		std::memset(descriptors, 0, sizeof(interrupt_descriptor) * 256);

		using namespace type_attributes;

		for (int i = 0; i < 0x20; i++)
		{
			descriptors[i] = interrupt_descriptor((uint32_t)isr_stub_table[i],
												  generate_type_attributes(gate_type::trap_gate_32, descriptor_privilege_level::ring0));
		}

		for (int i = 0x20; i < 0x22; i++)
		{
			descriptors[i] = interrupt_descriptor((uint32_t)irq_stub_table[i - 0x20],
												  generate_type_attributes(gate_type::interrupt_gate_32, descriptor_privilege_level::ring0));
		}


		interrupt_descriptor_table_register idtr;
		idtr.base = (uint32_t)&descriptors[0];
		idtr.limit = (uint16_t)sizeof(interrupt_descriptor) * 256 - 1;

		asm volatile ("lidt %0" : : "m" (idtr));
		__asm__ volatile ("sti");

		pic::unmask(0);
		pic::unmask(1);
		pic::unmask(pic::PIC_EOI);

		logger::log(debug, "Interrupt descriptor table > Initialized.");
	}
}
