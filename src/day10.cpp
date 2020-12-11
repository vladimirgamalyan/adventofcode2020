#include "utils.h"

long long day10a()
{
	auto l = readIntList("input/10.txt");
	std::sort(l.begin(), l.end());
	l.push_back(l.back() + 3);

	std::map<int, long long> diffs;
	int v = 0;
	for (const auto& n : l)
	{
		diffs[n - v]++;
		v = n;
	}

	return diffs[1] * diffs[3];
}

long long day10b()
{
	auto l = readIntList("input/10.txt");
	std::sort(l.begin(), l.end());
	l.push_back(l.back() + 3);

	long long result = 1;
	int n = 0;
	int c = 0;
	for (size_t i = 0; i < l.size(); ++i)
	{
		++c;
		if (l[i] != n + 1)
		{
			if (c == 3)
				result *= 2;
			if (c == 4)
				result *= 4;
			if (c == 5)
				result *= 7;
			if (c > 5)
				throw std::exception();
			c = 0;
		}
		n = l[i];
	}

	return result;
}
