#ifndef TREE_H
#define TREE_H

#include "TreeNode.h"

template <class T>
class Tree
{
private:
	TreeNode<T> *root;		//Root of the tree

	int searchOp;

protected:
	void insertNode(T);
	int countNodes(TreeNode<T> *)const;
	int getHeightHelper(TreeNode<T> *);
	int max(int, int)const;

	void displayInOrder(TreeNode<T> *)const;
	void displayPreOrder(TreeNode<T> *)const;
	void displayPostOrder(TreeNode<T> *)const;
	
	void destroySubTree(TreeNode<T>*);
	
	void deleteLeafNode(TreeNode<T>*, TreeNode<T>*);
	
	TreeNode<T>* getSmallestNode(TreeNode<T>*);
	TreeNode<T>* getBiggerNode(TreeNode<T>*);
	TreeNode<T>* getParentOf(TreeNode<T>*);
public:
	Tree();
	virtual ~Tree();

	int getOperationsPerformedBySearch();

	void clear();
	void insert(T);
	bool remove(T);
	bool searchNode(T);
	bool isEmpty()const;

	int getCountNodes()const;
	int getHeight();
	
	T getRootData() const;
	void setRootData(T);

	void displayInOrder()const;
	void displayPreOrder()const;
	void displayPostOrder()const;

	TreeNode<T>* deleteNode(TreeNode<T>*, T);
	void displayTree();		//Function that will display the indented tree
};

template<class T>
Tree<T>::Tree()
{
	root = nullptr;
	searchOp = 0;
}

template<class T>
Tree<T>::~Tree()
{
	//Deletes the tree by calling the clear function, 
	//which calls destroySubTree function with root
	//as a parameter
	clear();
}

template<class T>
int Tree<T>::getOperationsPerformedBySearch()
{
	return searchOp;
}

template<class T>
void Tree<T>::clear()
{
	destroySubTree(root);
	
}  

template <class T>
void Tree<T>::destroySubTree(TreeNode<T>* nodePtr)
{
	if (nodePtr != nullptr)
	{
		destroySubTree(nodePtr->getLeft());
		destroySubTree(nodePtr->getRight());
		delete nodePtr;
	}
}

template<class T>
bool Tree<T>::remove(T key)
{
	if (!searchNode(key)) return true;

	deleteNode(root, key);
	return true;
}

template <class T>
void Tree<T>::deleteLeafNode(TreeNode<T>* parent, TreeNode<T> *nodePtr)
{
	if (parent->getLeft() == nodePtr)
		parent->setLeft(nullptr);
	else if (parent->getRight() == nodePtr)
		parent->setRight(nullptr);

	delete nodePtr;
	nodePtr = nullptr;
}

