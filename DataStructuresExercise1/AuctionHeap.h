#pragma once

#include "MaxHeap.h"

//A templatic AuctionHeap
//Supports insert at O(n) (using max heap)
//Supports GetMax at O(1) (using max heap)
//Supports GetBidByPlace (place k) at O(klog(k)) (using two max heaps)
template <unsigned int MAX_SIZE>
class AuctionHeap
{
public:
	AuctionHeap() = default;
	~AuctionHeap() = default;

	static constexpr unsigned int MIN_PLACE = 1;

	bool Insert(unsigned int value)
	{
		return m_bids.Insert(value);
	}

	bool GetMax(unsigned int& o_value)
	{
		return m_bids.GetMax(o_value);
	}

	bool Extract(unsigned int& o_value)
	{
		unsigned int unused;
		return m_bids.Extract(o_value, unused);
	}

	//This method is of order O(klog(k)) when place = k, since we do 2k inserts into a heap which it's size
	//is at max 2k it takes O(klog(k)), as well as 2k extracts from it O(klog(k)).
	//We access the sons by indexes in the actual heap in O(1) using GetLeftSonOf and GetRightSonOf k times
	//The result is 4k log(k) + k = klog(k)
	bool GetBidByPlace(unsigned int place, unsigned int& o_value)
	{
		if (place < MIN_PLACE)
		{
			return false;
		}

		if (place > m_bids.GetSize())
		{
			return false;
		}

		unsigned int tempVal = 0;
		unsigned int rootIndex = 0;
		unsigned int maxVal = 0;
		unsigned int sonIndex = 0;

		m_bids.GetMax(maxVal);

		m_tempBids.Insert(maxVal, MaxHeap<MAX_SIZE>::ROOT);

		//Runs K-1 times
		for (unsigned int i = 0; i < place - 1; i++)
		{
			m_tempBids.Extract(tempVal, rootIndex);
	
			if (m_bids.GetLeftSonOf(rootIndex, tempVal, sonIndex))
			{
				m_tempBids.Insert(tempVal, sonIndex);
			}

			if (m_bids.GetRightSonOf(rootIndex, tempVal, sonIndex))
			{
				m_tempBids.Insert(tempVal, sonIndex);
			}
		}

		m_tempBids.GetMax(o_value);

		m_tempBids.Clear();

		return true;
	}


	unsigned int GetSize()
	{
		return m_bids.GetSize();
	}

private:
	MaxHeap<MAX_SIZE> m_bids;
	MaxHeap<MAX_SIZE> m_tempBids;
};