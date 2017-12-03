#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "LinkedNode.h"

template <class T>
class LinkedList
{
protected:
	LinkedNode <T> *head;									// Pointer to the first LinkedNode
	int counter;											// Count of items
	LinkedNode <T> *getPointerTo(const T&) const;

public:

	LinkedList();
	LinkedList(const LinkedList <T>&);
	virtual ~LinkedList();

	bool isEmpty() const;
	void displayList() const;
	int getFrequencyOf(const T&) const;
	void clear();
	int getSize() const;
	bool contains(const T&) const;

	bool deleteLinkedNode(const T);
	bool deleteFirst();

	void insertLinkedNode(const T);
	void insertFirst(T);
};
#include "LinkedList.cpp"
#endif