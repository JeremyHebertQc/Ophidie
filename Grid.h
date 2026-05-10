#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "const.h"
#include "Settings.h"
#include "Snake.h"

enum TileType
{
	air,
	trap,
	egg,
	body
};

class Grid
{
private:
	sf::Vector2i transformGridToPixels(sf::Vector2i cellLocation, sf::RenderWindow *window, sf::Vector2f offsetInAbsolutePixels = {0, 0}) const; // Private method

	static const std::string _filePaths[3];

	mutable sf::Texture _textures[3];
	mutable sf::Sprite _renderers[3];

	int _width, _height, _numberOfEggs, _numberOfTraps;
	bool _hasRandomWalls;
	std::vector<std::vector<int>> _board;

public:
	// Constructor
	Grid();

	// Destructor
	~Grid();

	// Getters
	TileType getTileAt(sf::Vector2i coords) const;
	sf::Vector2i getGridOffset(sf::RenderWindow *window) const;

	// Setters
	void setTileAt(sf::Vector2i coords, TileType tile);
	void setWidth(const int width);
	void setHeight(const int height);
	void setScale(const int width, const int height);

	// Make map
	void createMap(int width, int heigth, GameMode mode, Difficulty difficulty);
	void configureGamemode(GameMode mode);
	void configureDifficulty(Difficulty difficulty);
	void placeBorder();
	void placeAir();
	void bodyLocationReserve();
	void placeTraps();
	void placeEggs(int eggsToPlace);

	// Methods
	void updateSnakePosition(std::vector<sf::Vector2i> bodyParts);
	void renderGrid(sf::RenderWindow* window) const;
};