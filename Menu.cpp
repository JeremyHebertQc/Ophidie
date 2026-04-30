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
	_buttons.clear();
}

// Getters
std::vector<Button> Menu::getButtons()
{
	return _buttons;
}

// Méthodes
void Menu::addButton(const unsigned int buttonID, const int action, const std::string text, const sf::Texture& texture, const sf::Vector2f scale, const sf::Vector2f position)
{
	_buttons.push_back(Button(buttonID, action, text, texture, scale, position));
}

int Menu::isButtonPressed(sf::Event event, sf::RenderWindow& window)
{
	if(_buttons.size() > 0)
		for (int i = 0; i < _buttons.size(); i++)
		{
			if (_buttons[i].isButtonPressed(event, window))
				return _buttons[i].getButtonID();
		}

	return -1;
}

int Menu::isButtonHover(sf::Event event, sf::RenderWindow& window)
{
	if (_buttons.size() > 0)
		for (int i = 0; i < _buttons.size(); i++)
		{
			if (_buttons[i].isButtonHover(event, window))
				return _buttons[i].getButtonID();
		}

	return -1;
}

void Menu::drawButton(sf::RenderWindow& window, const int activeID)
{
	_buttons[activeID].draw(window, activeID);
}
