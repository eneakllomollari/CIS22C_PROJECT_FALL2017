#ifndef WORLDCUP_H
#define WORLDCUP_H

#include <string>
class WorldCup
{
private:
	std::string winningTeam;
	std::string goldenBootWinner;
	std::string hostCountry;
	double goalsPerGame;

	long int totAtt;
	int aveAtt;
	int numberOfGamesPlayed;
	int yearHeld;
public:
	WorldCup();
	~WorldCup();
	WorldCup(int,std::string,std::string,int,double,int,int,std::string);

	void setWinningTeam(std::string);
	void setGoldenBWinner(std::string);
	void setHostCountry(std::string);
	void setAveAtt(int);
	void setTotAtt(int);
	void setYearHeld(int);
	void setNumGames(int);
	void setGoalsPGame(double);

	std::string getWinningTeam() const;
	std::string getGoldenBootWinner() const;
	std::string getHostCountry() const;
	int getAveAtt() const;
	int getTotAtt() const;
	int getYearHeld() const;
	int getNumGames() const;
	double getGoalsPerGame() const;

	void operator=(const WorldCup&);
	friend std::ostream &operator<<(std::ostream &, const WorldCup&);
	friend bool operator<(const WorldCup&, const WorldCup&);
	friend bool operator>(const WorldCup &, const WorldCup&);
	friend bool operator==(const WorldCup&, const WorldCup&);
};

#endif // !WORLDCUP_H