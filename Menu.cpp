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
	setButtonTexture(buttonStyle);
	_buttons.push_back(new Button(buttonID, action, text, _texture, scale, position));
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

void Menu::setButtonTexture(int buttonStyle)
{
	switch (buttonStyle)
	{
	case bigButton:
		_texture.loadFromFile(BUTTON_TEXTURE_PATH + "bigButton.png");
		break;

	case mediumButton:
		_texture.loadFromFile(BUTTON_TEXTURE_PATH + "mediumButton.png");
		break;

	case littleButton:
		_texture.loadFromFile(BUTTON_TEXTURE_PATH + "littleButton.png");
		break;

	case yesButton:
		_texture.loadFromFile(BUTTON_TEXTURE_PATH + "yesButton.png");
		break;

	case noButton:
		_texture.loadFromFile(BUTTON_TEXTURE_PATH + "noButton.png");
		break;

	case pressedBigButton:
		_texture.loadFromFile(BUTTON_TEXTURE_PATH + "pressedBigButton.png");
		break;

	case pressedMediumButton:
		_texture.loadFromFile(BUTTON_TEXTURE_PATH + "pressedMediumButton.png");
		break;

	case pressedLittleButton:
		_texture.loadFromFile(BUTTON_TEXTURE_PATH + "pressedLittleButton.png");
		break;

	case pressedYesButton:
		_texture.loadFromFile(BUTTON_TEXTURE_PATH + "pressedYesButton.png");
		break;

	case pressedNoButton:
		_texture.loadFromFile(BUTTON_TEXTURE_PATH + "pressedNoButton.png");
		break;

	default:
		exit(1); // TODO: Lors du merge, créer une erreur texture couldn't load.
	}
}
