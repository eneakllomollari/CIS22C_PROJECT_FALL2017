#ifndef TREENODE_H
#define TREENODE_H

template<class T>
class TreeNode
{
private:
	T data;
	int eff_counter = 0


	TreeNode<T> *left;
	TreeNode<T> *right;

public:
	TreeNode();
	TreeNode(T);
	TreeNode(T, TreeNode<T>*, TreeNode<T>*);

	void setLeft(TreeNode<T> *);
	void setRight(TreeNode<T> *);
	void setData(T);
	
	bool isLeaf() const;
	bool hasLeftChild() const;
	bool hasRightChild() const;

	TreeNode<T>* getRight();
	TreeNode<T>* getLeft();
	T getData();
};


template<class T>
TreeNode<T>::TreeNode()
{
	left = right = nullptr;
	eff_counter++;
}

template<class T>
TreeNode<T>::TreeNode(T d)
{
	data = d;
	left = nullptr;
	right = nullptr;
}

template<class T>
TreeNode<T>::TreeNode(T d, TreeNode<T> *l, TreeNode<T> *r)
{
	data = d;
	left = l;
	right = r;
}

/**
Description: Mutator
Pre: TreeNode pointer
Post: Sets the left pointer
*/
template<class T>
void TreeNode<T>::setLeft(TreeNode<T> *l)
{
	left = l;
}

/**
Description: Mutator
Pre: TreeNode pointer
Post: Sets the right pointer
*/
template<class T>
void TreeNode<T>::setRight(TreeNode<T> *r)
{
	right = r;
	eff_counter++;
}

template<class T>
void TreeNode<T>::setData(T d)
{
	data = d;
	eff_counter++;
}

template<class T>
bool TreeNode<T>::isLeaf() const
{
	return left == nullptr && right == nullptr;
	eff_counter++;
}

template<class T>
bool TreeNode<T>::hasLeftChild() const
{
	return left != nullptr;
	eff_counter++;
}

template<class T>
bool TreeNode<T>::hasRightChild() const
{
	return right != nullptr;
	eff_counter++;
}

/**
Description: Accessor
Pre: None
Post: Returns the right pointer
*/
template<class T>
TreeNode<T>* TreeNode<T>::getRight()
{
	return right;
	eff_counter++;
}

template<class T>
TreeNode<T>* TreeNode<T>::getLeft()
{
	return left;
	eff_counter++;
}

template<class T>
T TreeNode<T>::getData()
{
	return data;
	eff_counter++;
}

#endif // !TREENODE_H