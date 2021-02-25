#include "utils.h"

struct Line
{
	std::set<std::string> ingredients;
	std::set<std::string> allergens;
};

std::pair<int, std::string> day21()
{
	auto rawLines = readStringList("input/21.txt");
	const std::string del = "(contains ";
	std::vector<Line> data;
	for (const auto& l : rawLines)
	{
		const size_t p = l.find(del);
		assert(p != std::string::npos);
		const auto i = splitStr(l.substr(0, p), " ");
		const auto a = splitStr(l.substr(p + del.size()), " ),");
		data.emplace_back(std::set<std::string>{ i.begin(), i.end() }, std::set<std::string>{ a.begin(), a.end() });
	}

	std::map<std::string, std::string> readyAllergens;

	bool found = true;
	while (found)
	{
		found = false;

		std::set<std::string> allAllergens;
		for (const auto& l : data)
			allAllergens.insert(l.allergens.begin(), l.allergens.end());

		for (const auto& a : allAllergens)
		{
			//std::cout << "[" << a << "]\n";

			std::set<std::string> possibleIngredients;
			bool first = true;
			for (const auto& l : data)
			{
				if (l.allergens.contains(a))
				{
					if (first)
					{
						first = false;
						possibleIngredients.insert(l.ingredients.begin(), l.ingredients.end());
					}
					else
					{
						std::set<std::string> intersect;
						std::set_intersection(possibleIngredients.begin(), possibleIngredients.end(), l.ingredients.begin(), l.ingredients.end(),
							std::inserter(intersect, intersect.begin()));
						possibleIngredients = intersect;
					}

					//for (const auto& i : possibleIngredients)
					//	std::cout << i << " ";
					//std::cout << "\n";
				}
			}

			if (possibleIngredients.size() == 1)
			{
				//std::cout << "found\n\n";
				found = true;
				const std::string foundIngredient = *possibleIngredients.begin();
				readyAllergens[a] = foundIngredient;
				for (auto& l : data)
				{
					l.ingredients.erase(foundIngredient);
					l.allergens.erase(a);
				}
			}
			else
			{
				//std::cout << "not found\n\n";
			}
		}
	}

	int result = 0;
	for (const auto& l : data)
		result += l.ingredients.size();

	std::string result2 = "";
	for (const auto& [key, value] : readyAllergens)
	{
		//std::cout << key << ": " << value << "\n";
		if (!result2.empty())
			result2 += ",";
		result2 += value;
	}
	//std::cout << "\n";

	//std::cout << result2 << "\n";

	return {result, result2};
}
