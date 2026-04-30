/*====================================
Auteur : Vincent Gagnon
Projet : Ophidie
====================================*/

#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "const.h"

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

	int getHeadPositionX();
	int getHeadPositionY();
	Direction getBannedDirection();
	size_t getSnakeSize();
	Direction getHeadDirection();


	void setHeadDirection(Direction direction);
	void setHeadPosition(int x, int y);
	void setBannedDirection(Direction direction);

	void drawSnake(sf::RenderWindow& window);

	void moveForward();
	void eatingEgg();
};

