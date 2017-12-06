#include "BSTNode.h"

template<class K, class T>
BSTNode<K, T>::BSTNode()
{
	left = right = nullptr;
}

template<class K, class T>
BSTNode<K, T>::BSTNode(T d)
{
	pData = d;
	left = nullptr;
	right = nullptr;
}

template<class K, class T>
BSTNode<K, T>::BSTNode(K k, T d)
{
	key = k;
	pData = d;
	left = nullptr;
	right = nullptr;
}

template<class K, class T>
void BSTNode<K, T>::setLeft(BSTNode<K, T> *l)
{
	left = l;
}

template<class K, class T>
void BSTNode<K, T>::setRight(BSTNode<K, T> *r)
{
	right = r;
}

template<class K, class T>
void BSTNode<K, T>::setpData(T d)
{
	pData = d;
}

template<class K, class T>
void BSTNode<K, T>::setKey(K k)
{
	key = k;
}

template<class K, class T>
bool BSTNode<K, T>::isLeaf() const
{
	return left == nullptr && right == nullptr;
}

template<class K, class T>
bool BSTNode<K, T>::hasLeftChild() const
{
	return left != nullptr;
}

template<class K, class T>
bool BSTNode<K, T>::hasRightChild() const
{
	return right != nullptr;
}

template<class K, class T>
BSTNode<K, T>* BSTNode<K, T>::getRight()
{
	return right;
}

template<class K, class T>
BSTNode<K, T>* BSTNode<K, T>::getLeft()
{
	return left;
}

template<class K, class T>
T BSTNode<K, T>::getpData()
{
	return pData;
}

template<class K, class T>
K BSTNode<K, T>::getKey()
{
	return key;
}

