#ifndef INITIALIZER_FUNCTIONS_H
#define INITIALIZER_FUNCTIONS_H

#include <fstream>
#include <sstream>
#include "WorldCup.h"
#include "FinalMatch.h"
#include "TeamsParticipated.h"
#include "BinarySearchTree.h"
#include "HashTable.h"

//Functions that initialize the data at he beggining of the program
void initializeWorldCupData(BinarySearchTree<int, WorldCup>&, BinarySearchTree<double, WorldCup>&, BinarySearchTree<int, WorldCup>&, BinarySearchTree<int, WorldCup>&, BinarySearchTree<int, WorldCup>&, HashTable<int, WorldCup>&, HashTable<int, TeamsParticipated>&, BinarySearchTree<int, TeamsParticipated>&);
void initializeFinalMatchData(HashTable<int, FinalMatch>&);

void readFileWorldcupData(std::string &, BinarySearchTree<int, WorldCup>&, BinarySearchTree<double, WorldCup>&, BinarySearchTree<int, WorldCup>&, BinarySearchTree<int, WorldCup>&, BinarySearchTree<int, WorldCup>&, HashTable<int, WorldCup>&);
void readFileFinalMatchData(std::string &line, HashTable<int, FinalMatch>&);
void readFileTeamsByYearData(std::string &, HashTable<int, TeamsParticipated>&, BinarySearchTree<int, TeamsParticipated>&);


#endif // !INITIALIZER_FUNCTIONS_h