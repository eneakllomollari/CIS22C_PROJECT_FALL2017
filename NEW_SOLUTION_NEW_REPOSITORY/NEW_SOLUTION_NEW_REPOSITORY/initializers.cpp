#include "Metadata.h"

void Metadata::initializeWorldCupdataManager()
{
	//Declare Local Variables/Objects
	std::string buffer;
	std::ifstream finWorldCup;
	std::ifstream finTeamsByYear;

	//Open file for reading
	finWorldCup.open("worldCupGeneraldata.txt");

	//If the file is unable to open, then throw an error
	if (!finWorldCup) throw "worldCupGeneraldata.txt FILE COULD NOT BE OPENED IN initializeWorldCupdata()"; /*2 operations*/

	//Read the file line by line and initialize data
	while (getline(finWorldCup, buffer))
		readFileWorldcupdata(buffer);

	//Close the ifstream object
	finWorldCup.close();

	//*************************************

	//Open second file for reading
	finTeamsByYear.open("TeamsByYear.txt");

	//If the file couldn't be opened throw an error
	if (!finTeamsByYear) throw "TeamsbyYear.txt FILE COULD NOT BE OPENED IN initializeWorldCupdata()";

	//Read the file line by line and initialize data
	while (getline(finTeamsByYear, buffer))
		readFileTeamsByYeardata(buffer);

	//Close the ifstream object
	finTeamsByYear.close();
}

void Metadata::initializeFinalMatchdataManager()
{
	//Declare local variables/objects
	std::string buffer;
	std::ifstream finFinalMatch;

	//Open file for input
	finFinalMatch.open("FinalMatchdata.txt");

	//If file is unable to open throw error
	if (!finFinalMatch) throw "FinalMatchdata.txt FILE COULD NOT BE OPENED IN initializeFinalMatchdata()";

	//Read file line by line and initialize data
	while (getline(finFinalMatch, buffer))
	{
		readFileFinalMatchdata(buffer);
	}

	//Close ifstream object
	finFinalMatch.close();
}

void Metadata::readFileWorldcupdata(std::string &line)
{
	int yearHeld, numGames, aveAtt, totAtt;
	double goalsPerGame;
	std::string winningTeam, goldenBootWinner,hostCountry;

	// holds the element position of string find function
	size_t pos, end_pos;

	int insertCounter, putCounter;
	std::string temp;
	std::string buffer = line;

	// set year held
	yearHeld = stoi(buffer.substr(0, 5));

	// set winning team
	buffer = buffer.substr(7);
	pos = buffer.find(' ');
	winningTeam = buffer.substr(0, pos);

	// sets golden B winner
	pos = buffer.find('|');
	buffer = buffer.substr(pos + 2);
	end_pos = buffer.find(' ');
	temp = buffer.substr(0, end_pos);
	pos = end_pos;
	if (isalpha(buffer[pos + 1]))
	{
		end_pos = buffer.find(' ', pos + 1);
		temp += buffer.substr(pos, end_pos - pos);
	}
	goldenBootWinner = temp;


	// sets number of games
	pos = buffer.find('|');
	buffer = buffer.substr(pos + 2);
	numGames = std::stoi(buffer.substr(0, 2));;

	// sets goals per game
	pos = buffer.find('|');
	buffer = buffer.substr(pos + 2);
	goalsPerGame = std::stod(buffer.substr(0, 4));

	// sets average attendance
	pos = buffer.find('|');
	buffer = buffer.substr(pos + 2);
	aveAtt = std::stoi(buffer.substr(0, 5));

	// sets total attendance
	pos = buffer.find('|');
	buffer = buffer.substr(pos + 2);
	end_pos = buffer.find(' ');
	totAtt = std::stoi(buffer.substr(0, end_pos));

	// sets host country
	pos = buffer.find('|');
	hostCountry = buffer.substr(pos + 2);

	//Allocating object in the heap
	WorldCup* tempWorldCup = new WorldCup(yearHeld, winningTeam, goldenBootWinner, numGames, goalsPerGame, aveAtt, totAtt, hostCountry);
	
	//This is where you assign the values to the BinarySearchTrees and the hash table
	//Initializing the BinarySearchTrees
	yearHeldBinarySearchTree->insert(tempWorldCup->getYearHeld(), tempWorldCup, insertCounter);

	worldCupdata->put(tempWorldCup->getYearHeld(), tempWorldCup, putCounter);
}

