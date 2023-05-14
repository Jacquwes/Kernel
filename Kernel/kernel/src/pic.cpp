#include "pic.h"

namespace kernel::pic
{
	void wait()
	{
		outb(0x80, 0);
	}

	uint8_t inb(uint16_t port)
	{
		uint8_t val;
		asm volatile("inb %1, %0" : "=a"(val) : "Nd"(port));
		return val;
	}

	void outb(uint16_t port, uint8_t val)
	{
		asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
	}

	uint16_t inw(uint16_t port)
	{
		uint16_t val;
		asm volatile("inw %1, %0" : "=a"(val) : "dN"(port));
		return val;
	}

	void outw(uint16_t port, uint16_t val)
	{
		asm volatile("outw %0, %1" : : "a"(val), "dN"(port));
	}

	uint32_t inl(uint16_t port)
	{
		uint32_t val;
		asm volatile("inl %%dx, %%eax" : "=a"(val) : "dN"(port));
		return val;
	}

	void outl(uint16_t port, uint32_t val)
	{
		asm volatile("outl %%eax, %%dx" : : "dN"(port), "a"(val));
	}

	void init()
	{
		// start initialization sequence
		outb(MASTER_PIC_COMMAND, ICW1_INIT | ICW1_ICW4); // 0x11
		outb(SLAVE_PIC_COMMAND, ICW1_INIT | ICW1_ICW4); // 0x11

		// set vector offsets
		outb(MASTER_PIC_DATA, MASTER_PIC_ADDRESS); // 0x20
		outb(SLAVE_PIC_DATA, SLAVE_PIC_ADDRESS); // 0x28

		// tell master PIC that there is a slave PIC at IRQ2 (0000 0100)
		outb(MASTER_PIC_DATA, 0x04);
		// tell slave PIC its cascade identity (0000 0010)
		outb(SLAVE_PIC_DATA, 0x02);

		// set x86 mode
		outb(MASTER_PIC_DATA, ICW4_8086); // 0x01
		outb(SLAVE_PIC_DATA, ICW4_8086); // 0x01

		// mask registers
		outb(MASTER_PIC_DATA, 0xff);
		outb(SLAVE_PIC_DATA, 0xff);
	}

	void mask(uint8_t irq)
	{
		uint16_t port;
		uint8_t value;
		if (irq < 8)
		{
			port = MASTER_PIC_DATA;
		}
		else
		{
			port = SLAVE_PIC_DATA;
			irq -= 8;
		}
		value = inb(port) | (1 << irq);
		outb(port, value);
	}

	void unmask(uint8_t irq)
	{
		uint16_t port;
		uint8_t value;
		if (irq < 8)
		{
			port = MASTER_PIC_DATA;
		}
		else
		{
			port = SLAVE_PIC_DATA;
			irq -= 8;
		}
		value = inb(port) & ~(1 << irq);
		outb(port, value);
	}

	uint16_t get_irr()
	{
		outb(MASTER_PIC_COMMAND, PIC_READ_IRR);
		outb(SLAVE_PIC_COMMAND, PIC_READ_IRR);
		return (inb(SLAVE_PIC_COMMAND) << 8) | inb(MASTER_PIC_COMMAND);
	}

	void send_eoi(uint8_t irq)
	{
		if (irq >= 8)
			outb(SLAVE_PIC_COMMAND, PIC_EOI);

		outb(MASTER_PIC_COMMAND, PIC_EOI);
	}
}