#ifndef FINALMATCH_H
#define FINALMATCH_H

#include <string>
#include <iomanip>

class FinalMatch
{
private:
	int year;
	std::string teams[2];
	std::string result;
	std::string stadium;
	std::string city;

public:
	FinalMatch(){};
	FinalMatch(int,std::string*, std::string, std::string, std::string);
	void setYear(int);
	void setTeams(std::string, std::string);
	void setResult(std::string);
	void setStadium(std::string);
	void setCity(std::string);
	
	int getYear() const;
	std::string getTeam1() const;
	std::string getTeam2() const;
	std::string getResult() const;
	std::string getStadium() const;
	std::string getCity() const;

	friend std::ostream &operator<<(std::ostream &, FinalMatch&);
};


FinalMatch::FinalMatch(int y, std::string* teamsP, std::string res, std::string st, std::string ci)
{
	this->year = y;
	this->teams[0] = teamsP[0];
	this->teams[1] = teamsP[1];
	this->result = res;
	this->stadium = st;
	this->city = ci;
}

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
		<< std::left << std::setw(6) << m.year
		<< std::left << std::setw(18) << m.teams[0]
		<< std::left << std::setw(25) << m.teams[1]
		<< std::left << std::setw(20) << m.result
		<< std::left << std::setw(35) << m.stadium
		<< std::left << std::setw(40) << m.city;
	return o;
}
#endif