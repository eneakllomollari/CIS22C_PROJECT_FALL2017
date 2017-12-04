#include "HeadNode.h"

HeadNode::HeadNode()
{
	winnerTree = new Tree <std::string, WorldCup*>;
	yearHeldTree = new Tree <int, WorldCup*>;
	goalsPgameTree = new Tree<double, WorldCup*>;
	aveAtteTree = new Tree <int, WorldCup*>;
	totAtteTree = new Tree <int, WorldCup*>;
	numGamesTree = new Tree <int, WorldCup*>;
	numTeamsTree = new Tree <int, TeamsParticipated*>;
	finalMatchTree = new Tree<int, FinalMatch*>;

	worldCupData = new HashTable<int, WorldCup*>;
	finalMatchData = new HashTable<int, FinalMatch*>;
	teamsByYear = new HashTable<int, TeamsParticipated*>;

	worldCupRecycleBin = new Stack <WorldCup*>;
	finalMatchRecycleBin = new Stack <FinalMatch*>;
	teamsParticipatedRecycleBin = new Stack <TeamsParticipated*>;

	initializeWorldCupDataManager();
	initializeFinalMatchDataManager();
}

HeadNode::~HeadNode()
{
	saveToInputFileManager();

	delete winnerTree;
	delete yearHeldTree;
	delete goalsPgameTree;
	delete aveAtteTree;
	delete totAtteTree;
	delete numGamesTree;
	delete numTeamsTree;
	delete finalMatchTree;

	delete worldCupData;
	delete finalMatchData;
	delete teamsByYear;
	
	delete worldCupRecycleBin;
	delete finalMatchRecycleBin;
	delete teamsParticipatedRecycleBin;
}

