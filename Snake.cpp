#include "Snake.h"

#include "utils.h"

#include <SFML/Graphics.hpp>
#include <cassert>

// Constructor
Snake::Snake(sf::RenderWindow* window, sf::Vector2i offset)
{
	_window = window;

	if (!(_textureHead.loadFromFile(GAME_DIR + "snake/head.png") && _textureBody.loadFromFile(GAME_DIR + "snake/body.png") && _textureCurve.loadFromFile(GAME_DIR + "snake/body_curve.png") && _textureTail.loadFromFile(GAME_DIR + "snake/tail.png")))
		sendFatalError(FileNotOpened);

	setOffset(offset);

	_snake.push_back(sf::Sprite(_textureHead));
	setHeadDirection(Right);
	_snake.back().setOrigin(getSnakeTextureCenterPosition());
	_snake.back().setPosition(getSnakeTextureSizeX() * 3.f + getSnakeTextureCenterPositionX() + _offset.x, getSnakeTextureSizeY() + static_cast<float>(getSnakeTextureCenterPositionY()) + _offset.y);
	_snake.back().setRotation(_headDirection * static_cast<float>(CONVERT_DEGREE));

	_snake.push_back(sf::Sprite(_textureBody));
	_snake.back().setOrigin(getSnakeTextureCenterPosition());
	_snake.back().setPosition(getSnakeTextureSizeX() * 2.f + getSnakeTextureCenterPositionX() + _offset.x, getSnakeTextureSizeY() + static_cast<float>(getSnakeTextureCenterPositionY()) + _offset.y);
	_snake.back().setRotation(_headDirection * static_cast<float>(CONVERT_DEGREE));

	_snake.push_back(sf::Sprite(_textureTail));
	_snake.back().setOrigin(getSnakeTextureCenterPosition());
	_snake.back().setPosition(static_cast<float>(getSnakeTextureSizeX() + getSnakeTextureCenterPositionX()) + _offset.x, getSnakeTextureSizeY() + static_cast<float>(getSnakeTextureCenterPositionY()) + _offset.y);
	//_snake.back().setPosition(static_cast<float>(getSnakeTextureCenterPositionX()) + _offset.x, static_cast<float>(getSnakeTextureCenterPositionY()) + _offset.y);
	_snake.back().setRotation(_headDirection * static_cast<float>(CONVERT_DEGREE));

	setLiving(true);
	setBannedDirection(Left);
	updateLastDirection();
}

// Destructor
Snake::~Snake()
{
	_snake.clear();
	_headDirection = Up;
}

// Getters
int Snake::getHeadCoordX()
{
	return (_snake.front().getPosition().x - _snake.front().getTexture()->getSize().x / 2 - _offset.x) / _snake.front().getTexture()->getSize().x;
}

int Snake::getHeadCoordY()
{
	return (_snake.front().getPosition().y - _snake.front().getTexture()->getSize().y / 2 - _offset.y) / _snake.front().getTexture()->getSize().y;
}

Direction Snake::getBannedDirection()
{
	return _bannedDirection;
}

size_t Snake::getSnakeSize()
{
	return _snake.size();
}

Direction Snake::getHeadDirection() const
{
	return _headDirection;
}

sf::Vector2i Snake::getHeadCoord()
{
	return sf::Vector2i((_snake.front().getPosition().x - _snake.front().getTexture()->getSize().x / 2 - _offset.x) / _snake.front().getTexture()->getSize().x, (_snake.front().getPosition().y - _snake.front().getTexture()->getSize().y / 2 - _offset.y) / _snake.front().getTexture()->getSize().y);
}

std::vector<sf::Vector2i> Snake::getSnakeCoords()
{
	std::vector<sf::Vector2i> liste;

	for (size_t i = 0; i < _snake.size(); i++)
		liste.push_back(sf::Vector2i((_snake.at(i).getPosition().x - _snake.at(i).getTexture()->getSize().x / 2 - _offset.x) / _snake.at(i).getTexture()->getSize().x, (_snake.at(i).getPosition().y - _snake.at(i).getTexture()->getSize().y / 2 - _offset.y) / _snake.at(i).getTexture()->getSize().y));

	return liste;
}

sf::Vector2i Snake::getDestinationCoord()
{
	switch (_headDirection)
	{
	case Up:
		return sf::Vector2i(getHeadCoordX(), getHeadCoordY() - 1);
		break;
	case Right:
		return sf::Vector2i(getHeadCoordX() + 1, getHeadCoordY());
		break;
	case Down:
		return sf::Vector2i(getHeadCoordX(), getHeadCoordY() + 1);
		break;
	case Left:
		return sf::Vector2i(getHeadCoordX() - 1, getHeadCoordY());
		break;
	default:
		sendFatalError(InvalidDirection);
	}
}

int Snake::getSnakeTextureSizeX() const
{
	return _snake.back().getTexture()->getSize().x;
}

int Snake::getSnakeTextureSizeY() const
{
	return _snake.back().getTexture()->getSize().y;
}

int Snake::getSnakeTextureCenterPositionX() const
{
	return getSnakeTextureSizeX() / 2;
}

