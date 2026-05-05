/*====================================
Auteur : Jérémy Hébert
Projet : Ophidie
====================================*/

#include <fstream>
#include <iostream>

#ifdef _WIN32
#include <cassert>
#include <iostream>
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "utils.h"
#include "const.h"

void sleepMs(int ms)
{
#ifdef _WIN32
	Sleep(ms);
#else
	usleep(ms * 1000);
#endif
}

// Gestion des fichiers
void openFile(std::fstream &stream, const std::string &fileName, bool read)
{
	if (read)
		stream.open(fileName, std::ios::in);
	else
		stream.open(fileName, std::ios::out);
	isFileOpen(stream);
}

void closeFile(std::fstream &stream)
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

		exit(FILE_NOT_OPENED);
	}
}

int getRandIntInRange(int min, int max) {
	return rand() % (max - min +1) + min;
}
