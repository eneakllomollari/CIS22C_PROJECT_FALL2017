#include "functions.h"

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
			1) winnerTeamTable, TeamsPariticpated Hashtables (Key: Year World Cup Held)

	Post: Upon completion, this function will initialize the data into the respective Trees and Hashtables passed into it.

	SIDE NOTES: Initialization functions use Read Functions as Helpers

*/
void initializeWorldCupData(Tree<int, WorldCup>& yearHeld, Tree<double, WorldCup>& gpgT, Tree<int, WorldCup>&aveAttT,
	Tree<int, WorldCup>& totalAtt, Tree<int, WorldCup>&numGames, HashTable<int, WorldCup>&winnerTeamTable, HashTable<int, TeamsParticipated>&teamsParticTable)
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
		readFileWorldcupData(buffer, yearHeld, gpgT, aveAttT, totalAtt, numGames, winnerTeamTable);
	
	//Close the ifstream object
	finWorldCup.close();

	//*************************************
	
	//Open second file for reading
	finTeamsByYear.open("TeamsByYear.txt");

	//If the file couldn't be opened throw an error
	if (!finTeamsByYear) throw "TeamsbyYear.txt FILE COULD NOT BE OPENED IN initializeWorldCupData()" ;

	//Read the file line by line and initialize data
	while (getline(finTeamsByYear, buffer))
		readFileTeamsByYearData(buffer, teamsParticTable);

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
void readFileTeamsByYearData(std::string& line, HashTable<int,TeamsParticipated>& teamsParticTable)
{
	//Declare local variables/objects
	int  size = 0, numTeamsParticipated, index = 0;
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
	TeamsParticipated tempTeams_Object(numTeamsParticipated, tempArray_Teams);

	//"Put" tempTeams_Object with all the teams participated for 
	//a specific year into teamsParticTable HashTable
	teamsParticTable.put(yearHeld, tempTeams_Object);

	//Delete Pointer to Dynamically Allocated array of strings
	delete[] tempArray_Teams;
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
			1) winnerTeamTable, TeamsPariticpated Hashtables (Key: Year World Cup Held)

	Post: Upon completion, this function will have read and stored the data into the respective Trees and Hashtables passed into it.
*/
void readFileWorldcupData(std::string &line, Tree<int, WorldCup>& yearHeld, Tree<double, WorldCup>& gpgT, Tree<int, WorldCup>&aveAttT, Tree<int, WorldCup>& totalAtt,
	Tree<int, WorldCup>&numGames, HashTable<int, WorldCup>& winnerTeamTable)
{
	//Temporary object to be used for initialization
	WorldCup tempWorldCup;

	// holds the element position of string find function
	size_t pos, end_pos;

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
	yearHeld.insert(tempWorldCup.getYearHeld(), tempWorldCup);
	gpgT.insert(tempWorldCup.getGoalsPerGame(), tempWorldCup);
	aveAttT.insert(tempWorldCup.getAveAtt(), tempWorldCup);
	totalAtt.insert(tempWorldCup.getAveAtt(), tempWorldCup);
	numGames.insert(tempWorldCup.getNumGames(), tempWorldCup);
	winnerTeamTable.put(tempWorldCup.getYearHeld(), tempWorldCup);
}

/*
	Pre: N/A

	Post: Upon successful completion, this function will display the World Cup Years to user

	!%@^@#%@$^  THIS CODE NEEDS TO BE FIXED !&@%$^$@*#^^ 
	It is using useless recursion. 

*/
void yearChosen()
{
	//Declare Local Variables Objects
	int choiceYear;

	//First do while loop
	do {
		//Clear Screen
		system("CLS");

		//Display Years to User and ask for their choice
		std::cout << std::setw(WIDTH_BTW_LINES + 2) << "" << "Years a world cup was held on:\n\n";
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "1)  1930\t\t\t2)  1934\n";
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "3)  1938\t\t\t4)  1950\n";
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "5)  1954\t\t\t6)  1958\n";
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "7)  1962\t\t\t8)  1966\n";
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "9)  1970\t\t\t10) 1974\n";
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "11) 1978\t\t\t12) 1982\n";
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "13) 1986\t\t\t14) 1990\n";
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "15) 1994\t\t\t16) 1998\n";
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "17) 2002\t\t\t18) 2006\n";
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "19) 2010\t\t\t20) 2014\n";
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "0) EXIT\n";
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Enter your choice: ";
		std::cin >> choiceYear;
		
		//Skip lines for aesthetics
		std::cout << "\n\n";

		//Run user choice through swtich statement and run appropriate code
		switch (choiceYear)
		{
			case 1:yearChosen(); break;
			case 2:yearChosen(); break;
			case 3:yearChosen(); break;
			case 4:yearChosen(); break;
			case 5:yearChosen(); break;
			case 6:yearChosen(); break;
			case 7:yearChosen(); break;
			case 8:yearChosen(); break;
			case 9:yearChosen(); break;
			case 10:yearChosen(); break;
			case 11:yearChosen(); break;
			case 12:yearChosen(); break;
			case 13:yearChosen(); break;
			case 14:yearChosen(); break;
			case 15:yearChosen(); break;
			case 16:yearChosen(); break;
			case 17:yearChosen(); break;
			case 18:yearChosen(); break;
			case 19:yearChosen(); break;
			case 20:yearChosen(); break;
			case 0:	system("CLS"); break;
			default: 	system("CLS");
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "INVALID CHOICE. Please choose between 1 - 20!" << std::endl; 
				system("CLS");
				break;
		 }//END SWITCH

		 //it takes care of the strings entered
		std::cin.clear();					
		std::cin.ignore(INT_MAX, '\n');


	} while (choiceYear != 0);	//End of main do while loop

	//Clear Screen
	//it makes the UI cleaner
	system("CLS");              
}




