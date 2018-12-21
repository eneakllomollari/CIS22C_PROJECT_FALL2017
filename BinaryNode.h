#ifndef BINARYNODE_H
#define BINARYNODE_H

#include <iostream>
#include <iomanip>

template<class K, class T>
class BinaryNode
{
private:
	K key;
	T pdata;

	BinaryNode<K, T> *left;
	BinaryNode<K, T> *right;

public:
	BinaryNode();
	BinaryNode(T);
	BinaryNode(K, T);

	void setLeft(BinaryNode<K, T> *);
	void setRight(BinaryNode<K, T> *);
	void setpData(T);
	void setKey(K);

	bool isLeaf() const;
	bool hasLeftChild() const;
	bool hasRightChild() const;

	BinaryNode<K, T>* getRight();
	BinaryNode<K, T>* getLeft();
	T getpdata();
	K getKey();
};

template<class K, class T>
BinaryNode<K, T>::BinaryNode()
{
	left = right = nullptr;
}

template<class K, class T>
BinaryNode<K, T>::BinaryNode(T d)
{
	pdata = d;
	left = nullptr;
	right = nullptr;
}

template<class K, class T>
BinaryNode<K, T>::BinaryNode(K k, T d)
{
	key = k;
	pdata = d;
	left = nullptr;
	right = nullptr;
}

template<class K, class T>
void BinaryNode<K, T>::setLeft(BinaryNode<K, T> *l)
{
	left = l;
}

template<class K, class T>
void BinaryNode<K, T>::setRight(BinaryNode<K, T> *r)
{
	right = r;
}

template<class K, class T>
void BinaryNode<K, T>::setpData(T d)
{
	pdata = d;
}

template<class K, class T>
void BinaryNode<K, T>::setKey(K k)
{
	key = k;
}

template<class K, class T>
bool BinaryNode<K, T>::isLeaf() const
{
	return left == nullptr && right == nullptr;
}

template<class K, class T>
bool BinaryNode<K, T>::hasLeftChild() const
{
	return left != nullptr;
}

template<class K, class T>
bool BinaryNode<K, T>::hasRightChild() const
{
	return right != nullptr;
}

template<class K, class T>
BinaryNode<K, T>* BinaryNode<K, T>::getRight()
{
	return right;
}

template<class K, class T>
BinaryNode<K, T>* BinaryNode<K, T>::getLeft()
{
	return left;
}

template<class K, class T>
T BinaryNode<K, T>::getpdata()
{
	return pdata;
}

template<class K, class T>
K BinaryNode<K, T>::getKey()
{
	return key;
}
#endif // !BinaryNode_H