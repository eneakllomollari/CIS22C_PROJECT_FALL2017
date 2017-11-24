#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "TeamsParticipated.h"
#include "HashEntry.h"

const int TABLE_SIZE = 29;

template <class K, class T>
class HashTable
{
private:
	HashEntry<K, T> **table;

	int hash(K);

public:
	HashTable();
	~HashTable();

	T get(const K&);
	void put(const K&, const T&);
	void remove(const K&);
	int size()const;
	void display()const;
	double getLoadFactor()const;

	void writeTeamsParticipatedToTxt();
	void writeWorldCupGeneralDataToTxt();
	void writeFinalMatchDataToTxt();
};

template<class K, class T>
int HashTable<K, T>::hash(K k)
{
	return (2 * k + 3) % TABLE_SIZE;
}

template<class K, class T>
HashTable<K, T>::HashTable()
{
	//Dynamically allocate an array of HashEntries
	table = new HashEntry<K, T>*[TABLE_SIZE];
	for (int i = 0; i < TABLE_SIZE; i++)
		table[i] = nullptr;
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
		}
		table[i] = nullptr;
	}
	delete[]table;
}

template<class K, class T>
T HashTable<K, T>::get(const K& key)
{
	T value;
	//Hash the key and get the index
	int index = hash(key);
	HashEntry<K, T> *entry = table[index];

	while (entry != nullptr)
	{
		if (entry->getHashKey() == key)
		{
			value = entry->getHashData();
			return value;
		}
		entry = entry->getNext();
	}
	throw "THERE IS NO OBJECT STORED AT THIS KEY";
}

template<class K, class T>
void HashTable<K, T>::put(const K& key, const T& data)
{
	int index = hash(key);
	
	if (table[index] == nullptr)
		table[index] = new HashEntry<K,T>(key, data);
	else
	{
		HashEntry<K, T>*entry = table[index];
		while (entry->getNext() != nullptr)
			entry = entry->getNext();
		if (entry->getHashKey() == key)
			entry->setHashData(data);
		else
			entry->setNext(new HashEntry<K, T>(key, data));
	}
}

template<class K, class T>
void HashTable<K, T>::remove(const K& key)
{
	int index = hash(key);

	HashEntry<K, T> *prev = nullptr;
	HashEntry<K, T> *entry = table[hashValue];

	while (entry != nullptr && entry.getKey() != key)
	{
		prev = entry;
		entry = entry->getNext();
	}
	
	if (entry = nullptr) //Entry not found
		return false;
	else
	{
		if (prev == nullptr)
			//remove the first bucket of the list
			table[index] = entry->getNext();
		else
			prev->setNext(entry->getNext());
		delete entry;
		return true;
	}
}

template<class K, class T>
int HashTable<K, T>::size() const
{
	HashEntry<K, T> *entryPtr;
	int sum = 0;
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		entryPtr = table[i];
		while (entryPtr != nullptr)
		{
			sum++;
			entryPtr = entryPtr->getNext();
		}
	}
	return sum;
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
			std::cout << entry->getHashData() << std::endl;
			entry = entry->getNext();
		}
	}
}

template<class K, class T>
double HashTable<K, T>::getLoadFactor() const
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
			TeamsParticipated myTeam = entry->getHashData();

			//Create a pointer of type "String" to cycle through array of Teams
			std::string *tempTeamsArray = myTeam.getTeamsArr();

			//The key is the year of the WorldCup
			file << std::left << entry->getHashKey() << " | ";

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
			WorldCup tempWc_object = entry->getHashData();

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
			FinalMatch FinalMatch_temp = entry->getHashData();

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