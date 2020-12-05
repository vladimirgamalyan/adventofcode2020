#include "day4.h"

static const std::string digits = "0123456789";
static const std::string hexs = "0123456789abcdef";

static bool testInteger(const std::string& s, int min, int max)
{
	if (s.empty())
		return false;
	if (!containsOnly(s, digits))
		return false;
	if (s.size() > 1 && s[0] == '0')
		return false;
	int v = std::stoi(s);
	return v >= min && v <= max;
}

static bool checkField(const std::string& key, const std::string& value)
{
	if (key == "byr")
	{
		// four digits; at least 1920 and at most 2002.
		return testInteger(value, 1920, 2002);
	}

	if (key == "iyr")
	{
		// four digits; at least 2010 and at most 2020.
		return testInteger(value, 2010, 2020);
	}

	if (key == "eyr")
	{
		// four digits; at least 2020 and at most 2030.
		return testInteger(value, 2020, 2030);
	}

	if (key == "hgt")
	{
		// a number followed by either cm or in:
		//   If cm, the number must be at least 150 and at most 193.
		//   If in, the number must be at least 59 and at most 76.

		if (value.size() < 3)
			return false;
		if (endsWith(value, "cm"))
		{
			std::string s = value.substr(0, value.size() - 2);
			return testInteger(s, 150, 193);
		}

		if (endsWith(value, "in"))
		{
			std::string s = value.substr(0, value.size() - 2);
			return testInteger(s, 59, 76);
		}

		return false;
	}

	if (key == "hcl")
	{
		// a # followed by exactly six characters 0-9 or a-f.
		if (value.size() != 7)
			return false;
		if (value[0] != '#')
			return false;
		return containsOnly(value.substr(1), hexs);
	}

	if (key == "ecl")
	{
		// exactly one of: amb blu brn gry grn hzl oth.
		const std::set<std::string> validValues{ "amb",  "blu", "brn", "gry", "grn", "hzl", "oth" };
		return validValues.contains(value);
	}

	if (key == "pid")
	{
		// a nine-digit number, including leading zeroes.
		if (value.size() != 9)
			return false;
		return containsOnly(value, digits);
	}

	return false;
}

static int getValidPassports(bool strict)
{
	auto l = readStringList("input/4.txt");
	if (!l.back().empty())
		l.push_back("");
	std::vector<std::map<std::string, std::string>> recs;
	std::map<std::string, std::string> m;
	for (const auto& s : l)
	{
		if (s.empty())
		{
			recs.push_back(m);
			m.clear();
			continue;
		}
		auto v = splitStr(s, " \n");
		for (const auto& t : v)
		{
			auto k = splitStr(t, ":");
			m[k[0]] = k[1];
		}
	}

	int validRecords = 0;
	const std::vector<std::string> fields = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };
	for (const auto& r : recs)
	{
		int validFieldCount = 0;
		for (const auto& f : fields)
		{
			auto it = r.find(f);
			if (it != r.end())
			{
				if (!strict || checkField(it->first, it->second))
					++validFieldCount;
			}
		}
		if (validFieldCount == 7)
			++validRecords;
	}
	return validRecords;
}

int day4a()
{
	return getValidPassports(false);
}

int day4b()
{
	return getValidPassports(true);
}
