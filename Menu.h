#pragma once

#include <vector>
#include "Button.h"

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
	Menu();

	// Destructeur
	~Menu();

	// Getters
	std::vector<Button*> getButtons();

	// Méthodes
	void addButton(const unsigned int buttonID, const int action, const std::string text, const int buttonStyle, const float scale, const sf::Vector2f position);
	int isButtonPressed(sf::Event event, sf::RenderWindow& window);
	void isButtonHover(sf::Event event, sf::RenderWindow& window);
	void drawButtons(sf::RenderWindow& window);
	int isAction(sf::RenderWindow& window);

	// Créations des menus
	bool loadHomeMenu(sf::RenderWindow& window);
	void loadSettingsMenu(sf::RenderWindow& window);
	void loadHowToPlayMenu(sf::RenderWindow& window);
	void loadStartMenu(sf::RenderWindow& window);
	void loadScoreboardMenu(sf::RenderWindow& window);
	void loadScoreboardMenu(sf::RenderWindow& window, int scoreboardType);
};