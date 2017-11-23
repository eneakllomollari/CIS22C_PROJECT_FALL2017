#ifndef TREE_H
#define TREE_H

#include "TreeNode.h"

template <class K, class T>
class Tree
{
private:
	TreeNode<K, T> *root;		//Root of the tree

protected:
	void insertNode(K, T);
	int countNodes(TreeNode<K, T> *)const;
	int getHeightHelper(TreeNode<K, T> *);
	int max(int, int);

	void displayInOrder(TreeNode<K, T> *)const;
	void displayPreOrder(TreeNode<K, T> *)const;
	void displayPostOrder(TreeNode<K, T> *)const;

	void destroySubTree(TreeNode<K, T>*);
	TreeNode<K, T>* deleteNode(TreeNode<K, T>*, K);

	TreeNode<K, T>* getSmallestNode(TreeNode<K, T>*);
	TreeNode<K, T>* getBiggerNode(TreeNode<K, T>*);
	TreeNode<K, T>* getParentOf(TreeNode<K, T>*);

public:
	Tree();
	virtual ~Tree();

	void clear();
	void insert(K, T);
	bool remove(K);
	TreeNode<K, T>* searchNode(K);
	bool isEmpty()const;

	int getCountNodes()const;
	int getHeight();
	T getRootData() const;
	TreeNode<K, T>* getRootNode() const;

	void setRootData(K, T);

	void displayInOrder()const;
	void displayPreOrder()const;
	void displayPostOrder()const;
};

template <class K, class T>
int Tree<K, T>::max(int x, int y)
{
	return x > y ? x : y;
}

template<class K, class T>
Tree<K, T>::Tree()
{
	root = nullptr;
}

template<class K, class T>
Tree<K, T>::~Tree()
{
	//Deletes the tree by calling the clear function, 
	//which calls destroySubTree function with root
	//as a parameter
	clear();
}

template<class K, class T>
void Tree<K, T>::clear()
{
	destroySubTree(root);
}

template<class K, class T>
void Tree<K, T>::destroySubTree(TreeNode<K, T>* nodePtr)
{
	if (nodePtr != nullptr)
	{
		destroySubTree(nodePtr->getLeft());
		destroySubTree(nodePtr->getRight());
		delete nodePtr;
	}
}

template<class K, class T>
bool Tree<K, T>::remove(K key)
{
	deleteNode(root, key);
	return true;
}

template<class K, class T>
TreeNode<K, T>* Tree<K, T>::getParentOf(TreeNode<K, T> *nodePtr)
{
	TreeNode<K, T> *tempPtr = root;
	TreeNode<K, T> *parent = nullptr;

	K key = nodePtr->getKey();

	while (tempPtr != nullptr)
	{
		if (tempPtr->getKey() == key)	//If the node is found
		{
			return parent;
		}
		else if (key < tempPtr->getKey())
		{
			parent = tempPtr;
			tempPtr = tempPtr->getLeft();
		}
		else
		{
			parent = tempPtr;
			tempPtr = tempPtr->getRight();
		}
	}
	return nullptr;
}

template<class K, class T>
TreeNode<K, T>* Tree<K, T>::getSmallestNode(TreeNode<K, T>* rootPtr)
{
	TreeNode<K, T> *tempPtr = rootPtr;
	//Traverse all the way to the left most node which is 
	//at the same time the smallest node
	while (tempPtr->getLeft() != nullptr)
		tempPtr = tempPtr->getLeft();
	return tempPtr;
}

template<class K, class T>
TreeNode<K, T>* Tree<K, T>::getBiggerNode(TreeNode<K, T>* rootPtr)
{
	TreeNode<K, T> *tempPtr = rootPtr;
	while (tempPtr->getRight() != nullptr)
		tempPtr = tempPtr->getRight();

	//Will return the right most node which is also the biggest node 
	return tempPtr;
}

template<class K, class T>
void Tree<K, T>::insert(K key, T data)
{
	insertNode(key, data);
}

template<class K, class T>
void Tree<K, T>::insertNode(K k, T d)
{
	TreeNode<K, T>* t = new TreeNode<K, T>;	//Allocate a new TreeNode
	TreeNode<K, T>* parent = nullptr;

	t->setData(d);
	t->setKey(k);
	t->setLeft(nullptr);	//Because is will be a leaf node
	t->setRight(nullptr);

	// If it is a new tree
	if (root == nullptr) root = t;
	else
	{
		TreeNode<K, T> * curr;
		curr = root;

		// Find the Node's parent
		while (curr)
		{
			parent = curr;
			if (t->getKey() < curr->getKey()) curr = curr->getLeft();
			else curr = curr->getRight();
		}

		if (t->getKey() < parent->getKey())
			parent->setLeft(t);
		else
			parent->setRight(t);
	}
}