void HeadNode::addManager()
{
	system("CLS");

	//Operation counters
	int yearHeldInsertCounter = 0, gpgTInsertCounter = 0, aveAttTInsertCounter = 0, totalAttInsertCounter = 0, numTeamsTreeInsertCounter = 0, numGamesTreeInsertCounter = 0;
	int putCounterYearHeld = 0, putCounterGetYear = 0, putCounterTeamsParticYearHeld = 0;
	int numTeamsTreeInsertCounter1 = 0, winnerTreeInsertCounter = 0;
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
		//Exit if the user chooses to 
		if (year == -1) return;

		std::cout << std::endl << std::endl;
		//VALIDATE YEAR DATA
		while (std::cin.fail() || year < 1930 && year != -1)
		{
			if (std::cin.fail())
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "ERROR: INVALID INPUT! Use numeric digits(0-9) only ..." << std::endl;
			else
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "ERROR: INVALID INPUT! The first world cup was held in 1930 ..." << std::endl;
			std::cin.clear();
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Re-Enter Year:                                          ";
			std::cin >> year;
			getline(std::cin, dummy);
		}
		if (year == -1) return;
		if (worldCupData->contains(year) && finalMatchData->contains(year) && teamsByYear->contains(year))
		{
			std::cout << std::endl << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "THIS YEAR ALREADY EXISTS IN OUR RECORDS!" << std::endl << std::endl;
			system("pause");
			system("CLS");
			return;
		}

		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Enter the number of teams:    " << "                            ";
		std::cin >> numberOfTeams;
		getline(std::cin, dummy);
		if (numberOfTeams == -1) return;

		//VALIDATE NUMBER OF TEAMS
		while (std::cin.fail() || numberOfTeams < 2)
		{
			if (std::cin.fail())
			{
				std::cout << std::endl << std::endl;
				std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "ERROR: INVALID INPUT! Please use only numeric digits 0-9 while entering year..." << std::endl;
			}
			else
			{
				std::cout << std::endl << std::endl;
				std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "ERROR: INVALID INPUT! Number of Teams cannot be less than 2... " << std::endl;
			}
			std::cin.clear();
			std::cout << std::left << "\t" << "Re-Enter Number Of Teams: ";
			std::cin >> numberOfTeams;
			getline(std::cin, dummy);
		}

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
		if (numGames == -1) return;

		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Enter the goals per game:     " << "                            ";
		std::cin >> goalsPerGame;
		if (goalsPerGame == -1) return;
		getline(std::cin, dummy);

		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Enter the average attendance: " << "                            ";
		std::cin >> aveAttendance;
		if (aveAttendance == -1) return;
		getline(std::cin, dummy);

		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Enter the total attendance:   " << "                            ";
		std::cin >> totAttendance;
		getline(std::cin, dummy);
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
		if (goalScoredFirstTeam == "-1") return;
		getline(std::cin, dummy);
		if (std::cin.fail()) throw "\n\t\t\t\t\t\t\t\tINVALID INPUT";

		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Goals scored by " << secondteamFinalMatch << " were: " << std::right << std::setw(180);
		std::cin >> goalScoredSecondTeam;
		if (goalScoredSecondTeam == "-1") return;
		getline(std::cin, dummy);
		if (std::cin.fail()) throw "\n\t\t\t\t\t\t\t\tINVALID NUMBER OF GOALS";


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

		winnerTree->insert(tempWorldCup->getWinningTeam(), tempWorldCup, winnerTreeInsertCounter);
		yearHeldTree->insert(tempWorldCup->getYearHeld(), tempWorldCup, yearHeldInsertCounter);
		goalsPgameTree->insert(tempWorldCup->getGoalsPerGame(), tempWorldCup, gpgTInsertCounter);
		aveAtteTree->insert(tempWorldCup->getAveAtt(), tempWorldCup, aveAttTInsertCounter);
		totAtteTree->insert(tempWorldCup->getTotAtt(), tempWorldCup, totalAttInsertCounter);
		numGamesTree->insert(tempWorldCup->getNumGames(), tempWorldCup, numGamesTreeInsertCounter);
		numTeamsTree->insert(tempTeamsParticipated->getNumTeams(), tempTeamsParticipated, numTeamsTreeInsertCounter);

		worldCupData->put(tempWorldCup->getYearHeld(), tempWorldCup, putCounterYearHeld);
		finalMatchData->put(tempFinalMatch->getYear(), tempFinalMatch, putCounterGetYear);
		teamsByYear->put(tempTeamsParticipated->getYearHeld(), tempTeamsParticipated, putCounterTeamsParticYearHeld);

		system("CLS");
		std::cout << "\n\n\n\n";

		std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Operation Successful" << std::endl << std::endl;

		system("CLS");
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Inserted into World Cup      hash table:               #" << putCounterYearHeld << " operations." << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Inserted into Final Match    hash table:               #" << putCounterGetYear << " operations." << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Inserted into Teams By Year  hash table:               #" << putCounterTeamsParticYearHeld << " operations." << std::endl;
		std::cout << std::endl;

		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Inserted into year tree:                                #" << yearHeldInsertCounter << " operations." << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Inserted into goals per game tree:                      #" << gpgTInsertCounter << " operations." << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Inserted into average attendance tree:                  #" << aveAttTInsertCounter << " operations." << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Inserted into total attendance tree:                    #" << totalAttInsertCounter << " operations." << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Inserted into number of games tree:                     #" << numGamesTreeInsertCounter << " operations." << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Inserted into number of teams tree:                     #" << numTeamsTreeInsertCounter << " operations." << std::endl;
		std::cout << "\n\n";

	}
	catch (char *msg)
	{
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << msg << std::endl;
	}
	catch (...)
	{
		std::cout << "ERROR" << std::endl;
	}


	std::cin.ignore(INT_MAX, '\n');
	std::cout << std::setw(WIDTH_BTW_LINES) << "";
	system("PAUSE");
	system("CLS");
}

