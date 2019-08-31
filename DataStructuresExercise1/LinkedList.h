#pragma once

//A templatic node of the Linked List.
template <typename T>
class Node
{
public:
	//Constructor that sets initial value and next node.
	//If the next node won't be given, then the next will be default set to nullptr.
	explicit Node(T value, Node<T>* next = nullptr)
		: m_value(value), m_next(next)
	{}

	//Sets the next node pointer to next.
	bool SetNext(Node<T>* next)
	{
		if (next == nullptr)
		{
			return false;
		}

		m_next = next;
		return true;
	}

	//Returns the next node pointer.
	Node<T>* GetNext()
	{
		return m_next;
	}

	//Returns the templatic value of this node.
	T GetValue()
	{
		return m_value;
	}

	~Node() = default;
	
private:
	T m_value;
	Node<T>* m_next = nullptr;
};

//A LinkedList using the templatic node.
template <typename T>
class LinkedList
{
public:
	//A Constructor that initializes the linked list head node.
	LinkedList(Node<T>* head)
		: m_head(head)
	{}

	LinkedList() = default;


	//Adds a node to the front of the list.
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

	//Adds a node to the end of the list.
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

	//Gets the node at index "index" of the list. (from 0)
	Node<T>* GetAt(size_t index)
	{
		Node<T>* temp = m_head;
		int i = 0;

		for (; i < index && temp != nullptr;
			 ++i, temp = temp->GetNext());

		return temp;
	}

	//Removes the front node of the list and sets it's head to the second one.
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

	//Returns the size of the list (number of nodes).
	int GetSize()
	{
		return m_size;
	}

	~LinkedList() = default;
	
private:
	//Head of the list.
	Node<T>* m_head = nullptr;

	//A counter to save the list size.
	int m_size = 0;
};