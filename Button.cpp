#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cassert>

#include "const.h"
#include "utils.h"
#include "Button.h"

// Fonction privé
void Button::calculateTextPosition()
{
	float centerPositionX = _button.getGlobalBounds().width / 2.0,
		centerPositionY = _button.getGlobalBounds().height / 2.0;
	_text.setPosition(_button.getGlobalBounds().left + centerPositionX - (_text.getGlobalBounds().width / 2), _button.getGlobalBounds().top + centerPositionY - (_text.getGlobalBounds().height / 2));
}

// Constructeurs
Button::Button()
{
	_buttonID = 0;
	_action = debugAction;
}

Button::Button(const unsigned int buttonID, int action, const std::string text, const int buttonStyle, const sf::Vector2f scale, const sf::Vector2f position)
{
	// Gestion du bouton
	_buttonID = buttonID;
	_action = action;

	// Gestion de l'apparence
	setButtonTexture(buttonStyle);
	_button.setScale(scale);
	_button.setPosition(position);

	// Gestion du texte
	if (!_font.loadFromFile(FONT_PATH))
		exit(1);  //NOTE: Postmerge, créer un tag pour le enum des codes d'erreur et le sync

	_text.setFont(_font);
	_text.setCharacterSize(FONT_SIZE);
	_text.setString(text);
	_text.setStyle(sf::Text::Bold);
	setTextColor(61, 24, 79);
	calculateTextPosition();
}

// Destructeur
Button::~Button()
{
	_buttonID = 0;
	_action = debugAction;
	;
}

// Getters
unsigned int Button::getButtonID() const
{
	return _buttonID;
}

int Button::getAction() const
{
	return _action;
}

sf::Texture Button::getTexture() const
{
	return _texture;
}

sf::Vector2f Button::getScale() const
{
	return _scale;
}

sf::Vector2f Button::getPosition() const
{
	return _position;
}

sf::Text Button::getText() const
{
	return _text;
}

// Setters
void Button::setButtonID(unsigned int buttonID)
{
	assert(buttonID >= 0);

	_buttonID = buttonID;
}

void Button::setAction(int action)
{
	assert(action >= 0 && action < NbAction);

	_action = action;
}

void Button::setTexture(sf::Texture& texture)
{
	_texture = texture;
}

void Button::setScale(sf::Vector2f scale)
{
	_scale = scale;
}

void Button::setPosition(sf::Vector2f position)
{
	_position = position;
}

void Button::setText(const sf::Text& text)
{
	_text = text;
}

void Button::setTextColor(int r, int g, int b)
{
	assert((r >= 0 && r <= 255) && (g >= 0 && g <= 255) && (b >= 0 && b <= 255));

	_textColor.r = r;
	_textColor.g = g;
	_textColor.b = b;

	_text.setFillColor(_textColor);
}

// Fonctionnement du bouton
void Button::updateButton(sf::RenderWindow& window)
{
	window.draw(_button);
	window.draw(_text);
	window.display();
	playButtonSound(_pressedSoundBuffer, _pressedSound, BUTTON_SOUND_PATH + "button.wav");
	sf::sleep(sf::milliseconds(150));
}

void Button::playButtonSound(sf::SoundBuffer& pressedSoundBuffer, sf::Sound& pressedSound, std::string soundPath)
{
	if (!pressedSoundBuffer.loadFromFile(soundPath))
	{
		printf("ERROR: Sound can't load !"); //NOTE: Postmerge, créer un tag pour le enum des codes d'erreur et le sync + ne pas exit, c'est juste de la musique...
		return;
	}

	pressedSound.setBuffer(pressedSoundBuffer);
	pressedSound.setLoop(false);
	pressedSound.play();
}

void Button::draw(sf::RenderWindow& window)
{
	window.draw(_button);
	window.draw(_text);
}

bool Button::isButtonPressed(sf::Event event, sf::RenderWindow& window)
{
	window.display();
	if (event.type)
	{

		sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		if (_button.getGlobalBounds().contains(mousePosition.x, mousePosition.y) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			_button.setTexture(_pressedTexture);
			updateButton(window);

			if (sf::Event::MouseButtonReleased)
			{
				_button.setTexture(_texture);
				doButtonAction(_action);
			}

			return true;
		}
	}
	return false;
}

bool Button::isButtonHover(sf::Event event, sf::RenderWindow& window)
{
	static bool loadedCursor = false;
	static sf::Cursor cursorHand;

	if (!loadedCursor)
		if (!cursorHand.loadFromSystem(sf::Cursor::Hand))
			printf("ERROR: Cursor doesn't load!\n"); //TODO: Transformer en SFML


	if (event.type == sf::Event::MouseMoved)
	{
		sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		if (_button.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
		{
			window.setMouseCursor(cursorHand);
			return true;
		}
		else
			return false;
	}
}

void Button::doButtonAction(int action) //Faire un getter et mettre ceci dans game
{
	switch (action)
	{
	case debugAction:
		printf("Clique %02d\n", _buttonID); //TODO: Transformer en SFML
		break;

	case closeOphidie:
		printf("Fermeture du jeu\n"); //TODO: Replace by real action
		break;

	case startGame:
		printf("Démarrage de la partie\n"); //TODO: Replace by real action
		break;

	case openSettings:
		printf("Ouverture des paramètres\n"); //TODO: Replace by real action
		break;

	case openScoreboard:
		printf("Ouverture du scoreboard\n"); //TODO: Replace by real action
		break;

	case openHTP:
		printf("Ouverture du menu How to play\n"); //TODO: Replace by real action
		break;

	case openHomeMenu:
		printf("Ouverture du homescreen\n"); //TODO: Replace by real action
		break;

	case goToNormalSCR:
		printf("Ouverture du scoreboard normal\n"); //TODO: Replace by real action
		break;

	case goToSurvivalSCR:
		printf("Ouverture du scoreboard survival\n"); //TODO: Replace by real action
		break;

	case goToDeathTrapSCR:
		printf("Ouverture du scoreboard death trap\n"); //TODO: Replace by real action
		break;

	case goToSurviveHellSCR:
		printf("Ouverture du scoreboard survive hell\n"); //TODO: Replace by real action
		break;

	case OpenFile:
		printf("Ouverture d'un fichier\n"); //TODO: Replace by real action
		break;

	default:
		printf("Action doesn't exist !\n"); //TODO: Transformer en SFML
	}
}

void Button::setButtonTexture(int buttonStyle)
{
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
