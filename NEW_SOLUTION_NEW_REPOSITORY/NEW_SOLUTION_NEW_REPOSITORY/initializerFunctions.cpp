#include "initializerFunctions.h"
#include <iostream>


/*
Pre: This function requires the addresses of multiple Trees to initialize data into.
-Trees needed to be passed(All Have "WorldCup" Object Data in TreeNodes)
1) yearHeld (Key: Year World Cup Held)
2) gpgT (Key: Goals Per Game)
3) aveAttT (Key: Average Attendance World Cup)
4) totalAtt (Key: Total Attendance World Cup)
5) numGames (Key: Number of Games During World Cup)

Also, it expects two HashTable references as Input
-HashTables Contain Data of WorldCup and TeamsParticipated
1) worldCupData, TeamsPariticpated Hashtables (Key: Year World Cup Held)

Post: Upon completion, this function will initialize the data into the respective Trees and Hashtables passed into it.

SIDE NOTES: Initialization functions use Read Functions as Helpers

*/
void initializeWorldCupData(Tree<int, WorldCup>& yearHeld, Tree<double, WorldCup>& gpgT, Tree<int, WorldCup>&aveAttT, Tree<int, WorldCup>& totalAtt,
	Tree<int, WorldCup>&numGames, HashTable<int, WorldCup>&worldCupData, HashTable<int, TeamsParticipated>&teamsParticTable, Tree<int, TeamsParticipated>&numTeamsTree)
{
	//Declare Local Variables/Objects
	std::string buffer;
	std::ifstream finWorldCup;
	std::ifstream finTeamsByYear;

	//Open file for reading
	finWorldCup.open("worldCupGeneralData.txt");

	//If the file is unable to open, then throw an error
	if (!finWorldCup) throw "worldCupGeneralData.txt FILE COULD NOT BE OPENED IN initializeWorldCupData()"; /*2 operations*/

																											//Read the file line by line and initialize data
	while (getline(finWorldCup, buffer))
		readFileWorldcupData(buffer, yearHeld, gpgT, aveAttT, totalAtt, numGames, worldCupData);

	//Close the ifstream object
	finWorldCup.close();

	//*************************************

	//Open second file for reading
	finTeamsByYear.open("TeamsByYear.txt");

	//If the file couldn't be opened throw an error
	if (!finTeamsByYear) throw "TeamsbyYear.txt FILE COULD NOT BE OPENED IN initializeWorldCupData()";

	//Read the file line by line and initialize data
	while (getline(finTeamsByYear, buffer))
		readFileTeamsByYearData(buffer, teamsParticTable, numTeamsTree);

	//Close the ifstream object
	finTeamsByYear.close();
}



/*
Pre: This function expects a reference of a HashTable(Key: Year World Cup, Data: FinalMatch Object)

Post: Upon Completion, this function will initialize the finalMatch data into referenced HashTable

SIDE NOTES: Initialization functions use Read Functions as Helpers
*/
void initializeFinalMatchData(HashTable<int, FinalMatch>& finalMatch_hashTable)
{
	//Declare local variables/objects
	std::string buffer;
	std::ifstream finFinalMatch;

	//Open file for input
	finFinalMatch.open("FinalMatchData.txt");

	//If file is unable to open throw error
	if (!finFinalMatch) throw "FinalMatchData.txt FILE COULD NOT BE OPENED IN initializeFinalMatchData()";

	//Read file line by line and initialize data
	while (getline(finFinalMatch, buffer))
	{
		readFileFinalMatchData(buffer, finalMatch_hashTable);
	}

	//Close ifstream object
	finFinalMatch.close();

}




/*
Pre: Reference to String and reference to HashTable(Key: Year World Cup, Data: TeamsParticipated Object)

Post: Upon completion, this function will have read and stored data into "teamsParticTable" HashTable with (Key: Year World Cup, Data: TeamsParticipated Object)

*/
void readFileTeamsByYearData(std::string& line, HashTable<int, TeamsParticipated>& teamsParticTable, Tree<int, TeamsParticipated>&numTeamsTree)
{
	//Declare local variables/objects
	int  size = 0, numTeamsParticipated, index = 0;
	int insertCounter;
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

	//Create temporary TeamsParticipated object
	TeamsParticipated tempTeams_Object(yearHeld, numTeamsParticipated, tempArray_Teams);

	//"Put" tempTeams_Object with all the teams participated for 
	//a specific year into teamsParticTable HashTable
	teamsParticTable.put(yearHeld, tempTeams_Object);
	numTeamsTree.insert(numTeamsParticipated, tempTeams_Object, insertCounter);
	//Delete Pointer to Dynamically Allocated array of strings
	//delete[] tempArray_Teams;
}



