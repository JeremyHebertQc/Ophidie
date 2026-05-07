/*====================================
Auteur : Vincent Gagnon
Projet : Ophidie
====================================*/

#pragma once

#include <string>

#include "const.h"

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

class Settings
{
private:
	unsigned int _volSound,
		_volMusic,
		_volMenu,
		_gridW,
		_gridH;

	Difficulty _difficulty;
	
	GameMode _mode;

	bool _fullScr,
		_usingArrowKeys,
		_deafMode;

public:
	// Constructeur
	Settings();

	// Destructeur
	~Settings();

	// Getteurs
	unsigned int getSound() const;
	unsigned int getMusic() const;
	int getMenu() const;
	unsigned int getWidth() const;
	unsigned int getHeight() const;
	Difficulty getDifficulty() const;
	GameMode getMode() const;
	bool getFullScr() const;
	bool getArrow() const;
	bool getDeaf() const;

	// Setteurs
	void setSound(const unsigned int volSound);
	void setMusic(const unsigned int volMusic);
	void setMenuVolume(const unsigned int volMenu);
	void setWidth(const unsigned int gridW);
	void setHeight(const unsigned int gridH);
	void setDifficulty(const Difficulty difficulty);
	void setMode(const GameMode mode);
	void setFullScr(const bool fullScr);
	void setArrow(const bool usingArrow);
	void setDeaf(const bool deafMode);

	// Setteurs complexes
	void setGrid(const int gridW, const int gridH);
	void setVolume(const int volSound, const int volMusic, const int volMenu);

	// Lecture/Écriture de la BD
	void readFile();
	void saveSettings();
};