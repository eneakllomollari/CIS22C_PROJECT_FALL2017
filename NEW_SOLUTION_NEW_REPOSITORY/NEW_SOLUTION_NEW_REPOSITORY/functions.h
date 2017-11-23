#ifndef FUNCTION_H
#define FUNCTION_H

#include "WorldCup.h"
#include "FinalMatch.h"
#include <fstream>

const int WIDTH_BTW_LINES = 50;

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



void writeGeneralDataToTxt(WorldCup *, const int);
void writeTeamsByYearToTxt(WorldCup *, const int);
void writeFinalMatchDataToTxt(FinalMatch *, const int);

#endif // !FUNCTION_H

