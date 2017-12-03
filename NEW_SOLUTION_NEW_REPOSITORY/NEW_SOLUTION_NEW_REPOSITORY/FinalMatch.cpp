#include "FinalMatch.h"
#include <fstream>
#include <iomanip>

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

void FinalMatch::readFileFinalMatchData(std::string &line)
{
	// holds the element position of string find function
	size_t pos, end_pos;

	std::string temp1, temp2;
	std::string buffer = line;

	//set year
	pos = buffer.find('|');
	setYear(stoi(buffer.substr(0, pos - 1)));

	// sets team 1 and team 2
	buffer = buffer.substr(7);
	pos = buffer.find(',');
	temp1 = buffer.substr(0, pos);
	buffer = buffer.substr(pos + 2);
	end_pos = buffer.find('.');
	temp2 = buffer.substr(0, end_pos);
	setTeams(temp1, temp2);

	// set results
	pos = buffer.find('|');
	buffer = buffer.substr(pos + 2);
	temp1 = buffer.substr(0, 5);
	end_pos = buffer.find(')');

	if (buffer[6] == '(') {
		temp1 += buffer.substr(5, end_pos - 4);
	}
	setResult(temp1);

	// set stadium
	pos = buffer.find('|');
	buffer = buffer.substr(pos + 2);
	end_pos = buffer.find('.');
	setStadium(buffer.substr(0, end_pos));

	// set city
	pos = buffer.find('|');
	buffer = buffer.substr(pos + 2);
	end_pos = buffer.find('.');
	setCity(buffer.substr(0, end_pos));
}

void FinalMatch::outputFileFinalMatch()
{
	std::ofstream foutFM;

	foutFM.open("FinalMatchData.txt", std::ofstream::app);

	foutFM << std::left << year << " | ";
	foutFM << std::left << std::setw(24) << teams[0] + ", " + teams[1] + "." << " | ";
	foutFM << std::left << std::setw(13) << result << " | ";
	foutFM << std::left << std::setw(28) << stadium + "." << " | ";
	foutFM << std::left << std::setw(15) << city + "." << " |" << std::endl;

	foutFM.close();
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