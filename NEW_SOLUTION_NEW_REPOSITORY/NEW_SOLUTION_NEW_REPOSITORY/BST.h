#ifndef BST_H
#define BST_H

#include "BSTNode.h"
#include <vector>
#include "Stack.h"

template <class K, class T>
class BST
{
private:
	BSTNode<K, T> *root;		//Root of the BST
	int itemCount;
protected:
	void sortByGoalsPerGame();
	void insertNode(K, T);
	int countNodes(BSTNode<K, T> *)const;
	int getHeightHelper(BSTNode<K, T> *);
	int max(int, int);

	void displayInOrder(BSTNode<K, T> *)const;
	void displayPreOrder(BSTNode<K, T> *)const;
	void displayPostOrder(BSTNode<K, T> *)const;

	void calculateSum(BSTNode<K, T>*, K&)const;
	void destroySubBST(BSTNode<K, T>*);
	BSTNode<K, T>* deleteNode(BSTNode<K, T>*, K, int&);

	BSTNode<K, T>* getSmallestNode(BSTNode<K, T>*)const;
	BSTNode<K, T>* getBiggestNode(BSTNode<K, T>*)const;
	BSTNode<K, T>* getParentOf(BSTNode<K, T>*)const;
	void printIndentedBST(BSTNode<K, T>*, int indent = 0);

	void printRow(BSTNode<K, T>*, int, int);
	void getLine(BSTNode<K, T>*, int, std::vector<K>&);
	void searchByKeyHelper(BSTNode<K, T>*, K, Stack<T>*);
	void searchBySmallestKeyHelper(BSTNode<K, T>*, K, Stack<T>*);
	void searchByGreatestKeyHelper(BSTNode<K, T>*, K, Stack<T>*);
public:
	BST();
	virtual ~BST();

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
	T getpRootData() const;
	BSTNode<K, T>* getRootNode() const;
	void setRootData(K, T);

	void displayInOrder()const;
	void displayPreOrder()const;
	void displayPostOrder()const;

	void printBST();
};
#include "BST.cpp"
#endif // !BST_H