#include <locale>

namespace std
{
	ctype<char>::ctype(const mask* tbl, bool del, size_t refs)
		: facet(refs), _deletable(del)
	{
		if (tbl == nullptr)
			_table = classic_table();
		else
			_table = tbl;
	}
}