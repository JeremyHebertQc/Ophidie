#pragma once
#include <SFML/Graphics.hpp>
#include "Settings.h"

class Button
{
private:
	// Pointer declarations
	Settings *_settings;
	sf::RenderWindow *_window;

	// Button declarations
	int _action;
	bool _buttonPressed;

	// Interface declarations
	sf::Sprite _button;
	sf::Texture _texture;
	sf::Texture _pressedTexture;
	sf::Vector2f _scale;
	sf::Vector2f _position;

	// Text declarations
	sf::Font _font;
	sf::Text _text;
	sf::Color _textColor;
	void calculateTextPosition();

	// Sound declarations
	sf::SoundBuffer _soundEffectBuffer;
	sf::Sound _soundEffect;

public:
	// Constructors
	Button() = delete;
    Button(sf::RenderWindow* window, Settings* settings, ButtonAction action, const std::string& text, ButtonStyle style, float scale, sf::Vector2f position);

	// Destructor
	~Button();

	// Getter
	int getAction() const;

	// Setters
	void setTextColor(int r, int g, int b);
	void setButtonTexture(int buttonStyle);

	// Event management
	void updateButton();
	void playButtonSound(const std::string& soundPath, float volume);
	int isButtonPressed(const sf::Event& event);
	void isButtonHover(const sf::Event& event);

	// Drawing management
	void draw();
};