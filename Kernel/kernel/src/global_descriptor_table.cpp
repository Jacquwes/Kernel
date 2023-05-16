#include "global_descriptor_table.h"
#include "logger.h"
#include <cstring>

namespace kernel
{
	global_descriptor_table* global_descriptor_table::instance = nullptr;

	global_descriptor_table::global_descriptor_table()
	{
		logger::log(debug, "Global descriptor table > Initializing.");
		__asm__ volatile("cli");

		instance = this;

		null_descriptor() = segment_descriptor();

		// receiving irq0 causes a general protection fault if this is not present
		descriptors[1] = segment_descriptor();

		using namespace access_byte;
		using namespace flags;

		{
			auto flags = generate_flags(granularity_flag::page, size_flag::protected_32, long_mode_flag::legacy);
			auto access = generate_access_byte(descriptor_privilege_level::ring0, descriptor_type::code, executable::code,
											   direction_conforming::non_conforming, readable_writable::readable);

			kernel_code_descriptor() = segment_descriptor(0, 0xfffff, access, flags);
		}

		{
			auto flags = generate_flags(granularity_flag::page, size_flag::protected_32, long_mode_flag::legacy);
			auto access = generate_access_byte(descriptor_privilege_level::ring0, descriptor_type::code, executable::data,
											   direction_conforming::non_conforming, readable_writable::writable);

			kernel_data_descriptor() = segment_descriptor(0, 0xfffff, access, flags);
		}

		{
			auto flags = generate_flags(granularity_flag::byte, size_flag::protected_16, long_mode_flag::legacy);
			auto access = generate_access_byte(descriptor_privilege_level::ring0, descriptor_type::system,
											   system_segment_type::tss_32_available);

			task_state_descriptor() = segment_descriptor((uint32_t)&tss, sizeof(task_state_segment) - 1, access, flags);

			std::memset((uint8_t*)&tss, 0, sizeof(task_state_segment));
			tss.ss0 = 0x10;
			tss.ss = 0x10;
			tss.ds = 0x10;
			tss.es = 0x10;
			tss.fs = 0x10;
			tss.gs = 0x10;
			tss.cs = 0x08;
		}

		global_descriptor_table_register gdtr;
		gdtr.base = (uint32_t)&descriptors[0];
		gdtr.limit = (uint16_t)sizeof(segment_descriptor) * 5;

		asm volatile("lgdt %0" : : "m" (gdtr));

		logger::log(debug, "Global descriptor table > Initialized.");
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
