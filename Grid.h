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

	void createMap(int width, int heigth, GameMode mode, Difficulty difficulty);


	TileType getTileAt(sf::Vector2i coords) const;
	void setTileAt(sf::Vector2i coords, TileType tile);

	void placeEggs(int eggsToPlace);
	void renderGrid(sf::RenderWindow* window) const;

	sf::Vector2i getGridOffset() const;
private:

	sf::Vector2i transformGridToPixels(sf::Vector2i cellLocation, sf::RenderWindow* window, sf::Vector2f offsetInAbsolutePixels = {0,0}) const;
	static const std::string filePaths[4];

	mutable sf::Texture textures[4];
	mutable sf::Sprite renderers[4];

	int width, height, numberOfEggs, numberOfTraps;
	bool hasRandomWalls;
	std::vector<std::vector<int>> board;
};