void HeadNode::removeManager()
{
	system("CLS");

	int yearHeldTreeRemoveCounter = 0, goalsPerGameTreeRemoveCounter = 0, aveAtteTreeRemoveCounter = 0,
		totAttTreeRemoveCounter = 0, numGamesTreeRemoveCounter = 0, numTeamsTreeRemoveCounter = 0, finalMatchCounter = 0;
	int winnerTreeRemoveCounter = 0;
	int getCounterWorldCup, getCounterTeamsPaticipated, getCounterFinalMatch, hashRemoveCounterWC, hashRemoveCounterFM, hashRemoveCounterTY;

	int choiceYear;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "If you want to go back enter \" 0 \"" << std::endl;
	try {
		while (true)
		{
			try {
				std::cin.clear();
				std::cout << std::endl << std::endl;
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Enter the year here: ";
				std::cin >> choiceYear; std::cin.ignore(INT_MAX, '\n');
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

		WorldCup* worldCupObject = worldCupData->get(choiceYear, getCounterWorldCup);
		TeamsParticipated* teamsParticipatedObject = teamsByYear->get(choiceYear, getCounterTeamsPaticipated);
		FinalMatch* finalMatchObject = finalMatchData->get(choiceYear, getCounterFinalMatch);

		worldCupData->remove(choiceYear, hashRemoveCounterWC);
		finalMatchData->remove(choiceYear, hashRemoveCounterFM);
		teamsByYear->remove(choiceYear, hashRemoveCounterTY);

		winnerTree->remove(worldCupObject->getWinningTeam(), winnerTreeRemoveCounter);
		yearHeldTree->remove(worldCupObject->getYearHeld(), yearHeldTreeRemoveCounter);
		goalsPgameTree->remove(worldCupObject->getGoalsPerGame(), goalsPerGameTreeRemoveCounter);
		aveAtteTree->remove(worldCupObject->getAveAtt(), aveAtteTreeRemoveCounter);
		totAtteTree->remove(worldCupObject->getTotAtt(), totAttTreeRemoveCounter);
		numGamesTree->remove(worldCupObject->getNumGames(), numGamesTreeRemoveCounter);
		numTeamsTree->remove(teamsParticipatedObject->getNumTeams(), numTeamsTreeRemoveCounter);
		finalMatchTree->remove(finalMatchObject->getYear(), finalMatchCounter);

		//Pushing the deleted files to the "recycle stacks"
		worldCupRecycleBin->push(worldCupObject);
		finalMatchRecycleBin->push(finalMatchObject);
		teamsParticipatedRecycleBin->push(teamsParticipatedObject);

		system("CLS");
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Removed from  World Cup      hash table:               #" << hashRemoveCounterWC << " operations." << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Removed from  Final Match    hash table:               #" << hashRemoveCounterFM << " operations." << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Removed from  Teams By Year  hash table:               #" << hashRemoveCounterTY << " operations." << std::endl;
		std::cout << std::endl;

		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Removed from year tree:                                #" << yearHeldTreeRemoveCounter << " operations." << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Removed from goals per game tree:                      #" << goalsPerGameTreeRemoveCounter << " operations." << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Removed from average attendance tree:                  #" << aveAtteTreeRemoveCounter << " operations." << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Removed from total attendance tree:                    #" << totAttTreeRemoveCounter << " operations." << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Removed from number of games tree:                     #" << numGamesTreeRemoveCounter << " operations." << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Removed from number of teams tree:                     #" << numTeamsTreeRemoveCounter << " operations." << std::endl;
		std::cout << "\n\n";
	}
	catch (char *msg)
	{
		std::cout << std::endl << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << msg << std::endl;
	}
	catch (...)
	{
		std::cout << "EXPECTION THROWN";
	}
	system("PAUSE");
	system("CLS");
}

void HeadNode::searchManager()
{
	int yearChoice, choice;
	std::string winnerChoice;

	WorldCup *worldCupObject;
	FinalMatch* finalMatchObject;
	TeamsParticipated* teamsParticipatedObject;
	
	try {
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "\tSearch by:" << std::endl << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "1. Year" << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "2. Winner" << std::endl << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Enter your choice here: ";
		std::cin >> choice;
		std::cin.ignore(INT_MAX, '\n');

		switch (choice)
		{
		case 1:
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Enter the year: ";
			std::cin >> yearChoice;

			worldCupObject = yearHeldTree->searchByKey(yearChoice);
			finalMatchObject = finalMatchTree->searchByKey(worldCupObject->getYearHeld());

			displayData(worldCupObject, finalMatchObject);
			system("pause");
			break;
		
		case 2:
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Enter the winner: ";
			getline(std::cin, winnerChoice, '\n');
			
			Stack<WorldCup*>* myList = new Stack<WorldCup*>;
			winnerTree->searchByKey(winnerChoice, myList);

			
			if (!myList->isEmpty())
			{
				printGeneralWorldCupDataHeader();
				myList->displayStack();
			}
			else throw "THIS TEAM HAS NOT WON A COMPETITION";
			
			std::cout << std::endl << std::endl;
			system("pause");
			system("CLS");

			while (!myList->isEmpty())
			{
				worldCupObject = myList->peek();
				myList->pop();
				finalMatchObject = finalMatchTree->searchByKey(worldCupObject->getYearHeld());
				displayData(worldCupObject, finalMatchObject);
				system("pause");
			}
			std::cout << std::endl << std::endl;
					
			delete myList;
			break;
		}
		std::cout << std::endl;
	}
	catch (char *msg)
	{
		std::cout << std::endl << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << msg << std::endl;
		system("pause");
	}
}

void HeadNode::sortManager()
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
				yearHeldTree->displayInOrder();
				std::cout << "\n\n";
				system("pause");
				system("CLS");
				break;
			case 2:
				system("CLS");
				std::cout << "\n\n\n";
				printGeneralWorldCupDataHeader();
				goalsPgameTree->displayInOrder();
				std::cout << "\n\n";
				std::cout << "Average record is: " << goalsPgameTree->getAverage() << " goals per game." << std::endl;
				std::cout << "Highest record is: " << goalsPgameTree->getLargest() << " goals per game." << std::endl;
				std::cout << "Lowest  record is: " << goalsPgameTree->getSmallest() << " goals per game." << std::endl;
				std::cout << "\n\n";
				system("pause");
				system("CLS");
				break;
			case 3:
				system("CLS");
				std::cout << "\n\n\n";
				printGeneralWorldCupDataHeader();
				numGamesTree->displayInOrder();
				std::cout << "\n\n";
				std::cout << "Average number of games is: " << numGamesTree->getAverage() << " games" << std::endl;
				std::cout << "Highest number of games is: " << numGamesTree->getLargest() << " games." << std::endl;
				std::cout << "Lowest  number of games is: " << numGamesTree->getSmallest() << " games." << std::endl;
				std::cout << "\n\n";
				system("pause");
				system("CLS");
				break;
			case 4:
				system("CLS");
				std::cout << "\n\n\n";
				printGeneralWorldCupDataHeader();
				aveAtteTree->displayInOrder();
				std::cout << "\n\n";
				std::cout << "Average attendance is: " << aveAtteTree->getAverage() << " spectators" << std::endl;
				std::cout << "Highest attendance is: " << aveAtteTree->getLargest() << " spectators." << std::endl;
				std::cout << "Lowest  attendance is: " << aveAtteTree->getSmallest() << " spectators." << std::endl;
				std::cout << "\n\n";
				system("pause");
				system("CLS");
				break;
			case 5:
				system("CLS");
				std::cout << "\n\n\n";
				printGeneralWorldCupDataHeader();
				totAtteTree->displayInOrder();
				std::cout << "\n\n";
				std::cout << "Average number of overall attendance is: " << totAtteTree->getAverage() << " spectators" << std::endl;
				std::cout << "Highest number of overall attendance is: " << totAtteTree->getLargest() << " spectators." << std::endl;
				std::cout << "Lowest  number of overall attendance is: " << totAtteTree->getSmallest() << " spectators." << std::endl;
				std::cout << "\n\n";
				system("pause");
				system("CLS");
				break;
			case 6:
				system("CLS");
				std::cout << "\n\n\n";
				numTeamsTree->displayInOrder();
				std::cout << "\n\n";
				std::cout << "Average number of teams participating is: " << numTeamsTree->getAverage() << " teams" << std::endl;
				std::cout << "Highest number of teams participating is: " << numTeamsTree->getLargest() << " teams." << std::endl;
				std::cout << "Lowest  number of teams participating is: " << numTeamsTree->getSmallest() << " teams." << std::endl;
				std::cout << "\n\n";
				system("pause");
				system("CLS");
				break;
			case 0:
				system("pause");
				break;
			default:
				system("CLS");
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "INVALID CHOICE. Please enter a number 1 - 6!" << std::endl; break;
				system("CLS");
			}
		}
		catch (char *msg)
		{
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << msg << std::endl;
		}
		catch (...)
		{
			std::cout << "ERROR" << std::endl;
		}
	} while (user_choice != 0);
	system("CLS");
}

