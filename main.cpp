#include <iostream>
#include <nlohmann/json.hpp>
#include <SFML/graphics.hpp>
#include <string>

#include "const.h"
#include "Settings.h"

int main() {
    Settings settings("settings.json");
    Difficulty difficulty;

    difficulty = (Difficulty)1;

    settings.test();

    system("pause>NUL");
    return SUCCESS;
}