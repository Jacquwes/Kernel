#include <cstdio>


#include "global_descriptor_table.h"
#include "interrupt_descriptor_table.h"



namespace kernel
{
	struct regs
	{
		uint32_t gs, fs, es, ds;
		uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
		uint32_t int_no, err_code;
		uint32_t eip, cs, eflags, useresp, ss;
	};

	char exception[0x20][0x20] =
	{
		"division_error",
		"debug",
		"non_maskable_interrupt",
		"breakpoint",
		"overflow",
		"bound_range_exceeded",
		"invalid_opcode",
		"device_not_available",
		"double_fault",
		"coprocessor_segment_overrun",
		"invalid_tss",
		"segment_not_present",
		"stack_segment_fault",
		"general_protection_fault",
		"page_fault",
		"reserved",
		"x87_floating_point",
		"alignment_check",
		"machine_check",
		"simd_floating_point_exception",
		"virtualization_exception",
		"control_protection_exception",
		"reserved",
		"hypervisor_injection_exception",
		"vmm_communication_exception",
		"security_exception",
		"reserved",
	};

	constexpr bool abort(uint8_t code)
	{
		switch (code)
		{
		case 0x08:
		case 0x12:
			return true;
		default:
			return false;
		}
	}
}

extern "C" void exception_handler(kernel::regs* frame)
{
	//std::printf("kernel: An exception occurred: %x, code: %x\n", frame->int_no, frame->err_code);
	//std::printf("    gs: %x, fs: %x, es: %x, ds: %x\n", frame->gs, frame->fs, frame->es, frame->ds);
	//std::printf("    edi: %x, esi: %x, ebp: %x, esp: %x, ebx: %x, edx: %x, ecx: %x, eax: %x\n", frame->edi, frame->esi, frame->ebp, frame->esp, frame->ebx, frame->edx, frame->ecx, frame->eax);
	//std::printf("    eip: %x, cs: %x, eflags: %x, useresp: %x, ss: %x\n", frame->eip, frame->cs, frame->eflags, frame->useresp, frame->ss);
	
	std::printf("Kernel > An exception occurred: %s with error_code %x\n", kernel::exception[frame->int_no], frame->err_code);
	if (kernel::abort(frame->int_no))
	{
		std::printf("Kernel > Aborting...\n");
		__asm__ volatile ("hlt");
	}
}