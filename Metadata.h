#ifndef METADATA_H_
#define METADATA_H_

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "WorldCup.h"
#include "Stack.h"
#include "FinalMatch.h"
#include "TeamsParticipated.h"
#include "HashTable.h"
#include "BinarySearchTree.h"

const int WIDTH_BTW_LINES = 50;

class Metadata
{
private:
	//Declaring the BinarySearchTrees
	BinarySearchTree<int, WorldCup*> *yearHeldBST;
	BinarySearchTree<int, TeamsParticipated*> *numTeamsbyYearBST;
	BinarySearchTree<int, FinalMatch*> *finalMatchBST;

	//Declaring the hash tables
	HashTable<int, WorldCup*> *worldCupdata;
	HashTable<int, FinalMatch*> *finalMatchdata;
	HashTable<int, TeamsParticipated*> *teamsByYear;

	//Declaring the recovery Stacks
	Stack<WorldCup*> *worldCupRecycleBin;
	Stack<FinalMatch*> *finalMatchRecycleBin;
	Stack<TeamsParticipated*> *teamsParticipatedRecycleBin;

	int numBinarySearchTrees;
	int numHashTables;
protected:
	void printGeneralWorldCupdataHeader();
	void printFinalMatchdataHeader();

	void readFileWorldcupdata(std::string&);
	void readFileFinalMatchdata(std::string&);
	void readFileTeamsByYeardata(std::string&);

	void displaydata(WorldCup*, FinalMatch*, TeamsParticipated*);

public:
	Metadata();
	~Metadata();

	void initializeWorldCupdataManager();
	void initializeFinalMatchdataManager();

	void addManager();
	void removeManager();
	void sortKeyManager();
	void displayKeyManager();
	void displayTableManager();
	void undoDeleteManager();
	void saveToInputFileManager();
	void efficencyManager();
	void clearRecycleStacksManager();

	int getNumBinarySearchTrees();
	int getNumHashTables();
};

/*Metadata Constructor*/
Metadata::Metadata()
{
	yearHeldBST = new BinarySearchTree<int, WorldCup*>;
	finalMatchBST = new BinarySearchTree<int, FinalMatch*>;
	numTeamsbyYearBST = new BinarySearchTree<int, TeamsParticipated*>;
	numBinarySearchTrees = 3;

	worldCupdata = new HashTable<int, WorldCup*>;
	finalMatchdata = new HashTable<int, FinalMatch*>;
	teamsByYear = new HashTable<int, TeamsParticipated*>;
	numHashTables = 3;

	worldCupRecycleBin = new Stack <WorldCup*>;
	finalMatchRecycleBin = new Stack <FinalMatch*>;
	teamsParticipatedRecycleBin = new Stack <TeamsParticipated*>;

	initializeWorldCupdataManager();
	initializeFinalMatchdataManager();
}

/*Metadata Destructor*/
Metadata::~Metadata()
{
	worldCupdata->insertdataAddressToStack(worldCupRecycleBin);
	finalMatchdata->insertdataAddressToStack(finalMatchRecycleBin);
	teamsByYear->insertdataAddressToStack(teamsParticipatedRecycleBin);

	saveToInputFileManager();
	clearRecycleStacksManager();

	delete yearHeldBST;
	delete numTeamsbyYearBST;
	numBinarySearchTrees = 0;

	delete worldCupdata;
	delete finalMatchdata;
	delete teamsByYear;
	numHashTables = 0;

	delete worldCupRecycleBin;
	delete finalMatchRecycleBin;
	delete teamsParticipatedRecycleBin;
}

