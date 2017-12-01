#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "HashEntry.h"

template <class K, class T>
class HashTable
{
private:
	int TABLE_SIZE = 31;

	HashEntry<K, T> **table;

	int itemCount;
	int numCollisions;
protected:

	int hash(const K&)const;

public:
	HashTable();
	~HashTable();

	T get(K, int&)const;
	bool put(K, T, int&);
	bool remove(K, int&);

	bool isEmpty()const;
	int size()const;
	int getNumCollisions()const;
	void display()const;
	double loadFactor()const;

	void writeTeamsParticipatedToTxt();
	void writeWorldCupGeneralDataToTxt();
	void writeFinalMatchDataToTxt();
	
	void insertDataAddressToStack(Stack<T>*);
};

template<class K, class T>
HashTable<K, T>::HashTable()
{
	//Dynamically allocate an array of HashEntries
	table = new HashEntry<K, T>*[TABLE_SIZE];
	for (int i = 0; i < TABLE_SIZE; i++)
		table[i] = nullptr;
	itemCount = 0;
	numCollisions = 0;
}

template<class K, class T>
HashTable<K, T>::~HashTable()
{
	//Free the memory allocated by the table
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
	return (2 * k + 3) % TABLE_SIZE;
}

template<class K, class T>
T HashTable<K, T>::get(K searchKey, int& getCounter)const
{
	getCounter = 0;
	int i = hash(searchKey);                            getCounter++;
	HashEntry<K, T> *entry = table[i];                  getCounter++;
	getCounter++;
	while (entry != nullptr)
	{
		if (entry->getKey() == searchKey) {
			return entry->getpData();					getCounter += 2;
		}
		else {
			entry = entry->getNext();					getCounter++;
		}
	}
	throw "\nTHIS YEAR DOES NOT EXIST IN OUR RECORDS";
}

template < class K, class T>
bool HashTable<K, T>::put(K searchKey, T newItem, int &putCounter)
{
	putCounter = 0;
	// Create entry to add to dictionary
	HashEntry<K, T>* entryToAddPtr = new HashEntry<K, T>(searchKey, newItem); putCounter++;

	// Compute the hashed index into the array
	int itemHashIndex = hash(searchKey);                                      putCounter++;

	// Add the entry to the chain at itemHashIndex
	if (table[itemHashIndex] == nullptr) {
		table[itemHashIndex] = entryToAddPtr;								  putCounter += 2;
	}
	else
	{
		numCollisions++;
		//Insert it at the beggining of the chain
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
	// Compute the hashed index into the array
	int itemHashIndex = hash(searchKey);                                    removeCounter++;

	if (table[itemHashIndex] != nullptr)
	{
		removeCounter++;
		// Special case - first node has target
		if (searchKey == table[itemHashIndex]->getKey())
		{
			HashEntry<K, T>* entryToRemovePtr = table[itemHashIndex];       removeCounter++;
			table[itemHashIndex] = table[itemHashIndex]->getNext();         removeCounter++;

			//Deleting the allocated entry
			delete entryToRemovePtr;                                        removeCounter++;
			entryToRemovePtr = nullptr;  /*For safety */                    removeCounter++;

			itemCount--;
			itemFound = true;                                               removeCounter++;
		}
		else // Search the rest of the chain
		{
			HashEntry<K, T>* prevPtr = table[itemHashIndex];                removeCounter++;
			HashEntry<K, T>* curPtr = prevPtr->getNext();                   removeCounter++;
			while ((curPtr != nullptr) && !itemFound)
			{
				/* Found item in chain so remove that node */               removeCounter += 2;
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
	return (double(size()) / double(TABLE_SIZE))*100.00;
}

template<class K, class T>
void HashTable<K, T>::writeTeamsParticipatedToTxt()
{

	std::ofstream file("TeamsByYear.txt");
	if (!file) throw "TeamsByYear.txt COULD NOT BE OPENED IN writeTeamsParticipatedToTxt()";

	//Create a pointer of type HashEntry
	HashEntry<K, T>*entry;

	//Cycle through the HashTable
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		//Assign the first node of the LinkedList
		//at index of HashTable array to pointer
		//"entry"
		entry = table[i];

		//While the HashTable array at specific index 
		//contains data
		while (entry != nullptr)
		{
			//Create a temporary TeamsParticipated object
			//that stores the data of the first Node
			//in the LinkedList at index of HashTable array
			TeamsParticipated* myTeam = entry->getpData();

			//Create a pointer of type "String" to cycle through array of Teams
			std::string *tempTeamsArray = myTeam->getTeamsArr();

			//The key is the year of the WorldCup
			file << std::left << entry->getKey() << " | ";

			//Now print the teams that participated in specific year
			for (int i = 0; i < myTeam->getNumTeams(); i++)
			{
				if (i == myTeam->getNumTeams() - 1)
					file << tempTeamsArray[i];
				else
					file << tempTeamsArray[i] << ", ";
			}
			file << std::endl;

			//Now move onto the next Node in the Linked List
			//at Index of HashTable
			entry = entry->getNext();
		}
	}
}

template<class K, class T>
void HashTable<K, T>::writeWorldCupGeneralDataToTxt()
{
	std::ofstream file("WorldCupGeneralData.txt");
	if (!file) throw "WorldCupGeneralData.txt COULD NOT BE OPENED IN writeWorldCupGeneralDataToTxt()";

	//Create a pointer of type HashEntry
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
void HashTable<K, T>::writeFinalMatchDataToTxt()
{
	//Open file for output
	std::ofstream file("FinalMatchData.txt");
	if (!file) throw "FinalMatchData.txt COULD NOT BE OPENED IN writeFinalMatchDataToTxt()";

	//Create a pointer of type HashEntry
	HashEntry<K, T>*entry;

	//Cycle through HashTable
	for (int index = 0; index < TABLE_SIZE; index++)
	{
		//Set data of first Node in LinkedList
		entry = table[index];

		//If linked list contains data
		while (entry != nullptr)
		{
			//Create temporary object that stores FinalMatch object
			FinalMatch* FinalMatch_temp = entry->getpData();

			//Output to the file below
			file << std::left << FinalMatch_temp->getYear() << " | ";
			file << std::left << std::setw(24) << FinalMatch_temp->getTeam1() + ", " + FinalMatch_temp->getTeam2() + "." << " | ";
			file << std::left << std::setw(13) << FinalMatch_temp->getResult() << " | ";
			file << std::left << std::setw(28) << FinalMatch_temp->getStadium() + "." << " | ";
			file << std::left << std::setw(15) << FinalMatch_temp->getCity() + "." << " |" << std::endl;

			//Move to next Node in linked list
			entry = entry->getNext();
		}
	}
	//Close fileObject
	file.close();
}

template<class K, class T>
void HashTable<K, T>::insertDataAddressToStack(Stack<T>*myStack)
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