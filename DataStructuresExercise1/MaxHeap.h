#pragma once

#include <iostream>

using namespace std;


struct node
{
	unsigned int value;
	unsigned int index;
};

//A templatic max heap 
template <unsigned int MAX_SIZE>
class MaxHeap
{
public:
	static constexpr unsigned int ROOT = 0;
	static constexpr unsigned int EMPTY = 0;

	//Constructor that initializes the heap inner array.
	explicit MaxHeap() : m_size(0)
	{}

	bool Insert(unsigned int value, unsigned int index = 0)
	{
		if (m_size == MAX_SIZE)
		{
			return false;
		}
		
		m_nodes[m_size].value = value;
		m_nodes[m_size].index = index;
		bubbleUp(m_size);

		m_size++;

		return true;
	}

	bool GetMax(unsigned int& o_value)
	{
		if (IsEmpty())
		{
			return false;
		}

		o_value = m_nodes[ROOT].value;

		return true;
	}

	bool Extract(unsigned int& o_value, unsigned int& o_index)
	{
		if (IsEmpty())
		{
			return false;
		}

		o_value = m_nodes[ROOT].value;
		o_index = m_nodes[ROOT].index;
		m_nodes[ROOT] = m_nodes[m_size - 1];
		m_size--;

		heapify(ROOT);

		return true;
	}

	bool GetLeftSonOf(unsigned int index, unsigned int& o_val, unsigned int& o_index)
	{
		if (getLeftSonIndex(index) >= m_size)
		{
			return false;
		}

		o_val = m_nodes[getLeftSonIndex(index)].value;
		o_index = getLeftSonIndex(index);

		return true;
	}

	bool GetRightSonOf(unsigned int index, unsigned int& o_val, unsigned int& o_index)
	{
		if (getRightSonIndex(index) >= m_size)
		{
			return false;
		}

		o_val = m_nodes[getRightSonIndex(index)].value;
		o_index = getRightSonIndex(index);

		return true;
	}

	bool IsEmpty()
	{
		return (m_size == EMPTY);
	}

	unsigned int GetSize()
	{
		return m_size;
	}

	void Clear()
	{
		m_size = 0;
	}

	~MaxHeap() = default;


private:

	void bubbleUp(unsigned int index)
	{
		for (int i = index; i > ROOT; i /= 2)
		{
			if (m_nodes[i].value >= (m_nodes[getParentIndex(i)].value))
			{
				swap(i, getParentIndex(i));
			}
			else
			{
				break;
			}
		}
	}

	void heapify(unsigned int index)
	{
		unsigned int leftSonIndex = getLeftSonIndex(index);
		unsigned int rightSonIndex = getRightSonIndex(index);
		unsigned int largestIndex = index;

		if (isIndexInHeap(leftSonIndex) && (m_nodes[leftSonIndex].value > m_nodes[largestIndex].value))
		{
			largestIndex = leftSonIndex;
		}

		if (isIndexInHeap(rightSonIndex) && (m_nodes[rightSonIndex].value > m_nodes[largestIndex].value))
		{
			largestIndex = rightSonIndex;
		}

		if (largestIndex != index)
		{
			swap(index, largestIndex);
			heapify(largestIndex);
		}
	}

	void swap(unsigned int index1, unsigned int index2)
	{
		node tempNode;
		memcpy(&tempNode, &m_nodes[index1], sizeof(node));
		memcpy(&m_nodes[index1], &m_nodes[index2], sizeof(node));
		memcpy(&m_nodes[index2], &tempNode, sizeof(node));
	}

	unsigned int getParentIndex(unsigned int childIndex)
	{
		return (childIndex / 2);
	}

	unsigned int getLeftSonIndex(unsigned int parentIndex)
	{
		return ((parentIndex * 2) + 1);
	}

	unsigned int getRightSonIndex(unsigned int parentIndex)
	{
		return ((parentIndex * 2) + 2);
	}

	bool isIndexInHeap(unsigned int index)
	{
		return (index < m_size);
	}
	
private:
	node m_nodes[MAX_SIZE];
	unsigned int m_size;
};
