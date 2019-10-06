#ifndef STACK_H
#define STACK_H

#include "LinkedList.h"

template <class T>
class Stack : protected LinkedList <T>
{
public:
	Stack();
	virtual ~Stack();
	void push(T);
	bool pop();
	T peek();

	bool isEmpty();
	int getSize();
	void displayStack();
	void clearStack();
};

template<class T>
Stack<T>::Stack()
{
	LinkedList<T>();
}

template<class T>
Stack<T>::~Stack()
{
	clearStack();
}

template<class T>
void Stack<T>::push(T valueToPush)
{
	this->insertFirst(valueToPush);
}


template<class T>
bool Stack<T>::pop()
{
	if (this->deleteFirst()) return true;
	return false;
}

template<class T>
T Stack<T>::peek()
{
	if (this->head== nullptr) throw "The recovery bin is empty! You Have not deleted anything yet";
	return this->head->getItem();
}


template<class T>
bool Stack<T>::isEmpty()
{
	return this->getSize()== 0;
}

template <class T>
int Stack<T>::getSize()
{
	return this->counter;
}

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

#endif // !STACK_H