/*
Decription: Menu for entering user data for creating the objects and inserting the data to trees and Hash Table 
Pre: none
Post: none
*/
void Metadata::addManager()
{
	system("CLS");

	//Operation counters
	int bstOpCounter = 0, hashTableOpCounter = 0;
	
	//Will hold the user input
	int year, numGames, aveAttendance, totAttendance, numberOfTeams;
	double goalsPerGame;

	std::string	dummy, goalScoredFirstTeam, winningCountry, bestPlayer, hostCountry, goalScoredSecondTeam;

	std::string firstTeamFinalMatch, secondteamFinalMatch, stadiumName, cityHost, *teamsParticipatedArray;

	//Run entire code in "Try" Block #ExceptionHandling
	try {
		//Clear Screen
		system("CLS");

		std::cout << "\n\n\n\n";
		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Enter \'-1\' to exit!" << std::endl << std::endl;
		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Enter the year:               " << "                            ";
		std::cin >> year;
		getline(std::cin, dummy);

		std::cout << std::endl << std::endl;

		//VALIDATE YEAR DATA
		while ((std::cin.fail() || year < 1930) && year != -1)
		{
			if (std::cin.fail())
			{
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "ERROR: INVALID INPUT! Use numeric digits(0-9) only ..." << std::endl;
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Re-Enter Year:                                            ";
				std::cin.clear();
				std::cin.ignore(1000, '\n');
			
			}
			else
			{
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "ERROR: INVALID INPUT! The first world cup was held in 1930 ..." << std::endl;
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Re-Enter Year:                                            ";
			}
			
			std::cin >> year;
			getline(std::cin, dummy);
			
		}

		if (year == -1) return;

		if (worldCupdata->contains(year) && finalMatchdata->contains(year) && teamsByYear->contains(year))
		{
			std::cout << std::endl << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "THIS YEAR ALREADY EXISTS IN OUR RECORDS!" << std::endl << std::endl;
			 std::cout << std::endl << std::endl;system("pause");
			system("CLS");
			return;
		}

		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Enter the number of teams:    " << "                            ";
		std::cin >> numberOfTeams;
		getline(std::cin, dummy);

		//VALIDATE NUMBER OF TEAMS
		while ((std::cin.fail() || numberOfTeams < 2) && numberOfTeams != -1)
		{
			if (std::cin.fail())
			{
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "ERROR: INVALID INPUT! Use numeric digits(0-9) only ..." << std::endl;
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Re-Enter Number of Teams:                                            ";
				std::cin.clear();
				std::cin.ignore(1000, '\n');

			}
			else
			{
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "ERROR: INVALID INPUT! Number of Teams must be greater than or equal to 2 " << std::endl;
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Re-Enter Number of Teams:                                            ";
			}

			std::cin >> numberOfTeams;
			getline(std::cin, dummy);

		}

		if (numberOfTeams == -1) return;

		teamsParticipatedArray = new std::string[numberOfTeams];
		
		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Enter the teams:                " << std::endl;
		for (int n = 0; n < numberOfTeams; n++)
		{
			std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "                                                          " << ">";
			getline(std::cin, teamsParticipatedArray[n]);
			if ((teamsParticipatedArray[n]) == "-1") return;
		}

		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Enter the winning country:    " << "                            ";
		getline(std::cin, winningCountry);
		if (winningCountry == "-1") return;

		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Enter the best player:        " << "                            ";
		getline(std::cin, bestPlayer);
		if (bestPlayer == "-1") return;

		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Enter the number of games:    " << "                            ";
		std::cin >> numGames;
		getline(std::cin, dummy);

		//VALIDATE NUMBER OF GAMES
		while ((std::cin.fail() || numGames < 0) && numGames != -1)
		{
			if (std::cin.fail())
			{
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "ERROR: INVALID INPUT! Use numeric digits(0-9) only ..." << std::endl;
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Re-Enter Number of Games:                                            ";
				std::cin.clear();
				std::cin.ignore(1000, '\n');

			}
			else
			{
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "ERROR: INVALID INPUT! Number of Games cannot be less than 0.... " << std::endl;
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Re-Enter Number of Teams:                                            ";
			}

			std::cin >> numGames;
			getline(std::cin, dummy);

		}

		if (numGames == -1) return;

		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Enter the goals per game:     " << "                            ";
		std::cin >> goalsPerGame;
		getline(std::cin, dummy);

		//VALIDATE GOALS PER GAME
		while ((std::cin.fail() || goalsPerGame < 0) && goalsPerGame != -1)
		{
			if (std::cin.fail())
			{
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "ERROR: INVALID INPUT! Use numeric digits(0-9) only ..." << std::endl;
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Re-Enter Goals Per Game:                                            ";
				std::cin.clear();
				std::cin.ignore(1000, '\n');

			}
			else
			{
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "ERROR: INVALID INPUT! Goals per game cannot be less than 0.... " << std::endl;
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Re-Enter Goals Per Game:                                            ";
			}

			std::cin >> goalsPerGame;
			getline(std::cin, dummy);

		}

		if (goalsPerGame == -1) return;

		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Enter the average attendance: " << "                            ";
		std::cin >> aveAttendance;
		getline(std::cin, dummy);

		//VALIDATE AVERAGE ATTENDANCE
		while ((std::cin.fail() || aveAttendance < 0) && aveAttendance != -1)
		{
			if (std::cin.fail())
			{
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "ERROR: INVALID INPUT! Use numeric digits(0-9) only ..." << std::endl;
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Re-Enter Average Attendance:                                            ";
				std::cin.clear();
				std::cin.ignore(1000, '\n');

			}
			else
			{
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "ERROR: INVALID INPUT! Average Attendance cannot be less than 0.... " << std::endl;
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Re-Enter Average Attendance:                                            ";
			}

			std::cin >> aveAttendance;
			getline(std::cin, dummy);

		}

		if (aveAttendance == -1) return;

		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Enter the total attendance:   " << "                            ";
		std::cin >> totAttendance;
		getline(std::cin, dummy);

		//VALIDATE TOTAL ATTENDANCE
		while ((std::cin.fail() || totAttendance < 0) && totAttendance != -1)
		{
			if (std::cin.fail())
			{
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "ERROR: INVALID INPUT! Use numeric digits(0-9) only ..." << std::endl;
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Re-Enter Total Attendance:                                            ";
				std::cin.clear();
				std::cin.ignore(1000, '\n');

			}
			else
			{
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "ERROR: INVALID INPUT! Total Attendance cannot be less than 0.... " << std::endl;
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Re-Enter Total Attendance:                                            ";
			}

			std::cin >> totAttendance;
			getline(std::cin, dummy);

		}

		if (totAttendance == -1) return;

		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Enter the host country:       " << "                            ";
		getline(std::cin, hostCountry);
		if (hostCountry == "-1") return;

		std::cout << std::endl << std::endl;
		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Enter the final match data below " << std::endl;
		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Team #1: " << "                                    >";
		getline(std::cin, firstTeamFinalMatch);
		if (firstTeamFinalMatch == "-1") return;

		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Team #2: " << "                                    >";
		getline(std::cin, secondteamFinalMatch);
		if (secondteamFinalMatch == "-1") return;

		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Goals scored by " << firstTeamFinalMatch << " were: " << std::right << std::setw(80);
		std::cin >> goalScoredFirstTeam;
		getline(std::cin, dummy);

		if (goalScoredFirstTeam == "-1") return;

		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Goals scored by " << secondteamFinalMatch << " were: " << std::right << std::setw(180);
		std::cin >> goalScoredSecondTeam;
		if (goalScoredSecondTeam == "-1") return;
		getline(std::cin, dummy);
	//	if (std::cin.fail()) throw "\n\t\t\t\t\t\t\t\tINVALID NUMBER OF GOALS";


		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Enter the stadium's name:                     ";
		getline(std::cin, stadiumName);
		if (stadiumName == "-1") return;

		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Enter final match host city:	                 ";
		getline(std::cin, cityHost);
		if (cityHost == "-1") return;
		
		
		//*************************************
		WorldCup* tempWorldCup = new WorldCup(year, winningCountry, bestPlayer, numGames, goalsPerGame, aveAttendance, totAttendance, hostCountry);
		FinalMatch* tempFinalMatch = new FinalMatch(year, teamsParticipatedArray, goalScoredFirstTeam + " - " + goalScoredSecondTeam, stadiumName, cityHost);
		TeamsParticipated* tempTeamsParticipated = new TeamsParticipated(year, numberOfTeams, teamsParticipatedArray);

		yearHeldBST->insert(tempWorldCup->getYearHeld(), tempWorldCup, bstOpCounter);
		numTeamsbyYearBST->insert(tempTeamsParticipated->getYearHeld(), tempTeamsParticipated, bstOpCounter);
		finalMatchBST->insert(tempFinalMatch->getYear(), tempFinalMatch, bstOpCounter);

		worldCupdata->put(tempWorldCup->getYearHeld(), tempWorldCup, hashTableOpCounter);
		finalMatchdata->put(tempFinalMatch->getYear(), tempFinalMatch, hashTableOpCounter);
		teamsByYear->put(tempTeamsParticipated->getYearHeld(), tempTeamsParticipated, hashTableOpCounter);

		system("CLS");
		std::cout << "\n\n\n\n";
		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << year <<  " is now inserted in our database." << std::endl << std::endl;

		system("CLS");
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Average number of operations performed in HashTables:               #" << hashTableOpCounter/3 << " operations." << std::endl;
		std::cout << std::endl;

		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Average number of operations performed in BST:                      #" << bstOpCounter/10 << " operations." << std::endl;
		std::cout << "\n\n";

	}
	catch (char *msg)
	{
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << msg << std::endl;
	}
	catch (...)
	{
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "ERROR" << std::endl;
	}


	std::cin.ignore(100, '\n');
	std::cout << std::setw(WIDTH_BTW_LINES) << "";
	std::cout << std::endl << std::endl;
	system("pause");
	system("CLS");
}

