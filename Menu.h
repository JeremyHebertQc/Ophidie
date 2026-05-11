#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include "Button.h"
#include "const.h"
#include "Scoreboard.h"
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

	// Init checkup declarations
	bool _isMenuInit;
	bool _isSubmenuInit;

	// Scoreboard menu declartions
	sf::Vector2i _scoreboardMenuNavigation;
	std::string _currentScores[NUMBER_OF_SCORES];
	std::string _currentDifficulty;

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
	void setAlignment(TextAlignment alignment);

	// Event management
	int isButtonPressed(const sf::Event& event);
	void isButtonHover(const sf::Event& event);
	int isAction();

	// Music management
	void playMusic(const std::string& soundFileName, float volume);
	void stopMusic();

	// Vectors management
	void addButton(ButtonAction action, const std::string& text, ButtonStyle style, float scale, sf::Vector2f position);
	void addButton(ButtonAction action, const std::string& text, ButtonStyle style, float scale, sf::Vector2f position, bool* checked);
	void addText(int fontSize, const std::string& text, sf::Vector2f position, TextAlignment alignment, int r, int g, int b);
	void addTexture(const std::string& texture);
	void addSprite(float scale, sf::Vector2f position, const std::string& texture);
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
	void initPauseMenu();
	void initGameOverMenu();

	// Menu loading
	bool loadHomeMenu();
	bool loadSettingsMenu();
	bool loadHowToPlayMenu();
	bool loadStartMenu();
	bool loadScoreboardMenu();
	ButtonAction loadPauseMenu();
	bool loadGameOverMenu();
};