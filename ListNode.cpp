#include "ListNode.h"

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