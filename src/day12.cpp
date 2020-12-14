#include "utils.h"

// direction:
//	0 - N
//	1 - W
//	2 - S
//	3 - E

int day12a()
{
	auto l = readStringList("input/12.txt");
	int x = 0;
	int y = 0;
	char d = 3;
	for (const auto& s : l)
	{
		char cmd = s[0];
		int v = strToInt(s.substr(1));
		assert(v > 0);

		if (cmd == 'L')
		{
			while (v)
			{
				d = (d + 1) % 4;
				v -= 90;
				assert(v >= 0);
			}
		}
		if (cmd == 'R')
		{
			while (v)
			{
				d = d ? d - 1 : 3;
				v -= 90;
				assert(v >= 0);
			}
		}
		int td = -1;
		if (cmd == 'N') td = 0;
		if (cmd == 'W') td = 1;
		if (cmd == 'S') td = 2;
		if (cmd == 'E') td = 3;
		if (cmd == 'F')
		{
			td = d;
		}
		if (td != -1)
		{
			if (td == 0) y += v;
			if (td == 1) x -= v;
			if (td == 2) y -= v;
			if (td == 3) x += v;
		}
	}

	return abs(x) + abs(y);
}

int day12b()
{
	auto l = readStringList("input/12.txt");
	int waypointX = 10;
	int waypointY = 1;
	int x = 0;
	int y = 0;

	for (const auto& s : l)
	{
		char cmd = s[0];
		int v = strToInt(s.substr(1));
		assert(v > 0);

		if (cmd == 'L')
		{
			while (v)
			{
				int t = waypointY;
				waypointY = waypointX;
				waypointX = -t;
				v -= 90;
				assert(v >= 0);
			}
		}
		if (cmd == 'R')
		{
			while (v)
			{
				int t = waypointY;
				waypointY = -waypointX;
				waypointX = t;
				v -= 90;
				assert(v >= 0);
			}
		}

		if (cmd == 'N') waypointY += v;
		if (cmd == 'W') waypointX -= v;
		if (cmd == 'S') waypointY -= v;
		if (cmd == 'E') waypointX += v;

		if (cmd == 'F')
		{
			x += waypointX * v;
			y += waypointY * v;
		}
	}

	return abs(x) + abs(y);
}
