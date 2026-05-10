#pragma once
#include <SFML/Graphics.hpp>
#include "Settings.h"

class Button
{
private:
	// Button declarations
	int _action;
	bool _buttonPressed;

	// Interface declarations
	sf::Sprite _button;
	sf::Texture _texture, _pressedTexture;
	sf::Vector2f _scale, _position;

	// Text declarations
	sf::Text _text;
	sf::Font _font;
	sf::Color _textColor;
	void calculateTextPosition();

	// Sound declarations
	sf::SoundBuffer _soundEffectBuffer;
	sf::Sound _soundEffect;

public:
	// Constructors
	Button();
	Button(const int action, const std::string text, const int buttonStyle, const float scale, const sf::Vector2f position);

	// Destructor
	~Button();

	// Getter
	int getAction() const;

	// Setters
	void setTextColor(int r, int g, int b);
	void setButtonTexture(const int buttonStyle);

	// Event management
	void updateButton(sf::RenderWindow& window, Settings& settings);
	void playButtonSound(sf::SoundBuffer& soundEffectBuffer, sf::Sound& soundEffect, std::string soundPath, float volume);
	int isButtonPressed(sf::Event event, sf::RenderWindow& window, Settings& settings);
	void isButtonHover(sf::Event event, sf::RenderWindow& window);

	// Drawing management
	void draw(sf::RenderWindow& window);
};