/*
Description: Remove Menu for user to delete data by year the user enters
Pre: none
Post: none
*/
void Metadata::removeManager()
{
	system("CLS");

	int bstOpCounter = 0, hashTableOpCounter = 0, searchHashTableCounter = 0;

	int choiceYear;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "If you want to go back enter \" 0 \"" << std::endl;
	try {
		while (true)
		{
			try {
				std::cin.clear();
				std::cout << std::endl << std::endl;
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Enter the year here: ";
				std::cin >> choiceYear; std::cin.ignore(100, '\n');
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
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "UNHANDLED EXCEPTION" << std::endl;
			}
			std::cin.clear();
			std::cin.ignore(100, '\n');
		}	   //Input Validation
		if (choiceYear == 0)
		{
			system("CLS");
			return;
		}

		WorldCup* worldCupObject = worldCupdata->get(choiceYear, searchHashTableCounter);
		TeamsParticipated* teamsParticipatedObject = teamsByYear->get(choiceYear, searchHashTableCounter);
		FinalMatch* finalMatchObject = finalMatchdata->get(choiceYear, searchHashTableCounter);

		worldCupdata->remove(choiceYear, hashTableOpCounter);
		finalMatchdata->remove(choiceYear, hashTableOpCounter);
		teamsByYear->remove(choiceYear, hashTableOpCounter);

		yearHeldBST->remove(worldCupObject->getYearHeld(), bstOpCounter);
		finalMatchBST->remove(finalMatchObject->getYear(), bstOpCounter);
		numTeamsbyYearBST->remove(teamsParticipatedObject->getYearHeld(), bstOpCounter);

		//Pushing the deleted files to the "recycle stacks"
		worldCupRecycleBin->push(worldCupObject);
		finalMatchRecycleBin->push(finalMatchObject);
		teamsParticipatedRecycleBin->push(teamsParticipatedObject);

		system("CLS");
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << choiceYear << " is now removed from the database." << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Average number of operations performed to search the HashTables:               #" << searchHashTableCounter / 3 << " operations." << std::endl;
		std::cout << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Average number of operations performed to remove from the HashTables:          #" << hashTableOpCounter / 3 << " operations." << std::endl;
		std::cout << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Average number of operations performed to remove from the BSTs:                #" << bstOpCounter / 10 << " operations." << std::endl;
		std::cout << std::endl;
	}
	catch (char *msg)
	{
		std::cout << std::endl << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << ""<< msg << std::endl;
	}
	catch (...)
	{
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "EXPECTION THROWN";
	}

	 std::cout << std::endl << std::endl;system("pause");
	system("CLS");
}

