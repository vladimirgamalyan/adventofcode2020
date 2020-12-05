#include "utils.h"

static std::vector<bool> parse_trees(const std::string& s)
{
	std::vector<bool> result(s.size());
	std::transform(s.begin(), s.end(), result.begin(), [](char c) { return c == '#'; });
	return result;
}

static int64_t find(const std::vector<std::vector<bool>>& d, int right, int down)
{
	int c = 0;
	int s = 0;

	for (size_t i = 0; i < d.size(); i += down)
	{
		size_t col = (s * right) % d[i].size();
		if (d[i][col])
			++c;
		++s;
	}

	return c;
}

static std::vector<std::vector<bool>> getInput()
{
	auto l = readStringList("input/3.txt");
	std::vector<std::vector<bool>> d(l.size());
	std::transform(l.begin(), l.end(), d.begin(), parse_trees);
	return d;
}

int64_t day3a()
{
	auto d = getInput();
	return find(d, 3, 1);
}

int64_t day3b()
{
	auto d = getInput();
	return find(d, 1, 1) * find(d, 3, 1) * find(d, 5, 1) * find(d, 7, 1) * find(d, 1, 2);
}
