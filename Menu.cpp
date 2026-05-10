#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cassert>

#include "Menu.h"
#include "Button.h"
#include "utils.h"

// Constructor
Menu::Menu(sf::RenderWindow* window, Settings* settings)
{
	_settings = settings;
	_window = window;
	_isMenuInit = false;
	_isSubmenuInit = false;
	_wallpaper.setScale(static_cast<float>(_window->getSize().x), static_cast<float>(_window->getSize().y));
	_wallpaper.setScale(5.f, 5.f);
	addTexture(WALLPAPER_PATH);
	_wallpaper.setTexture(*_textures.back());
}

// Destructor
Menu::~Menu()
{
	for (Button* b : _buttons)
		delete b;

	_buttons.clear();
	_sprites.clear();
	_textures.clear();
	_texts.clear();
}

// Getters
float Menu::getCenterPositionX() const
{
	return (_window->getSize().x / 2.f);
}

float Menu::getCenterPositionY() const
{
	return (_window->getSize().y / 2.f);
}

// Setter
void Menu::setTextColor(int r, int g, int b, sf::Text& text)
{
	assert((r >= 0 && r <= 255) && (g >= 0 && g <= 255) && (b >= 0 && b <= 255));

	_textColor.r = r;
	_textColor.g = g;
	_textColor.b = b;

	text.setFillColor(_textColor);
}

// Event management
int Menu::isButtonPressed(sf::Event event)
{
	if (_buttons.size() > EMPTY)
		for (int i = 0; i < _buttons.size(); i++)
		{
			if (_buttons[i]->isButtonPressed(event) != -1)
				return _buttons.at(i)->getAction();
		}

	return -1;
}

void Menu::isButtonHover(sf::Event event)
{
	if (_buttons.size() > EMPTY)
		for (int i = 0; i < _buttons.size(); i++)
			_buttons[i]->isButtonHover(event);
}

int Menu::isAction()
{
	static sf::Cursor cursorArrow;
	if (!cursorArrow.loadFromSystem(sf::Cursor::Arrow))
		sendError(FILE_NOT_OPENED);

	sf::Event event;
	while (_window->pollEvent(event))
	{
		int action;
		switch (event.type)
		{
		case sf::Event::Closed:
			return closeOphidie;

		case sf::Event::KeyReleased:
			if (event.key.code == sf::Keyboard::Escape)
				return closeOphidie;

		case sf::Event::MouseButtonPressed:
		case sf::Event::MouseButtonReleased:
			action = isButtonPressed(event);
			_window->clear();
			if (action != -1)
				return action;

		case sf::Event::MouseMoved:
			_window->setMouseCursor(cursorArrow);
			isButtonHover(event);
			break;

		case sf::Event::Resized:
			_window->clear();
			_window->display();
			break;

		default:
			break;
		}
	}

	return -1;
}

// Music management
void Menu::playMusic(std::string soundFileName, float volume)
{
	if (!_musicBuffer.loadFromFile(SOUND_PATH + soundFileName))
	{
		sendError(FILE_NOT_OPENED);
		return;
	}

	_musicSound.setBuffer(_musicBuffer);
	_musicSound.setLoop(true);
	_musicSound.setVolume(volume);
	_musicSound.play();
}

void Menu::stopMusic()
{
	_musicSound.stop();
}

// Vectors management
void Menu::addButton(const int action, const std::string text, const int buttonStyle, const float scale, const sf::Vector2f position)
{
	_buttons.push_back(new Button(_window, _settings, action, text, buttonStyle, scale, position));
}

void Menu::addText(const int fontSize, const std::string text, const sf::Vector2f position, int r, int g, int b)
{
	if (!_font.loadFromFile(FONT_PATH))
		sendError(FILE_NOT_OPENED);

	_texts.push_back(sf::Text(text, _font, fontSize));

	_texts.back().setStyle(sf::Text::Regular);
	setTextColor(r, g, b, _texts.back());
	_texts.back().setPosition(position);
}

void Menu::addTexture(const std::string texture)
{
	_texture.loadFromFile(texture);
	_textures.push_back(new sf::Texture(_texture));
}

void Menu::addSprite(const float scale, const sf::Vector2f position, const std::string texture)
{
	addTexture(texture);
	_sprites.push_back(new sf::Sprite(*_textures.back()));

	_sprites.back()->setScale(sf::Vector2f(scale, scale));
	_sprites.back()->setOrigin(_textures.back()->getSize().x / 2.f, _textures.back()->getSize().y / 2.f);
	_sprites.back()->setPosition(position);
}

void Menu::clearVectors()
{
	_buttons.clear();
	_sprites.clear();
	_texts.clear();
}

// Drawing management
void Menu::drawButtons()
{

	for (int i = 0; i < _buttons.size(); i++)
	{
		_buttons.at(i)->draw();
	}
}

void Menu::drawTexts()
{
	for (int i = 0; i < _texts.size(); i++)
	{
		drawText(_texts.at(i));
	}
}

void Menu::drawText(sf::Text text)
{
	_window->draw(text);
}

