#pragma once
#include<vector>

class BinaryMaxHeap {
	std::vector<int> heap;

public:
	BinaryMaxHeap(std::vector<int> values);
	BinaryMaxHeap();

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