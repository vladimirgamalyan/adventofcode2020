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

bool containsOnly(const std::string& s, const std::string& chars)
{
	for (char c : s)
	{
		if (chars.find(c) == std::string::npos)
			return false;
	}
	return true;
}

bool endsWith(std::string const& value, std::string const& ending)
{
	if (ending.size() > value.size()) return false;
	return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

int strToInt(std::string s)
{
	if (s.empty())
		throw std::exception();
	bool minus = s[0] == '-';
	if (minus)
		s = s.substr(1);
	if (s.size() > 10)
		throw std::exception();
	if (!containsOnly(s, "0123456789"))
		throw std::exception();
	if (s[0] == '0' && (minus || s.size()))
		throw std::exception();
	if (minus)
		return -std::stoi(s);
	return std::stoi(s);
}
