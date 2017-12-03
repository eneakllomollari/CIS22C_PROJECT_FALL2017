#ifndef FINALMATCH_H
#define FINALMATCH_H

#include <string>

class FinalMatch
{
private:
	int year;
	std::string teams[2];
	std::string result;
	std::string stadium;
	std::string city;

public:
	FinalMatch(int,std::string*, std::string, std::string, std::string);
	void setYear(int);
	void setTeams(std::string, std::string);
	void setResult(std::string);
	void setStadium(std::string);
	void setCity(std::string);
	void readFileFinalMatchData(std::string &line);
	void outputFileFinalMatch();

	int getYear() const;
	std::string getTeam1() const;
	std::string getTeam2() const;
	std::string getResult() const;
	std::string getStadium() const;
	std::string getCity() const;

	friend std::ostream &operator<<(std::ostream &, FinalMatch&);
};
#endif