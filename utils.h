#pragma once
/*====================================
Auteur : Jérémy Hébert
Projet : Ophidie
====================================*/

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <string>
#include <fstream>
#include <string>

#ifndef WIN32
#include <cassert>
#endif

void sleepMs(int ms);

// Gestion des fichiers
void openFile(std::fstream& stream, const std::string& fileName, bool read);
void closeFile(std::fstream& stream);
void isFileOpen(std::fstream& stream);
int getRandIntInRange(int min, int max);

// Error management
void sendFatalError(ErrorCode code);
void sendError(ErrorCode code);
const std::string getErrorCodeName(ErrorCode code);