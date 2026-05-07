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
	_snake.back().setPosition(320 + 16, 192+16);
	_snake.back().setRotation(_headDirection * 90);

	setHeadDirection(RIGHT);


	_snake.push_back(sf::Sprite(_textureBody));
	_snake.back().setOrigin(_snake.back().getTexture()->getSize().x / 2, _snake.back().getTexture()->getSize().y / 2);
	_snake.back().setPosition(288 + 16, 192 + 16);
	_snake.back().setRotation(_headDirection * 90);
	_snake.push_back(sf::Sprite(_textureBody));
	_snake.back().setOrigin(_snake.back().getTexture()->getSize().x / 2, _snake.back().getTexture()->getSize().y / 2);
	_snake.back().setPosition(256 + 16, 192 + 16);
	_snake.back().setRotation(_headDirection * 90);
	_snake.push_back(sf::Sprite(_textureBody));
	_snake.back().setOrigin(_snake.back().getTexture()->getSize().x / 2, _snake.back().getTexture()->getSize().y / 2);
	_snake.back().setPosition(224 + 16, 192 + 16);
	_snake.back().setRotation(_headDirection * 90);
	_snake.push_back(sf::Sprite(_textureBody));
	_snake.back().setOrigin(_snake.back().getTexture()->getSize().x / 2, _snake.back().getTexture()->getSize().y / 2);
	_snake.back().setPosition(192 + 16, 192 + 16);
	_snake.back().setRotation(_headDirection * 90);
	_snake.push_back(sf::Sprite(_textureBody));
	_snake.back().setOrigin(_snake.back().getTexture()->getSize().x / 2, _snake.back().getTexture()->getSize().y / 2);
	_snake.back().setPosition(160 + 16, 192 + 16);
	_snake.back().setRotation(_headDirection * 90);
	_snake.push_back(sf::Sprite(_textureBody));
	_snake.back().setOrigin(_snake.back().getTexture()->getSize().x / 2, _snake.back().getTexture()->getSize().y / 2);
	_snake.back().setPosition(128 + 16, 192 + 16);
	_snake.back().setRotation(_headDirection * 90);
	_snake.push_back(sf::Sprite(_textureBody));
	_snake.back().setOrigin(_snake.back().getTexture()->getSize().x / 2, _snake.back().getTexture()->getSize().y / 2);
	_snake.back().setPosition(96 + 16, 192 + 16);
	_snake.back().setRotation(_headDirection * 90);
	_snake.push_back(sf::Sprite(_textureBody));
	_snake.back().setOrigin(_snake.back().getTexture()->getSize().x / 2, _snake.back().getTexture()->getSize().y / 2);
	_snake.back().setPosition(64 + 16, 192 + 16);
	_snake.back().setRotation(_headDirection * 90);



	_snake.push_back(sf::Sprite(_textureBody));
	_snake.back().setOrigin(_snake.back().getTexture()->getSize().x / 2, _snake.back().getTexture()->getSize().y / 2);
	_snake.back().setPosition(32 + 16, 192+16);
	_snake.back().setRotation(_headDirection * 90);

	_snake.push_back(sf::Sprite(_textureTail));
	_snake.back().setOrigin(_snake.back().getTexture()->getSize().x / 2, _snake.back().getTexture()->getSize().y / 2);
	_snake.back().setPosition(16, 192+16);
	_snake.back().setRotation(_headDirection * 90);

	setBannedDirection(LEFT);
	updateLastDirection();
}

