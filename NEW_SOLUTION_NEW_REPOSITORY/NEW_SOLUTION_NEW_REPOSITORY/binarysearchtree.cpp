#include "BinarySearchTree.h"

/*
	Pre: N/A

	Post: Upon creation of Tree object,
	the appropriate variables will be initialized
*/
template<class K, class T>
BinarySearchTree<K, T>::BinarySearchTree()
{
	root = nullptr;
	itemCount = 0;
}

/*
	Pre: N/A

	Post: Upon destruction of Tree object, the appropriate measures
	will be taken in order to ensure no memory leaks occur
*/
template<class K, class T>
BinarySearchTree<K, T>::~BinarySearchTree()
{
	//Deletes the BinarySearchTree by calling the clear function, 
	//which calls destroySubBinarySearchTree function with root
	//as a parameter
	clear();
	itemCount = 0;
}

/*
	Pre: N/A

	Post: Upon successful completion will destroy the subTree
	using helper function "destroySubTree"
*/
template<class K, class T>
void BinarySearchTree<K, T>::clear()
{
	destroySubBinarySearchTree(root);
}

/*
	Pre: 

	Post:
*/
template<class K, class T>
void BinarySearchTree<K, T>::calculateSum(BinaryNode<K, T>*nodePtr, K &sum) const
{
	if (nodePtr)
	{
		sum += nodePtr->getKey();
		calculateSum(nodePtr->getLeft(), sum);
		calculateSum(nodePtr->getRight(), sum);
	}
}

template<class K, class T>
void BinarySearchTree<K, T>::destroySubBinarySearchTree(BinaryNode<K, T>* nodePtr)
{
	if (nodePtr != nullptr)
	{
		destroySubBinarySearchTree(nodePtr->getLeft());
		destroySubBinarySearchTree(nodePtr->getRight());

		delete nodePtr;
		nodePtr = nullptr;
	}
}

template<class K, class T>
bool BinarySearchTree<K, T>::remove(K key, int & removeCounter)
{
	int deleteCounter = 0;
	removeCounter = 0;
	root = deleteNode(root, key, deleteCounter);		removeCounter += deleteCounter;
	itemCount--;						removeCounter++;
	return true;
}

