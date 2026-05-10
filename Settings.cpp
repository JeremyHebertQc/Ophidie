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
    _difficulty = BABY;
    _mode = NORMAL;
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
void Settings::setSound(const float volSound)
{
    assert(volSound >= MIN_VOLUME && volSound <= MAX_VOLUME);

    _volSound = volSound;
}

void Settings::setMusic(const float volMusic)
{
    assert(volMusic >= MIN_VOLUME && volMusic <= MAX_VOLUME);

    _volMusic = volMusic;
}

void Settings::setMenuVolume(const float volMenu)
{
	assert(volMenu >= MIN_VOLUME && volMenu <= MAX_VOLUME);

	_volMenu = volMenu;
}

void Settings::setWidth(const unsigned int gridW)
{
    assert(gridW >= MIN_GRID_SIZE && gridW <= MAX_GRID_SIZE);

    _gridW = gridW;
}

void Settings::setHeight(const unsigned int gridH)
{
    assert(gridH >= MIN_GRID_SIZE && gridH <= MAX_GRID_SIZE);

    _gridH = gridH;
}

void Settings::setDifficulty(const Difficulty difficulty)
{
    assert(difficulty >= BABY && difficulty <= HARDCORE);

    _difficulty = difficulty;
}

void Settings::setMode(const GameMode mode)
{
    assert(mode >= NORMAL && mode <= SURVIVE_HELL);

    _mode = mode;
}

void Settings::setFullScr(const bool fullScr)
{
    _fullScr = fullScr;
}

void Settings::setArrow(const bool usingArrow)
{
    _usingArrowKeys = usingArrow;
}

void Settings::setDeaf(const bool deafMode)
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
void Settings::setGrid(const int gridW, const int gridH)
{
    setWidth(gridW);
    setHeight(gridH);
}

void Settings::setVolume(const float volSound, const float volMusic, const float volMenu)
{
    setSound(volSound);
    setMusic(volMusic);
	setMenuVolume(volMenu);
}

void Settings::saveVolume(const int volSound, const int volMusic, const int volMenu)
{
	_savedSound = volSound;
	_savedMusic = volMusic;
	_savedMenu = volMenu;
}

// Lecture/Écriture de la BD
void Settings::readFile()
{
    std::fstream input;

    openFile(input, SETTINGS_FILE_NAME, true);

    json settings = json::parse(input);

    setDifficulty(Difficulty(settings["Difficulty"]));
    setMode(GameMode(settings["Mode"]));
    setGrid(settings["Width"], settings["Height"]);
    
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

void Settings::saveSettings()
{
    std::fstream output;

    json settings;

    settings["Difficulty"] = _difficulty;
    settings["Mode"] = _mode;
    settings["Width"] = _gridW;
    settings["Height"] = _gridH;
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

    openFile(output, SETTINGS_FILE_NAME, false);

    output << std::setw(2) << settings;

    closeFile(output);
}