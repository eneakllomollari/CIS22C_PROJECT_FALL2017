#ifndef ListNode_H
#define ListNode_H

template<class T >
class ListNode
{
private:
	T data;
	ListNode <T> *next;
public:

	ListNode();
	ListNode(const T&);
	ListNode(const T&, ListNode<T>);;
	
	void setItem(const T&);
	void setNext(ListNode <T> *);

	T getItem() const;
	ListNode <T> *getNext() const;
};
#include "ListNode.cpp"
#endif // !ListNode_H