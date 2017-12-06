#include "HashTable.h"

template<class K, class T>
HashTable<K, T>::HashTable()
{
	//Dynamically allocate an array of HashEntries
	table = new HashEntry<K, T>*[TABLE_SIZE];
	for (int i = 0; i < TABLE_SIZE; i++)
		table[i] = nullptr;
	itemCount = 0;
	numCollisions = 0;
	longestCollisionPath = 0;
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
bool HashTable<K, T>::is_primeNumber(int num_input)
{
	/*
	Author: Kamaljot Saini

	Pre: Function recieves some integer value

	Post: Returns TRUE if integer value is PRIME, and returns FALSE if not prime
	*/

	//Declare local variables
	bool is_prime = true;

	//Run through numbers from 2
	//and once division by number returns false to being 
	//prime then break out of loop
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
	/*
	Author: Kamaljot Saini

	Pre: N/A

	Post: Upon successful completion of this function,
	our hashTable should be re-Hashed with the size set to
	next 2 available prime numbers
	*/

	//Declare local variables and objects
	int old_TABLE_SIZE;

	//Double the old hashTable size and add 1
	old_TABLE_SIZE = TABLE_SIZE;
	TABLE_SIZE = (TABLE_SIZE * 2) + 1;

	//Check and see that new_TABLE_SIZE is prime
	//if not, then convert it to the next available prime number
	while (!is_primeNumber(TABLE_SIZE))
		//Increment new_TABLE_SIZE one by one
		TABLE_SIZE++;

	//Dynamically allocate new_HashTable with new_TABLE_SIZE(which should be a prime #)
	HashEntry<K, T>** new_HashTable = new HashEntry<K, T>*[TABLE_SIZE];

	//Dynamically allocate an array of HashEntries
	//into the newHashTable
	for (int i = 0; i < TABLE_SIZE; i++)
		new_HashTable[i] = nullptr;
	int countOperations = 0;
	//Store all the pointers from old hashTable into new_HashTable;
	for (int index = 0; index < old_TABLE_SIZE; index++)
	{
		//While loop will ensure that all 
		//pointers, including chained pointers, are
		//pushed into the stack
		//Create temporary traversalPtr
		HashEntry<K, T>* traversePtr = table[index];
		while (traversePtr != nullptr)
		{
			HashEntry<K, T>* temp = traversePtr;
			traversePtr = traversePtr->getNext();

			//Find the proper collision pointer
			HashEntry<K, T>*& entry1 = new_HashTable[hash(temp->getKey())];
			temp->setNext(entry1);
			entry1 = temp;
		} //end while loop
	} //end for loop
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
			return entry->getpData();					getCounter += 2;
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
	//Check and see if re_hash is needed
	//We will re_hash at > 85% load factor
	if (loadFactor() >= 90.00)
		re_hash();

	putCounter = 0;
	// Create entry to add to hash table
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
	return (double(size()) / double(TABLE_SIZE))*100.00;
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

