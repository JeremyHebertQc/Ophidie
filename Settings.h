#pragma once
/*====================================
Auteurs : Jeremy Hebert, Vincent Gagnon et Felix-Antoine Lacroix
Projet : Ophidie
====================================*/

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
	bool* getArrowPointer();
	bool getArrow() const;
	bool getDeaf() const;

	bool* getDeafPointer();

	// Setteurs
	void setSound(float volSound);
	void setMusic(float volMusic);
	void setMenuVolume(float volMenu);
	void setWidth(unsigned int gridW);
	void setHeight(unsigned int gridH);
	void setDifficulty(Difficulty difficulty);
	void setMode(GameMode mode);
	void setFullScr(bool fullScr);
	void setArrow(bool usingArrow);
	void setDeaf(bool deafMode);

	// Setteurs complexes
	void setGrid(int gridW, int gridH);
	void saveVolume(int volSound, int volMusic, int volMenu);
	void setVolume(float volSound, float volMusic, float volMenu);

	// Lecture/Écriture de la BD
	void readFile();
	void saveSettings() const;
};