#include "Game.h"

#include "Grid.h"
#include "Menu.h"
#include "Settings.h"
#include "utils.h"
#ifdef _WIN32
	#include "windows.h"
#endif

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Constructor
Game::Game()
{
	_window.create(sf::VideoMode::getDesktopMode(), "Ophidie");

#ifdef _WIN32
	ShowWindow(_window.getSystemHandle(), SW_MAXIMIZE); //NOTE: Maximize the window if we are on Windows, otherwise just use the desktop resolution size
#endif

	_window.setActive(true);
	_window.setFramerateLimit(60);

	sf::Image icon;
	if (icon.loadFromFile("assets/favicon/ophidie.png"))
	{
		_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	}
}

// Destructor
Game::~Game()
{
	_window.close();
}

// Method
void Game::play()
{
	Menu menu(&_window, &_settings);

	while (_window.isOpen())
	{
		if (!menu.loadHomeMenu())
			_window.close();
		else
			StartGame();
	}
}

bool Game::StartGame()
{
	playSound("startGame.wav", _settings.getSound());
	playMusic("game.wav", _settings.getMusic());
	Grid map(&_window, &_settings);
	map.createMap();

	sf::Clock moveCooldown;

	Snake snake(&_window, map.getGridOffset());

	bool eat = false;
	bool chain = true;

	while (snake.isLiving())
	{
		sf::Event event;
		while (_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				_window.close();
			case sf::Event::KeyPressed:
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Left:
					if (_settings.getArrow())
						snake.setHeadDirection(Left);
					break;
				case sf::Keyboard::A:
					if (!_settings.getArrow())
						snake.setHeadDirection(Left);
					break;
				case sf::Keyboard::Right:
					if (_settings.getArrow())
						snake.setHeadDirection(Right);
					break;
				case sf::Keyboard::D:
					if (!_settings.getArrow())
						snake.setHeadDirection(Right);
					break;
				case sf::Keyboard::Up:
					if (_settings.getArrow())
						snake.setHeadDirection(Up);
					break;
				case sf::Keyboard::W:
					if (!_settings.getArrow())
						snake.setHeadDirection(Up);
					break;
				case sf::Keyboard::Down:
					if (_settings.getArrow())
						snake.setHeadDirection(Down);
					break;
				case sf::Keyboard::S:
					if (!_settings.getArrow())
						snake.setHeadDirection(Down);
					break;
				case sf::Keyboard::Delete: //Note: quitout midgame
					snake.setLiving(false);
					break;
				}
				break;
			}
		}

		if (moveCooldown.getElapsedTime().asMilliseconds() > 500 / ((_settings.getDifficulty() % 4) + 1))
		{
			moveCooldown.restart();

			switch (map.getTileAt(snake.getDestinationCoord()))
			{
			case air:
				snake.moveForward(false);
				map.updateSnakePosition(snake.getSnakeCoords());
				break;
			case egg:
				snake.moveForward(true);
				playSound("eatingEgg.wav", _settings.getSound());
				map.updateSnakePosition(snake.getSnakeCoords());
				map.placeEgg();
				break;
			case body:
			case trap:
				snake.setLiving(false);
				playSound("gameOver.wav", _settings.getSound());
				break;
			}
		}

		_window.clear();
		map.renderGrid();
		snake.drawSnake();
		_window.display();
	}
	stopMusic();
	return false;
}

void Game::playSound(const std::string& soundPath, float volume)
{
	if (!_soundEffectBuffer.loadFromFile(SOUND_DIR + soundPath))
	{
		sendError(FileNotOpened);
		return;
	}

	_soundEffect.setBuffer(_soundEffectBuffer);
	_soundEffect.setLoop(false);
	_soundEffect.setVolume(volume);
	_soundEffect.play();
}

void Game::playMusic(const std::string& soundPath, float volume)
{
	if (!_musicBuffer.loadFromFile(MUSIC_DIR + soundPath))
	{
		sendError(FileNotOpened);
		return;
	}

	_music.setBuffer(_musicBuffer);
	_music.setLoop(true);
	_music.setVolume(volume);
	_music.play();
}

void Game::stopMusic()
{
	_music.stop();
}

// void Game::showEndScreen()
// {
//
// }
//
// void Game::savePlayerScore(Player player, GameMode mode)
// {
//
// }