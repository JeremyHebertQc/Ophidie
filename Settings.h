/*====================================
Auteur : Vincent Gagnon
Projet : Ophidie
====================================*/

#pragma once

#include <string>

#include "const.h"

class Settings
{
private:
	unsigned int _volSound,
		_volMusic,
		_volMenu,
		_gridW,
		_gridH,
		_savedSound,
		_savedMusic,
		_savedMenu;

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
	float getSound() const;
	float getMusic() const;
	float getMenu() const;
	unsigned int getWidth() const;
	unsigned int getHeight() const;
	Difficulty getDifficulty() const;
	GameMode getMode() const;
	bool getFullScr() const;
	bool getArrow() const;
	bool getDeaf() const;

	// Setteurs
	void setSound(const float volSound);
	void setMusic(const float volMusic);
	void setMenuVolume(const float volMenu);
	void setWidth(const unsigned int gridW);
	void setHeight(const unsigned int gridH);
	void setDifficulty(const Difficulty difficulty);
	void setMode(const GameMode mode);
	void setFullScr(const bool fullScr);
	void setArrow(const bool usingArrow);
	void setDeaf(const bool deafMode);

	// Setteurs complexes
	void setGrid(const int gridW, const int gridH);
	void saveVolume(const int volSound, const int volMusic, const int volMenu);
	void setVolume(const float volSound, const float volMusic, const float volMenu);

	// Lecture/Écriture de la BD
	void readFile();
	void saveSettings();
};