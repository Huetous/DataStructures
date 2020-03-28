#include "pch.h"
#include <vector>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <BinaryMaxHeap.h>
#include <BinaryMinHeap.h>

int main()
{
	std::vector<int> values = { 1,2,3,4,5,6,7,8,9,10 };
	BinaryMaxHeap *maxHeap = new BinaryMaxHeap(values);
	std::cout << maxHeap->getMax() << std::endl;

	maxHeap->Insert(100);
	std::cout << maxHeap->getMax() << std::endl;

	maxHeap->Remove(0);
	std::cout << maxHeap->getMax() << std::endl;

	int max = maxHeap->ExtractMax();
	std::cout << maxHeap->getMax() << std::endl;

	maxHeap->ChangePriority(0, 1);
	std::cout << maxHeap->getMax() << std::endl;

	
	BinaryMinHeap *minHeap = new BinaryMinHeap(values);
	std::cout << minHeap->getMin() << std::endl;

	minHeap->Insert(100);
	std::cout << minHeap->getMin() << std::endl;

	minHeap->Remove(0);
	std::cout << minHeap->getMin() << std::endl;

	int min = minHeap->ExtractMin();
	std::cout << minHeap->getMin() << std::endl;

	minHeap->ChangePriority(0, 1);
	std::cout << minHeap->getMin() << std::endl;

	/*int n_opers;
	std::cin >> n_opers;
	std::cin.ignore();

	BinaryHeap *heap = new BinaryHeap();
	std::string str;
	std::vector<std::string> data;
	for (int i = 0; i < n_opers; ++i) {
		data.clear();

		std::getline(std::cin, str);
		std::istringstream iss(str);
		std::string s;
		while (std::getline(iss, s, ' '))
			data.push_back(s.c_str());

		if (data[0] == "Insert")
			heap->Insert(std::stoi(data[1]));
		else
			std::cout << heap->ExtractMax() << std::endl;
	}*/


}