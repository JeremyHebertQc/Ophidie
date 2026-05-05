/*====================================
Auteurs : J�r�my H�bert, Vincent Gagnon et F�lix-Antoine Lacroix
Projet : Ophidie
====================================*/

#include <iostream>

#include "const.h"
#include "Snake.h"

int main() {
	Snake snake;

	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		

		window.clear();
		snake.drawSnake(window);
		window.display();
	}

    return SUCCESS;
}