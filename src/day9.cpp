#include "utils.h"

static bool testNumber(const std::vector<long long>& l, size_t index, size_t preamble)
{
	long long v = l[index];
	const auto* r = &l[index - preamble];
	for (size_t i = 0; i < preamble - 1; ++i)
		for (size_t k = i + 1; k < preamble; ++k)
			if (r[i] + r[k] == v)
				return true;
	return false;
}

static long long getInvalidNumber(const std::vector<long long>& l)
{
	const size_t preamble = 25;
	for (size_t i = preamble; i < l.size(); ++i)
		if (!testNumber(l, i, preamble))
			return l[i];
	throw std::exception();
}

long long day9a()
{
	const auto l = readLongIntList("input/9.txt");
	return getInvalidNumber(l);
}

long long day9b()
{
	const auto l = readLongIntList("input/9.txt");
	const long long x = getInvalidNumber(l);

	for (size_t i = 0; i < l.size() - 1; ++i)
	{
		long long s = l[i];
		for (size_t k = i + 1; k < l.size(); ++k)
		{
			s += l[k];
			if (s == x)
			{
				auto result = std::minmax_element(&l[i], &l[k + 1]);
				return *result.first + *result.second;
			}
			if (s > x)
				break;
		}
	}

	throw std::exception();
}
