#ifndef STACK_H
#define STACK_H

#include "LinkedList.h"

template <class T>
class Stack : protected LinkedList <T>
{
public:
	Stack();
	~Stack();
	void push(T);
	bool pop();
	T peek();

	bool isEmpty();
	int getSize();
	void displayStack();
	void clearStack();
};
#include "Stack.cpp"
#endif // !STACK_H