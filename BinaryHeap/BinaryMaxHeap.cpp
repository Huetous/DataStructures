#include "pch.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <BinaryMaxHeap.h>

template <typename T>
BinaryMaxHeap<T>::BinaryMaxHeap(std::vector<T> &values) {
	for (auto &value : values) {
		heap.push_back(value);
		sift_up(heap.size() - 1);
	}
}

template <typename T>
BinaryMaxHeap<T>::BinaryMaxHeap() {}

template <typename T>
uint32_t BinaryMaxHeap<T>::size() {
	return heap.size();
}

template <typename T>
int32_t BinaryMaxHeap<T>::get_max() {
	return size() > 0 ? heap[0] : 0;
}

template <typename T>
void BinaryMaxHeap<T>::insert(T value) {
	heap.push_back(value);
	sift_up(size() - 1);
}

template <typename T>
void BinaryMaxHeap<T>::change_priority(uint32_t i, int32_t priority) {
	if (0 <= i && i < size()) {
		if (heap[i] < priority) {
			heap[i] = priority;
			sift_up(i);
		}
		else if (heap[i] > priority) {
			heap[i]= priority;
			sift_down(i);
		}
	}
}

template <typename T>
void BinaryMaxHeap<T>::remove(uint32_t i) {
	if (0 <= i && i < size()) {
		change_priority(i, get_max() + 1);
		extract_max();
	}
}

template <typename T>
T BinaryMaxHeap<T>::extract_max() {
	if (size() == 0) return NULL;

	T max = heap[0];

	if (size() > 1) {
		std::swap(heap[0], heap[size() - 1]);
		heap.pop_back();
		sift_down(0);
	}
	else {
		heap.pop_back();
	}

	return max;
}

template <typename T>
void BinaryMaxHeap<T>::sift_up(uint32_t i) {
	if (i == 0) return;

	uint32_t parent = (i - 1) / 2;
	if (0 <= parent && parent < size())
		if (heap[i] > heap[parent]) {
			std::swap(heap[parent], heap[i]);
			sift_up(parent);
		}
}

template <typename T>
void BinaryMaxHeap<T>::sift_down(uint32_t i) {
	if (i == (size() - 1)) return;

	int32_t max_child = get_max_child_index(i);
	if (max_child == -1) return;

	if (heap[max_child] > heap[i]) {
		std::swap(heap[max_child], heap[i]);
		sift_down(max_child);
	}
}

template <typename T>
uint32_t  BinaryMaxHeap<T>::get_max_child_index(uint32_t parent_index) {
	uint32_t l = 2 * parent_index + 1;
	uint32_t r = l + 1;

	if (l < size() && r < size())
		return heap[l] > heap[r] ? l : r;

	else if (l < size())
		return l;

	return -1;
}