#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cassert>

#include "Menu.h"
#include "Button.h"

// Constructeurs
Menu::Menu(sf::RenderWindow& window)
{
	_wallpaper.setScale(window.getSize().x, window.getSize().y);
	_wallpaper.setScale(1.9f, 1.15f);
	_texture.loadFromFile("assets/menu/menuBackground.png");
	_wallpaper.setTexture(_texture);
}

// Destructeur
Menu::~Menu()
{
	// Destruction des boutons
	for (Button* b : _buttons)
		delete b;
		
	_buttons.clear();

	_texts.clear();
}

// Getters
std::vector<Button*> Menu::getButtons()
{
	return _buttons;
}

std::vector<sf::Text> Menu::getTexts()
{
	return _texts;
}

// Méthodes
void Menu::addButton(const unsigned int buttonID, const int action, const std::string text, const int buttonStyle, const float scale, const sf::Vector2f position)
{
	_buttons.push_back(new Button(buttonID, action, text, buttonStyle, scale, position));
}

int Menu::isButtonPressed(sf::Event event, sf::RenderWindow& window)
{
	if(_buttons.size() > 0)
		for (int i = 0; i < _buttons.size(); i++)
		{
			if (_buttons[i]->isButtonPressed(event, window) != -1)
				return _buttons[i]->getAction();
		}

	return -1;
}

void Menu::isButtonHover(sf::Event event, sf::RenderWindow& window)
{
	if (_buttons.size() > 0)
		for (int i = 0; i < _buttons.size(); i++)
			_buttons[i]->isButtonHover(event, window);
}

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

void Menu::drawSprites(sf::RenderWindow& window)
{
	for (int i = 0; i < _sprites.size(); i++)
	{
		drawSprite(window, _sprites.at(i));
	}
}

void Menu::drawText(sf::RenderWindow& window, sf::Text text)
{
	window.draw(text);
}

void Menu::drawSprite(sf::RenderWindow& window, sf::Sprite* sprite)
{
	window.draw(*sprite);
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

bool Menu::initHomMenu(sf::RenderWindow& window)
{
	static bool isCreated = false;
	if (isCreated == false)
	{
		float centerPositionX = window.getSize().x / 2.0f;
		addButton(0, startGame, "Play", bigButton, 0.5f, sf::Vector2f(centerPositionX, 300.0f));
		addButton(1, openHTP, "How to play?", bigButton, 0.5f, sf::Vector2f(centerPositionX, 450.0f));
		addButton(2, openScoreboard, "Scoreboard", bigButton, 0.5f, sf::Vector2f(centerPositionX, 600.0f));
		addButton(3, openSettings, "Settings", littleButton, 0.5f, sf::Vector2f(centerPositionX - 130.0f, 750.0f));
		addButton(4, closeOphidie, "Quit", littleButton, 0.5f, sf::Vector2f(centerPositionX + 130.0f, 750.0f));
		addText("Credits: Jérémy Hébert, Vincent Gagnon, Félix-Antoine Lacroix", sf::Vector2f(25.0f, window.getSize().y - 50.0f), 12, 61, 24, 79);
		addSprite(0.5f, sf::Vector2f(centerPositionX, 100.0f), "assets/menu/menuBackground.png");
		isCreated = true;
	}
	return 1;
}

bool Menu::loadHomeMenu(sf::RenderWindow& window)
{
	if (!initHomMenu(window))
		exit(1); //TODO: Add error code

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

void Menu::loadSettingsMenu(sf::RenderWindow& window) //TODO: Build it
{
	printf("Settings Menu");
}

void Menu::loadScoreboardMenu(sf::RenderWindow& window) //TODO: Build it
{
	printf("Scoreboard Menu");
}

void Menu::loadScoreboardMenu(sf::RenderWindow& window, int scoreboardType) //TODO: Build it
{
	switch (scoreboardType)
	{
	case goToNormalSCR:
		printf("Normal SCR");
		break;

	case goToSurvivalSCR:
		printf("Survival SCR");
		break;

	case goToDeathTrapSCR:
		printf("Death Trap SCR");
		break;

	case goToSurviveHellSCR:
		printf("Survive Hell SCR");
		break;

	default:
		break;
	}
}

void Menu::loadHowToPlayMenu(sf::RenderWindow& window) //TODO: Build it
{
	printf("How to play");
}

void Menu::loadStartMenu(sf::RenderWindow& window) //TODO: Build it
{
	printf("Start menu. Choose somes options");
}

void Menu::playMusic(std::string soundPath)
{
	if (!_musicBuffer.loadFromFile(SOUND_PATH + soundPath))
	{
		printf("ERROR: Sound can't load !"); //NOTE: Postmerge, créer un tag pour le enum des codes d'erreur et le sync + ne pas exit, c'est juste de la musique...
		return;
	}

	_musicSound.setBuffer(_musicBuffer);
	_musicSound.setLoop(true);
	_musicSound.play();
}

void Menu::stopMusic()
{
	_musicSound.stop();
}

void Menu::addText(const std::string text, const sf::Vector2f position, const int fontSize, int r, int g, int b)
{
	if (!_font.loadFromFile(FONT_PATH))
		exit(1);  //NOTE: Postmerge, créer un tag pour le enum des codes d'erreur et le sync

	_texts.push_back(sf::Text(text, _font, fontSize));

	_texts.back().setStyle(sf::Text::Regular);
	setTextColor(r, g, b, _texts.back());
	_texts.back().setPosition(position);
}

void Menu::addSprite(const float scale, const sf::Vector2f position, const std::string texture)
{
	_sprites.push_back(new sf::Sprite(_sprite));

	_texture.loadFromFile(texture);
	_sprites.back()->setScale(sf::Vector2f(scale, scale));
	_sprites.back()->setOrigin(_texture.getSize().x / 2.f, _texture.getSize().y / 2.f);
	_sprites.back()->setPosition(position);
}

void Menu::setPosition(sf::Vector2f position)
{
	_position = position;
}

void Menu::setText(const sf::Text& text)
{
	_text = text;
}

void Menu::setTextColor(int r, int g, int b, sf::Text& text)
{
	assert((r >= 0 && r <= 255) && (g >= 0 && g <= 255) && (b >= 0 && b <= 255));

	_textColor.r = r;
	_textColor.g = g;
	_textColor.b = b;

	text.setFillColor(_textColor);
}

void Menu::setScale(sf::Vector2f scale)
{
	_scale = scale;
}


void Menu::draw(sf::RenderWindow& window)
{
	window.draw(_wallpaper);
	drawButtons(window);
	drawTexts(window);
	drawSprites(window);
}