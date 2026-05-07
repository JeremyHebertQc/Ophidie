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
	sf::Vector2i _headPosition;

	Direction _headDirection;
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
	sf::Vector2i getHeadPosition();
	std::vector<sf::Vector2i> getSnakeCoords();

	void setHeadDirection(Direction direction);
	void setHeadPosition(int x, int y);
	void setBannedDirection(Direction direction);

	void drawSnake(sf::RenderWindow& window);

	void moveForward(bool eggEaten);
	void eatingEgg();
};