int Snake::getSnakeTextureCenterPositionY() const
{
	return getSnakeTextureSizeY() / 2;
}

sf::Vector2f Snake::getSnakeTextureCenterPosition() const
{
	return sf::Vector2f(getSnakeTextureCenterPositionX(), getSnakeTextureCenterPositionY());
}

// Setters
void Snake::setHeadDirection(Direction direction)
{
	assert(direction <= 4 && direction >= -1);

	if (direction != _bannedDirection)
		if (direction == -1) // DELETE: Before hand in
			_headDirection = Left;
		else if (direction == 4)
			_headDirection = Up;
		else // DELETE: BEfore hand in
			_headDirection = direction;
}

void Snake::setBannedDirection(Direction direction)
{
	assert(direction >= Up && direction <= Left);

	_bannedDirection = direction;
}

void Snake::setLiving(bool isAlive)
{
	_isAlive = isAlive;
}

void Snake::setOffset(sf::Vector2i offset)
{
	_offset = offset;
}

// Methods
bool Snake::isLiving() const
{
	return _isAlive;
}

void Snake::drawSnake()
{
	for (size_t i = 0; i < _snake.size(); i++)
		_window->draw(_snake.at(i));
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

void Snake::moveHurting()
{
	hurtSnake();
	moveHead();

	updateLastDirection();
}

void Snake::addNeck()
{
	if (_lastDirection != _headDirection)
	{
		_snake.insert(_snake.begin() + 1, sf::Sprite(_textureCurve));
		_snake.at(1).setOrigin(_snake.at(1).getTexture()->getSize().x / 2, (int)(_snake.at(1).getTexture()->getSize().y) / 2);
		_snake.at(1).setPosition(_snake.front().getPosition().x, _snake.front().getPosition().y);

		if (_headDirection - _lastDirection == 1 || _headDirection - _lastDirection == -3)
			_snake.at(1).setRotation(_headDirection * CONVERT_DEGREE);
		else if (_headDirection == Up || _headDirection == Down)
			_snake.at(1).setRotation(((_headDirection + 1) % 4) * -CONVERT_DEGREE);
		else
			_snake.at(1).setRotation(((_headDirection - 1) % 4) * -CONVERT_DEGREE);
	}
	else
	{
		_snake.insert(_snake.begin() + 1, sf::Sprite(_textureBody));
		_snake.at(1).setOrigin(_snake.at(1).getTexture()->getSize().x / 2, _snake.at(1).getTexture()->getSize().y / 2);
		_snake.at(1).setPosition(_snake.front().getPosition().x, _snake.front().getPosition().y);
		_snake.at(1).setRotation(_lastDirection * CONVERT_DEGREE);
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
	_snake.front().setRotation(_headDirection * CONVERT_DEGREE);

	switch (_headDirection)
	{
	case Up:
		_snake.front().setPosition(_snake.front().getPosition().x, _snake.front().getPosition().y - _snake.front().getTexture()->getSize().y);
		setBannedDirection(Down);
		break;
	case Right:
		_snake.front().setPosition(_snake.front().getPosition().x + _snake.front().getTexture()->getSize().x, _snake.front().getPosition().y);
		setBannedDirection(Left);
		break;
	case Down:
		_snake.front().setPosition(_snake.front().getPosition().x, _snake.front().getPosition().y + _snake.front().getTexture()->getSize().y);
		setBannedDirection(Up);
		break;
	case Left:
		_snake.front().setPosition(_snake.front().getPosition().x - _snake.front().getTexture()->getSize().x, _snake.front().getPosition().y);
		setBannedDirection(Right);
		break;
	default:
		sendFatalError(InvalidDirection);
	}
}

void Snake::moveTail()
{
	_snake.back().setPosition(_snake.at(_snake.size() - 2).getPosition());

	if (_snake.back().getRotation() != _snake.at(_snake.size() - 2).getRotation())
		if (_snake.back().getRotation() == _snake.at(_snake.size() - 2).getRotation() - CONVERT_DEGREE || _snake.back().getRotation() == _snake.at(_snake.size() - 2).getRotation() + 270)
			_snake.back().setRotation(_snake.at(_snake.size() - 2).getRotation());
		else
			_snake.back().setRotation(_snake.back().getRotation() - CONVERT_DEGREE);

	_snake.erase(_snake.end() - 2);
}

void Snake::hurtSnake()
{
	addNeck();

	_snake.back().setPosition(_snake.at(_snake.size() - 5).getPosition());

	if (_snake.back().getRotation() != _snake.at(_snake.size() - 5).getRotation())
		if (_snake.back().getRotation() == _snake.at(_snake.size() - 5).getRotation() - CONVERT_DEGREE || _snake.back().getRotation() == _snake.at(_snake.size() - 5).getRotation() + 270)
			_snake.back().setRotation(_snake.at(_snake.size() - 5).getRotation());
		else
			_snake.back().setRotation(_snake.back().getRotation() - CONVERT_DEGREE);

	for (int i = 5; i >= 2; i--)
		_snake.erase(_snake.end() - i);
}