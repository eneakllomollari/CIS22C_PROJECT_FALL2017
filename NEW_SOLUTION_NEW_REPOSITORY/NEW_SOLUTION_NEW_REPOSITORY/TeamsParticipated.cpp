#include "TeamsParticipated.h"
#include <iomanip>
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

std::ostream & operator<<(std::ostream &os, const TeamsParticipated &t)
{
	const int NUM_COL = 2;
	for (int i = 0; i < t.numTeams; i++)
	{
		if (i > 0 && i % NUM_COL == 0) os << std::endl;
		os << std::left << std::setw(40) << t.teamsArr[i];
	}
	return os;
}
