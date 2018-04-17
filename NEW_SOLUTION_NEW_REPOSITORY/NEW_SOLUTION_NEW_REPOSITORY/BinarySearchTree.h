#ifndef BinarySearchTree_H
#define BinarySearchTree_H

#include "BinaryNode.h"
#include <vector>
#include "Stack.h"

template <class K, class T>
class BinarySearchTree
{
private:
	BinaryNode<K, T> *root;		//Root of the BinarySearchTree
	int itemCount;
protected:
	void insertNode(K, T);
	int countNodes(BinaryNode<K, T> *)const;
	int getHeightHelper(BinaryNode<K, T> *);
	int max(int, int);

	void displayInOrder(BinaryNode<K, T> *)const;
	void displayPreOrder(BinaryNode<K, T> *)const;
	void displayPostOrder(BinaryNode<K, T> *)const;

	void calculateSum(BinaryNode<K, T>*, K&)const;
	void destroySubBinarySearchTree(BinaryNode<K, T>*);
	BinaryNode<K, T>* deleteNode(BinaryNode<K, T>*, K, int&);

	BinaryNode<K, T>* getSmallestNode(BinaryNode<K, T>*)const;
	BinaryNode<K, T>* getBiggestNode(BinaryNode<K, T>*)const;
	BinaryNode<K, T>* getParentOf(BinaryNode<K, T>*)const;

	void printRow(BinaryNode<K, T>*, int, int);
	void getLine(BinaryNode<K, T>*, int, std::vector<K>&);
	void searchByKeyHelper(BinaryNode<K, T>*, K, Stack<T>*);
	void searchBySmallestKeyHelper(BinaryNode<K, T>*, K, Stack<T>*);
	void searchByGreatestKeyHelper(BinaryNode<K, T>*, K, Stack<T>*);
public:
	BinarySearchTree();
	virtual ~BinarySearchTree();

	void clear();
	void insert(K, T, int&);
	bool remove(K, int&);

	bool isEmpty()const;
	
	T searchByKey(K);
	void searchByKey(K key, Stack<T>*);
	void searchBySmallestKey(K, Stack<T>*);
	void searchByGreatestKey(K, Stack<T>*);

	K getAverage() const;
	K getSmallest() const;
	K getLargest() const;

	int getCountNodes()const;
	int getHeight();
	T getpRootdata() const;
	BinaryNode<K, T>* getRootNode() const;
	void setRootdata(K, T);

	void displayInOrder()const;
	void displayPreOrder()const;
	void displayPostOrder()const;

};
#include "BinarySearchTree.cpp"
#endif // !BinarySearchTree_H