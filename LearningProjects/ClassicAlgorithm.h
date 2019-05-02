#pragma once

#include <iostream>
#include <math.h>
#include <vector>
#include <limits>
#include <iomanip>
#include <algorithm>

#define __DBL_MAX std::numeric_limits<double>::max()

struct Point {
	int x, y;
	double Distance(const Point& b) const {
		return std::sqrt((x - b.x) * (x - b.x) + (y - b.y) * (y - b.y));
	}
};

typedef std::vector<Point> Points;

class ClassicAlgorithm
{
public:
	ClassicAlgorithm();
	~ClassicAlgorithm();
	void CollatzConjecture();
	std::vector<int> GetArray();
	std::vector<int> MergeSort(std::vector<int>);
	int* Merge(std::vector<int>, std::vector<int>);
	std::vector<int> BubbleSort(std::vector<int>);
	void PrintArray(std::vector<int>);
	float ClosestPair(Points& );
	double SmallestDistance(const Points&, double);
	double DivideConquer(const Points& );
	Points GetPointArray();
	void FlagMultiples(bool[], int, unsigned int);
	void SieveOfEratosthenes();
};