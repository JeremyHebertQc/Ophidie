/*====================================
Auteurs : J�r�my H�bert, Vincent Gagnon et F�lix-Antoine Lacroix
Projet : Ophidie
====================================*/

#include <iostream>

#include "const.h"
#include "Grid.h"
#include "Scoreboard.h"

int main() {
	Scoreboard my;
	my.addScore(10, "q", NORMAL, BABY);
	my.writeData();
	/*
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML window");
	std::srand(time(NULL));
	std::cout << "Hello world!";
	Grid myGrid;
	myGrid.createMap(15,15, (GameMode)2, Difficulty(1));
	//std::cout << myGrid.getTileAt(2,2) << std::endl;

	std::cout << system("pwd");

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			// Close window: exit
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		myGrid.renderGrid(&window);


		window.display();

	}

	//system("pause>NUL");

	return SUCCESS;*/
}
