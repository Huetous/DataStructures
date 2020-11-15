#pragma once
#include<vector>

template <typename T>
class BinaryMaxHeap {
	std::vector<T> heap;

public:
	explicit BinaryMaxHeap(std::vector<T> &values);
	BinaryMaxHeap();

	void insert(T value);
	void remove(uint32_t i);
	void change_priority(uint32_t i, int32_t priority);
	int32_t get_max();
	T extract_max();
	uint32_t size();

private:
	void sift_down(uint32_t i);
	void sift_up(uint32_t i);
	uint32_t get_max_child_index(uint32_t parent_index);
};