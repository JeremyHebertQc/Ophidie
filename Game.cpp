#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector> //TODO: Transformer les boutons en vecteur.

#include "Button.h"
#include "Menu.h"
#include "Game.h"

void play()
{
    sf::RenderWindow window(sf::VideoMode(1024, 600), "Menu");
    window.setFramerateLimit(60);
    window.hasFocus();
    Menu menu;
        menu.addButton(0, debugAction, "Bouton 0", sf::Color::White, sf::Color::Cyan, sf::Vector2f(100, 50), sf::Vector2f(100, 100));
    Button /*button1(0, debugAction, "Bouton 0", sf::Color::White, sf::Color::Cyan, sf::Vector2f(100, 50), sf::Vector2f(100, 100)),*/
        button2(1, debugAction, "Bouton 1", sf::Color::Yellow, sf::Color::Green, sf::Vector2f(100, 50), sf::Vector2f(100, 200)),
        button3(2, debugAction, "Bouton 2", sf::Color::Yellow, sf::Color::Green, sf::Vector2f(100, 50), sf::Vector2f(100, 300)),
        button4(3, debugAction, "Bouton 3", sf::Color::Yellow, sf::Color::Green, sf::Vector2f(100, 50), sf::Vector2f(100, 400)),
        button5(4, debugAction, "Bouton 4", sf::Color::Yellow, sf::Color::Green, sf::Vector2f(100, 50), sf::Vector2f(100, 500));

    while (true)
    {
        window.clear();
        menu.getButtons()[0].draw(window, 0); // button1.draw(window, 0);
        button2.draw(window, 1);
        button3.draw(window, 2);
        button4.draw(window, 3);
        button5.draw(window, 4);
        window.display();

        static sf::Cursor cursorArrow;
        if (!cursorArrow.loadFromSystem(sf::Cursor::Arrow))
            printf("ERROR: Cursor doesn't load!\n"); //TODO: Transformer en SFML

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed:
            case sf::Event::MouseButtonReleased:
                if (/*button1.*/menu.getButtons()[0].isButtonPressed(event, window));
                else if (button2.isButtonPressed(event, window));
                else if (button3.isButtonPressed(event, window));
                else if (button4.isButtonPressed(event, window));
                else if (button5.isButtonPressed(event, window));
                break;

            case sf::Event::MouseMoved:
                window.setMouseCursor(cursorArrow);
                if (/*button1.*/menu.getButtons()[0].isButtonHover(event, window));
                else if (button2.isButtonHover(event, window));
                else if (button3.isButtonHover(event, window));
                else if (button4.isButtonHover(event, window));
                else if (button5.isButtonHover(event, window));
                break;

            default:
                break;
            }
        }
    }
}
