/*====================================
Auteur : Jérémy Hébert
Projet : Ophidie
====================================*/

#include <fstream>
#include <functional>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

#ifdef _WIN32
#include <cassert>
#include <iostream>
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "const.h"
#include "utils.h"

void sleepMs(int ms)
{
#ifdef _WIN32
	Sleep(ms);
#else
	usleep(ms * 1000);
#endif
}

// Gestion des fichiers
void openFile(std::fstream& stream, const std::string& fileName, bool read)
{
	if (read)
		stream.open(fileName, std::ios::in);
	else
		stream.open(fileName, std::ios::out);
	isFileOpen(stream);
}

void closeFile(std::fstream& stream)
{
	stream.close();
}

void isFileOpen(std::fstream& stream)
{
	if (!stream)
	{
		std::cerr << "Error: file could not be opened"; // TODO: Switch to SFML
#ifdef WIN32
		system("pause>NUL");
#else
		std::cin.get();
#endif

		sendFatalError(FILE_NOT_OPENED);
	}
}

int getRandIntInRange(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

void sendFatalError(const int errorCode)
{
	std::string errorCodeName = getErrorCodeName(errorCode);
	std::cerr << "ERROR : " << errorCodeName << " Check the wiki to find the problem.\nPress any key to close the game..."; //TODO: Transform in SFML if we have time

	system("pause>NUL");
	exit(errorCode);
}

void sendError(const int errorCode)
{
	std::string errorCodeName = getErrorCodeName(errorCode);
	std::cerr << "ERROR : " << errorCodeName << " Check the wiki to find the problem.\n"; //TODO: Transform in SFML if we have time
}

const std::string getErrorCodeName(const int errorCode)
{
	switch (errorCode)
	{
	case SUCCESS:
		return "SUCCESS - Success, no error found.";

	case FILE_NOT_OPENED:
		return "FILE_NOT_OPENED - A file could not be loaded.";

	case NOT_VALID_DIRECTION:
		return "NOT_VALID_DIRECTION - Head direction is invalid.";

	case INVALID_DIFFICULTY:
		return "INVALID_DIFFICULTY - The difficulty of the settings is incorrect.";

	case INVALID_GAMEMODE:
		return "INVALID_GAMEMODE - The gamemode of the settings is incorrect.";

	default:
		return "Undefined error.";
	}
}