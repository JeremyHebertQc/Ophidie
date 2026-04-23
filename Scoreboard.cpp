/*====================================
Auteur : Félix-Antoine Lacroix
Projet : Ophidie
====================================*/
#include <fstream>
#include <iostream> // TODO: Switch to SFML
#include "Scoreboard.h"

#include "utils.h"

const std::string Scoreboard::filePaths[] =
{
	SCOREBOARD_FILEPATH + "NORMAL_SCOREBOARD",
	SCOREBOARD_FILEPATH + "SURVIVAL_SCOREBOARD",
	SCOREBOARD_FILEPATH + "DEATH_TRAP_SCOREBOARD",
	SCOREBOARD_FILEPATH + "SURVIVE_HELL_SCOREBOARD"
};

void openFile(std::fstream& file,std::string filepath)
{
	file.open(filepath, std::ios::in | std::ios::out);
	if (!file.is_open())
	{
		std::cerr << "Failed to open file : " << filepath; // TODO: Switch to SFML
#ifdef WIN32
		system("pause>NUL");
#else
		std::cin.get();
#endif

		exit(FILE_NOT_OPENED);
	}
}


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
	int j = 0;

	for (const auto & filePath : filePaths)
	{
		openFile(file, filePath);
		for (int i = 0; i < NUMBER_OF_SCORES; i++)
		{
			if (file.eof())
				break;
			file >> _scoreboardData[j][i];
		}
		j++;
	}
	file.close();
}

void Scoreboard::writeData() const
{
	std::fstream file;
	int j = 0;

	for (const auto & filePath : filePaths)
	{
		openFile(file, filePath);
		for (int i = 0; i < NUMBER_OF_SCORES; i++)
		{
			file << _scoreboardData[j][i];
		}
		j++;
		file.close();
	}
}

// Gestion du score
bool Scoreboard::checkScore(float score, GameMode mode) const
{
	assert(score >= 0);
	assert(mode >= 0 || mode < total);

	if (score > _scoreboardData[mode][9]._score)
		return true;
	return false;
}

void Scoreboard::addScore(float score, std::string name, GameMode mode)
{
	assert(mode >= 0 || mode < total);
	assert(score >= _scoreboardData[mode][9]._score);

	std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c) { return std::toupper(c); });

	_scoreboardData[mode][9] = {std::move(name), score};


	//bubble sort
	for (size_t i = 0; i < NUMBER_OF_SCORES - 1; i++)
		for (size_t j = i + 1; j < NUMBER_OF_SCORES; j++)
			if (_scoreboardData[mode][i]._score < _scoreboardData[mode][j]._score)
				std::swap(_scoreboardData[mode][i], _scoreboardData[mode][j]);
}

// Affichage
void Scoreboard::showMenu()
{
	// TODO: showMenu using a menu
}

void Scoreboard::showScore(GameMode mode)
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