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

void Game::loadEndMenu(float score, GameMode mode, Difficulty difficulty)
{
	//_scoreboard.showScore(mode);
	if (_scoreboard.checkScore(score, mode, difficulty)) {
		if (bool userwantstosave = true) {
			std::string playerName;
			std::cin >> playerName;
			_scoreboard.addScore(score, playerName, mode, difficulty);
			_scoreboard.writeData();
			/*
			 * do fancy menus and stuff
			 *
			 */
		}
	}
}