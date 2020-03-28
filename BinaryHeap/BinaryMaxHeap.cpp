#include <stdlib.h>
#include "pch.h"
#include <vector>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <BinaryMaxHeap.h>


BinaryMaxHeap::BinaryMaxHeap(std::vector<int> values) {
	for (auto &value : values) {
		heap.push_back(value);
		SiftUp(heap.size() - 1);
	}
}

BinaryMaxHeap::BinaryMaxHeap() {}

void BinaryMaxHeap::Insert(int priority) {
	heap.push_back(priority);
	SiftUp(heap.size() - 1);
}

void BinaryMaxHeap::Remove(int index) {
	if (0 <= index <= heap.size() - 1) {
		heap[index] = getMax() + 1;
		ExtractMax();
	}
	return;
}

int BinaryMaxHeap::getMax() {
	if (heap.size() > 0)
		return heap[0];
}

int BinaryMaxHeap::ExtractMax() {
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

void BinaryMaxHeap::ChangePriority(int index, int priority) {
	if (0 <= index <= heap.size() - 1) {
		heap[index] = priority;
		if (heap[index] > priority)
			SiftUp(index);
		else
			SiftDown(index);
	}
	return;
}

void BinaryMaxHeap::SiftUp(int index) {
	if (index == 0) return;

	int parent_index = std::floor(index / 2);
	if (0 <= parent_index <= heap.size())
		if (heap[parent_index] < heap[index]) {
			Swap(parent_index, index);
			SiftUp(parent_index);
		}

	return;
}

void BinaryMaxHeap::SiftDown(int index) {
	if (index == heap.size()) return;

	int max_child_index = getMaxChildIndex(index);
	if (max_child_index == -1) return;

	if (heap[max_child_index] <= heap[index])
		return;
	else {
		Swap(max_child_index, index);
		SiftDown(max_child_index);
	}
}

void BinaryMaxHeap::Swap(int i, int j) {
	int tmp = heap[i];
	heap[i] = heap[j];
	heap[j] = tmp;
	return;
}

int BinaryMaxHeap::getMaxChildIndex(int parent_index) {
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
	else if (left_index <= last_index)
		return left_index;

	return -1;
}


