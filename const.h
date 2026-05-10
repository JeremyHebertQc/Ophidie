/*====================================
Auteur : Jérémy Hébert, Vincent Gagnon et Félix-Antoine Lacroix
Projet : Ophidie
====================================*/

#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

// === Enums ===
enum GameMode
{
	Normal,
	Survival,
	DeathTrap,
	SurviveHell,

	GameModeTotal // Leave last
};

enum Difficulty
{
	Baby,
	Ez,
	MediumRare,
	Medium,
	Hard,
	Harder,
	TooHard,
	Hardcore,

	DifficultyTotal
};

enum ErrorCode
{
	Success,
	FileNotOpened,
	InvalidDirection,
	InvalidDifficulty,
	InvalidGamemode,
	CursorFailedToLoad
};

enum ButtonStyle
{
	BigButton,
	MediumButton,
	LittleButton,
	YesButton,
	NoButton,

	nbStyle // Number of style
};

enum ButtonAction
{
	StartGame,
	CloseOphidie,
	OpenSettings,
	OpenHowToPlay,
	OpenScoreboard,
	GoToNormalSCR,
	GoToSurvivalSCR,
	GoToDeathTrapSCR,
	GoToSurviveHellSCR,
	CloseSubmenu,

	NbAction // Number of action
};

enum TextAlignment
{
	AlignmentRight,
	AlignmentLeft,
	AlignmentCenter
};

enum Direction
{
	Up,
	Right,
	Down,
	Left
};

// === Grid ===
const int MIN_GRID_SIZE = 10;
const int MAX_GRID_SIZE = 100;
const int GRID_OFFSET = 100;
const int GRID_CELL_SIZE = 32;
const int BORDER_SIZE = 2;
const int AIR_SPACE = 2;
const int AIR_SPACE_LOCATION[2] = {4, 5};
const int FIRST_ROW_LOCATION = 1;
const int BODY_SIZE_RESERVE = 6;
const int START_GRID_LOCATION = 1;

// === Audio ===
const int MIN_VOLUME = 0;
const int MAX_VOLUME = 100;
const std::string SOUND_PATH = "assets/soundEffects/";

// === Snake ===
const int CONVERT_DEGREE = 90;

// === Buttons / Menus ===
const int FONT_SIZE = 20;
const int BUTTON_TEXT_COLOR_R = 61;
const int BUTTON_TEXT_COLOR_G = 24;
const int BUTTON_TEXT_COLOR_B = 79;

// === Scoreboard ===
constexpr int NUMBER_OF_SCORES = 10;

// === Data filepaths ===
const std::string SETTINGS_PATH = "data/settings.json";
const std::string SCOREBOARD_DIR = "data/scoreboards/";

// === Assets filepaths ===
const std::string GAME_DIR = "assets/game/";
const std::string MENU_DIR = "assets/menu/";
const std::string SOUND_DIR = "assets/soundEffects/";
const std::string MUSIC_DIR = "assets/musics/";
const std::string BUTTON_DIR = "assets/buttons/";
const std::string LOGO_PATH = "assets/menu/logo.png";
const std::string WALLPAPER_PATH = MENU_DIR + "wallpaper.png";
const std::string FONT_PATH = "assets/fonts/PressStart2P.ttf";

const std::vector<std::string> GAMEMODES_PATH =
{
        SCOREBOARD_DIR + "Normal",
        SCOREBOARD_DIR + "Survival",
        SCOREBOARD_DIR + "DeathTrap",
        SCOREBOARD_DIR + "SurviveHell"
};

const std::vector<std::string> DIFFICULTY_PATH =
{
        "Baby.txt",
        "Ez.txt",
        "MediumRare.txt",
        "Medium.txt",
        "Hard.txt",
        "Harder.txt",
        "TooHard.txt",
        "Hardcore.txt"
};

const std::vector<std::string> GRID_PATH =
{
	GAME_DIR + "Background.png",
	GAME_DIR + "Traps.png",
	GAME_DIR + "egg.png"
};