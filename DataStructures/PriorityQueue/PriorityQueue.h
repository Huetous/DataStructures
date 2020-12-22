#pragma once
#include <vector>

/*
	Implements min-heap
*/
template <typename T>
class PriorityQueue {
public:
	explicit PriorityQueue(std::vector<T> &items);
	PriorityQueue();
	
	void insert(T item);
	void remove(int i);
	
	T get_min();
	T extract_min();

	void change_priority(int i, int priority);
	
	bool is_empty();
	int size();

	void print();

private:
	std::vector<T>* heap;
	
	void heapify();
	void sift_down(int i);
	void sift_up(int i);
	
	int get_min_child_index(int parent_index);
	bool validate(int i);
};