Snake::~Snake()
{
	_snake.clear();
	_headDirection = UP;
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

std::vector<sf::Vector2i> Snake::getSnakeCoords()
{
	std::vector<sf::Vector2i> liste;

	for (size_t i = 0; i < _snake.size(); i++)
		liste.push_back(sf::Vector2i((_snake.at(i).getPosition().x - _snake.at(i).getTexture()->getSize().x / 2) / _snake.at(i).getTexture()->getSize().x, (_snake.at(i).getPosition().y - _snake.at(i).getTexture()->getSize().y / 2) / _snake.at(i).getTexture()->getSize().y));

	return liste;
}

sf::Vector2i Snake::getDestinationCoord()
{
	switch (_headDirection)
	{
	case UP:
		return sf::Vector2i(getHeadCoordX(), getHeadCoordY() - 1);
		break;
	case RIGHT:
		return sf::Vector2i(getHeadCoordX() + 1, getHeadCoordY());
		break;
	case DOWN:
		return sf::Vector2i(getHeadCoordX(), getHeadCoordY() + 1);
		break;
	case LEFT:
		return sf::Vector2i(getHeadCoordX() - 1, getHeadCoordY());
		break;
	default:
		printf("ERROR EXEPTION NOT ADLED");
		system("pause>NUL");
		exit(NOT_VALID_DIRECTION);
	}

}

void Snake::setHeadDirection(Direction direction)
{
	assert(direction <= 4 && direction >= -1);

	if (direction == -1)
		_headDirection = LEFT;
	else if (direction == 4)
		_headDirection = UP;
	else
		_headDirection = direction;
}

void Snake::setBannedDirection(Direction direction)
{
	assert(direction >= UP && direction <= LEFT);

	_bannedDirection = direction;
}

void Snake::drawSnake(sf::RenderWindow& window)
{
	for (size_t i = 0; i < _snake.size(); i++)
		window.draw(_snake.at(i));
}

void Snake::moveForward(bool eggEaten)
{
	if (eggEaten)
		addNeck();
	else
		moveBody();
	moveHead();

	updateLastDirection();
}

void Snake::addNeck()
{
	if (_lastDirection != _headDirection)
	{
		_snake.insert(_snake.begin() + 1, sf::Sprite(_textureCurve));
		_snake.at(1).setOrigin(_snake.at(1).getTexture()->getSize().x / 2, std::trunc(_snake.at(1).getTexture()->getSize().y) / 2);
		_snake.at(1).setPosition(_snake.front().getPosition().x, _snake.front().getPosition().y);

		if (_headDirection - _lastDirection == 1 || _headDirection - _lastDirection == -3)
			_snake.at(1).setRotation(_headDirection * 90);
		else if (_headDirection == UP || _headDirection == DOWN)
			_snake.at(1).setRotation(((_headDirection + 1) % 4) * - 90);
		else
			_snake.at(1).setRotation(((_headDirection - 1) % 4) * - 90);
	}
	else
	{
		_snake.insert(_snake.begin() + 1, sf::Sprite(_textureBody));
		_snake.at(1).setOrigin(_snake.at(1).getTexture()->getSize().x / 2, _snake.at(1).getTexture()->getSize().y / 2);
		_snake.at(1).setPosition(_snake.front().getPosition().x, _snake.front().getPosition().y);
		_snake.at(1).setRotation(_lastDirection * 90);
	}
}

void Snake::updateLastDirection()
{
	_lastDirection = _headDirection;
}

void Snake::moveBody()
{
	addNeck();
	moveTail();
}

void Snake::moveHead()
{
	_snake.front().setRotation(_headDirection * 90);

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
		_snake.front().setPosition(_snake.front().getPosition().x - _snake.front().getTexture()->getSize().x, _snake.front().getPosition().y);
		break;
	default:
		printf("ERROR EXEPTION NOT ADLED");
		system("pause>NUL");
		exit(NOT_VALID_DIRECTION);
	}
}

void Snake::moveTail()
{
	_snake.back().setPosition(_snake.at(_snake.size() - 2).getPosition());

	if (_snake.back().getRotation() != _snake.at(_snake.size() - 2).getRotation())
		if (_snake.back().getRotation() == _snake.at(_snake.size() - 2).getRotation() - 90 || _snake.back().getRotation() == _snake.at(_snake.size() - 2).getRotation() + 270)
			_snake.back().setRotation(_snake.at(_snake.size() - 2).getRotation());
		else
			_snake.back().setRotation(_snake.back().getRotation() - 90);

	_snake.erase(_snake.end() - 2);
}
