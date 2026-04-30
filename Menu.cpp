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
	for (Button* b : _buttons)
		delete b;
		
	_buttons.clear();
}

// Getters
std::vector<Button*> Menu::getButtons()
{
	return _buttons;
}

// Méthodes
void Menu::addButton(const unsigned int buttonID, const int action, const std::string text, const int buttonStyle, const sf::Vector2f scale, const sf::Vector2f position)
{
	_buttons.push_back(new Button(buttonID, action, text, buttonStyle, scale, position));
}

int Menu::isButtonPressed(sf::Event event, sf::RenderWindow& window)
{
	if(_buttons.size() > 0)
		for (int i = 0; i < _buttons.size(); i++)
		{
			if (_buttons[i]->isButtonPressed(event, window))
				return _buttons[i]->getButtonID();
		}

	return -1;
}

int Menu::isButtonHover(sf::Event event, sf::RenderWindow& window)
{
	if (_buttons.size() > 0)
		for (int i = 0; i < _buttons.size(); i++)
		{
			if (_buttons[i]->isButtonHover(event, window))
				return _buttons[i]->getButtonID();
		}

	return -1;
}

void Menu::drawButtons(sf::RenderWindow& window)
{
	
	for (int i = 0; i < _buttons.size(); i++)
	{
		_buttons[i]->draw(window, i);
	}
}

