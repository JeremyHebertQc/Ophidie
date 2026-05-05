#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "const.h"
#include "Settings.h"
#include "Snake.h"

enum TileType {
	air = 0,
	trap = 1,
	egg = 2,
	body = 3
};


class Grid
{
public:
	Grid();
	~Grid();

	void createMap(int x, int y, GameMode mode, Difficulty difficulty);

	TileType getTileAt(int x, int y) const;
	void setTileAt(int x, int y, TileType tile);

	void placeEggs(int eggsToPlace);
	void renderGrid(sf::RenderWindow* window) const;

	sf::Vector2i getGridOffset() const;
private:

	sf::Vector2i transformGridToPixels(sf::Vector2i cellLocation, sf::RenderWindow* window, sf::Vector2f offsetInAbsolutePixels = {0,0}) const;
	static const std::string filePaths[4];

	sf::Texture textures[4];
	sf::Sprite renderers[4];

	int width, height, numberOfEggs, numberOfTraps;
	bool hasRandomWalls;
	std::vector<std::vector<int>> board;
};