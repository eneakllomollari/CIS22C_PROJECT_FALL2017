#ifndef HASHENTRY_H
#define HASHENTRY_H

template<class K, class T>
class HashEntry
{
private:
	K key;
	T pData;

	HashEntry<K, T> *next;

protected:
	void setKey(K);

public:
	HashEntry();
	HashEntry(K, T);

	void setpData(T);
	void setNext(HashEntry<K, T>*);

	K getKey() const;
	T getpData() const;
	HashEntry<K, T>* getNext() const;

};
#include "HashEntry.cpp"
#endif // !HASHENTRY_H