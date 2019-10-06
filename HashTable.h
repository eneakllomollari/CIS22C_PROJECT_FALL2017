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

template<class K, class T>
HashTable<K, T>::HashTable()
{
	table = new HashEntry<K, T>*[TABLE_SIZE];
	for (int i = 0; i < TABLE_SIZE; i++)
		table[i] = nullptr;

	//Set Counters
	itemCount = 0;
	numCollisions = 0;
	longestCollisionPath = 0;
}

template<class K, class T>
HashTable<K, T>::~HashTable()
{
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		HashEntry<K, T> *entry = table[i];
		while (entry != nullptr)
		{
			HashEntry<K, T> *prev = entry;
			entry = entry->getNext();

			delete prev;
			prev = nullptr;
		}
		table[i] = nullptr;
	}
	itemCount = 0;
	delete[]table;
	table = nullptr;
}

template<class K, class T>
int HashTable<K, T>::hash(const K& k)const
{
	return (5 * k + 7) % TABLE_SIZE;
}


template<class K, class T>
bool HashTable<K, T>::is_primeNumber(int num_input)
{
	bool is_prime = true;

	for (int index = 2; index <= num_input / 2; index++)
	{
		if (num_input % index == 0)
		{
			is_prime = false;
			break;
		}

	} //end for loop

	return is_prime;
}

template<class K, class T>
void HashTable<K, T>::re_hash()
{
	int old_TABLE_SIZE;

	old_TABLE_SIZE = TABLE_SIZE;
	TABLE_SIZE = (TABLE_SIZE * 2) + 1;

	while (!is_primeNumber(TABLE_SIZE))
		TABLE_SIZE++;

	HashEntry<K, T>** new_HashTable = new HashEntry<K, T>*[TABLE_SIZE];

	for (int i = 0; i < TABLE_SIZE; i++)
		new_HashTable[i] = nullptr;
	int countOperations = 0;
	for (int index = 0; index < old_TABLE_SIZE; index++)
	{
		HashEntry<K, T>* traversePtr = table[index];
		while (traversePtr != nullptr)
		{
			HashEntry<K, T>* temp = traversePtr;
			traversePtr = traversePtr->getNext();

			HashEntry<K, T>*& entry1 = new_HashTable[hash(temp->getKey())];
			temp->setNext(entry1);
			entry1 = temp;
		}
	}
	delete[]table;
	table = new_HashTable;
}

template<class K, class T>
T HashTable<K, T>::get(K searchKey, int& getCounter)
{
	getCounter = 0;
	int i = hash(searchKey);                            getCounter++;
	HashEntry<K, T> *entry = table[i];                  getCounter++;
	getCounter++;
	while (entry != nullptr)
	{
		if (entry->getKey() == searchKey)
		{
            getCounter += 2;
			return entry->getpData();
		}
		else
		{
			entry = entry->getNext();					getCounter++;
		}
	}
	throw "THIS YEAR DOES NOT EXIST IN OUR RECORDS";
}

template < class K, class T>
bool HashTable<K, T>::put(K searchKey, T newItem, int &putCounter)
{
	if (loadFactor() >= 90.00)
		re_hash();

	putCounter = 0;
	HashEntry<K, T>* entryToAddPtr = new HashEntry<K, T>(searchKey, newItem); putCounter++;

	int itemHashIndex = hash(searchKey);                                      putCounter++;

	if (table[itemHashIndex] == nullptr) {
		table[itemHashIndex] = entryToAddPtr;								  putCounter += 2;
	}
	else
	{
		numCollisions++;
		entryToAddPtr->setNext(table[itemHashIndex]);                         putCounter++;
		table[itemHashIndex] = entryToAddPtr;                                 putCounter++;
	}
	itemCount++;                                                              putCounter++;
	return true;
}

template < class K, class T>
bool HashTable<K, T>::remove(K searchKey, int &removeCounter)
{
	removeCounter = 0;
	bool itemFound = false;                                                 removeCounter++;
	int itemHashIndex = hash(searchKey);                                    removeCounter++;

	if (table[itemHashIndex] != nullptr)
	{
		removeCounter++;
		if (searchKey == table[itemHashIndex]->getKey())
		{
			HashEntry<K, T>* entryToRemovePtr = table[itemHashIndex];       removeCounter++;
			table[itemHashIndex] = table[itemHashIndex]->getNext();         removeCounter++;

			delete entryToRemovePtr;                                        removeCounter++;
			entryToRemovePtr = nullptr;  /*For safety */                    removeCounter++;

			itemCount--;
			itemFound = true;                                               removeCounter++;
		}
		else
		{
			HashEntry<K, T>* prevPtr = table[itemHashIndex];                removeCounter++;
			HashEntry<K, T>* curPtr = prevPtr->getNext();                   removeCounter++;
			while ((curPtr != nullptr) && !itemFound)
			{
				if (searchKey == curPtr->getKey())
				{
					prevPtr->setNext(curPtr->getNext());                    removeCounter++;
					delete curPtr;                                          removeCounter++;
					itemCount--;                                            removeCounter++;
					curPtr = nullptr; /*For safety*/                        removeCounter++;
					itemFound = true;                                       removeCounter++;
				}
				else // Look at next entry in chain
				{
					prevPtr = curPtr;                                       removeCounter++;
					curPtr = curPtr->getNext();                             removeCounter++;
				}
			}
		}
	}
	return itemFound;
}

