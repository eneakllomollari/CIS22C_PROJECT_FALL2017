#include "TeamsParticipated.h"

TeamsParticipated::TeamsParticipated()
{
	numTeams = 0;
	teamsArr = nullptr;
}

TeamsParticipated::TeamsParticipated(int s, std::string* arr)
{
	numTeams = s;
	teamsArr = new std::string[s];
	teamsArr = arr;
}

void TeamsParticipated::setYearHeld(int y)
{
	yearHeld = y;
}

void TeamsParticipated::setNumTeams(int n)
{
	numTeams = n;
}

void TeamsParticipated::setTeamsArr(std::string * a)
{
	teamsArr = a;
}

int TeamsParticipated::getYearHeld() const
{
	return yearHeld;
}

int TeamsParticipated::getNumTeams() const
{
	return numTeams;
}

std::string* TeamsParticipated::getTeamsArr() const
{
	return teamsArr;
}

std::ostream & operator<<(std::ostream &os, const TeamsParticipated &t)
{
	const int NUM_COL = 2;
	os << t.yearHeld << std::endl;
	for (int i = 0; i < t.numTeams; i++)
	{
		if (i > 0 && i % NUM_COL == 0) os << std::endl;
		os << std::left << std::setw(40) << t.teamsArr[i];
	}
	return os;
}
