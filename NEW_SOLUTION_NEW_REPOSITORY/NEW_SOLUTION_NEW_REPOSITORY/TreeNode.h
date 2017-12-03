#ifndef TREENODE_H
#define TREENODE_H

template<class K, class T>
class TreeNode
{
private:
	K key;
	T pData;

	TreeNode<K, T> *left;
	TreeNode<K, T> *right;

public:
	TreeNode();
	TreeNode(T);
	TreeNode(K, T);

	void setLeft(TreeNode<K, T> *);
	void setRight(TreeNode<K, T> *);
	void setpData(T);
	void setKey(K);

	bool isLeaf() const;
	bool hasLeftChild() const;
	bool hasRightChild() const;

	TreeNode<K, T>* getRight();
	TreeNode<K, T>* getLeft();
	T getpData();
	K getKey();
};
#include "TreeNode.cpp"
#endif // !TREENODE_H