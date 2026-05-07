/*====================================
Auteur : Félix-Antoine Lacroix
Projet : Ophidie
====================================*/
#include <fstream>
#include <iostream> // TODO: Switch to SFML
#include "Scoreboard.h"

#include "utils.h"

const std::string Scoreboard::gamemodesPaths[] =
{
	SCOREBOARD_FILEPATH + "NORMAL",
	SCOREBOARD_FILEPATH + "SURVIVAL",
	SCOREBOARD_FILEPATH + "DEATH_TRAP",
	SCOREBOARD_FILEPATH + "SURVIVE_HELL"
};
const std::string Scoreboard::difficultyPath[] =
{
	"BABY.txt",
	"EZ.txt",
	"MEDIUM_RARE.txt",
	"MEDIUM.txt",
	"HARD.txt",
	"HARDER.txt",
	"TOO_HARD.txt",
	"HARDCORE.txt"
};

// Constructeur
Scoreboard::Scoreboard()
{
	loadData();
}

// Destructeur
Scoreboard::~Scoreboard()
{
}

// Gestion des data
void Scoreboard::loadData()
{
	std::fstream file;
	std::string path;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++) {

			path.clear();

			path.append(gamemodesPaths[i]);
#ifdef WIN32
path.append("\\");
#else
path.append("/");
#endif
			path.append(difficultyPath[j]);

			//std::cout << "opened : "<< path << std::endl;

			openFile(file, path, true);
			for (int k = 0; k < NUMBER_OF_SCORES; k++)
			{
				if (file.eof())
					break;
				file >> _scoreboardData[i][j][k];
			}
			file.close();
		}
	}
}

void Scoreboard::writeData() const
{
std::fstream file;
	std::string path;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++) {

			path.clear();

			path.append(gamemodesPaths[i]);
#ifdef WIN32
path.append("\\");
#else
path.append("/");
#endif
			path.append(difficultyPath[j]);

			//std::cout << "opened : "<< path << std::endl;

			openFile(file, path, false);

			for (int k = 0; k < NUMBER_OF_SCORES; k++)
			{
				file << _scoreboardData[i][j][k];
			}
			file.close();
		}
	}
}

// Gestion du score
bool Scoreboard::checkScore(float score, GameMode mode, Difficulty difficulty) const
{
	assert(score >= 0);
	assert(mode >= 0 || mode < total);

	if (score > _scoreboardData[mode][difficulty][9]._score)
		return true;
	return false;
}

void Scoreboard::addScore(float score, std::string name, GameMode mode, Difficulty difficulty)
{
<<<<<<< felix-game
	assert(mode >= 0 || mode < GameModeTotal);
	assert(score >= _scoreboardData[mode][difficulty][9]._score);
=======
	assert(mode >= 0 || mode < total);
	assert(score >= _scoreboardData[mode][9]._score);
>>>>>>> main

	std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c) { return std::toupper(c); });

	_scoreboardData[mode][difficulty][9] = {std::move(name), score};


	//bubble sort
	for (size_t i = 0; i < NUMBER_OF_SCORES - 1; i++)
		for (size_t j = i + 1; j < NUMBER_OF_SCORES; j++)
			if (_scoreboardData[mode][difficulty][i]._score < _scoreboardData[mode][difficulty][j]._score)
				std::swap(_scoreboardData[mode][difficulty][i], _scoreboardData[mode][difficulty][j]);
}

// Affichage
void Scoreboard::showMenu()
{
	// TODO: showMenu using a menu
}

void Scoreboard::showScore(GameMode mode, Difficulty difficulty)
{
	// TODO: showScore using a menu
}

// Surcharge des opérateurs
std::fstream & operator<<(std::fstream &file, Player player)
{
	file << player._name << ", " << player._score << std::endl;
	return file;
}

std::fstream & operator>>(std::fstream &file, Player& player)
{
	std::string clearToNext;
	getline(file, player._name, ',');
	file >> player._score;
	getline(file, clearToNext, '\n');
	return file;
}