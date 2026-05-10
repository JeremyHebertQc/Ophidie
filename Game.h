#pragma once

#include "Settings.h"

#include <SFML/Graphics.hpp>

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
	bool StartGame();
	// void showEndScreen();
	// void savePlayerScore(Player player, GameMode mode);
};