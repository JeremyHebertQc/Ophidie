#pragma once
/*====================================
Auteurs : Jeremy Hebert, Vincent Gagnon et Felix-Antoine Lacroix
Projet : Ophidie
====================================*/

#include "Settings.h"
#include "Grid.h"
#include "Snake.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Game
{
  private:
	sf::RenderWindow _window;
	Settings _settings;

	// SoundEffect declarations
	sf::SoundBuffer _soundEffectBuffer;
	sf::Sound _soundEffect;

	// Music declarations
	sf::SoundBuffer _musicBuffer;
	sf::Sound _music;

	// Wallpaper declaration
	sf::Sprite _wallpaper;
	sf::Texture _texture;

	// Game
	sf::Text _hungerMeter;
	sf::Clock _moveCooldown;
	sf::Clock _timeLived;
	sf::Clock _pauseTimer;
	int _hunger;
	int _timePaused;
	bool _isHungry;
	Grid _map{&_window, &_settings};
	sf::Font _font;

  public:
	// Constructor
	Game();

	// Destructor
	~Game();

	// Method
	void play();
	int StartGame();
	void initializeGame(Snake& snake);

	// Music management
	void playSound(const std::string& soundPath, float volume);
	void playMusic(const std::string& soundPath, float volume);
	void stopMusic();

	// Display managment
	void chooseWallpaper(GameMode mode);
	void addWallpaper(const std::string& texture);
	void draw(sf::Text& hungerMeter, Grid& map, Snake& snake);
};