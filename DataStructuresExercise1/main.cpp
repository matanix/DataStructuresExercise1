#include <string>
#include <iostream>
#include "LevenshteinDistance.h"

using namespace std;

int main()
{
	LevenshteinDistance levenshteinDistance;
	const char* start = "kitten";
	const char* end = "sitting";
	cout << "recursive result (from " << start << " to " << end << ") is " << levenshteinDistance.recursive(start,end) << "\n";
	cout << "dynamic result (from " << start << " to " << end << ") is " << levenshteinDistance.dynamic(start, end) << "\n";
	cout << "iterative result (from " << start << " to " << end << ") is " << levenshteinDistance.iterative(start, end) << "\n";

}