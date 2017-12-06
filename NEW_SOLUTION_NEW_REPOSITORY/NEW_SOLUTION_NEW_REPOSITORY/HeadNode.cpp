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
	numBSTs = 9;

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
	saveToInputFileManager();

	delete winnerBST;
	delete hostBST;
	delete yearHeldBST;
	delete goalsPgameBST;
	delete aveAtteBST;
	delete totAtteBST;
	delete numGamesBST;
	delete numTeamsBST;
	delete finalMatchBST;
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
	int yearHeldInsertCounter = 0, gpgTInsertCounter = 0, aveAttTInsertCounter = 0, totalAttInsertCounter = 0, numTeamsBSTInsertCounter = 0, numGamesBSTInsertCounter = 0;
	int putCounterYearHeld = 0, putCounterGetYear = 0, putCounterTeamsParticYearHeld = 0, hostBSTInsertCounter = 0;
	int numTeamsBSTInsertCounter1 = 0, winnerBSTInsertCounter = 0;
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
			 std::cout << std::endl << std::endl;system("pause");;
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

		hostBST->insert(tempWorldCup->getHostCountry(), tempWorldCup, hostBSTInsertCounter);
		winnerBST->insert(tempWorldCup->getWinningTeam(), tempWorldCup, winnerBSTInsertCounter);
		yearHeldBST->insert(tempWorldCup->getYearHeld(), tempWorldCup, yearHeldInsertCounter);
		goalsPgameBST->insert(tempWorldCup->getGoalsPerGame(), tempWorldCup, gpgTInsertCounter);
		aveAtteBST->insert(tempWorldCup->getAveAtt(), tempWorldCup, aveAttTInsertCounter);
		totAtteBST->insert(tempWorldCup->getTotAtt(), tempWorldCup, totalAttInsertCounter);
		numGamesBST->insert(tempWorldCup->getNumGames(), tempWorldCup, numGamesBSTInsertCounter);
		numTeamsBST->insert(tempTeamsParticipated->getNumTeams(), tempTeamsParticipated, numTeamsBSTInsertCounter);

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

		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Inserted into year BST:                                #" << yearHeldInsertCounter << " operations." << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Inserted into goals per game BST:                      #" << gpgTInsertCounter << " operations." << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Inserted into average attendance BST:                  #" << aveAttTInsertCounter << " operations." << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Inserted into total attendance BST:                    #" << totalAttInsertCounter << " operations." << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Inserted into number of games BST:                     #" << numGamesBSTInsertCounter << " operations." << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Inserted into number of teams BST:                     #" << numTeamsBSTInsertCounter << " operations." << std::endl;
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
	 std::cout << std::endl << std::endl;system("pause");;
	system("CLS");
}