void HeadNode::displayKeyManager()
{
	int choiceYear;

	int getCounterWC, getCounterTP, getCounterTM;

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

		WorldCup* worldCupObject = worldCupData->get(choiceYear, getCounterWC);
		FinalMatch* finalMatchObject = finalMatchData->get(choiceYear, getCounterTM);
		TeamsParticipated* teamsParticipatedObject = teamsByYear->get(choiceYear, getCounterTP);

		displayData(worldCupObject, finalMatchObject, teamsParticipatedObject);
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

void HeadNode::displayTableManager()
{

	system("CLS");
	std::cout << "\n\n\n";

	printGeneralWorldCupDataHeader();
	worldCupData->display();
	for (int i = 0; i < 148; i++)std::cout << "-";
	std::cout << "\n\n\n";

	system("pause");
	system("CLS");

	printFinalMatchDataHeader();
	finalMatchData->display();
	for (int i = 0; i < 120; i++)std::cout << "-";
	std::cout << "\n\n\n";

	system("pause");
	system("CLS");

	teamsByYear->display();

	std::cout << "\n\n\n";

	system("pause");
	system("CLS");
}

void HeadNode::printIndentedTree()
{
	//To be completed
	system("CLS");
	system("pause");
	yearHeldTree->printTree();
	
	system("pause");
	system("CLS");

	goalsPgameTree->printTree();
	system("pause");
	system("CLS");

	aveAtteTree->printTree();
	system("pause");
	system("CLS");

	totAtteTree->printTree();
	system("pause");
	system("CLS");

	numGamesTree->printTree();
	system("pause");
	system("CLS");

	numTeamsTree->printTree();
	system("CLS");
	system("pause");
}

void HeadNode::undoDeleteManager()
{
	int yearHeldCounter = 0, gpgTCounter = 0, aveAttTCounter = 0, totAttTCounter = 0, numGamesTCounter = 0, numTeamsTreeCounter = 0,
		wCCounter = 0, fMCounter = 0, teamsByYearCounter = 0;
	int winnerTreeCounter = 0;
	//Get the addresses that are at the top of the stack
	WorldCup* tempWC = worldCupRecycleBin->peek();
	TeamsParticipated* tempTP = teamsParticipatedRecycleBin->peek();
	FinalMatch* tempFM = finalMatchRecycleBin->peek();

	//pop the stacks
	worldCupRecycleBin->pop();
	teamsParticipatedRecycleBin->pop();
	finalMatchRecycleBin->pop();

	//Re-insert the addresses in the trees
	winnerTree->insert(tempWC->getWinningTeam(), tempWC, winnerTreeCounter);
	yearHeldTree->insert(tempWC->getYearHeld(), tempWC, yearHeldCounter);
	goalsPgameTree->insert(tempWC->getGoalsPerGame(), tempWC, gpgTCounter);
	aveAtteTree->insert(tempWC->getAveAtt(), tempWC, aveAttTCounter);
	totAtteTree->insert(tempWC->getTotAtt(), tempWC, totAttTCounter);
	numGamesTree->insert(tempWC->getNumGames(), tempWC, numGamesTCounter);
	numTeamsTree->insert(tempTP->getNumTeams(), tempTP, numTeamsTreeCounter);

	//Re-insert the addresses in the hash tables
	worldCupData->put(tempWC->getYearHeld(), tempWC, wCCounter);
	finalMatchData->put(tempFM->getYear(), tempFM, fMCounter);
	teamsByYear->put(tempTP->getYearHeld(), tempTP, teamsByYearCounter);

	//NEED TO DECIDE WHETHER WE SHOULD USE THE COUNTERS HERE OR NOT
}

void HeadNode::saveToInputFileManager()
{
	//Saving to Files
	worldCupData->writeWorldCupGeneralDataToTxt();
	finalMatchData->writeFinalMatchDataToTxt();
	teamsByYear->writeTeamsParticipatedToTxt();
}

void HeadNode::clearRecycleStacksManager()
{
	//Clearing the Recycle Bins
	worldCupRecycleBin->clearStack();
	teamsParticipatedRecycleBin->clearStack();
	finalMatchRecycleBin->clearStack();
}

void HeadNode::efficencyManager()
{
	system("CLS");
	//Since we are using tree hash tables, but with the same key the data of one tree is sufficent
	std::cout << std::endl << std::endl << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Current World Cup Hash Table load factor:                 " << worldCupData->loadFactor() << "%" << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Current Final Match Hash Table load factor:               " << finalMatchData->loadFactor() << "%" << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Current Teams Participated Hash Table load factor:        " << teamsByYear->loadFactor() << "%" << std::endl;
	std::cout << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "World Cup HashTable number of collisions:                 #" << worldCupData->getNumCollisions() << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "World Cup HashTable longest chain:                        #" << worldCupData->getLongestCollisionPath() << std::endl;
	std::cout << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Teams Participated HashTable number of collisions:        #" << teamsByYear->getNumCollisions() << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Teams Participated HashTable longest chain:               #" << teamsByYear->getLongestCollisionPath() << std::endl;
	std::cout << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Final Match HashTable number of collisions:               #" << finalMatchData->getNumCollisions() << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Final Match HashTable longest chain:                      #" << finalMatchData->getLongestCollisionPath() << std::endl;
	std::cout << std::endl << std::endl << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Number of TreeNodes:              " << yearHeldTree->getCountNodes() << std::endl << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Year Held          Tree height:               " << yearHeldTree->getHeight() << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Goals Per Game     Tree height:               " << goalsPgameTree->getHeight() << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Average Attendance Tree height:               " << aveAtteTree->getHeight() << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Total Attendance   Tree height:               " << totAtteTree->getHeight() << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Number of Games    Tree height:               " << numGamesTree->getHeight() << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Number of Teams    Tree height:               " << numTeamsTree->getHeight() << std::endl;
	std::cout << std::endl << std::endl << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "";
}

void HeadNode::printGeneralWorldCupDataHeader()
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

void HeadNode::printFinalMatchDataHeader()
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

void HeadNode::displayData(WorldCup*worldCupObject)
{
	system("CLS");
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
	system("PAUSE");
}

void HeadNode::displayData(WorldCup*worldCupObject, FinalMatch*finalMatchObject)
{
	system("CLS");
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
}

void HeadNode::displayData(TeamsParticipated*teamsParticipatedObject)
{
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "TEAMS PARTICIPATED" << std::endl << std::endl;
	for (int i = 0; i < teamsParticipatedObject->getNumTeams(); i++)std::cout << std::setw(WIDTH_BTW_LINES) << "" << i + 1 << ". " << teamsParticipatedObject->getTeamsArr()[i] << std::endl;
}

void HeadNode::displayData(WorldCup*worldCupObject, FinalMatch*finalMatchObject, TeamsParticipated*teamsParticipatedObject)
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