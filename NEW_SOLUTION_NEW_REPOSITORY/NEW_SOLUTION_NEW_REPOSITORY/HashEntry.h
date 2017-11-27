#ifndef HASHENTRY_H
#define HASHENTRY_H

template<class K, class T>
class HashEntry
{
private:
	K key;
	T data;

	HashEntry<K, T> *next;

protected:
	void setKey(const K&);

public:
	HashEntry();
	HashEntry(K,T);

	void setData(const T&);
	void setNext(HashEntry<K, T>*);

	K getKey() const;
	T getData() const;
	HashEntry<K, T>* getNext() const;

	//bool operator==(const HashEntry<K, T>&)const;
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
	data = d;
	next = nullptr;
}

template<class K, class T>
void HashEntry<K, T>::setKey(const K& k)
{
	key = k;
}

template<class K, class T>
void HashEntry<K, T>::setData(const T& d)
{
	data = d;
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
T HashEntry<K, T>::getData() const
{
	return data;
}

template<class K, class T>
HashEntry<K, T>* HashEntry<K, T>::getNext() const
{
	return next;
}