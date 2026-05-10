#include "Grid.h"

#include "utils.h"

const std::string Grid::filePaths[] =
{
	IMAGES_FILEPATH + "Background.png",
	IMAGES_FILEPATH + "Traps.png",
	IMAGES_FILEPATH + "egg.png"
};

Grid::Grid() {
	width = height = numberOfTraps = numberOfEggs = 0;
	hasRandomWalls = false;

	for (int i = 0; i < 3; i++)
	{
		if (!textures[i].loadFromFile(filePaths[i]))
		{
			printf("ERROR: Texture doesn't load"); //TODO: Replace by SFML
			system("pause>NUL");
			exit(1);
		}
		renderers[i].setTexture(textures[i]);
	}

}

Grid::~Grid()
{
	width = height = numberOfTraps = numberOfEggs = 0;
	hasRandomWalls = false;

	board.clear();
}

void Grid::placeEggs(int eggsToPlace)
{
	int randX;
	int randY;

	while (eggsToPlace > 0)
	{
		randX = getRandIntInRange(1, width);
		randY = getRandIntInRange(1, height);

		if (board.at(randY).at(randX) == air)
		{
			board.at(randY).at(randX) = egg;
			eggsToPlace--;
		}
	}
}

void Grid::renderGrid(sf::RenderWindow* window) const
{
	//masterAirTile.setScale(100,100);

	for (int i = 0; i < width + 2; i++)
		for (int j = 0; j < height + 2; j++)
		{
			auto pos = transformGridToPixels({j,i}, window);
			renderers[air].setPosition(pos.x,pos.y);
			window->draw(renderers[air]);

			if (board.at(j).at(i) != 0 && board.at(j).at(i) != 3)
			{
				renderers[board.at(j).at(i)].setPosition(pos.x,pos.y);
				window->draw(renderers[board.at(j).at(i)]);
			}

		}
}

sf::Vector2i Grid::getGridOffset(sf::RenderWindow* window) const
{
	sf::Vector2i boardSize = {(height + 2) * GRID_CELL_SIZE, (width + 2) * GRID_CELL_SIZE};
	return {((int)window->getSize().x - boardSize.x) / 2, ((int)window->getSize().y - boardSize.y) / 2};
}

void Grid::createMap(int x, int heigth, GameMode mode, Difficulty difficulty)
{
	width = x;
	height = heigth;

	board.reserve(width + 2);
	for (std::vector<int>& temp : board)
		temp.reserve(height + 2);

	switch (mode)
	{
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
	switch (difficulty)
	{
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
		exit(1); //TODO: UPDATE
	}

	for (int i = 0; i < height + 2; i++)
	{
		board.emplace_back();
		for (int j = 0; j < width + 2; j++)
			board.at(i).push_back(trap);
	}

	for (int i = 1; i < height + 1; i++)
	{
		board.emplace_back();
		for (int j = 1; j < width + 1; j++)
			setTileAt(sf::Vector2i(i, j), air);
	}

	for (int i = 1; i < 6; i++)
		board.at(i).at(1) = body;

	if (hasRandomWalls)
	{
		int randX, randY = 0;
		while (numberOfTraps > 0)
		{
			randX = getRandIntInRange(1, width);
			randY = getRandIntInRange(1, height);

			if (board.at(randY).at(randX) == air)
			{
				board.at(randY).at(randX) = trap;
				numberOfTraps--;
			}
		}
	}


	placeEggs(numberOfEggs);

	board.at(4).at(1) = air;
	board.at(5).at(1) = air;
}

TileType Grid::getTileAt(sf::Vector2i coords) const
{
	return (TileType)board.at(coords.x).at(coords.y);
}

void Grid::setTileAt(sf::Vector2i coords, TileType tile)
{
	board.at(coords.x).at(coords.y) = tile;
}

void Grid::updateSnakePosition(std::vector<sf::Vector2i> bodyParts)
{
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
			if (board.at(j).at(i) == 3)
				board.at(j).at(i) = 0;

	for (auto body_part : bodyParts)
		board.at(body_part.x).at(body_part.y) = 3;
}

sf::Vector2i Grid::transformGridToPixels(sf::Vector2i cellLocation, sf::RenderWindow *window, sf::Vector2f offsetInAbsolutePixels) const
{
	return sf::Vector2i{cellLocation.x * GRID_CELL_SIZE, cellLocation.y * GRID_CELL_SIZE} + getGridOffset(window);
}