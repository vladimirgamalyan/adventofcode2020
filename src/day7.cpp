#include "utils.h"

typedef std::map<std::string, std::map<std::string, int>> Rules;

bool testRule(const Rules& rules, const std::string& bag)
{
	const auto it = rules.find(bag);
	assert(it != rules.end());
	for (const auto& n : it->second)
	{
		if (n.first == "shinygold")
			return true;
		if (testRule(rules, n.first))
			return true;
	}
	return false;
}

Rules readRules()
{
	auto l = readStringList("input/7.txt");
	Rules rules;
	for (const auto& s : l)
	{
		auto tokens = splitStr(s, " ,.");
		std::string name = tokens[0] + tokens[1];

		//TODO: сделать map, цвет + кол-вл
		std::map<std::string, int> contains;
		for (size_t i = 4; i < tokens.size(); i += 4)
		{
			std::string count = tokens[i];
			if (count == "no")
				break;
			std::string k = tokens[i + 1] + tokens[i + 2];
			contains[k] = std::stoi(count);
		}
		rules[name] = contains;
	}
	return rules;
}

int getBagSize(const Rules& rules, const std::string& bag)
{
	const auto it = rules.find(bag);
	assert(it != rules.end());
	int result = 0;
	for (const auto& n : it->second)
		result += (n.second + getBagSize(rules, n.first) * n.second);
	return result;
}

int day7a()
{
	auto rules = readRules();
	int result = 0;
	for (const auto& i : rules)
		if (testRule(rules, i.first))
			++result;
	return result;
}

int day7b()
{
	return getBagSize(readRules(), "shinygold");
}
