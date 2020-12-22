#include "pch.h"
#include "Queue.h"
#include <iostream>

template <typename T>
void Queue<T>::push_back(T data) {
	put.push_back(data);
}

template <typename T>
int Queue<T>::size() {
	return take.size() + put.size();
}

template <typename T>
bool Queue<T>::is_empty() {
	return size() == 0;
}

template <typename T>
T Queue<T>::pop_front() {
	if (size() == 0) return NULL;
	
	if (take.size() == 0) {
		int put_size = put.size();
		for (int i = 0; i < put_size; ++i){
			take.push_back(put.back());
			put.pop_back();
		}
	}
		
	T temp = take.back();
	take.pop_back();
	return temp;
}

template <typename T>
T Queue<T>::get_back() {
	if (size() == 0) return NULL;

	if (put.size() != 0)
		return put.back();

	return take.front();
}

template <typename T>
T Queue<T>::get_front() {
	if (size() == 0) return NULL;

	if (take.size() != 0)
		return take.back();

	return put.front();
}

template <typename T>
void Queue<T>::print() {
	if (size() == 0)
		std::cout << std::endl;

	int put_size = put.size(), take_size = take.size();

	for (int i = take_size - 1; i >= 0; --i)
		std::cout << take[i] << " ";

	for (int i = 0; i < put_size; ++i)
		std::cout << put[i] << " ";

	std::cout << std::endl;
}