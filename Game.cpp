#include "Game.h"

#include <iostream>

Game::Game()
{
}

Game::~Game()
{
}

void Game::loadMainMenu()
{
	bool exit = false;
	while (!exit) {
		/*
		 * handle input
		 * render
		 * call other util functions
		 */

	}
}

void Game::playGame(GameMode mode)
{
	bool notDead = true;
	float score = 0;
	while (notDead) {
		/*
		 * grid.play(); or smth
		 * handle the game loop here
		 *
		 */

		score += mode; // insane score scalling by difficulty

	}
	loadEndMenu(score, mode);
}

Action Game::loadPauseMenu() {
}

void Game::loadSettingsMenu()
{
}

void Game::loadTutorialMenu()
{
}

void Game::loadScoreboardMenu()
{
	_scoreboard.showMenu();
}

void Game::loadEndMenu(float score, GameMode mode)
{
	_scoreboard.showScore(mode);
	if (_scoreboard.checkScore(score, mode)) {
		if (bool userwantstosave = true) {
			std::string playerName;
			std::cin >> playerName;
			_scoreboard.addScore(score, playerName, mode);
			_scoreboard.writeData();
			/*
			 * do fancy menus and stuff
			 *
			 */
		}
	}
}