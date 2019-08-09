#include "BigCrossFinder.h"
#include <algorithm>

using namespace std;

/** BigCross1 - Finds the center and branch length of the biggest cross
Time efficiency: O(m^3) = O(n^1.5)
No use of data structure **/
void BigCrossFinder::BigCross1(const vector<vector<int>>& matrix, BigCrossResult &o_result)
{
	int matrixDimensionSize = matrix.size();

	//Initialize the result and use it to keep track of the biggest cross data.
	//Use -1 so if we won't find any cross we will know that there are no crosses.
	o_result.crossCenter.i = -1;
	o_result.crossCenter.j = -1;
	o_result.branchLength = -1;
	
	for (int i = 0; i < matrixDimensionSize; i++)
	{
		//Iterate through all points
		for (int j = 0; j < matrixDimensionSize; j++)
		{
			//If the point itself isn't 1 then this isn't a cross.
			if (matrix[i][j] != 1)
			{
				continue;
			}

			//Calculate all max branch lengths from each side of the point
			int maxLeftOnes = 0, maxRightOnes = 0, maxUpOnes = 0, maxDownOnes = 0;

			for (int leftPtr = j - 1; leftPtr >= 0; leftPtr--)
			{
				if (matrix[i][leftPtr] == 1)
				{
					maxLeftOnes++;
				}
				else
				{
					break;
				}
			}

			for (int rightPtr = j + 1; rightPtr < matrixDimensionSize; rightPtr++)
			{
				if (matrix[i][rightPtr] == 1)
				{
					maxRightOnes++;
				}
				else
				{
					break;
				}
			}

			for (int upPtr = i - 1; upPtr >= 0; upPtr--)
			{
				if (matrix[upPtr][j] == 1)
				{
					maxUpOnes++;
				}
				else
				{
					break;
				}
			}

			for (int downPtr = i + 1; downPtr < matrixDimensionSize; downPtr++)
			{
				if (matrix[downPtr][j] == 1)
				{
					maxDownOnes++;
				}
				else
				{
					break;
				}
			}

			//The minimum of all maximum branch lengths of the point is it's cross branch length.
			int branchLength = min(min(min(maxRightOnes, maxLeftOnes), maxUpOnes), maxDownOnes);

			//If the branch length is bigger than the current one, save this point as the biggest cross.
			if (branchLength > o_result.branchLength)
			{
				o_result.crossCenter.i = i;
				o_result.crossCenter.j = j;
				o_result.branchLength = branchLength;
			}
		}
	}
}

/** BigCross 2 - Find the center and branch length of the biggest cross
Time efficiency: O(m^2) = O(n)
Use of data structure with size n^2 **/
void BigCrossFinder::BigCross2(const vector<vector<int>>& matrix, BigCrossResult &o_result)
{
}