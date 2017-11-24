#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "WorldCup.h"
#include "FinalMatch.h"
#include "TeamsParticipated.h"
#include "Tree.h"
#include "HashTable.h"

const int WIDTH_BTW_LINES = 50;


//Functions that initialize the data at he beggining of the program
void initializeWorldCupData(Tree<int, WorldCup>&, Tree<double, WorldCup>&, Tree<int, WorldCup>&, Tree<int, WorldCup>&, Tree<int, WorldCup>&, HashTable<int, WorldCup>&, HashTable<int, TeamsParticipated>&);
void initializeFinalMatchData(HashTable<int, FinalMatch>&);

void readFileWorldcupData(std::string &, Tree<int, WorldCup>&, Tree<double, WorldCup>&, Tree<int, WorldCup>&, Tree<int, WorldCup>&, Tree<int, WorldCup>&, HashTable<int, WorldCup>&);
void readFileFinalMatchData(std::string &line, HashTable<int, FinalMatch>&);
void readFileTeamsByYearData(std::string &, HashTable<int, TeamsParticipated>&);


void yearChosen();
void add();
void display_year_data(HashTable<int, WorldCup>);
void hashtable_list();
void sortDataByChoice(Tree<int, WorldCup>, Tree<double, WorldCup>, Tree<int, WorldCup>, Tree<int, WorldCup>, Tree<int, WorldCup>);		
//void descending_sort();				
//int count_efficiency();				
void pretty_print();				
void remove_year();					


#endif // !FUNCTION_H

