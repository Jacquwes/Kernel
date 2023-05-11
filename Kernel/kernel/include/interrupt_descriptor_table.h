#pragma once

#include <cstdint>

#include "global_descriptor_table.h"

namespace kernel
{
	namespace type_attributes
	{
		enum class gate_type : uint8_t
		{
			task_gate = 0x5, // offset should be set to 0
			interrupt_gate_16 = 0x6,
			trap_gate_16 = 0x7,
			interrupt_gate_32 = 0xe,
			trap_gate_32 = 0xf
		};

		using descriptor_privilege_level = access_byte::descriptor_privilege_level;

		inline constexpr uint8_t generate_type_attributes(gate_type type, descriptor_privilege_level dpl)
		{
			uint8_t result = 0;

			result |= 1 << 7; // present byte
			result |= static_cast<uint8_t>(dpl) << 5;
			result |= static_cast<uint8_t>(type);
				
			return result;
		}
	}

	struct interrupt_descriptor
	{
		interrupt_descriptor();
		interrupt_descriptor(uint32_t offset, uint8_t type_attributes);

		uint16_t offset_low;
		uint16_t segment_selector;
		uint8_t reserved;
		uint8_t type_attributes;
		uint16_t offset_high;
	} __attribute__((packed));

	struct interrupt_descriptor_table_register
	{
		uint16_t limit;
		uint32_t base;
	} __attribute__((packed));

	struct interrupt_descriptor_table
	{
		interrupt_descriptor_table();

		interrupt_descriptor descriptors[256];
	};
}