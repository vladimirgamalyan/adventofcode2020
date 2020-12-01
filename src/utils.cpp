#include "utils.h"
#include <fstream>

std::vector<int> readIntList(const std::string& path)
{
	std::ifstream ifs(path);
	std::vector<int> result;
	for (std::string line; std::getline(ifs, line);)
		result.push_back(std::stoi(line));
	return result;
}
