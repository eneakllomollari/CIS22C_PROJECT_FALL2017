#ifndef STACK_H
#define STACK_H

#include "LinkedList.h"

template <class T>
class Stack : protected LinkedList <T>
{
public:
	/**
	Description: Stack Destructor
	Pre :	None
	Post :	Assigns the  head and counter using the base class constructor
	*/
	Stack() : LinkedList() {};

	void clearStack();

	/**
	Description: Adds valueToPush to the top of the stack
	Pre :	valueToPush
	Post :	None
	*/
	void push(T valueToPush)
	{
		this->insertFirst(valueToPush);
	}

	/**
	Description: Removes the top of the stack, that is removes the element that was added last
	Pre :	None
	Post :	True if operation was succesful, otherwise false
	*/
	bool pop()
	{
		if (this->deleteFirst())return true;
		return false;
	}

	/**
	Description:	Returns the top of this stack. That is it gets the item that was added most recently
	It does not change the stack
	Pre :	None
	Post :	The top of the stack
	*/
	T peek()
	{
		if (head == nullptr) throw "THERE IS NO OBJECT TO BE RESTORED";
		return this->head->getItem();
	}

	/**
	Description: Sees whether the stack is empty
	Pre :	None
	Post :	True if the stack is empty, otherwise false
	*/
	bool isEmpty()
	{
		return  counter == 0;
	}

	/**
	Description: Returns the size of the stack, that is the number of elements in the stack
	Pre :	None
	Post :	The number of elements in the stack
	*/
	int getSize()
	{
		return this->getSize();
	}

	/**
	Description:	Displays the elements present in the stack
	Pre :	None
	Post :	Sends the elements of the stack in the output, each one at a line
	*/
	void displayStack()
	{
		this->displayList();
	}
};
#endif // !STACK_H

template<class T>
void Stack<T>::clearStack()
{
	this->clear();
}
