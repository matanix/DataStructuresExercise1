#pragma once

#include "LinkedList.h"

template <typename T>
class Stack
{
public:
	Stack() = default;

	bool Push(T element)
	{
		Node<T>* newNode = new Node<T>(element);
		if (newNode == nullptr)
		{
			return false;
		}
		
		return m_list.AddFront(newNode);
	}

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

	int GetSize()
	{
		return m_list.GetSize();
	}

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
