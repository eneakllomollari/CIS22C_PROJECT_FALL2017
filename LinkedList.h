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

/**
Description: Insert LinkedNode in the list
Pre :	LinkedNode to be inserted
Post :	None
*/
template<class T>
void LinkedList<T>::insertListNode(const T LinkedNodeToInsert)
{
	ListNode <T> *newListNode = new ListNode <T>(LinkedNodeToInsert);
	ListNode <T> *ListNodePtr;
	ListNode <T> *previosListNode = nullptr;

	if (!head)
	{
		head = newListNode;
		newListNode->setNext(nullptr);
	}
	else
	{
		ListNodePtr = head;
		previosListNode = nullptr;

		while (ListNodePtr != nullptr && ListNodePtr->getItem() < LinkedNodeToInsert)
		{
			previosListNode = ListNodePtr;
			ListNodePtr = ListNodePtr->getNext();
		}

		if (previosListNode == nullptr)
		{
			head = newListNode;
			newListNode->setNext(ListNodePtr);
		}
		else
		{
			previosListNode->setNext(newListNode);
			newListNode->setNext(ListNodePtr);
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
	ListNode <T> *originalChain = aList->head;

	if (originalChain == nullptr) head = nullptr;
	else
	{
		//Copy first LinkedNode
		head = new ListNode <T>();
		head->setItem(originalChain->getItem());

		//Copy remaining LinkedNodes
		ListNode <T> *newChain = head;
		while (originalChain != nullptr)
		{
			originalChain = originalChain->getNext();

			//Get item from original chain
			T nextItem = originalChain->getItem();

			//Create a new LinkedNode containing the next item
			ListNode<T> *newLinkedNode = new ListNode <T>(nextItem);

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
	int frequency = 0,
		number = 0;
	ListNode <T> *curLinkedNode = head;
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
		ListNode <T> *LinkedNodeToDel = head;
		head = head->getNext();

		//Here we get the address of the data that we have allocated
		//T dataToDel = LinkedNodeToDel->getItem();

		//Remove the link
		LinkedNodeToDel->setNext(nullptr);

		//Delete the LinkedNode
		delete LinkedNodeToDel;

		//delete the allocated object
		//This will avoid the memory leak
		//delete dataToDel;

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
bool LinkedList<T>::deleteListNode(const T LinkedNodeToDelete)
{
	ListNode <T> *entryNode = getPointerTo(LinkedNodeToDelete);
	bool canRemoveItem = !isEmpty() && entryNode != nullptr;

	if (canRemoveItem)
	{
		//Copy data from first LinkedNode to located LinkedNode
		entryNode->setItem(head->getItem());

		//Delete first LinkedNode
		ListNode <T> *LinkedNodeToDel = head;
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
	ListNode <T> *temp;

	if (isEmpty()) return false;

	temp = head;
	head = head->getNext();

	delete temp;
	counter--;

	return true;
}


#endif