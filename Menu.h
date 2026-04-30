#include <vector>
#include "Button.h"

#pragma once

const std::string BUTTON_TEXTURE_PATH = "assets/buttons/"; //TODO: Déplacer dans const

enum ButtonStyle
{
	bigButton,
	mediumButton,
	littleButton,
	yesButton,
	noButton,

	pressedBigButton,
	pressedMediumButton,
	pressedLittleButton,
	pressedYesButton,
	pressedNoButton
};

class Menu
{
private:
	std::vector<Button*> _buttons;
	sf::Texture _texture;

public:
	// Constructeurs
	Menu();

	// Destructeur
	~Menu();

	// Getters
	std::vector<Button*> getButtons();

	// Méthodes
	void addButton(const unsigned int buttonID, const int action, const std::string text, const int buttonStyle, const sf::Vector2f scale, const sf::Vector2f position);
	int isButtonPressed(sf::Event event, sf::RenderWindow& window);
	int isButtonHover(sf::Event event, sf::RenderWindow& window);
	void drawButtons(sf::RenderWindow& window);
	void setButtonTexture(int buttonStyle);
};

