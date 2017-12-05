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
#include "Tree.h"

const int WIDTH_BTW_LINES = 50;

class HeadNode
{
private:
	//Declaring the trees
	Tree<std::string, WorldCup*> *winnerTree;
	Tree<std::string, WorldCup*> *hostTree;
	Tree<int, WorldCup*> *yearHeldTree;
	Tree<double, WorldCup*> *goalsPgameTree;
	Tree<int, WorldCup*> *aveAtteTree;
	Tree<int, WorldCup*> *totAtteTree;
	Tree<int, WorldCup*> *numGamesTree;
	Tree<int, TeamsParticipated*> *numTeamsTree;
	Tree<int, FinalMatch*> *finalMatchTree;

	//Declaring the hash tables
	HashTable<int, WorldCup*> *worldCupData;
	HashTable<int, FinalMatch*> *finalMatchData;
	HashTable<int, TeamsParticipated*> *teamsByYear;

	//Declaring the recovery Stacks
	Stack<WorldCup*> *worldCupRecycleBin;
	Stack<FinalMatch*> *finalMatchRecycleBin;
	Stack<TeamsParticipated*> *teamsParticipatedRecycleBin;

protected:
	void printGeneralWorldCupDataHeader();
	void printFinalMatchDataHeader();

	void readFileWorldcupData(std::string&);
	void readFileFinalMatchData(std::string&);
	void readFileTeamsByYearData(std::string&);

	void displayData(WorldCup*, FinalMatch*, TeamsParticipated*);
	void displayData(WorldCup*);
	void displayData(WorldCup*, FinalMatch*);
	void displayData(TeamsParticipated*);
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
	void printIndentedTree();
	void undoDeleteManager();
	void saveToInputFileManager();
	void efficencyManager();
	void clearRecycleStacksManager();
};
#endif // !HEAD_NODE