#pragma once
#include <SFML/Audio.hpp>
#include "Scoreboard.h"

class Game {
public:
	void showEndScreen();
	void savePlayerScore(Player player, GameMode mode);

};




