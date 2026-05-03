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
    bool playing;
    do
    {
        playing = false;
        switch (menu.doButtonAction(_window, menu.loadHomeMenu(_window)))
        {
        case openHomeMenu:
        case NbAction + 1:
            playing = true;
            break;

        case NbAction + 2:
            printf("Goodbye!"); //TODO: Replace by SFML
            system("pause>NUL"); //TODO: Replace by SFML
            exit(0); //TODO: Replace by real exit code
            break;

        case OpenFile:
            printf("OpenFile"); //TODO: Replace by real action
            sf::sleep(sf::milliseconds(1000));
            break;

        case startGame:
            printf("Game will start soon..."); //TODO: Replace by real action
            system("pause>NUL");
            break;

        case -1:
        default:
            printf("ERROR"); //TODO: Replace by SFML
            system("pause>NUL"); //TODO: Replace by SFML
            exit(1); //TODO: Replace by real exit code
        }
    } while (playing == true);
}
