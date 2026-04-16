#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
//#include <nlohmann/json.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    sf::Texture texture;
    if (!texture.loadFromFile("/home/qh4cker/CLionProjects/Ophidia/res/Images/snake.png"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);

    sf::Font myFont;
    myFont.loadFromFile("/home/qh4cker/CLionProjects/Ophidia/res/Fonts/PressStart2P.ttf");
    sf::Text text("Hello SFML", myFont, 50);

    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clear screen
        window.clear();
        // Draw the sprite
        sprite.setScale({0.5,0.5});
        window.draw(sprite);
        // Draw the string
        window.draw(text);
        // Update the window
        window.display();

        sf::Music mySound;
        mySound.openFromFile("/home/qh4cker/CLionProjects/Ophidia/res/Audio/GC-BANNER.wav");
        mySound.setLoop(true);
        mySound.setVolume(50);
        mySound.play();

    }





    std::cin.get();
    //system("pause>NUL");
    return 0;
}