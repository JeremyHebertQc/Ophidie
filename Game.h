#pragma once

#include <SFML/Graphics.hpp>
#include "Scoreboard.h"
#include "Grid.h"

class Game
{
private:
	sf::RenderWindow _window;

  Scoreboard _scoreboard;
  Grid _grid;

public:
	// Constructor
	Game();

	// Destructor
	~Game();

	// Method
	void play();
};

