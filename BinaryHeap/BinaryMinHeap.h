#pragma once
#include <vector>

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