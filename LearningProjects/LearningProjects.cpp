// LearningProjects.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
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

//TODO Create classes for each group of problemsI finish.
void CollatzConjecture();
std::vector<int> MergeSort(std::vector<int>, int);
int* Merge(std::vector<int>, int, std::vector<int>, int);
std::vector<int> BubbleSort(std::vector<int>);
std::vector<int> GetArray();
void PrintArray(std::vector<int>);
float ClosestPair(Points &points_array);
double SmallestDistance(const Points& point_array, double min);
double DivideConquer(const Points& point_array);
Points GetPointArray();


int main()
{
	int choice = 0;
	const int max_choice = 4;

	while (choice <= max_choice) {
		std::cout << "Introduce a number to choose one the the problems." << std::endl;
		std::cout << "1. Collatz Conjecture." << std::endl;
		std::cout << "2. Merge Sort." << std::endl;
		std::cout << "3. Bubble Sort." << std::endl;
		std::cout << "4. Closest Pair Problem." << std::endl;
		std::cin >> choice;
	
		switch (choice) {
		case 1:
			CollatzConjecture();
			break;
		case 2: {
			std::vector<int> unordered_array = GetArray();
			std::vector<int> ordered_array = MergeSort(unordered_array, unordered_array.size());
			PrintArray(ordered_array);
			break;
		}
		case 3: {
			std::vector<int> unordered_array = GetArray();
			std::vector<int> ordered_array = BubbleSort(unordered_array);
			PrintArray(ordered_array);
			break;
		}
		case 4: {
			Points point_array = GetPointArray();
			std::cout << "Smallest Distance = " << ClosestPair(point_array) << std::endl;
			break;
		}
		default:
			return 0;
		}
	}
}

void CollatzConjecture() {
	int given_number = 0;
	int steps = 1;
	std::cout << "Introduce a number." << std::endl;
	std::cin >> given_number;

	while (given_number != 1) {
		if (given_number % 2 == 0) {
			std::cout << given_number << " >> ";
			given_number /= 2;
		}
		else {
			std::cout << given_number << " >> ";
			given_number = given_number * 3 + 1;
		}

		steps++;
	}
	std::cout << given_number << std::endl;
	std::cout << "The number of operations to reach the number on is: " << steps << std::endl;

	return;
}

std::vector<int> GetArray() {
	std::vector<int> unordered_array;
	std::cout << "Introduce 6 unordered integers.";
	for (int i = 0; i < 6; i++) {
		int typed_integer = 0;
		std::cin >> typed_integer;
		unordered_array.push_back(typed_integer);
	}

	return unordered_array;
}

std::vector<int> MergeSort(std::vector<int> unordered_array, int length) {
	if (length <= 1) return unordered_array;
	int length_subarray_1 = length / 2;
	int length_subarray_2 = length - length_subarray_1;

	std::vector<int> temp_array_1;
	temp_array_1.resize(length_subarray_1);
	std::vector<int> temp_array_2;
	temp_array_2.resize(length_subarray_2);

	int i = 0, k = 0;

	for (; i < length_subarray_1; i++) temp_array_1[k++] = unordered_array[i];
	for (k = 0; i < length; i++) temp_array_2[k++] = unordered_array[i];

	MergeSort(temp_array_1, length_subarray_1);
	MergeSort(temp_array_2, length_subarray_2);

	int* result = Merge(temp_array_1, length_subarray_1, temp_array_2, length_subarray_2);

	for (int i = 0; i < length; i++) unordered_array[i] = result[i];

	delete result;
	temp_array_1.clear();
	temp_array_1.shrink_to_fit();
	temp_array_2.clear();
	temp_array_2.shrink_to_fit();

	return unordered_array;
}

int* Merge(std::vector<int> temp_array_1, int length_subarray_1, std::vector<int> temp_array_2, int length_subarray_2) {
	int* result = new int[length_subarray_1 + length_subarray_2];
	int i = 0, j = 0, k = 0;

	while (i < length_subarray_1 && j < length_subarray_2) {
		if (temp_array_1[i] < temp_array_2[j]) result[k++] = temp_array_1[i++];
		else result[k++] = temp_array_2[j++];
	}

	while (i < length_subarray_1) result[k++] = temp_array_1[i++];
	while (j < length_subarray_2) result[k++] = temp_array_2[j++];

	return result;
}

std::vector<int> BubbleSort(std::vector<int> unordered_array) {
	for (int i = unordered_array.size() - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) if (unordered_array[j] > unordered_array[j + 1]) std::swap(unordered_array[j], unordered_array[j + 1]);
	}

	return unordered_array;
}


void PrintArray(std::vector<int>ordered_array) {
	for (int i = 0; i < ordered_array.size(); i++) std::cout << ordered_array[i] << " ";

	std::cout << std::endl;
}

Points GetPointArray() {
	Point point_value;
	Points point_array;
	std::cout << "Introduce six pairs of points(ex. 2 6)" << std::endl;
	for (int i = 0; i < 6; i++) {
		std::cin >> point_value.x >> point_value.y;
		point_array.push_back(point_value);
	}

	return point_array;
}

float ClosestPair(Points &point_array) {
	std::sort(point_array.begin(), point_array.end(), [](const Point & a, const Point & b) {return (a.x == b.x) ? (a.y < b.y) : (a.x < b.x); });

	return DivideConquer(point_array);
}

double SmallestDistance(const Points& point_array, double min = __DBL_MAX) {
	for (auto it1 = point_array.begin(); it1 != point_array.end(); ++it1)
		for (auto it2 = it1 + 1; it2 != point_array.end() && std::abs(it2->y - it1->y) < min; ++it2)
			min = std::min(it1->Distance(*it2), min);

	return min;
}

double DivideConquer(const Points& point_array) {
	if (point_array.size() <= 3) return SmallestDistance(point_array);

	size_t mid = point_array.size() / 2;

	Points left_array(point_array.begin(), point_array.begin() + mid);
	Points right_array(point_array.begin() + mid, point_array.end());

	double left_index = DivideConquer(left_array);
	double right_index = DivideConquer(right_array);
	double smallest_distance = std::min(left_index, right_index);

	Points strip;
	const Point& mid_point = point_array[mid];

	for (auto point : point_array)
		if (std::abs(mid_point.x - point.x) < smallest_distance) strip.push_back(point);

	std::sort(strip.begin(), strip.end(), [](const Point & a, const Point & b) {return (a.y == b.y) ? (a.x < b.x) : (a.y < b.y); });

	return std::min(smallest_distance, SmallestDistance(strip, smallest_distance));
}