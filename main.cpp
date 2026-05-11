/*====================================
Auteurs : Jeremy Hebert, Vincent Gagnon et Felix-Antoine Lacroix
Projet : Ophidie
====================================*/

#include "const.h"
#include "Game.h"

int main() {
	srand(time(NULL));

    Game game;
    game.play();

    return Success;
}