void Metadata::sortKeyManager()
{
	printGeneralWorldCupdataHeader();
	yearHeldBST->displayInOrder();
	std::cout << "\n\n";
	std::cout << std::endl << std::endl; system("pause");
	system("CLS");

}

/*
Discription: Menu for diplaying the data by key year 
Pre: none
Post: none
*/
void Metadata::displayKeyManager()
{
	int choiceYear;

	int opCounter = 0;

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
			std::cin.ignore(100, '\n');
		}	   //Input Validation

		if (choiceYear == 0)
		{
			system("CLS");
			return;
		}

		WorldCup* worldCupObject = worldCupdata->get(choiceYear, opCounter);
		FinalMatch* finalMatchObject = finalMatchdata->get(choiceYear, opCounter);
		TeamsParticipated* teamsParticipatedObject = teamsByYear->get(choiceYear, opCounter);

		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Average number of operations performed to search the HashTables:      #" << opCounter / 3 << std::endl;
		std::cout << "\n\n";

		displaydata(worldCupObject, finalMatchObject, teamsParticipatedObject);
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
	std::cout << std::setw(WIDTH_BTW_LINES) << "";  std::cout << std::endl << std::endl;system("pause");
	system("CLS");
}

/*
Description: Menu for Display The Hash Tables
Pre: none
Post: none
*/
void Metadata::displayTableManager()
{
	char userChoice;

	do
	{
		std::cout << "\n\n\n";

		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "HashTables in the database are shown below!" << std::endl << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "1. WorldCup_GeneralData" << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "2. FinalMatch_Data" << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "3. TeamsParticipated_Data" << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "0. Return to the Main Menu" << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Enter your choice here: ";
		std::cin >> userChoice;
		std::cin.ignore(100, '\n');

		system("CLS");
		switch (userChoice)
		{
		case '1':
			printGeneralWorldCupdataHeader();
			worldCupdata->display();
			for (int i = 0; i < 148; i++)std::cout << "-";
			std::cout << "\n\n\n";

			std::cout << std::endl << std::endl; system("pause");
			system("CLS");

			break;
		case '2':
			printFinalMatchdataHeader();
			finalMatchdata->display();
			for (int i = 0; i < 120; i++)std::cout << "-";
			std::cout << "\n\n\n";

			std::cout << std::endl << std::endl; system("pause");
			system("CLS");

			break;
		case '3':
			std::cout << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES-20) << "" << "ATTENTION!       You will need to scroll through the following screen in order to see all the data!" << std::endl;
			std::cout << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;
			system("pause");
			system("CLS");

			teamsByYear->display();

			std::cout << "\n\n\n";

			std::cout << std::endl << std::endl;
			system("pause");
			system("CLS");

			break;
		case '0':break;
		default:
			system("CLS");
			std::cout << "\n\n\n";
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "INVALID CHOICE! Please enter a choice 1 - 3!" << std::endl;
			break;
		}
	} while (userChoice != '0');
}

