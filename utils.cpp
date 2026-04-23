/*====================================
Auteur : Jérémy Hébert
Projet : Ophidie
====================================*/

#ifdef _WIN32
#include <cassert>
#else
#include <unistd.h>
#endif

#include "utils.h"
void sleepMs(int ms)
{
#ifdef _WIN32
	Sleep(ms);
#else
	usleep(ms * 1000);
#endif
}