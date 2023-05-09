#include "global_descriptor_table.h"
#include <cstdio>

namespace kernel
{
	global_descriptor_table* global_descriptor_table::instance = nullptr;

	global_descriptor_table::global_descriptor_table()
	{
		std::printf("kernel: Initializing global descriptor table.\n");
		__asm__ volatile("cli");

		instance = this;

		// null descriptor
		descriptors[0] = segment_descriptor(0, 0, 0);
		// unused
		descriptors[1] = segment_descriptor(0, 0, 0);
		// kernel code segment
		descriptors[2] = segment_descriptor(0, 0xfffff, 0x9a);
		// kernel data segment
		descriptors[3] = segment_descriptor(0, 0xfffff, 0x92);
		global_descriptor_table_register gdtr;
		gdtr.base = (uint32_t)&descriptors[0];
		gdtr.limit = (uint16_t)sizeof(segment_descriptor) * 8;

		asm volatile("lgdt %0" : : "m" (gdtr));

		std::printf("kernel: Global descriptor table initialized.\n");
	}

	segment_descriptor::segment_descriptor()
	{
		limit_low = 0;
		base_low = 0;
		base_mid = 0;
		access_byte = 0;
		limit_high = 0;
		flags = 0;
		base_high = 0;
	}

	segment_descriptor::segment_descriptor(uint32_t base, uint32_t limit, uint8_t _access_byte, uint8_t _flags)
	{
		limit_low = limit & 0xffff;
		base_low = base & 0xffff;
		base_mid = (base >> 16) & 0xff;
		access_byte = _access_byte;
		limit_high = (limit >> 16) & 0x0f;
		flags = _flags;
		base_high = (base >> 24) & 0xff;
	}
}