/*
Pre: A reference to a string object, and a reference to a HashTable(Key: Year World Cup, Data: FinalMatch Object)

Post: Upon Completion, this function will have read and stored data into the finalMatch_hashTable
*/
void readFileFinalMatchData(std::string &line, HashTable<int, FinalMatch>& finalMatch_hashTable)
{
	// holds the element position of string find function
	size_t pos, end_pos;

	//Temporary Final Match object
	FinalMatch temp_FinalMatch_object;

	std::string temp1, temp2;
	std::string buffer = line;

	//set year
	pos = buffer.find('|');
	temp_FinalMatch_object.setYear(stoi(buffer.substr(0, pos - 1)));

	// sets team 1 and team 2
	buffer = buffer.substr(7);
	pos = buffer.find(',');
	temp1 = buffer.substr(0, pos);
	buffer = buffer.substr(pos + 2);
	end_pos = buffer.find('.');
	temp2 = buffer.substr(0, end_pos);
	temp_FinalMatch_object.setTeams(temp1, temp2);

	// set results
	pos = buffer.find('|');
	buffer = buffer.substr(pos + 2);
	temp1 = buffer.substr(0, 5);
	end_pos = buffer.find(')');

	if (buffer[6] == '(') {
		temp1 += buffer.substr(5, end_pos - 4);
	}
	temp_FinalMatch_object.setResult(temp1);

	// set stadium
	pos = buffer.find('|');
	buffer = buffer.substr(pos + 2);
	end_pos = buffer.find('.');
	temp_FinalMatch_object.setStadium(buffer.substr(0, end_pos));

	// set city
	pos = buffer.find('|');
	buffer = buffer.substr(pos + 2);
	end_pos = buffer.find('.');
	temp_FinalMatch_object.setCity(buffer.substr(0, end_pos));

	//Store data in HashTable
	//Key = yearHeld
	//Data = FinalMatch
	finalMatch_hashTable.put(temp_FinalMatch_object.getYear(), temp_FinalMatch_object);
}




/*
Pre: This function requires the addresses of multiple Trees to store data into.
-Trees needed to be passed(All Have "WorldCup" Object Data in TreeNodes)
1) yearHeld (Key: Year World Cup Held)
2) gpgT (Key: Goals Per Game)
3) aveAttT (Key: Average Attendance World Cup)
4) totalAtt (Key: Total Attendance World Cup)
5) numGames (Key: Number of Games During World Cup)

Also, it expects two HashTable references as Input
-HashTables Contain Data of WorldCup and TeamsParticipated
1) worldCupData, TeamsPariticpated Hashtables (Key: Year World Cup Held)

Post: Upon completion, this function will have read and stored the data into the respective Trees and Hashtables passed into it.
*/
void readFileWorldcupData(std::string &line, Tree<int, WorldCup>& yearHeld, Tree<double, WorldCup>& gpgT, Tree<int, WorldCup>&aveAttT, Tree<int, WorldCup>& totalAtt,
	Tree<int, WorldCup>&numGames, HashTable<int, WorldCup>& worldCupData)
{
	//Temporary object to be used for initialization
	WorldCup tempWorldCup;

	// holds the element position of string find function
	size_t pos, end_pos;

	int insertCounter;
	std::string temp;
	std::string buffer = line;

	// set year held
	tempWorldCup.setYearHeld(stoi(buffer.substr(0, 5)));

	// set winning team
	buffer = buffer.substr(7);
	pos = buffer.find(' ');
	tempWorldCup.setWinningTeam(buffer.substr(0, pos));

	// sets golden B winner
	pos = buffer.find('|');
	buffer = buffer.substr(pos + 2);
	end_pos = buffer.find(' ');
	temp = buffer.substr(0, end_pos);
	pos = end_pos;
	if (isalpha(buffer[pos + 1])) {
		end_pos = buffer.find(' ', pos + 1);
		temp += buffer.substr(pos, end_pos - pos);
	}
	tempWorldCup.setGoldenBWinner(temp);


	// sets number of games
	pos = buffer.find('|');
	buffer = buffer.substr(pos + 2);
	tempWorldCup.setNumGames(std::stoi(buffer.substr(0, 2)));

	// sets goals per game
	pos = buffer.find('|');
	buffer = buffer.substr(pos + 2);
	tempWorldCup.setGoalsPGame(std::stod(buffer.substr(0, 4)));

	// sets average attendance
	pos = buffer.find('|');
	buffer = buffer.substr(pos + 2);
	tempWorldCup.setAveAtt(std::stoi(buffer.substr(0, 5)));

	// sets total attendance
	pos = buffer.find('|');
	buffer = buffer.substr(pos + 2);
	end_pos = buffer.find(' ');
	tempWorldCup.setTotAtt(std::stol(buffer.substr(0, end_pos)));

	// sets host country
	pos = buffer.find('|');
	tempWorldCup.setHostCountry(buffer.substr(pos + 2));

	//This is where you assign the values to the trees and the hash table
	//Initializing the trees
	yearHeld.insert(tempWorldCup.getYearHeld(), tempWorldCup, insertCounter);
	gpgT.insert(tempWorldCup.getGoalsPerGame(), tempWorldCup, insertCounter);
	aveAttT.insert(tempWorldCup.getAveAtt(), tempWorldCup, insertCounter);
	totalAtt.insert(tempWorldCup.getAveAtt(), tempWorldCup, insertCounter);
	numGames.insert(tempWorldCup.getNumGames(), tempWorldCup, insertCounter);
	worldCupData.put(tempWorldCup.getYearHeld(), tempWorldCup);
}
