#include "Grid.h"
#include <iostream>
#include "utils.h"

Grid::Grid() {
	width = height = 0;
}

Grid::~Grid() {
	width = height = 0;
}

void Grid::placeEggs(int numberOfEggs) {
	int randX;
	int randY;

	while (numberOfEggs > 0) {
		randX = getRandIntInRange(0,width - 1);
		randY = getRandIntInRange(0,height - 1);

		if (board.at(randY).at(randX) == air) {
			board.at(randY).at(randX) = egg;
			numberOfEggs--;
		}
	}
}

void Grid::createMap(int x, int y, GameMode mode, Difficulty difficulty) {
	width = x;
	height = y;

	board.reserve(width);
	for (std::vector<int>& temp : board) {
		temp.reserve(height);
	}

	int numberOfEggs = 0;
	int numberOfTraps = 0;
	bool hasRandomWalls = false;

	switch (mode) {
		case NORMAL:
		break;
		case SURVIVAL:
		break;
		case DEATH_TRAP:
			hasRandomWalls = true;
		break;
		case SURVIVE_HELL:
			hasRandomWalls = true;
		break;
		default:
			exit(1);
	}
	switch (difficulty) {
		case BABY:
			numberOfEggs = 3;
			numberOfTraps = 0;
		break;
		case EZ:
			numberOfEggs = 3;
			numberOfTraps = 0.05 * x * height;
		break;
		case MEDIUM_RARE:
			numberOfEggs = 2;
			numberOfTraps = 0.10 * width * height;
		break;
		case MEDIUM:
			numberOfEggs = 1;
			numberOfTraps = 0.15 * width * height;
		break;
		case HARD:
			numberOfEggs = 1;
			numberOfTraps = 0.20 * width * height;
		break;
		case HARDER:
			numberOfEggs = 1;
			numberOfTraps = 0.25 * width * height;
		break;
		case TOO_HARD:
			numberOfEggs = 1;
			numberOfTraps = 0.30 * width * height;
		break;
		case HARDCORE:
			numberOfEggs = 1;
			numberOfTraps = 0.35 * width * height;
		break;
		default:
			exit(1);
	}

	for (int i = 0; i < width; i++) {
		board.emplace_back();
		for (int j = 0; j < height; j++) {
			board.at(i).push_back(0); //init everything as air
		}
	}

	board.at(0).at(0) = TileType::snake;
	board.at(0).at(1) = TileType::snake;
	board.at(0).at(2) = TileType::snake;

	if (hasRandomWalls) {
		int randX, randY = 0;
		while (numberOfTraps > 0) {
			randX = getRandIntInRange(0,width - 1);
			randY = getRandIntInRange(0,height - 1);

			if (board.at(randY).at(randX) == air) {
				board.at(randY).at(randX) = wall;
				numberOfTraps--;
			}
		}
	}


	placeEggs(numberOfEggs);



	/* --- render map in console --- */
	std::cout << std::endl;
	std::cout << std::endl;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			std::cout << board.at(i).at(j) << ' ';
		}
		std::cout << '\n';
	}
		std::cout << std::endl;
		std::cin.get();
}

TileType Grid::getTileAt(int x, int y) {
	return (TileType)board.at(x).at(y);
}
