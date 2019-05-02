#include "pch.h"
#include "ClassicAlgorithm.h"


ClassicAlgorithm::ClassicAlgorithm()
{
}


ClassicAlgorithm::~ClassicAlgorithm()
{
}

void ClassicAlgorithm::CollatzConjecture()
{
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

std::vector<int> ClassicAlgorithm::GetArray()
{
	std::vector<int> unordered_array;
	std::cout << "Introduce 6 unordered integers.";
	for (int i = 0; i < 6; i++) {
		int typed_integer = 0;
		std::cin >> typed_integer;
		unordered_array.push_back(typed_integer);
	}

	return unordered_array;
}

std::vector<int> ClassicAlgorithm::MergeSort(std::vector<int> unordered_array)
{
	if (unordered_array.size() <= 1) return unordered_array;
	int length_subarray_1 = unordered_array.size() / 2;
	int length_subarray_2 = unordered_array.size() - length_subarray_1;

	std::vector<int> temp_array_1(length_subarray_1);
	std::vector<int> temp_array_2(length_subarray_2);

	int i = 0, k = 0;

	for (; i < length_subarray_1; i++) temp_array_1[k++] = unordered_array[i];
	for (k = 0; i < unordered_array.size(); i++) temp_array_2[k++] = unordered_array[i];

	MergeSort(temp_array_1);
	MergeSort(temp_array_2);

	int* result = Merge(temp_array_1, temp_array_2);

	for (int i = 0; i < unordered_array.size(); i++) unordered_array[i] = result[i];

	delete result;
	temp_array_1.clear();
	temp_array_1.shrink_to_fit();
	temp_array_2.clear();
	temp_array_2.shrink_to_fit();

	return unordered_array;
}

int* ClassicAlgorithm::Merge(std::vector<int> temp_array_1, std::vector<int> temp_array_2)
{
	int* result = new int[temp_array_1.size() + temp_array_2.size()];
	int i = 0, j = 0, k = 0;

	while (i < temp_array_1.size() && j < temp_array_2.size()) {
		if (temp_array_1[i] < temp_array_2[j]) result[k++] = temp_array_1[i++];
		else result[k++] = temp_array_2[j++];
	}

	while (i < temp_array_1.size()) result[k++] = temp_array_1[i++];
	while (j < temp_array_2.size()) result[k++] = temp_array_2[j++];

	return result;
}

std::vector<int> ClassicAlgorithm::BubbleSort(std::vector<int> unordered_array)
{
	for (int i = unordered_array.size() - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) if (unordered_array[j] > unordered_array[j + 1]) std::swap(unordered_array[j], unordered_array[j + 1]);
	}

	return unordered_array;
}

void ClassicAlgorithm::PrintArray(std::vector<int> ordered_array)
{
	for (int i = 0; i < ordered_array.size(); i++) std::cout << ordered_array[i] << " ";

	std::cout << std::endl;
}

Points ClassicAlgorithm::GetPointArray()
{
	Point point_value;
	Points point_array;
	std::cout << "Introduce six pairs of points(ex. 2 6)" << std::endl;
	for (int i = 0; i < 6; i++) {
		std::cin >> point_value.x >> point_value.y;
		point_array.push_back(point_value);
	}

	return point_array;
}

float ClassicAlgorithm::ClosestPair(Points& point_array)
{
	std::sort(point_array.begin(), point_array.end(), [](const Point & a, const Point & b) {return (a.x == b.x) ? (a.y < b.y) : (a.x < b.x); });

	return DivideConquer(point_array);
}

double ClassicAlgorithm::SmallestDistance(const Points& point_array, double min)
{
	for (auto it1 = point_array.begin(); it1 != point_array.end(); ++it1)
		for (auto it2 = it1 + 1; it2 != point_array.end() && std::abs(it2->y - it1->y) < min; ++it2)
			min = std::min(it1->Distance(*it2), min);

	return min;
}

double ClassicAlgorithm::DivideConquer(const Points& point_array)
{
	if (point_array.size() <= 3) return SmallestDistance(point_array, point_array.size());

	size_t mid = point_array.size() / 2;

	Points left_array(point_array.begin(), point_array.begin() + mid);
	Points right_array(point_array.begin() + mid, point_array.end());

	double left_index = DivideConquer(left_array);
	double right_index = DivideConquer(right_array);
	double smallest_distance = std::min(left_index, right_index);

	Points strip;
	const Point & mid_point = point_array[mid];

	for (auto point : point_array)
		if (std::abs(mid_point.x - point.x) < smallest_distance) strip.push_back(point);

	std::sort(strip.begin(), strip.end(), [](const Point & a, const Point & b) {return (a.y == b.y) ? (a.x < b.x) : (a.y < b.y); });

	return std::min(smallest_distance, SmallestDistance(strip, smallest_distance));
}

void ClassicAlgorithm::FlagMultiples(bool bool_array[], int a, unsigned int num)
{
	int i = 2;
	int temp = i * a;
	while (temp <= num) {
		bool_array[temp - 1] = true;
		++i;
		temp = i * a;
	}
}

void ClassicAlgorithm::SieveOfEratosthenes()
{
	unsigned int num;
	std::cout << "Introduce a positive number." << std::endl;
	std::cin >> num;

	if (num < 2) return;

	bool* visited = new bool[num];
	for (int k = 0; k < num; k++) visited[k] = false;

	for (unsigned int i = 1; i < num; ++i) {
		if (visited[i] == 0) {
			std::cout << i + 1 << " ";
			FlagMultiples(visited, i + 1, num);
		}
	}

	std::cout << std::endl;

	delete[] visited;
}
