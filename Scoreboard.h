#pragma once
/*====================================
Auteurs : Jeremy Hebert, Vincent Gagnon et Felix-Antoine Lacroix
Projet : Ophidie
====================================*/

#include <string>
#include <SFML/Audio.hpp>

#include "const.h"
#include "Menu.h"

struct Player
{
	std::string _name = "NULL";
	float _score = 0;
};

class Scoreboard
{
private:
	static const std::string _gamemodesPaths[4];
	static const std::string _difficultyPath[8];
	Player _scoreboardData[GameModeTotal][DifficultyTotal][NUMBER_OF_SCORES];

public:
	// Constructor
	Scoreboard();

	// Destructor
	~Scoreboard();

	// Data management
	void loadData();
	void writeData() const;

	// Score management
	std::string getScoreAt(int gamemode, int difficulty, int place);
	bool checkScore(float score, GameMode mode, Difficulty difficulty) const; // Returns true if score is at least in top 10
	void addScore(float score, GameMode mode, Difficulty difficulty, sf::RenderWindow* window); // Adds the score to the scoreboards
	void addScore(float score, std::string name, GameMode mode, Difficulty difficulty); // Adds the score to the scoreboards

	// Display management
	void showMenu(); //Note: Show the menu when selected in main menu
	void showScore(GameMode mode, Difficulty difficulty); //Note: Shows the selected mode
};

// Operator overload
std::fstream& operator<<(std::fstream& file, Player player);
std::fstream& operator>>(std::fstream& file, Player& player);