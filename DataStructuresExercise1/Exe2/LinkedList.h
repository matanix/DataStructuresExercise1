#pragma once

template <typename T>
class Node
{
public:
	explicit Node(T& value, T* next = nullptr)
		: m_value(value), m_next(next)
	{}

	bool SetNext(T* next)
	{
		if (next == nullptr)
		{
			return false;
		}

		m_next = next;
		return true;
	}

	T* GetNext()
	{
		return m_next;
	}

	T& GetValue()
	{
		return m_value;
	}

	~Node() = default;
	
private:

	T& m_value;
	T* m_next = nullptr;
};

template <typename T>
class LinkedList
{
public:
	LinkedList(T* head)
		: m_head(head)
	{}

	LinkedList() = default;

	bool AddFront(T* node)
	{
		if (node == nullptr)
		{
			return false;
		}

		node->next = m_head;
		m_head = node;

		return true;
	}

	bool AddLast(T* node)
	{
		if (node == nullptr)
		{
			return false;
		}

		Node<T>* temp = m_head;

		while(temp->next != nullptr)
		{
			temp = temp->next;
		}

		temp->next = node;

		return true;
	}

	Node<T>* GetAt(size_t index)
	{
		Node<T>* temp = m_head;
		int i = 0;

		for (; i < index || temp != nullptr;
			 ++i, temp = temp->GetNext());

		return temp;
	}

	bool RemoveFront()
	{
		if (m_head == nullptr)
		{
			return false;
		}

		m_head = m_head->next;

		return true;
	}

	~LinkedList() = default;
	
private:
	Node<T>* m_head = nullptr;
};