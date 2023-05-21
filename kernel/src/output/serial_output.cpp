#include "logger.h"
#include "output.h"
#include "pic.h"

#include <cstdio>

namespace kernel
{
	serial_output* serial_output::instance = nullptr;
	bool serial_output::port_initialized = false;

	serial_output::serial_output()
	{
		instance = this;

		logger::log(info, "Serial output > Initialized.");
		
		if (port_initialized)
			return;

		pic::outb(pic::COM1 + 1, 0x00); // interrupts disabled
		pic::outb(pic::COM1 + 3, 0x80); // enable DLAB (set baud rate divisor)
		pic::outb(pic::COM1 + 0, 0x03); // set divisor to 3 (lo byte) 38400 baud
		pic::outb(pic::COM1 + 1, 0x00); //                  (hi byte)
		pic::outb(pic::COM1 + 3, 0x03); // 8 bits, no parity, one stop bit
		pic::outb(pic::COM1 + 2, 0xC7); // enable FIFO, clear them, with 14-byte threshold
		pic::outb(pic::COM1 + 4, 0x0B); // IRQs enabled, RTS/DSR set
		pic::outb(pic::COM1 + 4, 0x0F); // normal operation mode

		port_initialized = true;

		logger::log(debug, "Serial output > Port COM1 initialized.");
	}

	void serial_output::putchar(const char& c)
	{
		while ((pic::inb(pic::COM1 + 5) & 0x20) == 0);
		pic::outb(pic::COM1, c);
	}
}