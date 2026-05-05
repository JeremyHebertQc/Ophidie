#pragma once
#include <vector>

#include "const.h"
#include "Settings.h"
#include "Snake.h"

enum TileType {
	air = 0,
	wall = 1,
	egg = 2,
	snake = 3
};


class Grid
{
public:
	Grid(); //genere stuff based on mode, create egg
	~Grid();


	void createMap(int x, int y, GameMode mode, Difficulty difficulty);
	TileType getTileAt(int x, int y);

	void placeEggs(int numberOfEggs);

private:
	Snake snake;
	int width, height;
	std::vector<std::vector<int>> board;
};