template<class K, class T>
TreeNode<K, T>* Tree<K, T>::searchNode(K key)
{
	TreeNode <K, T>* nodePtr = root;

	//Traverse the tree
	while (nodePtr != nullptr)
	{
		if (nodePtr->getKey() == key)
			return nodePtr;				//If the data is found, return true
		else if (key < nodePtr->getKey())
			nodePtr = nodePtr->getLeft();	//Else if the data is less, move to the left of the tree
		else
			nodePtr = nodePtr->getRight(); //Else, Move to the right
	}
	return nullptr;
}

template<class K, class T>
void Tree<K, T>::displayInOrder() const
{
	displayInOrder(root);
}

template<class K, class T>
void Tree<K, T>::displayPreOrder() const
{
	displayPreOrder(root);
}

template<class K, class T>
void Tree<K, T>::displayPostOrder() const
{
	displayPostOrder(root);
}

template<class K, class T>
int Tree<K, T>::getCountNodes() const
{
	return countNodes(root);
}

template<class K, class T>
bool Tree<K, T>::isEmpty() const
{
	return root == nullptr;
}

template<class K, class T>
int Tree<K, T>::getHeight()
{
	return getHeightHelper(root);
}

template<class K, class T>
T Tree<K, T>::getRootData() const
{
	return root->data;
}

template<class K, class T>
TreeNode<K, T>* Tree<K, T>::getRootNode() const
{
	return root;
}

template<class K, class T>
void Tree<K, T>::setRootData(K key_input, T newData)
{
	if (root != nullptr)
	{
		root->setData(newData);
		root->setKey(key_input);
	}

	else insertNode(key_input, newData);
}

template<class K, class T>
int Tree<K, T>::countNodes(TreeNode<K, T> *nodePtr) const
{
	if (nodePtr == nullptr)
		return 0;
	else
	{
		int count = 1;

		count += countNodes(nodePtr->getLeft());	//Count nodes to the left
		count += countNodes(nodePtr->getRight());	//Count nodes to the right

		return count;
	}
}

template<class K, class T>
int Tree<K, T>::getHeightHelper(TreeNode<K, T>* nodePtr)
{
	if (nodePtr == nullptr)
		return 0;
	else
	{
		return 1 + max(getHeightHelper(nodePtr->getLeft()), getHeightHelper(nodePtr->getRight()));
	}
}

template<class K, class T>
void Tree<K, T>::displayInOrder(TreeNode<K, T> *nodePtr) const
{
	if (nodePtr)
	{
		displayInOrder(nodePtr->getLeft());
		std::cout << nodePtr->getData() << "\n";
		displayInOrder(nodePtr->getRight());
	}
}

template<class K, class T>
void Tree<K, T>::displayPreOrder(TreeNode<K, T>* nodePtr) const
{
	if (nodePtr)
	{
		std::cout << nodePtr->getData() << "\n";
		displayPreOrder(nodePtr->getLeft());
		displayPreOrder(nodePtr->getRight());
	}
}

template<class K, class T>
void Tree<K, T>::displayPostOrder(TreeNode<K, T>* nodePtr) const
{
	if (nodePtr)
	{
		displayPostOrder(nodePtr->getLeft());
		displayPostOrder(nodePtr->getRight());
		std::cout << nodePtr->getData() << "\n";
	}
}

template<class K, class T>
TreeNode<K, T>* Tree<K, T>::deleteNode(TreeNode<K, T>*root, K key_input)
{
	if (root == nullptr)return root;
	else if (key_input < root->getKey())  root->setLeft(deleteNode(root->getLeft(), key_input));
	else if (key_input > root->getKey()) root->setRight(deleteNode(root->getRight(), key_input));
	else
	{
		if (root->isLeaf())
		{
			delete root;
			root = nullptr;
		}
		else if (root->hasLeftChild() && !root->hasRightChild())
		{
			root = root->getLeft();
			deleteNode(root, key_input);
		}
		else if (root->hasRightChild() && !root->hasLeftChild())
		{
			root = root->getRight();
			deleteNode(root, key_input);
		}
		else
		{
			TreeNode<K, T> *smallestValue = getSmallestNode(root->getRight());
			K minKey_Data = smallestValue->getKey();
			root->setKey(minKey_Data);
			root->setRight(deleteNode(root->getRight(), minKey_Data));
		}
	}
	return root;
}

#endif // !TREE_H