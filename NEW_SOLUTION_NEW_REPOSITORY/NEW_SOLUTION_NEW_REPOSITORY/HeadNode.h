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
	Tree<int, WorldCup*> *yearHeldTree;
	Tree<double, WorldCup*> *goalsPgameTree;
	Tree<int, WorldCup*> *aveAtteTree;
	Tree<int, WorldCup*> *totAtteTree;
	Tree<int, WorldCup*> *numGamesTree;
	Tree<int, TeamsParticipated*> *numTeamsTree;

	//Declaring the hash tables
	HashTable<int, WorldCup*> *worldCupData;
	HashTable<int, FinalMatch*> *finalMatchData;
	HashTable<int, TeamsParticipated*> *teamsByYear;

	Stack<WorldCup*> *worldCupRecycleBin;
	Stack<FinalMatch*> *finalMatchRecycleBin;
	Stack<TeamsParticipated*> *teamsParticipatedRecycleBin;

protected:
	void printGeneralWorldCupDataHeader();
	void printFinalMatchDataHeader();

	void readFileWorldcupData(std::string&);
	void readFileFinalMatchData(std::string&);
	void readFileTeamsByYearData(std::string&);
public:
	HeadNode();
	~HeadNode();

	void initializeWorldCupDataManager();
	void initializeFinalMatchDataManager();

	void addManager();
	void removeManager();
	void sortManager();
	void displayKeyManager();
	void displayTableManager();
	void printIndentedTree();
	void undoDeleteManager();
	void saveToInputFileManager();
	void efficencyManager();
};
#endif // !HEAD_NODE