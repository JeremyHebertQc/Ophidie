#pragma once

#include <SFML/Graphics.hpp>

class Game
{
private:
	sf::RenderWindow _window;

public:
	// Constructeur
	Game();

	// Destructeur
	~Game();

	// Méthodes
	void play();
};

