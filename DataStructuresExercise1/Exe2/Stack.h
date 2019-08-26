#pragma once

#include <iostream>
#include "LinkedList.h"

template <typename T>
class Stack
{
public:
	Stack() = default;

	Stack(LinkedList<T>* list)
		: m_list(list)
	{}

	bool Push(T* element)
	{
		if (element == nullptr || m_list == nullptr)
		{
			return false;
		}

		return m_list.AddFront(element);
	}

	bool Pop()
	{
		return m_list.RemoveFront();
	}

	bool Top(T* o_element)
	{
		if (o_element == nullptr || m_list == nullptr)
		{
			return false;
		}

		o_element = m_list.GetAt(0);
		return true;
	}

	~Stack() = default;
private:
	LinkedList<T>* m_list = nullptr;
};
