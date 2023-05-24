#include <locale>

namespace std
{
	size_t locale::id::_id_count = 0;

	locale::facet::facet(size_t refs)
		: _refs(refs)
	{}

	locale::locale() noexcept
	{
		if (_global_called)
			*this = locale(* _global);
		else
			*this = locale(classic());
	}

	locale::locale(locale const& other) noexcept
		: _name(other._name)
	{}

	locale::locale(const char* std_name)
		: _name(std_name)
	{}

	locale::locale(string const& std_name)
		: _name(std_name.c_str())
	{}

	locale::locale(locale const& other, const char* std_name, category cat)
		: _name(std_name)
	{}
}