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
#include <climits>

void readStringList(const std::string& path, std::vector<std::string>& result);
std::vector<std::string> readStringList(const std::string& path);
std::vector<std::vector<std::string>> readStringLists(const std::string& path);
std::vector<int> readIntList(const std::string& path);
std::vector<long long> readLongIntList(const std::string& path);

std::vector<std::string> splitStr(const std::string& s, const std::string& delimiters);
std::vector<int> splitStrToInt(const std::string& s, const std::string& delimiters);
std::string trimString(const std::string& s);

bool containsOnly(const std::string& s, const std::string& chars);
bool endsWith(const std::string& s, const std::string& ending);
bool startsWith(const std::string& s, const std::string& beginning);

long strToInt(const std::string& s, int base = 0);
long long strToLongLong(const std::string& s, int base = 0);
