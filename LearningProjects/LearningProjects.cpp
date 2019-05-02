// LearningProjects.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "ClassicAlgorithm.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <limits>
#include <iomanip>
#include <algorithm>



ClassicAlgorithm* Algorithm;

int main()
{
	int choice = 0;
	const int max_choice = 5;

	while (choice <= max_choice) {
		std::cout << "Introduce a number to choose one the the problems." << std::endl;
		std::cout << "1. Collatz Conjecture." << std::endl;
		std::cout << "2. Merge Sort." << std::endl;
		std::cout << "3. Bubble Sort." << std::endl;
		std::cout << "4. Closest Pair Problem." << std::endl;
		std::cout << "5. Sieve of Eratosthenes" << std::endl;
		std::cin >> choice;
	
		switch (choice) {
		case 1:
			Algorithm->CollatzConjecture();
			break;
		case 2: {
			std::vector<int> ordered_array = Algorithm->MergeSort(Algorithm->GetArray());
			Algorithm->PrintArray(ordered_array);
			break;
		}
		case 3: {
			std::vector<int> ordered_array = Algorithm->BubbleSort(Algorithm->GetArray());
			Algorithm->PrintArray(ordered_array);
			break;
		}
		case 4: {
			Points point_array = Algorithm->GetPointArray();
			std::cout << "Smallest Distance = " << Algorithm->ClosestPair(point_array) << std::endl;
			break;
		}
		case 5:
			Algorithm->SieveOfEratosthenes();
			break;
		default:
			return 0;
		}
	}
}