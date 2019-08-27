#include <iostream>
#include "Game.h"

using namespace std;

void GetInput(int& k, int& m, int& n)
{
	cout << "Enter height of the first tower: k\n";
	cin >> k;
	cout << "Enter height of the second tower: m\n";
	cin >> m;
	cout << "Enter height of the third tower: n\n";
	cin >> n;
}

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
	GetInput(k, m, n);

	if (k == 0 && m == 0 && n == 0)
	{
		cout << "Must have at least 1 cube to play with";
		return -1;
	}

	if (k < 0 || m < 0 || n < 0)
	{
		cout << "Negative values aren't legal";
		return -1;
	}


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

	Game game(firstTower, secondTower, thirdTower);
	game.Play();

	return 0;
}