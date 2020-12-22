#pragma once
#include <vector>

/*
	This implementation by default assumes that the type of stored objects is simple (number, char, etc).
	If you want to use this class with more complex types (struct, class), then you should
	override method print() for correct display. 
	*/
template <typename T>
class Queue {
public:
	T pop_front();
	void push_back(T data);

	T get_back();
	T get_front();

	bool is_empty();
	int size();

	void print();

protected:
	std::vector<T> put, take;
};

