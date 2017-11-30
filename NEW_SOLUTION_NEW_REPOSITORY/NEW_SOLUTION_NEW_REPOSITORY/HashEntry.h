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

#endif // !HASHENTRY_H

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