#pragma once

#include <cstdint>
#include <cstdio>

namespace std
{
	template <typename char_type>
	struct char_traits
	{
		using int_type						= unsigned long;
		// TODO :
		// typedef std::streampos			pos_type;
		// typedef std::streamoff			off_type;
		// typedef std::mbstate_t			state_type;

		static constexpr void				assign(char_type& destination, const char_type& source);
		static constexpr char_type*			assign(char_type* destination, size_t count, const char_type source);

		static constexpr bool				eq(char_type char1, char_type char2) noexcept;
		static constexpr bool				lt(char_type char1, char_type char2) noexcept;
	
		static constexpr char_type*			move(char_type* destination, const char_type* source, size_t count);
		static constexpr char_type*			copy(char_type* destination, const char_type* source, size_t count);

		static constexpr int				compare(const char_type* string1, const char_type* string2, size_t count);

		static constexpr size_t				length(const char_type* string);

		static constexpr const char_type*	find(char_type const* string, size_t count, char_type const& character);

		static constexpr char_type			to_char_type(int_type int_value) noexcept { return (char_type)int_value; }
		static constexpr int_type			to_int_type(char_type char_value) noexcept { return (int_type)char_value; }

		static constexpr bool				eq_int_type(int_type character1, int_type character2) noexcept;

		static constexpr int_type			eof() noexcept { return (int_type)(EOF); }
		static constexpr int_type			not_eof(int_type int_value) noexcept { return (int_value != EOF) ? int_value : int_value + 1; }
	};
}