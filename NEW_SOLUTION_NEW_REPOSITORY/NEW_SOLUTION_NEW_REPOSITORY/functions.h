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
void initializeWorldCupData(Tree<int, WorldCup>&, Tree<double, WorldCup>&, Tree<int, WorldCup>&, Tree<int, WorldCup>&, Tree<int, WorldCup>&, HashTable<int, WorldCup>&);
void initializeFinalMatchData(HashTable<int, FinalMatch>&);

void readFileWorldcupData(std::string &, Tree<int, WorldCup>&, Tree<double, WorldCup>&, Tree<int, WorldCup>&, Tree<int, WorldCup>&, Tree<int, WorldCup>&, HashTable<int, WorldCup>&);
void readFileFinalMatchData(std::string &line, HashTable<int, FinalMatch>&);
void readFileTeamsByYearData(std::string &, HashTable<int, TeamsParticipated>&);



void yearChosen();
void add();
void display_year_data(HashTable<int, WorldCup>);
//void checkPreviousYears();
void hashtable_list();
void sort_data_by_choice(Tree<int, WorldCup>, Tree<double, WorldCup>, Tree<int, WorldCup>, Tree<int, WorldCup>, Tree<int, WorldCup>);			//asks user how he or she wants our database to be sorted ex. by year, mvp, city, etc
void descending_sort();				//sort function
int count_efficiency();				//does a count for how many lines of code is processsed in our functions
void pretty_print();				//prints bst in a pretty way
void remove_year();					//removes enter node of the year selected



void writeGeneralDataToTxt(WorldCup *, const int);
void writeTeamsByYearToTxt(WorldCup *, const int);
void writeFinalMatchDataToTxt(FinalMatch *, const int);

#endif // !FUNCTION_H

