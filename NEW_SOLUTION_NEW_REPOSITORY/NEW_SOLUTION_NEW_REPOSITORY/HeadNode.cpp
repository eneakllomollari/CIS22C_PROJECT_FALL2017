#include "HeadNode.h"

HeadNode::HeadNode()
{
	winnerBST = new BST <std::string, WorldCup*>;
	hostBST = new BST<std::string, WorldCup*>;
	yearHeldBST = new BST <int, WorldCup*>;
	goalsPgameBST = new BST<double, WorldCup*>;
	aveAtteBST = new BST <int, WorldCup*>;
	totAtteBST = new BST <int, WorldCup*>;
	numGamesBST = new BST <int, WorldCup*>;
	numTeamsBST = new BST <int, TeamsParticipated*>;
	finalMatchBST = new BST<int, FinalMatch*>;
	numTeamsbyYearBST = new BST<int, TeamsParticipated*>;
	numBSTs = 10;

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

	delete winnerBST;
	delete hostBST;
	delete yearHeldBST;
	delete goalsPgameBST;
	delete aveAtteBST;
	delete totAtteBST;
	delete numGamesBST;
	delete numTeamsBST;
	delete finalMatchBST;
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
		//Exit if the user chooses to 
		if (year == -1) return;

		std::cout << std::endl << std::endl;
		//VALIDATE YEAR DATA
		while ((std::cin.fail() || year < 1930) && year != -1)
		{
			if (std::cin.fail())
			{
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "ERROR: INVALID INPUT! Use numeric digits(0-9) only ..." << std::endl;
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Re-Enter Year:                                            ";
				std::cin.clear();
				std::cin.ignore();

			}
			else
			{
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "ERROR: INVALID INPUT! The first world cup was held in 1930 ..." << std::endl;
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Re-Enter Year:                                            ";
				std::cin.clear();


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
			std::cout << std::left << std::setw(WIDTH_BTW_LINES) << "" << "Re-Enter Number Of Teams:                                ";
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

		hostBST->insert(tempWorldCup->getHostCountry(), tempWorldCup, bstOpCounter);
		winnerBST->insert(tempWorldCup->getWinningTeam(), tempWorldCup, bstOpCounter);
		yearHeldBST->insert(tempWorldCup->getYearHeld(), tempWorldCup, bstOpCounter);
		goalsPgameBST->insert(tempWorldCup->getGoalsPerGame(), tempWorldCup, bstOpCounter);
		aveAtteBST->insert(tempWorldCup->getAveAtt(), tempWorldCup, bstOpCounter);
		totAtteBST->insert(tempWorldCup->getTotAtt(), tempWorldCup, bstOpCounter);
		numGamesBST->insert(tempWorldCup->getNumGames(), tempWorldCup, bstOpCounter);
		numTeamsBST->insert(tempTeamsParticipated->getNumTeams(), tempTeamsParticipated, bstOpCounter);
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
		std::cout << "ERROR" << std::endl;
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

		hostBST->remove(worldCupObject->getHostCountry(), bstOpCounter);
		winnerBST->remove(worldCupObject->getWinningTeam(), bstOpCounter);
		yearHeldBST->remove(worldCupObject->getYearHeld(), bstOpCounter);
		goalsPgameBST->remove(worldCupObject->getGoalsPerGame(), bstOpCounter);
		aveAtteBST->remove(worldCupObject->getAveAtt(), bstOpCounter);
		totAtteBST->remove(worldCupObject->getTotAtt(), bstOpCounter);
		numGamesBST->remove(worldCupObject->getNumGames(), bstOpCounter);
		numTeamsBST->remove(teamsParticipatedObject->getNumTeams(), bstOpCounter);
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
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << msg << std::endl;
	}
	catch (...)
	{
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "EXPECTION THROWN";
	}

	 std::cout << std::endl << std::endl;system("pause");
	system("CLS");
}

void HeadNode::searchManager()
{
	char choice;
	int yearChoice, minAveAtt, minTotAtt, maxAveAtt, maxTotAtt;
	double minValueOfGoals, maxValueOfGoals;
	std::string winnerChoice, hostChoice;

	WorldCup *worldCupObject;
	FinalMatch* finalMatchObject;
	TeamsParticipated* teamsParticipatedObject;

	do 
	{
		try
		{
			system("CLS");
			std::cout << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "\tSearch by:" << std::endl << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "1. Year" << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "2. Winner Country" << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "3. Host Country" << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "4. Goals per game minimum value" << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "5. Goals per game maximum value" << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "6. Average Attendance minimum value" << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "7. Average Attendance maximum value" << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "8. Total Attendance minimum value" << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "9. Total Attendance maximum value" << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "0. Return to Main Menu" << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Enter your choice here:    ";
			std::cin >> choice;
			std::cin.ignore(INT_MAX, '\n');

			if (choice == '1')
			{
				std::cout << std::endl << std::endl;
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Enter the year:        ";
				std::cin >> yearChoice;

				worldCupObject = yearHeldBST->searchByKey(yearChoice);
				finalMatchObject = finalMatchBST->searchByKey(worldCupObject->getYearHeld());
				teamsParticipatedObject = numTeamsbyYearBST->searchByKey(worldCupObject->getYearHeld());

				displayData(worldCupObject, finalMatchObject, teamsParticipatedObject);
				 std::cout << std::endl << std::endl;system("pause");
			}
			else if (choice == '2')
			{
				Stack<WorldCup*>* myWinnerList = new Stack<WorldCup*>;

				std::cout << std::endl << std::endl;
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Enter the winner:      ";
				getline(std::cin, winnerChoice, '\n');
				winnerBST->searchByKey(winnerChoice, myWinnerList);


				if (!myWinnerList->isEmpty())
				{
					system("CLS");
					std::cout << std::endl;
					std::cout << std::setw(WIDTH_BTW_LINES) << "" << winnerChoice << " has won " << myWinnerList->getSize() << " major competitions!" << std::endl << std::endl;
					printGeneralWorldCupDataHeader();
					myWinnerList->displayStack();
				}
				else
				{
					std::string s = winnerChoice + " has not won a major competition so far";
					throw s;
				}
				std::cout << std::endl << std::endl;
				 std::cout << std::endl << std::endl;system("pause");
				system("CLS");

				while (!myWinnerList->isEmpty())
				{
					worldCupObject = myWinnerList->peek();
					myWinnerList->pop();
					finalMatchObject = finalMatchBST->searchByKey(worldCupObject->getYearHeld());
					teamsParticipatedObject = numTeamsbyYearBST->searchByKey(worldCupObject->getYearHeld());

					displayData(worldCupObject, finalMatchObject, teamsParticipatedObject);
					std::cout << std::endl << std::endl; system("pause");
				}
				std::cout << std::endl << std::endl;

				system("CLS");
				delete myWinnerList;
			}
			else if (choice == '3')
			{
				Stack<WorldCup*>* myHostStack = new Stack<WorldCup*>;

				std::cout << std::endl << std::endl;
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Enter the host country:      ";
				getline(std::cin, hostChoice, '\n');
				hostBST->searchByKey(hostChoice, myHostStack);

				if (!myHostStack->isEmpty())
				{
					system("CLS");
					std::cout << std::endl;
					std::cout << std::setw(WIDTH_BTW_LINES) << "" << hostChoice << " has hosted " << myHostStack->getSize() << " major competitions!" << std::endl << std::endl;
					printGeneralWorldCupDataHeader();
					myHostStack->displayStack();
				}
				else
				{
					std::string s = hostChoice + " has not hosted a major competition so far";
					throw s;
				}
				std::cout << std::endl << std::endl;
				 std::cout << std::endl << std::endl;system("pause");
				system("CLS");

				while (!myHostStack->isEmpty())
				{
					worldCupObject = myHostStack->peek();
					myHostStack->pop();
					finalMatchObject = finalMatchBST->searchByKey(worldCupObject->getYearHeld());
					teamsParticipatedObject = numTeamsbyYearBST->searchByKey(worldCupObject->getYearHeld());
					displayData(worldCupObject, finalMatchObject, teamsParticipatedObject);

					std::cout << std::endl << std::endl; system("pause");
				}
				std::cout << std::endl << std::endl;

				system("CLS");
				delete myHostStack;
			}
			else if (choice == '4')
			{
				Stack<WorldCup*>* myGoalsPerGameStackMin = new Stack<WorldCup*>;

				std::cout << std::endl << std::endl;
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Enter the minimum number of goals: ";
				std::cin >> minValueOfGoals;
				goalsPgameBST->searchBySmallestKey(minValueOfGoals, myGoalsPerGameStackMin);

				if (!myGoalsPerGameStackMin->isEmpty())
				{
					system("CLS");
					std::cout << std::endl;
					std::cout << std::setw(WIDTH_BTW_LINES) << "" << "More than " << minValueOfGoals << " goals per game on average have been scored " << myGoalsPerGameStackMin->getSize() << " times in major competitions!" << std::endl << std::endl;
					printGeneralWorldCupDataHeader();
					myGoalsPerGameStackMin->displayStack();
				}
				else
					throw "Goals could not be found";

				std::cout << std::endl << std::endl;
				 std::cout << std::endl << std::endl;system("pause");
				system("CLS");

				while (!myGoalsPerGameStackMin->isEmpty())
				{
					worldCupObject = myGoalsPerGameStackMin->peek();
					myGoalsPerGameStackMin->pop();
					finalMatchObject = finalMatchBST->searchByKey(worldCupObject->getYearHeld());
					teamsParticipatedObject = numTeamsbyYearBST->searchByKey(worldCupObject->getYearHeld());

					displayData(worldCupObject, finalMatchObject, teamsParticipatedObject);
					std::cout << std::endl << std::endl; system("pause");
				}
				std::cout << std::endl << std::endl;

				system("CLS");
				delete myGoalsPerGameStackMin;
			}
			else if (choice == '5')
			{
				Stack<WorldCup*>* myGoalsPerGameStackMax = new Stack<WorldCup*>;

				std::cout << std::endl << std::endl;
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Enter the maximum goals per game: ";
				std::cin >> maxValueOfGoals;

				goalsPgameBST->searchByGreatestKey(maxValueOfGoals, myGoalsPerGameStackMax);

				if (!myGoalsPerGameStackMax->isEmpty())
				{
					system("CLS");
					std::cout << std::endl;
					std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Less than " << maxValueOfGoals << " goals per game on average have been scored in " << myGoalsPerGameStackMax->getSize() << " major competitions" << std::endl << std::endl;
					printGeneralWorldCupDataHeader();
					myGoalsPerGameStackMax->displayStack();
				}
				else
					throw "Goals could not be found";

				std::cout << std::endl << std::endl;
				std::cout << std::endl << std::endl; system("pause");
				system("CLS");

				while (!myGoalsPerGameStackMax->isEmpty())
				{
					worldCupObject = myGoalsPerGameStackMax->peek();
					myGoalsPerGameStackMax->pop();

					finalMatchObject = finalMatchBST->searchByKey(worldCupObject->getYearHeld());
					teamsParticipatedObject = numTeamsbyYearBST->searchByKey(worldCupObject->getYearHeld());

					displayData(worldCupObject, finalMatchObject, teamsParticipatedObject);

					std::cout << std::endl << std::endl; system("pause");
				}
				std::cout << std::endl << std::endl;

				system("CLS");

				delete myGoalsPerGameStackMax;
			}
			else if (choice == '6')
			{
				Stack<WorldCup*>* myAveAttStackMin = new Stack<WorldCup*>;

				std::cout << std::endl << std::endl;
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Enter the minimum average attendance: ";
				std::cin >> minAveAtt;

				aveAtteBST->searchBySmallestKey(minAveAtt, myAveAttStackMin);

				if (!myAveAttStackMin->isEmpty())
				{
					system("CLS");
					std::cout << std::endl;
					std::cout << std::setw(WIDTH_BTW_LINES) << "" << "More than " << myAveAttStackMin->getSize() << " matches have been attended by more than " << minAveAtt << " people! " << std::endl << std::endl;
					printGeneralWorldCupDataHeader();
					myAveAttStackMin->displayStack();
				}
				else
					throw "Attendance could not be found";

				std::cout << std::endl << std::endl;
				std::cout << std::endl << std::endl; system("pause");
				system("CLS");

				while (!myAveAttStackMin->isEmpty())
				{
					worldCupObject = myAveAttStackMin->peek();
					myAveAttStackMin->pop();
					finalMatchObject = finalMatchBST->searchByKey(worldCupObject->getYearHeld());
					teamsParticipatedObject = numTeamsbyYearBST->searchByKey(worldCupObject->getYearHeld());

					displayData(worldCupObject, finalMatchObject, teamsParticipatedObject);
					std::cout << std::endl << std::endl; system("pause");
				}
				std::cout << std::endl << std::endl;

				system("CLS");
				delete myAveAttStackMin;
			}
			else if (choice == '7')
			{
				Stack<WorldCup*>* myAveAttStackMax = new Stack<WorldCup*>;

				std::cout << std::endl << std::endl;
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Enter the maximum average attendance: ";
				std::cin >> maxAveAtt;

				aveAtteBST->searchByGreatestKey(maxAveAtt, myAveAttStackMax);

				if (!myAveAttStackMax->isEmpty())
				{
					system("CLS");
					std::cout << std::endl;
					std::cout << std::setw(WIDTH_BTW_LINES) << "" << myAveAttStackMax->getSize() << " major competitions have had less than " << maxAveAtt << " average attendance!" << std::endl << std::endl;
					printGeneralWorldCupDataHeader();
					myAveAttStackMax->displayStack();
				}
				else
					throw "Goals could not be found";

				std::cout << std::endl << std::endl;
				 std::cout << std::endl << std::endl;system("pause");
				system("CLS");

				while (!myAveAttStackMax->isEmpty())
				{
					worldCupObject = myAveAttStackMax->peek();
					myAveAttStackMax->pop();

					finalMatchObject = finalMatchBST->searchByKey(worldCupObject->getYearHeld());
					teamsParticipatedObject = numTeamsbyYearBST->searchByKey(worldCupObject->getYearHeld());
					displayData(worldCupObject, finalMatchObject, teamsParticipatedObject);

					std::cout << std::endl << std::endl; system("pause");
				}
				std::cout << std::endl << std::endl;

				system("CLS");
				delete myAveAttStackMax;
			}
			else if (choice == '8')
			{
				Stack<WorldCup*>* myTotAttStackMin = new Stack<WorldCup*>;

				std::cout << std::endl << std::endl;
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Enter the minimum total attendance: ";
				std::cin >> minTotAtt;

				totAtteBST->searchBySmallestKey(minTotAtt, myTotAttStackMin);

				if (!myTotAttStackMin->isEmpty())
				{
					system("CLS");
					std::cout << std::endl;
					std::cout << std::setw(WIDTH_BTW_LINES) << "" << myTotAttStackMin->getSize() << " matches have been attended by more than " << minTotAtt << " people! " << std::endl << std::endl;
					printGeneralWorldCupDataHeader();
					myTotAttStackMin->displayStack();
				}
				else
					throw "Attendance could not be found";

				std::cout << std::endl << std::endl;
				 std::cout << std::endl << std::endl;system("pause");
				system("CLS");

				while (!myTotAttStackMin->isEmpty())
				{
					worldCupObject = myTotAttStackMin->peek();
					myTotAttStackMin->pop();
					finalMatchObject = finalMatchBST->searchByKey(worldCupObject->getYearHeld());
					teamsParticipatedObject = numTeamsbyYearBST->searchByKey(worldCupObject->getYearHeld());

					displayData(worldCupObject, finalMatchObject, teamsParticipatedObject);
					std::cout << std::endl << std::endl; system("pause");
				}
				std::cout << std::endl << std::endl;

				system("CLS");
				delete myTotAttStackMin;
			}
			else if (choice == '9')
			{
				Stack<WorldCup*>* myTotAttStackMax = new Stack<WorldCup*>;

				std::cout << std::endl << std::endl;
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Enter the maximum total attendance: ";
				std::cin >> maxTotAtt;

				totAtteBST->searchByGreatestKey(maxTotAtt, myTotAttStackMax);

				if (!myTotAttStackMax->isEmpty())
				{
					system("CLS");
					std::cout << std::endl;
					std::cout << std::setw(WIDTH_BTW_LINES) << "" << myTotAttStackMax->getSize() << " major competitions have had less than " << maxTotAtt << " total attendance!" << std::endl << std::endl;
					printGeneralWorldCupDataHeader();
					myTotAttStackMax->displayStack();
				}
				else
					throw "Attendance could not be found";

				std::cout << std::endl << std::endl;
				 std::cout << std::endl << std::endl;system("pause");
				system("CLS");

				while (!myTotAttStackMax->isEmpty())
				{
					worldCupObject = myTotAttStackMax->peek();
					myTotAttStackMax->pop();

					finalMatchObject = finalMatchBST->searchByKey(worldCupObject->getYearHeld());
					teamsParticipatedObject = numTeamsbyYearBST->searchByKey(worldCupObject->getYearHeld());

					displayData(worldCupObject, finalMatchObject, teamsParticipatedObject);

					 std::cout << std::endl << std::endl;system("pause");
				}
				std::cout << std::endl << std::endl;

				system("CLS");
				delete myTotAttStackMax;

			}
			else if (choice == '0') break;
			else
			{
				if (std::cin.fail())std::cin.clear();
				throw "YOU ENTERED AN INVALID OPTION";
			}
			std::cout << std::endl;
		}
		catch (char *msg)
		{
			std::cout << std::endl << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << msg << std::endl;
			std::cout << std::endl << std::endl;
			std::cout << std::endl << std::endl;
			std::cout << std::endl << std::endl; system("pause");
			system("CLS");
		}
		catch (std::string s)
		{
			std::cout << std::endl << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << s << std::endl;
			std::cout << std::endl << std::endl;
			std::cout << std::endl << std::endl;
			 std::cout << std::endl << std::endl;system("pause");
			system("CLS");
		}
		catch (...)
		{
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "ERROR" << std::endl;
		}
	} while (choice != 0);
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
				yearHeldBST->displayInOrder();
				std::cout << "\n\n";
				 std::cout << std::endl << std::endl;system("pause");
				system("CLS");
				break;
			case 2:
				system("CLS");
				std::cout << "\n\n\n";
				printGeneralWorldCupDataHeader();
				goalsPgameBST->displayInOrder();
				std::cout << "\n\n";
				std::cout << "Average record is: " << goalsPgameBST->getAverage() << " goals per game." << std::endl;
				std::cout << "Highest record is: " << goalsPgameBST->getLargest() << " goals per game." << std::endl;
				std::cout << "Lowest  record is: " << goalsPgameBST->getSmallest() << " goals per game." << std::endl;
				std::cout << "\n\n";
				 std::cout << std::endl << std::endl;system("pause");
				system("CLS");
				break;
			case 3:
				system("CLS");
				std::cout << "\n\n\n";
				printGeneralWorldCupDataHeader();
				numGamesBST->displayInOrder();
				std::cout << "\n\n";
				std::cout << "Average number of games is: " << numGamesBST->getAverage() << " games" << std::endl;
				std::cout << "Highest number of games is: " << numGamesBST->getLargest() << " games." << std::endl;
				std::cout << "Lowest  number of games is: " << numGamesBST->getSmallest() << " games." << std::endl;
				std::cout << "\n\n";
				 std::cout << std::endl << std::endl;system("pause");
				system("CLS");
				break;
			case 4:
				system("CLS");
				std::cout << "\n\n\n";
				printGeneralWorldCupDataHeader();
				aveAtteBST->displayInOrder();
				std::cout << "\n\n";
				std::cout << "Average attendance is: " << aveAtteBST->getAverage() << " spectators" << std::endl;
				std::cout << "Highest attendance is: " << aveAtteBST->getLargest() << " spectators." << std::endl;
				std::cout << "Lowest  attendance is: " << aveAtteBST->getSmallest() << " spectators." << std::endl;
				std::cout << "\n\n";
				 std::cout << std::endl << std::endl;system("pause");
				system("CLS");
				break;
			case 5:
				system("CLS");
				std::cout << "\n\n\n";
				printGeneralWorldCupDataHeader();
				totAtteBST->displayInOrder();
				std::cout << "\n\n";
				std::cout << "Average number of overall attendance is: " << totAtteBST->getAverage() << " spectators" << std::endl;
				std::cout << "Highest number of overall attendance is: " << totAtteBST->getLargest() << " spectators." << std::endl;
				std::cout << "Lowest  number of overall attendance is: " << totAtteBST->getSmallest() << " spectators." << std::endl;
				std::cout << "\n\n";
				 std::cout << std::endl << std::endl;system("pause");
				system("CLS");
				break;
			case 6:
				system("CLS");
				std::cout << "\n\n\n";
				numTeamsBST->displayInOrder();
				std::cout << "\n\n";
				std::cout << "Average number of teams participating is: " << numTeamsBST->getAverage() << " teams" << std::endl;
				std::cout << "Highest number of teams participating is: " << numTeamsBST->getLargest() << " teams." << std::endl;
				std::cout << "Lowest  number of teams participating is: " << numTeamsBST->getSmallest() << " teams." << std::endl;
				std::cout << "\n\n";
				 std::cout << std::endl << std::endl;system("pause");
				system("CLS");
				break;
			case 0:
				 std::cout << std::endl << std::endl;system("pause");
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
	//To be completed
	system("CLS");
	 std::cout << std::endl << std::endl;system("pause");
	yearHeldBST->printBST();
	
	 std::cout << std::endl << std::endl;system("pause");
	system("CLS");

	goalsPgameBST->printBST();
	 std::cout << std::endl << std::endl;system("pause");
	system("CLS");

	aveAtteBST->printBST();
	 std::cout << std::endl << std::endl;system("pause");
	system("CLS");

	totAtteBST->printBST();
	 std::cout << std::endl << std::endl;system("pause");
	system("CLS");

	numGamesBST->printBST();
	 std::cout << std::endl << std::endl;system("pause");
	system("CLS");

	numTeamsBST->printBST();
	system("CLS");
	 std::cout << std::endl << std::endl;system("pause");
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
		hostBST->insert(tempWC->getHostCountry(), tempWC, bstOperations);
		winnerBST->insert(tempWC->getWinningTeam(), tempWC, bstOperations);
		yearHeldBST->insert(tempWC->getYearHeld(), tempWC, bstOperations);
		goalsPgameBST->insert(tempWC->getGoalsPerGame(), tempWC, bstOperations);
		aveAtteBST->insert(tempWC->getAveAtt(), tempWC, bstOperations);
		totAtteBST->insert(tempWC->getTotAtt(), tempWC, bstOperations);
		numGamesBST->insert(tempWC->getNumGames(), tempWC, bstOperations);
		numTeamsBST->insert(tempTP->getNumTeams(), tempTP, bstOperations);
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

	totalBSTHeight = hostBST->getHeight() + winnerBST->getHeight() + numTeamsBST->getHeight() 
					+ numGamesBST->getHeight() + totAtteBST->getHeight() + aveAtteBST->getHeight()
					+ yearHeldBST->getHeight() + goalsPgameBST->getHeight() + finalMatchBST->getHeight();

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