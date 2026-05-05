#include "Snake.h"

#include <SFML/Graphics.hpp>
#include <cassert>

Snake::Snake()
{ 
	setHeadPosition(2, 0);
	setHeadDirection(RIGHT);
	setBannedDirection(LEFT);
	
	_textureHead.loadFromFile("assets/images/snake_head.png");
	_textureBody.loadFromFile("assets/images/snake_body.png");
	_textureCurve.loadFromFile("assets/images/body_curve.png");
	_textureTail.loadFromFile("assets/images/snake_tail.png");

	_snake.push_back(sf::Sprite(_textureHead));
	_snake.at(0).setOrigin(16, 16);

	_snake.push_back(sf::Sprite(_textureBody));
	_snake.at(1).setOrigin(16, 16);
	_snake.at(1).setPosition(32 + 16, 16);
	_snake.at(1).setRotation(_headDirection * 90);

	_snake.push_back(sf::Sprite(_textureTail));
	_snake.at(2).setOrigin(16, 16);
	_snake.at(2).setPosition(16, 16);
	_snake.at(2).setRotation(_headDirection * 90);
}

Snake::~Snake()
{
	_snake.clear();
	_headDirection = UP;
	_headPosition.x = _headPosition.y = 0;
}

int Snake::getHeadPositionX()
{
	return (_snake.at(0).getPosition().x - 16) / 32;
}

int Snake::getHeadPositionY()
{
	return (_snake.at(0).getPosition().y - 16) / 32;
}

Direction Snake::getBannedDirection()
{
	return _bannedDirection;
}

size_t Snake::getSnakeSize()
{
	return _snake.size();
}

Direction Snake::getHeadDirection()
{
	return _headDirection;
}

void Snake::setHeadDirection(Direction direction)
{
	assert(direction >= UP && direction <= LEFT);

	_headDirection = direction;
}

void Snake::setHeadPosition(int x, int y)
{
	_headPosition.x = x * 32 + 16;
	_headPosition.y = y * 32 + 16;
}

void Snake::setBannedDirection(Direction direction)
{
	assert(direction >= UP && direction <= LEFT);

	_bannedDirection = direction;
}

void Snake::drawSnake(sf::RenderWindow& window)
{
	_snake.at(0).setPosition(_headPosition.x, _headPosition.y);
	_snake.at(0).setRotation(_headDirection * 90);
	
	for (size_t i = 0; i < _snake.size(); i++)
	{
		window.draw(_snake.at(i));
	}
	
}

void Snake::moveForward()
{
	switch (_headDirection)
	{
	case UP:
		setHeadPosition(getHeadPositionX(), getHeadPositionY() + 1);
		break;
	case RIGHT:
		setHeadPosition(getHeadPositionX() + 1, getHeadPositionY());
		break;
	case DOWN:
		setHeadPosition(getHeadPositionX(), getHeadPositionY() - 1);
		break;
	case LEFT:
		setHeadPosition(getHeadPositionX() - 1, getHeadPositionY());
		break;
	default:
		printf("ERROR EXEPTION NOT ADLED");
		system("pause>NUL");
		exit(NOT_VALID_DIRECTION);
		//TODO mettre en sfml
	}
}

void Snake::eatingEgg()
{
	_snake.insert(_snake.begin() + 1, sf::Sprite(_textureBody));
	_snake.at(1).setOrigin(16, 16);
	_snake.at(1).setPosition(32 * (getSnakeSize() - 2) +16,	16);
	_snake.at(1).setRotation(_headDirection * 90);
}
