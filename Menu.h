#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include "Button.h"
#include "const.h"
#include "Settings.h"

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

	// Use extern declarations
	Settings* _settings;
	sf::RenderWindow* _window;

	// Init checkup declaration
	bool _isMenuInit;
	bool _isSubmenuInit;

  public:
	// Constructor
	Menu(sf::RenderWindow* window, Settings* settings);

	// Destructor
	~Menu();

	// Getters
	float getCenterPositionX() const;
	float getCenterPositionY() const;

	// Setter
	void setTextColor(int r, int g, int b, sf::Text& text);

	// Event management
	int isButtonPressed(sf::Event event);
	void isButtonHover(sf::Event event);
	int isAction();

	// Music management
	void playMusic(std::string soundFileName, float volume);
	void stopMusic();

	// Vectors management
	void addButton(const int action, const std::string text, const int buttonStyle, const float scale, const sf::Vector2f position);
	void addText(const int fontSize, const std::string text, const sf::Vector2f position, int r, int g, int b);
	void addTexture(const std::string texture);
	void addSprite(const float scale, const sf::Vector2f position, const std::string texture);
	void clearVectors();

	// Drawing management
	void drawButtons();
	void drawTexts();
	void drawText(sf::Text text);
	void drawSprites();
	void drawSprite(sf::Sprite* sprite);
	void draw();

	// Menu initiation
	void initHomeMenu();
	void initSettingsMenu();
	void initHowToPlayMenu();
	void initStartMenu();
	void initScoreboardMenu();

	// Menu loading
	bool loadHomeMenu();
	bool loadSettingsMenu();
	bool loadHowToPlayMenu();
	bool loadStartMenu();
	bool loadScoreboardMenu();
	bool loadScoreboardMenu(int scoreboardType);
};