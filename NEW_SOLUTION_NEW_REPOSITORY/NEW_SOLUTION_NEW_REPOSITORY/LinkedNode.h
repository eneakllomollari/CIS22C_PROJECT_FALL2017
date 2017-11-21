#ifndef LINKEDNODE_H
#define LINKEDNODE_H

template<class T >
class LinkedNode
{
private:
	T data;
	LinkedNode <T> *next;
public:

	int eff_counter = 0;

	LinkedNode();
	LinkedNode(const T&anItem);
	LinkedNode(const T&anItem, LinkedNode<T> nextLinkedNodePtr);

	void setItem(const T& anItem);
	void setNext(LinkedNode <T> *nextLinkedNodePtr);

	T getItem() const;
	LinkedNode <T> *getNext() const;
};

/**
Description:	Constructor 1
Pre :	None
Post :	Assigns the next pointer to nullptr
*/
template<class T>
LinkedNode<T>::LinkedNode()
{
	next = nullptr;
	eff_counter++;
}


/**
Description: Constructor 2
Pre : anItem
Post :	Assigns the elements of the list to the elements of the entry list
*/
template<class T>
LinkedNode<T>::LinkedNode(const T & anItem)
{
	data = anItem;
	next = nullptr;
	eff_counter += 2;
}
/**
Description:  Constructor 3
Pre :	anItem and nextLinkedNodePtr
Post :	assigns anItem to data and nextLinkedNodePtr to next
*/
template<class T>
LinkedNode<T>::LinkedNode(const T & anItem, LinkedNode<T> nextLinkedNodePtr)
{
	data = anItem;
	next = nextLinkedNodePtr;
	eff_counter += 2;
}

/**
Description:	Sets the value of data
Pre :	anItem
Post :	None
*/
template<class T>
void LinkedNode<T>::setItem(const T & anItem)
{
	data = anItem;
	eff_counter ++;
}
/**
Description: Sets the value next
Pre :	nextLinkedNodePtr
Post :	None
*/
template<class T>
void LinkedNode<T>::setNext(LinkedNode<T>* nextLinkedNodePtr)
{
	next = nextLinkedNodePtr;
	eff_counter ++;
}
/**
Description: Returns the value of data
Pre :	None
Post :	Whatever is stored in data
*/
template<class T>
T LinkedNode<T>::getItem() const
{
	return data;
	eff_counter ++;
}

/**
Description: Returns next pointer
Pre :	None
Post :	Whatever is stored in next
*/
template<class T>
LinkedNode<T>* LinkedNode<T>::getNext() const
{
	return next;
	eff_counter ++;
}

#endif // !LinkedNode_H