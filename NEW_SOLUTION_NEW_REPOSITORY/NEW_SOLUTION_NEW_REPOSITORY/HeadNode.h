#ifndef HEAD_NODE
#define HEAD_NODE

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "WorldCup.h"
#include "Stack.h"
#include "FinalMatch.h"
#include "TeamsParticipated.h"
#include "HashTable.h"
#include "BST.h"

const int WIDTH_BTW_LINES = 50;

class HeadNode
{
private:
	//Declaring the BSTs
	BST<std::string, WorldCup*> *winnerBST;
	BST<std::string, WorldCup*> *hostBST;
	BST<int, WorldCup*> *yearHeldBST;
	BST<double, WorldCup*> *goalsPgameBST;
	BST<int, WorldCup*> *aveAtteBST;
	BST<int, WorldCup*> *totAtteBST;
	BST<int, WorldCup*> *numGamesBST;
	BST<int, TeamsParticipated*> *numTeamsBST;
	BST<int, TeamsParticipated*> *numTeamsbyYearBST;
	BST<int, FinalMatch*> *finalMatchBST;

	//Declaring the hash tables
	HashTable<int, WorldCup*> *worldCupData;
	HashTable<int, FinalMatch*> *finalMatchData;
	HashTable<int, TeamsParticipated*> *teamsByYear;

	//Declaring the recovery Stacks
	Stack<WorldCup*> *worldCupRecycleBin;
	Stack<FinalMatch*> *finalMatchRecycleBin;
	Stack<TeamsParticipated*> *teamsParticipatedRecycleBin;

	int numBSTs;
	int numHashTables;
protected:
	void printGeneralWorldCupDataHeader();
	void printFinalMatchDataHeader();

	void readFileWorldcupData(std::string&);
	void readFileFinalMatchData(std::string&);
	void readFileTeamsByYearData(std::string&);

	void displayData(WorldCup*, FinalMatch*, TeamsParticipated*);

public:
	HeadNode();
	~HeadNode();

	void initializeWorldCupDataManager();
	void initializeFinalMatchDataManager();

	void addManager();
	void removeManager();
	void searchManager();
	void sortManager();
	void displayKeyManager();
	void displayTableManager();
	void printIndentedBST();
	void undoDeleteManager();
	void saveToInputFileManager();
	void efficencyManager();
	void clearRecycleStacksManager();

	int getNumBSTs();
	int getNumHashTables();
};
#endif // !HEAD_NODE