/*
	Pre: N/A

	Post:


	!^^@%@$%^ THIS CODE NEEDS FIXING.... LOOK NEAR END.... !^%^$@%^$@%@$
*/
void add()
{
	//*******************************************************************************************
	//The user should be given a choice to exit in the middle of entering the data
	//*******************************************************************************************

	//Declare local variables/constants/arrays
	const int MAX_NUM_TEAMS = 50;
	int year, numberOfTeams, goalScoredFirstTeam, goalScoredSecondTeam;
	std::string teams[MAX_NUM_TEAMS];
	std::string FirstTeamFinalMatch, SecondteamFinalMatch, stadiumName, cityHost;

	//Run entire code in "Try" Block #ExceptionHandling
	try {
		//Clear Screen
		system("CLS");

		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Enter the year: " << "                            ";
		std::cin >> year;					                                               // to be changed with writing in the file
		if (std::cin.fail()) throw "\n\t\t\t\t\t\t\t\tINVALID YEAR";
		std::cin.ignore(INT_MAX, '\n');

		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Enter the number of teams: " << "                 ";
		std::cin >> numberOfTeams;
		if (std::cin.fail()) throw "\n\t\t\t\t\t\t\t\tINVALID INPUT";
		std::cin.ignore(INT_MAX, '\n');

		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Enter the teams: " << std::endl;
		for (int n = 0; n < numberOfTeams; n++)
		{
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "                                          " << ">";

			getline(std::cin, teams[n], '\n');
			std::cin.ignore(INT_MAX, '\n');
		}

		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Enter the teams in the final match: " << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Team #1: " << "                                   ";
		getline(std::cin, FirstTeamFinalMatch);
		std::cin.ignore(INT_MAX, '\n');
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Team #2: " << "                                   ";
		getline(std::cin, SecondteamFinalMatch);
		std::cin.ignore(INT_MAX, '\n');

		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Enter the result of the final match: " << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Goals made by " << FirstTeamFinalMatch << " were: " << "                      ";
		std::cin >> goalScoredFirstTeam;
		if (std::cin.fail()) throw "\n\t\t\t\t\t\t\t\tINVALID INPUT";
		std::cin.ignore(INT_MAX, '\n');

		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Goals made by " << SecondteamFinalMatch << " were: " << "                      ";
		std::cin >> goalScoredSecondTeam;
		if (std::cin.fail()) throw "\n\t\t\t\t\t\t\t\tINVALID NUMBER OF GOALS";
		std::cin.ignore(INT_MAX, '\n');

		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Enter the stadium's name? " << "                  ";
		getline(std::cin, stadiumName);
		std::cin.ignore(INT_MAX, '\n');

		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Enter the city that hosted the Final match: ";
		getline(std::cin, cityHost);
		std::cin.ignore(INT_MAX, '\n');

		//Need to store into temporary object of some sort


		//Push into trees and Hashtables
	}
	catch (char *msg)
	{
		std::cout << msg << std::endl;
	}
	catch (...)
	{
		std::cout << "ERROR" << std::endl;
	}
}

void display_year_data(HashTable<int, WorldCup> table)
{
	int choiceYear;
	system("CLS");

	std::cout << std::endl << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Enter the year: ";
	std::cin >> choiceYear;
	std::cout << "\n";

	//Sample on how to display the elements of the hash table
	try {
		WorldCup worldCupObject = table.get(choiceYear);

		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "YEAR HELD:             " << worldCupObject.getYearHeld() << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "WINNING COUNTRY:       " << worldCupObject.getWinningTeam() << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "GOLDEN BOOT WINNER:    " << worldCupObject.getGoldenBootWinner() << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "GOALS PER GAME:        " << worldCupObject.getGoalsPerGame() << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "TOTAL ATTENDANCE:      " << worldCupObject.getTotAtt() << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "AVERAGE ATTENDANCE:    " << worldCupObject.getAveAtt() << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "NUMBER OF GAMES:       " << worldCupObject.getNumGames() << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "HOST COUNTRY:          " << worldCupObject.getHostCountry() << std::endl;
		std::cout << std::endl;
	}
	catch (char *msg)
	{
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << msg << std::endl;
	}
	std::cout << "\n\n";
	std::cout << std::setw(WIDTH_BTW_LINES) << ""; system("pause");
	system("CLS");
}

