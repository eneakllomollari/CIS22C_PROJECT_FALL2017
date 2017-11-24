#include "functions.h"
#include "HashTable.h"

int main()
{
	std::cout << std::fixed << std::setprecision(2);

	//Declaring the trees
	Tree<int, WorldCup> yearHeld;						//WORKS FINE
	Tree<double, WorldCup> goalsPgameTree;				//WORKS FINE
	Tree<int, WorldCup> aveAtteTree;					//WORKS FINE
	Tree<int, WorldCup> totAtteTree;					//WORKS FINE
	Tree<int, WorldCup> numGamesTree;					//WORKS FINE

	//Declaring the hash tables
	HashTable<int, WorldCup> worldCupData;				//WORKS FINE
	HashTable<int, FinalMatch> finalMatchData;			//WORKS FINE
	HashTable<int, TeamsParticipated> teamsByYear;		//WORKS FINE


	int choice;

	try
	{
		//Initializes the trees correctly
		initializeWorldCupData(yearHeld, goalsPgameTree, aveAtteTree, totAtteTree, numGamesTree, worldCupData, teamsByYear);
		
		//Initialize data into HashTable from "FinalMatch.txt" file
		initializeFinalMatchData(finalMatchData);

		//THIS WAS JUST FOR TESTING PURPOSES CAN BE DELETED
		/*std::cout << "Year held height:  " << yearHeld.getHeight() << std::endl;
		std::cout << "Goals per game height:  " << goalsPgameTree.getHeight() << std::endl;
		std::cout << "Average att height:  " << aveAtteTree.getHeight() << std::endl;
		std::cout << "Totat att height:  " << totAtteTree.getHeight() << std::endl;
		std::cout << "Num Games att height:  " << numGamesTree.getHeight() << std::endl << std::endl;

		std::cout << "WorldCupData load factor: " << worldCupData.getLoadFactor() << std::endl;
		std::cout << "finalMatchData load factor: " << finalMatchData.getLoadFactor()<< std::endl;
		std::cout << "teamsByYear load factor: " << teamsByYear.getLoadFactor() << std::endl << std::endl;
		system("pause");
		*/


		//MENU STARTS HERE 
		// MAKE THIS A FUNCTION
		//MAIN MENU OF THE PROGRAM
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Welcome to World Cup Soccer Stats " << std::endl << std::endl;

		do {
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "The list of possible operations\n" << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "1) Check previous years stats" << std::endl; // this is the <Team choice menu option>
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "2) Add a new year stats" << std::endl; //this is <add new data>
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "3) Remove a year" << std::endl; //this is <delete data>
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "4) Find and display one data record of a year" << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "5) List data in hash table sequence" << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "6) List sorted data" << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "7) Print indented tree" << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "8) Efficency " << std::endl;

			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "0) EXIT\n";

			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Enter your choice: ";
			std::cin >> choice;

			std::cout << "\n\n";
			switch (choice)
			{
				case 1: 
					yearChosen(); 
					break;
				case 2: 
					add();
					break;
				case 3: 
					remove_year(); 
					break;
				case 4: 
					display_year_data(worldCupData);
					break;
				case 5: 
					hashtable_list();  
					break;
				case 6: 
					sortDataByChoice(yearHeld, goalsPgameTree, aveAtteTree, totAtteTree, numGamesTree);
					break;
				case 7: 
					pretty_print(); 
					break;
				case 0:
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
		std::cout << msg << "\n";
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