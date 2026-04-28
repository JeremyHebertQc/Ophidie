#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cassert>

#include "const.h"
#include "utils.h"
#include "Button.h"

void Button::calculatePos()
{
	float positionMidX = _rectangle.getGlobalBounds().width / 2.0,
		positionMidY = _rectangle.getGlobalBounds().height / 2.0;
	_text.setPosition(_rectangle.getGlobalBounds().left + positionMidX - (_text.getGlobalBounds().width / 2), _rectangle.getGlobalBounds().top + positionMidY - (_text.getGlobalBounds().height / 2));
}

// Constructeurs
Button::Button()
{
	_buttonID = 0;
	_isMouseReleased = false;
}

Button::Button(const unsigned int buttonID, const std::string text, const sf::Color fillColor, const sf::Color outlineColor, const sf::Vector2f scale, const sf::Vector2f position)
{
	_buttonID = buttonID;
	_isMouseReleased = false;

	_rectangle.setFillColor(fillColor);
	_rectangle.setOutlineColor(outlineColor);
	_rectangle.setOutlineThickness(OUTLINE_THICKNESS_BUTTON);
	_rectangle.setSize(scale);
	_rectangle.setPosition(position);

	if (!_font.loadFromFile("assets/fonts/arial.ttf")) //TODO: REmplacer pour la font const
		exit(1);

	_text.setFont(_font);
	_text.setCharacterSize(12);
	_text.setString(text);
	_text.setStyle(sf::Text::Bold);
	_text.setFillColor(sf::Color::Black);
	calculatePos();
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

float Button::getOutlineThickness() const
{
	return _rectangle.getOutlineThickness();
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
void Button::setRectangle(const sf::RectangleShape& rectangle)
{
	_rectangle = rectangle;
}

void Button::setText(const sf::Text& text)
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

void Button::setOutlineThickness(float thickness)
{
	_rectangle.setOutlineThickness(thickness);
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
void Button::updateButton(sf::RenderWindow& window)
{
	printf("Clique %02d\n", _buttonID);
}

void Button::playButtonSound(sf::SoundBuffer& pressedSoundBuffer, sf::Sound& pressedSound, std::string soundPath)
{
	if (!pressedSoundBuffer.loadFromFile(soundPath)) // On charge la musique du jeu
		exit(1);

	pressedSound.setBuffer(pressedSoundBuffer); // On applique la musique chargée à l’objet de type "Sound"
	pressedSound.setLoop(false); // La musique jouera en boucle
	pressedSound.play(); // On fait jouer la musique
}

void Button::draw(sf::RenderWindow& window, const int activeID)
{
	window.draw(_rectangle);
	window.draw(_text);
}

bool Button::isButtonPressed(sf::Event event, sf::RenderWindow& window)
{
 if (event.type)
	if (_rectangle.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		updateButton(window);
		switch (event.type)
		{
		case sf::Event::MouseButtonPressed:
			_rectangle.setOutlineColor(sf::Color::Red);
			
			break;
			
		case sf::Event::MouseButtonReleased:
			_rectangle.setOutlineColor(sf::Color::Cyan);
			sleepMs(500);
			break;
		}
		playButtonSound(_pressedSoundBuffer, _pressedSound);
		return true;
	}
	return false;
}

bool Button::isButtonHover(sf::Event event, sf::RenderWindow& window)
{
	static bool loadedCursor = false;
	static sf::Cursor cursorHand;

	if (!loadedCursor)
		if (!cursorHand.loadFromSystem(sf::Cursor::Hand))
			printf("ERREUR CHARGEMENT CURSEUR!\n");


	if (event.type == sf::Event::MouseMoved)
		if (_rectangle.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
		{
			window.setMouseCursor(cursorHand);
			return true;
		}
		else
			return false;
}
