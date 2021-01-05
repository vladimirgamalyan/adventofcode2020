#include "utils.h"

class Tile
{
public:
	struct Side
	{
		static const int Any = -1;
		static const int Nothing = -2;
	};


	static const size_t width = 10;
	static const size_t height = 10;
	static const size_t variants = 8;

	typedef std::array<std::array<bool, width>, height> Bitmap;

	void dump(size_t variant, std::ostream& os) const
	{
		const auto b = getBitmapVariant(variant);
		os << "Tile " << id << ":\n";
		for (int row = 0; row < height; ++row)
		{
			for (int col = 0; col < width; ++col)
				os << (b[row][col] ? '#' : '.');
			os << "\n";
		}
	}

	void dump(std::ostream& os) const
	{
		dump(curVariant, os);
	}

	void parse(const std::vector<std::string>& l, size_t lineIndex)
	{
		const std::string tileTitle = l[lineIndex];
		assert(tileTitle.size() == 10);
		assert(tileTitle[9] == ':');
		const std::string idStr = tileTitle.substr(5, 4);
		id = strToInt(idStr);
		curVariant = 0;
		++lineIndex;

		for (size_t row = 0; row < height; ++row)
			for (size_t col = 0; col < width; ++col)
				bitmap[row][col] = l[lineIndex + row][col] == '#';

		std::set<Bitmap> differentBitmaps;

		for (size_t variant = 0; variant < variants; ++variant)
		{
			differentBitmaps.insert(getBitmapVariant(variant));

			for (size_t side = 0; side < 4; ++side)
			{
				uint16_t s = getSide(variant, side);
				borders.at(variant).at(side) = s;
				borderSet.insert(s);
			}
		}
		assert(differentBitmaps.size() == 8);
	}

	uint16_t top() const
	{
		return borders.at(curVariant).at(0);
	}

	uint16_t right() const
	{
		return borders.at(curVariant).at(1);
	}

	uint16_t bottom() const
	{
		return borders.at(curVariant).at(2);
	}

	uint16_t left() const
	{
		return borders.at(curVariant).at(3);
	}

	bool hasBorder(uint16_t b) const
	{
		return borderSet.contains(b);
	}

	int getId() const
	{
		return id;
	}

	bool operator< (const Tile& other) const
	{
		return id < other.id;
	}

	void setVariant(size_t v)
	{
		curVariant = v;
	}

	Bitmap getBmp() const
	{
		return getBitmapVariant(curVariant);
	}

private:
	int id = -1;
	size_t curVariant = 0;
	Bitmap bitmap;
	std::array<std::array<uint16_t, 4>, variants> borders;
	std::set<uint16_t> borderSet;

	Bitmap getBitmapVariant(size_t variant) const
	{
		Bitmap result;

		bool rotate = variant & 1;
		bool flipHor = variant & 2;
		bool flipVert = variant & 4;

		for (int row = 0; row < height; ++row)
		{
			for (int col = 0; col < width; ++col)
			{
				int x = col;
				int y = row;

				if (rotate)
				{
					y = col;
					x = width - 1 - row;
				}

				if (flipHor)
					x = width - 1 - x;
				if (flipVert)
					y = height - 1 - y;

				result[row][col] = bitmap[y][x];
			}
		}

		return result;
	}

	uint16_t getSide(size_t variant, size_t side) const
	{
		uint16_t result = 0;

		const auto b = getBitmapVariant(variant);
		switch (side)
		{
		case 0:
			// top
			for (size_t col = 0; col < width; ++col)
				if (b[0][col])
					result |= (1u << col);
			break;
		case 1:
			// right
			for (size_t row = 0; row < height; ++row)
				if (b[row][width - 1])
					result |= (1u << row);
			break;
		case 2:
			// bottom
			for (size_t col = 0; col < width; ++col)
				if (b[height - 1][col])
					result |= (1u << col);
			break;
		case 3:
			// left
			for (size_t row = 0; row < height; ++row)
				if (b[row][0])
					result |= (1u << row);
			break;
		}

		return result;
	}
};

typedef std::vector<Tile> Tiles;
// row, then col
typedef std::vector<std::vector<Tile>> Field;


typedef std::vector<std::vector<int>> FullPicture;

static bool borderExists(const Tiles& tiles, uint16_t border, int excludedTileId)
{
	for (const auto& tile : tiles)
		if (tile.getId() != excludedTileId && tile.hasBorder(border))
			return true;
	return false;
}

static Tiles parseInput()
{
	auto l = readStringList("input/20.txt");
	Tiles tiles;

	for (size_t lineIndex = 0; lineIndex < l.size(); lineIndex += 12)
	{
		tiles.push_back(Tile());
		tiles.back().parse(l, lineIndex);
	}

	return tiles;
}

static std::vector<Tile> findTiles(int top, int right, int bottom, int left,
	const Tiles& tiles, const std::set<int>& usedTiles)
{
	std::vector<Tile> result;

	for (auto tile : tiles)
	{
		if (usedTiles.contains(tile.getId()))
			continue;

		for (size_t i = 0; i < Tile::variants; ++i)
		{
			tile.setVariant(i);

			if (top == Tile::Side::Nothing && borderExists(tiles, tile.top(), tile.getId()))
				continue;
			if (right == Tile::Side::Nothing && borderExists(tiles, tile.right(), tile.getId()))
				continue;
			if (bottom == Tile::Side::Nothing && borderExists(tiles, tile.bottom(), tile.getId()))
				continue;
			if (left == Tile::Side::Nothing && borderExists(tiles, tile.left(), tile.getId()))
				continue;

			if (top >= 0 && tile.top() != top)
				continue;
			if (right >= 0 && tile.right() != right)
				continue;
			if (bottom >= 0 && tile.bottom() != bottom)
				continue;
			if (left  >= 0 && tile.left() != left)
				continue;

			result.push_back(tile);
		}
	}

	return result;
}

