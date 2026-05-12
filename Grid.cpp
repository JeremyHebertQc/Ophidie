/*====================================
Auteurs : Jeremy Hebert, Vincent Gagnon et Felix-Antoine Lacroix
Projet : Ophidie
====================================*/

#include "Grid.h"
#include "utils.h"
#include "const.h"
#include "Menu.h"

#include <cassert>

// Private method
sf::Vector2i Grid::transformGridToPixels(sf::Vector2i cellLocation, sf::Vector2f offsetInAbsolutePixels) const
{
	return sf::Vector2i{cellLocation.x * GRID_CELL_SIZE, cellLocation.y * GRID_CELL_SIZE} + getGridOffset();
}

// Constructor
Grid::Grid(sf::RenderWindow* window, Settings* settings)
{
	_window = window;
	_settings = settings;

	_width = settings->getWidth();
	_height = settings->getHeight();
	_numberOfTraps = _numberOfEggs = 0;
	_hasRandomWalls = false;

	for (int i = 0; i < GRID_PATH.size(); i++)
	{
		if (!_texture.loadFromFile(GRID_PATH.at(i)))
			sendFatalError(FileNotOpened);

		_textures.push_back(new sf::Texture(_texture));

		_renderers.push_back(new sf::Sprite(*_textures.back()));
	}
}

// Destructor
Grid::~Grid()
{
	_width = _height = _numberOfTraps = _numberOfEggs = 0;
	_hasRandomWalls = false;
	for (sf::Texture *t : _textures)
		delete t;
	for (sf::Sprite *s : _renderers)
		delete s;
	_textures.clear();
	_renderers.clear();
	_board.clear();
}

// Getters
TileType Grid::getTileAt(sf::Vector2i coords) const
{
	return (TileType)_board.at(coords.x).at(coords.y);
}

sf::Vector2i Grid::getGridOffset() const
{
	sf::Vector2i boardSize = {(_height + BORDER_SIZE) * GRID_CELL_SIZE, (_width + BORDER_SIZE) * GRID_CELL_SIZE};
	return {((int)_window->getSize().x - boardSize.x) / 2, ((int)_window->getSize().y - boardSize.y) / 2};
}

// Setters
void Grid::setTileAt(sf::Vector2i coords, TileType tile)
{
	_board.at(coords.x).at(coords.y) = tile;
}

void Grid::setWidth(int width)
{
	assert(width > 0);

	_width = width;
}

void Grid::setHeight(int height)
{
	assert(height > 0);

	_height = height;
}

void Grid::setScale(int width, int height)
{
	setWidth(width);
	setHeight(height);
}

// Make map
void Grid::createMap()
{
	setScale(_settings->getWidth(), _settings->getHeight());

	_board.reserve(_width + AIR_SPACE);
	for (std::vector<int>& i : _board)
		i.reserve(_height + AIR_SPACE);

	configureGamemode();
	configureDifficulty();

	placeBorder();
	placeAir();
	bodyLocationReserve();

	if (_hasRandomWalls)
		placeTraps();
	for (int i = 0; i < _numberOfEggs; i++)
		placeEgg();

	for (int i = 0; i < AIR_SPACE; i++)
		_board.at(AIR_SPACE_LOCATION[i]).at(FIRST_ROW_LOCATION) = Air;
}

void Grid::configureGamemode()
{
	switch (_settings->getMode())
	{
	case Normal:
	case Survival:
		break;

	case DeathTrap:
	case SurviveHell:
		_hasRandomWalls = true;
		break;

	default:
		sendFatalError(InvalidGamemode);
	}
}

void Grid::configureDifficulty()
{
	switch (_settings->getDifficulty())
	{
	case Baby:
		_numberOfEggs = 3;
		_numberOfTraps = 0.01 * _width * _height;
		break;

	case Ez:
		_numberOfEggs = 3;
		_numberOfTraps = 0.03 * _width * _height;
		break;

	case MediumRare:
		_numberOfEggs = 2;
		_numberOfTraps = 0.05 * _width * _height;
		break;

	case Medium:
		_numberOfEggs = 1;
		_numberOfTraps = 0.07 * _width * _height;
		break;

	case Hard:
		_numberOfEggs = 1;
		_numberOfTraps = 0.08 * _width * _height;
		break;

	case Harder:
		_numberOfEggs = 1;
		_numberOfTraps = 0.10 * _width * _height;
		break;

	case TooHard:
		_numberOfEggs = 1;
		_numberOfTraps = 0.12 * _width * _height;
		break;

	case Hardcore:
		_numberOfEggs = 1;
		_numberOfTraps = 0.12 * _width * _height;
		break;

	default:
		sendFatalError(InvalidDifficulty);
	}
}

void Grid::placeBorder()
{
	for (int i = 0; i < _height + BORDER_SIZE; i++)
	{
		_board.emplace_back();
		for (int j = 0; j < _width + BORDER_SIZE; j++)
			_board.at(i).push_back(Trap);
	}
}

void Grid::placeAir()
{
	for (int i = 1; i <= _height; i++)
	{
		//_board.emplace_back();
		for (int j = 1; j <= _width; j++)
			setTileAt(sf::Vector2i(i, j), Air);
	}
}

void Grid::bodyLocationReserve() //NOTE: On prend plus long que le serpent afin de laisser le temps au joueurs de bouger au demarrage du jeu.
{
	for (int i = 1; i < BODY_SIZE_RESERVE; i++)
		_board.at(i).at(FIRST_ROW_LOCATION) = Body;
}

void Grid::placeTraps()
{
	while (_numberOfTraps > 0)
	{
		int randX = getRandIntInRange(START_GRID_LOCATION, _width);
		int randY = getRandIntInRange(START_GRID_LOCATION, _height);

		if (_board.at(randY).at(randX) == Air)
		{
			_board.at(randY).at(randX) = Trap;
			_numberOfTraps--;
		}
	}
}

void Grid::placeEgg()
{
	bool eggPlaced = true;
	while (eggPlaced)
	{
		int randX = getRandIntInRange(START_GRID_LOCATION, _width);
		int randY = getRandIntInRange(START_GRID_LOCATION, _height);

		if (_board.at(randY).at(randX) == Air)
		{
			_board.at(randY).at(randX) = TileType(getRandIntInRange(WhiteEgg, RedEgg));
			eggPlaced = false;
		}
	}
}

// Methods
void Grid::renderGrid() const
{
	for (int i = 0; i < _width + BORDER_SIZE; i++)
		for (int j = 0; j < _height + BORDER_SIZE; j++)
		{
			auto pos = transformGridToPixels({j,i});
			_renderers.at(Air)->setPosition(pos.x,pos.y);
			_window->draw(*_renderers.at(Air));

			if (_board.at(j).at(i) != Air && _board.at(j).at(i) != Body)
			{
				_renderers.at(_board.at(j).at(i))->setPosition(pos.x, pos.y);
				_window->draw(*_renderers.at(_board.at(j).at(i)));
			}

		}
}

void Grid::updateSnakePosition(std::vector<sf::Vector2i> bodyParts)
{
	for (int i = 0; i <= _width; i++)
		for (int j = 0; j <= _height; j++)
			if (_board.at(j).at(i) == Body)
				_board.at(j).at(i) = Air;

	for (auto body_part : bodyParts)
		_board.at(body_part.x).at(body_part.y) = Body;
}