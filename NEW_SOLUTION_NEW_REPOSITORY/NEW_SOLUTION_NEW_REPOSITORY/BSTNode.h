#ifndef BSTNODE_H
#define BSTNODE_H

template<class K, class T>
class BSTNode
{
private:
	K key;
	T pData;

	BSTNode<K, T> *left;
	BSTNode<K, T> *right;

public:
	BSTNode();
	BSTNode(T);
	BSTNode(K, T);

	void setLeft(BSTNode<K, T> *);
	void setRight(BSTNode<K, T> *);
	void setpData(T);
	void setKey(K);

	bool isLeaf() const;
	bool hasLeftChild() const;
	bool hasRightChild() const;

	BSTNode<K, T>* getRight();
	BSTNode<K, T>* getLeft();
	T getpData();
	K getKey();
};
#include "BSTNode.cpp"
#endif // !BSTNODE_H