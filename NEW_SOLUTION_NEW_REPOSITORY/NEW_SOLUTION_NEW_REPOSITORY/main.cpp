#include "functions.h"
#include "initializerFunctions.h"

int main()
{
	std::cout << std::fixed << std::setprecision(2);

	//Declaring the trees
	Tree<int, WorldCup> yearHeldTree;					//WORKS FINE
	Tree<double, WorldCup> goalsPgameTree;				//WORKS FINE
	Tree<int, WorldCup> aveAtteTree;					//WORKS FINE
	Tree<int, WorldCup> totAtteTree;					//WORKS FINE
	Tree<int, WorldCup> numGamesTree;					//WORKS FINE
	Tree<int, TeamsParticipated> numTeamsTree;

	//Declaring the hash tables
	HashTable<int, WorldCup> worldCupData;				//WORKS FINE
	HashTable<int, FinalMatch> finalMatchData;			//WORKS FINE
	HashTable<int, TeamsParticipated> teamsByYear;		//WORKS FINE

	int choice;

	try
	{
		//Initializes the trees correctly
		initializeWorldCupData(yearHeldTree, goalsPgameTree, aveAtteTree, totAtteTree, numGamesTree, worldCupData, teamsByYear, numTeamsTree);

		//Initialize data into HashTable from "FinalMatch.txt" file
		initializeFinalMatchData(finalMatchData);

		//MENU STARTS HERE 
		// MAKE THIS A FUNCTION
		//MAIN MENU OF THE PROGRAM
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Welcome to World Cup Soccer Stats " << std::endl << std::endl;

		do {
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "The list of possible operations\n" << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "1) Add a new year stats" << std::endl; //this is <add new data>
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "2) Remove a year" << std::endl; //this is <delete data>
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "3) Find and display one data record of a year" << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "4) List data in hash table sequence" << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "5) List sorted data" << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "6) Print indented tree" << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "7) Efficency " << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "8) Load Factor " << std::endl;

			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "0) EXIT\n";

			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Enter your choice: ";
			std::cin >> choice;

			std::cout << "\n\n";
			switch (choice)
			{
				case 1: 
					add(yearHeldTree, goalsPgameTree, aveAtteTree, totAtteTree, numGamesTree, numTeamsTree, worldCupData, finalMatchData, teamsByYear);
					break;
				case 2: 
					remove_year(yearHeldTree, goalsPgameTree, aveAtteTree, totAtteTree, numGamesTree, numTeamsTree, worldCupData, finalMatchData, teamsByYear);
					break;
				case 3: 
					display_year_data(worldCupData, finalMatchData, teamsByYear);
					break;
				case 4: 
					hashtable_list(worldCupData, finalMatchData, teamsByYear);
					break;
				case 5: 
					sortDataByChoice(yearHeldTree, goalsPgameTree, aveAtteTree, totAtteTree, numGamesTree, numTeamsTree);
					break;
				case 6: 
					pretty_print(); 
					break;
				case 7:
					//EFFICENY HERE
					break;
				case 8:
					std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Current Hash Table load factor: " << worldCupData.loadFactor() << "%" << std::endl;
					break;
				case 0:
					system("pause");
					system("CLS"); break;
				default:
					system("CLS");
					std::cout << std::setw(WIDTH_BTW_LINES) << "" << "INVALID CHOICE. Please enter a number 1 - 8!" << std::endl; 
					break;
			}
			std::cin.clear();             //it takes care of the strings entered
			std::cin.ignore(INT_MAX, '\n');

			std::cout << std::endl << std::endl;
		} while (choice != 0);	//End of main do while loop
	}
	catch (char *msg)
	{
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << msg << "\n";
	}
	catch (...)
	{
		std::cout << "DEFAULT CATCHER" << std::endl;
	}

	std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	std::cout << std::endl << std::setw(WIDTH_BTW_LINES + 10) << "" << "\"GOODBYE\"" << std::endl << std::endl << std::endl << std::endl << std::endl;
	std::cout << "\n\n\n\n\n\n\n\n\n\n\n";


	//****************************************************************************************************************
	// WRITE BACK TO THE FILES
	finalMatchData.writeFinalMatchDataToTxt();
	teamsByYear.writeTeamsParticipatedToTxt();
	worldCupData.writeWorldCupGeneralDataToTxt();
	//****************************************************************************************************************

	system("pause");
	return 0;
}