template<class K, class T>
bool HashTable<K, T>::isEmpty() const
{
	return itemCount == 0;
}

template<class K, class T>
bool HashTable<K, T>::contains(K searchKey) const
{
	int i = hash(searchKey);
	HashEntry<K, T> *entry = table[i];
	while (entry != nullptr)
	{
		if (entry->getKey() == searchKey)
			return true;
		else
			entry = entry->getNext();
	}
	return false;
}

template<class K, class T>
int HashTable<K, T>::size() const
{
	return itemCount;
}

template<class K, class T>
int HashTable<K, T>::getNumCollisions() const
{
	return numCollisions;
}

template<class K, class T>
void HashTable<K, T>::display() const
{
	HashEntry<K, T>*entry;
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		entry = table[i];
		while (entry != nullptr)
		{
			std::cout << *entry->getpData() << std::endl;
			entry = entry->getNext();
		}
	}
}

template<class K, class T>
double HashTable<K, T>::loadFactor() const
{
	return (double(size()) / double(TABLE_SIZE)) * 100.00;
}

template<class K, class T>
int HashTable<K, T>::getLongestCollisionPath()
{
	calculateLongestCollisionPath();
	return longestCollisionPath;
}

template<class K, class T>
void HashTable<K, T>::writeTeamsParticipatedToTxt()
{

	std::ofstream file("TeamsByYear.txt");
	if (!file) throw "TeamsByYear.txt COULD NOT BE OPENED IN writeTeamsParticipatedToTxt()";

	HashEntry<K, T>*entry;

	for (int i = 0; i < TABLE_SIZE; i++)
	{
		entry = table[i];
		while (entry != nullptr)
		{
			TeamsParticipated* myTeam = entry->getpData();

			std::string *tempTeamsArray = myTeam->getTeamsArr();

			file << std::left << entry->getKey() << " | ";
			for (int i = 0; i < myTeam->getNumTeams(); i++)
			{
				if (i == myTeam->getNumTeams() - 1)
					file << tempTeamsArray[i];
				else
					file << tempTeamsArray[i] << ", ";
			}
			file << std::endl;
			entry = entry->getNext();
		}
	}
}

template<class K, class T>
void HashTable<K, T>::writeWorldCupGeneraldataToTxt()
{
	std::ofstream file("WorldCupGeneralData.txt");
	if (!file) throw "WorldCupGeneralData.txt COULD NOT BE OPENED IN writeWorldCupGeneralDataToTxt()";

	HashEntry<K, T>*entry;

	for (int i = 0; i < TABLE_SIZE; i++)
	{
		entry = table[i];

		while (entry != nullptr)
		{
			WorldCup* tempWc_object = entry->getpData();

			file << std::fixed << std::setprecision(2);
			file << std::left << tempWc_object->getYearHeld() << " | ";
			file << std::left << std::setw(9) << tempWc_object->getWinningTeam() << " | ";
			file << std::left << std::setw(18) << tempWc_object->getGoldenBootWinner() << " | ";
			file << std::left << tempWc_object->getNumGames() << " | ";
			file << std::left << std::setw(4) << tempWc_object->getGoalsPerGame() << " | ";
			file << std::left << tempWc_object->getAveAtt() << " | ";
			file << std::left << std::setw(7) << tempWc_object->getTotAtt() << " | ";
			file << std::left << tempWc_object->getHostCountry() << std::endl;

			entry = entry->getNext();
		}
	}
	file.close();
}

template<class K, class T>
void HashTable<K, T>::writeFinalMatchdataToTxt()
{
	std::ofstream file("FinalMatchData.txt");
	if (!file) throw "FinalMatchData.txt COULD NOT BE OPENED IN writeFinalMatchDataToTxt()";

	HashEntry<K, T>*entry;

	for (int index = 0; index < TABLE_SIZE; index++)
	{
		entry = table[index];

		while (entry != nullptr)
		{
			FinalMatch* FinalMatch_temp = entry->getpData();

			file << std::left << FinalMatch_temp->getYear() << " | ";
			file << std::left << std::setw(24) << FinalMatch_temp->getTeam1() + ", " + FinalMatch_temp->getTeam2() + "." << " | ";
			file << std::left << std::setw(13) << FinalMatch_temp->getResult() << " | ";
			file << std::left << std::setw(28) << FinalMatch_temp->getStadium() + "." << " | ";
			file << std::left << std::setw(15) << FinalMatch_temp->getCity() + "." << " |" << std::endl;

			entry = entry->getNext();
		}
	}
	file.close();
}

template<class K, class T>
void HashTable<K, T>::calculateLongestCollisionPath()
{
	int count = 0, preCount = 0;
	HashEntry<K, T>*entry;
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		count = 0;
		entry = table[i];
		while (entry != nullptr)
		{
			count++;
			entry = entry->getNext();
		}
		if (count > preCount) preCount = count;
	}
	longestCollisionPath = preCount;
}

template<class K, class T>
void HashTable<K, T>::insertdataAddressToStack(Stack<T>*myStack)
{
	HashEntry<K, T>*entry;
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		entry = table[i];
		while (entry != nullptr)
		{
			myStack->push(entry->getpData());
			entry = entry->getNext();
		}
	}
}

#endif // !HASHTABLE_H