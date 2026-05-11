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
Button::Button(sf::RenderWindow* window, Settings* settings, ButtonAction action, const std::string& text, ButtonStyle style, float scale, sf::Vector2f position)
{
	// Extern variables initializations
	_window = window;
	_settings = settings;

	// Button initializations
	_action = action;
	_buttonPressed = false;
	_checkedButton = false;
	if (style == CheckButton)
		_checkButton = true;
	else
		_checkButton = false;

	// Display management
	setButtonTexture(style);
	_button.setScale(sf::Vector2f(scale, scale));
	_button.setOrigin(_texture.getSize().x / 2.f, _texture.getSize().y / 2.f);
	_button.setPosition(position);

	// Text management
	if (!_font.loadFromFile(FONT_PATH))
		sendError(FileNotOpened);

	_text.setFont(_font);
	_text.setCharacterSize(FONT_SIZE);
	_text.setString(text);
	_text.setStyle(sf::Text::Bold);
	setTextColor(BUTTON_TEXT_COLOR_R, BUTTON_TEXT_COLOR_G, BUTTON_TEXT_COLOR_B);
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

void Button::setButtonTexture(int buttonStyle)
{
	assert(buttonStyle >= 0 && buttonStyle <= nbStyle);

	switch (buttonStyle)
	{
	case BigButton:
		_texture.loadFromFile(BUTTON_DIR + "bigButton.png");
		_pressedTexture.loadFromFile(BUTTON_DIR + "pressedBigButton.png");
		break;

	case MediumButton:
		_texture.loadFromFile(BUTTON_DIR + "mediumButton.png");
		_pressedTexture.loadFromFile(BUTTON_DIR + "pressedMediumButton.png");
		break;

	case LittleButton:
		_texture.loadFromFile(BUTTON_DIR + "littleButton.png");
		_pressedTexture.loadFromFile(BUTTON_DIR + "pressedLittleButton.png");
		break;

	case YesButton:
		_texture.loadFromFile(BUTTON_DIR + "yesButton.png");
		_pressedTexture.loadFromFile(BUTTON_DIR + "pressedYesButton.png");
		break;

	case NoButton:
		_texture.loadFromFile(BUTTON_DIR + "NoButton.png");
		_pressedTexture.loadFromFile(BUTTON_DIR + "pressedNoButton.png");
		break;

	case CheckButton:
		_texture.loadFromFile(BUTTON_DIR + "emptyButton.png");
		_pressedTexture.loadFromFile(BUTTON_DIR + "pressedEmptyButton.png");
		_secondTexture.loadFromFile(BUTTON_DIR + "yesButton.png");
		_pressedSecondTexture.loadFromFile(BUTTON_DIR + "pressedYesButton.png");
		break;


	default:
		sendFatalError(FileNotOpened);
	}

	_button.setTexture(_texture);
}

// Event management
void Button::updateButton()
{
	_window->draw(_button);
	_window->draw(_text);
	_window->display();
	playButtonSound(SOUND_DIR + "button.wav", _settings->getMenu());
	sf::sleep(sf::milliseconds(250));
}

void Button::playButtonSound(const std::string& soundPath, float volume)
{
	if (!_soundEffectBuffer.loadFromFile(soundPath))
	{
		sendError(FileNotOpened);
		return;
	}

	_soundEffect.setBuffer(_soundEffectBuffer);
	_soundEffect.setLoop(false);
	_soundEffect.setVolume(volume);
	_soundEffect.play();
}

int Button::isButtonPressed(const sf::Event& event)
{
	sf::Vector2f mousePosition = _window->mapPixelToCoords(sf::Mouse::getPosition(*_window));

	if (_buttonPressed && event.type == sf::Event::MouseButtonReleased)
	{
		if (_checkButton && _checkedButton)
		{
			_button.setTexture(_texture);
			_checkedButton = false;
		}
		else if (_checkButton && !_checkedButton)
		{
			_button.setTexture(_secondTexture);
			_checkedButton = true;
		}
		else
			_button.setTexture(_texture);

		_buttonPressed = false;
		return _action;
	}

	if (_button.getGlobalBounds().contains(mousePosition) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		_buttonPressed = true;
		if (_checkButton && _checkedButton)
			_button.setTexture(_pressedTexture);
		else if (_checkButton && !_checkedButton)
			_button.setTexture(_pressedSecondTexture);
		else
			_button.setTexture(_pressedTexture);

		updateButton();
	}
	return -1;
}

void Button::isButtonHover(const sf::Event& event)
{
	static bool loadedCursor = false;
	static sf::Cursor cursorHand;

	if (!loadedCursor)
		if (!cursorHand.loadFromSystem(sf::Cursor::Hand))
			sendError(CursorFailedToLoad);


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