#pragma once

#include <cstdint>

#include "global_descriptor_table.h"

namespace kernel
{
	struct interrupt_descriptor
	{
		interrupt_descriptor() = default;
		interrupt_descriptor(uint32_t base, uint16_t selector, uint8_t flags);

		uint16_t base_low;
		uint16_t selector;
		uint8_t reserved;
		uint8_t flags;
		uint16_t base_high;
	} __attribute__((packed));

	struct interrupt_descriptor_table
	{
		interrupt_descriptor_table();

		interrupt_descriptor descriptors[32];
	} __attribute__((packed));
}