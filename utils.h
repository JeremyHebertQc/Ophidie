/*====================================
Auteur : Jérémy Hébert
Projet : Ophidie
====================================*/

#pragma once

#include <algorithm>
#include <string>
#include <fstream>

#ifndef WIN32
#include <cassert>
#endif

void sleepMs(int ms);

// Gestion des fichiers
void openFile(std::fstream& stream, const std::string& fileName, bool read);
void closeFile(std::fstream& stream);
void isFileOpen(std::fstream& stream);
int getRandIntInRange(int min, int max);