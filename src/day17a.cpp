#include "utils.h"

struct Cell
{
	Cell() {};
	Cell(int x, int y, int z) : x(x), y(y), z(z) {}
	int x = 0;
	int y = 0;
	int z = 0;

	bool operator== (const Cell& other) const
	{
		return (x == other.x) && (y == other.y) && (z == other.z);
	}

	std::vector<Cell> getNeighborsPos() const
	{
		std::vector<Cell> result;
		for (int x = -1; x < 2; ++x)
			for (int y = -1; y < 2; ++y)
				for (int z = -1; z < 2; ++z)
					if (x || y || z)
						result.emplace_back(this->x + x, this->y + y, this->z + z);
		return result;
	}

	bool containded(const std::vector<Cell>& cells) const
	{
		for (const auto& c : cells)
			if (c == *this)
				return true;
		return false;
	}

	int getNeighborCount(const std::vector<Cell>& cells) const
	{
		int result = 0;
		const auto neighborsPos = getNeighborsPos();
		for (const auto& n : neighborsPos)
		{
			if (n.containded(cells))
			{
				++result;
				if (result > 3)
					break;
			}
		}

		return result;
	}
};

int day17a()
{
	std::vector<Cell> cells;

	auto l = readStringList("input/17.txt");
	for (size_t row = 0; row < l.size(); ++row)
	{
		const auto& s = l[row];
		for (size_t col = 0; col < s.size(); ++col)
			if (s[col] == '#')
				cells.emplace_back(col, row, 0);
	}

	for (int i = 0; i < 6; ++i)
	{
		std::vector<Cell> newCells;
		for (const auto& cell : cells)
		{
			int neighborsCount = cell.getNeighborCount(cells);
			if (neighborsCount == 2 || neighborsCount == 3)
				newCells.push_back(cell);

			const auto neighbors = cell.getNeighborsPos();
			for (const auto& n : neighbors)
			{
				if (!n.containded(cells))
				{
					int neighborsCount = n.getNeighborCount(cells);
					if (neighborsCount == 3)
						if (!n.containded(newCells))
							newCells.push_back(n);
				}
			}
		}

		cells = newCells;
	}

	return cells.size();
}
