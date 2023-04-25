#include <cstdint>

#include <string>

class chart : public std::char_traits<char>
{

};

void main()
{
	volatile int a = 3;
	chart b[5];
}