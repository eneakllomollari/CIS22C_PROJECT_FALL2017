#ifndef INITIALIZER_FUNCTIONS_H
#define INITIALIZER_FUNCTIONS_H

#include <fstream>
#include <sstream>
#include "WorldCup.h"
#include "FinalMatch.h"
#include "TeamsParticipated.h"
#include "Tree.h"
#include "HashTable.h"

//Functions that initialize the data at he beggining of the program
void initializeWorldCupData(Tree<int, WorldCup>&, Tree<double, WorldCup>&, Tree<int, WorldCup>&, Tree<int, WorldCup>&, Tree<int, WorldCup>&, HashTable<int, WorldCup>&, HashTable<int, TeamsParticipated>&, Tree<int, TeamsParticipated>&);
void initializeFinalMatchData(HashTable<int, FinalMatch>&);

void readFileWorldcupData(std::string &, Tree<int, WorldCup>&, Tree<double, WorldCup>&, Tree<int, WorldCup>&, Tree<int, WorldCup>&, Tree<int, WorldCup>&, HashTable<int, WorldCup>&);
void readFileFinalMatchData(std::string &line, HashTable<int, FinalMatch>&);
void readFileTeamsByYearData(std::string &, HashTable<int, TeamsParticipated>&, Tree<int, TeamsParticipated>&);


#endif // !INITIALIZER_FUNCTIONS_h