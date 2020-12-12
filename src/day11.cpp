#include "utils.h"

// 0 bit - chair
// 1 bit - occupied
// 2 bit - next occupied

static int getNeighbors(const std::vector<std::vector<int>>& maze, int x, int y, bool adjacentOnly)
{
	std::vector<std::pair<int, int>> directions = {
		{-1, -1},	{-1, 0},	{-1, 1},
		{0, -1},				{0, 1},
		{1, -1},	{1, 0},		{1, 1},
	};

	const int h = maze.size();
	const int w = maze.front().size();

	int result = 0;

	for (const auto& [lx, ly] : directions)
	{
		int nx = x;
		int ny = y;
		for (;;)
		{
			nx += lx;
			ny += ly;
			if (nx < 0 || nx >= w || ny < 0 || ny >= h)
				break;

			if (maze[ny][nx] & 2)
				++result;

			if (maze[ny][nx] & 1)
				break;

			if (adjacentOnly)
				break;
		}
	}

	return result;
}

static int getOccupedSeats(const std::vector<std::vector<int>>& maze)
{
	int result = 0;

	for (size_t y = 0; y < maze.size(); ++y)
	{
		for (size_t x = 0; x < maze[y].size(); ++x)
		{
			if (maze[y][x] == 3)
				++result;
		}
	}

	return result;
}

static int stepMaze(std::vector<std::vector<int>>& maze, int maxChair, bool adjacentOnly)
{
	for (size_t y = 0; y < maze.size(); ++y)
	{
		for (size_t x = 0; x < maze[y].size(); ++x)
		{
			int& k = maze[y][x];
			if (k)
			{
				int n = getNeighbors(maze, x, y, adjacentOnly);
				if ((k & 2 && n < maxChair) || (k + n == 1))
					k |= 4;
			}
		}
	}

	int changes = 0;

	for (size_t y = 0; y < maze.size(); ++y)
	{
		for (size_t x = 0; x < maze[y].size(); ++x)
		{
			int& k = maze[y][x];
			if (k == 3 || k == 5)
				++changes;
			k = k >> 1 | k & 1;
		}
	}

	return changes;
}

static void printMaze(const std::vector<std::vector<int>>& maze)
{
	for (size_t y = 0; y < maze.size(); ++y)
	{
		for (size_t x = 0; x < maze[y].size(); ++x)
		{
			int k = maze[y][x];
			char c = '?';
			if (k == 0)
				c = '.';
			else if (k == 1)
				c = 'L';
			else if (k == 3)
				c = '#';
			std::cout << c;
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

static std::vector<std::vector<int>> loadMaze()
{
	auto l = readStringList("input/11.txt");
	std::vector<std::vector<int>> maze(l.size());
	for (size_t i = 0; i < l.size(); ++i)
	{
		const auto& line = l[i];
		if (i)
			assert(maze.front().size() == line.size());
		maze[i].resize(line.size());
		std::transform(line.begin(), line.end(), maze[i].begin(), [](char c) { return c == 'L'; });
	}
	return maze;
}

static int getResult(int maxChair, bool adjacentOnly)
{
	auto maze = loadMaze();

	//printMaze(maze);
	while (stepMaze(maze, maxChair, adjacentOnly))
	{
		//printMaze(maze);
	}

	return getOccupedSeats(maze);
}

int day11a()
{
	return getResult(4, true);
}

int day11b()
{
	return getResult(5, false);
}
