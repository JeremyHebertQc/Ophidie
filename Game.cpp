#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

#include "Button.h"
#include "Menu.h"
#include "Game.h"

void Game::play()
{
    _window.setSize(sf::Vector2u(1024, 600));
    _window.setTitle("Menu");
    _window.setActive(true);
    _window.setFramerateLimit(60);
    _window.hasFocus();
    sf::Texture texture;
    texture.loadFromFile("assets/buttons/bigButton.png");
    Menu menu;
        menu.addButton(0, debugAction, "Bouton 0", texture, sf::Vector2f(0.5, 0.3), sf::Vector2f(250, 100));
        menu.addButton(1, debugAction, "Bouton 1", texture, sf::Vector2f(0.5, 0.3), sf::Vector2f(250, 210));
        menu.addButton(2, debugAction, "Bouton 2", texture, sf::Vector2f(0.5, 0.3), sf::Vector2f(250, 320));
        menu.addButton(3, debugAction, "Bouton 3", texture, sf::Vector2f(0.5, 0.3), sf::Vector2f(250, 430));
        menu.addButton(4, debugAction, "Bouton 4", texture, sf::Vector2f(0.5, 0.3), sf::Vector2f(250, 540));

    while (true)
    {
        for (int i = 0; i < menu.getButtons().size(); i++)
        {
            menu.drawButton(_window, i);
        }
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
                    for (int i = 0; i < menu.getButtons().size(); i++)
                    {
                        menu.drawButton(_window, i);
                    }
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
