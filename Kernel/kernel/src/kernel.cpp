#include <cstdint>
#include <cstdio>
#include <memory>
#include <new>
#include <string>

#include <kernel.h>
#include <global_descriptor_table.h>
#include <interrupt_descriptor_table.h>
#include <memory_manager.h>
#include <multiboot.h>
#include <output.h>


void main(multiboot_info_t* info, uint32_t magic)
{
	kernel::output();
	kernel::memory_manager(info, magic);
	kernel::global_descriptor_table();
}