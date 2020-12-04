#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <sstream>
#include <cstdint>
#include <fstream>

std::vector<std::string> readStringList(const std::string& path);
std::vector<int> readIntList(const std::string& path);
