/*====================================
Auteur : Vincent Gagnon
Projet : Ophidie
====================================*/

#pragma once

#include "const.h"

#include <SFML/Graphics.hpp>
#include <vector>

class Snake
{
  private:
	std::vector<sf::Sprite> _snake;

	sf::Texture _textureHead;
	sf::Texture _textureBody;
	sf::Texture _textureTail;
	sf::Texture _textureCurve;

	Direction _headDirection;
	Direction _lastDirection;
	Direction _bannedDirection;

  public:
	Snake();

	~Snake();

	int getHeadCoordX();
	int getHeadCoordY();
	Direction getBannedDirection();
	size_t getSnakeSize();
	Direction getHeadDirection();
	sf::Vector2i getHeadCoord();
	std::vector<sf::Vector2i> getSnakeCoords();
	sf::Vector2i getDestinationCoord();

	void setHeadDirection(Direction direction);
	void setBannedDirection(Direction direction);

	void drawSnake(sf::RenderWindow& window);

	void moveForward(bool eggEaten);
	void addNeck();
	void updateLastDirection();
	void moveBody();
	void moveHead();
	void moveTail();
};
