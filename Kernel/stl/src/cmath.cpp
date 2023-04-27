#include <cmath>

namespace std
{
	double log(double n, uint64_t iterations)
	{
		if (n <= 0)
			return 0;

		double result = 0.;
		double term = (n - 1.) / (n + 1.);
		double term_i = term;

		for (double i = 0; i < iterations; i += 2.)
		{
			result += term_i / i;
			term_i *= term * term;
		}

		return result * 2.;
	}

	double log10(double n, uint64_t iterations)
	{
		return log(n, iterations) / log(10., iterations);
	}

	uint64_t log2_binary(uint64_t n)
	{
		if (n <= 0)
			return 0;

		double result = -1;

		while (n)
		{
			result++;
			n >>= 1;
		}

		return result;
	}

	uint64_t log10_binary(uint64_t n)
	{
		return log2_binary(n) / log2_binary(10);
	}
}