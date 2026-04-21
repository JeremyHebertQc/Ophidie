/*====================================
Auteur : Vincent Gagnon
Projet : Ophidie
====================================*/

#pragma once

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

enum Difficulty
{
	BABY,
	EZ,
	MEDIUM_RARE,
	MEDIUM,
	HARD,
	HARDER,
	TOO_HARD,
	HARDCORE
};

enum GameMode
{
	NORMAL,
	SURVIVAL,
	DEATH_TRAP,
	SURVIVE_HELL
};

class Settings
{
private:
	int _volSound,
		_volMusic,
		_gridW,
		_gridH;

	Difficulty _difficulty;
	
	GameMode _mode;

	bool _fullScr,
		_usingArrowKeys,
		_deafMode;

public:
	Settings() = delete;
	Settings(std::string fichier);

	int getSound();
	int getMusic();
	int getWidth();
	int getHeight();
	Difficulty getDifficulty();
	GameMode getMode();
	bool getFullScr();
	bool getArrow();
	bool getDeaf();
};

/*
TODO:
- volume musique
- volume sound
- grid size
- difficulty
	- Longueur snake
	- Vie
	- Vitesse
	- Egg point
- full screen mode
- Mapping des touches (wasd vs arrow key)

secondary:
- background
- skins
- music choice
- master volume
- Mapping des touches (full mapping)
- timer before starving

*/