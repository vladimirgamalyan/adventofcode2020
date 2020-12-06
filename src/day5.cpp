#include "utils.h"

static int parseSeatId(std::string s)
{
	for (char& c : s)
		c = c == 'B' || c == 'R' ? '1' : '0';
	
	return std::stoi(s, nullptr, 2);
}

static std::vector<int> getSeatIdList()
{
	auto l = readStringList("input/5.txt");
	std::vector<int> result(l.size());
	std::transform(l.begin(), l.end(), result.begin(), parseSeatId);
	return result;
}

int day5a()
{
	auto l = getSeatIdList();
	return *std::max_element(l.begin(), l.end());
}

int day5b()
{
	auto l = getSeatIdList();
	std::sort(l.begin(), l.end());

	for (size_t i = 0; i < l.size() - 1; ++i)
		if (l[i] + 2 == l[i + 1])
			return l[i] + 1;

	return -1;
}
