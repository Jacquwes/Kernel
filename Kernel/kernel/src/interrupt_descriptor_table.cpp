#include <cstdio>
#include <cstring>

#include "interrupt_descriptor_table.h"
#include "global_descriptor_table.h"

extern "C" __attribute__((noreturn)) void exception_handler(void);
void exception_handler(void)
{
	std::printf("kernel: Exception handler called.\n");
	while (true);
}

extern void* isr_stub_table[];

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
		std::printf("Interrupt descriptor table > Initializing.\n");

		std::memset(descriptors, 0, sizeof(descriptors));

		std::memset(descriptors, 0, sizeof(interrupt_descriptor) * 256);

		using namespace type_attributes;

		for (int i = 0; i < 0x20; i++)
		{
			descriptors[i] = interrupt_descriptor((uint32_t)isr_stub_table[i],
												  generate_type_attributes(gate_type::trap_gate_32, descriptor_privilege_level::ring0));
		}

		{
			descriptors[i] = interrupt_descriptor(
				(uint32_t)isr_stub_table[i],
				(uint8_t*)&global_descriptor_table::instance->descriptors[2] - (uint8_t*)&global_descriptor_table::instance->descriptors,
				0x8e);
		}


		interrupt_descriptor_table_register idtr;
		idtr.base = (uint32_t)&descriptors[0];
		idtr.limit = (uint16_t)sizeof(interrupt_descriptor) * 256 - 1;

		asm volatile ("lidt %0" : : "m" (idtr));
		__asm__ volatile ("sti");

		std::printf("kernel: Interrupt descriptor table initialized.\n");
	}
}
