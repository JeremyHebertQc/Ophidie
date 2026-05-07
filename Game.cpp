#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Menu.h"
#include "Game.h"

// Constructor
Game::Game()
{
    _window.create(sf::VideoMode::getDesktopMode(), "Ophidie");
    _window.setActive(true);
    _window.setFramerateLimit(60);
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
        if(!menu.loadHomeMenu(_window))
            _window.close();
    }
}

void Game::showEndScreen() {

}

void Game::savePlayerScore(Player player, GameMode mode) {

}
