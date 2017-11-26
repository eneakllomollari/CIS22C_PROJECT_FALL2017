#include "TeamsParticipated.h"

TeamsParticipated::TeamsParticipated()
{
	numTeams = 0;
	teamsArr = nullptr;
}

TeamsParticipated::TeamsParticipated(int y, int s, std::string* arr)
{
	yearHeld = y;
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
	const int NUM_COL = 1;
	os << std::endl;
	os << "________________________\n";
	os << "\t" <<  t.yearHeld << std::endl;
	os << "________________________\n";
	for (int i = 0; i < t.numTeams; i++)
	{
		if (i > 0 && i % NUM_COL == 0) os << std::endl;
		os << i + 1 << ".  " << t.teamsArr[i] << std::right << std::setw(20) << "";
	}
	os << std::endl;
	for (int i = 0; i < 24; i++)os << "-";

	return os;
}
