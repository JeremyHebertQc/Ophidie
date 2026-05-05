#include "Grid.h"
#include <iostream>
#include "utils.h"

const std::string Grid::filePaths[] =
{
	IMAGES_FILEPATH + "Background.png",
	IMAGES_FILEPATH + "Traps.png",
	IMAGES_FILEPATH + "egg1.png",
	IMAGES_FILEPATH + "snake1.png"
};

Grid::Grid() {
	width = height = numberOfTraps = numberOfEggs = 0;
	hasRandomWalls = false;

	for (int i = 0; i < 4; i++) {
		if (!textures[i].loadFromFile(filePaths[i])) exit(1);
		renderers[i].setTexture(textures[i]);
	}

}

Grid::~Grid() {
	width = height = numberOfTraps = numberOfEggs = 0;
	hasRandomWalls = false;
}

void Grid::placeEggs(int eggsToPlace) {
	int randX;
	int randY;

	while (eggsToPlace > 0) {
		randX = getRandIntInRange(0,width - 1);
		randY = getRandIntInRange(0,height - 1);

		if (board.at(randY).at(randX) == air) {
			board.at(randY).at(randX) = egg;
			eggsToPlace--;
		}
	}
}

void Grid::renderGrid(sf::RenderWindow* window) {
	//masterAirTile.setScale(100,100);

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {

			auto pos = transformGridToPixels({j,i}, window);
			renderers[air].setPosition(pos.x,pos.y);
			window->draw(renderers[air]);

			if (board.at(i).at(j) != 0) {
				renderers[board.at(i).at(j)].setPosition(pos.x,pos.y);
				window->draw(renderers[board.at(i).at(j)]);
			}

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

	board.at(0).at(0) = TileType::body;
	board.at(0).at(1) = TileType::body;
	board.at(0).at(2) = TileType::body;

	if (hasRandomWalls) {
		int randX, randY = 0;
		while (numberOfTraps > 0) {
			randX = getRandIntInRange(0,width - 1);
			randY = getRandIntInRange(0,height - 1);

			if (board.at(randY).at(randX) == air) {
				board.at(randY).at(randX) = trap;
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
		//std::cin.get();
}

TileType Grid::getTileAt(int x, int y) {
	return (TileType)board.at(x).at(y);
}

sf::Vector2i Grid::transformGridToPixels(sf::Vector2i cellLocation, sf::RenderWindow *window, sf::Vector2f offsetInAbsolutePixels) {
	//sf::Vector2u size = {window->getSize().x / WINDOW_WIDTH, window->getSize().y / WINDOW_HEIGHT};

	sf::Vector2i boardSize = {width * GRID_CELL_SIZE, height * GRID_CELL_SIZE};

	sf::Vector2i scaled = {cellLocation.x * GRID_CELL_SIZE, cellLocation.y * GRID_CELL_SIZE};
	sf::Vector2i center = {WINDOW_WIDTH/2 - boardSize.x / 2, WINDOW_HEIGHT/2 - boardSize.y / 2};

	//return window->mapCoordsToPixel(offseted);
	return scaled + center;

}