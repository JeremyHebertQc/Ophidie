#pragma once
#include <map>
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

	void loadSettingsMenu();
	void loadTutorialMenu();
	void loadScoreboardMenu();

	void loadEndMenu(float score, GameMode mode);
private:
	Menu _mainMenu;
	Menu _settingMenu;
	Menu _tutorialMenu;
	Scoreboard _scoreboard;
	Grid _grid;
};




