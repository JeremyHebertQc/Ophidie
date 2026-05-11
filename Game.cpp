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

int Game::StartGame()
{
	playSound("startGame.wav", _settings.getSound());
	playMusic("game.wav", _settings.getMusic());
	Grid map(&_window, &_settings);
	map.createMap();
	chooseWallpaper(_settings.getMode());

	sf::Clock moveCooldown;

	sf::Font font;
	if (!font.loadFromFile(FONT_PATH))
		sendError(FileNotOpened);

	sf::Text hungerMeter("100", font, 30);
	hungerMeter.setStyle(sf::Text::Regular);
	hungerMeter.setFillColor(sf::Color::White);
	hungerMeter.setPosition(sf::Vector2f(100.f, 20.f));

	sf::Clock timeLived;
	sf::Clock pauseTimer;

	int hunger = 100,
		timePaused = 0;

	bool isHungry = false;

	Snake snake(&_window, map.getGridOffset());

	Menu pauseMenu(&_window, &_settings);

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
				case sf::Keyboard::Escape:
					pauseTimer.restart();

					//if(pauseMenu.)

					break;
				case sf::Event::Resized:
					_window.clear();
					_window.display();
					break;
				default:
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
				if (isHungry)
					if (snake.getSnakeSize() > 5)
					{
						snake.moveHurting();
						hunger += 50;
					}
					else
						snake.setLiving(false);
				else
					snake.moveForward(false);
				map.updateSnakePosition(snake.getSnakeCoords());
				break;
			case egg:
				snake.moveForward(true);
				playSound("eatingEgg.wav", _settings.getSound());
				map.updateSnakePosition(snake.getSnakeCoords());
				map.placeEgg();

				if (_settings.getMode() % 2)
					hunger += 60;

				break;
			case body:
			case trap:
				snake.setLiving(false);
				playSound("gameOver.wav", _settings.getSound());
				break;
			}

			if (_settings.getMode() % 2)
			{
				hunger = (hunger > ((_settings.getDifficulty() % 4) + 1) ? hunger - ((_settings.getDifficulty() % 4) + 1) : 0);
				hungerMeter.setString(std::to_string(hunger));
				if (hunger <= 0)
					isHungry = true;
				else
					isHungry = false;
			}
		}

		_window.clear();
		draw(hungerMeter, map, snake);
		_window.display();
	}
	stopMusic();

	if (_settings.getMode() % 2)
		return timeLived.getElapsedTime().asMilliseconds();//TODO: add the minus pausedTime
	return snake.getSnakeSize();
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

void Game::chooseWallpaper(GameMode mode)
{
	switch (mode)
	{
	case Normal:
		addWallpaper("wallpaper/ocean.png");
		break;

	case Survival:
		addWallpaper("wallpaper/water.png");
		break;

	case DeathTrap:
		addWallpaper("wallpaper/lava.png");
		break;

	case SurviveHell:
		addWallpaper("wallpaper/hell.png");
		break;

		default:
		break;
	}
}

void Game::addWallpaper(const std::string& texture)
{
	_wallpaper.setScale(static_cast<float>(_window.getSize().x), static_cast<float>(_window.getSize().y));
	_wallpaper.setScale(5.f, 5.f);
	_texture.loadFromFile(GAME_DIR + texture);
	_wallpaper.setTexture(_texture);
}

void Game::draw(sf::Text hungerMeter, Grid map, Snake snake)
{
	_window.draw(_wallpaper);

	if (_settings.getMode() % 2)
	{
		_window.draw(hungerMeter);
	}
	map.renderGrid();
	snake.drawSnake();
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