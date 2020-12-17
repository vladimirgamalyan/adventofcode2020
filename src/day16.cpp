#include "utils.h"

typedef std::pair<int, int> NumberRange;
typedef std::vector<NumberRange> Rule;
typedef std::map<std::string, Rule> Rules;
typedef std::vector<int> Ticket;
typedef std::vector<Ticket> Tickets;

struct InputData
{
	Rules rules;
	Ticket yourTicket;
	Tickets nearbyTickets;
};

static bool inRange(const NumberRange& numberRange, int v)
{
	return (v >= numberRange.first && v <= numberRange.second);
}

static bool testField(const Rule& rule, int field)
{
	return std::any_of(rule.begin(), rule.end(), [field](const auto& r) {return inRange(r, field); });
}

static bool testField(const Rules& rules, int field)
{
	return std::any_of(rules.begin(), rules.end(), [field](const auto& r) {return testField(r.second, field); });
}

static bool validateTicket(const Rules& rules, const Ticket& ticket)
{
	return std::all_of(ticket.begin(), ticket.end(), [&rules](const auto& field) {return testField(rules, field); });
}

static bool testRule(const Rule& rule, const Tickets& tickets, size_t fieldIndex)
{
	return std::all_of(tickets.begin(), tickets.end(), [&rule, fieldIndex](const auto& ticket) {return testField(rule, ticket[fieldIndex]); });
}

static InputData readInputData()
{
	InputData result;

	auto l = readStringList("input/16.txt");

	enum class ParserStage
	{
		ParseRules,
		ParseYourTicket,
		ParseNearbyTickets
	};

	ParserStage parserStage = ParserStage::ParseRules;
	size_t line;
	for (line = 0; line < l.size(); ++line)
	{
		const auto& s = l[line];
		if (s.empty())
			continue;

		if (trimString(s) == "your ticket:")
		{
			assert(parserStage == ParserStage::ParseRules);
			parserStage = ParserStage::ParseYourTicket;
			continue;
		}

		if (trimString(s) == "nearby tickets:")
		{
			assert(parserStage == ParserStage::ParseYourTicket);
			parserStage = ParserStage::ParseNearbyTickets;
			continue;
		}

		if (parserStage == ParserStage::ParseRules)
		{
			const auto kv = splitStr(s, ":");
			assert(kv.size() == 2);
			const auto ruleName = trimString(kv.front());
			auto& curRule = result.rules[ruleName];
			const auto rulesStr = splitStr(kv[1], " or");
			assert(!rulesStr.empty());
			for (const auto& r : rulesStr)
			{
				const auto minMax = splitStr(r, "-");
				assert(minMax.size() == 2);
				curRule.emplace_back(std::make_pair(strToInt(minMax[0]), strToInt(minMax[1])));
			}
		}

		if (parserStage == ParserStage::ParseYourTicket)
		{
			assert(result.yourTicket.empty());
			result.yourTicket = splitStrToInt(s, " ,");
			assert(!result.yourTicket.empty());
		}

		if (parserStage == ParserStage::ParseNearbyTickets)
		{
			result.nearbyTickets.push_back(splitStrToInt(s, " ,"));
		}
	}
	assert(!result.rules.empty());
	assert(!result.yourTicket.empty());
	assert(!result.nearbyTickets.empty());

	size_t fieldCount = result.yourTicket.size();
	for (const auto& ticket : result.nearbyTickets)
		assert(fieldCount == ticket.size());

	return result;
}

int day16a()
{
	const auto data = readInputData();

	int errorSum = 0;
	for (const auto& tickets : data.nearbyTickets)
		for (int v : tickets)
			if (!testField(data.rules, v))
				errorSum += v;

	return errorSum;
}

long long day16b()
{
	auto data = readInputData();
	size_t fieldCount = data.yourTicket.size();

	Tickets validNearbyTickets;
	for (const auto& ticket : data.nearbyTickets)
		if (validateTicket(data.rules, ticket))
			validNearbyTickets.push_back(ticket);
	data.nearbyTickets = validNearbyTickets;

	std::set<size_t> foundFields;
	std::map<std::string, size_t> fieldPositions;

	while (foundFields.size() < fieldCount)
	{
		bool foundRule = false;
		for (const auto& [name, rule] : data.rules)
		{
			int validPositions = 0;
			size_t p = 0;
			for (size_t i = 0; i < fieldCount; ++i)
			{
				if (foundFields.contains(i))
					continue;

				if (testRule(rule, data.nearbyTickets, i))
				{
					p = i;
					++validPositions;
				}
			}
			if (validPositions == 1)
			{
				fieldPositions[name] = p;
				foundFields.insert(p);
				break;
			}
		}
	}

	long long result = 1;
	for (const auto& [name, v] : fieldPositions)
		if (startsWith(name, "departure"))
			result *= data.yourTicket[v];

	return result;
}
