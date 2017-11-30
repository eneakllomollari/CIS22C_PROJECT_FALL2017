#include "WorldCup.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>

void WorldCup::setNumOfTeamsParticipated(int s)
{
	numOfTeamsParticipated = s;
}

void WorldCup::setWinningTeam(std::string s)
{
	winningTeam = s;
}

void WorldCup::setGoldenBWinner(std::string s)
{
	goldenBootWinner = s;
}

void WorldCup::setHostCountry(std::string s)
{
	hostCountry = s;
}

void WorldCup::setAveAtt(int s)
{
	aveAtt = s;
}

void WorldCup::setTotAtt(int a)
{
	totAtt = a;
}

void WorldCup::setYearHeld(int y)
{
	yearHeld = y;
}

void WorldCup::setNumGames(int n)
{
	numberOfGamesPlayed = n;
}

void WorldCup::setGoalsPGame(double gpg)
{
	goalsPerGame = gpg;
}

void WorldCup::setTeamsParticipatedArray(int size)
{
	this->teamsParticipated = new std::string[size];
}

WorldCup::WorldCup()
{
	this->winningTeam = "DEFAULT TEAM";
	this->goldenBootWinner = "DEFAULT PLAYER";
	this->hostCountry = "DEFAULT COUNTRY";
	this->teamsParticipated = nullptr;
	this->goalsPerGame = 0.0;
	this->aveAtt = 0;
	this->totAtt = 0;
	this->numberOfGamesPlayed = 0;
	this->yearHeld = 1000;
}

WorldCup::~WorldCup()
{
	delete[] teamsParticipated;
}

void WorldCup::displayTeamsParticipated()
{
	std::cout << yearHeld << std::endl;
	for (int i = 0; i < numOfTeamsParticipated; i++)
		std::cout << teamsParticipated[i] << std::endl;

	system("pause");
	system("CLS");
}

std::string WorldCup::getWinningTeam() const
{
	return winningTeam;
}

std::string WorldCup::getGoldenBootWinner() const
{
	return goldenBootWinner;
}

std::string WorldCup::getHostCountry() const
{
	return hostCountry;
}

int WorldCup::getNumOfTeamsParticipated() const
{
	return numOfTeamsParticipated;
}

int WorldCup::getAveAtt() const
{
	return aveAtt;
}

int WorldCup::getTotAtt() const
{
	return totAtt;
}

int WorldCup::getYearHeld() const
{
	return yearHeld;
}

int WorldCup::getNumGames() const
{
	return numberOfGamesPlayed;
}

double WorldCup::getGoalsPerGame() const
{
	return goalsPerGame;
}

void WorldCup::readFileWorldcupData(std::string &line)
{
	//Here we should also insert into a tree


	// holds the element position of string find function
	size_t pos, end_pos;

	std::string temp;
	std::string buffer = line;

	// set year held
	setYearHeld(stoi(buffer.substr(0, 5)));

	// set winning team
	buffer = buffer.substr(7);
	pos = buffer.find(' ');
	setWinningTeam(buffer.substr(0, pos));

	// sets golden B winner
	pos = buffer.find('|');
	buffer = buffer.substr(pos + 2);
	end_pos = buffer.find(' ');
	temp = buffer.substr(0, end_pos);
	pos = end_pos;
	if (isalpha(buffer[pos + 1])) {
		end_pos = buffer.find(' ', pos + 1);
		temp += buffer.substr(pos, end_pos - pos);
	}
	setGoldenBWinner(temp);

	// sets number of games
	pos = buffer.find('|');
	buffer = buffer.substr(pos + 2);
	setNumGames(std::stoi(buffer.substr(0, 2)));

	// sets goals per game
	pos = buffer.find('|');
	buffer = buffer.substr(pos + 2);
	setGoalsPGame(std::stod(buffer.substr(0, 4)));

	// sets average attendance
	pos = buffer.find('|');
	buffer = buffer.substr(pos + 2);
	setAveAtt(std::stoi(buffer.substr(0, 5)));

	// sets total attendance
	pos = buffer.find('|');
	buffer = buffer.substr(pos + 2);
	end_pos = buffer.find(' ');
	setTotAtt(std::stol(buffer.substr(0, end_pos)));

	// sets host country
	pos = buffer.find('|');
	setHostCountry(buffer.substr(pos + 2));
}

void WorldCup::readFileTeamsByYearData(std::string &line)
{
	line = line.substr(6);
	std::istringstream buffer(line);
	std::string temp;
	int  size = 0;

	// checks size 
	for (auto &i : line)
		if (i == ',') size++;
	size += 1;

	numOfTeamsParticipated = size;

	setTeamsParticipatedArray(size);
	int index = 0;
	while (getline(buffer, temp, ','))
	{
		temp = temp.substr(1);
		teamsParticipated[index] = temp;
		index++;
	}
}

void WorldCup::outputFileWorldcupData()
{
	std::ofstream foutWC;

	foutWC.open("worldCupGeneralData.txt", std::ofstream::app);

	foutWC << std::fixed << std::setprecision(2);
	foutWC << std::left << yearHeld << " | ";
	foutWC << std::left << std::setw(9) << winningTeam << " | ";
	foutWC << std::left << std::setw(18) << goldenBootWinner << " | ";
	foutWC << std::left << numberOfGamesPlayed << " | ";
	foutWC << std::left << std::setw(4) << goalsPerGame << " | ";
	foutWC << std::left << aveAtt << " | ";
	foutWC << std::left << std::setw(7) << totAtt << " | ";
	foutWC << std::left << hostCountry << std::endl;

	foutWC.close();
}

void WorldCup::outputFileTeamsParticipated()
{
	std::ofstream foutTY;

	foutTY.open("TeamsByYear.txt", std::ofstream::app);

	foutTY << std::left << yearHeld << " | ";
	for (int i = 0; i < numOfTeamsParticipated; i++) {
		if (i == numOfTeamsParticipated - 1)
			foutTY << teamsParticipated[i];
		else
			foutTY << teamsParticipated[i] << ", ";
	}

	foutTY << std::endl;

	foutTY.close();
}

std::ostream & operator<<(std::ostream & os, const WorldCup &wC)
{
	//Written by Kamaljot Saini
	os << std::left << std::setw(6) << wC.getYearHeld();
	os << std::left << std::setw(18) << wC.getWinningTeam();
	os << std::left << std::setw(25) << wC.getGoldenBootWinner();
	os << std::left << std::setw(13) << wC.getNumGames();
	os << std::left << std::setw(23) << wC.getGoalsPerGame();
	os << std::left << std::setw(23) << wC.getAveAtt();
	os << std::left << std::setw(17) << wC.getTotAtt();
	os << std::left << std::setw(0) << wC.getHostCountry();

	return os;
}

bool operator<(const WorldCup &a, const WorldCup &b)
{
	return a.yearHeld < b.yearHeld;
}

bool operator>(const WorldCup &a, const WorldCup &b)
{
	return a.yearHeld > b.yearHeld;
}

bool operator==(const WorldCup &a, const WorldCup &b)
{
	return a.yearHeld == b.yearHeld;
}