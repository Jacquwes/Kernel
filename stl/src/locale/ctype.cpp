#include <locale>

namespace std
{
	template <typename CharT>
	ctype<CharT>::ctype(size_t refs)
		: facet(refs)
	{}

	template <typename CharT>
	bool ctype<CharT>::is(mask m, char_type c) const
	{
		return do_is(m, c);
	}

	template <typename CharT>
	const CharT* ctype<CharT>::is(const CharT* low, const CharT* high, mask* vec) const
	{
		return do_is(low, high, vec);
	}

	template <typename CharT>
	const ctype<CharT>::char_type* ctype<CharT>::scan_is(mask m, const char_type* low, const char_type* high) const
	{
		return do_scan_is(m, low, high);
	}

	template <typename CharT>
	const ctype<CharT>::char_type* ctype<CharT>::scan_not(mask m, const char_type* low, const char_type* high) const
	{
		return do_scan_not(m, low, high);
	}

	template <typename CharT>
	ctype<CharT>::char_type ctype<CharT>::toupper(char_type c) const
	{
		return do_toupper(c);
	}

	template <typename CharT>
	const ctype<CharT>::char_type* ctype<CharT>::toupper(char_type* low, const char_type* high) const
	{
		return do_toupper(low, high);
	}

	template <typename CharT>
	ctype<CharT>::char_type ctype<CharT>::tolower(char_type c) const
	{
		return do_tolower(c);
	}

	template <typename CharT>
	const ctype<CharT>::char_type* ctype<CharT>::tolower(char_type* low, const char_type* high) const
	{
		return do_tolower(low, high);
	}

	template <typename CharT>
	ctype<CharT>::char_type ctype<CharT>::widen(char c) const
	{
		return do_widen(c);
	}

	template <typename CharT>
	const char* ctype<CharT>::widen(const char* low, const char* high, char_type* to) const
	{
		return do_widen(low, high, to);
	}

	template <typename CharT>
	char ctype<CharT>::narrow(char_type c, char dfault) const
	{
		return do_narrow(c, dfault);
	}

	template <typename CharT>
	const ctype<CharT>::char_type* ctype<CharT>::narrow(const char_type* low, const char_type* high, char dfault, char* to) const
	{
		return do_narrow(low, high, dfault, to);
	}

	template <typename CharT>
	bool ctype<CharT>::do_is(mask m, char_type c) const
	{
		return false;
	}

	template <typename CharT>
	const CharT* ctype<CharT>::do_is(const CharT* low, const CharT* high, mask* vec) const
	{
		return nullptr;
	}

	template <typename CharT>
	const ctype<CharT>::char_type* ctype<CharT>::do_scan_is(mask m, const char_type* low, const char_type* high) const
	{
		return nullptr;
	}

	template <typename CharT>
	const ctype<CharT>::char_type* ctype<CharT>::do_scan_not(mask m, const char_type* low, const char_type* high) const
	{
		return nullptr;
	}

	template <typename CharT>
	ctype<CharT>::char_type ctype<CharT>::do_toupper(char_type c) const
	{
		return c;
	}

	template <typename CharT>
	const ctype<CharT>::char_type* ctype<CharT>::do_toupper(char_type* low, const char_type* high) const
	{
		return nullptr;
	}

	template <typename CharT>
	ctype<CharT>::char_type ctype<CharT>::do_tolower(char_type c) const
	{
		return c;
	}

	template <typename CharT>
	const ctype<CharT>::char_type* ctype<CharT>::do_tolower(char_type* low, const char_type* high) const
	{
		return nullptr;
	}

	template <typename CharT>
	ctype<CharT>::char_type ctype<CharT>::do_widen(char c) const
	{
		return c;
	}

	template <typename CharT>
	const char* ctype<CharT>::do_widen(const char* low, const char* high, char_type* to) const
	{
		return nullptr;
	}

	template <typename CharT>
	char ctype<CharT>::do_narrow(char_type c, char dfault) const
	{
		return c;
	}

	template <typename CharT>
	const ctype<CharT>::char_type* ctype<CharT>::do_narrow(const char_type* low, const char_type* high, char dfault, char* to) const
	{
		return nullptr;
	}
}