/*
Description: function for user's deleted data addres to be pushed to a stack so that deleted data can be retrived and inserted back
Pre: none
Post: none
*/
void Metadata::undoDeleteManager()
{
	int bstOperations = 0, hashTableOperations = 0;

	try 
	{	
		//Get the addresses that are at the top of the stack
		WorldCup* tempWC = worldCupRecycleBin->peek();
		TeamsParticipated* tempTP = teamsParticipatedRecycleBin->peek();
		FinalMatch* tempFM = finalMatchRecycleBin->peek();

		//pop the stacks
		worldCupRecycleBin->pop();
		teamsParticipatedRecycleBin->pop();
		finalMatchRecycleBin->pop();

		//Re-insert the addresses in the BSTs
		yearHeldBST->insert(tempWC->getYearHeld(), tempWC, bstOperations);
		finalMatchBST->insert(tempFM->getYear(), tempFM, bstOperations);
		numTeamsbyYearBST->insert(tempTP->getYearHeld(), tempTP, bstOperations);

		//Re-insert the addresses in the hash tables
		worldCupdata->put(tempWC->getYearHeld(), tempWC, hashTableOperations);
		finalMatchdata->put(tempFM->getYear(), tempFM, hashTableOperations);
		teamsByYear->put(tempTP->getYearHeld(), tempTP, hashTableOperations);

		std::cout << std::endl << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Recovery Successful!" << std::endl;
		std::cout << std::endl << std::endl;
	
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Averge number of operations performed on BSTs:                 #" << bstOperations / 10 << std::endl;
		std::cout << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Averge number of operations performed on HashTables:           #" << hashTableOperations / 3 << std::endl;
		std::cout << std::endl;
		std::cout << std::endl << std::endl; system("pause");
		system("CLS");
	}
	catch (char *msg)
	{
		std::cout << std::endl << std::endl << std::endl;
		std::cout << std::endl << std::endl << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << msg << std::endl;
		std::cout << std::endl << std::endl; system("pause");
		system("CLS");
	}
}

