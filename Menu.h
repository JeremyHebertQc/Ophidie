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
	void addButton(const unsigned int buttonID, const int action, const std::string text, const sf::Texture& texture, const sf::Vector2f scale, const sf::Vector2f position);
	int isButtonPressed(sf::Event event, sf::RenderWindow& window);
	int isButtonHover(sf::Event event, sf::RenderWindow& window);
	void drawButton(sf::RenderWindow& window, const int activeID);
};

