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
	//void showEndScreen();
	//void savePlayerScore(Player player, GameMode mode);
};

