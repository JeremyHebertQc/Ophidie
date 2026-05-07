#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cassert>

#include "const.h"
#include "utils.h"
#include "Button.h"

// Private method
void Button::calculateTextPosition()
{
	float centerPositionX = _button.getGlobalBounds().width / 2.0,
		centerPositionY = _button.getGlobalBounds().height / 2.0;
	_text.setPosition(_button.getGlobalBounds().left + centerPositionX - (_text.getGlobalBounds().width / 2), _button.getGlobalBounds().top + centerPositionY - (_text.getGlobalBounds().height / 2));
}

// Constructors
Button::Button()
{
	_action = -1;
	_buttonPressed = false;
}

Button::Button(const int action, const std::string text, const int buttonStyle, const float scale, const sf::Vector2f position)
{
	// Button initializations
	_action = action;
	_buttonPressed = false;

	// Display management
	setButtonTexture(buttonStyle);
	_button.setScale(sf::Vector2f(scale, scale));
	_button.setOrigin(_texture.getSize().x / 2.f, _texture.getSize().y / 2.f);
	_button.setPosition(position);

	// Text management
	if (!_font.loadFromFile(FONT_PATH))
		exit(1);  //NOTE: Postmerge, créer un tag pour le enum des codes d'erreur et le sync

	_text.setFont(_font);
	_text.setCharacterSize(FONT_SIZE);
	_text.setString(text);
	_text.setStyle(sf::Text::Bold);
	setTextColor(61, 24, 79);
	calculateTextPosition();
}

// Destructor
Button::~Button()
{
	_action = 0;
	_buttonPressed = 0;
}

// Getter
int Button::getAction() const
{
	return _action;
}

// Setters
void Button::setTextColor(int r, int g, int b)
{
	assert((r >= 0 && r <= 255) && (g >= 0 && g <= 255) && (b >= 0 && b <= 255));

	_textColor.r = r;
	_textColor.g = g;
	_textColor.b = b;

	_text.setFillColor(_textColor);
}

void Button::setButtonTexture(const int buttonStyle)
{
	assert(buttonStyle >= 0 && buttonStyle <= nbStyle);

	switch (buttonStyle)
	{
	case bigButton:
		_texture.loadFromFile(BUTTON_TEXTURE_PATH + "bigButton.png");
		_pressedTexture.loadFromFile(BUTTON_TEXTURE_PATH + "pressedBigButton.png");
		break;

	case mediumButton:
		_texture.loadFromFile(BUTTON_TEXTURE_PATH + "mediumButton.png");
		_pressedTexture.loadFromFile(BUTTON_TEXTURE_PATH + "pressedMediumButton.png");
		break;

	case littleButton:
		_texture.loadFromFile(BUTTON_TEXTURE_PATH + "littleButton.png");
		_pressedTexture.loadFromFile(BUTTON_TEXTURE_PATH + "pressedLittleButton.png");
		break;

	case yesButton:
		_texture.loadFromFile(BUTTON_TEXTURE_PATH + "yesButton.png");
		_pressedTexture.loadFromFile(BUTTON_TEXTURE_PATH + "pressedYesButton.png");
		break;

	case noButton:
		_texture.loadFromFile(BUTTON_TEXTURE_PATH + "noButton.png");
		_pressedTexture.loadFromFile(BUTTON_TEXTURE_PATH + "pressedNoButton.png");
		break;

	default:
		exit(1); // TODO: Lors du merge, créer une erreur texture couldn't load.
	}

	_button.setTexture(_texture);
}

// Event management
void Button::updateButton(sf::RenderWindow& window)
{
	window.draw(_button);
	window.draw(_text);
	window.display();
	playButtonSound(_soundEffectBuffer, _soundEffect, BUTTON_SOUND_PATH + "button.wav");
	sf::sleep(sf::milliseconds(250));
}

void Button::playButtonSound(sf::SoundBuffer& soundEffectBuffer, sf::Sound& soundEffect, std::string soundPath)
{
	if (!soundEffectBuffer.loadFromFile(soundPath))
	{
		printf("ERROR: Sound can't load !"); //NOTE: Postmerge, créer un tag pour le enum des codes d'erreur et le sync + ne pas exit, c'est juste de la musique...
		return;
	}

	soundEffect.setBuffer(soundEffectBuffer);
	soundEffect.setLoop(false);
	soundEffect.setVolume(BUTTON_VOLUME); //TODO: Utiliser les settings des paramètres
	soundEffect.play();
}

int Button::isButtonPressed(sf::Event event, sf::RenderWindow& window)
{
	sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	if (_buttonPressed == true && (sf::Event::MouseButtonReleased))
	{
		_button.setTexture(_texture);
		_buttonPressed = false;
		return _action;
	}

	if (_button.getGlobalBounds().contains(mousePosition) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		_buttonPressed = true;
		_button.setTexture(_pressedTexture);
		updateButton(window);
	}
	return -1;
}

void Button::isButtonHover(sf::Event event, sf::RenderWindow& window)
{
	static bool loadedCursor = false;
	static sf::Cursor cursorHand;

	if (!loadedCursor)
		if (!cursorHand.loadFromSystem(sf::Cursor::Hand))
			printf("ERROR: Cursor doesn't load!\n"); //TODO: Transformer en SFML


	if (event.type == sf::Event::MouseMoved)
	{
		sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		if (_button.getGlobalBounds().contains(mousePosition))
			window.setMouseCursor(cursorHand);
	}
}

// Drawing management
void Button::draw(sf::RenderWindow& window)
{
	window.draw(_button);
	window.draw(_text);
}