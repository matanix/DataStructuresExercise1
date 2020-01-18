#include "LevenshteinDistance.h"
#include "string.h"
#include <algorithm>

int LevenshteinDistance::recursive(const char* start,const char* end)
{
	int startLen = int(strlen(start));
	int endLen = int(strlen(end));
	return innerRecursive(start, startLen, end, endLen);
}

int LevenshteinDistance::innerRecursive(const char* start, int startLen, const char* end, int endLen)
{
	//if we reached end of start string, we need to add all remaining end characters;
	if (startLen == 0)
	{
		return endLen;
	}

	//if we reached end of end string, we need to remove all remaining start characters;
	if (endLen == 0)
	{
		return startLen;
	}

	//Return minimum of insert, remove, replace.
	return std::min<int>(std::min<int>(innerRecursive(start, startLen - 1, end, endLen - 1) + (start[startLen - 1] != end[endLen - 1]), // replace or proceed if equal
						innerRecursive(start, startLen - 1, end, endLen) + 1), //remove
						innerRecursive(start, startLen, end, endLen - 1) + 1); //insert
}


int LevenshteinDistance::dynamic(const char* start, const char* end)
{
	int startLen = int(strlen(start));
	int endLen = int(strlen(end));
	int matrix[MAX_SIZE][MAX_SIZE];
	memset(matrix, -1, sizeof(matrix));
	return innerDynamic(start, startLen, end, endLen, matrix);
}

int LevenshteinDistance::innerDynamic(const char* start, int startLen, const char* end, int endLen, int matrix[][MAX_SIZE])
{
	if (startLen == 0)
	{
		return endLen;
	}

	if (endLen == 0)
	{
		return startLen;
	}

	//Use memory if already calculated
	if (matrix[startLen - 1][endLen - 1] != -1)
	{
		return matrix[startLen - 1][endLen - 1];
	}

	//If equal, return the value by removing both and save it.
	if (start[startLen - 1] == end[endLen - 1])
	{
		matrix[startLen - 1][endLen - 1] = innerDynamic(start, startLen - 1, end, endLen - 1, matrix);
		return matrix[startLen - 1][endLen - 1];
	}

	//else save and return minimum of insert / remove / replace.
	matrix[startLen - 1][endLen - 1] =
		1 + std::min<int>(std::min<int>(innerDynamic(start, startLen, end, endLen - 1, matrix), //Insert
			innerDynamic(start, startLen - 1, end, endLen, matrix)), //Remove
			innerDynamic(start, startLen - 1, end, endLen - 1, matrix)); //Replace
	return matrix[startLen - 1][endLen - 1];
}

int LevenshteinDistance::iterative(const char* start, const char* end)
{
	return 0;
}