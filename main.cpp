#include <iostream>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Button.h"

int main() {
    //sf::SoundBuffer mainMusicBuffer;
    //sf::Sound mainMusic;

    //if (!mainMusicBuffer.loadFromFile("assets/soundEffects/button.wav")) // On charge la musique du jeu
    //    return 1;

    //mainMusic.setBuffer(mainMusicBuffer); // On applique la musique chargée à l’objet de type "Sound"
    //mainMusic.setLoop(true); // La musique jouera en boucle
    //mainMusic.play(); // On fait jouer la musique

    std::cout << "Hello world!";

    sf::RenderWindow window(sf::VideoMode(1024, 600), "Menu");
    window.setFramerateLimit(60);
    window.hasFocus();

    Button button1(0, "Hello world !", sf::Color::White, sf::Color::Cyan, sf::Vector2f(300, 200), sf::Vector2f(100, 50)),
        button2(1, "Hello world x2 !", sf::Color::Yellow, sf::Color::Green, sf::Vector2f(150, 150), sf::Vector2f(100, 300));
    while (true)
    {

        window.clear();
        button1.draw(window, 0);
        button2.draw(window, 1);
        window.display();


        static sf::Cursor cursorArrow;
        if (!cursorArrow.loadFromSystem(sf::Cursor::Arrow))
            printf("ERREUR CHARGEMENT CURSEUR!\n");

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
                if (button1.isButtonPressed(event, window));
                else if (button2.isButtonPressed(event, window));
                break;

            case sf::Event::MouseMoved:
                window.setMouseCursor(cursorArrow);
                if (button1.isButtonHover(event, window));
                else if (button2.isButtonHover(event, window));
                break;

            default:
                break;
            }

            window.clear();
            button1.draw(window, 0);
            button2.draw(window, 1);
            window.display();
        }


            //if(button1.isButtonPressed())
            //    button1.updateButton(window);
    }

    return 0;
}