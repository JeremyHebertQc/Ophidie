#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Menu.h"
#include "Game.h"

Game::Game()
{
    // VideoMode mode, const String& title, Uint32 style = Style::Default, const ContextSettings& settings = ContextSettings()
    _window.create(sf::VideoMode::getDesktopMode(), "Ophidie");
    _window.setActive(true);
    _window.setFramerateLimit(60);
}

Game::~Game()
{
    _window.close();
}

// Methode
void Game::play()
{
    Menu menu;
    while (_window.isOpen())
    {
        if(!menu.loadHomeMenu(_window))
            _window.close();
    }
}