/*
description: function to save data to text file
Pre: none
Post: none
*/
void Metadata::saveToInputFileManager()
{
	//Saving to Files
	worldCupdata->writeWorldCupGeneraldataToTxt();
	finalMatchdata->writeFinalMatchdataToTxt();
	teamsByYear->writeTeamsParticipatedToTxt();
}

/*
description: function to clear the recycle bin stacks
Pre: none
Post: none
*/
void Metadata::clearRecycleStacksManager()
{
	//Clearing the Recycle Bins
	while (!worldCupRecycleBin->isEmpty())
	{
		WorldCup *WCObject = worldCupRecycleBin->peek();
		worldCupRecycleBin->pop();
		delete WCObject;
		WCObject = nullptr;
	}
	while (!teamsParticipatedRecycleBin->isEmpty())
	{
		TeamsParticipated* TPObject = teamsParticipatedRecycleBin->peek();
		teamsParticipatedRecycleBin->pop();
		delete TPObject;
		TPObject = nullptr;
	}
	while (!finalMatchRecycleBin->isEmpty())
	{
		FinalMatch* FMObject = finalMatchRecycleBin->peek();
		finalMatchRecycleBin->pop();
		delete FMObject;
		FMObject = nullptr;
	}
}

/*
Description: function to display the Laod factor of each hash table and collisions. Display the hieght of each tree
Pre: none
Post: none
*/
void Metadata::efficencyManager()
{
	int totalBSTHeight;
	system("CLS");
	//Since we are using BST hash tables, but with the same key the data of one BST is sufficent
	std::cout << std::endl << std::endl << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Current World Cup Hash Table load factor:                 " << worldCupdata->loadFactor() << "%" << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Current Final Match Hash Table load factor:               " << finalMatchdata->loadFactor() << "%" << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Current Teams Participated Hash Table load factor:        " << teamsByYear->loadFactor() << "%" << std::endl;
	std::cout << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "World Cup HashTable number of collisions:                 #" << worldCupdata->getNumCollisions() << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "World Cup HashTable longest chain:                        #" << worldCupdata->getLongestCollisionPath() << std::endl;
	std::cout << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Teams Participated HashTable number of collisions:        #" << teamsByYear->getNumCollisions() << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Teams Participated HashTable longest chain:               #" << teamsByYear->getLongestCollisionPath() << std::endl;
	std::cout << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Final Match HashTable number of collisions:               #" << finalMatchdata->getNumCollisions() << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Final Match HashTable longest chain:                      #" << finalMatchdata->getLongestCollisionPath() << std::endl;
	std::cout << std::endl << std::endl << std::endl;

	totalBSTHeight = yearHeldBST->getHeight() + numTeamsbyYearBST->getHeight() + finalMatchBST->getHeight();

	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Number of Nodes in the BST:           " << yearHeldBST->getCountNodes() << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Average height of BSTs:               "<< totalBSTHeight / numBinarySearchTrees  << std::endl;
	std::cout << std::endl << std::endl << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "";
}

