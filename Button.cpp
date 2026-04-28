#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cassert>

#include "const.h"
#include "Button.h"

// Constructeurs
Button::Button()
{
	_buttonID = 0;
	_isMouseReleased = false;
}

Button::Button(const unsigned int buttonID, bool isMouseReleased)
{
	_buttonID = buttonID;
	_isMouseReleased = isMouseReleased;
}

// Destructeur
Button::~Button()
{
	_scale = _position;
	_buttonID = _isMouseReleased = 0;
}

// Getters
sf::RectangleShape Button::getRectangle() const
{
	return _rectangle;
}

sf::Text Button::getText() const
{
	return _text;
}

sf::Color Button::getFillColor() const
{
	return _fillColor;
}

sf::Color Button::getOutlineColor() const
{
	return _outlineColor;
}

sf::Vector2f Button::getScale() const
{
	return _scale;
}

sf::Vector2f Button::getPosition() const
{
	return _position;
}

sf::SoundBuffer Button::getpressedSoundBuffer() const
{
	return _pressedSoundBuffer;
}

sf::Sound Button::getPressedSound() const
{
	return _pressedSound;
}

unsigned int Button::getButtonID() const
{
	return _buttonID;
}

bool Button::getIsMouseReleased() const
{
	return _isMouseReleased;
}

// Setters
void Button::setRectangle(sf::RectangleShape rectangle)
{
	_rectangle = rectangle;
}

void Button::setText(sf::Text text)
{
	_text = text;
}

void Button::setFillColor(sf::Color fillColor)
{
	_fillColor = fillColor;
}

void Button::setOutlineColor(sf::Color outlineColor)
{
	_outlineColor = outlineColor;
}

void Button::setScale(sf::Vector2f scale)
{
	_scale = scale;
}

void Button::setPosition(sf::Vector2f position)
{
	_position = position;
}

void Button::setpressedSoundBuffer(sf::SoundBuffer pressedSoundBuffer)
{
	_pressedSoundBuffer = pressedSoundBuffer;
}

void Button::setPressedSound(sf::Sound pressedSound)
{
	_pressedSound = pressedSound;
}

void Button::setButtonID(unsigned int buttonID)
{
	assert(buttonID >= 0);
	_buttonID = buttonID;
}

void Button::setIsmouseReleased(bool isMouseReleased)
{
	assert(isMouseReleased == (0 || 1));
	_isMouseReleased = isMouseReleased;
}

// Fonctionnement du bouton
void Button::playButtonSound(sf::SoundBuffer pressedSoundBuffer, sf::Sound pressedSound, std::string soundPath)
{
	if (!pressedSoundBuffer.loadFromFile(soundPath)) // On charge la musique du jeu
		return;

	pressedSound.setBuffer(pressedSoundBuffer); // On applique la musique chargée à l’objet de type "Sound"
	pressedSound.setLoop(false); // La musique jouera en boucle
	pressedSound.play(); // On fait jouer la musique
}