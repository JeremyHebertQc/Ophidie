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
        menu.addButton(0, debugAction, "Bouton 0", bigButton, sf::Vector2f(0.5, 0.3), sf::Vector2f(250, 100));
        menu.addButton(1, debugAction, "Bouton 1", bigButton, sf::Vector2f(0.5, 0.3), sf::Vector2f(250, 210));
        menu.addButton(2, debugAction, "Bouton 2", bigButton, sf::Vector2f(0.5, 0.3), sf::Vector2f(250, 320));
        menu.addButton(3, debugAction, "Bouton 3", bigButton, sf::Vector2f(0.5, 0.3), sf::Vector2f(250, 430));
        menu.addButton(4, debugAction, "Bouton 4", bigButton, sf::Vector2f(0.5, 0.3), sf::Vector2f(250, 540));

    while (_window.isOpen())
    {
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
