#include "functions.h"

/*
	Pre: N/A

	Post: Upon successful completion, this function will display the World Cup Years to user

	!%@^@#%@$^  THIS CODE NEEDS TO BE FIXED !&@%$^$@*#^^ 
	It is using useless recursion. 

*/
//void yearChosen()
//{
//	//Declare Local Variables Objects
//	int choiceYear;
//
//	//First do while loop
//	do {
//		//Clear Screen
//		system("CLS");
//
//		//Display Years to User and ask for their choice
//		std::cout << std::setw(WIDTH_BTW_LINES + 2) << "" << "Years a world cup was held on:\n\n";
//		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "1)  1930\t\t\t2)  1934\n";
//		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "3)  1938\t\t\t4)  1950\n";
//		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "5)  1954\t\t\t6)  1958\n";
//		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "7)  1962\t\t\t8)  1966\n";
//		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "9)  1970\t\t\t10) 1974\n";
//		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "11) 1978\t\t\t12) 1982\n";
//		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "13) 1986\t\t\t14) 1990\n";
//		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "15) 1994\t\t\t16) 1998\n";
//		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "17) 2002\t\t\t18) 2006\n";
//		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "19) 2010\t\t\t20) 2014\n";
//		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "0) EXIT\n";
//		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Enter your choice: ";
//		std::cin >> choiceYear;
//		
//		//Skip lines for aesthetics
//		std::cout << "\n\n";
//
//		//Run user choice through swtich statement and run appropriate code
//		switch (choiceYear)
//		{
//			case 1:yearChosen(); break;
//			case 2:yearChosen(); break;
//			case 3:yearChosen(); break;
//			case 4:yearChosen(); break;
//			case 5:yearChosen(); break;
//			case 6:yearChosen(); break;
//			case 7:yearChosen(); break;
//			case 8:yearChosen(); break;
//			case 9:yearChosen(); break;
//			case 10:yearChosen(); break;
//			case 11:yearChosen(); break;
//			case 12:yearChosen(); break;
//			case 13:yearChosen(); break;
//			case 14:yearChosen(); break;
//			case 15:yearChosen(); break;
//			case 16:yearChosen(); break;
//			case 17:yearChosen(); break;
//			case 18:yearChosen(); break;
//			case 19:yearChosen(); break;
//			case 20:yearChosen(); break;
//			case 0:	system("CLS"); break;
//			default: 	system("CLS");
//				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "INVALID CHOICE. Please choose between 1 - 20!" << std::endl; 
//				system("CLS");
//				break;
//		 }//END SWITCH
//
//		 //it takes care of the strings entered
//		std::cin.clear();					
//		std::cin.ignore(INT_MAX, '\n');
//
//
//	} while (choiceYear != 0);	//End of main do while loop
//
//	//Clear Screen
//	//it makes the UI cleaner
//	system("CLS");              
//}


