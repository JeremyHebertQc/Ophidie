#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cassert>

#include "Menu.h"
#include "Button.h"

// Constructor
Menu::Menu(sf::RenderWindow& window)
{
	_wallpaper.setScale(window.getSize().x, window.getSize().y);
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
float Menu::getCenterPositionX(sf::RenderWindow& window) const
{
	return (window.getSize().x / 2.f);
}

float Menu::getCenterPositionY(sf::RenderWindow& window) const
{
	return (window.getSize().y / 2.f);
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
int Menu::isButtonPressed(sf::Event event, sf::RenderWindow& window)
{
	if (_buttons.size() > EMPTY)
		for (int i = 0; i < _buttons.size(); i++)
		{
			if (_buttons[i]->isButtonPressed(event, window) != -1)
				return _buttons[i]->getAction();
		}

	return -1;
}

void Menu::isButtonHover(sf::Event event, sf::RenderWindow& window)
{
	if (_buttons.size() > EMPTY)
		for (int i = 0; i < _buttons.size(); i++)
			_buttons[i]->isButtonHover(event, window);
}

int Menu::isAction(sf::RenderWindow& window)
{
	static sf::Cursor cursorArrow;
	if (!cursorArrow.loadFromSystem(sf::Cursor::Arrow))
		printf("ERROR: Cursor doesn't load!\n"); //TODO: Transformer en SFML

	sf::Event event;
	while (window.pollEvent(event))
	{
		int action;
		switch (event.type)
		{
		case sf::Event::Closed:
			return closeOphidie;

		case sf::Event::MouseButtonPressed:
		case sf::Event::MouseButtonReleased:
			action = isButtonPressed(event, window);
			window.clear();
			if (action != -1)
				return action;

		case sf::Event::MouseMoved:
			window.setMouseCursor(cursorArrow);
			isButtonHover(event, window);
			break;

		case sf::Event::Resized:
			window.clear();
			window.display();
			break;

		default:
			break;
		}
	}

	return -1;
}

// Music management
void Menu::playMusic(std::string soundFileName)
{
	if (!_musicBuffer.loadFromFile(SOUND_PATH + soundFileName))
	{
		printf("ERROR: Sound can't load !"); //NOTE: Postmerge, créer un tag pour le enum des codes d'erreur et le sync + ne pas exit, c'est juste de la musique...
		return;
	}

	_musicSound.setBuffer(_musicBuffer);
	_musicSound.setLoop(true);
	_musicSound.setVolume(50); //TODO: Utiliser les settings des paramètres
	_musicSound.play();
}

void Menu::stopMusic()
{
	_musicSound.stop();
}

// Vectors management
void Menu::addButton(const int action, const std::string text, const int buttonStyle, const float scale, const sf::Vector2f position)
{
	_buttons.push_back(new Button(action, text, buttonStyle, scale, position));
}

void Menu::addText(const int fontSize, const std::string text, const sf::Vector2f position, int r, int g, int b)
{
	if (!_font.loadFromFile(FONT_PATH))
		exit(1);  //NOTE: Postmerge, créer un tag pour le enum des codes d'erreur et le sync

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

// Drawing management
void Menu::drawButtons(sf::RenderWindow& window)
{

	for (int i = 0; i < _buttons.size(); i++)
	{
		_buttons[i]->draw(window);
	}
}

void Menu::drawTexts(sf::RenderWindow& window)
{
	for (int i = 0; i < _texts.size(); i++)
	{
		drawText(window, _texts.at(i));
	}
}

void Menu::drawText(sf::RenderWindow& window, sf::Text text)
{
	window.draw(text);
}

void Menu::drawSprites(sf::RenderWindow& window)
{
	for (int i = 0; i < _sprites.size(); i++)
	{
		drawSprite(window, _sprites.at(i));
	}
}

void Menu::drawSprite(sf::RenderWindow& window, sf::Sprite* sprite)
{
	window.draw(*sprite);
}

void Menu::draw(sf::RenderWindow& window)
{
	window.draw(_wallpaper);
	drawButtons(window);
	drawTexts(window);
	drawSprites(window);
}

// Menu initiation
void Menu::initHomeMenu(sf::RenderWindow& window)
{
	addButton(startGame, "Play", bigButton, 0.5f, sf::Vector2f(getCenterPositionX(window), 300.f));
	addButton(openHTP, "How to play?", bigButton, 0.5f, sf::Vector2f(getCenterPositionX(window), 450.f));
	addButton(openScoreboard, "Scoreboard", bigButton, 0.5f, sf::Vector2f(getCenterPositionX(window), 600.f));
	addButton(openSettings, "Settings", littleButton, 0.5f, sf::Vector2f(getCenterPositionX(window) - 130.f, 750.f));
	addButton(closeOphidie, "Quit", littleButton, 0.5f, sf::Vector2f(getCenterPositionX(window) + 130.f, 750.f));
	addText(12, "Credits: Jérémy Hébert, Vincent Gagnon, Félix-Antoine Lacroix", sf::Vector2f(25.f, window.getSize().y - 50.f), 61, 24, 79);
	addSprite(1.f, sf::Vector2f(getCenterPositionX(window), 100.f), LOGO_PATH);
}

void Menu::initSettingsMenu(sf::RenderWindow& window)
{
	//TODO: Build it
}

void Menu::initHowToPlayMenu(sf::RenderWindow& window)
{
	//TODO: Build it
}

void Menu::initStartMenu(sf::RenderWindow& window)
{
	//TODO: Build it
}

void Menu::initScoreboardMenu(sf::RenderWindow& window)
{
	//TODO: Build it
}

// Menu loading
bool Menu::loadHomeMenu(sf::RenderWindow& window)
{
	static bool isCreated = false;
	if (isCreated == false)
	{
		initHomeMenu(window);
		isCreated = true;
	}

	playMusic("menuMusic.wav");

	while (true)
	{
		window.clear();
		draw(window);
		window.display();

		switch (isAction(window))
		{
		case startGame:
			loadStartMenu(window);
			stopMusic();
			return true;

		case closeOphidie:
			stopMusic();
			return false;
			
		case openHTP:
			loadHowToPlayMenu(window);
			break;

		case openScoreboard:
			loadScoreboardMenu(window);
			break;
			
		case openSettings:
			loadSettingsMenu(window);
			break;

		default:
		case -1:
			break;
		}
	}
}

void Menu::loadSettingsMenu(sf::RenderWindow& window) 
{
	addSprite(1.0f, sf::Vector2f(getCenterPositionX(window), getCenterPositionY(window)), "assets/menu/menuBackground.png");

	//TODO: Build it
}

void Menu::loadHowToPlayMenu(sf::RenderWindow& window)
{
	addSprite(1.0f, sf::Vector2f(getCenterPositionX(window), getCenterPositionY(window)), "assets/menu/menuBackground.png");

	//TODO: Build it
}

void Menu::loadStartMenu(sf::RenderWindow& window)
{
	addSprite(1.0f, sf::Vector2f(getCenterPositionX(window), getCenterPositionY(window)), "assets/menu/menuBackground.png");

	//TODO: Build it
}

void Menu::loadScoreboardMenu(sf::RenderWindow& window)
{
	addSprite(1.0f, sf::Vector2f(getCenterPositionX(window), getCenterPositionY(window)), "assets/menu/menuBackground.png");

	//TODO: Build it
}

void Menu::loadScoreboardMenu(sf::RenderWindow& window, int scoreboardType)
{
	switch (scoreboardType)
	{
	case goToNormalSCR:
		addSprite(1.0f, sf::Vector2f(getCenterPositionX(window), getCenterPositionY(window)), "assets/menu/menuBackground.png");

		//TODO: Build it
		break;

	case goToSurvivalSCR:
		addSprite(1.0f, sf::Vector2f(getCenterPositionX(window), getCenterPositionY(window)), "assets/menu/menuBackground.png");

		//TODO: Build it
		break;

	case goToDeathTrapSCR:
		addSprite(1.0f, sf::Vector2f(getCenterPositionX(window), getCenterPositionY(window)), "assets/menu/menuBackground.png");

		//TODO: Build it
		break;

	case goToSurviveHellSCR:
		addSprite(1.0f, sf::Vector2f(getCenterPositionX(window), getCenterPositionY(window)), "assets/menu/menuBackground.png");

		//TODO: Build it
		break;

	default:
		break;
	}
}