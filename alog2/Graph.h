#pragma once

#include <vector>
#include "LinkedList.h"

template<typename T>
struct Vertex
{
	Vertex(T& n, std::vector<T> v)
		: value(n)
	{
		for (typename std::vector<T>::iterator i = v.begin(); i != v.end(); ++i)
		{
			adjList.AddLast(&*i);
		}
	}

	bool operator==(const Vertex<T>& rhs)
	{
		 return this->value == rhs.value;
	}

	T& GetValue() const
	{
		return value;
	}

	bool AddAdj(T& value)
	{
		return adjList.AddLast(&value);
	}

	std::vector<T> GetAllAdj()
	{
		std::vector<T> vectorAdj;
		size_t i = 0;
		bool continueLoop = true;

		do
		{
			Node<T>* val = adjList.GetAt(i);

			if (val == nullptr)
			{
				continueLoop = false;
				continue;
			}

			vectorAdj.push_back(val->GetValue());
			i++;

		} while (continueLoop);

		return vectorAdj;
	}

	T& value;
	LinkedList<T> adjList;
};

template<typename T>
class Graph
{
public:
	Graph() = default;

	Graph(Graph& graph)
		: m_elements(graph.GetElements()),
		  m_elementsCount(graph.GetElementsCount())
	{}

	LinkedList<Vertex<T>> GetElements() const
	{
		return m_elements;
	}

	// LinkedList<Vertex> GetAdjList() const
	// {
	// 	return m_elements.GetAdj();
	// }

	size_t GetElementsCount() const
	{
		return m_elementsCount;
	}

	bool AddVertex(Vertex<T>& element, std::vector<T>& fathers)
	{
		if (!m_elements.AddLast(&element))
		{
			return false;
		}
		
		for (typename std::vector<T>::iterator it = fathers.begin(); it != fathers.end(); ++it)
		{
			for (int i = 0; i < m_elementsCount; ++i)
			{
				Node<Vertex<T>>* elementsIterator = m_elements.GetAt(i);

				if (elementsIterator == nullptr)
				{
					break;
				}

				if (elementsIterator->GetValue().GetValue() == *it)
				{
					if (!elementsIterator->GetValue().AddAdj(element.GetValue()))
					{
						return false;
					}
				}
			}
		}
		
		m_elementsCount++;
		return true;
	}



	~Graph() = default;

private:
	LinkedList<Vertex<T>> m_elements;
	// LinkedList<T> m_adjList;

	size_t m_elementsCount = 0;
	
};