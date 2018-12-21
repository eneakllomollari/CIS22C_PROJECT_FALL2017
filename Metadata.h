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
#endif // !HEAD_NODE
