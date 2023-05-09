#pragma once

#include <cstdint>

namespace kernel
{
	constexpr auto MASTER_PIC_ADDRESS = 0x20;
	constexpr auto MASTER_PIC_COMMAND = MASTER_PIC_ADDRESS;
	constexpr auto MASTER_PIC_DATA = MASTER_PIC_ADDRESS + 1;
	constexpr auto SLAVE_PIC_ADDRESS = 0xA0;
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
	constexpr auto ICW4_BUF_MASTER = 0x0C;
	constexpr auto ICW4_SFNM = 0x10;

	void init_pic();

	uint8_t inb(uint16_t port);
	void io_wait();
	void outb(uint16_t port, uint8_t val);
}