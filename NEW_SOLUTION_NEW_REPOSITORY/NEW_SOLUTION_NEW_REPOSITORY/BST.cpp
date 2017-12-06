#include "BST.h"

template<class K, class T>
BST<K, T>::BST()
{
	root = nullptr;
	itemCount = 0;
}

template<class K, class T>
BST<K, T>::~BST()
{
	//Deletes the BST by calling the clear function, 
	//which calls destroySubBST function with root
	//as a parameter
	clear();
	itemCount = 0;
}

template<class K, class T>
void BST<K, T>::clear()
{
	destroySubBST(root);
}

template<class K, class T>
void BST<K, T>::calculateSum(BSTNode<K, T>*nodePtr, K &sum) const
{
	if (nodePtr)
	{
		sum += nodePtr->getKey();
		calculateSum(nodePtr->getLeft(), sum);
		calculateSum(nodePtr->getRight(), sum);
	}
}

template<class K, class T>
void BST<K, T>::destroySubBST(BSTNode<K, T>* nodePtr)
{
	if (nodePtr != nullptr)
	{
		destroySubBST(nodePtr->getLeft());
		destroySubBST(nodePtr->getRight());

		delete nodePtr;
		nodePtr = nullptr;
	}
}

template<class K, class T>
bool BST<K, T>::remove(K key, int & removeCounter)
{
	int deleteCounter = 0;
	removeCounter = 0;
	root = deleteNode(root, key, deleteCounter);		removeCounter += deleteCounter;
	itemCount--;						removeCounter++;
	return true;
}

