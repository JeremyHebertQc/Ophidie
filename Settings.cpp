#include <iostream>
#include <fstream>

#include "Settings.h"
#include "const.h"

using json = nlohmann::json;

Settings::Settings(std::string fichier)
{
    std::ifstream file("settings.json");
    if (!file.is_open())
    {
        std::cerr << "Error: file could not be opened";
        system("pause>NUL");
        exit(FILE_NOT_OPENED);
    }

    json settings = json::parse(file);

    _difficulty = Difficulty(settings["Difficulty"]);
    _mode = GameMode(settings["Mode"]);
    _gridW = settings["Width"];
    _gridH = settings["Height"];
    _volSound = settings["Sound"];
    _volMusic = settings["Music"];
    _fullScr = settings["FullScreen"];
    _usingArrowKeys = settings["Arrow"];
    _deafMode = settings["Deaf"];
}

int Settings::getSound()
{
    return _volSound;
}

int Settings::getMusic()
{
    return _volMusic;
}

int Settings::getWidth()
{
    return _gridW;
}

int Settings::getHeight()
{
    return _gridH;
}

Difficulty Settings::getDifficulty()
{
    return _difficulty;
}

GameMode Settings::getMode()
{
    return _mode;
}

bool Settings::getFullScr()
{
    return _fullScr;
}

bool Settings::getArrow()
{
    return _usingArrowKeys;
}

bool Settings::getDeaf()
{
    return _deafMode;
}



//int volSound,
//volMusic,
//gridW,
//gridH;
//
//Difficulty difficulty;
//
//GameMode mode;
//
//bool fullScr,
//usingArrowKey,
//deafMode;