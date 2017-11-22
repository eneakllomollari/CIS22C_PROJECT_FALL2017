#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include "WorldCup.h"
#include "FinalMatch.h"
#include "Tree.h"


const int WIDTH_BTW_LINES = 50;

//Functions that write back to the txt files at the end of the program
void writeWorldCupGeneralDataToTxt(WorldCup[], const int);
void writeTeamsParticipatedToTxt(WorldCup[], const int);
void writeFinalMatchDataToTxt(FinalMatch[], const int);

//Functions that initialize the data at he beggining of the program
void initializeWorldCupData(WorldCup *);
void initializeFinalMatchData(FinalMatch *);

void readFileTeamsByYearData(std::string &);
void readFileWorldcupData(std::string &);



void yearChosen();
void add();
void display_year_data();
//void checkPreviousYears();
void hashtable_list();
void sort_data_by_choice();			//asks user how he or she wants our database to be sorted ex. by year, mvp, city, etc
void descending_sort();				//sort function
int count_efficiency();				//does a count for how many lines of code is processsed in our functions
void pretty_print();				//prints bst in a pretty way
void remove_year();					//removes enter node of the year selected

#endif // !FUNCTION_H

