#pragma once

#include <SFML/Graphics.hpp>
#include "Settings.h"

class Game
{
private:
	sf::RenderWindow _window;
  Settings _settings;

public:
	// Constructor
	Game();

	// Destructor
	~Game();

	// Method
	void play();
	//void showEndScreen();
	//void savePlayerScore(Player player, GameMode mode);
	bool startGame();
};

