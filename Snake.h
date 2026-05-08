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

	sf::Vector2i _offset;

	sf::Texture _textureHead;
	sf::Texture _textureBody;
	sf::Texture _textureTail;
	sf::Texture _textureCurve;

	Direction _headDirection;
	Direction _lastDirection;
	Direction _bannedDirection;

	bool _isAlive;

  public:
	Snake() = delete;
	Snake(sf::Vector2i offset);

	~Snake();

	int getHeadCoordX();
	int getHeadCoordY();
	Direction getBannedDirection();
	size_t getSnakeSize();
	Direction getHeadDirection();
	sf::Vector2i getHeadCoord();
	std::vector<sf::Vector2i> getSnakeCoords();
	sf::Vector2i getDestinationCoord();
	
	bool isLiving() const;

	void setHeadDirection(Direction direction);
	void setBannedDirection(Direction direction);
	void setLiving(bool isAlive);
	void setOffset(sf::Vector2i offset);

	void drawSnake(sf::RenderWindow& window);

	void moveForward(bool eggEaten);
	void addNeck();
	void updateLastDirection();
	void moveBody();
	void moveHead();
	void moveTail();
};
