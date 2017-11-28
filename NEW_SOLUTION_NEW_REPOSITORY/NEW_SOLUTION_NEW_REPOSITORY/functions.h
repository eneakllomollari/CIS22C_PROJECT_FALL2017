#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <iomanip>
#include "WorldCup.h"
#include "FinalMatch.h"
#include "TeamsParticipated.h"
#include "Tree.h"
#include "HashTable.h"
#include "Stack.h"

const int WIDTH_BTW_LINES = 50;



void add(Tree<int, WorldCup>&, Tree<double, WorldCup>&, Tree<int, WorldCup>&, Tree<int, WorldCup>&, Tree<int, WorldCup>&, HashTable<int, WorldCup>&, HashTable<int, FinalMatch>&, HashTable<int, TeamsParticipated>&);
void display_year_data(const HashTable<int, WorldCup>&, const HashTable<int, FinalMatch>&, const HashTable<int, TeamsParticipated>&);
void hashtable_list(const HashTable<int, WorldCup>&,const HashTable<int, FinalMatch>&,const HashTable<int, TeamsParticipated>&);
void sortDataByChoice(const Tree<int, WorldCup>&, const Tree<double, WorldCup>&, const Tree<int, WorldCup>&, const Tree<int, WorldCup>&, const Tree<int, WorldCup>&, const Tree<int, TeamsParticipated>&);
//void descending_sort();				
//int count_efficiency();				
void pretty_print();				
void remove_year(Tree<int, WorldCup>&, Tree<double, WorldCup>&, Tree<int, WorldCup>&, Tree<int, WorldCup>&, Tree<int, WorldCup>&, Tree<int, TeamsParticipated>&, HashTable<int, WorldCup>&, HashTable<int, FinalMatch>&, HashTable<int, TeamsParticipated>&, Stack<WorldCup>&, Stack<FinalMatch>&, Stack<TeamsParticipated>&);
void restoreDlte(Tree<int, WorldCup>&, Tree<double, WorldCup>&, Tree<int, WorldCup>&, Tree<int, WorldCup>&, Tree<int, WorldCup>&, Tree<int, TeamsParticipated>&, HashTable<int, WorldCup>&, HashTable<int, FinalMatch>&, HashTable<int, TeamsParticipated>&, Stack<WorldCup>&, Stack<FinalMatch>&, Stack<TeamsParticipated>&);



void printGeneralWorldCupDataHeader();
void printFinalMatchDataHeader();
#endif // !FUNCTION_H