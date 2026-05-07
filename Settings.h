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
	unsigned int getWidth() const;
	unsigned int getHeight() const;
	Difficulty getDifficulty() const;
	GameMode getMode() const;
	bool getFullScr() const;
	bool getArrow() const;
	bool getDeaf() const;

	// Setteurs
	void setSound(unsigned int volSound);
	void setMusic(unsigned int volMusic);
	void setWidth(unsigned int gridW);
	void setHeight(unsigned int gridH);
	void setDifficulty(Difficulty difficulty);
	void setMode(GameMode mode);
	void setFullScr(bool fullScr);
	void setArrow(bool usingArrow);
	void setDeaf(bool deafMode);

	// Setteurs complexes
	void setGrid(int gridW, int gridH);
	void setVolume(int volSound, int volMusic);

	// Lecture/�criture de la BD
	void readFile();
	void saveSettings();
};