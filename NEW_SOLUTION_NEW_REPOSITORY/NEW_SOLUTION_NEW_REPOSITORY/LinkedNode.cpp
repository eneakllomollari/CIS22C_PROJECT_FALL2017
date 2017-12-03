#include "LinkedNode.h"

template<class T>
LinkedNode<T>::LinkedNode(const T & anItem, LinkedNode<T> nextLinkedNodePtr)
{
	data = anItem;
	next = nextLinkedNodePtr;
}

template<class T>
void LinkedNode<T>::setItem(const T & anItem)
{
	data = anItem;
}

template<class T>
void LinkedNode<T>::setNext(LinkedNode<T>* nextLinkedNodePtr)
{
	next = nextLinkedNodePtr;
}

template<class T>
T LinkedNode<T>::getItem() const
{
	return data;
}

template<class T>
LinkedNode<T>* LinkedNode<T>::getNext() const
{
	return next;
}

template<class T>
LinkedNode<T>::LinkedNode()
{
	next = nullptr;
}

template<class T>
LinkedNode<T>::LinkedNode(const T & anItem)
{
	data = anItem;
	next = nullptr;
}

