#include <locale>

namespace std
{
	template <typename CharT>
	collate<CharT>::collate(size_t refs)
		: facet(refs)
	{}

	template <typename CharT>
	int collate<CharT>::compare(const CharT* low1, const CharT* high1,
								const CharT* low2, const CharT* high2) const
	{
		return do_compare(low1, high1, low2, high2);
	}

	template <typename CharT>
	int collate<CharT>::do_compare(const CharT* low1, const CharT* high1,
								   const CharT* low2, const CharT* high2) const
	{
		if (low1 >= high1 || low2 >= high2)
			return 0;

		while (low1 != high1 && low2 != high2)
		{
			if (*low1 < *low2)
				return -1;
			else if (*low1 > *low2)
				return 1;

			++low1;
			++low2;
		}

		if (low1 == high1 && low2 == high2)
			return 0;
		else if (low1 == high1)
			return -1;
		else
			return 1;
	}

	template <typename CharT>
	typename collate<CharT>::string_type collate<CharT>::transform(const CharT* low, const CharT* high) const
	{
		return do_transform(low, high);
	}

	template <typename CharT>
	typename collate<CharT>::string_type collate<CharT>::do_transform(const CharT* low, const CharT* high) const
	{
		string_type result;

		while (low != high)
		{
			result.push_back(*low);
			++low;
		}

		return result;
	}

	template <typename CharT>
	long collate<CharT>::hash(const CharT* beg, const CharT* end) const
	{
		return do_hash(beg, end);
	}

	template <typename CharT>
	long collate<CharT>::do_hash(const CharT* beg, const CharT* end) const
	{
		long result = 0;

		while (beg != end)
		{
			result += *beg;
			++beg;
		}

		return result;
	}
}