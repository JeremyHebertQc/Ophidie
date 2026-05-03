#include <vector>
#include "Button.h"

#pragma once

enum MenuList
{
	homeMenu,
	scoreboard,
	settings,
	howToPlay,
	startMenu
};

class Menu
{
private:
	// Gestion de l'interface
	sf::Sprite _wallpaper, _background;
	sf::Sprite _button;
	sf::Texture _texture;
	sf::Vector2f _scale, _position;

	// Gestion du texte
	sf::Text _text;
	sf::Font _font;
	sf::Color _textColor;

	// Gestion du son
	sf::SoundBuffer _musicBuffer;
	sf::Sound _musicSound;

	// Gestion des boutons
	std::vector<Button*> _buttons;

public:
	// Constructeurs
	Menu(); //NOTE: Créer un enum des types de menu et inclure un switch case dedans afin d'appeller différent constructeur selon le menu.

	// Destructeur
	~Menu();

	// Getters
	std::vector<Button*> getButtons();

	// Méthodes
	void addButton(const unsigned int buttonID, const int action, const std::string text, const int buttonStyle, const float scale, const sf::Vector2f position);
	int isButtonPressed(sf::Event event, sf::RenderWindow& window);
	int isButtonHover(sf::Event event, sf::RenderWindow& window);
	void drawButtons(sf::RenderWindow& window);

	// Créations des menus
	int loadHomeMenu(sf::RenderWindow& window);
	int loadSettingsMenu(sf::RenderWindow& window);
	int loadHowToPlayMenu(sf::RenderWindow& window);
	int loadStartMenu(sf::RenderWindow& window);
	int loadScoreboardMenu(sf::RenderWindow& window);
	int loadScoreboardMenu(sf::RenderWindow& window, int scoreboardType);

	// Gestion des actions
	int doButtonAction(sf::RenderWindow& window, int action);
};

