#include <iostream>
#include "Game.h"

using namespace std;

/**
 * This function gets the 3 towers heights from the user into k,m,n out parameters.
 **/
void GetInput(int& k, int& m, int& n)
{
	cout << "Enter height of the first tower: k\n";
	cin >> k;
	cout << "Enter height of the second tower: m\n";
	cin >> m;
	cout << "Enter height of the third tower: n\n";
	cin >> n;
}

/**
 * This function builds a stack of integers filled with numbers from 1 to its size.
 * The stack built is the out parameter.
 **/
bool BuildStack(Stack<int>& stackToBuild, int size)
{
	for (int i = 1; i <= size; i++)
	{
		if (stackToBuild.Push(i) == false)
		{
			return false;
		}
	}

	return true;
}

int main(int argc, char const *argv[])
{
	int k, m, n = 0;

	//Get input from user
	GetInput(k, m, n);

	//If all sizes are 0, we cannot play, so exit.
	if (k == 0 && m == 0 && n == 0)
	{
		cout << "Must have at least 1 cube to play with";
		return -1;
	}

	//If any of the input numbers are negative the input is invalid.
	if (k < 0 || m < 0 || n < 0)
	{
		cout << "Negative values aren't legal";
		return -1;
	}


	//Build the three towers as stacks.
	Stack<int> firstTower;
	Stack<int> secondTower;
	Stack<int> thirdTower;

	if (BuildStack(firstTower, k) == false)
	{
		cout << "Failed to allocate and build first stack. Exiting\n";
		return -1;
	}

	if (BuildStack(secondTower, m) == false)
	{
		cout << "Failed to allocate and build second stack. Exiting\n";
		return -1;
	}

	if (BuildStack(thirdTower, n) == false)
	{
		cout << "Failed to allocate and build third stack. Exiting\n";
		return -1;
	}

	//Create a game object with the three towers and start to play.
	Game game(firstTower, secondTower, thirdTower);
	game.Play();

	return 0;
}