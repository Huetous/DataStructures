#pragma once
#include <algorithm>
#include <iostream>

template <typename T>
class Node {
public:
	T key;
	Node* left;
	Node* right;
	int height;

	explicit Node(T key);
	void update_height();
};

template <typename T>
class AVL_Tree {
public:
	AVL_Tree();

	void insert(T key);
	void remove(T key);

	T min();
	T max();

	int count(T key);

	void traverse(int order);

	bool is_empty();
	int size();

private:
	Node<T>* head;
	int size_;

	Node<T>* left_rotation(Node<T>* x);
	Node<T>* right_rotation(Node<T>* y);
	
	Node<T>* insert(Node<T>* node, T key);
	Node<T>* remove(Node<T>* node, T key);

	Node<T>* max(Node<T>* node);
	Node<T>* min(Node<T>* node);

	void count(Node<T>* node, T key, int& count);

	void traverse(Node<T>* node, int order);
};


