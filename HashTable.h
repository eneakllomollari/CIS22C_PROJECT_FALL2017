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

/*
	Pre: N/A

	Post: Upon creation of a new HashTable object... The 2-Dimensional HashTable array
	will be initialized and the counters will be set
*/
template<class K, class T>
HashTable<K, T>::HashTable()
{
	//Dynamically allocate an array of HashEntries
	table = new HashEntry<K, T>*[TABLE_SIZE];
	for (int i = 0; i < TABLE_SIZE; i++)
		table[i] = nullptr;

	//Set Counters
	itemCount = 0;
	numCollisions = 0;
	longestCollisionPath = 0;
}

/*
	Pre: N/A

	Post: Upon destruction of HashTable object...The pointers in 2-Dimensional HashTable
	array will be deleted and the pointer to the table will be deleted
*/
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

/*
	Pre: Requires a Key(ONLY INTEGER) as argument

	Post: Will appropriately hash the INTEGER key and return it
*/
template<class K, class T>
int HashTable<K, T>::hash(const K& k)const
{
	return (5 * k + 7) % TABLE_SIZE;
}


/*
	Pre: Function recieves some integer value

	Post: Returns TRUE if integer value is PRIME, and returns FALSE if not prime
*/
template<class K, class T>
bool HashTable<K, T>::is_primeNumber(int num_input)
{
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

/*
	Pre: N/A

	Post: Upon successful completion of this function,
	our hashTable should be re-Hashed with the size set to
	next 2 available prime numbers
*/
template<class K, class T>
void HashTable<K, T>::re_hash()
{
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

/*
	Pre: This function requires an INTEGER searchKey as an argument, 
	alongside the reference to an integer counter... This way we can 
	keep track of number of operatrions for specific function

	Post: Upon successful completion this function will return the data
	associated to the passed "searchKey" and will throw an exception
	if not found
*/
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

/*
	Pre: Needs an INTEGER "searchKey," a generic object "newItem," and a 
	reference to a counter to keep track of how many operations are performed
	within this specific function

	Post: Upon successful completion this function will have inserted 
	the "newItem" object into hashTable, and if there is a collission at time of insertion
	it will CHAIN the new entry
*/
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

/*
	Pre: This function requires input of an INTEGER "searchKey" and a reference to 
	integer "removeCounter" that will count number of operations specific to this function

	Post: Upon successful completion this function will have removed the data associated to the
	given INTEGER "searchKey" from HashTable object and deallocated the memory associated with it 
	within the Hashtable. Will return TRUE if item was found and deleted, and FALSE otherwise
*/
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

/*
	Pre: N/A

	Post: Will return the itemCount inside the HashTable
*/
template<class K, class T>
bool HashTable<K, T>::isEmpty() const
{
	return itemCount == 0;
}

/*
	Pre: Some INTEGER "searchKey"

	Post: Function will return TRUE if the item was found based on "searchKey," 
	and FALSE otherwise
*/
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

/*
	Pre: N/A

	Post: Returns itemCount(a.k.a size) of the HashTable
*/
template<class K, class T>
int HashTable<K, T>::size() const
{
	return itemCount;
}

/*
	Pre: N/A

	Post: Returns the # of collisions within HashTable
*/
template<class K, class T>
int HashTable<K, T>::getNumCollisions() const
{
	return numCollisions;
}

/*
	Pre: N/A

	Post: Upon Successful completion, this function will display
	the contents contained within the HashTable
*/
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

/*
	Pre: N/A

	Post: This function will return the loadFactor of the HashTable
*/
template<class K, class T>
double HashTable<K, T>::loadFactor() const
{
	//Divide the # of items in HashTable by the SIZE of the HashTable
	//array and multiply by 100 to get percentage
	return (double(size()) / double(TABLE_SIZE))*100.00;
}

/*
	Pre: N/A

	Post: Simply returns the longest collision Path in array...
	DEPENDS on another function to do the actual calculation
*/
template<class K, class T>
int HashTable<K, T>::getLongestCollisionPath()
{
	calculateLongestCollisionPath();
	return longestCollisionPath;
}

/*
	Pre: N/A

	Post: Upon successful completion this function will have output
	the Teams that participated by year into file "TeamsByYear.txt"
*/
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

/*
	Pre: N/A

	Post: Upon successful completion this function will have output 
	the data of each worldCup stored in HashTable into "WorldCupGeneralData.txt"
	file
*/
template<class K, class T>
void HashTable<K, T>::writeWorldCupGeneraldataToTxt()
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

/*
	Pre: N/A

	Post: Upon successful completion this function will write the data of Final Matches
	stored in HashTable into file "FinalMatchData.txt"
*/
template<class K, class T>
void HashTable<K, T>::writeFinalMatchdataToTxt()
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

/*
	Pre: N/A

	Post: Upon successful completion, this function will have calculated the
	longest collision path in HashTable since we are using CHAINING to 
	resolve collision conflicts
*/
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

/*
	Pre: Pointer to recycle bin Stack

	Post: Upon successful completiton this function will 
	push some data item into RecycleBin stack after it is deleted from
	HashTable...This will allow us the functionality to undo delete changes
*/
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