#pragma once

#include "LinkedList.h"

//A Templatic stack using the LinkedList implementation.
//This stack manages dynamic allocation in itself 
template <typename T>
class Stack
{
public:
	Stack() = default;

	//Allocates a node of the given value and pushes it to the front of the stack.
	bool Push(T element)
	{
		Node<T>* newNode = new Node<T>(element);
		if (newNode == nullptr)
		{
			return false;
		}
		
		return m_list.AddFront(newNode);
	}

	//Pops the front element of the stack and returns it's value.
	bool Pop(T& o_element)
	{
		Top(o_element);

		Node<T>* toFree = m_list.GetAt(0);
		bool retVal = true;

		if (toFree != nullptr)
		{
			retVal = m_list.RemoveFront();
			delete toFree;
		}
		
		return retVal;
	}

	//Returns the value of the front element of the stack.
	bool Top(T& o_element)
	{
		Node<T>* head = m_list.GetAt(0);

		if (head == nullptr)
		{
			return false;
		}

		o_element = head->GetValue();
		return true;
	}

	//Returns the size of the stack.
	int GetSize()
	{
		return m_list.GetSize();
	}

	//A D'tor that frees all remaining dynamically allocated nodes.
	~Stack()
	{
		Node<T>* ptr = m_list.GetAt(0);
		Node<T>* toFree = nullptr;

		while (ptr != nullptr)
		{
			toFree = ptr;
			ptr = ptr->GetNext();
			delete toFree;
		}
	}
private:
	LinkedList<T> m_list;
};
