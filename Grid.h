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
	sf::Vector2i transformGridToPixels(sf::Vector2i cellLocation, sf::Vector2f offsetInAbsolutePixels = {0, 0}) const; // Private method

	mutable sf::Texture _textures[3];
	mutable sf::Sprite _renderers[3];

	int _width, _height, _numberOfEggs, _numberOfTraps;
	bool _hasRandomWalls;
	std::vector<std::vector<int>> _board;

	// Use extern declarations
	Settings* _settings;
	sf::RenderWindow* _window;

public:
	// Constructor
	Grid(sf::RenderWindow* window, Settings* settings);

	// Destructor
	~Grid();

	// Getters
	TileType getTileAt(sf::Vector2i coords) const;
	sf::Vector2i getGridOffset() const;

	// Setters
	void setTileAt(sf::Vector2i coords, TileType tile);
	void setWidth(const int width);
	void setHeight(const int height);
	void setScale(const int width, const int height);

	// Make map
	void createMap();
	void configureGamemode();
	void configureDifficulty();
	void placeBorder();
	void placeAir();
	void bodyLocationReserve();
	void placeTraps();
	void placeEggs(int eggsToPlace);

	// Methods
	void updateSnakePosition(std::vector<sf::Vector2i> bodyParts);
	void renderGrid() const;
};