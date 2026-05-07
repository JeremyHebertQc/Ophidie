#pragma once
<<<<<<< felix-game
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
=======
>>>>>>> main

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

<<<<<<< felix-game
	void loadEndMenu(float score, GameMode mode, Difficulty difficulty);
private:
	Menu _mainMenu;
	Menu _pauseMenu;
	Menu _settingMenu;
	Menu _tutorialMenu;
	Scoreboard _scoreboard;
	Grid _grid;
=======
	// Method
	void play();
	//void showEndScreen();
	//void savePlayerScore(Player player, GameMode mode);
>>>>>>> main
};

