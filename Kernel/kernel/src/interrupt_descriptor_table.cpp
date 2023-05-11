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
		std::printf("kernel: Initializing interrupt descriptor table.\n");

		std::memset(descriptors, 0, sizeof(descriptors));

		for (int i = 0; i < 256; i++)
		{
			descriptors[i] = interrupt_descriptor(
				(uint32_t)isr_stub_table[i],
				(uint8_t*)&global_descriptor_table::instance->descriptors[2] - (uint8_t*)&global_descriptor_table::instance->descriptors,
				0x8e);
		}

		uint32_t idtr[2];
		idtr[0] = sizeof(descriptors) - 1;
		idtr[1] = (uint32_t)descriptors;
		__asm volatile ("lidt %0" : : "m" (idtr));
		__asm__ volatile ("sti");

		std::printf("kernel: Interrupt descriptor table initialized.\n");
	}
}