static bool solvePuzzleFromLeftTopTile(Field& field, const Tiles& tiles, const Tile& leftTopTile, size_t sideLen)
{
	field[0][0] = leftTopTile;

	std::set<int> usedTiles;
	usedTiles.insert(field[0][0].getId());

	for (size_t row = 0; row < sideLen; ++row)
	{
		for (size_t col = 0; col < sideLen; ++col)
		{
			if (row == 0 && col == 0)
				continue;

			int top = (row > 0) ? field[row - 1][col].bottom() : Tile::Side::Nothing;
			int right = (col == sideLen - 1) ? Tile::Side::Nothing : Tile::Side::Any;
			int bottom = (row == sideLen - 1) ? Tile::Side::Nothing : Tile::Side::Any;
			int left = (col > 0) ? field[row][col - 1].right() : Tile::Side::Nothing;

			const auto nextPossibleTiles = findTiles(top, right, bottom, left, tiles, usedTiles);
			if (nextPossibleTiles.empty())
				return false;

			assert(nextPossibleTiles.size() == 1);

			auto nextTile = nextPossibleTiles[0];
			field[row][col] = nextTile;
			usedTiles.insert(nextTile.getId());
		}
	}

	return true;
}

static Field solvePuzzle(const Tiles& tiles)
{
	const size_t sideLen = static_cast<size_t>(sqrt(tiles.size()));
	assert(sideLen * sideLen == tiles.size());

	Field field(sideLen);
	for (auto& row : field)
		row.resize(sideLen);

	std::set<int> usedTiles;
	auto cornerTiles = findTiles(Tile::Side::Nothing, Tile::Side::Any, Tile::Side::Any, Tile::Side::Nothing, tiles, usedTiles);

	for (size_t i = 0; i < cornerTiles.size(); ++i)
		if (solvePuzzleFromLeftTopTile(field, tiles, cornerTiles[i], sideLen))
			return field;

	throw std::runtime_error("can't resolve ");
}

struct Snake
{
	size_t width;
	size_t height;
	std::vector<std::pair<size_t, size_t>> pixels;
};

static bool findSnake(const FullPicture& fullPicture, const Snake& snake, size_t col, size_t row, size_t variant, size_t sideLen)
{
	bool rotate = variant & 1;
	bool flipHor = variant & 2;
	bool flipVert = variant & 4;

	for (const auto& p : snake.pixels)
	{
		size_t x = p.second + col;
		size_t y = p.first + row;

		if (rotate)
		{
			int t = y;
			y = x;
			x = sideLen - 1 - t;
		}

		if (flipHor)
			x = sideLen - 1 - x;
		if (flipVert)
			y = sideLen - 1 - y;

		if (!fullPicture[y][x])
			return false;
	}
	return true;
}

static Snake getSnake()
{
	std::vector<std::string> snakePattern = {
		"                  # ",
		"#    ##    ##    ###",
		" #  #  #  #  #  #   "
	};

	Snake snake;
	snake.height = snakePattern.size();
	snake.width = snakePattern[0].length();

	for (size_t row = 0; row < snakePattern.size(); ++row)
		for (size_t col = 0; col < snakePattern[row].size(); ++col)
			if (snakePattern[row][col] == '#')
				snake.pixels.emplace_back(row, col);

	return snake;
}

long long day20a()
{
	const auto tiles = parseInput();
	auto field = solvePuzzle(tiles);

	long long result = field.front().front().getId();
	result *= field.front().back().getId();
	result *= field.back().front().getId();
	result *= field.back().back().getId();

	return result;
}

long long day20b()
{
	const auto tiles = parseInput();
	Field field = solvePuzzle(tiles);

	size_t sideLen = field.size() * 8;

	FullPicture fullPicture(sideLen);
	size_t pixelCount = 0;
	for (size_t row = 0; row < sideLen; ++row)
	{
		fullPicture[row].resize(sideLen);
		for (size_t col = 0; col < sideLen; ++col)
		{
			bool pixel = field[row / 8][col / 8].getBmp()[row % 8 + 1][col % 8 + 1];
			if (pixel)
				++pixelCount;
			fullPicture[row][col] = pixel;
		}
	}

	Snake snake = getSnake();

	size_t searchZoneH = sideLen - snake.height  + 1;
	size_t searchZoneW = sideLen - snake.width + 1;

	int snakeCount = 0;
	for (size_t v = 0; v < 8; ++v)
	{
		snakeCount = 0;
		for (size_t y = 0; y < searchZoneH; ++y)
			for (size_t x = 0; x < searchZoneW; ++x)
				if (findSnake(fullPicture, snake, x, y, v, sideLen))
					++snakeCount;
		if (snakeCount)
			break;
	}

	return pixelCount - snake.pixels.size() * snakeCount;
}