template<class K, class T>
BSTNode<K, T>* BST<K, T>::getParentOf(BSTNode<K, T> *nodePtr)const
{
	BSTNode<K, T> *tempPtr = root;
	BSTNode<K, T> *parent = nullptr;

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
BSTNode<K, T>* BST<K, T>::getSmallestNode(BSTNode<K, T>* rootPtr)const
{
	BSTNode<K, T> *tempPtr = rootPtr;
	//Traverse all the way to the left most node which is 
	//at the same time the smallest node
	while (tempPtr->getLeft() != nullptr)
		tempPtr = tempPtr->getLeft();
	return tempPtr;
}

template<class K, class T>
BSTNode<K, T>* BST<K, T>::getBiggestNode(BSTNode<K, T>* rootPtr)const
{
	BSTNode<K, T> *tempPtr = rootPtr;
	while (tempPtr->getRight() != nullptr)
		tempPtr = tempPtr->getRight();

	//Will return the right most node which is also the biggest node 
	return tempPtr;
}

template<class K, class T>
void BST<K, T>::insert(K key, T data, int &insertCounter)
{
	insertCounter = 0;
	insertNode(key, data);				insertCounter++;
	itemCount++;						insertCounter++;
}

template<class K, class T>
void BST<K, T>::insertNode(K k, T d)
{
	BSTNode<K, T>* t = new BSTNode<K, T>;	//Allocate a new BSTNode
	BSTNode<K, T>* parent = nullptr;

	t->setpData(d);
	t->setKey(k);
	t->setLeft(nullptr);	//Because is will be a leaf node
	t->setRight(nullptr);

	// If it is a new BST
	if (root == nullptr) root = t;
	else
	{
		BSTNode<K, T> * curr;
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
void BST<K, T>::searchByKeyHelper(BSTNode<K,T>* nodePtr,K key, Stack<T>* myList)
{
	//Traverse the BST
	if (nodePtr)
	{
		searchByKeyHelper(nodePtr->getLeft(),key,myList);
		if (key == nodePtr->getKey()) myList->push(nodePtr->getpData());
		searchByKeyHelper(nodePtr->getRight(), key, myList);
	}
}

template<class K, class T>
void BST<K, T>::searchBySmallestKeyHelper(BSTNode<K, T>*nodePtr, K key, Stack<T>*myStack)
{
	if (nodePtr)
	{
		if (key < nodePtr->getKey()) myStack->push(nodePtr->getpData());
		searchBySmallestKeyHelper(nodePtr->getLeft(), key, myStack);
		searchBySmallestKeyHelper(nodePtr->getRight(), key, myStack);
	}
}

template<class K, class T>
void BST<K, T>::searchByGreatestKeyHelper(BSTNode<K, T>*nodePtr, K key, Stack<T>*myStack)
{
	if (nodePtr)
	{
		if (key > nodePtr->getKey()) myStack->push(nodePtr->getpData());
		searchByGreatestKeyHelper(nodePtr->getLeft(), key, myStack);
		searchByGreatestKeyHelper(nodePtr->getRight(), key, myStack);
	}
}

template<class K, class T>
T BST<K, T>::searchByKey(K key)
{
	BSTNode <K, T>* nodePtr = root;

	//Traverse the BST
	while (nodePtr != nullptr)
	{
		if (nodePtr->getKey() == key)
			return nodePtr->getpData();
		else if (key < nodePtr->getKey())
			nodePtr = nodePtr->getLeft();	//Else if the data is less, move to the left of the BST
		else
			nodePtr = nodePtr->getRight(); //Else, Move to the right
	}
	throw "OBJECT COULD NOT BE FOUND IN OUR DATABASE";
}

template<class K, class T>
void BST<K, T>::searchByKey(K key, Stack<T>*myList)
{
	searchByKeyHelper(root, key, myList);
}

template<class K, class T>
void BST<K, T>::searchBySmallestKey(K key, Stack<T>*myStack)
{
	searchBySmallestKeyHelper(root, key, myStack);
}

template<class K, class T>
void BST<K, T>::searchByGreatestKey(K key, Stack<T>*myStack)
{
	searchByGreatestKeyHelper(root, key, myStack);
}

template<class K, class T>
void BST<K, T>::displayInOrder() const
{
	displayInOrder(root);
}

template<class K, class T>
void BST<K, T>::displayPreOrder() const
{
	displayPreOrder(root);
}

template<class K, class T>
void BST<K, T>::displayPostOrder() const
{
	displayPostOrder(root);
}

template<class K, class T>
void BST<K, T>::printBST()
{
	printIndentedBST(root);
}

template<class K, class T>
int BST<K, T>::getCountNodes() const
{
	return itemCount;
}

template<class K, class T>
bool BST<K, T>::isEmpty() const
{
	return root == nullptr;
}

template<class K, class T>
K BST<K, T>::getAverage() const
{
	K sum = 0;
	calculateSum(root, sum);
	return sum / (K)itemCount;
}

template<class K, class T>
K BST<K, T>::getSmallest() const
{
	return getSmallestNode(root)->getKey();
}

template<class K, class T>
K BST<K, T>::getLargest() const
{
	return getBiggestNode(root)->getKey();
}

template<class K, class T>
int BST<K, T>::getHeight()
{
	return getHeightHelper(root);
}

template<class K, class T>
T BST<K, T>::getpRootData() const
{
	return root->getpData();
}

template<class K, class T>
BSTNode<K, T>* BST<K, T>::getRootNode() const
{
	return root;
}

template<class K, class T>
void BST<K, T>::setRootData(K key_input, T newData)
{
	if (root != nullptr)
	{
		root->setpData(newData);
		root->setKey(key_input);
	}

	else insertNode(key_input, newData);
}

template<class K, class T>
int BST<K, T>::countNodes(BSTNode<K, T> *nodePtr) const
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
int BST<K, T>::getHeightHelper(BSTNode<K, T>* nodePtr)
{
	if (nodePtr == nullptr)
		return 0;
	else
	{
		return 1 + max(getHeightHelper(nodePtr->getLeft()), getHeightHelper(nodePtr->getRight()));
	}
}

template<class K, class T>
void BST<K, T>::displayInOrder(BSTNode<K, T> *nodePtr) const
{
	if (nodePtr)
	{
		displayInOrder(nodePtr->getLeft());
		std::cout << *nodePtr->getpData() << "\n";
		displayInOrder(nodePtr->getRight());
	}
}

template<class K, class T>
void BST<K, T>::displayPreOrder(BSTNode<K, T>* nodePtr) const
{
	if (nodePtr)
	{
		std::cout << *nodePtr->getpData() << "\n";
		displayPreOrder(nodePtr->getLeft());
		displayPreOrder(nodePtr->getRight());
	}
}

template<class K, class T>
void BST<K, T>::displayPostOrder(BSTNode<K, T>* nodePtr) const
{
	if (nodePtr)
	{
		displayPostOrder(nodePtr->getLeft());
		displayPostOrder(nodePtr->getRight());
		std::cout << *nodePtr->getpData() << "\n";
	}
}

template<class K, class T>
BSTNode<K, T>* BST<K, T>::deleteNode(BSTNode<K, T>*root, K key_input, int &deleteCounter)
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
			K minKey_Data = getSmallestNode(root->getRight())->getKey();				deleteCounter++;
			root->setKey(minKey_Data);												deleteCounter++;
			root->setRight(deleteNode(root->getRight(), minKey_Data, deleteCounter));deleteCounter++;
		}
	}
	return root;																	deleteCounter++;
}

template <class K, class T>
int BST<K, T>::max(int x, int y)
{
	return x > y ? x : y;
}

template <class K, class T>
void BST<K, T>::printIndentedBST(BSTNode<K, T> *p, int indent = 0)
{
	int height = getHeight() * 4;


	for (int i = 0; i < height; i++)
		printRow(p, height, i);
}

template <class K, class T>
void BST<K, T>::printRow(BSTNode<K, T>* p, int height, int depth)
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
void BST<K, T>::getLine(BSTNode<K, T>*root, int depth, std::vector<K>&vals)
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