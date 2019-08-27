#pragma once
#include "Stack.h"

class Game
{
public:
	Game(Stack<int>& firstTower, Stack<int>& secondTower, Stack<int>& thirdTower);

	void Play();

private:
	bool doIStart();
	bool isWinningStateForMe(int firstTowerSize, int secondTowerSize, int thirdTowerSize);
	bool isGameEnd();
	bool isLegalTurn(bool removeFromFirst, bool removeFromSecond, bool removeFromThird);
	bool executeTurn(bool isPlayer, bool removeFromFirst, bool removeFromSecond, bool removeFromThird);
	void getTurn(bool isPlayer, bool& removeFromFirst, bool& removeFromSecond, bool& removeFromThird);
	int getRand(int maxNum);

private:
	Stack<int>& m_firstTower;
	Stack<int>& m_secondTower;
	Stack<int>& m_thirdTower;

};