template<class T>
TreeNode<T>* Tree<T>::getParentOf(TreeNode<T> *nodePtr)
{
	TreeNode<T> *tempPtr = root;
	TreeNode<T> *parent = nullptr;
	
	T key = nodePtr->getData();

	while (tempPtr != nullptr) 
	{
		if (tempPtr->getData() == key)	//If the node is found
		{
			return parent;
		}
		else if (key < tempPtr->getData())
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

template<class T>
TreeNode<T>* Tree<T>::getSmallestNode(TreeNode<T>* rootPtr)
{
	TreeNode<T> *tempPtr = rootPtr;
	//Traverse all the way to the left most node which is 
	//at the same time the smallest node
	while (tempPtr->getLeft() != nullptr)
		tempPtr = tempPtr->getLeft();
	return tempPtr;
}

template<class T>
TreeNode<T>* Tree<T>::getBiggerNode(TreeNode<T>* rootPtr)
{
	TreeNode<T> *tempPtr = rootPtr;
	while (tempPtr->getRight() != nullptr)
		tempPtr = tempPtr->getRight();

	//Will return the right most node which is also the biggest node 
	return tempPtr;	
}

template<class T>
void Tree<T>::insert(T data)
{
	insertNode(data);
}

template<class T>
void Tree<T>::insertNode(T d)
{
	TreeNode<T>* t = new TreeNode<T>;	//Allocate a new TreeNode
	TreeNode<T>* parent = nullptr;

	t->setData(d);
	t->setLeft(nullptr);	//Because is will be a leaf node
	t->setRight(nullptr);

	// If it is a new tree
	if (root == nullptr) root = t;
	else
	{
		TreeNode<T> * curr = root;

		// Find the Node's parent
		while (curr)
		{
			parent = curr;
			if (t->getData() < curr->getData()) curr = curr->getLeft();
			else curr = curr->getRight();
		}

		if (t->getData() < parent->getData())
			parent->setLeft(t);
		else
			parent->setRight(t);
	}
}

template<class T>
bool Tree<T>::searchNode(T key)
{
	TreeNode <T>* nodePtr = root;	searchOp++;
	//Traverse the tree
	searchOp++;
	while (nodePtr != nullptr)
	{
		if (nodePtr->getData() == key)
		{
			searchOp += 2;
			return true;
		}//If the data is found, return true
		else if (key < nodePtr->getData())
		{
			searchOp += 2;
			nodePtr = nodePtr->getLeft();
		}//Else if the data is less, move to the left of the tree
		else
		{
			nodePtr = nodePtr->getRight(); //Else, Move to the right
			searchOp += 2;
		}
		searchOp++;
	}	
	return false;
}

template<class T>
void Tree<T>::displayInOrder() const
{
	displayInOrder(root);
}

template<class T>
void Tree<T>::displayPreOrder() const
{
	displayPreOrder(root);
}

template<class T>
void Tree<T>::displayPostOrder() const
{
	displayPostOrder(root);
}

template<class T>
int Tree<T>::getCountNodes() const
{
	return countNodes(root);
}

template<class T>
bool Tree<T>::isEmpty() const
{
	return root == nullptr;
}

template<class T>
int Tree<T>::getHeight() 
{
	return getHeightHelper(root);
}

template<class T>
T Tree<T>::getRootData() const
{
	return root->data;
}

template<class T>
void Tree<T>::setRootData(T newData)
{	
	if (root != nullptr) root->setData(newData);
	else insertNode(newData);
}

template<class T>
int Tree<T>::countNodes(TreeNode<T> *nodePtr) const
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

template<class T>
int Tree<T>::getHeightHelper(TreeNode<T>* nodePtr) 
{
	if (nodePtr == nullptr) 
		return 0;
	else
	{
		return 1 + max(getHeightHelper(nodePtr->getLeft()), getHeightHelper(nodePtr->getRight()));
	}
}

template<class T>
void Tree<T>::displayInOrder(TreeNode<T> *nodePtr) const
{
	if (nodePtr)
	{
		displayInOrder(nodePtr->getLeft());
		std::cout << nodePtr->getData() << "\n";
		displayInOrder(nodePtr->getRight());
	}
}

template<class T>
void Tree<T>::displayPreOrder(TreeNode<T>* nodePtr) const
{
	if (nodePtr)
	{
		std::cout << nodePtr->getData() << "\n";
		displayPreOrder(nodePtr->getLeft());
		displayPreOrder(nodePtr->getRight());
	}
}

template<class T>
void Tree<T>::displayPostOrder(TreeNode<T>* nodePtr) const
{
	if (nodePtr)
	{
		displayPostOrder(nodePtr->getLeft());
		displayPostOrder(nodePtr->getRight());
		std::cout << nodePtr->getData() << "\n";
	}
}

template<class T>
int Tree<T>::max(int i,int j)const
{
	return i > j ? i : j;
}

template<class T>
TreeNode<T>* Tree<T>::deleteNode(TreeNode<T>*root, T value)
{
	if (root == nullptr)return root;
	else if (value < root->getData())  root->setLeft(deleteNode(root->getLeft(),value));
	else if (value > root->getData()) root->setRight(deleteNode(root->getRight(), value));
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
			deleteNode(root,value);
		}
		else if (root->hasRightChild() && !root->hasLeftChild())
		{
			root = root->getRight();
			deleteNode(root, value);
		}
		else
		{
			TreeNode<T> *smallestValue = getSmallestNode(root->getRight());
			T minData = smallestValue->getData();
			root->setData(minData);
			root->setRight(deleteNode(root->getRight(), minData));
		}
	}
	return root;
}

template<class T>
void Tree<T>::displayTree()
{
	//Breadth-first traversal
	Stack<TreeNode<std::string>*> q;
	if (root)
	{
		q.push(root);
		bDayOutFile << root->getData() << "\n";
	}
	while (!q.isEmpty())
	{
		TreeNode<std::string> *temp_node = q.peek();
		q.pop();

		if (temp_node->getLeft())
		{
			q.push(temp_node->getLeft());
			bDayOutFile << temp_node->getLeft()->getData() << "\n";
		}
		if (temp_node->getRight())
		{
			q.push(temp_node->getRight());
			bDayOutFile << temp_node->getRight()->getData() << "\n";
		}
	}

}

#endif // !TREE_H