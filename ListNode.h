#ifndef ListNode_H
#define ListNode_H

#include <iostream>

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

template<class T>
ListNode<T>::ListNode(const T & anItem, ListNode<T> nextListNodePtr)
{
	this->data = anItem;
	this->next = nextListNodePtr;
}

template<class T>
void ListNode<T>::setItem(const T & anItem)
{
	this->data = anItem;
}

template<class T>
void ListNode<T>::setNext(ListNode<T>* nextListNodePtr)
{
	this->next = nextListNodePtr;
}

template<class T>
T ListNode<T>::getItem() const
{
	return this->data;
}

template<class T>
ListNode<T>* ListNode<T>::getNext() const
{
	return this->next;
}

template<class T>
ListNode<T>::ListNode()
{
	this->next = nullptr;
}

template<class T>
ListNode<T>::ListNode(const T & anItem)
{
	this->data = anItem;
	this->next = nullptr;
}
#endif // !ListNode_H