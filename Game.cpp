#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Menu.h"
#include "Game.h"
#include "Grid.h"
#include "Settings.h"

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
	Settings settings;

    while (_window.isOpen())
    {
        if(!menu.loadHomeMenu(_window))
            _window.close();
		else
			startGame();
    }
}

bool Game::startGame()
{
	Grid map;
	map.createMap(10, 10, SURVIVAL, BABY);

    sf::Clock moveCooldown;

	Snake snake(map.getGridOffset());

	bool eat = false;
	bool chain = true;

	
	while (snake.isLiving())
	{
		sf::Event event;
		while (_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				_window.close();
			else if (event.type == sf::Event::KeyReleased)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::A:
					snake.setHeadDirection(LEFT);
					break;
				case sf::Keyboard::D:
					snake.setHeadDirection(RIGHT);
					break;
				case sf::Keyboard::W:
					snake.setHeadDirection(UP);
					break;
				case sf::Keyboard::S:
					snake.setHeadDirection(DOWN);
					break;
				case sf::Keyboard::Space:
					if (eat)
						eat = false;
					else
						eat = true;
					break;
				case sf::Keyboard::Enter:
					if (chain)
						chain = false;
					else
						chain = true;
					break;
				}
			}
		}

		if (moveCooldown.getElapsedTime().asMilliseconds() > 250)
		{
			
			if (map.getTileAt(snake.getDestinationCoord()) == 2)
				snake.setLiving(false);
			moveCooldown.restart();

			snake.moveForward(eat);
		}

		_window.clear();
		map.renderGrid(&_window);
		snake.drawSnake(_window);
		_window.display();
	}

	return false;
}

//void Game::showEndScreen() {
//
//}
//
//void Game::savePlayerScore(Player player, GameMode mode) {
//
//}
