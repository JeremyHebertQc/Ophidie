#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Menu.h"
#include "Game.h"

// Constructor
Game::Game()
{
<<<<<<< felix-game
}

Game::~Game()
{
}

void Game::loadMainMenu()
{
	bool exit = false;
	while (!exit) {
		/*
		 * handle input
		 * render
		 * call other util functions
		 */

	}
}


=======
    _window.create(sf::VideoMode::getDesktopMode(), "Ophidie");
    _window.setActive(true);
    _window.setFramerateLimit(60);

    sf::Image icon;
	if (icon.loadFromFile("assets/favicon/ophidie.png"))
	{
		_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	}
}
>>>>>>> main

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
        if(!menu.loadHomeMenu(_window))
            _window.close();
    }
}

<<<<<<< felix-game
void Game::loadEndMenu(float score, GameMode mode, Difficulty difficulty)
{
	//_scoreboard.showScore(mode);
	if (_scoreboard.checkScore(score, mode, difficulty)) {
		if (bool userwantstosave = true) {
			std::string playerName;
			std::cin >> playerName;
			_scoreboard.addScore(score, playerName, mode, difficulty);
			_scoreboard.writeData();
			/*
			 * do fancy menus and stuff
			 *
			 */
		}
	}
}
=======
//void Game::showEndScreen() {
//
//}
//
//void Game::savePlayerScore(Player player, GameMode mode) {
//
//}
>>>>>>> main
