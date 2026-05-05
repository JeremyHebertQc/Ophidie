#pragma once

#include <vector>
#include <string>
#include "Button.h"

const std::string SOUND_PATH = "assets/soundEffects/"; //TODO: Déplacer dans const
const int TEXT_FONT_SIZE = 12; //TODO: Déplacer dans const

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
	std::vector<sf::Sprite*> _sprites;
	sf::Sprite _wallpaper, _sprite;
	sf::Sprite _button;
	sf::Texture _texture;
	sf::Vector2f _scale, _position;

	// Gestion du texte
	std::vector<sf::Text> _texts;
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
	Menu(sf::RenderWindow& window);

	// Destructeur
	~Menu();

	// Getters
	std::vector<Button*> getButtons();
	std::vector<sf::Text> getTexts();

	// Setters
	void setPosition(sf::Vector2f position);
	void setText(const sf::Text& text);
	void setTextColor(int r, int g, int b, sf::Text& text);
	void setScale(sf::Vector2f scale);

	// Méthodes
	void addButton(const unsigned int buttonID, const int action, const std::string text, const int buttonStyle, const float scale, const sf::Vector2f position);
	int isButtonPressed(sf::Event event, sf::RenderWindow& window);
	void isButtonHover(sf::Event event, sf::RenderWindow& window);
	void drawButtons(sf::RenderWindow& window);
	void drawTexts(sf::RenderWindow& window);
	void drawSprites(sf::RenderWindow& window);
	int isAction(sf::RenderWindow& window);
	void drawText(sf::RenderWindow& window, sf::Text text);
	void drawSprite(sf::RenderWindow& window, sf::Sprite* sprite);
	void draw(sf::RenderWindow& window);

	// Créations des menus
	bool initHomMenu(sf::RenderWindow& window);
	bool loadHomeMenu(sf::RenderWindow& window);
	void loadSettingsMenu(sf::RenderWindow& window);
	void loadHowToPlayMenu(sf::RenderWindow& window);
	void loadStartMenu(sf::RenderWindow& window);
	void loadScoreboardMenu(sf::RenderWindow& window);
	void loadScoreboardMenu(sf::RenderWindow& window, int scoreboardType);

	// Gestion de la musique
	void playMusic(std::string soundPath);
	void stopMusic();

	// Gestion du texte
	void addText(const std::string text, const sf::Vector2f position, const int fontSize, int r, int g, int b);

	// Gestion des sprites
	void addSprite(const float scale, const sf::Vector2f position, const std::string texture);
};