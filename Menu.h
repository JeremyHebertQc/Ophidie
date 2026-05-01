#include <vector>
#include "Button.h"

#pragma once

class Menu
{
private:
	std::vector<Button*> _buttons;
	sf::Texture _texture;

public:
	// Constructeurs
	Menu(); //NOTE: Créer un enum des types de menu et inclure un switch case dedans afin d'appeller différent constructeur selon le menu.

	// Destructeur
	~Menu();

	// Getters
	std::vector<Button*> getButtons();

	// Méthodes
	void addButton(const unsigned int buttonID, const int action, const std::string text, const int buttonStyle, const sf::Vector2f scale, const sf::Vector2f position);
	int isButtonPressed(sf::Event event, sf::RenderWindow& window);
	int isButtonHover(sf::Event event, sf::RenderWindow& window);
	void drawButtons(sf::RenderWindow& window);
};