template<class K, class T>
BinaryNode<K, T>* BinarySearchTree<K, T>::getParentOf(BinaryNode<K, T> *nodePtr)const
{
	BinaryNode<K, T> *tempPtr = root;
	BinaryNode<K, T> *parent = nullptr;

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
BinaryNode<K, T>* BinarySearchTree<K, T>::getSmallestNode(BinaryNode<K, T>* rootPtr)const
{
	BinaryNode<K, T> *tempPtr = rootPtr;
	//Traverse all the way to the left most node which is 
	//at the same time the smallest node
	while (tempPtr->getLeft() != nullptr)
		tempPtr = tempPtr->getLeft();
	return tempPtr;
}

template<class K, class T>
BinaryNode<K, T>* BinarySearchTree<K, T>::getBiggestNode(BinaryNode<K, T>* rootPtr)const
{
	BinaryNode<K, T> *tempPtr = rootPtr;
	while (tempPtr->getRight() != nullptr)
		tempPtr = tempPtr->getRight();

	//Will return the right most node which is also the biggest node 
	return tempPtr;
}

template<class K, class T>
void BinarySearchTree<K, T>::insert(K key, T data, int &insertCounter)
{
	insertCounter = 0;
	insertNode(key, data);				insertCounter++;
	itemCount++;						insertCounter++;
}

template<class K, class T>
void BinarySearchTree<K, T>::insertNode(K k, T d)
{
	BinaryNode<K, T>* t = new BinaryNode<K, T>;	//Allocate a new BinaryNode
	BinaryNode<K, T>* parent = nullptr;

	t->setpData(d);
	t->setKey(k);
	t->setLeft(nullptr);	//Because is will be a leaf node
	t->setRight(nullptr);

	// If it is a new BinarySearchTree
	if (root == nullptr) root = t;
	else
	{
		BinaryNode<K, T> * curr;
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
void BinarySearchTree<K, T>::searchByKeyHelper(BinaryNode<K,T>* nodePtr,K key, Stack<T>* myList)
{
	//Traverse the BinarySearchTree
	if (nodePtr)
	{
		searchByKeyHelper(nodePtr->getLeft(),key,myList);
		if (key == nodePtr->getKey()) myList->push(nodePtr->getpdata());
		searchByKeyHelper(nodePtr->getRight(), key, myList);
	}
}

template<class K, class T>
void BinarySearchTree<K, T>::searchBySmallestKeyHelper(BinaryNode<K, T>*nodePtr, K key, Stack<T>*myStack)
{
	if (nodePtr)
	{
		if (key < nodePtr->getKey()) myStack->push(nodePtr->getpdata());
		searchBySmallestKeyHelper(nodePtr->getLeft(), key, myStack);
		searchBySmallestKeyHelper(nodePtr->getRight(), key, myStack);
	}
}

template<class K, class T>
void BinarySearchTree<K, T>::searchByGreatestKeyHelper(BinaryNode<K, T>*nodePtr, K key, Stack<T>*myStack)
{
	if (nodePtr)
	{
		if (key > nodePtr->getKey()) myStack->push(nodePtr->getpdata());
		searchByGreatestKeyHelper(nodePtr->getLeft(), key, myStack);
		searchByGreatestKeyHelper(nodePtr->getRight(), key, myStack);
	}
}

template<class K, class T>
T BinarySearchTree<K, T>::searchByKey(K key)
{
	BinaryNode <K, T>* nodePtr = root;

	//Traverse the BinarySearchTree
	while (nodePtr != nullptr)
	{
		if (nodePtr->getKey() == key)
			return nodePtr->getpdata();
		else if (key < nodePtr->getKey())
			nodePtr = nodePtr->getLeft();	//Else if the data is less, move to the left of the BinarySearchTree
		else
			nodePtr = nodePtr->getRight(); //Else, Move to the right
	}
	throw "OBJECT COULD NOT BE FOUND IN OUR dataBASE";
}

template<class K, class T>
void BinarySearchTree<K, T>::searchByKey(K key, Stack<T>*myList)
{
	searchByKeyHelper(root, key, myList);
}

template<class K, class T>
void BinarySearchTree<K, T>::searchBySmallestKey(K key, Stack<T>*myStack)
{
	searchBySmallestKeyHelper(root, key, myStack);
}

template<class K, class T>
void BinarySearchTree<K, T>::searchByGreatestKey(K key, Stack<T>*myStack)
{
	searchByGreatestKeyHelper(root, key, myStack);
}

template<class K, class T>
void BinarySearchTree<K, T>::displayInOrder() const
{
	displayInOrder(root);
}

template<class K, class T>
void BinarySearchTree<K, T>::displayPreOrder() const
{
	displayPreOrder(root);
}

template<class K, class T>
void BinarySearchTree<K, T>::displayPostOrder() const
{
	displayPostOrder(root);
}

template<class K, class T>
int BinarySearchTree<K, T>::getCountNodes() const
{
	return itemCount;
}

template<class K, class T>
bool BinarySearchTree<K, T>::isEmpty() const
{
	return root == nullptr;
}

template<class K, class T>
K BinarySearchTree<K, T>::getAverage() const
{
	K sum = 0;
	calculateSum(root, sum);
	return sum / (K)itemCount;
}

template<class K, class T>
K BinarySearchTree<K, T>::getSmallest() const
{
	return getSmallestNode(root)->getKey();
}

template<class K, class T>
K BinarySearchTree<K, T>::getLargest() const
{
	return getBiggestNode(root)->getKey();
}

template<class K, class T>
int BinarySearchTree<K, T>::getHeight()
{
	return getHeightHelper(root);
}

template<class K, class T>
T BinarySearchTree<K, T>::getpRootdata() const
{
	return root->getpdata();
}

template<class K, class T>
BinaryNode<K, T>* BinarySearchTree<K, T>::getRootNode() const
{
	return root;
}

template<class K, class T>
void BinarySearchTree<K, T>::setRootdata(K key_input, T newdata)
{
	if (root != nullptr)
	{
		root->setpdata(newdata);
		root->setKey(key_input);
	}

	else insertNode(key_input, newdata);
}

template<class K, class T>
int BinarySearchTree<K, T>::countNodes(BinaryNode<K, T> *nodePtr) const
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
int BinarySearchTree<K, T>::getHeightHelper(BinaryNode<K, T>* nodePtr)
{
	if (nodePtr == nullptr)
		return 0;
	else
	{
		return 1 + max(getHeightHelper(nodePtr->getLeft()), getHeightHelper(nodePtr->getRight()));
	}
}

template<class K, class T>
void BinarySearchTree<K, T>::displayInOrder(BinaryNode<K, T> *nodePtr) const
{
	if (nodePtr)
	{
		displayInOrder(nodePtr->getLeft());
		std::cout << *nodePtr->getpdata() << "\n";
		displayInOrder(nodePtr->getRight());
	}
}

template<class K, class T>
void BinarySearchTree<K, T>::displayPreOrder(BinaryNode<K, T>* nodePtr) const
{
	if (nodePtr)
	{
		std::cout << *nodePtr->getpdata() << "\n";
		displayPreOrder(nodePtr->getLeft());
		displayPreOrder(nodePtr->getRight());
	}
}

template<class K, class T>
void BinarySearchTree<K, T>::displayPostOrder(BinaryNode<K, T>* nodePtr) const
{
	if (nodePtr)
	{
		displayPostOrder(nodePtr->getLeft());
		displayPostOrder(nodePtr->getRight());
		std::cout << *nodePtr->getpdata() << "\n";
	}
}

template<class K, class T>
BinaryNode<K, T>* BinarySearchTree<K, T>::deleteNode(BinaryNode<K, T>*root, K key_input, int &deleteCounter)
{
	if (root == nullptr)
	{
		return root;												deleteCounter++;
	}
	else if (key_input < root->getKey())
	{
		root->setLeft(deleteNode(root->getLeft(), key_input, deleteCounter));		deleteCounter++;
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
			root = root->getLeft();									deleteCounter++;
			deleteNode(root, key_input, deleteCounter);
		}
		else if (root->hasRightChild() && !root->hasLeftChild())
		{
			root = root->getRight();								deleteCounter++;
			deleteNode(root, key_input, deleteCounter);
		}
		else
		{
			K minKey_data = getSmallestNode(root->getRight())->getKey();				deleteCounter++;
			root->setKey(minKey_data);												deleteCounter++;
			root->setRight(deleteNode(root->getRight(), minKey_data, deleteCounter));deleteCounter++;
		}
	}
	return root;																	deleteCounter++;
}

template <class K, class T>
int BinarySearchTree<K, T>::max(int x, int y)
{
	return x > y ? x : y;
}

template <class K, class T>
void BinarySearchTree<K, T>::printRow(BinaryNode<K, T>* p, int height, int depth)
{
	int placeholder = 0;

	std::vector<K> vec;
	getLine(p, depth, vec);
	std::cout << std::setw((height - depth) * 2);
	bool toggle = true;
	if (vec.size() > 1)
	{
		for (int v : vec)
		{
			if (v != placeholder)
			{
				if (toggle)
					std::cout << "/" << "   ";
				else
					std::cout << "\\" << "   ";
			}
			toggle = !toggle;
		}
		std::cout << std::endl;
		std::cout << std::setw((height - depth) * 2);
	}
	for (K v : vec)
		if (v != placeholder)
			std::cout << v << "   ";
	std::cout << std::endl;
}

template<class K, class T>
void BinarySearchTree<K, T>::getLine(BinaryNode<K, T>*root, int depth, std::vector<K>&vals)
{
	int placeholder = 0;
	if (depth <= 0 && root != nullptr)
	{
		vals.push_back(root->getKey());
		return;
	}
	if (root->getLeft() != nullptr)
		getLine(root->getLeft(), depth - 1, vals);
	else if (depth - 1 <= 0)
		vals.push_back(placeholder);
	if (root->getRight() != nullptr)
		getLine(root->getRight(), depth - 1, vals);
	else if (depth - 1 <= 0)
		vals.push_back(placeholder);
}