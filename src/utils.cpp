#include "utils.h"

void readStringList(const std::string& path, std::vector<std::string>& result)
{
	std::ifstream ifs(path);
	for (std::string line; std::getline(ifs, line);)
		result.push_back(line);
}

std::vector<std::string> readStringList(const std::string& path)
{
	std::vector<std::string> result;
	readStringList(path, result);
	return result;
}

std::vector<std::vector<std::string>> readStringLists(const std::string& path)
{
	std::vector<std::vector<std::string>> result(1);
	std::ifstream ifs(path);
	for (std::string line; std::getline(ifs, line);)
		if (line.empty())
			result.resize(result.size() + 1);
		else
			result.back().push_back(line);
	return result;
}

std::vector<int> readIntList(const std::string& path)
{
	auto l = readStringList(path);
	std::vector<int> result(l.size());
	std::transform(l.begin(), l.end(), result.begin(), [](const std::string& s) {return std::stoi(s); });
	return result;
}

std::vector<long long> readLongIntList(const std::string& path)
{
	auto l = readStringList(path);
	std::vector<long long> result(l.size());
	std::transform(l.begin(), l.end(), result.begin(), [](const std::string& s) {return std::stoll(s); });
	return result;
}

std::vector<std::string> splitStr(const std::string& s, const std::string& delimiters)
{
	std::vector<std::string> result;
	size_t last = 0;
	size_t next = 0;
	std::string token;
	while ((next = s.find_first_of(delimiters, last)) != std::string::npos)
	{
		token = s.substr(last, next - last);
		if (!token.empty())
			result.push_back(token);
		last = next + 1;
	}
	token = s.substr(last);
	if (!token.empty())
		result.push_back(token);
	return result;
}

std::vector<int> splitStrToInt(const std::string& s, const std::string& delimiters)
{
	const auto l = splitStr(s, delimiters);
	std::vector<int> result;
	for (const auto& s : l)
		result.push_back(strToInt(s));
	return result;
}

bool containsOnly(const std::string& s, const std::string& chars)
{
	for (char c : s)
	{
		if (chars.find(c) == std::string::npos)
			return false;
	}
	return true;
}

bool endsWith(const std::string& s, const std::string& ending)
{
	if (ending.size() > s.size()) return false;
	return std::equal(ending.rbegin(), ending.rend(), s.rbegin());
}

bool startsWith(const std::string& s, const std::string& beginning)
{
	return s.rfind(beginning, 0) == 0;
}

long strToInt(const std::string& s, int base)
{
	char* end;
	errno = 0;
	long result = std::strtol(s.c_str(), &end, base);
	if (errno == ERANGE || result > INT_MAX || result < INT_MIN)
		throw std::out_of_range("strToInt: string is out of range");
	if (s.length() == 0 || *end != '\0')
		throw std::invalid_argument("strToInt: invalid string");
	return result;
}

long long strToLongLong(const std::string& s, int base)
{
	char* end;
	errno = 0;
	long long result = std::strtoll(s.c_str(), &end, base);
	if (errno == ERANGE || result > LLONG_MAX || result < LLONG_MIN)
		throw std::out_of_range("strToLongLong: string is out of range");
	if (s.length() == 0 || *end != '\0')
		throw std::invalid_argument("strToLongLong: invalid string");
	return result;
}

std::string trimString(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && isspace(*it))
		it++;

	std::string::const_reverse_iterator rit = s.rbegin();
	while (rit.base() != it && isspace(*rit))
		rit++;

	return std::string(it, rit.base());
}

size_t nthOccurrence(const std::string& str, const std::string& findMe, int nth)
{
	size_t pos = 0;
	int cnt = 0;

	while (cnt != nth)
	{
		++pos;
		pos = str.find(findMe, pos);
		if (pos == std::string::npos)
			return -1;
		++cnt;
	}
	return pos;
}
