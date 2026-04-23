/*====================================
Auteur : Jérémy Hébert, Vincent Gagnon et Félix-Antoine Lacroix
Projet : Ophidie
====================================*/

#pragma once
#include <string>

constexpr int NUMBER_OF_SCORES = 10;

enum GameMode {
	NORMAL,
	SURVIVAL,
	DEATH_TRAP,
	SURVIVE_HELL,

	total // leave last
};

const std::string SCOREBOARD_FILEPATH = "res/scoreboard/";