#include "utils.h"

int day13a()
{
	auto l = readStringList("input/13.txt");
	assert(l.size() == 2);
	int n = strToInt(l[0]);
	auto schedule = splitStr(l[1], ",x");
	assert(!schedule.empty());
	int bus = 0;
	int best = -1;
	for (const auto s : schedule)
	{
		int a = strToInt(s);
		int t = (a - (n % a)) % a;
		if (best == -1 || best > t)
		{
			best = t;
			bus = a;
		}
	}

	return bus * best;
}

uint64_t day13b()
{
	struct Item
	{
		Item(size_t index, int id) : index(index), id(id) {};
		size_t index;
		int id;
	};

	auto l = readStringList("input/13.txt");
	assert(l.size() == 2);
	auto t = splitStr(l[1], ",");

	std::vector<Item> data;
	for (size_t i = 0; i < t.size(); ++i)
		if (t[i] != "x")
			data.emplace_back(i, strToInt(t[i]));
	
	uint64_t result = data.front().id;
	uint64_t s = 1;
	for (const auto& i : data)
	{
		while ((result + i.index) % i.id)
			result += s;
		s *= i.id;
	}

	return result;
}
