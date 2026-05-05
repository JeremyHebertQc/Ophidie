/*====================================
Auteurs : J�r�my H�bert, Vincent Gagnon et F�lix-Antoine Lacroix
Projet : Ophidie
====================================*/

#include <iostream>

#include "const.h"
#include "Grid.h"

int main() {
    std::srand(time(NULL));
    std::cout << "Hello world!";
    Grid myGrid;
    myGrid.createMap(10,10, (GameMode)2, Difficulty(7));
    //std::cout << myGrid.getTileAt(2,2) << std::endl;
    std::cin.get();
    //system("pause>NUL");

    return SUCCESS;
}
