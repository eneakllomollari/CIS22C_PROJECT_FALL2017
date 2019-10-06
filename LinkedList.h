#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "ListNode.h"

template <class T>
class LinkedList
{
protected:
	ListNode <T> *head;
	int counter;
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

template<class T>
void LinkedList<T>::insertListNode(const T LinkedNodeToInsert)
{
	ListNode <T> *newListNode = new ListNode <T>(LinkedNodeToInsert);
	ListNode <T> *ListNodePtr;
	ListNode <T> *previousListNode = nullptr;

	if (!head)
	{
		head = newListNode;
		newListNode->setNext(nullptr);
	}
	else
	{
		ListNodePtr = head;
		previousListNode = nullptr;

		while (ListNodePtr != nullptr && ListNodePtr->getItem() < LinkedNodeToInsert)
		{
			previousListNode = ListNodePtr;
			ListNodePtr = ListNodePtr->getNext();
		}

		if (previousListNode == nullptr)
		{
			head = newListNode;
			newListNode->setNext(ListNodePtr);
		}
		else
		{
			previousListNode->setNext(newListNode);
			newListNode->setNext(ListNodePtr);
		}
	}
	counter++;
}

template<class T>
void LinkedList<T>::insertFirst(T linkedNodeToInsert)
{
	ListNode <T> *LinkedNodePtr;
	ListNode <T> *newLinkedNode = new ListNode <T>(linkedNodeToInsert);

	LinkedNodePtr = head;

	newLinkedNode->setNext(LinkedNodePtr);
	head = newLinkedNode;
	counter++;
}

template<class T>
ListNode<T>* LinkedList<T>::getPointerTo(const T & target) const
{
	bool found = false;
	ListNode <T> *curr = head;

	while (!found && curr != nullptr)
	{
		if (target == curr->getItem())	found = true;
		else curr = curr->getNext();
	}
	return curr;
}

template<class T>
LinkedList<T>::LinkedList()
{
	head = nullptr;
	counter = 0;
}

template< class T>
LinkedList<T>::LinkedList(const LinkedList<T>& aList)
{
	counter = aList->counter;
	ListNode <T> *originalChain = aList->head;

	if (originalChain == nullptr) head = nullptr;
	else
	{
		head = new ListNode <T>();
		head->setItem(originalChain->getItem());

		ListNode <T> *newChain = head;
		while (originalChain != nullptr)
		{
			originalChain = originalChain->getNext();
			T nextItem = originalChain->getItem();
			ListNode<T> *newLinkedNode = new ListNode <T>(nextItem);
			newChain->setNext(newLinkedNode);
			newChain = newChain->getNext();
		}
		newChain->setNext(nullptr);
	}
}

template <class T>
LinkedList<T>::~LinkedList()
{
	clear();
}

template <class T>
bool LinkedList<T>::isEmpty() const
{
	return counter == 0;
}

template<class T>
void LinkedList<T>::displayList() const
{
	ListNode <T> *LinkedNodePtr = head;
	while (LinkedNodePtr != nullptr)
	{
		std::cout << *LinkedNodePtr->getItem() << std::endl;
		LinkedNodePtr = LinkedNodePtr->getNext();
	}
}


template<class T>
int LinkedList<T>::getFrequencyOf(const T & anEntry) const
{
	int frequency = 0, number = 0;
	ListNode <T> *curLinkedNode = head;
	while (curLinkedNode != nullptr && number < counter)
	{
		if (anEntry == curLinkedNode->getItem()) frequency++;
		number++;
		curLinkedNode = curLinkedNode->getNext();
	}
	return frequency;
}

template<class T>
void LinkedList<T>::clear()
{
	while (head != nullptr)
	{
		ListNode <T> *LinkedNodeToDel = head;
		head = head->getNext();
		LinkedNodeToDel->setNext(nullptr);
		delete LinkedNodeToDel;
	}
	counter = 0;
}

template<class T>
int LinkedList<T>::getSize() const
{
	return counter;
}

template<class T>
bool LinkedList<T>::contains(const T & anEntry) const
{
	return getPointerTo(anEntry) != nullptr;
}

template<class T>
bool LinkedList<T>::deleteListNode(const T LinkedNodeToDelete)
{
	ListNode <T> *entryNode = getPointerTo(LinkedNodeToDelete);
	bool canRemoveItem = !isEmpty() && entryNode != nullptr;

	if (canRemoveItem)
	{
		entryNode->setItem(head->getItem());

		ListNode <T> *LinkedNodeToDel = head;
		head = head->getNext();

		LinkedNodeToDel->setNext(nullptr);
		delete LinkedNodeToDel;
		LinkedNodeToDel = nullptr;

		counter--;
	}
	return canRemoveItem;
}

template<class T>
bool LinkedList<T>::deleteFirst()
{
	ListNode <T> *temp;

	if (isEmpty()) return false;

	temp = head;
	head = head->getNext();

	delete temp;
	counter--;

	return true;
}

#endif