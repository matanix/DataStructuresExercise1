#include <iostream>
#include "BigCrossFinder.h"
#include <ctime>
using namespace std;

/* Sizes and matrixes */
constexpr int CONSTANT_TEST_MATRIX_SIZE = 15;
constexpr int RANDOM_TEST_MATRIX_SIZE = 50;

void PrintMatrix(const vector<vector<int>>& matrix)
{
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			cout << matrix[i][j] << ' ';
		}
		cout << '\n';
	}
}

int GenerateBinary()
{
	return rand() % 2;
}

void GetRandomMatrix(vector<vector<int>>& matrix)
{
	//Initialize SRAND with time seed
	srand(time(NULL));

	//Fill the matrix with random values;
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			matrix[i][j] = GenerateBinary();
		}
	}
}

void PrintResult(const BigCrossResult &bigCrossResult)
{
	cout << "\nRESULT: \n";
	if (bigCrossResult.crossCenter.i == -1)
	{
		cout << "There are no crosses at all";
	}
	else
	{
		cout << "The biggest cross is at: (" << (bigCrossResult.crossCenter.i + 1) << ","
											 << (bigCrossResult.crossCenter.j + 1) << ") \n";

		cout << "It's branch length is: " << bigCrossResult.branchLength << '\n';
	}
	
	cout << '\n';
	cout << "--------------------------------------- " << '\n';
	cout << "--------------------------------------- ";
	cout << "\n\n";
}

int main()
{
	//15x15 Matrix
	const vector<vector<int>> constMatrix = {{1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1},
											 {0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1},
											 {1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0},
											 {1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0},
											 {0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1},
											 {1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1},
											 {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
											 {1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1},
											 {0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0},
											 {1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0},
											 {1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1},
											 {1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0},
											 {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
											 {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
											 {1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1}};

	//50x50 Random matrix
	vector<vector<int>> randomMatrix(RANDOM_TEST_MATRIX_SIZE, vector<int>(RANDOM_TEST_MATRIX_SIZE));
	GetRandomMatrix(randomMatrix);
	
	BigCrossFinder bigCrossFinder;
	BigCrossResult result;

	//Use BigCross1 on both matrixes.
	cout << "Finding biggest cross using BigCross1 on the following constant matrix:\n";
	PrintMatrix(constMatrix);
	bigCrossFinder.BigCross1(constMatrix, result);
	PrintResult(result);

	cout << "Finding biggest cross using BigCross1 on the following random matrix:\n";
	PrintMatrix(randomMatrix);
	bigCrossFinder.BigCross1(randomMatrix, result);
	PrintResult(result);

	//Use BigCross2 on both matrixes.
	cout << "Finding the biggest cross using BigCross2 on the following constant matrix:\n";
	PrintMatrix(constMatrix);
	bigCrossFinder.BigCross2(constMatrix, result);
	PrintResult(result);

	cout << "Finding biggest cross using BigCross2 on the following random matrix:\n";
	PrintMatrix(randomMatrix);
	bigCrossFinder.BigCross2(randomMatrix, result);
	PrintResult(result);

	return 1;
}