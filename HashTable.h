#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "HashEntry.h"
#include "Stack.h"
#include "TeamsParticipated.h"
#include "WorldCup.h"
#include "FinalMatch.h"

template <class K, class T>

class HashTable
{
private:
	int TABLE_SIZE = 41;

	HashEntry<K, T> **table;

	int itemCount;
	int numCollisions;
	int longestCollisionPath;

protected:
	int hash(const K&)const;
	bool is_primeNumber(int num_input);
	void re_hash();

public:
	HashTable();
	~HashTable();

	T get(K, int&);

	bool put(K, T, int&);
	bool remove(K, int&);

	bool isEmpty()const;
	bool contains(K)const;
	int size()const;
	int getNumCollisions()const;
	double loadFactor()const;
	int getLongestCollisionPath();
	void display()const;

	void writeTeamsParticipatedToTxt();
	void writeWorldCupGeneraldataToTxt();
	void writeFinalMatchdataToTxt();
	void calculateLongestCollisionPath();
	
	void insertdataAddressToStack(Stack<T>*);
};
#endif // !HASHTABLE_H