#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

#include "Menu.h"
#include "Button.h"

// Constructeurs
Menu::Menu()
{
}

// Destructeur
Menu::~Menu()
{
}

// Getters
std::vector<Button> Menu::getButtons()
{
	return _buttons;
}

// Méthodes
void Menu::addButton(const unsigned int buttonID, const int action, const std::string text, const sf::Color fillColor, const sf::Color outlineColor, const sf::Vector2f scale, const sf::Vector2f position)
{
	_buttons.push_back(Button(buttonID, action, text, fillColor, outlineColor, scale, position));
}
