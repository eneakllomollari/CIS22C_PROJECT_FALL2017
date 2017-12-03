#include "Stack.h"

/**
Description: Stack Destructor
Pre :	None
Post :	Assigns the  head and counter using the base class constructor
*/
template<class T>
Stack<T>::Stack()
{
	LinkedList();
}

template<class T>
Stack<T>::~Stack()
{
	clearStack();
}

/**
Description: Adds valueToPush to the top of the stack
Pre :	valueToPush
Post :	None
*/
template<class T>
void Stack<T>::push(T valueToPush)
{
	this->insertFirst(valueToPush);
}


/**
Description: Removes the top of the stack, that is removes the element that was added last
Pre :	None
Post :	True if operation was succesful, otherwise false
*/
template<class T>
bool Stack<T>::pop()
{
	if (this->deleteFirst()) return true;
	return false;
}

/**
Description:	Returns the top of this stack. That is it gets the item that was added most recently
It does not change the stack
Pre :	None
Post :	The top of the stack
*/
template<class T>
T Stack<T>::peek()
{
	if (head == nullptr) throw "Cannot peek";
	return this->head->getItem();
}


/**
Description: Sees whether the stack is empty
Pre :	None
Post :	True if the stack is empty, otherwise false
*/
template<class T>
bool Stack<T>::isEmpty()
{
	return counter == 0;
}

/**
Description: Returns the number of elements in the stack
Pre :	None
Post :	True if the stack is empty, otherwise false
*/
template <class T>
int Stack<T>::getSize()
{
	return counter;
}

/**
Description: Displays the elements of the stack to standart output
Pre :	None
Post :	Node
*/
template<class T>
void Stack<T>::displayStack()
{
	this->displayList();
}

template<class T>
void Stack<T>::clearStack()
{
	this->clear();
}

