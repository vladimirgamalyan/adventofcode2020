#include "utils.h"
#include <fstream>
#include <algorithm>

std::vector<std::string> readStringList(const std::string& path)
{
	std::ifstream ifs(path);
	std::vector<std::string> result;
	for (std::string line; std::getline(ifs, line);)
		result.push_back(line);
	return result;
}

std::vector<int> readIntList(const std::string& path)
{
	auto l = readStringList(path);
	std::vector<int> result(l.size());
	std::transform(l.begin(), l.end(), result.begin(), [](const std::string& s) {return std::stoi(s); });
	return result;
}
