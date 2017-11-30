#ifndef LINKEDNODE_H
#define LINKEDNODE_H

template<class T >
class LinkedNode
{
private:
	T data;
	LinkedNode <T> *next;
public:

	/**
	Description:	Constructor 1
	Pre :	None
	Post :	Assigns the next pointer to nullptr
	*/
	LinkedNode() : next(nullptr)
	{

	}

	/**
	Description: Constructor 2
	Pre : anItem
	Post :	Assigns the elements of the list to the elements of the entry list
	*/
	LinkedNode(const T&anItem) : data(anItem), next(nullptr)
	{

	}

	/**
	Description:  Constructor 3
	Pre :	anItem and nextLinkedLinkedNodePtr
	Post :	assigns anItem to data and nextLinkedLinkedNodePtr to next
	*/
	LinkedNode(const T&anItem, LinkedNode<T> nextLinkedNodePtr) : data(anItem), next(nextLinkedNodePtr)
	{
	}

	/**
	Description:	Sets the value of data
	Pre :	anItem
	Post :	None
	*/
	void setItem(const T& anItem)
	{
		data = anItem;
	}

	/**
	Description: Sets the value next
	Pre :	nextLinkedNodePtr
	Post :	None
	*/
	void setNext(LinkedNode <T> *nextLinkedNodePtr)
	{
		next = nextLinkedNodePtr;
	}

	/**
	Description: Returns the value of data
	Pre :	None
	Post :	Whatever is stored in data
	*/
	T getItem() const
	{
		return data;
	}

	/**
	Description: Returns next pointer
	Pre :	None
	Post :	Whatever is stored in next
	*/
	LinkedNode <T> *getNext() const
	{
		return next;
	}
};
#endif // !LINKEDNODE_H