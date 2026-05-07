#pragma comment(linker, "/ENTRY:mainCRTStartup")
/*====================================
Auteurs : Jeremy Hebert, Vincent Gagnon et Felix-Antoine Lacroix
Projet : Ophidie
====================================*/

#include "Game.h"
#include "const.h"

int main() {
    Game game;
    game.play();

    return SUCCESS;
}