#include "utils.h"

int day1a()
{
	std::vector<int> numbers = readIntList("input/1.txt");

	for (size_t i = 0; i < numbers.size() - 1; ++i)
	{
		for (size_t k = i + 1; k < numbers.size(); ++k)
		{
			int a = numbers[i];
			int b = numbers[k];
			if (a + b == 2020)
				return a * b;
		}
	}

	throw std::exception();
}

int day1b()
{
	std::vector<int> numbers = readIntList("input/1.txt");

	for (size_t i = 0; i < numbers.size() - 2; ++i)
	{
		for (size_t k = i + 1; k < numbers.size() - 1; ++k)
		{
			for (size_t j = k + 1; j < numbers.size(); ++j)
			{
				int a = numbers[i];
				int b = numbers[k];
				int c = numbers[j];
				if (a + b + c == 2020)
					return a * b * c;
			}
		}
	}

	throw std::exception();
}
