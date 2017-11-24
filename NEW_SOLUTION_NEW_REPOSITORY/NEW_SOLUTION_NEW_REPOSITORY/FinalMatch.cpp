#include "FinalMatch.h"
#include <iomanip>

void FinalMatch::setYear(int y)
{
	year = y;
}

void FinalMatch::setTeams(std::string t1, std::string t2)
{
	teams[0] = t1;
	teams[1] = t2;
}

void FinalMatch::setResult(std::string s)
{
	result = s;
}

void FinalMatch::setStadium(std::string s)
{
	stadium = s;
}

void FinalMatch::setCity(std::string c)
{
	city = c;
}

int FinalMatch::getYear() const
{
	return year;
}

std::string FinalMatch::getTeam1() const
{
	return teams[0];
}

std::string FinalMatch::getTeam2() const
{
	return teams[1];
}

std::string FinalMatch::getResult() const
{
	return result;
}

std::string FinalMatch::getStadium() const
{
	return stadium;
}

std::string FinalMatch::getCity() const
{
	return city;
}

std::ostream& operator<<(std::ostream &o, FinalMatch &m)
{

	o << std::fixed << std::setprecision(2)
		<< std::left << std::setw(15) << m.teams[0]
		<< std::left << std::setw(18) << m.teams[1]
		<< std::left << std::setw(15) << m.result
		<< std::left << std::setw(30) << m.stadium
		<< std::left << std::setw(30) << m.city;
	return o;
}