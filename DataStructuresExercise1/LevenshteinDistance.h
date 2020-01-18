#pragma once
class LevenshteinDistance
{
public:
	static constexpr int MAX_SIZE = 10;
	int recursive(const char* start, const char* end);
	int dynamic(const char* start, const char* end);
	int iterative(const char* start, const char* end);

private:
	int innerRecursive(const char* start, int startLen, const char* end, int endLen);
	int innerDynamic(const char* start, int startLen, const char* end, int endLen, int matrix[][MAX_SIZE]);
	
};

