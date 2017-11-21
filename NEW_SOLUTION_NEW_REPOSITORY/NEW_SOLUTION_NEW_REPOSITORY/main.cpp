#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "functions.h"
#include "WorldCup.h"
#include "FinalMatch.h"

void initializeWorldCupData(WorldCup *);
void initializeFinalMatchData(FinalMatch *);

int main()
{
	const int SIZE = 20;

	int choice;

	WorldCup *worldCup = new WorldCup[SIZE];
	FinalMatch *finalMatch = new FinalMatch[SIZE];

	try
	{
		//Initialize the arrays
		initializeWorldCupData(worldCup);
		initializeFinalMatchData(finalMatch);

		for (int i = 0; i < SIZE; i++)
		{
			std::cout << "TEMS PARTICIPATED\n";
			worldCup[i].displayTeamsParticipated();
		}
		system("pause");
		system("cls");

		for (int i = 0; i < SIZE; i++)
			std::cout << worldCup[i] << std::endl;
		std::cout << std::endl;

		system("pause");
		system("cls");

		for (int i = 0; i < SIZE; i++)
			std::cout << finalMatch[i] << std::endl;
		std::cout << std::endl;





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
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "6) List data in key sequence (sorted)" << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "7) Print indented tree" << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "8) Efficency " << std::endl;

			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "0) EXIT\n";

			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Enter your choice: ";
			std::cin >> choice;

			std::cout << "\n\n";
			switch (choice)
			{
			case 1: yearChosen(); break;
			case 2: add(); break;
			case 3: remove_year(); break;
			case 4: display_year_data(); break;
			case 5: hashtable_list();  break;
			case 6: sort_data_by_choice();  break;
			case 7: pretty_print(); break;
				//case 8: count_efficiency(); break;
			case 0: system("CLS"); break;
			default:
				system("CLS");
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "INVALID CHOICE. Please enter a number 1 - 8!" << std::endl; break;

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
	//WRITE THE FILE
	std::ofstream clearFile;

	clearFile.open("worldCupGeneralData.txt", std::ofstream::trunc);
	clearFile.close();

	for (int i = 0; i < SIZE; i++)
		worldCup[i].outputFileWorldcupData();

	clearFile.open("TeamsByYear.txt", std::ofstream::trunc);
	clearFile.close();

	for (int i = 0; i < SIZE; i++)
		worldCup[i].outputFileTeamsParticipated();

	clearFile.open("FinalMatchData.txt", std::ofstream::trunc);
	clearFile.close();

	for (int i = 0; i < SIZE; i++)
		finalMatch[i].outputFileFinalMatch();


	//****************************************************************************************************************
	delete[] worldCup;
	delete[] finalMatch;
	system("pause");
	return 0;
}

void initializeWorldCupData(WorldCup *worldC) 
{
	int index = 0;																						

	std::string buffer;
	std::ifstream finWorldCup;
	std::ifstream finTeamsByYear;
	finWorldCup.open("worldCupGeneralData.txt");													

	if (!finWorldCup) throw "worldCupGeneralData.txt FILE COULD NOT BE OPENED"; /*2 operations*/	
	while (getline(finWorldCup, buffer))																
	{
		worldC[index].readFileWorldcupData(buffer);					
		index++;																					
	}
	finWorldCup.close();																			

	finTeamsByYear.open("TeamsByYear.txt");														

	if (!finTeamsByYear) throw "TeamsbyYear.txt FILE COULD NOT BE OPENED";							
	index = 0;																						
	while (getline(finTeamsByYear, buffer))
	{
																									
		worldC[index].readFileTeamsByYearData(buffer);					
		index++;																					
	}
	finTeamsByYear.close();																		
}

void initializeFinalMatchData(FinalMatch *finalM) 
{
	int index = 0;																	

	std::string buffer;

	std::ifstream finFinalMatch;
	finFinalMatch.open("FinalMatchData.txt");									

	if (!finFinalMatch) throw "FinalMatchData.txt FILE COULD NOT BE OPENED";	
	while (getline(finFinalMatch, buffer))
	{

		finalM[index].readFileFinalMatchData(buffer);
		index++;
	}
	finFinalMatch.close();
}