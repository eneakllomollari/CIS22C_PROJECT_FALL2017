#include "WorldCup.h"
#include <iomanip>
#include <iostream>
#include <fstream>

//void WorldCup::setNumOfTeamsParticipated(int s)
//{
//	numOfTeamsParticipated = s;
//}

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

//void WorldCup::setTeamsParticipatedArray(int size)
//{
//	this->teamsParticipated = new std::string[size];
//}

WorldCup::WorldCup()
{
	this->winningTeam = "DEFAULT TEAM";
	this->goldenBootWinner = "DEFAULT PLAYER";
	this->hostCountry = "DEFAULT COUNTRY";
	//this->teamsParticipated = nullptr;
	this->goalsPerGame = 0.0;
	this->aveAtt = 0;
	this->totAtt = 0;
	this->numberOfGamesPlayed = 0;
	this->yearHeld = 1000;
}

WorldCup::~WorldCup()
{
	//delete[] teamsParticipated;
}

//void WorldCup::displayTeamsParticipated()
//{
//	std::cout << yearHeld << std::endl;
//	for (int i = 0; i < numOfTeamsParticipated; i++)
//		std::cout << teamsParticipated[i] << std::endl;
//
//	system("pause");
//	system("CLS");
//}

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

//int WorldCup::getNumOfTeamsParticipated() const
//{
//	return numOfTeamsParticipated;
//}

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

//void WorldCup::outputFileTeamsParticipated()
//{
//	std::ofstream foutTY;
//
//	foutTY.open("TeamsByYear.txt", std::ofstream::app);
//
//	foutTY << std::left << yearHeld << " | ";
//	for (int i = 0; i < numOfTeamsParticipated; i++) {
//		if (i == numOfTeamsParticipated - 1)
//			foutTY << teamsParticipated[i];
//		else
//			foutTY << teamsParticipated[i] << ", ";
//	}
//
//	foutTY << std::endl;
//
//	foutTY.close();
//}

std::ostream & operator<<(std::ostream & os, const WorldCup &wC)
{
	//Written by Kamaljot Saini
	os << std::fixed << std::setprecision(2);
	os << std::left << std::setw(6) << wC.getYearHeld();
	os << std::left << std::setw(15) << wC.getWinningTeam();
	os << std::left << std::setw(20) << wC.getGoldenBootWinner();
	os << std::left << std::setw(5) << wC.getNumGames();
	os << std::left << std::setw(6) << wC.getGoalsPerGame();
	os << std::left << std::setw(8) << wC.getAveAtt();
	os << std::left << std::setw(10) << wC.getTotAtt();

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