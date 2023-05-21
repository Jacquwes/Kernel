#include "logger.h"

#include <cstdio>

namespace kernel
{
	uint8_t logger::canals = log_canal::none;

	void logger::log(const char* format, ...)
	{
		__builtin_va_list list;
		__builtin_va_start(list, format);
		log(info, format, list);
		__builtin_va_end(list);
	}

	void logger::log(log_canal canal, const char* format, ...)
	{
		if ((canals & canal) == 0)
			return;
		__builtin_va_list list;
		__builtin_va_start(list, format);
		log(canal, format, list);
		__builtin_va_end(list);
	}

	void logger::log(log_canal canal, const char* format, __builtin_va_list args)
	{
		if ((canals & canal) == 0)
			return;

		switch (canal)
		{
		case error:
			std::fprintf(stdserial, "[ERROR]   | ");
			break;
		case warning:
			std::fprintf(stdserial, "[WARNING] | ");
			break;
		case info:
			std::fprintf(stdserial, "[INFO]    | ");
			break;
		case debug:
			std::fprintf(stdserial, "[DEBUG]   | ");
			break;
		default:
			break;
		}

		std::vfprintf(stdserial, format, args);
		std::fprintf(stdserial, "\n");
	}

	void logger::set_canals(uint8_t canals_)
	{
		canals = canals_;
	}
}