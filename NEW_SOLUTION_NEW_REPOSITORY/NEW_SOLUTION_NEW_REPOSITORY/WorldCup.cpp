#include "WorldCup.h"
#include <iomanip>
#include <iostream>
#include <fstream>


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

WorldCup::WorldCup()
{
	this->winningTeam = "DEFAULT TEAM";
	this->goldenBootWinner = "DEFAULT PLAYER";
	this->hostCountry = "DEFAULT COUNTRY";
	this->goalsPerGame = 0.0;
	this->aveAtt = 0;
	this->totAtt = 0;
	this->numberOfGamesPlayed = 0;
	this->yearHeld = 1000;
}

WorldCup::~WorldCup()
{
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

std::ostream & operator<<(std::ostream & os, const WorldCup &wC)
{
	//Written by Kamaljot Saini
	os << std::fixed << std::setprecision(2);
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