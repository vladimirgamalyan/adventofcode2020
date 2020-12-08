#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <sstream>
#include <cstdint>
#include <fstream>
#include <map>
#include <set>

std::vector<std::string> readStringList(const std::string& path);
std::vector<std::vector<std::string>> readStringLists(const std::string& path);
std::vector<int> readIntList(const std::string& path);
std::vector<std::string> splitStr(const std::string& s, const std::string& delimiters);
bool containsOnly(const std::string& s, const std::string& chars);
bool endsWith(std::string const& value, std::string const& ending);
int strToInt(const std::string& s);