/*void checkPreviousYears()
{

	system("CLS");
	int choice;
	do {

		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "What do you want to check? " << "" << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "1) Teams in the World Cup" << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "2) Final match information" << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "3) Best Player " << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "4) Number of games" << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "5) Goal per game" << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "6) Average Attendence" << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "7) Total attendence" << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "8) Host country" << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "0) EXIT\n";

		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Enter your choice: ";
		std::cin >> choice;
		std::cout << "\n\n";
		switch (choice)
		{
			case 1: break;
			case 2: break;
			case 3: break;
			case 4: break;
			case 5: break;
			case 6: break;
			case 7: break;
			case 8: break;

		default: 	system("CLS");
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "INVALID CHOICE. Please enter a number 1 - 8!" << std::endl; break;

		}

		std::cin.clear();             //it takes care of the strings entered
		std::cin.ignore(INT_MAX, '\n');

	} while (choice != 0);	//End of main do while loop


};*/

void hashtable_list()
{
	//call hashtable file io function (get data from txt, put into hashtable)
}

void sortDataByChoice(Tree<int, WorldCup> yearTree, Tree<double, WorldCup> goalsPerGameTree, Tree<int, WorldCup> aveAttTree, Tree<int, WorldCup> totAttTree,Tree<int,WorldCup> numGamesTree)
{
	int user_choice;
	system("CLS");
	do
	{

		try {
			std::cout << std::setw(WIDTH_BTW_LINES + 2) << "" << "By which information do you want our database to be sorted in?:\n\n";
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "1) Year Held\n";
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "2) Goals per game\n";
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "3) Number of games\n";
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "4) Average Attendance\n";
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "5) Total Attendance\n";
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "0) EXIT\n";

			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Enter your choice: ";
			std::cin >> user_choice;
			if (std::cin.fail() || user_choice < 0 || user_choice >= 6)throw "INVALID CHOICE. PLEASE ENTER A CHOICE 1-20 !";

			std::cout << "\n\n";
			switch (user_choice)
			{
			case 1:
				system("CLS");
				std::cout << "\n\n\n";
				yearTree.displayInOrder();
				std::cout << "\n\n";
				system("pause");
				system("CLS");
				break;
			case 2:
				system("CLS");
				std::cout << "\n\n\n";
				goalsPerGameTree.displayInOrder();
				std::cout << "\n\n";
				system("pause");
				system("CLS");
				break;
			case 3:
				system("CLS");
				std::cout << "\n\n\n";
				numGamesTree.displayInOrder();
				std::cout << "\n\n";
				system("pause");
				system("CLS"); 
				break;
			case 4:
				system("CLS");
				std::cout << "\n\n\n";
				aveAttTree.displayInOrder();
				std::cout << "\n\n";
				system("pause");
				system("CLS");
				break;
			case 5:
				system("CLS");
				std::cout << "\n\n\n";
				totAttTree.displayInOrder();
				std::cout << "\n\n";
				system("pause");
				system("CLS");
				break;
			case 0: break;
			default:
				system("CLS");
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "INVALID CHOICE. Please enter a number 1 - 6!" << std::endl; break;
				system("CLS");
			}
		}
		catch (char *msg)
		{
			std::cout << msg << std::endl;
		}
		catch (...)
		{
			std::cout << "ERROR" << std::endl;
		}
	} while (user_choice != 0);
	system("CLS");
}

void pretty_print()
{
	//call bst.print();
}

void remove_year()
{
	int choiceYear;

	do {
		system("CLS");

		try {
			std::cout << std::setw(WIDTH_BTW_LINES + 2) << "" << "Years a world cup was held on:\n\n";
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "1)  1930\t\t\t2)  1934\n";
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "3)  1938\t\t\t4)  1950\n";
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "5)  1954\t\t\t6)  1958\n";
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "7)  1962\t\t\t8)  1966\n";
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "9)  1970\t\t\t10) 1974\n";
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "11) 1978\t\t\t12) 1982\n";
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "13) 1986\t\t\t14) 1990\n";
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "15) 1994\t\t\t16) 1998\n";
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "17) 2002\t\t\t18) 2006\n";
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "19) 2010\t\t\t20) 2014\n";
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "0) EXIT\n";

			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Enter your choice: ";
			std::cin >> choiceYear;
			std::cout << "\n\n";
			if (std::cin.fail() || (choiceYear < 0) || choiceYear >= 20) throw "PLEASE ENTER AN VALID CHOICE 1-20 !";
		}
		catch (char *msg)
		{
			std::cout << msg << std::endl;
		}
		//search function to traverse BST and find year
		//
		// call bst.remove(value)
	} while (choiceYear != 0);
}


