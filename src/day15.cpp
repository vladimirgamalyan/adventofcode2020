#include "utils.h"

static int doTheWorkV1(int count)
{
	std::vector<int> v = { 11, 0, 1, 10, 5, 19 };

	for (int i = v.size(); i < count; ++i)
	{
		auto n = v.back();
		auto it = std::find(v.rbegin() + 1, v.rend(), n);
		auto k = (it == v.rend()) ? 0 : std::distance(v.rbegin(), it);
		v.push_back(k);
	}

	return v.back();
}

static int doTheWorkV2(int count)
{
	std::vector<int> v = { 11, 0, 1, 10, 5, 19 };
	
	std::map<int, int> numbers;
	for (size_t i = 0; i < v.size() - 1; ++i)
		numbers[v[i]] = i;

	int last = v.back();
	for (int i = numbers.size(); i < count - 1; ++i)
	{
		if (!(i % 1000000))
			std::cout << ".";
		int spoken = 0;
		auto it = numbers.find(last);
		if (it != numbers.end())
			spoken = i - it->second;
		numbers[last] = i;
		last = spoken;
	}
	std::cout << "\n";
	return last;
}

int day15a()
{
	return doTheWorkV1(2020);
}

int day15b()
{
	return doTheWorkV2(30000000);
}
