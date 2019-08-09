#pragma once
#include <iostream>
#include <vector>

struct Point
{
	int i;
	int j;
};

struct BigCrossResult
{
	Point crossCenter;
	int branchLength;
};

class BigCrossFinder
{
public:
	BigCrossFinder() {}
	~BigCrossFinder() {}

	/** BigCross1 - Finds the center and branch length of the biggest cross
	Time efficiency: O(m^3) = O(n^1.5)
	No use of data structure **/
	void BigCross1(const std::vector<std::vector<int>> &matrix, BigCrossResult &o_result);

	/** BigCross 2 - Find the center and branch length of the biggest cross
	Time efficiency: O(m^2) = O(n)
	Use of data structure with size n^2 **/
	void BigCross2(const std::vector<std::vector<int>> &matrix, BigCrossResult &o_result);
};
