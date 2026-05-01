#pragma once
#include <vector>

#include "Snake.h"

enum TileType {
	Air,
	Egg,
	snake,
	wall
};


class Grid
{
public:
	Grid();
	~Grid();

	void handleCollision(TileType type);

private:
	Snake snake;
	std::vector<std::vector<int>> board;
};