void Menu::drawSprites()
{
	for (int i = 0; i < _sprites.size(); i++)
	{
		drawSprite(_sprites.at(i));
	}
}

void Menu::drawSprite(sf::Sprite* sprite)
{
	_window->draw(*sprite);
}

void Menu::draw()
{
	_window->draw(_wallpaper);

	drawSprites();
	drawTexts();
	drawButtons();
}

// Menu initiation
void Menu::initHomeMenu()
{
	addButton(startGame, "Play", bigButton, 0.5f, sf::Vector2f(getCenterPositionX(), 300.f));
	addButton(openHTP, "How to play?", bigButton, 0.5f, sf::Vector2f(getCenterPositionX(), 450.f));
	addButton(openScoreboard, "Scoreboard", bigButton, 0.5f, sf::Vector2f(getCenterPositionX(), 600.f));
	addButton(openSettings, "Settings", littleButton, 0.5f, sf::Vector2f(getCenterPositionX() - 130.f, 750.f));
	addButton(closeOphidie, "Quit", littleButton, 0.5f, sf::Vector2f(getCenterPositionX() + 130.f, 750.f));
	addText(12, "Credits: Jérémy Hébert, Vincent Gagnon, Félix-Antoine Lacroix & Nathan Bricault", sf::Vector2f(_window->getSize().y - 0.97*  _window->getSize().y, _window->getSize().y - 0.05*  _window->getSize().y), 61, 24, 79);
	addSprite(1.f, sf::Vector2f(getCenterPositionX(), 100.f), LOGO_PATH);
}

void Menu::initSettingsMenu()
{
	addSprite(1.f, sf::Vector2f(getCenterPositionX(), getCenterPositionY()), "assets/menu/menuBackground.png");

	//TODO: Build it
}

void Menu::initHowToPlayMenu()
{
	addSprite(1.f, sf::Vector2f(getCenterPositionX(), getCenterPositionY()), "assets/menu/menuBackground.png");

	//TODO: Build it
}

void Menu::initStartMenu()
{
	addSprite(1.f, sf::Vector2f(getCenterPositionX(), getCenterPositionY()), "assets/menu/menuBackground.png");
	addButton(closeSubmenu, "", yesButton, 0.5f, sf::Vector2f(getCenterPositionX(), 500.f));

	//TODO: Build it
}

void Menu::initScoreboardMenu()
{
	addSprite(1.f, sf::Vector2f(getCenterPositionX(), getCenterPositionY()), "assets/menu/menuBackground.png");

	//TODO: Build it
}

// Menu loading
bool Menu::loadHomeMenu()
{
	_isMenuInit = false;
	_isSubmenuInit = false;
	playMusic("menuMusic.wav", _settings->getMusic());

	while (true)
	{
		if (_isMenuInit == false)
		{
			initHomeMenu();
			_isMenuInit = true;
		}

		_window->clear();
		draw();
		_window->display();

		switch (isAction())
		{
		case startGame:
			clearVectors();
			if (_isSubmenuInit == false)
			{
				initStartMenu();
				_isSubmenuInit = true;
			}

			while (loadStartMenu())
				;
			_isSubmenuInit = false;
			clearVectors();

			stopMusic();
			return true;

		case closeOphidie:
			stopMusic();
			return false;

		case openHTP:
			clearVectors();

			if (_isSubmenuInit == false)
			{
				initHowToPlayMenu();
				_isSubmenuInit = true;
			}

			_isMenuInit = false;

			while (loadHowToPlayMenu())
				;

			_isSubmenuInit = false;
			clearVectors();
			break;

		case openScoreboard:
			loadScoreboardMenu();
			clearVectors();
			break;

		case openSettings:
			loadSettingsMenu();
			clearVectors();
			break;

		default:
		case -1:
			break;
		}
	}
}

bool Menu::loadSettingsMenu()
{
	initSettingsMenu();

	//TODO: Build it

	//switch (isAction(window))
	//{
	//case closeHTP:
	//	return false;
	//default:
	//	return true;
	//}
	return true;
}

bool Menu::loadHowToPlayMenu()
{
	initHowToPlayMenu();

	//TODO: Build it

	return true;
}

bool Menu::loadStartMenu()
{
	initStartMenu();

	_window->clear();
	draw();
	_window->display();

	switch (isAction())
	{
	case closeSubmenu:
		return false;
	default:
		return true;
	}

	// TODO: Build it
}

bool Menu::loadScoreboardMenu()
{
	initScoreboardMenu();

	//TODO: Build it

	return true;
}

bool Menu::loadScoreboardMenu(int scoreboardType)
{
	switch (scoreboardType)
	{
	case goToNormalSCR:
		initScoreboardMenu();

		//TODO: Build it
		break;

	case goToSurvivalSCR:
		initScoreboardMenu();

		//TODO: Build it
		break;

	case goToDeathTrapSCR:
		initScoreboardMenu();

		//TODO: Build it
		break;

	case goToSurviveHellSCR:
		initScoreboardMenu();

		//TODO: Build it
		break;

	default:
		break;
	}

	return true;
}