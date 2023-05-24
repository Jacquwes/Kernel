#include <algorithm>

namespace std
{
	template<typename InputIt1, typename InputIt2>
	constexpr bool std::equal(InputIt1 first1, InputIt1 last, InputIt2 first2)
	{
		for (; first1 != last; first1++, first2++)
			if (*first1 != *first2)
				return false;

		return true;
	}

	template <typename InputIt1, typename InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
								 InputIt2 first2, InputIt2 last2)
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, ++first2) {
			if (*first1 < *first2) return true;
			if (*first2 < *first1) return false;
		}

		return (first1 == last1) && (first2 != last2);
	}
}