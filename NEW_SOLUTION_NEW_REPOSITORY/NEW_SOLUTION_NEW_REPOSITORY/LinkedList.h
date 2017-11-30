#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "LinkedNode.h"

template <class T>
class LinkedList
{
protected:
	LinkedNode <T> *head;													// Pointer to the first LinkedNode
	int counter;													// Count of items
	LinkedNode <T> *getPointerTo(const T& target) const
	{
		bool found = false;
		LinkedNode <T> *curr = head;

		while (!found && curr != nullptr)
		{
			if (target == curr->getItem())	found = true;
			else curr = curr->getNext();
		}
		return curr;
	}			// Helper function			// Helper function

public:

	LinkedList();
	LinkedList(const LinkedList <T>&);
	virtual ~LinkedList();

	bool isEmpty() const;
	void displayList() const;
	int getFrequencyOf(const T& anEntry) const;
	void clear();
	int getSize() const;
	bool contains(const T& anEntry) const;

	bool deleteLinkedNode(const T LinkedNodeToDelete);
	bool deleteFirst();

	void insertLinkedNode(const T LinkedNodeToInsert);
	void insertFirst(T LinkedNodeToInsert);
};

/**
Description: LinkedList Constructor
Pre :	None
Post :	head of the list is assigned to nullptr and counter is assigned to 0
*/
template<class T>
LinkedList<T>::LinkedList()
{
	head = nullptr;
	counter = 0;
}


/**
Description:  Constructor
Pre :	list object
Post :	Adds to contents of the entry list to this list
*/
template< class T>
LinkedList<T>::LinkedList(const LinkedList<T>& aList)

{
	counter = aList->counter;
	LinkedNode <T> *originalChain = aList->head;

	if (originalChain == nullptr) head = nullptr;
	else
	{
		//Copy first LinkedNode
		head = new LinkedNode <T>();
		head->setItem(originalChain->getItem());

		//Copy remaining LinkedNodes
		LinkedNode <T> *newChain = head;
		while (originalChain != nullptr)
		{
			originalChain = originalChain->getNext();

			//Get item from original chain
			T nextItem = originalChain->getItem();

			//Create a new LinkedNode containing the next item
			LinkedNode <T> *newLinkedNode = new LinkedNode <T>(nextItem);

			//Link new LinkedNode to end of chain
			newChain->setNext(newLinkedNode);

			//Advance pointer to new last LinkedNode
			newChain = newChain->getNext();
		} // end of while
		newChain->setNext(nullptr);
	}//end if
}//end of copy constructor


 /**
 Description: Virtual Destructor
 Pre :	None
 Post :	Frees the memory allocated by the list and deletes the list object
 */
template <class T>
LinkedList<T>::~LinkedList()
{
	clear();
}


/**
Description:	Sees whether the list is empty
Pre: None
Post: True if list is empty, otherwise is false
*/
template <class T>
bool LinkedList<T>::isEmpty() const
{
	return counter == 0;
}


/**
Description: Get the number of times a LinkedNode is present in the list
Pre : the LinkedNode whose frequency is to be checked
Post : the number of times the LinkedNode is present in the list
*/
template<class T>
void LinkedList<T>::displayList() const
{
	LinkedNode <T> *LinkedNodePtr = head;
	while (LinkedNodePtr != nullptr)
	{
		std::cout << LinkedNodePtr->getItem() << std::endl;
		LinkedNodePtr = LinkedNodePtr->getNext();
	}
}


template<class T>
int LinkedList<T>::getFrequencyOf(const T & anEntry) const
{
	int frequency = 0,
		number = 0;
	LinkedNode <T> *curLinkedNode = head;
	while (curLinkedNode != nullptr && number < counter)
	{
		if (anEntry == curLinkedNode->getItem()) frequency++;
		number++;
		curLinkedNode = curLinkedNode->getNext();
	}
	return frequency;
}

