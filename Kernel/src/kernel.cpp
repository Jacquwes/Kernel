#include <cstdint>
#include <kernel/display.hpp>

void main()
{
	Kernel::Display::Console console;
	console.ClearScreen();
	console.Print('c');
}