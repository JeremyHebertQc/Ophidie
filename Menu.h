#pragma once

#include <vector>
#include <string>
#include "Button.h"

const std::string SOUND_PATH = "assets/soundEffects/"; //TODO: Déplacer dans const
const int TEXT_FONT_SIZE = 12; //TODO: Déplacer dans const
const int EMPTY = 0; // TODO: Déplacer dans const
const std::string LOGO_PATH = "assets/menu/logo.png"; // TODO: Déplacer dans const
const std::string WALLPAPER_PATH = "assets/menu/wallpaper.png"; // TODO: Déplacer dans const
const std::string MENU_ASSET_PATH = "assets/menu/"; // TODO: Déplacer dans const

class Menu
{
private:
	// Interface declarations
	std::vector<sf::Sprite*> _sprites;
	std::vector<sf::Texture*> _textures;
	sf::Sprite _wallpaper, _sprite;
	sf::Sprite _button;
	sf::Texture _texture;
	sf::Vector2f _scale, _position;

	// Text declarations
	std::vector<sf::Text> _texts;
	sf::Text _text;
	sf::Font _font;
	sf::Color _textColor;

	// Music declarations
	sf::SoundBuffer _musicBuffer;
	sf::Sound _musicSound;

	// Buttons declarations
	std::vector<Button*> _buttons;

public:
	// Constructor
	Menu(sf::RenderWindow& window);

	// Destructor
	~Menu();

	// Getters
	float getCenterPositionX(sf::RenderWindow& window) const;
	float getCenterPositionY(sf::RenderWindow& window) const;

	// Setter
	void setTextColor(int r, int g, int b, sf::Text& text);

	// Event management
	int isButtonPressed(sf::Event event, sf::RenderWindow& window);
	void isButtonHover(sf::Event event, sf::RenderWindow& window);
	int isAction(sf::RenderWindow& window);

	// Music management
	void playMusic(std::string soundFileName);
	void stopMusic();

	// Vectors management
	void addButton(const int action, const std::string text, const int buttonStyle, const float scale, const sf::Vector2f position);
	void addText(const int fontSize, const std::string text, const sf::Vector2f position, int r, int g, int b);
	void addTexture(const std::string texture);
	void addSprite(const float scale, const sf::Vector2f position, const std::string texture);

	// Drawing management
	void drawButtons(sf::RenderWindow& window);
	void drawTexts(sf::RenderWindow& window);
	void drawText(sf::RenderWindow& window, sf::Text text);
	void drawSprites(sf::RenderWindow& window);
	void drawSprite(sf::RenderWindow& window, sf::Sprite* sprite);
	void draw(sf::RenderWindow& window);

	// Menu initiation
	void initHomeMenu(sf::RenderWindow& window);
	void initSettingsMenu(sf::RenderWindow& window);
	void initHowToPlayMenu(sf::RenderWindow& window);
	void initStartMenu(sf::RenderWindow& window);
	void initScoreboardMenu(sf::RenderWindow& window);

	// Menu loading
	bool loadHomeMenu(sf::RenderWindow& window);
	void loadSettingsMenu(sf::RenderWindow& window);
	void loadHowToPlayMenu(sf::RenderWindow& window);
	void loadStartMenu(sf::RenderWindow& window);
	void loadScoreboardMenu(sf::RenderWindow& window);
	void loadScoreboardMenu(sf::RenderWindow& window, int scoreboardType);
};