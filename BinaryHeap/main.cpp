#include "pch.h"
#include <vector>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <BinaryMaxHeap.cpp>

int main()
{
	std::vector<int> values = { 1,2,3,4,5,6,7,8,9,10 };
	BinaryMaxHeap<int>* maxHeap = new BinaryMaxHeap<int>(values);
	std::cout << maxHeap->get_max() << std::endl;

	maxHeap->insert(100);
	std::cout << maxHeap->get_max() << std::endl;

	maxHeap->remove(0);
	std::cout << maxHeap->get_max() << std::endl;

	int max = maxHeap->extract_max();
	std::cout << maxHeap->get_max() << std::endl;

	maxHeap->change_priority(0, 1);
	std::cout << maxHeap->get_max() << std::endl;
}