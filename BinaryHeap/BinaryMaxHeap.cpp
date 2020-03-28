#include "pch.h"
#include <vector>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>

// MaxHeap
class BinaryHeap {
	std::vector<int> heap;
	
public:
	BinaryHeap(std::vector<int> values);
	BinaryHeap();

	void Insert(int priority);
	void Remove(int index);
	int getMax();
	int ExtractMax();
	void ChangePriority(int index, int priority);

private:
	void SiftUp(int index);
	void SiftDown(int index);

	int getMaxChildIndex(int parent_index);
	void Swap(int i, int j);
};

BinaryHeap::BinaryHeap(std::vector<int> values) {
	for (auto &value : values){
		heap.push_back(value);
		SiftUp(heap.size() - 1);
	}
}

BinaryHeap::BinaryHeap(){}

void BinaryHeap::Insert(int priority) {
	heap.push_back(priority);
	SiftUp(heap.size()-1);
}

void BinaryHeap::Remove(int index) {
	if (0 <= index <= heap.size() - 1) {
		heap[index] = getMax() + 1;
		ExtractMax();
	}
	return;
}

int BinaryHeap::getMax() {
	if(heap.size() > 0)
		return heap[0];
}

int BinaryHeap::ExtractMax() {
	int max = heap[0];
	if (heap.size() == 1) {
		heap.pop_back();
		return max;
	}
	int last_leaf = heap[heap.size() - 1];
	Swap(0, heap.size() - 1);
	heap.pop_back();
	SiftDown(0);
	return max;
}

void BinaryHeap::ChangePriority(int index, int priority) {
	if (0 <= index <= heap.size() -1 ) {
		heap[index] = priority;
		if (heap[index] > priority)
			SiftUp(index);
		else
			SiftDown(index);
	}
	return;
}

void BinaryHeap::SiftUp(int index) {
	if (index == 0) return;

	int parent_index = std::floor(index / 2);
	if(0 <= parent_index <= heap.size())
		if (heap[parent_index] < heap[index]) {
			Swap(parent_index, index);
			SiftUp(parent_index);
		}
	
	return;
}

void BinaryHeap::SiftDown(int index) {
	if (index == heap.size()) return;

	int max_child_index = getMaxChildIndex(index);
	if (max_child_index == -1) return;

	if (heap[max_child_index] <= heap[index])
		return;
	else{
		Swap(max_child_index, index);
		SiftDown(max_child_index);
	}
}

void BinaryHeap::Swap(int i, int j) {
	int tmp = heap[i];
	heap[i] = heap[j];
	heap[j] = tmp;
	return;
}

int BinaryHeap::getMaxChildIndex(int parent_index) {
	int left_index = 2 * parent_index + 1;
	int right_index = left_index + 1;

	int max_index;
	int last_index = heap.size() - 1;
	if (left_index <= last_index && right_index <= last_index) {
		if (heap[left_index] >= heap[right_index])
			max_index = left_index;
		else
			max_index = right_index;
		return max_index;
	}
	else if(left_index <= last_index)
		return left_index;

	return -1;
}

int main()
{	
	std::vector<int> values = { 1,2,3,4,5,6,7,8,9,10 };
	BinaryHeap *heap = new BinaryHeap(values);
	std::cout << heap->getMax() << std::endl;
	
	heap->Insert(100);
	std::cout << heap->getMax() << std::endl;
	
	heap->Remove(0);
	std::cout << heap->getMax() << std::endl;

	int max = heap->ExtractMax();
	std::cout << heap->getMax() << std::endl;
	
	heap->ChangePriority(0, 1);
	std::cout << heap->getMax() << std::endl;

	
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
