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
    int matrixDimensionSize = matrix.size();

    vector<vector<int>> left(matrixDimensionSize, vector<int>(matrixDimensionSize));
    vector<vector<int>> right(matrixDimensionSize, vector<int>(matrixDimensionSize));
    vector<vector<int>> top(matrixDimensionSize, vector<int>(matrixDimensionSize));
    vector<vector<int>> bottom(matrixDimensionSize, vector<int>(matrixDimensionSize));

    // initialize all four matrices
    for (int i = 0; i < matrixDimensionSize; i++) 
    { 
        // initialize first row of top 
        top[0][i] = matrix[0][i]; 
  
        // initialize last row of bottom 
        bottom[matrixDimensionSize - 1][i] = matrix[matrixDimensionSize - 1][i]; 
  
        // initialize first column of left 
        left[i][0] = matrix[i][0]; 
  
        // initialize last column of right 
        right[i][matrixDimensionSize - 1] = matrix[i][matrixDimensionSize - 1]; 
    } 
  
    // fill the indexes of all four matrices 
    for (int i = 0; i < matrixDimensionSize; i++) 
    { 
        for (int j = 1; j < matrixDimensionSize; j++) 
        { 
            // fill left matrix, from left to right 
            if (matrix[i][j] == 1)
            {
            	left[i][j] = left[i][j - 1] + 1; 
            }
            else
            {
                left[i][j] = 0; 
            }
  
            // fill top matrix 
            if (matrix[j][i] == 1)
            {
                top[j][i] = top[j - 1][i] + 1; 
            } 
            else
            {
                top[j][i] = 0; 
            }
  
            // use j from end to start to fill the value of bottom(i, j) and right(i, j)
            j = matrixDimensionSize - 1 - j; 
  
            // calculate bottom matrix 
            if (matrix[j][i] == 1)
            {
                bottom[j][i] = bottom[j + 1][i] + 1; 
            }
            else
            {
                bottom[j][i] = 0; 
            }
  
            // calculate right matrix 
            if (matrix[i][j] == 1) 
            {
                right[i][j] = right[i][j + 1] + 1; 
            }
            else
            {
                right[i][j] = 0; 
            }
  
            // revert back to old j 
            j = matrixDimensionSize - 1 - j; 
        } 
    } 
  
    int longestBranchLength = 0; 
  
    for (int i = 0; i < matrixDimensionSize; i++) 
    { 
        for (int j = 0; j < matrixDimensionSize; j++) 
        { 
            // find minimum of left(i, j), right(i, j), 
            // top(i, j), bottom(i, j) 
            int len = min(min(top[i][j], bottom[i][j]), 
                          min(left[i][j], right[i][j])); 
  
            // largest + would be formed by a cell that 
            // has maximum value 
            if(len > longestBranchLength)
            {
            	longestBranchLength = len;
                o_result.crossCenter.i = i;
				o_result.crossCenter.j = j;
				o_result.branchLength = len -1; 
            }
        } 
    }
}