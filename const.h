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

	total // Leave last
};

enum ErrorCode
{
	SUCCESS,
	FILE_NOT_OPENED,
	NOT_VALID_DIRECTION
};

// Constantes pour les settings
const int MIN_VOLUME = 0,
	MAX_VOLUME = 100,
	MIN_GRID_SIZE = 10,
	MAX_GRID_SIZE = 100;

// Chemins
const std::string SCOREBOARD_FILEPATH = "data/scoreboards/";
const std::string SETTINGS_FILE_NAME = "data/settings.json";

enum Direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT
};

// Constantes pour les menus et boutons
const std::string SOUND_PATH = "assets/soundEffects/";
const int TEXT_FONT_SIZE = 12;
const int EMPTY = 0;
const std::string LOGO_PATH = "assets/menu/logo.png";
const std::string WALLPAPER_PATH = "assets/menu/wallpaper.png";
const std::string MENU_ASSET_PATH = "assets/menu/";
const std::string BUTTON_SOUND_PATH = "assets/soundEffects/";
const std::string FONT_PATH = "assets/fonts/PressStart2P.ttf";
const std::string BUTTON_TEXTURE_PATH = "assets/buttons/";
const int FONT_SIZE = 20;