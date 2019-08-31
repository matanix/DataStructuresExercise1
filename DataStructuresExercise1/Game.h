#pragma once
#include "Stack.h"

/**
 * The Game class is constructed with three game towers 
 * And encapsulates the virtual game between the player and the computer with the public "Play" method
 * Using the Play method will start a virtual game between algorithmic always-winning virtual player
 * And a random decision computer.
 **/
class Game
{
public:
	/**
	 * Creates a game object using three initialized game towers.
	 * Each tower is a stack filled with integers from 1 to it's size.
	 **/
	Game(Stack<int>& firstTower, Stack<int>& secondTower, Stack<int>& thirdTower);

	/**
	 * This method will start a virtual game between the algoritmic player and random decisions computer.
	 * It will print wether the virtual player decided to start or let the computer start,
	 * And then go through each turn.
	 * If the turn is of the player, the player will calculate the step to victory.
	 * If the turn is of the computer, the computer will randomly pick a valid turn execution.
	 * The method will continue printing the game info until victory of the player.
	 */
	void Play();

private:
	/**
	 *  doIStart is called at the beggining of Play and uses the private towers sizes
	 *  To calculate wether the player should start in order to win or the computer.
	 *  It returns true if the player should choose to start, else false.
	 **/
	bool doIStart();

	/**
	 * isWinningStateForMe is a function that takes 3 tower sizes
	 * And returns true if finishing the player turn with these sizes
	 * will grant him ensured victory, else false.
	 **/
	bool isWinningStateForMe(int firstTowerSize, int secondTowerSize, int thirdTowerSize);

	/**
	 * isGameEnd checks wether all towers have no cubes left,
	 * which means the game ended.
	 * Returns true if the game ended, else false.
	 **/
	bool isGameEnd();

	/**
	 * isLegalTurn gets a boolean for each tower removal.
	 * if the removals requested are allowed in the current state of the towers,
	 * it returns True, else False.
	 **/
	bool isLegalTurn(bool removeFromFirst, bool removeFromSecond, bool removeFromThird);

	/**
	 * executeTurn receives a boolean that says wether this turn is a player or computer turn.
	 * it uses 3 booleans that say wether to remove from each one of the three towers.
	 * When called, it will remove cubes from towers according to the parameters
	 * And print the turn execution info to output.
	 **/
	bool executeTurn(bool isPlayer, bool removeFromFirst, bool removeFromSecond, bool removeFromThird);

	/**
	 * getTurn receives a boolean that says wether this turn is a player or computer turn.
	 * if isPlayer = True, then this is a player turn, and getTurn will return what should the player do
	 * to ensure victory (Which towers should he remove a cube from).
	 * If isPlayer = False, then this is a computer turn, and getTurn will return a random valid turn option
	 * For the computer to execute.
	 **/
	void getTurn(bool isPlayer, bool& removeFromFirst, bool& removeFromSecond, bool& removeFromThird);

	/**
	 * getRand returns a random number from 0 to maxNum.
	 **/
	int getRand(int maxNum);

private:
	Stack<int>& m_firstTower;
	Stack<int>& m_secondTower;
	Stack<int>& m_thirdTower;

};