#pragma once

template <typename T>
class Node
{
public:
	explicit Node(T value, Node<T>* next = nullptr)
		: m_value(value), m_next(next)
	{}

	bool SetNext(Node<T>* next)
	{
		if (next == nullptr)
		{
			return false;
		}

		m_next = next;
		return true;
	}

	Node<T>* GetNext()
	{
		return m_next;
	}

	T GetValue()
	{
		return m_value;
	}

	~Node() = default;
	
private:

	T m_value;
	Node<T>* m_next = nullptr;
};

template <typename T>
class LinkedList
{
public:
	LinkedList(Node<T>* head)
		: m_head(head)
	{}

	LinkedList() = default;

	bool AddFront(Node<T>* node)
	{
		if (node == nullptr)
		{
			return false;
		}

		node->SetNext(m_head);
		m_head = node;
		m_size++;

		return true;
	}

	bool AddLast(Node<T>* node)
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

		temp->SetNext(node);
		m_size++;

		return true;
	}

	Node<T>* GetAt(size_t index)
	{
		Node<T>* temp = m_head;
		int i = 0;

		for (; i < index && temp != nullptr;
			 ++i, temp = temp->GetNext());

		return temp;
	}

	bool RemoveFront()
	{
		if (m_head == nullptr)
		{
			return false;
		}

		m_head = m_head->GetNext();
		m_size--;

		return true;
	}

	int GetSize()
	{
		return m_size;
	}

	~LinkedList() = default;
	
private:
	Node<T>* m_head = nullptr;
	int m_size = 0;
};