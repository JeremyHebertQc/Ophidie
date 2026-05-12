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
	CheckButton,
	EmptySquareButton,

	nbStyle // Number of style
};

enum ButtonAction
{
	StartGame,
	StartGameNow,
	CloseOphidie,
	OpenSettings,
	OpenHowToPlay,
	OpenScoreboard,
	GoToNormalSCR,
	GoToSurvivalSCR,
	GoToDeathTrapSCR,
	GoToSurviveHellSCR,
	GoToNext,
	GoToPrevious,
	CloseSubmenu,
	OpenHomeMenu,
	SaveSettings,
	DeafMode,

	Resume,
	QuitGame,

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

enum TileType
{
	air,
	trap,
	whiteEgg,
	brownEgg,
	blueEgg,
	greenEgg,
	redEgg,
	body
};

// === Grid ===
const int MIN_GRID_SIZE = 5;
const int MAX_GRID_SIZE = 32;
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
        "NORMAL",
        "SURVIVAL",
        "DEATH_TRAP",
        "SURVIVE_HELL"
};

const std::vector<std::string> DIFFICULTY_PATH =
{
        "BABY.txt",
        "EZ.txt",
        "MEDIUM_RARE.txt",
        "MEDIUM.txt",
        "HARD.txt",
        "HARDER.txt",
        "TOO_HARD.txt",
        "HARDCORE.txt"
};

const std::vector<std::string> GRID_PATH =
{
	GAME_DIR + "grid/Background.png",
	GAME_DIR + "grid/Traps.png",
	GAME_DIR + "eggs/whiteEgg.png",
	GAME_DIR + "eggs/brownEgg.png",
	GAME_DIR + "eggs/blueEgg.png",
	GAME_DIR + "eggs/greenEgg.png",
	GAME_DIR + "eggs/redEgg.png"
};

const int GRID_SMALL_SIZE = 8;
const int GRID_BIG_SIZE = 16;