#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

#include "Button.h"
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
        menu.addButton(0, startGame, "Play", bigButton, sf::Vector2f(0.5, 0.3), sf::Vector2f(500, 100));
        menu.addButton(1, openHTP, "How to play?", bigButton, sf::Vector2f(0.5, 0.3), sf::Vector2f(500, 250));
        menu.addButton(2, openScoreboard, "Scoreboard", bigButton, sf::Vector2f(0.5, 0.3), sf::Vector2f(500, 400));
        menu.addButton(3, debugAction, "Settings", littleButton, sf::Vector2f(0.5, 0.3), sf::Vector2f(500, 550));
        menu.addButton(4, closeOphidie, "Quit", littleButton, sf::Vector2f(0.5, 0.3), sf::Vector2f(750, 550));

    while (_window.isOpen())
    {
        _window.clear();
        menu.drawButtons(_window);
        _window.display();

        static sf::Cursor cursorArrow;
        if (!cursorArrow.loadFromSystem(sf::Cursor::Arrow))
            printf("ERROR: Cursor doesn't load!\n"); //TODO: Transformer en SFML

        sf::Event event;
        while (_window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                _window.close();
                break;

            case sf::Event::Resized:


            case sf::Event::MouseButtonPressed:
            case sf::Event::MouseButtonReleased:
                //int btnid = menu.isButtonPressed(event, window);
                if (menu.isButtonPressed(event, _window) == -1);
                {
                    menu.drawButtons(_window);
                    _window.display();
                }
                break;

            case sf::Event::MouseMoved:
                _window.setMouseCursor(cursorArrow);
                //int btnid2 = menu.isButtonHover(event, window);
                if (menu.isButtonHover(event, _window) == -1);
                break;

            default:
                break;
            }
        }
    }
}