/*
 Description: displays the header for world cup data
 Pre: none
 Post: none
*/
void Metadata::printGeneralWorldCupdataHeader()
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

/*
Description: displays the header for Final Match Data
Pre: none
Post: none
*/
void Metadata::printFinalMatchdataHeader()
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

void Metadata::displaydata(WorldCup*worldCupObject, FinalMatch*finalMatchObject, TeamsParticipated*teamsParticipatedObject)
{
	system("CLS");
	std::string *teamsParic = teamsParticipatedObject->getTeamsArr();
	const int NUM_TEAMS = teamsParticipatedObject->getNumTeams();

	std::cout << std::endl << std::endl << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "GENERAL INFORMATION" << std::endl << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "YEAR HELD:             " << worldCupObject->getYearHeld() << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "WINNING COUNTRY:       " << worldCupObject->getWinningTeam() << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "GOLDEN BOOT WINNER:    " << worldCupObject->getGoldenBootWinner() << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "GOALS PER GAME:        " << worldCupObject->getGoalsPerGame() << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "TOTAL ATTENDANCE:      " << worldCupObject->getTotAtt() << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "AVERAGE ATTENDANCE:    " << worldCupObject->getAveAtt() << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "NUMBER OF GAMES:       " << worldCupObject->getNumGames() << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "HOST COUNTRY:          " << worldCupObject->getHostCountry() << std::endl;
	std::cout << std::endl << std::endl << std::endl;

	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "FINAL MATCH DATA" << std::endl << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "FINALIST 1:            " << finalMatchObject->getTeam1() << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "FINALIST 2:            " << finalMatchObject->getTeam2() << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "FINAL RESULT:          " << finalMatchObject->getResult() << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "CITY IT WAS HELD IN:   " << finalMatchObject->getCity() << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "STADIUM PLAYED IN:     " << finalMatchObject->getStadium() << std::endl;
	std::cout << std::endl << std::endl << std::endl;

	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "TEAMS PARTICIPATED" << std::endl << std::endl;
	for (int i = 0; i < NUM_TEAMS; i++)std::cout << std::setw(WIDTH_BTW_LINES) << "" << i + 1 << ". " << teamsParic[i] << std::endl;
}

int Metadata::getNumBinarySearchTrees()
{
	return numBinarySearchTrees;
}

int Metadata::getNumHashTables()
{
	return numHashTables;
}

#include "Metadata.h"

void Metadata::initializeWorldCupdataManager()
{
	//Declare Local Variables/Objects
	std::string buffer;
	std::ifstream finWorldCup;
	std::ifstream finTeamsByYear;

	//Open file for reading
    std::string wcgeneral;
    std::cout << "Enter the world cup general data directory: ";
    getline(std::cin,wcgeneral);

    finWorldCup.open(wcgeneral);

	//If the file is unable to open, then throw an error
	if (!finWorldCup) throw "worldCupGeneraldata.txt FILE COULD NOT BE OPENED IN initializeWorldCupdata()"; /*2 operations*/

	//Read the file line by line and initialize data
	while (getline(finWorldCup, buffer))
		readFileWorldcupdata(buffer);

	//Close the ifstream object
	finWorldCup.close();

	//*************************************

	//Open second file for reading
    std::string teamsbyyear;
    std::cout << "Enter the teams by year data directory: ";
    getline(std::cin,teamsbyyear);

	finTeamsByYear.open(teamsbyyear);

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
    std::string finMatch;
	std::cout << "Enter the final match data directory: ";
	getline(std::cin, finMatch);

	finFinalMatch.open(finMatch);

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
	yearHeldBST->insert(tempWorldCup->getYearHeld(), tempWorldCup, insertCounter);

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
	finalMatchBST->insert(temp_FinalMatch_object->getYear(), temp_FinalMatch_object,putCounter);
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

	numTeamsbyYearBST->insert(yearHeld, tempTeams_Object, numTeamsByYearBinarySearchTreeCounter);
}
#endif // !HEAD_NODE
