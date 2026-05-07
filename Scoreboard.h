/*====================================
Auteur : Félix-Antoine Lacroix
Projet : Ophidie
====================================*/

#pragma once
#include <string>
#include <SFML/Graphics.hpp>
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
	static const std::string filePaths[4];
	Player _scoreboardData[4][NUMBER_OF_SCORES];

public:
	// Constructeur
	Scoreboard();

	// Destructeur
	~Scoreboard();

	// Gestion des data
	void loadData();
	void writeData() const;

	// Gestion du score
	bool checkScore(float score, GameMode mode) const; // Returns true if score is at least in top 10
	void addScore(float score, std::string name, GameMode mode); // Adds the score to the scoreboards

	// Affichage
	void showMenu(); // Show the menu when selected in main menu
	void showScore(GameMode mode); // Shows the selected mode
};

// Surcharge des opérateurs
std::fstream& operator<<(std::fstream& file, Player player);
std::fstream& operator>>(std::fstream& file, Player& player);