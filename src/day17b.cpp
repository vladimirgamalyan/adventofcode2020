#include "utils.h"

struct Cell4D
{
	Cell4D() {};
	Cell4D(int x, int y, int z, int w) : x(x), y(y), z(z), w(w) {}
	int x = 0;
	int y = 0;
	int z = 0;
	int w = 0;

	bool operator== (const Cell4D& other) const
	{
		return (x == other.x) && (y == other.y) && (z == other.z) && (w == other.w);
	}

	std::vector<Cell4D> getNeighborsPos() const
	{
		std::vector<Cell4D> result;
		for (int x = -1; x < 2; ++x)
			for (int y = -1; y < 2; ++y)
				for (int z = -1; z < 2; ++z)
					for (int w = -1; w < 2; ++w)
						if (x || y || z || w)
							result.emplace_back(this->x + x, this->y + y, this->z + z, this->w + w);
		return result;
	}

	bool containded(const std::vector<Cell4D>& cells) const
	{
		for (const auto& c : cells)
			if (c == *this)
				return true;
		return false;
	}

	int getNeighborCount(const std::vector<Cell4D>& cells) const
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

int day17b()
{
	std::vector<Cell4D> cells;

	auto l = readStringList("input/17.txt");
	for (size_t row = 0; row < l.size(); ++row)
	{
		const auto& s = l[row];
		for (size_t col = 0; col < s.size(); ++col)
			if (s[col] == '#')
				cells.emplace_back(col, row, 0, 0);
	}

	for (int i = 0; i < 6; ++i)
	{
		std::vector<Cell4D> newCells;
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
