#pragma once

#include <cstdint>

namespace kernel::pic
{
	constexpr auto MASTER_PIC_ADDRESS = 0x20;
	constexpr auto MASTER_PIC_COMMAND = MASTER_PIC_ADDRESS;
	constexpr auto MASTER_PIC_DATA = MASTER_PIC_ADDRESS + 1;
	constexpr auto SLAVE_PIC_ADDRESS = 0x28;
	constexpr auto SLAVE_PIC_COMMAND = SLAVE_PIC_ADDRESS;
	constexpr auto SLAVE_PIC_DATA = SLAVE_PIC_ADDRESS + 1;

	constexpr auto ICW1_ICW4 = 0x01;
	constexpr auto ICW1_SINGLE = 0x02;
	constexpr auto ICW1_INTERVAL4 = 0x04;
	constexpr auto ICW1_LEVEL = 0x08;
	constexpr auto ICW1_INIT = 0x10;

	constexpr auto ICW4_8086 = 0x01;
	constexpr auto ICW4_AUTO = 0x02;
	constexpr auto ICW4_BUF_SLAVE = 0x08;
	constexpr auto ICW4_BUF_MASTER = 0x0c;
	constexpr auto ICW4_SFNM = 0x10;

	constexpr auto PIC_READ_IRR = 0x0a;
	constexpr auto PIC_READ_ISR = 0x0b;

	constexpr auto PIC_EOI = 0x20;

	void init();
	void mask(uint8_t irq);
	void unmask(uint8_t irq);

	void wait();

	uint8_t inb(uint16_t port);
	void outb(uint16_t port, uint8_t val);

	uint16_t inw(uint16_t port);
	void outw(uint16_t port, uint16_t val);

	uint32_t inl(uint16_t port);
	void outl(uint16_t port, uint32_t val);

	uint16_t get_irr();

	void send_eoi(uint8_t irq);
}