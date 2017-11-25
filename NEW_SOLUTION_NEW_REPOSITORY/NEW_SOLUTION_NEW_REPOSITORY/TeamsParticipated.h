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
	TeamsParticipated(int, std::string *);

	void setYearHeld(int);
	void setNumTeams(int);
	void setTeamsArr(std::string *);

	int getYearHeld()const;
	int getNumTeams()const;
	std::string *getTeamsArr()const;

	friend std::ostream& operator<<(std::ostream&, const TeamsParticipated&);
};

#endif // !TEAMS_PARTICIPATED_H
