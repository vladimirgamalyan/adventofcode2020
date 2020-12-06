#include "utils.h"

int day6a()
{
	int result = 0;
	auto l = readStringLists("input/6.txt");
	for (const auto& group : l)
	{
		std::set<char> answers;
		for (const auto& line : group)
			for (char c : line)
				answers.insert(c);
		result += answers.size();
	}
	return result;
}

int day6b()
{
	int result = 0;
	auto l = readStringLists("input/6.txt");
	for (const auto& group : l)
	{
		std::vector<char> cmn;
		bool first = true;
		for (const auto& line : group)
		{
			std::vector<char> t;
			for (char c : line)
				t.push_back(c);
			std::sort(t.begin(), t.end());

			if (first)
			{
				first = false;
				cmn = t;
			}
			else
			{
				std::vector<char> r(cmn.size());
				auto it = std::set_intersection(cmn.begin(), cmn.end(), 
					t.begin(), t.end(), r.begin());
				r.resize(it - r.begin());
				cmn = r;
			}
			if (cmn.empty())
				break;
		}
		result += cmn.size();

	}
	return result;
}
