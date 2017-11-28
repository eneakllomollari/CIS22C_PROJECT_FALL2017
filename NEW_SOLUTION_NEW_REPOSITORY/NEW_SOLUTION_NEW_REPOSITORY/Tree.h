#ifndef TREE_H
#define TREE_H

#include "TreeNode.h"

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
	TreeNode<K, T>* deleteNode(TreeNode<K, T>*, K,int&);///////////////////////////////

	TreeNode<K, T>* getSmallestNode(TreeNode<K, T>*)const;
	TreeNode<K, T>* getBiggestNode(TreeNode<K, T>*)const;
	TreeNode<K, T>* getParentOf(TreeNode<K, T>*)const;

public:
	Tree();
	virtual ~Tree();

	void clear();
	void insert(K, T,int&);////////////////////////
	bool remove(K,int&);//////////////////////////
	TreeNode<K, T>* searchNode(K);
	bool isEmpty()const;

	K getAverage() const;
	K getSmallest() const;
	K getLargest() const;

	int getCountNodes()const;
	int getHeight();
	T getRootData() const;
	TreeNode<K, T>* getRootNode() const;

	void setRootData(K, T);

	void displayInOrder()const;
	void displayPreOrder()const;
	void displayPostOrder()const;
};

template<class K, class T>
Tree<K, T>::Tree()
{
	root = nullptr;
	itemCount = 0;
}

template<class K, class T>
Tree<K, T>::~Tree()
{
	//Deletes the tree by calling the clear function, 
	//which calls destroySubTree function with root
	//as a parameter
	clear();
	itemCount = 0;
}

template<class K, class T>
void Tree<K, T>::clear()
{
	destroySubTree(root);
}

template<class K, class T>
void Tree<K, T>::calculateSum(TreeNode<K, T>*nodePtr, K &sum) const
{
	if (nodePtr)
	{
		sum += nodePtr->getKey();
		calculateSum(nodePtr->getLeft(), sum);
		calculateSum(nodePtr->getRight(), sum);
	}
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
bool Tree<K, T>::remove(K key,int & removeCounter)
{
	int deleteCounter = 0;
	removeCounter = 0;
	root = deleteNode(root, key, deleteCounter);		removeCounter += deleteCounter;
	itemCount--;						removeCounter++;
	return true;
}

template<class K, class T>
TreeNode<K, T>* Tree<K, T>::getParentOf(TreeNode<K, T> *nodePtr)const
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
TreeNode<K, T>* Tree<K, T>::getSmallestNode(TreeNode<K, T>* rootPtr)const
{
	TreeNode<K, T> *tempPtr = rootPtr;
	//Traverse all the way to the left most node which is 
	//at the same time the smallest node
	while (tempPtr->getLeft() != nullptr)
		tempPtr = tempPtr->getLeft();
	return tempPtr;
}

template<class K, class T>
TreeNode<K, T>* Tree<K, T>::getBiggestNode(TreeNode<K, T>* rootPtr)const
{
	TreeNode<K, T> *tempPtr = rootPtr;
	while (tempPtr->getRight() != nullptr)
		tempPtr = tempPtr->getRight();

	//Will return the right most node which is also the biggest node 
	return tempPtr;
}

template<class K, class T>
void Tree<K, T>::insert(K key, T data,int &insertCounter)
{
	insertCounter=0;
	insertNode(key, data);				insertCounter++;
	itemCount++;						insertCounter++;
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
	return itemCount;
}

template<class K, class T>
bool Tree<K, T>::isEmpty() const
{
	return root == nullptr;
}

template<class K, class T>
K Tree<K, T>::getAverage() const
{
	K sum = 0;
	calculateSum(root, sum);
	return sum / (K)itemCount;
}

template<class K, class T>
K Tree<K, T>::getSmallest() const
{
	return getSmallestNode(root)->getKey();
}

template<class K, class T>
K Tree<K, T>::getLargest() const
{
	return getBiggestNode(root)->getKey();
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
TreeNode<K, T>* Tree<K, T>::deleteNode(TreeNode<K, T>*root, K key_input,int &deleteCounter)
{
	deleteCounter = 0;
	if (root == nullptr)
	{
		return root;												deleteCounter++;
	}
	else if (key_input < root->getKey())
	{
		root->setLeft(deleteNode(root->getLeft(), key_input,deleteCounter));		deleteCounter++;
	}
	else if (key_input > root->getKey())
	{
		root->setRight(deleteNode(root->getRight(), key_input, deleteCounter));	deleteCounter++;
	}
	else
	{
		if (root->isLeaf())
		{
			delete root;											deleteCounter++;
			root = nullptr;											deleteCounter++;
		}
		else if (root->hasLeftChild() && !root->hasRightChild())
		{
			TreeNode<K, T> *temp = root->getLeft();					deleteCounter++;
			
			//deleteNode(root, key_input);
			delete root;											deleteCounter++;
			root = nullptr;											//deleteCounter++;
			return temp;											//deleteCounter++;
		}
		else if (root->hasRightChild() && !root->hasLeftChild())
		{
			TreeNode<K, T>*temp = root->getRight();					deleteCounter++;
			//deleteNode(root, key_input);
			delete root;											deleteCounter++;
			root = nullptr;											//deleteCounter++;
			return temp;											//deleteCounter++;
		}
		else
		{
			TreeNode<K, T> *smallestValue = getSmallestNode(root->getRight());		deleteCounter++;
			K minKey_Data = smallestValue->getKey();								deleteCounter++;
			root->setKey(minKey_Data);												deleteCounter++;
			root->setRight(deleteNode(root->getRight(), minKey_Data, deleteCounter));				deleteCounter++;
		}
	}
	return root;																	deleteCounter++;
}

template <class K, class T>
int Tree<K, T>::max(int x, int y)
{
	return x > y ? x : y;
}

#endif // !TREE_H