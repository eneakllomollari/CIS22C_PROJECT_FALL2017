#include "functions.h"

//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************


void initializeWorldCupData(Tree<int, WorldCup>& yearHeld, Tree<double, WorldCup>& gpgT, Tree<int, WorldCup>&aveAttT,
	Tree<int, WorldCup>& totalAtt, Tree<int, WorldCup>&numGames, HashTable<int, WorldCup>&winnerTeamTable, HashTable<int, TeamsParticipated>&teamsParticTable)
{
	int index = 0;

	std::string buffer;
	std::ifstream finWorldCup;
	std::ifstream finTeamsByYear;
	finWorldCup.open("worldCupGeneralData.txt");
	if (!finWorldCup) throw "worldCupGeneralData.txt FILE COULD NOT BE OPENED"; /*2 operations*/

	while (getline(finWorldCup, buffer))
		readFileWorldcupData(buffer, yearHeld, gpgT, aveAttT, totalAtt, numGames, winnerTeamTable);	//This is the function that initializes everything, 
	finWorldCup.close();

	//Here starts the teams by year function that needs to be done similar to the previous one
	finTeamsByYear.open("TeamsByYear.txt");

	if (!finTeamsByYear) throw "TeamsbyYear.txt FILE COULD NOT BE OPENED";
	index = 0;

	while (getline(finTeamsByYear, buffer))
		readFileTeamsByYearData(buffer, teamsParticTable);
	finTeamsByYear.close();
}

void readFileWorldcupData(std::string &line, Tree<int, WorldCup>& yearHeld, Tree<double, WorldCup>& gpgT, Tree<int, WorldCup>&aveAttT, Tree<int, WorldCup>& totalAtt,
						  Tree<int,WorldCup>&numGames, HashTable<int,WorldCup>& winnerTeamTable)
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

void initializeFinalMatchData(HashTable<int, FinalMatch>& finalMatch_hashTable)
{
	int index = 0;

	std::string buffer;

	std::ifstream finFinalMatch;
	finFinalMatch.open("FinalMatchData.txt");

	if (!finFinalMatch) throw "FinalMatchData.txt FILE COULD NOT BE OPENED";
	while (getline(finFinalMatch, buffer))
	{
		readFileFinalMatchData(buffer, finalMatch_hashTable);
	}
	finFinalMatch.close();

}

void readFileTeamsByYearData(std::string& line, HashTable<int,TeamsParticipated>& teamsParticTable)
{
	std::string *tempArray_Teams;
	int numTeamsParticipated;
	
	int yearHeld = std::stoi(line.substr(0, 4));
	
	line = line.substr(6);
	std::istringstream buffer(line);
	std::string temp;
	int  size = 0;

	// checks size 
	for (auto &i : line)
		if (i == ',') size++;
	size += 1;

	numTeamsParticipated = size;
	tempArray_Teams = new std::string[numTeamsParticipated];

	int index = 0;
	while (getline(buffer, temp, ','))
	{
		temp = temp.substr(1);
		tempArray_Teams[index] = temp;
		index++;
	}
	TeamsParticipated tempTeams_Object(numTeamsParticipated, tempArray_Teams);
	teamsParticTable.put(yearHeld, tempTeams_Object);
}

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

//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************
//************************************************************************************************************************************************************************************************


void writeWorldCupGeneralDataToTxt(WorldCup wC[], const int SIZE)
{
	std::ofstream clearFile;

	clearFile.open("worldCupGeneralData.txt", std::ofstream::trunc);
	clearFile.close();

	for (int i = 0; i < SIZE; i++)
		wC[i].outputFileWorldcupData();
}

//void writeTeamsParticipatedToTxt(WorldCup wc[], const int SIZE)
//{
//	std::ofstream clearFile("TeamsByYear.txt", std::ofstream::trunc);
//	clearFile.close();
//
//	for (int i = 0; i < SIZE; i++)
//		wc[i].outputFileTeamsParticipated();
//}

//void writeFinalMatchDataToTxt(FinalMatch fM[], const int SIZE)
//{
//	std::ofstream clearFile("FinalMatchData.txt", std::ofstream::trunc);
//	clearFile.close();
//
//	for (int i = 0; i < SIZE; i++)
//		fM[i].outputFileFinalMatch();
//}

void yearChosen()
{
	int choiceYear;


	//First do while loop
	do {
		system("CLS");

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
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "INVALID CHOICE. Please choose between 1 - 20!" << std::endl; break;
			system("CLS");
		}
		std::cin.clear();					//it takes care of the strings entered
		std::cin.ignore(INT_MAX, '\n');
	} while (choiceYear != 0);	//End of main do while loop

	system("CLS");              //it makes the UI cleaner
}

//IMPORTANT NOTICE: how to print year if someone adds one?
void add()
{
	//*******************************************************************************************
	//The user should be given a choice to exit in the middle of entering the data
	//*******************************************************************************************
	const int MAX_NUM_TEAMS = 50;
	int year;
	int numberOfTeams;
	int goalScoredFirstTeam, goalScoredSecondTeam;
	std::string teams[MAX_NUM_TEAMS];
	std::string FirstTeamFinalMatch, SecondteamFinalMatch;
	std::string stadiumName;
	std::string cityHost;


	try {
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


//USELESS CODE FOR NOW
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

void sort_data_by_choice(Tree<int, WorldCup> yearTree, Tree<double, WorldCup> goalsPerGameTree, Tree<int, WorldCup> aveAttTree, Tree<int, WorldCup> totAttTree,Tree<int,WorldCup> numGamesTree)
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

//IMPORTANT NOTE: How to print years if someone deletes a year?
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


//
//void writeGeneralDataToTxt(WorldCup *wc, const int SIZE)
//{
//	std::ofstream clearFile;
//
//	clearFile.open("worldCupGeneralData.txt", std::ofstream::trunc);
//	clearFile.close();
//
//	for (int i = 0; i < SIZE; i++)
//		wc[i].outputFileWorldcupData();
//}
//
//void writeTeamsByYearToTxt(WorldCup *wC, const int SIZE)
//{
//	std::ofstream clearFile;
//
//	clearFile.open("TeamsByYear.txt", std::ofstream::trunc);
//	clearFile.close();
//
//	for (int i = 0; i < SIZE; i++)
//		wC[i].outputFileTeamsParticipated();
//
//}
//
//void writeFinalMatchDataToTxt(FinalMatch *fM, const int SIZE)
//{
//	std::ofstream clearFile;
//	clearFile.open("FinalMatchData.txt", std::ofstream::trunc);
//	clearFile.close();
//
//	for (int i = 0; i < SIZE; i++)
//		fM[i].outputFileFinalMatch();
//
//
//
//}