void HeadNode::removeManager()
{
	system("CLS");

	int yearHeldBSTRemoveCounter = 0, goalsPerGameBSTRemoveCounter = 0, aveAtteBSTRemoveCounter = 0,
		totAttBSTRemoveCounter = 0, numGamesBSTRemoveCounter = 0, numTeamsBSTRemoveCounter = 0, finalMatchCounter = 0;
	int winnerBSTRemoveCounter = 0, hostBSTRemoveCounter = 0;
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

		WorldCup* worldCupObject = worldCupData->get(choiceYear, getCounterWorldCup);
		TeamsParticipated* teamsParticipatedObject = teamsByYear->get(choiceYear, getCounterTeamsPaticipated);
		FinalMatch* finalMatchObject = finalMatchData->get(choiceYear, getCounterFinalMatch);

		worldCupData->remove(choiceYear, hashRemoveCounterWC);
		finalMatchData->remove(choiceYear, hashRemoveCounterFM);
		teamsByYear->remove(choiceYear, hashRemoveCounterTY);

		hostBST->remove(worldCupObject->getHostCountry(), hostBSTRemoveCounter);
		winnerBST->remove(worldCupObject->getWinningTeam(), winnerBSTRemoveCounter);
		yearHeldBST->remove(worldCupObject->getYearHeld(), yearHeldBSTRemoveCounter);
		goalsPgameBST->remove(worldCupObject->getGoalsPerGame(), goalsPerGameBSTRemoveCounter);
		aveAtteBST->remove(worldCupObject->getAveAtt(), aveAtteBSTRemoveCounter);
		totAtteBST->remove(worldCupObject->getTotAtt(), totAttBSTRemoveCounter);
		numGamesBST->remove(worldCupObject->getNumGames(), numGamesBSTRemoveCounter);
		numTeamsBST->remove(teamsParticipatedObject->getNumTeams(), numTeamsBSTRemoveCounter);
		finalMatchBST->remove(finalMatchObject->getYear(), finalMatchCounter);

		//Pushing the deleted files to the "recycle stacks"
		worldCupRecycleBin->push(worldCupObject);
		finalMatchRecycleBin->push(finalMatchObject);
		teamsParticipatedRecycleBin->push(teamsParticipatedObject);

		system("CLS");
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Removed from  World Cup      hash table:               #" << hashRemoveCounterWC << " operations." << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Removed from  Final Match    hash table:               #" << hashRemoveCounterFM << " operations." << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Removed from  Teams By Year  hash table:               #" << hashRemoveCounterTY << " operations." << std::endl;
		std::cout << std::endl;

		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Removed from year BST:                                #" << yearHeldBSTRemoveCounter << " operations." << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Removed from goals per game BST:                      #" << goalsPerGameBSTRemoveCounter << " operations." << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Removed from average attendance BST:                  #" << aveAtteBSTRemoveCounter << " operations." << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Removed from total attendance BST:                    #" << totAttBSTRemoveCounter << " operations." << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Removed from number of games BST:                     #" << numGamesBSTRemoveCounter << " operations." << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Removed from number of teams BST:                     #" << numTeamsBSTRemoveCounter << " operations." << std::endl;
		std::cout << "\n\n";
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

	 std::cout << std::endl << std::endl;system("pause");;
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

				displayData(worldCupObject, finalMatchObject);
				 std::cout << std::endl << std::endl;system("pause");;
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
					std::cout << std::setw(WIDTH_BTW_LINES) << "" << winnerChoice << " has won " << myWinnerList->getSize() << " major competitions!" << std::endl << std::endl;;
					printGeneralWorldCupDataHeader();
					myWinnerList->displayStack();
				}
				else
				{
					std::string s = winnerChoice + " has not won a major competition so far";
					throw s;
				}
				std::cout << std::endl << std::endl;
				 std::cout << std::endl << std::endl;system("pause");;
				system("CLS");

				while (!myWinnerList->isEmpty())
				{
					worldCupObject = myWinnerList->peek();
					myWinnerList->pop();
					finalMatchObject = finalMatchBST->searchByKey(worldCupObject->getYearHeld());
					displayData(worldCupObject, finalMatchObject);
					 std::cout << std::endl << std::endl;system("pause");;
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
					std::cout << std::setw(WIDTH_BTW_LINES) << "" << hostChoice << " has hosted " << myHostStack->getSize() << " major competitions!" << std::endl << std::endl;;
					printGeneralWorldCupDataHeader();
					myHostStack->displayStack();
				}
				else
				{
					std::string s = hostChoice + " has not hosted a major competition so far";
					throw s;
				}
				std::cout << std::endl << std::endl;
				 std::cout << std::endl << std::endl;system("pause");;
				system("CLS");

				while (!myHostStack->isEmpty())
				{
					worldCupObject = myHostStack->peek();
					myHostStack->pop();
					finalMatchObject = finalMatchBST->searchByKey(worldCupObject->getYearHeld());
					displayData(worldCupObject, finalMatchObject);
					 std::cout << std::endl << std::endl;system("pause");;
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
					std::cout << std::setw(WIDTH_BTW_LINES) << "" << "More than " << minValueOfGoals << " goals per game on average have been scored " << myGoalsPerGameStackMin->getSize() << " times in major competitions!" << std::endl << std::endl;;
					printGeneralWorldCupDataHeader();
					myGoalsPerGameStackMin->displayStack();
				}
				else
					throw "Goals could not be found";

				std::cout << std::endl << std::endl;
				 std::cout << std::endl << std::endl;system("pause");;
				system("CLS");

				while (!myGoalsPerGameStackMin->isEmpty())
				{
					worldCupObject = myGoalsPerGameStackMin->peek();
					myGoalsPerGameStackMin->pop();
					finalMatchObject = finalMatchBST->searchByKey(worldCupObject->getYearHeld());
					displayData(worldCupObject, finalMatchObject);
					 std::cout << std::endl << std::endl;system("pause");;
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
				 std::cout << std::endl << std::endl;system("pause");;
				system("CLS");

				while (!myGoalsPerGameStackMax->isEmpty())
				{
					worldCupObject = myGoalsPerGameStackMax->peek();
					myGoalsPerGameStackMax->pop();

					finalMatchObject = finalMatchBST->searchByKey(worldCupObject->getYearHeld());
					displayData(worldCupObject, finalMatchObject);

					 std::cout << std::endl << std::endl;system("pause");;
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
					std::cout << std::setw(WIDTH_BTW_LINES) << "" << "More than " << myAveAttStackMin->getSize() << " matches have been attended by more than " << minAveAtt << " people! " << std::endl << std::endl;;
					printGeneralWorldCupDataHeader();
					myAveAttStackMin->displayStack();
				}
				else
					throw "Attendance could not be found";

				std::cout << std::endl << std::endl;
				 std::cout << std::endl << std::endl;system("pause");;
				system("CLS");

				while (!myAveAttStackMin->isEmpty())
				{
					worldCupObject = myAveAttStackMin->peek();
					myAveAttStackMin->pop();
					finalMatchObject = finalMatchBST->searchByKey(worldCupObject->getYearHeld());
					displayData(worldCupObject, finalMatchObject);
					 std::cout << std::endl << std::endl;system("pause");;
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
				 std::cout << std::endl << std::endl;system("pause");;
				system("CLS");

				while (!myAveAttStackMax->isEmpty())
				{
					worldCupObject = myAveAttStackMax->peek();
					myAveAttStackMax->pop();

					finalMatchObject = finalMatchBST->searchByKey(worldCupObject->getYearHeld());
					displayData(worldCupObject, finalMatchObject);

					 std::cout << std::endl << std::endl;system("pause");;
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
					std::cout << std::setw(WIDTH_BTW_LINES) << "" << myTotAttStackMin->getSize() << " matches have been attended by more than " << minTotAtt << " people! " << std::endl << std::endl;;
					printGeneralWorldCupDataHeader();
					myTotAttStackMin->displayStack();
				}
				else
					throw "Attendance could not be found";

				std::cout << std::endl << std::endl;
				 std::cout << std::endl << std::endl;system("pause");;
				system("CLS");

				while (!myTotAttStackMin->isEmpty())
				{
					worldCupObject = myTotAttStackMin->peek();
					myTotAttStackMin->pop();
					finalMatchObject = finalMatchBST->searchByKey(worldCupObject->getYearHeld());
					displayData(worldCupObject, finalMatchObject);
					 std::cout << std::endl << std::endl;system("pause");;
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
				 std::cout << std::endl << std::endl;system("pause");;
				system("CLS");

				while (!myTotAttStackMax->isEmpty())
				{
					worldCupObject = myTotAttStackMax->peek();
					myTotAttStackMax->pop();

					finalMatchObject = finalMatchBST->searchByKey(worldCupObject->getYearHeld());
					displayData(worldCupObject, finalMatchObject);

					 std::cout << std::endl << std::endl;system("pause");;
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
			 std::cout << std::endl << std::endl;system("pause");;
			system("CLS");
		}
		catch (std::string s)
		{
			std::cout << std::endl << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << s << std::endl;
			std::cout << std::endl << std::endl;
			std::cout << std::endl << std::endl;
			 std::cout << std::endl << std::endl;system("pause");;
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
				 std::cout << std::endl << std::endl;system("pause");;
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
				 std::cout << std::endl << std::endl;system("pause");;
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
				 std::cout << std::endl << std::endl;system("pause");;
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
				 std::cout << std::endl << std::endl;system("pause");;
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
				 std::cout << std::endl << std::endl;system("pause");;
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
				 std::cout << std::endl << std::endl;system("pause");;
				system("CLS");
				break;
			case 0:
				 std::cout << std::endl << std::endl;system("pause");;
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
	std::cout << std::setw(WIDTH_BTW_LINES) << "";  std::cout << std::endl << std::endl;system("pause");;
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

	 std::cout << std::endl << std::endl;system("pause");;
	system("CLS");

	printFinalMatchDataHeader();
	finalMatchData->display();
	for (int i = 0; i < 120; i++)std::cout << "-";
	std::cout << "\n\n\n";

	 std::cout << std::endl << std::endl;system("pause");;
	system("CLS");

	teamsByYear->display();

	std::cout << "\n\n\n";

	 std::cout << std::endl << std::endl;system("pause");;
	system("CLS");
}

void HeadNode::printIndentedBST()
{
	//To be completed
	system("CLS");
	 std::cout << std::endl << std::endl;system("pause");;
	yearHeldBST->printBST();
	
	 std::cout << std::endl << std::endl;system("pause");;
	system("CLS");

	goalsPgameBST->printBST();
	 std::cout << std::endl << std::endl;system("pause");;
	system("CLS");

	aveAtteBST->printBST();
	 std::cout << std::endl << std::endl;system("pause");;
	system("CLS");

	totAtteBST->printBST();
	 std::cout << std::endl << std::endl;system("pause");;
	system("CLS");

	numGamesBST->printBST();
	 std::cout << std::endl << std::endl;system("pause");;
	system("CLS");

	numTeamsBST->printBST();
	system("CLS");
	 std::cout << std::endl << std::endl;system("pause");;
}

void HeadNode::undoDeleteManager()
{
	int yearHeldCounter = 0, gpgTCounter = 0, aveAttTCounter = 0, totAttTCounter = 0, numGamesTCounter = 0, numTeamsBSTCounter = 0,
		wCCounter = 0, fMCounter = 0, teamsByYearCounter = 0, hostBSTCounter = 0, finalMatchBSTCounter = 0;
	int winnerBSTCounter = 0;
	try {	//Get the addresses that are at the top of the stack
		WorldCup* tempWC = worldCupRecycleBin->peek();
		TeamsParticipated* tempTP = teamsParticipatedRecycleBin->peek();
		FinalMatch* tempFM = finalMatchRecycleBin->peek();

		//pop the stacks
		worldCupRecycleBin->pop();
		teamsParticipatedRecycleBin->pop();
		finalMatchRecycleBin->pop();

		//Re-insert the addresses in the BSTs
		hostBST->insert(tempWC->getHostCountry(), tempWC, hostBSTCounter);
		winnerBST->insert(tempWC->getWinningTeam(), tempWC, winnerBSTCounter);
		yearHeldBST->insert(tempWC->getYearHeld(), tempWC, yearHeldCounter);
		goalsPgameBST->insert(tempWC->getGoalsPerGame(), tempWC, gpgTCounter);
		aveAtteBST->insert(tempWC->getAveAtt(), tempWC, aveAttTCounter);
		totAtteBST->insert(tempWC->getTotAtt(), tempWC, totAttTCounter);
		numGamesBST->insert(tempWC->getNumGames(), tempWC, numGamesTCounter);
		numTeamsBST->insert(tempTP->getNumTeams(), tempTP, numTeamsBSTCounter);
		finalMatchBST->insert(tempFM->getYear(), tempFM, finalMatchBSTCounter);

		//Re-insert the addresses in the hash tables
		worldCupData->put(tempWC->getYearHeld(), tempWC, wCCounter);
		finalMatchData->put(tempFM->getYear(), tempFM, fMCounter);
		teamsByYear->put(tempTP->getYearHeld(), tempTP, teamsByYearCounter);

		std::cout << std::endl << std::endl;
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Recovery Successful!" << std::endl;
	}
	catch (char *msg)
	{
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << msg << std::endl;
		std::cout << std::endl << std::endl << std::endl;
		 std::cout << std::endl << std::endl;system("pause");;
		system("CLS");
	}
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

	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Number of Nodes in the BST:           " << yearHeldBST->getCountNodes() << std::endl << std::endl;
	std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Average BST height:                   "<< totalBSTHeight / numBSTs  << std::endl;
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
	 std::cout << std::endl << std::endl;system("pause");;
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

int HeadNode::getNumBSTs()
{
	return numBSTs;
}

int HeadNode::getNumHashTables()
{
	return numHashTables;
}