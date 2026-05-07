#include "Snake.h"

#include <SFML/Graphics.hpp>
#include <cassert>

Snake::Snake()
{
	_textureHead.loadFromFile("assets/images/snake_head.png");
	_textureBody.loadFromFile("assets/images/snake_body.png");
	_textureCurve.loadFromFile("assets/images/body_curve.png");
	_textureTail.loadFromFile("assets/images/snake_tail.png");

	_snake.push_back(sf::Sprite(_textureHead));
	_snake.back().setOrigin(_snake.back().getTexture()->getSize().x / 2, _snake.back().getTexture()->getSize().y / 2);
	_snake.back().setPosition(64 + 16, 16);
	_snake.back().setRotation(_headDirection * 90);

	setHeadDirection(RIGHT);

	_snake.push_back(sf::Sprite(_textureBody));
	_snake.back().setOrigin(_snake.back().getTexture()->getSize().x / 2, _snake.back().getTexture()->getSize().y / 2);
	_snake.back().setPosition(32 + 16, 16);
	_snake.back().setRotation(_headDirection * 90);

	_snake.push_back(sf::Sprite(_textureTail));
	_snake.back().setOrigin(_snake.back().getTexture()->getSize().x / 2, _snake.back().getTexture()->getSize().y / 2);
	_snake.back().setPosition(16, 16);
	_snake.back().setRotation(_headDirection * 90);

	setBannedDirection(LEFT);
}

Snake::~Snake()
{
	_snake.clear();
	_headDirection = UP;
	_headPosition.x = _headPosition.y = 0;
}

int Snake::getHeadCoordX()
{
	return (_snake.front().getPosition().x - _snake.front().getTexture()->getSize().x / 2) / _snake.front().getTexture()->getSize().x;
}

int Snake::getHeadCoordY()
{
	return (_snake.front().getPosition().y - _snake.front().getTexture()->getSize().y / 2) / _snake.front().getTexture()->getSize().y;
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

sf::Vector2i Snake::getHeadCoord()
{
	return sf::Vector2i((_snake.front().getPosition().x - _snake.front().getTexture()->getSize().x / 2) / _snake.front().getTexture()->getSize().x, (_snake.front().getPosition().y - _snake.front().getTexture()->getSize().y / 2) / _snake.front().getTexture()->getSize().y);
}

sf::Vector2i Snake::getHeadPosition()
{
	return _headPosition;
}

std::vector<sf::Vector2i> Snake::getSnakeCoords()
{
	std::vector<sf::Vector2i> liste;

	for (size_t i = 0; i < _snake.size(); i++)
	{
		liste.push_back(sf::Vector2i((_snake.at(i).getPosition().x - _snake.at(i).getTexture()->getSize().x / 2) / _snake.at(i).getTexture()->getSize().x, (_snake.at(i).getPosition().y - _snake.at(i).getTexture()->getSize().y / 2) / _snake.at(i).getTexture()->getSize().y));
	}

	return liste;
}

void Snake::setHeadDirection(Direction direction)
{
	assert(direction >= UP && direction <= LEFT);

	_headDirection = direction;
	_snake.front().setRotation(_headDirection * 90);
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
	for (size_t i = 0; i < _snake.size(); i++)
	{
		window.draw(_snake.at(i));
	}
}

void Snake::moveForward(bool eggEaten)
{
	if (eggEaten)
	{
		eatingEgg();

		switch (_headDirection)
		{
		case UP:
			_snake.front().setPosition(_snake.front().getPosition().x, _snake.front().getPosition().y - _snake.front().getTexture()->getSize().y);
			break;
		case RIGHT:
			_snake.front().setPosition(_snake.front().getPosition().x + _snake.front().getTexture()->getSize().x, _snake.front().getPosition().y);
			break;
		case DOWN:
			_snake.front().setPosition(_snake.front().getPosition().x, _snake.front().getPosition().y + _snake.front().getTexture()->getSize().y);
			break;
		case LEFT:
			setHeadPosition(getHeadCoordX() - 1, getHeadCoordY());
			break;
		default:
			printf("ERROR EXEPTION NOT ADLED");
			system("pause>NUL");
			exit(NOT_VALID_DIRECTION);
			// TODO mettre en sfml
		}
	}
	else
	{
		switch (_headDirection)
		{
		case UP:
			setHeadPosition(getHeadCoordX(), getHeadCoordY() + 1);

			for (size_t i = 0; i < _snake.size(); i++)
			{
				_snake.at(i).setPosition(_snake.at(i).getPosition().x, _snake.at(i).getPosition().y + 32);
			}
			break;
		case RIGHT:
			setHeadPosition(getHeadCoordX() + 1, getHeadCoordY());

			for (size_t i = 0; i < _snake.size(); i++)
			{
				_snake.at(i).setPosition(_snake.at(i).getPosition().x + 32, _snake.at(i).getPosition().y);
			}
			break;
		case DOWN:
			setHeadPosition(getHeadCoordX(), getHeadCoordY() - 1);

			for (size_t i = 0; i < _snake.size(); i++)
			{
				_snake.at(i).setPosition(_snake.at(i).getPosition().x, _snake.at(i).getPosition().y - 32);
			}
			break;
		case LEFT:
			setHeadPosition(getHeadCoordX() - 1, getHeadCoordY());

			for (size_t i = 0; i < _snake.size(); i++)
			{
				_snake.at(i).setPosition(_snake.at(i).getPosition().x - 32, _snake.at(i).getPosition().y);
			}
			break;
		default:
			printf("ERROR EXEPTION NOT ADLED");
			system("pause>NUL");
			exit(NOT_VALID_DIRECTION);
			// TODO mettre en sfml
		}
	}
}

void Snake::eatingEgg()
{
	_snake.insert(_snake.begin() + 1, sf::Sprite(_textureBody));
	_snake.at(1).setOrigin(_snake.at(1).getTexture()->getSize().x / 2, _snake.at(1).getTexture()->getSize().y / 2);
	_snake.at(1).setPosition(32 * getHeadCoordX() + 16, 32 * getHeadCoordY() + 16);
	_snake.at(1).setRotation(_headDirection * 90);
}

// TODO: movement & update head position, getdestinationcoord