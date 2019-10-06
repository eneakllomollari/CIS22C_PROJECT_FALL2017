#ifndef TEAMS_PARTICIPATED_H
#define TEAMS_PARTICIPATED_H

#include <string>
#include <iomanip>

class TeamsParticipated
{

private:
	std::string *teamsArr;
	int numTeams;
	int yearHeld;
public:
	TeamsParticipated();
	TeamsParticipated(int, int, std::string *);
	~TeamsParticipated();

	void setYearHeld(int);
	void setNumTeams(int);
	void setTeamsArr(std::string *);

	int getYearHeld()const;
	int getNumTeams()const;
	std::string *getTeamsArr()const;

	friend std::ostream& operator<<(std::ostream&, const TeamsParticipated&);
};

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

TeamsParticipated::~TeamsParticipated()
{
	delete[] teamsArr;
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
	const int NUM_COLS = 9;
	const int NUM_DASHES = 220;
	const int SPACING = 25;


	os << std::endl;
	for (int i = 0; i < NUM_DASHES; i++)os << "^";
	os << std::endl;
	os << "\t\t\t\t\t\t\t\t" << t.yearHeld << std::endl;
	os << std::endl;

	os << std::setw(SPACING) << std::left;
	for (int i = 0; i < t.numTeams; i++)
	{
		if (i > 0 && i % NUM_COLS == 0) os << std::endl;
		os << t.teamsArr[i] << std::setw(SPACING) << std::left;
	}
	os << std::setw(0) << std::endl;
	os << "\n\t\t\t\t\t\t\t" << t.getNumTeams() << " teams participated in " << t.getYearHeld() << std::endl;
	os << std::endl << std::endl;
	return os;
}
#endif // !TEAMS_PARTICIPATED_H