/**
Description: Clear all the elements in the list
Pre : None
Post : None
*/
template<class T>
void LinkedList<T>::clear()
{
	while (head != nullptr)
	{
		LinkedNode <T> *LinkedNodeToDel = head;
		head = head->getNext();
		
		T dataToDel = LinkedNodeToDel->getItem();
	
		LinkedNodeToDel->setNext(nullptr);
		
		delete LinkedNodeToDel;
		delete dataToDel;

	}
	counter = 0;
}


/**
Description: Return the size of the list
Pre :  None
Post :  The size of the list
*/
template<class T>
int LinkedList<T>::getSize() const
{
	return counter;
}


/**
Description: Checks to see if a LinkedNode is contained in the list
Pre :	the LinkedNode to be checked
Post :	true if LinkedNode is contained, false otherwise
*/
template<class T>
bool LinkedList<T>::contains(const T & anEntry) const
{
	return getPointerTo(anEntry) != nullptr;
}


/**
Description: Delete a LinkedNode from the list
Pre :	LinkedNode to be deleted
Post :	true if LinkedNode was found and deleted, false otherwise
*/
template<class T>
bool LinkedList<T>::deleteLinkedNode(const T LinkedNodeToDelete)
{
	LinkedNode <T> *entryLinkedNode = getPointerTo(LinkedNodeToDelete);
	bool canRemoveItem = !isEmpty() && entryLinkedNode != nullptr;

	if (canRemoveItem)
	{
		//Copy data from first LinkedNode to located LinkedNode
		entryLinkedNode->setItem(head->getItem());

		//Delete first LinkedNode
		LinkedNode <T> *LinkedNodeToDel = head;
		head = head->getNext();

		//Return LinkedNode to the system
		LinkedNodeToDel->setNext(nullptr);
		delete LinkedNodeToDel;
		LinkedNodeToDel = nullptr;

		counter--;
	}
	return canRemoveItem;
}


/**
Description: Delete the first LinkedNode in the list
Pre :	None
Post : True if LinkedNode was found and deleted, false otherwise
*/
template<class T>
bool LinkedList<T>::deleteFirst()
{
	LinkedNode <T> *temp;

	if (isEmpty()) return false;

	temp = head;
	head = head->getNext();

	delete temp;
	counter--;

	return true;
}


/**
Description: Insert LinkedNode in the list
Pre :	LinkedNode to be inserted
Post :	None
*/
template<class T>
void LinkedList<T>::insertLinkedNode(const T LinkedNodeToInsert)
{
	LinkedNode <T> *newLinkedNode = new LinkedNode <T>(LinkedNodeToInsert);
	LinkedNode <T> *LinkedNodePtr;
	LinkedNode <T> *previosLinkedNode = nullptr;

	if (!head)
	{
		head = newLinkedNode;
		newLinkedNode->setNext(nullptr);
	}
	else
	{
		LinkedNodePtr = head;

		previosLinkedNode = nullptr;

		while (LinkedNodePtr != nullptr && LinkedNodePtr->getItem() < LinkedNodeToInsert)
		{
			previosLinkedNode = LinkedNodePtr;
			LinkedNodePtr = LinkedNodePtr->getNext();
		}

		if (previosLinkedNode == nullptr)
		{
			head = newLinkedNode;
			newLinkedNode->setNext(LinkedNodePtr);
		}
		else
		{
			previosLinkedNode->setNext(newLinkedNode);
			newLinkedNode->setNext(LinkedNodePtr);
		}
	}
	counter++;
}


/**
Description: Insert LinkedNode to the first position in the list
Pre :	LinkedNode to be inserted
Post :	None
*/
template<class T>
void LinkedList<T>::insertFirst(T LinkedNodeToInsert)
{
	LinkedNode <T> *LinkedNodePtr;
	LinkedNode <T> *newLinkedNode = new LinkedNode <T>(LinkedNodeToInsert);

	LinkedNodePtr = head;

	newLinkedNode->setNext(LinkedNodePtr);
	head = newLinkedNode;
	counter++;
}

#endif