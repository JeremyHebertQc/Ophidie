/*====================================
Auteurs : Jeremy Hebert, Vincent Gagnon et Felix-Antoine Lacroix
Projet : Ophidie
====================================*/

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

	if (!_font.loadFromFile(FONT_PATH))
		sendError(FileNotOpened);
	_hungerMeter.setString("100");
	_hungerMeter.setFont(_font);
	_hungerMeter.setCharacterSize(30);
	_hungerMeter.setStyle(sf::Text::Regular);
	_hungerMeter.setFillColor(sf::Color::White);
	sf::FloatRect bounds = _hungerMeter.getLocalBounds();
	_hungerMeter.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
	_hungerMeter.setPosition(sf::Vector2f(_window.getSize().x / 2.f + 200, 20.f));

	_hunger = 100;
	_timePaused = 0;
	_isHungry = false;
}

// Destructor
Game::~Game()
{
	_window.close();
}

// Method
void Game::play()
{

	//Scoreboard my;
	//my.addScore(12.0f, (GameMode)0, (Difficulty)2, &_window);
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
	Snake snake(&_window, _map.getGridOffset());
	Menu pauseMenu(&_window, &_settings);
	Menu gameOverMenu(&_window, &_settings);
	float score = 0;
	sf::Text scoreMeter("0", _font, 30);
	Scoreboard scoreboard;

	sf::Clock scoreTimer;
	scoreMeter.setStyle(sf::Text::Regular);
	scoreMeter.setFillColor(sf::Color::White);
	sf::FloatRect bounds = scoreMeter.getLocalBounds();
	scoreMeter.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
	if (_settings.getMode() % 2)
		scoreMeter.setPosition(sf::Vector2f(_window.getSize().x / 2.f - 200, 20.f));
	else
		scoreMeter.setPosition(sf::Vector2f(_window.getSize().x / 2.f, 20.f));

	do
	{
		scoreTimer.restart();
		scoreMeter.setString("0");
		score = 0;
		initializeGame(snake);
		while (snake.isLiving())
		{
			sf::Event event;
			while (_window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					_window.close();
					break;

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
						_pauseTimer.restart();

						if (pauseMenu.loadPauseMenu())
							snake.setLiving(false);

						_timePaused += _pauseTimer.getElapsedTime().asMicroseconds();
						break;

					case sf::Event::Resized:
						_window.display();
						break;

					default:
						break;
					}
					break;
				}
			}

			if (_moveCooldown.getElapsedTime().asMilliseconds() > 500 / ((_settings.getDifficulty() % 4) + 1))
			{
				_moveCooldown.restart();

				switch (_map.getTileAt(snake.getDestinationCoord()))
				{
				case Air:
					if (_isHungry)
						if (snake.getSnakeSize() > 5)
						{
							snake.moveHurting();
							_hunger += 50;
							playSound("hungry.wav", _settings.getSound());
						}
						else
						{
							playSound("gameOver.wav", _settings.getSound());
							snake.setLiving(false);
						}
					else
						snake.moveForward(false);
					_map.updateSnakePosition(snake.getSnakeCoords());
					break;

				case WhiteEgg:
				case BrownEgg:
				case BlueEgg:
				case GreenEgg:
				case RedEgg:
					snake.moveForward(true);
					playSound("eatingEgg.wav", _settings.getSound());
					_map.updateSnakePosition(snake.getSnakeCoords());
					_map.placeEgg();

				if (_settings.getMode() % 2)
					_hunger += 60;
				else
					score += 100;
				break;

			case Body:
			case Trap:
				snake.setLiving(false);
				playSound("gameOver.wav", _settings.getSound());
				break;

			}

			if (_settings.getMode() % 2)
			{
				_hunger = (_hunger > ((_settings.getDifficulty() % 4) + 1) ? _hunger - ((_settings.getDifficulty() % 4) + 1) : 0);
				_hungerMeter.setString(std::to_string(_hunger));
				if (_hunger <= 0)
					_isHungry = true;
				else
					_isHungry = false;
			}
		}
			if (_settings.getMode() % 2)
			{
				score = (int(scoreTimer.getElapsedTime().asMicroseconds()) - _timePaused) / 10000;
			}

			scoreMeter.setString(std::to_string(int(score / 100) * 100));
			draw(_hungerMeter, _map, snake);
			_window.draw(scoreMeter);
			_window.display();
	}
	stopMusic();
		if (scoreboard.checkScore(score, _settings.getMode(),_settings.getDifficulty()))
		{
			bool nameFound = false;
			std::string name;
			sf::Text saveText("New highScore! Enter your name", _font, 30);
			saveText.setFillColor({255,255,255});
			saveText.setPosition(200, 200);
			while (!nameFound)
			{
				sf::Event event;
				while (_window.pollEvent(event)) {
					if (!nameFound && event.type == sf::Event::TextEntered) {
						if (event.text.unicode == 8) { // Backspace
							if (!name.empty())
								name.pop_back();
						} else if (event.text.unicode == 13) { // Enter
							nameFound = true;
						} else if (event.text.unicode >= 32 && event.text.unicode < 127) { // any valid
							name += (char)(event.text.unicode);
						}
					}
				}

				scoreMeter.setString(std::to_string(int(score / 100) * 100));
				draw(_hungerMeter, _map, snake);
				_window.draw(scoreMeter);
				_window.draw(saveText);
				_window.display();


			}
			scoreboard.addScore(score, name, _settings.getMode(), _settings.getDifficulty());
			scoreboard.writeData();

		}


		//	return _timeLived.getElapsedTime().asMilliseconds(); // TODO: add the minus pausedTime

		//	return _timeLived.getElapsedTime().asMilliseconds(); // TODO: add the minus pausedTime

		gameOverMenu.initGameOverMenu();
	} while (gameOverMenu.loadGameOverMenu());
	scoreboard.writeData();
	return score;
}

void Game::initializeGame(Snake& snake)
{
	_moveCooldown.restart();
	_timeLived.restart();
	_pauseTimer.restart();
	_map.createMap();
	chooseWallpaper(_settings.getMode());
	playSound("startGame.wav", _settings.getSound());
	playMusic("game.wav", _settings.getMusic());

	_hunger = 100;
	_timePaused = 0;
	_isHungry = false;
	snake.initializeSnake();
}

// Music management
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

// Display managment
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

void Game::draw(sf::Text& hungerMeter, Grid& map, Snake& snake)
{
	_window.draw(_wallpaper);

	if (_settings.getMode() % 2)
	{
		_window.draw(_hungerMeter);
	}
	_map.renderGrid();
	snake.drawSnake();
}