#ifndef LINKEDNODE_H
#define LINKEDNODE_H

template<class T >
class LinkedNode
{
private:
	T data;
	LinkedNode <T> *next;
public:

	LinkedNode();
	LinkedNode(const T&);
	LinkedNode(const T&, LinkedNode<T>);;
	
	void setItem(const T&);
	void setNext(LinkedNode <T> *);

	T getItem() const;
	LinkedNode <T> *getNext() const;
};
#include "LinkedNode.cpp"
#endif // !LINKEDNODE_H