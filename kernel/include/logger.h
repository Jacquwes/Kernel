#pragma once

#include "output.h"

#include <cstdio>

namespace kernel
{
	enum log_canal : uint8_t
	{
		none    = 0b00000000,
		error   = 0b00000001,
		warning = 0b00000010,
		info    = 0b00000100,
		debug   = 0b00001000,
		all     = 0b00001111
	};

	class logger
	{
	public:
		static void log(const char* format, ...);
		static void log(log_canal canal, const char* format, ...);
		static void log(log_canal canal, const char* format, __builtin_va_list args);

		static void set_canals(uint8_t canals);

	private:
		static uint8_t canals;
	};
}