#pragma once

#include "Settings.h"

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

  public:
	// Constructor
	Game();

	// Destructor
	~Game();

	// Method
	void play();
	bool StartGame();

	// Music management
	void playSound(const std::string& soundPath, float volume);
	void playMusic(const std::string& soundPath, float volume);
	void stopMusic();
	// void showEndScreen();
	// void savePlayerScore(Player player, GameMode mode);
};