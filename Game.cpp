#include "Game.h"

#include "Grid.h"
#include "Menu.h"
#include "Settings.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Constructor
Game::Game()
{
	_window.create(sf::VideoMode::getDesktopMode(), "Ophidie");
	_window.setActive(true);
	_window.setFramerateLimit(60);

	sf::Image icon;
	if (icon.loadFromFile("assets/favicon/ophidie.png"))
	{
		_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	}
}

// Destructor
Game::~Game()
{
	_window.close();
}

// Method
void Game::play()
{
	Menu menu(_window);

	while (_window.isOpen())
	{
		if (!menu.loadHomeMenu(_window, _settings))
			_window.close();
		else
			startGame();
	}
}

bool Game::startGame()
{
	Grid map;
	map.createMap(_settings.getWidth(), _settings.getHeight(), _settings.getMode(), _settings.getDifficulty());

	sf::Clock moveCooldown;

	Snake snake(map.getGridOffset(&_window));

	bool eat = false;
	bool chain = true;

	while (snake.isLiving())
	{
		sf::Event event;
		while (_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				_window.close();
			case sf::Event::KeyPressed:
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Left:
					if (_settings.getArrow())
						snake.setHeadDirection(LEFT);
					break;
				case sf::Keyboard::A:
					if (!_settings.getArrow())
						snake.setHeadDirection(LEFT);
					break;
				case sf::Keyboard::Right:
					if (_settings.getArrow())
						snake.setHeadDirection(RIGHT);
					break;
				case sf::Keyboard::D:
					if (!_settings.getArrow())
						snake.setHeadDirection(RIGHT);
					break;
				case sf::Keyboard::Up:
					if (_settings.getArrow())
						snake.setHeadDirection(UP);
					break;
				case sf::Keyboard::W:
					if (!_settings.getArrow())
						snake.setHeadDirection(UP);
					break;
				case sf::Keyboard::Down:
					if (_settings.getArrow())
						snake.setHeadDirection(DOWN);
					break;
				case sf::Keyboard::S:
					if (!_settings.getArrow())
						snake.setHeadDirection(DOWN);
					break;
				case sf::Keyboard::Delete: //  quitout midgame
					snake.setLiving(false);
					break;
				}
				break;
			}
		}

		if (moveCooldown.getElapsedTime().asMilliseconds() > 500 / ((_settings.getDifficulty() % 4) + 1))
		{
			moveCooldown.restart();

			switch (map.getTileAt(snake.getDestinationCoord()))
			{
			case air:
				snake.moveForward(false);
				for (size_t i = 0; i < snake.getSnakeSize(); i++)
					map.setTileAt(snake.getSnakeCoords().at(i), body);
				break;
			case egg:
				snake.moveForward(true);
				for (size_t i = 0; i < snake.getSnakeSize(); i++)
					map.setTileAt(snake.getSnakeCoords().at(i), body);
				map.placeEggs(1);
				break;
			case body:
			case trap:
				snake.setLiving(false);
				break;
			}
		}

		_window.clear();
		map.renderGrid(&_window);
		snake.drawSnake(_window);
		_window.display();
	}

	return false;
}

// void Game::showEndScreen() {
//
// }
//
// void Game::savePlayerScore(Player player, GameMode mode) {
//
// }