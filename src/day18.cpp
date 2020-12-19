#include "utils.h"

static long long calcLine(const std::string& s)
{
	enum Operation
	{
		Nop,
		Plus,
		Mult
	};

	std::vector<long long> resultStack;
	std::vector<Operation> operationStack;

	long long result = 0;
	Operation operation = Plus;

	for (const auto& c : s)
	{
		if (c == ' ')
			continue;
		if (c == '+')
			operation = Plus;
		else if (c == '*')
			operation = Mult;
		else if (c == '(')
		{
			resultStack.push_back(result);
			operationStack.push_back(operation);
			result = 0;
			operation = Plus;
		}
		else if (c == ')')
		{
			long long n = result;

			result = resultStack.back();
			operation = operationStack.back();
			operationStack.pop_back();
			resultStack.pop_back();

			if (operation == Plus)
				result += n;
			if (operation == Mult)
				result *= n;
		}
		else
		{
			long long n = c - '0';
			if (operation == Plus)
				result += n;
			if (operation == Mult)
				result *= n;
		}
	}

	return result;
}

static std::string wrapNumbersInParentheses(const std::string& s)
{
	std::string result;

	for (const char c : s)
	{
		if (c < '0' || c > '9')
			result.push_back(c);
		else
		{
			result.push_back('(');
			result.push_back(c);
			result.push_back(')');
		}
	}

	return result;
}

static std::string wrapAdditionsInParentheses(const std::string& s)
{
	std::string str = wrapNumbersInParentheses(s);

	for (int i = 0; ; ++i)
	{
		size_t pos = nthOccurrence(str, "+", i + 1);
		if (pos == std::string::npos)
			break;

		size_t pre = pos;
		int parenthesesLevel = 0;
		for (;;)
		{
			--pre;
			if (str[pre] == ')')
				++parenthesesLevel;
			if (str[pre] == '(')
			{
				--parenthesesLevel;
				if (!parenthesesLevel)
				{
					str.insert(pre, "(");
					break;
				}
			}
		}

		size_t post = pos + 1;
		parenthesesLevel = 0;
		for (;;)
		{
			++post;
			if (str[post] == '(')
				++parenthesesLevel;
			if (str[post] == ')')
			{
				--parenthesesLevel;
				if (!parenthesesLevel)
				{
					str.insert(post + 1, ")");
					break;
				}
			}
		}
	}

	return str;
}

static long long calcLine2(const std::string& s)
{
	return calcLine(wrapAdditionsInParentheses(s));
}

long long day18a()
{
	long long result = 0;
	auto l = readStringList("input/18.txt");
	for (const auto& s : l)
		result += calcLine(s);
	return result;
}

long long day18b()
{
	long long result = 0;
	auto l = readStringList("input/18.txt");
	for (const auto& s : l)
		result += calcLine2(s);
	return result;
}
