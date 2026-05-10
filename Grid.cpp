#include "Grid.h"

#include "utils.h"
#include "Menu.h"

#include <cassert>

const std::string Grid::_filePaths[] =
{
        IMAGES_FILEPATH + "Background.png",
        IMAGES_FILEPATH + "Traps.png",
        IMAGES_FILEPATH + "egg.png"
};

// Private method
sf::Vector2i Grid::transformGridToPixels(sf::Vector2i cellLocation, sf::RenderWindow *window, sf::Vector2f offsetInAbsolutePixels) const
{
	return sf::Vector2i{cellLocation.x * GRID_CELL_SIZE, cellLocation.y * GRID_CELL_SIZE} + getGridOffset(window);
}

// Constructor
Grid::Grid() {
	_width = _height = _numberOfTraps = _numberOfEggs = 0;
	_hasRandomWalls = false;

	for (int i = 0; i < 3; i++)
	{
		if (!_textures[i].loadFromFile(_filePaths[i]))
			sendFatalError(FILE_NOT_OPENED);

		_renderers[i].setTexture(_textures[i]);
	}

}

// Destructor
Grid::~Grid()
{
	_width = _height = _numberOfTraps = _numberOfEggs = 0;
	_hasRandomWalls = false;

	_board.clear();
}

// Getters
TileType Grid::getTileAt(sf::Vector2i coords) const
{
	return (TileType)_board.at(coords.x).at(coords.y);
}

sf::Vector2i Grid::getGridOffset(sf::RenderWindow *window) const
{
	sf::Vector2i boardSize = {(_height + 2) * GRID_CELL_SIZE, (_width + 2) * GRID_CELL_SIZE};
	return {((int)window->getSize().x - boardSize.x) / 2, ((int)window->getSize().y - boardSize.y) / 2};
}

// Setters

void Grid::setTileAt(sf::Vector2i coords, TileType tile)
{
	_board.at(coords.x).at(coords.y) = tile;
}

void Grid::setWidth(const int width)
{
	assert(width > 0);

	_width = width;
}

void Grid::setHeight(const int height)
{
	assert(height > 0);

	_height = height;
}

void Grid::setScale(const int width, const int height)
{
	setWidth(width);
	setHeight(height);
}

// Make map
void Grid::createMap(int width, int heigth, GameMode mode, Difficulty difficulty)
{
	setScale(width, heigth);

	_board.reserve(_width + 2);
	for (std::vector<int>& temp : _board)
		temp.reserve(_height + 2);

	configureGamemode(mode);
	configureDifficulty(difficulty);

	placeBorder();
	placeAir();
	bodyLocationReserve();

	if (_hasRandomWalls)
		placeTraps();

	placeEggs(_numberOfEggs);

	_board.at(4).at(1) = air;
	_board.at(5).at(1) = air;
}

void Grid::configureGamemode(GameMode mode)
{
	switch (mode)
	{
	case NORMAL:
		break;
	case SURVIVAL:
		break;
	case DEATH_TRAP:
		_hasRandomWalls = true;
		break;
	case SURVIVE_HELL:
		_hasRandomWalls = true;
		break;
	default:
		sendFatalError(INVALID_GAMEMODE);
	}
}

void Grid::configureDifficulty(Difficulty difficulty)
{
	switch (difficulty)
	{
	case BABY:
		_numberOfEggs = 3;
		_numberOfTraps = 0;
		break;
	case EZ:
		_numberOfEggs = 3;
		_numberOfTraps = 0.05 * _width * _height;
		break;
	case MEDIUM_RARE:
		_numberOfEggs = 2;
		_numberOfTraps = 0.10 * _width * _height;
		break;
	case MEDIUM:
		_numberOfEggs = 1;
		_numberOfTraps = 0.15 * _width * _height;
		break;
	case HARD:
		_numberOfEggs = 1;
		_numberOfTraps = 0.20 * _width * _height;
		break;
	case HARDER:
		_numberOfEggs = 1;
		_numberOfTraps = 0.25 * _width * _height;
		break;
	case TOO_HARD:
		_numberOfEggs = 1;
		_numberOfTraps = 0.30 * _width * _height;
		break;
	case HARDCORE:
		_numberOfEggs = 1;
		_numberOfTraps = 0.35 * _width * _height;
		break;
	default:
		sendFatalError(INVALID_DIFFICULTY);
	}
}

void Grid::placeBorder()
{
	for (int i = 0; i < _height + 2; i++)
	{
		_board.emplace_back();
		for (int j = 0; j < _width + 2; j++)
			_board.at(i).push_back(trap);
	}
}

void Grid::placeAir()
{
	for (int i = 1; i < _height + 1; i++)
	{
		_board.emplace_back();
		for (int j = 1; j < _width + 1; j++)
			setTileAt(sf::Vector2i(i, j), air);
	}
}

void Grid::bodyLocationReserve()
{
	for (int i = 1; i < 6; i++)
		_board.at(i).at(1) = body;
}

void Grid::placeTraps()
{
	while (_numberOfTraps > 0)
	{
		int randX = getRandIntInRange(1, _width);
		int randY = getRandIntInRange(1, _height);

		if (_board.at(randY).at(randX) == air)
		{
			_board.at(randY).at(randX) = trap;
			_numberOfTraps--;
		}
	}
}

void Grid::placeEggs(int eggsToPlace)
{
	int randX;
	int randY;

	while (eggsToPlace > 0)
	{
		randX = getRandIntInRange(1, _width);
		randY = getRandIntInRange(1, _height);

		if (_board.at(randY).at(randX) == air)
		{
			_board.at(randY).at(randX) = egg;
			eggsToPlace--;
		}
	}
}

// Methods
void Grid::renderGrid(sf::RenderWindow* window) const
{
	//masterAirTile.setScale(100,100);

	for (int i = 0; i < _width + 2; i++)
		for (int j = 0; j < _height + 2; j++)
		{
			auto pos = transformGridToPixels({j,i}, window);
			_renderers[air].setPosition(pos.x,pos.y);
			window->draw(_renderers[air]);

			if (_board.at(j).at(i) != 0 && _board.at(j).at(i) != 3)
			{
				_renderers[_board.at(j).at(i)].setPosition(pos.x,pos.y);
				window->draw(_renderers[_board.at(j).at(i)]);
			}

		}
}

void Grid::updateSnakePosition(std::vector<sf::Vector2i> bodyParts)
{
	for (int i = 0; i < _width; i++)
		for (int j = 0; j < _height; j++)
			if (_board.at(j).at(i) == 3)
				_board.at(j).at(i) = 0;

	for (auto body_part : bodyParts)
		_board.at(body_part.x).at(body_part.y) = 3;
}