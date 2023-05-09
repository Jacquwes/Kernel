#include "pic.h"

namespace kernel
{
	uint8_t inb(uint16_t port)
	{
		uint8_t val;
		asm volatile("inb %1, %0" : "=a"(val) : "Nd"(port));
		return val;
	}

	void io_wait()
	{
		outb(0x80, 0);
	}

	void outb(uint16_t port, uint8_t val)
	{
		asm volatile("outb %0, %1" : "=a"(val) : "Nd"(port));
	}

	void init_pic()
	{
		// start initialization sequence
		outb(MASTER_PIC_COMMAND, ICW1_INIT | ICW1_ICW4);
		io_wait();
		outb(SLAVE_PIC_COMMAND, ICW1_INIT | ICW1_ICW4);
		io_wait();

		// set vector offsets
		outb(MASTER_PIC_DATA, 0x20);
		io_wait();
		outb(SLAVE_PIC_DATA, 0x28);
		io_wait();

		// tell master PIC that there is a slave PIC at IRQ2 (0000 0100)
		outb(MASTER_PIC_DATA, 0x04);
		io_wait();
		// tell slave PIC its cascade identity (0000 0010)
		outb(SLAVE_PIC_DATA, 0x02);
		io_wait();

		// set mode
		outb(MASTER_PIC_DATA, ICW4_8086);
		io_wait();
		outb(SLAVE_PIC_DATA, ICW4_8086);
		io_wait();
	}
}