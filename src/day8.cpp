#include "utils.h"

struct ProgLine
{
	enum Cmd
	{
		nop,
		acc,
		jmp
	};

	Cmd cmd;
	int arg;
};

typedef std::vector<ProgLine> Prog;

static Prog readProg()
{
	Prog result;
	auto l = readStringList("input/8.txt");
	for (const auto& s : l)
	{
		auto tokens = splitStr(s, " +");
		assert(tokens.size() == 2);
		ProgLine progLine;
		if (tokens[0] == "nop")
			progLine.cmd = ProgLine::nop;
		else if (tokens[0] == "acc")
			progLine.cmd = ProgLine::acc;
		else if (tokens[0] == "jmp")
			progLine.cmd = ProgLine::jmp;
		else
			throw std::exception();
		progLine.arg = strToInt(tokens[1]);
		result.push_back(progLine);
	}
	return result;
}

static bool runProg(const Prog& prog, int& acc, int patch)
{
	int pc = 0;
	std::set<int> used;
	for (;;)
	{
		if (used.contains(pc))
			return false;
		used.insert(pc);

		ProgLine progLine = prog[pc];

		if (pc == patch)
		{
			if (progLine.cmd == ProgLine::jmp)
				progLine.cmd = ProgLine::nop;
			else if (progLine.cmd == ProgLine::nop)
				progLine.cmd = ProgLine::jmp;
		}

		switch (progLine.cmd)
		{
		case ProgLine::acc:
			acc += progLine.arg;
			++pc;
			break;
		case ProgLine::nop:
			++pc;
			break;
		case ProgLine::jmp:
			pc += progLine.arg;
			break;
		}

		assert(pc >= 0);
		if (pc >= int(prog.size()))
			return true;
	}
}

int day8a()
{
	int acc = 0;
	assert(!runProg(readProg(), acc, -1));
	return acc;
}

int day8b()
{
	auto prog = readProg();
	for (size_t i = 0; i < prog.size(); ++i)
	{
		int acc = 0;
		if (runProg(readProg(), acc, i))
			return acc;
	}

	throw std::exception();
}
