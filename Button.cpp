#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cassert>

#include "const.h"
#include "utils.h"
#include "Button.h"
#include "Settings.h"

// Private method
void Button::calculateTextPosition()
{
	float centerPositionX = _button.getGlobalBounds().width / 2.f,
		centerPositionY = _button.getGlobalBounds().height / 2.f;
	_text.setPosition(_button.getGlobalBounds().left + centerPositionX - (_text.getGlobalBounds().width / 2.f), _button.getGlobalBounds().top + centerPositionY - (_text.getGlobalBounds().height / 2.f));
}

// Constructor
Button::Button(sf::RenderWindow* window, Settings* settings, const int action, const std::string text, const int buttonStyle, const float scale, const sf::Vector2f position)
{
	// Extern variables initializations
	_window = window;
	_settings = settings;

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
		sendError(FILE_NOT_OPENED);

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
		sendFatalError(FILE_NOT_OPENED);
	}

	_button.setTexture(_texture);
}

// Event management
void Button::updateButton()
{
	_window->draw(_button);
	_window->draw(_text);
	_window->display();
	playButtonSound(BUTTON_SOUND_PATH + "button.wav", _settings->getMenu());
	sf::sleep(sf::milliseconds(250));
}

void Button::playButtonSound(std::string soundPath, float volume)
{
	if (!_soundEffectBuffer.loadFromFile(soundPath))
	{
		sendError(FILE_NOT_OPENED);
		return;
	}

	_soundEffect.setBuffer(_soundEffectBuffer);
	_soundEffect.setLoop(false);
	_soundEffect.setVolume(volume);
	_soundEffect.play();
}

int Button::isButtonPressed(sf::Event event)
{
	sf::Vector2f mousePosition = _window->mapPixelToCoords(sf::Mouse::getPosition(*_window));

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
		updateButton();
	}
	return -1;
}

void Button::isButtonHover(sf::Event event)
{
	static bool loadedCursor = false;
	static sf::Cursor cursorHand;

	if (!loadedCursor)
		if (!cursorHand.loadFromSystem(sf::Cursor::Hand))
			sendError(CURSOR_FAILED_TO_LOAD);


	if (event.type == sf::Event::MouseMoved)
	{
		sf::Vector2f mousePosition = _window->mapPixelToCoords(sf::Mouse::getPosition(*_window));
		if (_button.getGlobalBounds().contains(mousePosition))
			_window->setMouseCursor(cursorHand);
	}
}

// Drawing management
void Button::draw()
{
	_window->draw(_button);
	_window->draw(_text);
}