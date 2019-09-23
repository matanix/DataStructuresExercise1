#include <iostream>
#include "AuctionHeap.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

static constexpr unsigned int MAX_AUCTION_HEAP_SIZE = 20;

using namespace std;

int main(int argc, char const *argv[])
{
	srand(static_cast<unsigned int>(time(nullptr)));
	AuctionHeap<MAX_AUCTION_HEAP_SIZE> auctionHeap;
	
	for (int i = 0; i < MAX_AUCTION_HEAP_SIZE / 2; i++)
	{
		unsigned int randVal = rand() % 100 + 1;
		auctionHeap.Insert(randVal);
		cout << "Inserted " << randVal << " \n";
	}

	unsigned int resultVal = 0;
	auctionHeap.GetMax(resultVal);

	cout << "Max is " << resultVal << " \n" ;

	for (int place = 1; place <= MAX_AUCTION_HEAP_SIZE / 2; place++)
	{
		auctionHeap.GetBidByPlace(place, resultVal);

		cout << "Val at place " << place << " is " << resultVal << " \n";
	}

	for (int i = 0; i < MAX_AUCTION_HEAP_SIZE; i++)
	{
		unsigned int randVal = rand() % 100 + 1;
		auctionHeap.Insert(randVal);
		cout << "Inserted " << randVal << " \n";
	}

	resultVal = 0;
	auctionHeap.GetMax(resultVal);

	cout << "Max is " << resultVal << " \n" ;

	for (int place = 1; place <= MAX_AUCTION_HEAP_SIZE; place++)
	{
		auctionHeap.GetBidByPlace(place, resultVal);

		cout << "Val at place " << place << " is " << resultVal << " \n";
	}

	return 0;
}