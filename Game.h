#pragma once

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

  public:
	// Constructor
	Game();

	// Destructor
	~Game();

	// Method
	void play();
	int StartGame();

	// Music management
	void playSound(const std::string& soundPath, float volume);
	void playMusic(const std::string& soundPath, float volume);
	void stopMusic();
	// void showEndScreen();
	// void savePlayerScore(Player player, GameMode mode);

	// Display managment
	void chooseWallpaper(GameMode mode);
	void addWallpaper(const std::string& texture);
	void draw(sf::Text& hungerMeter, Grid& map, Snake& snake);
};