#pragma once

#include <SFML/Graphics.hpp>

class Game
{
private:
	sf::RenderWindow _window;

public:
	// Constructor
	Game();

	// Destructor
	~Game();

	// Method
	void play();
};

