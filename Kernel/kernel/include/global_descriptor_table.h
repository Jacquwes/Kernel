#pragma once

#include <cstdint>

namespace kernel {
	struct segment_descriptor
	{
		segment_descriptor() = default;
		segment_descriptor(uint32_t base, uint32_t limit, uint16_t flag);

		uint16_t limit_low;
		uint16_t base_low;
		uint8_t base_high;
		uint8_t flag;
		uint8_t limit_high;
		uint8_t base_vhi;
	} __attribute__((packed));

	struct global_descriptor_table
	{
		global_descriptor_table();
		
		segment_descriptor descriptors[4];
	} __attribute__((packed));;
}