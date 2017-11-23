#ifndef HASHENTRY_H
#define HASHENTRY_H

template<class K, class T>
class HashEntry
{
private:
	K key;
	T data;
	HashEntry<K, T> *next;
public:
	HashEntry(K,T);

	void setHashKey(K);
	void setHashData(T);
	void setNext(HashEntry<K, T>*);

	K getHashKey() const;
	T getHashData() const;
	HashEntry<K, T>* getNext() const;
};

#endif // !HASHENTRY_H

template<class K, class T>
HashEntry<K, T>::HashEntry(K k, T d)
{
	key = k;
	data = d;
	next = nullptr;
}

template<class K, class T>
void HashEntry<K, T>::setHashKey(K k)
{
	key = k;
}

template<class K, class T>
void HashEntry<K, T>::setHashData(T d)
{
	data = d;
}

template<class K, class T>
void HashEntry<K, T>::setNext(HashEntry<K, T>* n)
{
	next = n;
}

template<class K, class T>
K HashEntry<K, T>::getHashKey() const
{
	return key;
}

template<class K, class T>
T HashEntry<K, T>::getHashData() const
{
	return data;
}

template<class K, class T>
HashEntry<K, T>* HashEntry<K, T>::getNext() const
{
	return next;
}
