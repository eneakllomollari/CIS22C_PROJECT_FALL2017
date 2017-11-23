#ifndef TREENODE_H
#define TREENODE_H

template<class K, class T>
class TreeNode
{
private:
	K key;
	T data;

	TreeNode<K, T> *left;
	TreeNode<K, T> *right;

public:
	TreeNode();
	TreeNode(T);
	TreeNode(K, T, TreeNode<K, T>*, TreeNode<K, T>*);

	void setLeft(TreeNode<K, T> *);
	void setRight(TreeNode<K, T> *);
	void setData(T);
	void setKey(K);

	bool isLeaf() const;
	bool hasLeftChild() const;
	bool hasRightChild() const;

	TreeNode<K, T>* getRight();
	TreeNode<K, T>* getLeft();
	T getData();
	K getKey();
};


template<class K, class T>
TreeNode<K, T>::TreeNode()
{
	left = right = nullptr;
}

template<class K, class T>
TreeNode<K, T>::TreeNode(T d)
{
	data = d;
	left = nullptr;
	right = nullptr;
}

template<class K, class T>
TreeNode<K, T>::TreeNode(K k, T d, TreeNode<K, T> *l, TreeNode<K, T> *r)
{
	key = k;
	data = d;
	left = l;
	right = r;
}

/**
Description: Mutator
Pre: TreeNode pointer
Post: Sets the left pointer
*/
template<class K, class T>
void TreeNode<K, T>::setLeft(TreeNode<K, T> *l)
{
	left = l;
}

/**
Description: Mutator
Pre: TreeNode pointer
Post: Sets the right pointer
*/
template<class K, class T>
void TreeNode<K, T>::setRight(TreeNode<K, T> *r)
{
	right = r;
}

template<class K, class T>
void TreeNode<K, T>::setData(T d)
{
	data = d;
}

template<class K, class T>
void TreeNode<K, T>::setKey(K k)
{
	key = k;
}

template<class K, class T>
bool TreeNode<K, T>::isLeaf() const
{
	return left == nullptr && right == nullptr;
}

template<class K, class T>
bool TreeNode<K, T>::hasLeftChild() const
{
	return left != nullptr;
}

template<class K, class T>
bool TreeNode<K, T>::hasRightChild() const
{
	return right != nullptr;
}

/**
Description: Accessor
Pre: None
Post: Returns the right pointer
*/
template<class K, class T>
TreeNode<K, T>* TreeNode<K, T>::getRight()
{
	return right;
}

template<class K, class T>
TreeNode<K, T>* TreeNode<K, T>::getLeft()
{
	return left;
}

template<class K, class T>
T TreeNode<K, T>::getData()
{
	return data;
}

template<class K, class T>
K TreeNode<K, T>::getKey()
{
	return key;
}

#endif // !TREENODE_H