#include "global_descriptor_table.h"
#include <cstdio>

namespace kernel
{
	global_descriptor_table* global_descriptor_table::instance = nullptr;

	segment_descriptor::segment_descriptor(uint32_t base, uint32_t limit, uint16_t _flag)
	{
		uint64_t* descriptor = (uint64_t*)this;

		// high 32 bit segment
		*descriptor = limit & 0x000f'0000;
		*descriptor |= (_flag << 8) & 0x00f0'ff00;
		*descriptor |= (base >> 16) & 0x0000'00ff;
		*descriptor |= base & 0xff00'0000;

		*descriptor <<= 0x20;

		*descriptor |= base << 0x10;
		*descriptor |= limit & 0x0000'ffff;
	}

	global_descriptor_table::global_descriptor_table()
	{
		std::printf("kernel: Initializing global descriptor table.\n");

		instance = this;

		// null descriptor
		descriptors[0] = segment_descriptor(0, 0, 0);
		// unused
		descriptors[1] = segment_descriptor(0, 0, 0);
		// kernel code segment
		descriptors[2] = segment_descriptor(0, 0xfffff, 0x9a);
		// kernel data segment
		descriptors[3] = segment_descriptor(0, 0xfffff, 0x92);

		uint32_t gdtr[2];
		gdtr[0] = (uint32_t)this;
		gdtr[1] = sizeof(descriptors) - 1;
		__asm volatile ("lgdt (%0)" : : "p" (((uint8_t*)gdtr) + 2));

		std::printf("kernel: Global descriptor table initialized.\n");
	}
}