#pragma once
/*====================================
Auteurs : Jeremy Hebert, Vincent Gagnon et Felix-Antoine Lacroix
Projet : Ophidie
====================================*/

#include <vector>
#include <SFML/Graphics.hpp>
#include "const.h"
#include "Settings.h"
#include "Snake.h"

class Grid
{
private:
	sf::Vector2i transformGridToPixels(sf::Vector2i cellLocation, sf::Vector2f offsetInAbsolutePixels = {0, 0}) const; // Private method

	mutable std::vector<sf::Texture*> _textures;
	mutable std::vector<sf::Sprite*> _renderers;

	int _width, _height, _numberOfEggs, _numberOfTraps;
	bool _hasRandomWalls;
	std::vector<std::vector<int>> _board;
	sf::Texture _texture;
	sf::Sprite _renderer;

	// Pointer declarations
	Settings* _settings;
	sf::RenderWindow* _window;

public:
	// Constructor
	Grid() = delete;
	Grid(sf::RenderWindow* window, Settings* settings);

	// Destructor
	~Grid();

	// Getters
	TileType getTileAt(sf::Vector2i coords) const;
	sf::Vector2i getGridOffset() const;

	// Setters
	void setTileAt(sf::Vector2i coords, TileType tile);
	void setWidth(int width);
	void setHeight(int height);
	void setScale(int width, int height);

	// Make map
	void createMap();
	void configureGamemode();
	void configureDifficulty();
	void placeBorder();
	void placeAir();
	void bodyLocationReserve();
	void placeTraps();
	void placeEgg();

	// Methods
	void updateSnakePosition(std::vector<sf::Vector2i> bodyParts);
	void renderGrid() const;
};