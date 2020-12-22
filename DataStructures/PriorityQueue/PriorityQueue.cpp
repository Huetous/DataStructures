#include "pch.h"
#include "PriorityQueue.h"
#include <vector>
#include <algorithm>
#include <iostream>

template <typename T>
PriorityQueue<T>::PriorityQueue() {
	heap = new std::vector<T>();
};

template <typename T>
void PriorityQueue<T>::print() {
	if(!is_empty()) {
		for(int i = 0; i < heap->size(); ++i)
			std::cout << heap->at(i)<< " ";
		std::cout << std::endl;
	}
}

template <typename T>
bool PriorityQueue<T>::validate(int i) {
	return (0 <= i) && (i < size());
}

template <typename T>
void PriorityQueue<T>::heapify() {
	for (int i = size() / 2; i >= 0; --i)
		sift_down(i);
}

template <typename T>
PriorityQueue<T>::PriorityQueue(std::vector<T>& items) {
	heap = &items;
	heapify();
}

template <typename T>
int PriorityQueue<T>::size() {
	return heap->size();
}

template <typename T>
bool PriorityQueue<T>::is_empty() {
	return size() == 0;
}

template <typename T>
T PriorityQueue<T>::get_min() {
	return size() > 0 ? heap->at(0) : NULL;
}

template <typename T>
void PriorityQueue<T>::insert(T item) {
	heap->push_back(item);
	sift_up(size() - 1);
}

template <typename T>
void PriorityQueue<T>::change_priority(int i, int priority) {
	if (validate(i)) {
		if (heap->at(i) > priority) {
			heap->at(i) = priority;
			sift_up(i);
		}
		else if (heap->at(i) < priority) {
			heap->at(i) = priority;
			sift_down(i);
		}
	}
}

template <typename T>
void PriorityQueue<T>::remove(int i) {
	if (validate(i)) {
		change_priority(i, get_min() - 1);
		extract_min();
	}
}

template <typename T>
T PriorityQueue<T>::extract_min() {
	if (size() == 0) return NULL;

	T min = heap->at(0);

	if (size() > 1) {
		std::swap(heap->at(0), heap->at(size() - 1));
		heap->pop_back();
		sift_down(0);
	}
	else 
		heap->pop_back();

	return min;
}

template <typename T>
void PriorityQueue<T>::sift_up(int i) {
	if (i == 0) return;

	int parent = (i - 1) / 2;
	if (validate(parent))
		if (heap->at(i) < heap->at(parent)) {
			std::swap(heap->at(parent), heap->at(i));
			sift_up(parent);
		}
}

template <typename T>
void PriorityQueue<T>::sift_down(int i) {
	if (i == size() - 1) return;

	int min_child = get_min_child_index(i);
	if (!validate(min_child)) return;

	if (heap->at(min_child) < heap->at(i)) {
		std::swap(heap->at(min_child), heap->at(i));
		sift_down(min_child);
	}
}

template <typename T>
int  PriorityQueue<T>::get_min_child_index(int parent_index) {
	int l = 2 * parent_index + 1,
		r = l + 1;

	if (l < size() && r < size())
		return heap->at(l) < heap->at(r) ? l : r;

	else if (l < size())
		return l;

	return -1;
}