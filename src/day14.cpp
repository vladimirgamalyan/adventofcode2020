#include "utils.h"

uint64_t day14a()
{
	auto l = readStringList("input/14.txt");
	uint64_t result = 0;

	uint64_t mask_0 = 0;
	uint64_t mask_1 = 0;
	std::map<uint64_t, uint64_t> memory;
	result = 0;

	for (const auto& s : l)
	{
		auto t = splitStr(s, " =");
		assert(t.size() == 2);
		const std::string cmd = t[0];
		const std::string arg = t[1];
		
		if (cmd == "mask")
		{
			assert(arg.size() == 36);
			assert(containsOnly(arg, "01X"));

			mask_0 = 0;
			mask_1 = 0;

			for (size_t i = 0; i < 36; ++i)
			{
				char c = arg[35 - i];
				if (c == '0') mask_0 |= (1ULL << i);
				if (c == '1') mask_1 |= (1ULL << i);
			}
		}
		else
		{
			assert(cmd.size() >= 6);
			assert(cmd.substr(0, 4) == "mem[");
			assert(cmd.substr(cmd.size() - 1) == "]");

			uint64_t a = strToLongLong(cmd.substr(4, cmd.size() - 5));
			uint64_t v = strToLongLong(arg);

			v &= ~mask_0;
			v |= mask_1;

			result -= memory[a];
			memory[a] = v;
			result += v;
		}
	}

	return result;
}

uint64_t day14b()
{
	auto l = readStringList("input/14.txt");
	uint64_t result = 0;

	uint64_t mask_x = 0;
	uint64_t mask_x_bitcount = 0;
	uint64_t mask_1 = 0;
	std::map<uint64_t, uint64_t> memory;
	result = 0;

	for (const auto& s : l)
	{
		auto t = splitStr(s, " =");
		assert(t.size() == 2);
		const std::string cmd = t[0];
		const std::string arg = t[1];

		if (cmd == "mask")
		{
			assert(arg.size() == 36);
			assert(containsOnly(arg, "01X"));

			mask_x = 0;
			mask_1 = 0;

			for (size_t i = 0; i < 36; ++i)
			{
				char c = arg[35 - i];
				if (c == 'X') mask_x |= (1ULL << i);
				if (c == '1') mask_1 |= (1ULL << i);
			}

			mask_x_bitcount = 0;
			for (size_t i = 0; i < 64; ++i)
				if (mask_x & (1ULL << i))
					++mask_x_bitcount;
		}
		else
		{
			assert(cmd.size() >= 6);
			assert(cmd.substr(0, 4) == "mem[");
			assert(cmd.substr(cmd.size() - 1) == "]");

			uint64_t a = strToLongLong(cmd.substr(4, cmd.size() - 5));
			uint64_t val = strToLongLong(arg);

			a |= mask_1;
			a &= ~mask_x;

			for (size_t v = 0; v < (1ULL << mask_x_bitcount); ++v)
			{
				uint64_t a1 = a;
				size_t b = 0;
				for (size_t k = 0; k < 64; ++k)
				{
					if (mask_x & (1ULL << k))
					{
						if (v & (1ULL << b))
							a1 |= (1ULL << k);
						++b;
					}
				}
				result -= memory[a1];
				memory[a1] = val;
				result += val;
			}
		}
	}

	return result;
}
