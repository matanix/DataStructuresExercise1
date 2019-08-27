#include "Game.h"
#include <ctime>
#include <stdlib.h>
#include <iostream>

#define POSSIBLE_TURNS_COUNT 6

using namespace std;

Game::Game(Stack<int>& firstTower, Stack<int>& secondTower, Stack<int>& thirdTower) :
	m_firstTower(firstTower), m_secondTower(secondTower), m_thirdTower(thirdTower) 
{
	srand(time(NULL));
}

void Game::Play()
{
	bool isPlayerTurn = doIStart();
	if (isPlayerTurn)
	{
		cout << "Player decides to start\n";
	}
	else
	{
		cout << "Player decides that computer starts\n";
	}

	while (!isGameEnd())
	{
		bool removeFromFirst = false;
		bool removeFromSecond = false;
		bool removeFromThird = false;
		getTurn(isPlayerTurn, removeFromFirst, removeFromSecond, removeFromThird);

		if (executeTurn(isPlayerTurn, removeFromFirst, removeFromSecond, removeFromThird) == false)
		{
			cout << "Error. Exiting game.\n";
			return;
		}

		isPlayerTurn = !isPlayerTurn;
	}
	
	if (isPlayerTurn)
	{
		cout << "Computer won\n";
	}
	else
	{
		cout << "Player won\n";
	}
}

bool Game::isWinningStateForMe(int firstTowerSize, int secondTowerSize, int thirdTowerSize)
{
	int firstDiff = firstTowerSize - secondTowerSize;
	int secondDiff = secondTowerSize - thirdTowerSize;

	if ((firstDiff % 2 == 0) && (secondDiff % 2 == 0))
	{
		return true;
	}

	return false;
}

void Game::getTurn(bool isPlayer, bool& removeFromFirst, bool& removeFromSecond, bool& removeFromThird)
{
	int possibleTurns[][POSSIBLE_TURNS_COUNT] = { {true,true,false},
												  {true,false,true},
	                                              {false,true,true},
	                                              {true,false,false},
	                                              {false,true,false},
	                                              {false,false,true} };

	bool isTurnLegal[POSSIBLE_TURNS_COUNT] = { false, false, false, false, false, false };

	for (int i = 0; i < POSSIBLE_TURNS_COUNT; i++)
	{
		if (isLegalTurn(possibleTurns[i][0], possibleTurns[i][1], possibleTurns[i][2]))
		{
			isTurnLegal[i] = true;
		}
	}

	if (isPlayer)
	{
		for (int i = 0; i < POSSIBLE_TURNS_COUNT; i++)
		{
			if (isTurnLegal[i] == true)
			{
				if (isWinningStateForMe(m_firstTower.GetSize() - possibleTurns[i][0],
					m_secondTower.GetSize() - possibleTurns[i][1],
					m_thirdTower.GetSize() - possibleTurns[i][2]))
				{
					removeFromFirst = possibleTurns[i][0];
					removeFromSecond = possibleTurns[i][1];
					removeFromThird = possibleTurns[i][2];
					return;
				}
			}
		}
	}
	else
	{
		int randomTurnMap[POSSIBLE_TURNS_COUNT] = { 0 };
		int mappedTurnIndex = 0;

		for (int i = 0; i < POSSIBLE_TURNS_COUNT; i++)
		{
			if (isTurnLegal[i])
			{
				randomTurnMap[mappedTurnIndex] = i;
				mappedTurnIndex++;
			}
		}
	
		int randTurn = getRand(mappedTurnIndex);
		int selectedTurnIndex = randomTurnMap[randTurn];

		removeFromFirst = possibleTurns[selectedTurnIndex][0];
		removeFromSecond = possibleTurns[selectedTurnIndex][1];
		removeFromThird = possibleTurns[selectedTurnIndex][2];
		return;
	}
}

int Game::getRand(int maxNum)
{
	return rand() % maxNum;
}

bool Game::doIStart()
{
	return !isWinningStateForMe(m_firstTower.GetSize(), m_secondTower.GetSize(), m_thirdTower.GetSize());
}

bool Game::isGameEnd()
{
	return (m_firstTower.GetSize() == 0 && m_secondTower.GetSize() == 0 && m_thirdTower.GetSize() == 0);
}

bool Game::isLegalTurn(bool removeFromFirst, bool removeFromSecond, bool removeFromThird)
{
	if (removeFromFirst && removeFromSecond && removeFromThird)
	{
		return false;
	}

	if (m_firstTower.GetSize() < 1 && removeFromFirst)
	{
		return false;
	}

	if (m_secondTower.GetSize() < 1 && removeFromSecond)
	{
		return false;
	}

	if (m_thirdTower.GetSize() < 1 && removeFromThird)
	{
		return false;
	}

	return true;
}

bool Game::executeTurn(bool isPlayer, bool removeFromFirst, bool removeFromSecond, bool removeFromThird)
{
	if (isPlayer)
	{
		cout << "Player turn:\n";
	}
	else
	{
		cout << "Computer turn:\n";
	}

	int cubeNum = 0;

	if (removeFromFirst)
	{
		if (m_firstTower.Pop(cubeNum) == false)
		{
			return false;
		}

		cout << "Removed cube " << cubeNum << " from first tower\n";
	}
	if (removeFromSecond)
	{
		if (m_secondTower.Pop(cubeNum) == false)
		{
			return false;
		}

		cout << "Removed cube " << cubeNum << " from second tower\n";
	}
	if (removeFromThird)
	{
		if (m_thirdTower.Pop(cubeNum) == false)
		{
			return false;
		}

		cout << "Removed cube " << cubeNum << " from third tower\n";
	}

	cout << "\n";

	return true;
}
