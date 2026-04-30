/*====================================
Auteur : Jérémy Hébert, Vincent Gagnon et Félix-Antoine Lacroix
Projet : Ophidie
====================================*/

#pragma once
#include <string>

// Constantes pour le scoreboard
constexpr int NUMBER_OF_SCORES = 10;

// Constantes pour l'ensemble de la solution
enum GameMode
{
	NORMAL,
	SURVIVAL,
	DEATH_TRAP,
	SURVIVE_HELL,

	GameModeTotal // Leave last
};

enum Action
{
	Resume,
	Exit,
	Save,
	ExitSave,

	ActionTotal // Leave last
};


enum ErrorCode
{
	SUCCESS,
	FILE_NOT_OPENED
};

// Constantes pour les settings
const int MIN_VOLUME = 0,
	MAX_VOLUME = 100,
	MIN_GRID_SIZE = 10,
	MAX_GRID_SIZE = 100;

// Chemins
const std::string SCOREBOARD_FILEPATH = "data/scoreboards/";
const std::string SETTINGS_FILE_NAME = "data/settings.json";