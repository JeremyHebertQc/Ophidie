/*====================================
Auteur : Vincent Gagnon
Projet : Ophidie
====================================*/

#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <cassert>

#include "Settings.h"
#include "utils.h"
#include "const.h"

 using json = nlohmann::json;

// Constructeur
Settings::Settings()
{
	saveVolume(0, 0, 0);
    readFile();
}

// Destructeur
Settings::~Settings()
{
    _gridH = _gridW = _volSound = _volMusic = _fullScr = _usingArrowKeys = _deafMode = 0;
    _difficulty = Baby;
    _mode = Normal;
}

// Getteurs
float Settings::getSound() const
{
    return _volSound;
}

float Settings::getMusic() const
{
    return _volMusic;
}

float Settings::getMenu() const
{
	return _volMenu;
}

unsigned int Settings::getWidth() const
{
    return _gridW;
}

unsigned int Settings::getHeight() const
{
    return _gridH;
}

Difficulty Settings::getDifficulty() const
{
    return _difficulty;
}

GameMode Settings::getMode() const
{
    return _mode;
}

bool Settings::getFullScr() const
{
    return _fullScr;
}

bool Settings::getArrow() const
{
    return _usingArrowKeys;
}

bool Settings::getDeaf() const
{
    return _deafMode;
}

// Setteurs
void Settings::setSound(float volSound)
{
    assert(volSound >= MIN_VOLUME && volSound <= MAX_VOLUME);

    _volSound = volSound;
}

void Settings::setMusic(float volMusic)
{
    assert(volMusic >= MIN_VOLUME && volMusic <= MAX_VOLUME);

    _volMusic = volMusic;
}

void Settings::setMenuVolume(float volMenu)
{
	assert(volMenu >= MIN_VOLUME && volMenu <= MAX_VOLUME);

	_volMenu = volMenu;
}

void Settings::setWidth(unsigned int gridW)
{
    assert(gridW >= MIN_GRID_SIZE && gridW <= MAX_GRID_SIZE);

    _gridW = gridW;
}

void Settings::setHeight(unsigned int gridH)
{
    assert(gridH >= MIN_GRID_SIZE && gridH <= MAX_GRID_SIZE);

    _gridH = gridH;
}

void Settings::setDifficulty(Difficulty difficulty)
{
    assert(difficulty >= Baby && difficulty <= Hardcore);

    _difficulty = difficulty;
}

void Settings::setMode(GameMode mode)
{
    assert(mode >= Normal && mode <= SurviveHell);

    _mode = mode;
}

void Settings::setFullScr(bool fullScr)
{
    _fullScr = fullScr;
}

void Settings::setArrow(bool usingArrow)
{
    _usingArrowKeys = usingArrow;
}

void Settings::setDeaf(bool deafMode)
{
	if (deafMode)
	{
		_deafMode = deafMode;
		saveVolume(_volSound, _volMusic, _volMenu);
		setVolume(0, 0, 0);
	}
    else
    {
		_deafMode = deafMode;
	    setVolume(_savedSound, _savedMusic, _savedMenu);
    }
}

// Setteurs complexes
void Settings::setGrid(int gridW, int gridH)
{
    setWidth(gridW);
    setHeight(gridH);
}

void Settings::setVolume(float volSound, float volMusic, float volMenu)
{
    setSound(volSound);
    setMusic(volMusic);
	setMenuVolume(volMenu);
}

void Settings::saveVolume(int volSound, int volMusic, int volMenu)
{
	_savedSound = volSound;
	_savedMusic = volMusic;
	_savedMenu = volMenu;
}

// Lecture/Écriture de la BD
void Settings::readFile()
{
    std::fstream input;

    openFile(input, SETTINGS_PATH, true);

    json settings = json::parse(input);

    setDifficulty(Difficulty(settings["Difficulty"]));
	if (_difficulty / 4)
		setGrid(GRID_SMALL_SIZE, GRID_SMALL_SIZE);
	else
		setGrid(GRID_BIG_SIZE, GRID_BIG_SIZE);

    setMode(GameMode(settings["Mode"]));

    setDeaf(settings["Deaf"]);
    if (_deafMode)
    {
		saveVolume(settings["Sound"], settings["Music"], settings["Menu"]);
		setVolume(0, 0, 0);
    }
	else
	    setVolume(settings["Sound"], settings["Music"], settings["Menu"]);

    setFullScr(settings["FullScreen"]);
    setArrow(settings["Arrow"]);

    closeFile(input);
}

void Settings::saveSettings() const
{
    std::fstream output;

    json settings;

    settings["Difficulty"] = _difficulty;
    settings["Mode"] = _mode;
    settings["FullScreen"] = _fullScr;
    settings["Arrow"] = _usingArrowKeys;

    settings["Deaf"] = _deafMode;
	if (_deafMode)
	{
		settings["Sound"] = _savedSound;
		settings["Music"] = _savedMusic;
		settings["Menu"] = _savedMenu;
	}
    else
    {
		settings["Sound"] = _volSound;
		settings["Music"] = _volMusic;
		settings["Menu"] = _volMenu;
    }

    openFile(output, SETTINGS_PATH, false);

    output << std::setw(2) << settings;

    closeFile(output);
}