#ifndef HASHTABLE_H
#define HASHTABLE_H

const int TABLE_SIZE = 31;

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

	bool get(K, T&);
	void put(K, T);
	void remove(K);
};

template<class K, class T>
int HashTable<K, T>::hash(K k)
{
	return (23 * k + 29) % TABLE_SIZE;
}

template<class K, class T>
HashTable<K, T>::HashTable()
{
	//Dynamically allocate a 2D table
	table = new HashEntry<K, T>*[TABLE_SIZE];
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
bool HashTable<K, T>::get(K key, T &value)
{
	//Hash the key and get the index
	int index = hash(key);
	HashEntry<K, T> *entry = table[index];

	while (entry != nullptr)
	{
		if (entry->getKey() == key)
		{
			value = entry->getData();
			return true;
		}
		entry = entry->getNext();
	}
	return false;
}

template<class K, class T>
void HashTable<K, T>::put(K key, T data)
{
	int index = hash(key);

	HashEntry<K, T>*prev = nullptr;
	HashEntry<K, T>*entry = table[index];

	while (entry != nullptr && entry->getHashKey() != key)
	{
		prev = entry;
		entry = entry->getNext();
	}

	if (entry == nullptr)
	{
		entry = new HashEntry<K, T>(key, data);
		if (prev == nullptr)
			//Insert as the first bucket
			table[index] = entry;
		else
			prev->setNext(entry);
	}
	else
		//Just update the value
		entry->setHashData(data);
}

template<class K, class T>
void HashTable<K, T>::remove(K key)
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

#endif // !HASHTABLE_H