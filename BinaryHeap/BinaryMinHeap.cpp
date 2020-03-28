#include "pch.h"
#include <vector>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>

class BinaryMinHeap {
	std::vector<int> heap;

public:
	BinaryMinHeap(std::vector<int> values);
	BinaryMinHeap();

	void Insert(int priority);
	void Remove(int index);
	int getMin();
	int ExtractMin();
	void ChangePriority(int index, int priority);

private:
	void SiftUp(int index);
	void SiftDown(int index);

	int getMinChildIndex(int parent_index);
	void Swap(int i, int j);
};

BinaryMinHeap::BinaryMinHeap(std::vector<int> values) {
	for (auto &value : values) {
		heap.push_back(value);
		SiftUp(heap.size() - 1);
	}
}

BinaryMinHeap::BinaryMinHeap() {}

void BinaryMinHeap::Insert(int priority) {
	heap.push_back(priority);
	SiftUp(heap.size() - 1);
}

void BinaryMinHeap::Remove(int index) {
	if (0 <= index <= heap.size() - 1) {
		heap[index] = getMin() - 1;
		ExtractMin();
	}
	return;
}

int BinaryMinHeap::getMin() {
	if (heap.size() > 0)
		return heap[0];
}

int BinaryMinHeap::ExtractMin() {
	int min = heap[0];
	if (heap.size() == 1) {
		heap.pop_back();
		return min;
	}
	int last_leaf = heap[heap.size() - 1];
	Swap(0, heap.size() - 1);
	heap.pop_back();
	SiftDown(0);
	return min;
}

void BinaryMinHeap::ChangePriority(int index, int priority) {
	if (0 <= index <= heap.size() - 1) {
		heap[index] = priority;
		if (heap[index] < priority)
			SiftUp(index);
		else
			SiftDown(index);
	}
	return;
}

void BinaryMinHeap::SiftUp(int index) {
	if (index == 0) return;

	int parent_index = std::floor(index / 2);
	if (0 <= parent_index <= heap.size())
		if (heap[parent_index] > heap[index]) {
			Swap(parent_index, index);
			SiftUp(parent_index);
		}

	return;
}

void BinaryMinHeap::SiftDown(int index) {
	if (index == heap.size()) return;

	int min_child_index = getMinChildIndex(index);
	if (min_child_index == -1) return;

	if (heap[min_child_index] >= heap[index])
		return;
	else {
		Swap(min_child_index, index);
		SiftDown(min_child_index);
	}
}

void BinaryMinHeap::Swap(int i, int j) {
	int tmp = heap[i];
	heap[i] = heap[j];
	heap[j] = tmp;
	return;
}

int BinaryMinHeap::getMinChildIndex(int parent_index) {
	int left_index = 2 * parent_index + 1;
	int right_index = left_index + 1;

	int max_index;
	int last_index = heap.size() - 1;
	if (left_index <= last_index && right_index <= last_index) {
		if (heap[left_index] <= heap[right_index])
			max_index = left_index;
		else
			max_index = right_index;
		return max_index;
	}
	else if (left_index <= last_index)
		return left_index;

	return -1;
}

int main()
{
	std::vector<int> values = { 1,2,3,4,5,6,7,8,9,10 };
	BinaryMinHeap *heap = new BinaryMinHeap(values);
	std::cout << heap->getMin() << std::endl;

	heap->Insert(100);
	std::cout << heap->getMin() << std::endl;

	heap->Remove(0);
	std::cout << heap->getMin() << std::endl;

	int max = heap->ExtractMin();
	std::cout << heap->getMin() << std::endl;

	heap->ChangePriority(0, 1);
	std::cout << heap->getMin() << std::endl;


	/*int n_opers;
	std::cin >> n_opers;
	std::cin.ignore();

	BinaryMinHeap *heap = new BinaryMinHeap();
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
			std::cout << heap->ExtractMin() << std::endl;
	}*/

}
