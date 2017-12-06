#include "HeadNode.h"

HeadNode::HeadNode()
{
	yearHeldBST = new BST <int, WorldCup*>;
	finalMatchBST = new BST<int, FinalMatch*>;
	numTeamsbyYearBST = new BST<int, TeamsParticipated*>;
	numBSTs = 3;

	worldCupData = new HashTable<int, WorldCup*>;
	finalMatchData = new HashTable<int, FinalMatch*>;
	teamsByYear = new HashTable<int, TeamsParticipated*>;
	numHashTables = 3;

	worldCupRecycleBin = new Stack <WorldCup*>;
	finalMatchRecycleBin = new Stack <FinalMatch*>;
	teamsParticipatedRecycleBin = new Stack <TeamsParticipated*>;

	initializeWorldCupDataManager();
	initializeFinalMatchDataManager();
}

HeadNode::~HeadNode()
{
	worldCupData->insertDataAddressToStack(worldCupRecycleBin);
	finalMatchData->insertDataAddressToStack(finalMatchRecycleBin);
	teamsByYear->insertDataAddressToStack(teamsParticipatedRecycleBin);

	saveToInputFileManager();
	clearRecycleStacksManager();

	delete yearHeldBST;
	delete numTeamsbyYearBST;
	numBSTs = 0;

	delete worldCupData;
	delete finalMatchData;
	delete teamsByYear;
	numHashTables = 0;

	delete worldCupRecycleBin;
	delete finalMatchRecycleBin;
	delete teamsParticipatedRecycleBin;
}

void HeadNode::addManager()
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
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			
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

		if (worldCupData->contains(year) && finalMatchData->contains(year) && teamsByYear->contains(year))
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
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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

		yearHeldBST->insert(tempWorldCup->getYearHeld(), tempWorldCup, bstOpCounter);
		numTeamsbyYearBST->insert(tempTeamsParticipated->getYearHeld(), tempTeamsParticipated, bstOpCounter);
		finalMatchBST->insert(tempFinalMatch->getYear(), tempFinalMatch, bstOpCounter);

		worldCupData->put(tempWorldCup->getYearHeld(), tempWorldCup, hashTableOpCounter);
		finalMatchData->put(tempFinalMatch->getYear(), tempFinalMatch, hashTableOpCounter);
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


	std::cin.ignore(INT_MAX, '\n');
	std::cout << std::setw(WIDTH_BTW_LINES) << "";
	std::cout << std::endl << std::endl;
	system("pause");
	system("CLS");
}

void HeadNode::removeManager()
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
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "UNHANDLED EXCEPTION" << std::endl;
			}
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		}	   //Input Validation
		if (choiceYear == 0)
		{
			system("CLS");
			return;
		}

		WorldCup* worldCupObject = worldCupData->get(choiceYear, searchHashTableCounter);
		TeamsParticipated* teamsParticipatedObject = teamsByYear->get(choiceYear, searchHashTableCounter);
		FinalMatch* finalMatchObject = finalMatchData->get(choiceYear, searchHashTableCounter);

		worldCupData->remove(choiceYear, hashTableOpCounter);
		finalMatchData->remove(choiceYear, hashTableOpCounter);
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

void HeadNode::sortKeyManager()
{
	printGeneralWorldCupDataHeader();
	yearHeldBST->displayInOrder();
	std::cout << "\n\n";
	std::cout << std::endl << std::endl; system("pause");
	system("CLS");

}

void HeadNode::displayKeyManager()
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
			std::cin.ignore(INT_MAX, '\n');
		}	   //Input Validation

		if (choiceYear == 0)
		{
			system("CLS");
			return;
		}

		WorldCup* worldCupObject = worldCupData->get(choiceYear, opCounter);
		FinalMatch* finalMatchObject = finalMatchData->get(choiceYear, opCounter);
		TeamsParticipated* teamsParticipatedObject = teamsByYear->get(choiceYear, opCounter);

		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Average number of operations performed to search the HashTables:      #" << opCounter / 3 << std::endl;
		std::cout << "\n\n";

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
	std::cout << std::setw(WIDTH_BTW_LINES) << "";  std::cout << std::endl << std::endl;system("pause");
	system("CLS");
}

void HeadNode::displayTableManager()
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
		std::cin.ignore(INT_MAX, '\n');

		system("CLS");
		switch (userChoice)
		{
		case '1':
			printGeneralWorldCupDataHeader();
			worldCupData->display();
			for (int i = 0; i < 148; i++)std::cout << "-";
			std::cout << "\n\n\n";

			std::cout << std::endl << std::endl; system("pause");
			system("CLS");

			break;
		case '2':
			printFinalMatchDataHeader();
			finalMatchData->display();
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

void HeadNode::printIndentedBST()
{
	//To be completed by Zach
}

void HeadNode::undoDeleteManager()
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
		worldCupData->put(tempWC->getYearHeld(), tempWC, hashTableOperations);
		finalMatchData->put(tempFM->getYear(), tempFM, hashTableOperations);
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

void HeadNode::efficencyManager()
{
	int totalBSTHeight;
	system("CLS");
	//Since we are using BST hash tables, but with the same key the data of one BST is sufficent
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

	totalBSTHeight = yearHeldBST->getHeight() + numTeamsbyYearBST->getHeight() + finalMatchBST->getHeight();

	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Number of Nodes in the BST:           " << yearHeldBST->getCountNodes() << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Average height of BSTs:               "<< totalBSTHeight / numBSTs  << std::endl;
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

int HeadNode::getNumBSTs()
{
	return numBSTs;
}

int HeadNode::getNumHashTables()
{
	return numHashTables;
}