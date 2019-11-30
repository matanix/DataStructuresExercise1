#pragma once

template <typename T>
class Node
{
public:
	explicit Node(T& value)
		: m_value(value)
	{}

	T& operator=(const T& other) // copy assignment
	{
		m_value = other.GetValue();
		m_next = other.GetNext();
		return *this;
	}

	bool SetNext(T* next)
	{
		if (next == nullptr)
		{
			return false;
		}

		Node<T>* nextNode = new Node<T>(*next);

		if (nextNode == nullptr)
		{
			return false;
		}

		m_next = nextNode;
		return true;
	}

	Node<T>* GetNext()
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
	Node<T>* m_next = nullptr;
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

		Node<T>* temp = new Node<T>(*node);

		if (!temp->SetNext(m_head))
		{
			return false;
		}

		m_head = temp;

		return true;
	}

	bool AddLast(T* node)
	{
		if (node == nullptr)
		{
			return false;
		}

		if (m_head == nullptr)
		{
			m_head = new Node<T>(*node);
			return true;
		}

		Node<T>* temp = m_head;

		while(temp->GetNext() != nullptr)
		{
			temp = temp->GetNext();
		}

		temp->SetNext(node);

		return true;
	}

	Node<T>* GetAt(size_t index)
	{
		Node<T>* temp = m_head;
		int i = 0;

		for (; i < index && temp != nullptr; ++i, temp = temp->GetNext())
		{
			if (temp == nullptr)
			{
				return temp;
			}
		}

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