void Metadata::readFileFinalMatchdata(std::string &line)
{
	// holds the element position of string find function
	size_t pos, end_pos;

	int putCounter;
	int year;
	std::string buffer = line;

	std::string temp1, temp2;
	std::string teams[2];
	std::string result;
	std::string stadium;
	std::string city;
	//set year
	pos = buffer.find('|');
	year = stoi(buffer.substr(0, pos - 1));

	// sets team 1 and team 2
	buffer = buffer.substr(7);
	pos = buffer.find(',');
	temp1 = buffer.substr(0, pos);
	buffer = buffer.substr(pos + 2);
	end_pos = buffer.find('.');
	temp2 = buffer.substr(0, end_pos);
	teams[0] = temp1;
	teams[1] = temp2;

	// set results
	pos = buffer.find('|');
	buffer = buffer.substr(pos + 2);
	temp1 = buffer.substr(0, 5);
	end_pos = buffer.find(')');

	if (buffer[6] == '(') {
		temp1 += buffer.substr(5, end_pos - 4);
	}
	result = temp1;

	// set stadium
	pos = buffer.find('|');
	buffer = buffer.substr(pos + 2);
	end_pos = buffer.find('.');
	stadium = (buffer.substr(0, end_pos));

	// set city
	pos = buffer.find('|');
	buffer = buffer.substr(pos + 2);
	end_pos = buffer.find('.');
	city = buffer.substr(0, end_pos);

	FinalMatch* temp_FinalMatch_object = new FinalMatch(year, teams, result, stadium, city);

	//Store data in HashTable
	//Key = yearHeld
	//data = FinalMatch
	finalMatchdata->put(temp_FinalMatch_object->getYear(), temp_FinalMatch_object, putCounter);
	finalMatchBinarySearchTree->insert(temp_FinalMatch_object->getYear(), temp_FinalMatch_object,putCounter);
}

void Metadata::readFileTeamsByYeardata(std::string &line)
{
	//Declare local variables/objects
	int  size = 0, numTeamsParticipated, index = 0, numTeamsByYearBinarySearchTreeCounter = 0;
	int insertCounter, putCounter;

	std::string *tempArray_Teams, temp;

	//Convert the string input YearHeld to an integer value
	int yearHeld = std::stoi(line.substr(0, 4));

	//Line now stores the year of the World Cup
	line = line.substr(6);

	std::istringstream buffer(line);

	//Calculates the # of Teams Participated
	for (auto &i : line)
		if (i == ',') size++;
	size += 1;

	//Set the number of teams after caluclation
	numTeamsParticipated = size;

	//Dynamically allocated array of strings
	tempArray_Teams = new std::string[numTeamsParticipated];

	//Store the teams between commas into "Temp" string
	while (getline(buffer, temp, ','))
	{
		temp = temp.substr(1);
		tempArray_Teams[index] = temp;
		index++;
	}
	TeamsParticipated* tempTeams_Object = new TeamsParticipated(yearHeld, numTeamsParticipated, tempArray_Teams);

	//"Put" tempTeams_Object with all the teams participated for a specific year into teamsParticTable HashTable
	teamsByYear->put(yearHeld, tempTeams_Object, putCounter);

	numTeamsbyYearBinarySearchTree->insert(yearHeld, tempTeams_Object, numTeamsByYearBinarySearchTreeCounter);
}