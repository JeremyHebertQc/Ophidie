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

	// Use extern declarations
	sf::RenderWindow* _window;

  public:
	// Constructors
	Snake() = delete;
	Snake(sf::RenderWindow* window, sf::Vector2i offset);

	// Destructor
	~Snake();

	// Getters
	int getHeadCoordX();
	int getHeadCoordY();
	Direction getBannedDirection();
	size_t getSnakeSize();
	Direction getHeadDirection() const;
	sf::Vector2i getHeadCoord();
	std::vector<sf::Vector2i> getSnakeCoords();
	sf::Vector2i getDestinationCoord();
	int getSnakeTextureSizeX() const;
	int getSnakeTextureSizeY() const;
	int getSnakeTextureCenterPositionX() const;
	int getSnakeTextureCenterPositionY() const;
	sf::Vector2f getSnakeTextureCenterPosition() const;

	// Setters
	void setHeadDirection(Direction direction);
	void setBannedDirection(Direction direction);
	void setLiving(bool isAlive);
	void setOffset(sf::Vector2i offset);

	// Methods
	bool isLiving() const;
	void drawSnake();

	void moveForward(bool eggEaten);
	void moveHurting();
	void addNeck();
	void updateLastDirection();
	void moveBody();
	void moveHead();
	void moveTail();
	void hurtSnake();

	void initializeSnake();
};