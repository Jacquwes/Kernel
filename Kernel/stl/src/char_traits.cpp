#include <char_traits.h>
#include <cstdio>

namespace std
{
	template <typename char_type>
	constexpr void char_traits<char_type>::assign(char_type& destination, const char_type& source)
	{
		destination = source;
	}

	template <typename char_type>
	constexpr char_type* char_traits<char_type>::assign(char_type* destination, size_t count, const char_type source)
	{
		for (size_t i = 0; i < count; i++)
		{
			destination[i] = source;
		}
		return destination;
	}

	template <typename char_type>
	constexpr bool char_traits<char_type>::eq(char_type char1, char_type char2) noexcept
	{
		return char1 == char2;
	}

	template <typename char_type>
	constexpr bool char_traits<char_type>::lt(char_type char1, char_type char2) noexcept
	{
		return char1 < char2;
	}

	template <typename char_type>
	constexpr char_type* char_traits<char_type>::move(char_type* destination, const char_type* source, size_t count)
	{
		for (size_t i = 0; i < count; i++)
		{
			destination[i] = source[i];
		}
		return destination;
	}

	template <typename char_type>
	constexpr char_type* char_traits<char_type>::copy(char_type* destination, const char_type* source, size_t count)
	{
		for (size_t i = 0; i < count; i++)
		{
			destination[i] = source[i];
		}
		return destination;
	}

	template <typename char_type>
	constexpr int char_traits<char_type>::compare(const char_type* string1, const char_type* string2, size_t count)
	{
		if (string1 < string2)
			return -1;
		else if (string1 > string2)
			return 1;
		return 0;
	}

	template <typename char_type>
	constexpr size_t char_traits<char_type>::length(const char_type* string)
	{
		size_t length = 0;
		char_type null_char = char_type();
		while (string[length] != null_char)
		{
			length++;
		}
		return length;
	}

	template <typename char_type>
	constexpr const char_type* char_traits<char_type>::find(const char_type* string, size_t count, const char_type& character)
	{
		for (size_t i = 0; i < count; i++)
		{
			if (string[i] == character)
				return &string[i];
		}
		return nullptr;
	}

	template <typename char_type>
	constexpr bool char_traits<char_type>::eq_int_type(int_type character1, int_type character2) noexcept
	{
		return character1 == character2;
	}
}