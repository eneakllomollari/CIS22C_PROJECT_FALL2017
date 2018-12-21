#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "ListNode.h"

template <class T>
class LinkedList
{
protected:
	ListNode <T> *head;									// Pointer to the first ListNode
	int counter;											// Count of items
	ListNode <T> *getPointerTo(const T&) const;

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

	bool deleteListNode(const T);
	bool deleteFirst();

	void insertListNode(const T);
	void insertFirst(T);
};
#endif