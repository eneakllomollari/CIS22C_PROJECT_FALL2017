#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "TeamsParticipated.h"
#include "HashEntry.h"

template <class K, class T>
class HashTable
{
private:
	const int TABLE_SIZE = 31;

	HashEntry<K, T> **table;

	int itemCount;
protected:
	
	int hash(const K&)const;

public:
	HashTable();
	~HashTable();

	T get(const K&)const;
	bool put(const K&, const T&);
	bool remove(const K&);

	bool isEmpty()const;
	int size()const;
	void display()const;
	double loadFactor()const;

	void writeTeamsParticipatedToTxt();
	void writeWorldCupGeneralDataToTxt();
	void writeFinalMatchDataToTxt();
};

template<class K, class T>
HashTable<K, T>::HashTable()
{
	//Dynamically allocate an array of HashEntries
	table = new HashEntry<K, T>*[TABLE_SIZE];
	for (int i = 0; i < TABLE_SIZE; i++)
		table[i] = nullptr;
	itemCount = 0;
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
T HashTable<K, T>::get(const K& searchKey)const
{
	int i = hash(searchKey);
	HashEntry<K, T> *entry = table[i];

	while (entry != nullptr)
	{
		if (entry->getKey() == searchKey)
			return entry->getData();
		else
			entry = entry->getNext();
	}
	throw "YEAR NOT FOUND";
}

template < class K, class T>
bool HashTable<K, T>::put(const K& searchKey, const T& newItem)
{
	// Create entry to add to dictionary
	HashEntry<K, T>* entryToAddPtr = new HashEntry<K, T>(searchKey, newItem);

	// Compute the hashed index into the array
	int itemHashIndex = hash(searchKey);

	// Add the entry to the chain at itemHashIndex
	if (table[itemHashIndex] == nullptr)
		table[itemHashIndex] = entryToAddPtr;
	else
	{
		//Insert it at the beggining of the chain
		entryToAddPtr->setNext(table[itemHashIndex]);
		table[itemHashIndex] = entryToAddPtr;
	}
	itemCount++;
	return true;
}

template < class K, class T>
bool HashTable<K, T>::remove(const K& searchKey)
{
	bool itemFound = false;
	// Compute the hashed index into the array
	int itemHashIndex = hash(searchKey);
	
	if (table[itemHashIndex] != nullptr)
	{
		// Special case - first node has target
		if (searchKey == table[itemHashIndex]->getHashKey())
		{
			HashEntry<K, T>* entryToRemovePtr = table[itemHashIndex];
			table[itemHashIndex] = table[itemHashIndex]->getNext();
			delete entryToRemovePtr;
			itemCount--;
			entryToRemovePtr = nullptr; // For safety
			itemFound = true;
		}
		else // Search the rest of the chain
		{
			HashEntry<K, T>* prevPtr = table[itemHashIndex];
			HashedEntry<K, T>* curPtr = prevPtr->getNext();
			while ((curPtr != nullptr) && !itemFound)
			{
				// Found item in chain so remove that node
				if (searchKey == curPtr->getKey())
				{
					prevPtr->setNext(curPtr->getNext());
					delete curPtr;
					itemCount--;
					curPtr = nullptr; // For safety
					itemFound = true;
				}
				else // Look at next entry in chain
				{
					prevPtr = curPtr;
					curPtr = curPtr->getNext();
				} 
			} 
		} 
	}
	return itemFound;
}

template<class K, class T>
inline bool HashTable<K, T>::isEmpty() const
{
	return itemCount == 0;
}

template<class K, class T>
int HashTable<K, T>::size() const
{
	return itemCount;
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
			std::cout << entry->getData() << std::endl;
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
			TeamsParticipated myTeam = entry->getData();

			//Create a pointer of type "String" to cycle through array of Teams
			std::string *tempTeamsArray = myTeam.getTeamsArr();

			//The key is the year of the WorldCup
			file << std::left << entry->getKey() << " | ";

			//Now print the teams that participated in specific year
			for (int i = 0; i < myTeam.getNumTeams(); i++)
			{
				if (i == myTeam.getNumTeams() - 1)
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
	std::ofstream file("worldCupGeneralData.txt");
	if (!file) throw "worldCupGeneralData.txt COULD NOT BE OPENED IN writeWorldCupGeneralDataToTxt()";

	//Create a pointer of type HashEntry
	HashEntry<K, T>*entry;

	for (int i = 0; i < TABLE_SIZE; i++)
	{
		entry = table[i];

		while (entry != nullptr)
		{
			WorldCup tempWc_object = entry->getData();

			file << std::fixed << std::setprecision(2);
			file << std::left << tempWc_object.getYearHeld() << " | ";
			file << std::left << std::setw(9) << tempWc_object.getWinningTeam() << " | ";
			file << std::left << std::setw(18) << tempWc_object.getGoldenBootWinner() << " | ";
			file << std::left << tempWc_object.getNumGames()<< " | ";
			file << std::left << std::setw(4) << tempWc_object.getGoalsPerGame() << " | ";
			file << std::left << tempWc_object.getAveAtt() << " | ";
			file << std::left << std::setw(7) << tempWc_object.getTotAtt() << " | ";
			file << std::left << tempWc_object.getHostCountry() << std::endl;
			
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
			FinalMatch FinalMatch_temp = entry->getData();

			//Output to the file below
			file << std::left << FinalMatch_temp.getYear() << " | ";
			file << std::left << std::setw(24) << FinalMatch_temp.getTeam1() + ", " + FinalMatch_temp.getTeam2() + "." << " | ";
			file << std::left << std::setw(13) << FinalMatch_temp.getResult() << " | ";
			file << std::left << std::setw(28) << FinalMatch_temp.getStadium() + "." << " | ";
			file << std::left << std::setw(15) << FinalMatch_temp.getCity() + "." << " |" << std::endl;

			//Move to next Node in linked list
			entry = entry->getNext();
		}
	}
	//Close fileObject
	file.close();
}

#endif // !HASHTABLE_H