#include "utils.h"

struct Item
{
	int a;
	int b;
	char letter;
	std::string pass;
};

static Item fromString(const std::string& s)
{
	Item result;
	std::stringstream ss;
	char skip;
	ss << s;
	ss >> result.a >> skip >> result.b >> result.letter >> skip >> result.pass;
	return result;
}

static bool isValidA(const std::string& s)
{
	Item item = fromString(s);
	int count = std::count(item.pass.begin(), item.pass.end(), item.letter);
	return count >= item.a && count <= item.b;
}

static bool isValidB(const std::string& s)
{
	Item item = fromString(s);
	int c = 0;
	if (item.pass[item.a - 1] == item.letter)
		++c;
	if (item.pass[item.b - 1] == item.letter)
		++c;
	return c == 1;
}

int day2a()
{
	auto l = readStringList("input/2.txt");
	return count_if(l.begin(), l.end(), isValidA);
}

int day2b()
{
	auto l = readStringList("input/2.txt");
	return count_if(l.begin(), l.end(), isValidB);
}