/*
	Pre: N/A

	Post:


	!^^@%@$%^ THIS CODE NEEDS FIXING.... LOOK NEAR END.... !^%^$@%^$@%@$
*/
void add(Tree<int, WorldCup>&yearHeld, Tree<double, WorldCup>&gpgT, Tree<int, WorldCup>&aveAttT, Tree<int, WorldCup>&totalAtt, Tree<int, WorldCup>&numGamesTree, 
	 HashTable<int, WorldCup>&worldCupData,  HashTable<int, FinalMatch>&finalMatchData,  HashTable<int, TeamsParticipated>&teamsByYear)
{
	//Declare local variables/constants/arrays
	WorldCup tempWorldCup;
	FinalMatch tempFinalMatch;
	TeamsParticipated tempTeamsParticipated;

	int yearHeldInsertCounter, gpgTInsertCounter, aveAttTInsertCounter, totalAttInsertCounter,
		numGamesTreeInsertCounter;
	int year, numGames, aveAttendance, totAttendance,
		numberOfTeams;
	double goalsPerGame;
	std::string	dummy, goalScoredFirstTeam, winningCountry, bestPlayer, hostCountry,
		goalScoredSecondTeam;

	std::string firstTeamFinalMatch, secondteamFinalMatch, stadiumName, cityHost,
		*teamsParticipatedArray;

	//Run entire code in "Try" Block #ExceptionHandling
	try {
		//Clear Screen
		system("CLS");

		std::cout << "\n\n\n\n";
		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Enter the year:               " << "                            ";
		std::cin >> year;
		getline(std::cin, dummy);
		
		//VALIDATE YEAR DATA
		while (std::cin.fail() || year < 1930)
		{
			if (std::cin.fail())
				std::cout << std::left << "\t" << "ERROR: INVALID INPUT! Use numeric digits(0-9) only while entering year..." << std::endl;
			else
				std::cout << std::left << "\t" << "ERROR: INVALID INPUT! Year cannot be less than 1930, as 1930 was the first World Cup...." << std::endl;

			std::cin.clear();
			std::cout << std::left << "\t" << "Re-Enter Year: ";
			std::cin >> year;
			getline(std::cin, dummy);
		}

		tempWorldCup.setYearHeld(year);
		tempFinalMatch.setYear(year);
		tempTeamsParticipated.setYearHeld(year);


		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Enter the number of teams:    " << "                            ";
		std::cin >> numberOfTeams;
		getline(std::cin, dummy);

		//VALIDATE NUMBER OF TEAMS
		while (std::cin.fail() || numberOfTeams < 2)
		{
			if (std::cin.fail())
				std::cout << std::left << "\t" << "ERROR: INVALID INPUT! Please use only numeric digits 0-9 while entering year..." << std::endl;
			else
				std::cout << std::left << "\t" << "ERROR: INVALID INPUT! Number of Teams cannot be less than 2... " << std::endl;

			std::cin.clear();
			std::cout << std::left << "\t" << "Re-Enter Number Of Teams: ";
			std::cin >> numberOfTeams;
			getline(std::cin, dummy);
		}
		
		tempTeamsParticipated.setNumTeams(numberOfTeams);
		teamsParticipatedArray = new std::string[numberOfTeams];
		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Enter the teams:                " << std::endl;
		for (int n = 0; n < numberOfTeams; n++)
		{
			std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "                                                          " <<  ">";
			getline(std::cin, teamsParticipatedArray[n]);
		}
		tempTeamsParticipated.setTeamsArr(teamsParticipatedArray);

		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Enter the winning country:    " << "                            ";
		getline(std::cin, winningCountry);
		tempWorldCup.setWinningTeam(winningCountry);

		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Enter the best player:        " << "                            ";
		getline(std::cin, bestPlayer);
		tempWorldCup.setGoldenBWinner(bestPlayer);

		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Enter the number of games:    " << "                            ";
		std::cin >> numGames;
		getline(std::cin, dummy);
		tempWorldCup.setNumGames(numGames);

		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Enter the goals per game:     " << "                            ";
		std::cin >> goalsPerGame;
		getline(std::cin, dummy);
		tempWorldCup.setGoalsPGame(goalsPerGame);

		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Enter the average attendance: " << "                            ";
		std::cin >> aveAttendance;
		getline(std::cin, dummy);
		tempWorldCup.setAveAtt(aveAttendance);

		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Enter the total attendance:   " << "                            ";
		std::cin >> totAttendance;
		getline(std::cin, dummy);
		tempWorldCup.setTotAtt(totAttendance);

		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Enter the host country:       " << "                            ";
		getline(std::cin, hostCountry);
		tempWorldCup.setHostCountry(hostCountry);

		std::cout << std::endl << std::endl;
		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Enter the final match data below " << std::endl;
		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Team #1: " << "                                     ";
		getline(std::cin, firstTeamFinalMatch);

		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Team #2: " << "                                     ";
		getline(std::cin, secondteamFinalMatch);
		tempFinalMatch.setTeams(firstTeamFinalMatch, secondteamFinalMatch);

		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Goals scored by " << firstTeamFinalMatch << " were: " << "              ";
		std::cin >> goalScoredFirstTeam;
		getline(std::cin, dummy);
		if (std::cin.fail()) throw "\n\t\t\t\t\t\t\t\tINVALID INPUT";

		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Goals scored by " << secondteamFinalMatch << " were: " << "              ";
		std::cin >> goalScoredSecondTeam;
		getline(std::cin, dummy);
		if (std::cin.fail()) throw "\n\t\t\t\t\t\t\t\tINVALID NUMBER OF GOALS";
		tempFinalMatch.setResult(goalScoredFirstTeam + " - " + goalScoredSecondTeam);


		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Enter the stadium's name:                     ";
		getline(std::cin, stadiumName);
		tempFinalMatch.setStadium(stadiumName);

		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Enter final match host city: " << "                 ";
		getline(std::cin, cityHost);
		tempFinalMatch.setCity(cityHost);
	}
	catch (char *msg)
	{
		std::cout << msg << std::endl;
	}
	catch (...)
	{
		std::cout << "ERROR" << std::endl;
	}
	std::cout << tempTeamsParticipated << std::endl;



	yearHeld.insert(tempWorldCup.getYearHeld(), tempWorldCup, yearHeldInsertCounter);//////////////////////////////////////////////////////////////////////////////////////////////////////
	gpgT.insert(tempWorldCup.getGoalsPerGame(), tempWorldCup, gpgTInsertCounter);
	aveAttT.insert(tempWorldCup.getAveAtt(), tempWorldCup, aveAttTInsertCounter);
	totalAtt.insert(tempWorldCup.getAveAtt(), tempWorldCup, totalAttInsertCounter);
	numGamesTree.insert(tempWorldCup.getNumGames(), tempWorldCup, numGamesTreeInsertCounter);
	worldCupData.put(tempWorldCup.getYearHeld(), tempWorldCup);
	finalMatchData.put(tempFinalMatch.getYear(), tempFinalMatch);
	teamsByYear.put(tempTeamsParticipated.getYearHeld(), tempTeamsParticipated);

	std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Operation Successful" << std::endl << std::endl;

	std::cout << yearHeldInsertCounter;
	std::cout << gpgTInsertCounter;
	std::cout << gpgTInsertCounter;
	std::cout << gpgTInsertCounter;
	std::cout << gpgTInsertCounter;



	std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "";
	system("pause");
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

//LISTS DATA IN HASHTABLE SEQUENCE
void hashtable_list(const HashTable<int, WorldCup>& worldCupData,const HashTable<int, FinalMatch>& finalMatchData, const HashTable<int, TeamsParticipated>& teamsByYear)
{

	system("CLS");
	std::cout << "\n\n\n";
	
	printGeneralWorldCupDataHeader();
	worldCupData.display();
	for (int i = 0; i < 148; i++)std::cout << "-";
	std::cout << "\n\n\n";

	system("pause");
	system("CLS");

	printFinalMatchDataHeader();
	finalMatchData.display();
	for (int i = 0; i < 120; i++)std::cout << "-";
	std::cout << "\n\n\n";
	
	system("pause");
	system("CLS");

	teamsByYear.display();
	
	std::cout << "\n\n\n";

	system("pause");
	system("CLS");
}

void pretty_print()
{
	//call bst.print();
}

void remove_year(Tree<int, WorldCup>& yearHeldTree, Tree<double, WorldCup>&goalsPerGameTree, Tree<int, WorldCup>& aveAtteTree, Tree<int, WorldCup>& totAttTree, Tree<int, WorldCup>& numGamesTree, 
	             Tree<int, TeamsParticipated>& numTeamsTree, HashTable<int, WorldCup>& worldCupData, HashTable<int, FinalMatch>&finalMatchData, HashTable<int, TeamsParticipated>& teamsByYear)
{
	int yearHeldTreeRemoveCounter, goalsPerGameTreeRemoveCounter, aveAtteTreeRemoveCounter,
		totAttTreeRemoveCounter, numGamesTreeRemoveCounter, numTeamsTreeRemoveCounter;

	int choiceYear;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "If you want to go back enter \" 0 \"" << std::endl;

	while (true)
	{
		try {
			std::cin.clear();
			std::cout << std::endl << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Enter the year here: ";
			std::cin >> choiceYear; std::cin.ignore();
			if (std::cin.fail()) throw 0;
			break;
		}
		catch (int i)
		{
			std::cout << std::endl << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "INVALID ENTRY! PLEASE ENTER A VALID FOUR DIGIT YEAR!";
		}
		catch (...)
		{
			std::cout << "UNHANDLED EXCEPTION" << std::endl;
		}
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}	   //Input Validation
	if (choiceYear == 0)
	{
		system("CLS");
		return;
	}

	WorldCup worldCupObject = worldCupData.get(choiceYear);
	TeamsParticipated teamsParticipatedObject = teamsByYear.get(choiceYear);
	FinalMatch finalMatchObject = finalMatchData.get(choiceYear);

	worldCupData.remove(choiceYear);
	finalMatchData.remove(choiceYear);
	teamsByYear.remove(choiceYear);
	yearHeldTree.remove(choiceYear, yearHeldTreeRemoveCounter);
	goalsPerGameTree.remove(worldCupObject.getGoalsPerGame(), goalsPerGameTreeRemoveCounter);
	aveAtteTree.remove(worldCupObject.getAveAtt(), aveAtteTreeRemoveCounter);
	totAttTree.remove(worldCupObject.getTotAtt(), totAttTreeRemoveCounter);
	numGamesTree.remove(worldCupObject.getNumGames(), numGamesTreeRemoveCounter);
	numTeamsTree.remove(teamsParticipatedObject.getNumTeams(), numTeamsTreeRemoveCounter);

	std::cout << yearHeldTreeRemoveCounter<<std::endl;
	std::cout << goalsPerGameTreeRemoveCounter << std::endl;
	std::cout << aveAtteTreeRemoveCounter << std::endl;
	std::cout << totAttTreeRemoveCounter << std::endl;
	std::cout << numGamesTreeRemoveCounter << std::endl;
	std::cout << numTeamsTreeRemoveCounter << std::endl;

}

void sortDataByChoice(const Tree<int, WorldCup>& yearTree, const  Tree<double, WorldCup>& goalsPerGameTree, const  Tree<int, WorldCup>& aveAttTree, const  Tree<int, WorldCup>& totAttTree,
	const Tree<int, WorldCup>& numGamesTree, const  Tree<int, TeamsParticipated>& teamsParticipated)
{
	int user_choice;

	system("CLS");
	do
	{

		try {
			std::cout << std::setw(WIDTH_BTW_LINES + 2) << "" << "You can sort data based on these attributes\n\n";
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "1) Year Held\n";
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "2) Goals per game\n";
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "3) Number of games\n";
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "4) Average Attendance\n";
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "5) Total Attendance\n";
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "6) Number of teams\n";
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "0) EXIT\n";

			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Enter your choice: ";
			std::cin >> user_choice;
			if (std::cin.fail() || user_choice < 0 || user_choice >= 7)throw "INVALID CHOICE. PLEASE ENTER A CHOICE 1-20 !";

			std::cout << "\n\n";
			switch (user_choice)
			{
			case 1:
				system("CLS");
				std::cout << "\n\n\n";
				printGeneralWorldCupDataHeader();
				yearTree.displayInOrder();
				std::cout << "\n\n";
				system("pause");
				system("CLS");
				break;
			case 2:
				system("CLS");
				std::cout << "\n\n\n";
				printGeneralWorldCupDataHeader();
				goalsPerGameTree.displayInOrder();
				std::cout << "\n\n";
				std::cout << "Average record is: " << goalsPerGameTree.getAverage() << " goals per game." << std::endl;
				std::cout << "Highest record is: " << goalsPerGameTree.getLargest() << " goals per game." << std::endl;
				std::cout << "Lowest  record is: " << goalsPerGameTree.getSmallest() << " goals per game." << std::endl;
				std::cout << "\n\n";
				system("pause");
				system("CLS");
				break;
			case 3:
				system("CLS");
				std::cout << "\n\n\n";
				printGeneralWorldCupDataHeader();
				numGamesTree.displayInOrder();
				std::cout << "\n\n";
				std::cout << "Average number of games is: " << numGamesTree.getAverage() << " games" << std::endl;
				std::cout << "Highest number of games is: " << numGamesTree.getLargest() << " games." << std::endl;
				std::cout << "Lowest  number of games is: " << numGamesTree.getSmallest() << " games." << std::endl;
				std::cout << "\n\n";
				system("pause");
				system("CLS");
				break;
			case 4:
				system("CLS");
				std::cout << "\n\n\n";
				printGeneralWorldCupDataHeader();
				aveAttTree.displayInOrder();
				std::cout << "\n\n";
				std::cout << "Average attendance is: " << aveAttTree.getAverage() << " spectators" << std::endl;
				std::cout << "Highest attendance is: " << aveAttTree.getLargest() << " spectators." << std::endl;
				std::cout << "Lowest  attendance is: " << aveAttTree.getSmallest() << " spectators." << std::endl;
				std::cout << "\n\n";
				system("pause");
				system("CLS");
				break;
			case 5:
				system("CLS");
				std::cout << "\n\n\n";
				printGeneralWorldCupDataHeader();
				totAttTree.displayInOrder();
				std::cout << "\n\n";
				std::cout << "Average number of overall attendance is: " << totAttTree.getAverage() << " spectators" << std::endl;
				std::cout << "Highest number of overall attendance is: " << totAttTree.getLargest() << " spectators." << std::endl;
				std::cout << "Lowest  number of overall attendance is: " << totAttTree.getSmallest() << " spectators." << std::endl;
				std::cout << "\n\n";
				system("pause");
				system("CLS");
				break;
			case 6:
				system("CLS");
				std::cout << "\n\n\n";
				teamsParticipated.displayInOrder();
				std::cout << "\n\n";
				std::cout << "Average number of teams participating is: " << teamsParticipated.getAverage() << " teams" << std::endl;
				std::cout << "Highest number of teams participating is: " << teamsParticipated.getLargest() << " teams." << std::endl;
				std::cout << "Lowest  number of teams participating is: " << teamsParticipated.getSmallest() << " teams." << std::endl;
				std::cout << "\n\n";
				system("pause");
				system("CLS");
				break;
			case 0:
				break;
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

//THIS FUNCTION IS 99% FINISHED
void display_year_data(const HashTable<int, WorldCup>& table, const HashTable <int, FinalMatch>&finalMatch, const HashTable<int, TeamsParticipated>&teams)
{
	int choiceYear;
	system("CLS");
	try
	{
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "If you want to go back enter \" 0 \"" << std::endl;

		while (true)
		{
			try {
				std::cin.clear();
				std::cout << std::endl << std::endl;
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Enter the year here: ";
				std::cin >> choiceYear; std::cin.ignore();
				if (std::cin.fail()) throw 0;
				break;
			}
			catch (int i)
			{
				std::cout << std::endl << std::endl;
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "INVALID ENTRY! PLEASE ENTER A VALID FOUR DIGIT YEAR!";
			}
			catch (...)
			{
				std::cout << "UNHANDLED EXCEPTION" << std::endl;
			}
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		}	   //Input Validation

		if (choiceYear == 0)
		{
			system("CLS");
			return;
		}

		WorldCup worldCupObject = table.get(choiceYear);
		FinalMatch finalMatchObject = finalMatch.get(choiceYear);
		TeamsParticipated teamsParticiaptedObject = teams.get(choiceYear);

		std::string *teamsParic = teamsParticiaptedObject.getTeamsArr();
		const int NUM_TEAMS = teamsParticiaptedObject.getNumTeams();

		system("CLS");
		std::cout << std::endl << std::endl << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "GENERAL INFORMATION" << std::endl << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "YEAR HELD:             " << worldCupObject.getYearHeld() << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "WINNING COUNTRY:       " << worldCupObject.getWinningTeam() << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "GOLDEN BOOT WINNER:    " << worldCupObject.getGoldenBootWinner() << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "GOALS PER GAME:        " << worldCupObject.getGoalsPerGame() << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "TOTAL ATTENDANCE:      " << worldCupObject.getTotAtt() << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "AVERAGE ATTENDANCE:    " << worldCupObject.getAveAtt() << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "NUMBER OF GAMES:       " << worldCupObject.getNumGames() << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "HOST COUNTRY:          " << worldCupObject.getHostCountry() << std::endl;
		std::cout << std::endl << std::endl << std::endl;

		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "FINAL MATCH DATA" << std::endl << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "FINALIST 1:            " << finalMatchObject.getTeam1() << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "FINALIST 2:            " << finalMatchObject.getTeam2() << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "FINAL RESULT:          " << finalMatchObject.getResult() << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "CITY IT WAS HELD IN:   " << finalMatchObject.getCity() << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "STADIUM IT WAS:        " << finalMatchObject.getStadium() << std::endl;
		std::cout << std::endl << std::endl << std::endl;

		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "TEAMS PARTICIPATED" << std::endl << std::endl;
		for (int i = 0; i < NUM_TEAMS; i++) std::cout << std::setw(WIDTH_BTW_LINES) << "" << i + 1 << ". " << teamsParic[i] << std::endl;
	}
	catch (char *msg)
	{
		std::cout << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << msg << std::endl;
	}
	catch (...)
	{
		std::cout << "ERROR! INVALID OPERATION!" << std::endl;
	}
	std::cout << "\n\n";
	std::cout << std::setw(WIDTH_BTW_LINES) << ""; system("pause");
	system("CLS");
}

void printGeneralWorldCupDataHeader()
{
	int numDashes = 148;
	for (int i = 0; i < numDashes; i++)std::cout << "_";
	std::cout << std::endl;
	std::cout << std::left << std::setw(6) << "Year";
	std::cout << std::left << std::setw(18) << "Winner";
	std::cout << std::left << std::setw(23) << "Best Player";
	std::cout << std::left << std::setw(13) << "#Games";
	std::cout << std::left << std::setw(20) << "Goals per game";
	std::cout << std::left << std::setw(24) << "Average Attendance";
	std::cout << std::left << std::setw(20) << "Total Attendance";
	std::cout << std::left << std::setw(20) << "Host Country";
	std::cout << std::endl;
	for (int i = 0; i < numDashes; i++)std::cout << "_";
	std::cout << std::endl;
}

void printFinalMatchDataHeader()
{
	int numDashes = 120;
	for (int i = 0; i < numDashes; i++)std::cout << "_";
	std::cout << std::endl;
	std::cout << std::left << std::setw(6) << "Year";
	std::cout << std::left << std::setw(18) << "Finalist 1";
	std::cout << std::left << std::setw(25) << "Finalist 2";
	std::cout << std::left << std::setw(20) << "Final Result";
	std::cout << std::left << std::setw(35) << "Stadium";
	std::cout << std::left << std::setw(40) << "City";
	std::cout << std::endl;
	for (int i = 0; i < numDashes; i++)std::cout << "_";
	std::cout << std::endl;
}