#pragma once

#include <cstdint>

namespace kernel {
	namespace access_byte
	{
		enum class descriptor_privilege_level : uint8_t
		{
			ring0,
			ring1,
			ring2,
			ring3
		};

		enum class descriptor_type : uint8_t
		{
			system = 0,
			code = 1,
			data = 1,
		};

		enum class executable : uint8_t
		{
			data,
			code
		};

		enum class direction_conforming : uint8_t
		{
			up,
			down,
			non_conforming = 0,
			conforming = 1
		};

		enum class readable_writable : uint8_t
		{
			non_readable = 0,
			readable = 1,
			non_writable = 0,
			writable = 1,
		};

		enum class system_segment_type : uint8_t
		{
			tss_16_available,
			local_descriptor_table,
			tss_16_busy,
			tss_32_available = 0x9,
			tss_32_busy = 0xb,
		};

		inline constexpr uint8_t generate_access_byte(descriptor_privilege_level dpl, descriptor_type s, executable e, direction_conforming dc, readable_writable rw)
		{
			uint8_t result = 0;

			// present bit
			result |= 1 << 7;
			result |= static_cast<uint8_t>(dpl) << 5;
			result |= static_cast<uint8_t>(s) << 4;
			result |= static_cast<uint8_t>(e) << 3;
			result |= static_cast<uint8_t>(dc) << 2;
			result |= static_cast<uint8_t>(rw) << 1;
			// accessed bit is set by cpu

			return result;
		}

		inline constexpr uint8_t generate_access_byte(descriptor_privilege_level dpl, descriptor_type s, system_segment_type type)
		{
			uint8_t result = 0;

			// present bit
			result |= 1 << 7;
			result |= static_cast<uint8_t>(dpl) << 5;
			result |= static_cast<uint8_t>(s) << 4;
			result |= static_cast<uint8_t>(type);

			return result;
		}
	}

	namespace flags
	{
		enum class granularity_flag : uint8_t
		{
			byte,
			page
		};

		/// <summary>
		/// Should be clear if long mode is enabled.
		/// </summary>
		enum class size_flag : uint8_t
		{
			protected_16,
			protected_32
		};

		enum class long_mode_flag : uint8_t
		{
			legacy,
			code_64
		};

		inline constexpr uint8_t generate_flags(granularity_flag g, size_flag db, long_mode_flag l)
		{
			uint8_t result = 0;

			result |= static_cast<uint8_t>(g) << 3;
			result |= static_cast<uint8_t>(db) << 2;
			result |= static_cast<uint8_t>(l) << 1;
			// reserved bit is always 0

			return result;
		}

	}


	struct segment_descriptor
	{
		segment_descriptor();
		segment_descriptor(uint32_t base, uint32_t limit, uint8_t access_byte, uint8_t flags);

		uint16_t limit_low;
		uint16_t base_low;
		uint8_t base_mid;
		uint8_t access_byte;
		uint8_t limit_high : 4;
		uint8_t flags : 4;
		uint8_t base_high;
	} __attribute__((packed));

	struct global_descriptor_table_register
	{
		uint16_t limit;
		uint32_t base;
	} __attribute__((packed));

	struct task_state_segment
	{
		uint16_t link; uint16_t reserved0;
		uint32_t esp0;
		uint16_t ss0; uint16_t reserved1;
		uint32_t esp1;
		uint16_t ss1; uint16_t reserved2;
		uint32_t esp2;
		uint16_t ss2; uint16_t reserved3;
		uint32_t cr3;
		uint32_t eip;
		uint32_t eflags;
		uint32_t eax;
		uint32_t ecx;
		uint32_t edx;
		uint32_t ebx;
		uint32_t esp;
		uint32_t ebp;
		uint32_t esi;
		uint32_t edi;
		uint16_t es; uint16_t reserved4;
		uint16_t cs; uint16_t reserved5;
		uint16_t ss; uint16_t reserved6;
		uint16_t ds; uint16_t reserved7;
		uint16_t fs; uint16_t reserved8;
		uint16_t gs; uint16_t reserved9;
		uint16_t ldtr; uint16_t reserved10;
		uint16_t reserved11; uint16_t iopb;
		uint32_t ssp;
	} __attribute__((packed));

	struct global_descriptor_table
	{
		global_descriptor_table();

		static global_descriptor_table* instance;

		task_state_segment tss;

		global_descriptor_table_register gdtr;
		segment_descriptor descriptors[5];

		inline constexpr segment_descriptor& null_descriptor() { return descriptors[0]; }
		inline constexpr segment_descriptor& kernel_code_descriptor() { return descriptors[2]; }
		inline constexpr segment_descriptor& kernel_data_descriptor() { return descriptors[3]; }
		inline constexpr segment_descriptor& task_state_descriptor() { return descriptors[4]; }
	};
}