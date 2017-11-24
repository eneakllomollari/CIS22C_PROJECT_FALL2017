#ifndef HASHTABLE_H
#define HASHTABLE_H

const int TABLE_SIZE = 29;

//******************************************************
//				NOTE
// KEY HAS TO BE AN INTEGER IN THIS IMPLEMENTATION
//******************************************************

#include "HashEntry.h"
template <class K, class T>
class HashTable
{
private:
	HashEntry<K,T> **table;

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
};

template<class K, class T>
int HashTable<K, T>::hash(K k)
{
	return (199 * k + 197) % TABLE_SIZE;
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

#endif // !HASHTABLE_H