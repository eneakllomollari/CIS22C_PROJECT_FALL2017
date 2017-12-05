#ifndef TREE_H
#define TREE_H

#include "TreeNode.h"
#include <vector>
#include "Stack.h"

template <class K, class T>
class Tree
{
private:
	TreeNode<K, T> *root;		//Root of the tree
	int itemCount;

protected:
	void insertNode(K, T);
	int countNodes(TreeNode<K, T> *)const;
	int getHeightHelper(TreeNode<K, T> *);
	int max(int, int);

	void displayInOrder(TreeNode<K, T> *)const;
	void displayPreOrder(TreeNode<K, T> *)const;
	void displayPostOrder(TreeNode<K, T> *)const;

	void calculateSum(TreeNode<K, T>*, K&)const;
	void destroySubTree(TreeNode<K, T>*);
	TreeNode<K, T>* deleteNode(TreeNode<K, T>*, K, int&);

	TreeNode<K, T>* getSmallestNode(TreeNode<K, T>*)const;
	TreeNode<K, T>* getBiggestNode(TreeNode<K, T>*)const;
	TreeNode<K, T>* getParentOf(TreeNode<K, T>*)const;
	void printIndentedTree(TreeNode<K, T>*, int indent = 0);

	void printRow(TreeNode<K, T>*, int, int);
	void getLine(TreeNode<K, T>*, int, std::vector<K>&);
	void searchByKeyHelper(TreeNode<K, T>*, K, Stack<T>*);
	void searchBySmallestKeyHelper(TreeNode<K, T>*, K, Stack<T>*);
public:
	Tree();
	virtual ~Tree();

	void clear();
	void insert(K, T, int&);
	bool remove(K, int&);

	bool isEmpty()const;
	
	T searchByKey(K);
	void searchByKey(K key, Stack<T>*);
	void searchBySmallestKey(K key, Stack<T>*);

	K getAverage() const;
	K getSmallest() const;
	K getLargest() const;

	int getCountNodes()const;
	int getHeight();
	T getpRootData() const;
	TreeNode<K, T>* getRootNode() const;
	void setRootData(K, T);

	void displayInOrder()const;
	void displayPreOrder()const;
	void displayPostOrder()const;

	void printTree();
};
#include "Tree.cpp"
#endif // !TREE_H