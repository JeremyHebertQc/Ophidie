#include <vector>
#include "Button.h"

#pragma once

class Menu
{
private:
	std::vector<Button> _buttons;

public:
	// Constructeurs
	Menu();

	// Destructeur
	~Menu();

	// Getters
	std::vector<Button> getButtons();

	// Méthodes
	void addButton(const unsigned int buttonID, const int action, const std::string text, const sf::Color fillColor, const sf::Color outlineColor, const sf::Vector2f scale, const sf::Vector2f position);
};

