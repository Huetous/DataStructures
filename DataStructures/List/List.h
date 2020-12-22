#pragma once
#include <algorithm>

template<typename T>
struct Node {
	T data;
	Node<T>* next;
};

/*
	This implementation by default assumes that the type of stored objects is simple (number, char, etc).
	If you want to use this class with more complex types (struct, class), then you should
	override method print() for correct display. And also with complex type it should override operator == 
	for correct work of some methods (e.g., remove, count)
	*/

template<typename T>
class SinglyLinkedList {
public:
	T pop();
	void remove(T data);  // removes first occurence of the data

	void push(T data);
	void insert_after(T prev, T data);

	Node<T>* find(T data);  // find first occurence of the data and returns the whole node.
	int count(T data);  // count numbers of occurences of the data in the list

	void replace(T data, T new_data);
	void swap(T left, T right); 

	bool is_empty();
	int size();

	
	void print(); 

	SinglyLinkedList() : head(NULL), _size(0) {};

private:
	int _size;
	Node<T>* create_node(T data, Node<T>* next);

protected:
	Node<T>* head;
};

