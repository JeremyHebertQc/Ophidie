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
void Menu::addButton(const unsigned int buttonID, const int action, const std::string text, const int buttonStyle, const float scale, const sf::Vector2f position)
{
	_buttons.push_back(new Button(buttonID, action, text, buttonStyle, scale, position));
}

int Menu::isButtonPressed(sf::Event event, sf::RenderWindow& window)
{
	if(_buttons.size() > 0)
		for (int i = 0; i < _buttons.size(); i++)
		{
			if (_buttons[i]->isButtonPressed(event, window) != -1)
				return _buttons[i]->getAction();
		}

	return -1;
}

void Menu::isButtonHover(sf::Event event, sf::RenderWindow& window)
{
	if (_buttons.size() > 0)
		for (int i = 0; i < _buttons.size(); i++)
			_buttons[i]->isButtonHover(event, window);
}

void Menu::drawButtons(sf::RenderWindow& window)
{
	
	for (int i = 0; i < _buttons.size(); i++)
	{
		_buttons[i]->draw(window);
	}
}

int Menu::isAction(sf::RenderWindow& window)
{
	static sf::Cursor cursorArrow;
	if (!cursorArrow.loadFromSystem(sf::Cursor::Arrow))
		printf("ERROR: Cursor doesn't load!\n"); //TODO: Transformer en SFML

	sf::Event event;
	while (window.pollEvent(event))
	{
		int action;
		switch (event.type)
		{
		case sf::Event::Closed:
			return closeOphidie;

		case sf::Event::MouseButtonPressed:
		case sf::Event::MouseButtonReleased:
			action = isButtonPressed(event, window);
			window.clear();
			if (action != -1)
				return action;

		case sf::Event::MouseMoved:
			window.setMouseCursor(cursorArrow);
			isButtonHover(event, window);
			break;

		case sf::Event::Resized:
			window.clear();
			window.display();
			break;

		default:
			break;
		}
	}

	return -1;
}

bool Menu::loadHomeMenu(sf::RenderWindow& window)
{
	static bool isCreated = false;
	if (isCreated == false)
	{
		float centerPositionX = window.getSize().x;
		addButton(0, startGame, "Play", bigButton, 0.5f, sf::Vector2f(centerPositionX / 2.0f, 300.0f));
		addButton(1, openHTP, "How to play?", bigButton, 0.5f, sf::Vector2f(centerPositionX / 2.0f, 450.0f));
		addButton(2, openScoreboard, "Scoreboard", bigButton, 0.5f, sf::Vector2f(centerPositionX / 2.0f, 600.0f));
		addButton(3, openSettings, "Settings", littleButton, 0.5f, sf::Vector2f(centerPositionX / 2.0f - 130.0f, 750.0f));
		addButton(4, closeOphidie, "Quit", littleButton, 0.5f, sf::Vector2f(centerPositionX / 2.0f + 130.0f, 750.0f));
		isCreated = true;
	}

	while (true)
	{
		window.clear();
		drawButtons(window);
		window.display();

		switch (isAction(window))
		{
		case startGame:
			loadStartMenu(window);
			return true;

		case closeOphidie:
			return false;
			
		case openHTP:
			loadHowToPlayMenu(window);
			break;

		case openScoreboard:
			loadScoreboardMenu(window);
			break;
			
		case openSettings:
			loadSettingsMenu(window);
			break;

		default:
		case -1:
			break;
		}
	}
}

void Menu::loadSettingsMenu(sf::RenderWindow& window) //TODO: Build it
{
	printf("Settings Menu");
	sf::sleep(sf::milliseconds(1000));
}

void Menu::loadScoreboardMenu(sf::RenderWindow& window) //TODO: Build it
{
	printf("Scoreboard Menu");
	sf::sleep(sf::milliseconds(1000));
}

void Menu::loadScoreboardMenu(sf::RenderWindow& window, int scoreboardType) //TODO: Build it
{
	switch (scoreboardType)
	{
	case goToNormalSCR:
		printf("Normal SCR");
		sf::sleep(sf::milliseconds(1000));
		break;

	case goToSurvivalSCR:
		printf("Survival SCR");
		sf::sleep(sf::milliseconds(1000));
		break;

	case goToDeathTrapSCR:
		printf("Death Trap SCR");
		sf::sleep(sf::milliseconds(1000));
		break;

	case goToSurviveHellSCR:
		printf("Survive Hell SCR");
		sf::sleep(sf::milliseconds(1000));
		break;

	default:
		break;
	}
}

void Menu::loadHowToPlayMenu(sf::RenderWindow& window) //TODO: Build it
{
	printf("How to play");
	sf::sleep(sf::milliseconds(1000));
}

void Menu::loadStartMenu(sf::RenderWindow& window) //TODO: Build it
{
	printf("Start menu. Choose somes options");
	sf::sleep(sf::milliseconds(1000));
}