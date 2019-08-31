#include "Game.h"
#include <ctime>
#include <stdlib.h>
#include <iostream>

//Count of maximum possible turns in the game.
#define POSSIBLE_TURNS_COUNT 6

using namespace std;

Game::Game(Stack<int>& firstTower, Stack<int>& secondTower, Stack<int>& thirdTower) :
	m_firstTower(firstTower), m_secondTower(secondTower), m_thirdTower(thirdTower) 
{
	//Initialize random with time seed.
	srand(time(NULL));
}

void Game::Play()
{
	//Check wether the player should choose to start.
	bool isPlayerTurn = doIStart();

	//Print if the player starts or the computer.
	if (isPlayerTurn)
	{
		cout << "Player decides to start\n";
	}
	else
	{
		cout << "Player decides that computer starts\n";
	}

	//Calculate and execute turns until game ends.
	while (!isGameEnd())
	{
		//Get the turn action.
		//If we are in a player turn, the function will calculate the best action.
		//If we are in a computer turn, the function will return a random valid action.
		bool removeFromFirst = false;
		bool removeFromSecond = false;
		bool removeFromThird = false;
		getTurn(isPlayerTurn, removeFromFirst, removeFromSecond, removeFromThird);

		//Execute the calculated turn and print it's info.
		if (executeTurn(isPlayerTurn, removeFromFirst, removeFromSecond, removeFromThird) == false)
		{
			cout << "Error. Exiting game.\n";
			return;
		}

		//Swap between player and computer.
		isPlayerTurn = !isPlayerTurn;
	}
	
	//Print who won (Player always wins)
	//If the game ended and it's the player turn, the computer won
	//If the game ended and it's the computer turn, the player won
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
	//Calculate differences between all towers
	int firstDiff = firstTowerSize - secondTowerSize;
	int secondDiff = secondTowerSize - thirdTowerSize;

	//If all differences are even, this is a winning state for the player.
	if ((firstDiff % 2 == 0) && (secondDiff % 2 == 0))
	{
		return true;
	}

	return false;
}

void Game::getTurn(bool isPlayer, bool& removeFromFirst, bool& removeFromSecond, bool& removeFromThird)
{
	//This array represents all valid possible turns with booleans 
	//That represent removing a cube from tower 
	//For example, {true, true, false} means removing from tower 1 and 2, and not removing from tower 3.
	int possibleTurns[][POSSIBLE_TURNS_COUNT] = { {true,true,false},
												  {true,false,true},
	                                              {false,true,true},
	                                              {true,false,false},
	                                              {false,true,false},
	                                              {false,false,true} };

	//An array to save which turns are legal from possible turns in the current state.
	bool isTurnLegal[POSSIBLE_TURNS_COUNT] = { false, false, false, false, false, false };

	//Check which possible turns are legal now.
	for (int i = 0; i < POSSIBLE_TURNS_COUNT; i++)
	{
		if (isLegalTurn(possibleTurns[i][0], possibleTurns[i][1], possibleTurns[i][2]))
		{
			isTurnLegal[i] = true;
		}
	}

	//If it's a player turn,
	//Check which possible turn gives a winning state and return it.
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
	//Else get a random valid turn for the computer
	else
	{
		//This will be filled with indexes of valid actions for the computer (of the possible turn array)
		int randomTurnMap[POSSIBLE_TURNS_COUNT] = { 0 };
		int mappedTurnIndex = 0;

		//For each legal turn map it to the randomTurnMap.
		for (int i = 0; i < POSSIBLE_TURNS_COUNT; i++)
		{
			if (isTurnLegal[i])
			{
				randomTurnMap[mappedTurnIndex] = i;
				mappedTurnIndex++;
			}
		}
	
		//Select a random index of the randomTurnMap.
		int randTurn = getRand(mappedTurnIndex);
		
		//Get the matching possibleTurns index.
		int selectedTurnIndex = randomTurnMap[randTurn];

		//Return the random turn 
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
	//If the current state ensures victory, the Player doesn't start.
	//If the current state doesn't ensure victory, the Player has to start in order to make it ensure victory.
	return !isWinningStateForMe(m_firstTower.GetSize(), m_secondTower.GetSize(), m_thirdTower.GetSize());
}

bool Game::isGameEnd()
{
	//If all towers are empty the game has ended.
	return (m_firstTower.GetSize() == 0 && m_secondTower.GetSize() == 0 && m_thirdTower.GetSize() == 0);
}

bool Game::isLegalTurn(bool removeFromFirst, bool removeFromSecond, bool removeFromThird)
{
	//Must remove at least one cube.
	if (removeFromFirst && removeFromSecond && removeFromThird)
	{
		return false;
	}

	//Check if trying to remove from an empty tower.
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

	//All checks passed, return valid.
	return true;
}

bool Game::executeTurn(bool isPlayer, bool removeFromFirst, bool removeFromSecond, bool removeFromThird)
{
	//Print who's turn this is.
	if (isPlayer)
	{
		cout << "Player turn:\n";
	}
	else
	{
		cout << "Computer turn:\n";
	}

	int cubeNum = 0;
	
	//Remove 1 cube from the requested towers and print which cube num was removed.
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
