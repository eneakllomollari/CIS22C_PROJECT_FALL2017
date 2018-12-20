#include "HashEntry.h"

template<class K, class T>
HashEntry<K, T>::HashEntry()
{
	next = nullptr;
}

template<class K, class T>
HashEntry<K, T>::HashEntry(K k, T d)
{
	key = k;
	pData = d;
	next = nullptr;
}

template<class K, class T>
void HashEntry<K, T>::setKey(K k)
{
	key = k;
}

template<class K, class T>
void HashEntry<K, T>::setpData(T d)
{
	pData = d;
}

template<class K, class T>
void HashEntry<K, T>::setNext(HashEntry<K, T>* n)
{
	next = n;
}

template<class K, class T>
K HashEntry<K, T>::getKey() const
{
	return key;
}

template<class K, class T>
T HashEntry<K, T>::getpData() const
{
	return pData;
}

template<class K, class T>
HashEntry<K, T>* HashEntry<K, T>::getNext() const
{
	return next;
}