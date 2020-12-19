#include "utils.h"

struct Rule
{
	char c = 0;
	std::vector<int> a;
	std::vector<int> b;
};

typedef std::map<int, Rule> Rules;

static std::string getRegex(const Rules& rules, int ruleIndex, bool partB)
{
	const auto it = rules.find(ruleIndex);
	assert(it != rules.end());
	const auto& v = it->second;
	if (v.c)
		return &v.c;

	std::string result;
	for (int n : v.a)
		result += getRegex(rules, n, partB);

	if (partB)
	{
		if (ruleIndex == 8)
		{
			result = "(" + getRegex(rules, 42, partB) + ")+";
		}

		if (ruleIndex == 11)
		{
			std::string result = "(";

			std::string rule42 = getRegex(rules, 42, partB);
			std::string rule31 = getRegex(rules, 31, partB);
			
			for (int i = 0; i < 10; ++i)
			{
				std::string rules42 = rule42;
				std::string rules31 = rule31;

				for (int k = 0; k < i; ++k)
				{
					rules42 += rule42;
					rules31 += rule31;
				}

				if (i)
					result += "|";
				result += rules42 + rules31;
			}
			result += ")";

			return result;
		}
	}

	if (!v.b.empty())
	{
		result = "(" + result + "|";
		for (int n : v.b)
			result += getRegex(rules, n, partB);
		result += ")";
	}

	return result;
}

static long long calc(bool partB)
{
	Rules rules;
	auto l = readStringList("input/19.txt");
	size_t i;
	for (i = 0; i < l.size(); ++i)
	{
		const auto s = l[i];
		if (s.empty())
			break;
		const auto kv = splitStr(s, ":");
		assert(kv.size() == 2);
		const auto k = trimString(kv[0]);
		const auto v = trimString(kv[1]);
		int ruleIndex = strToInt(k);

		if (v[0] == '\"')
		{
			rules[ruleIndex].c = v[1];
			continue;
		}

		const auto& parts = splitStr(v, "|");
		assert(parts.size() == 1 || parts.size() == 2);
		rules[ruleIndex].a = splitStrToInt(parts[0], " ");
		if (parts.size() == 2)
			rules[ruleIndex].b = splitStrToInt(parts[1], " ");
	}

	const auto regexStr = getRegex(rules, 0, partB);
	const auto rgx = std::regex(regexStr);

	int result = 0;
	for (++i; i < l.size(); ++i)
	{
		const auto s = l[i];
		assert(!s.empty());

		if (std::regex_match(s, rgx))
			++result;
	}

	return result;
}

long long day19a()
{
	return calc(false);
}

long long day19b()
{
	return calc(true);
}
