#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Grid.h"
#include "Scoreboard.h"

class Game
{
public:
	Game();
	~Game();

	void loadMainMenu();

	void playGame(GameMode mode);
	Action loadPauseMenu();

	void loadSettingsMenu();
	void loadTutorialMenu();
	void loadScoreboardMenu();

	void loadEndMenu(float score, GameMode mode, Difficulty difficulty);
private:
	Menu _mainMenu;
	Menu _pauseMenu;
	Menu _settingMenu;
	Menu _tutorialMenu;
	Scoreboard _scoreboard;
	Grid _grid;
};




