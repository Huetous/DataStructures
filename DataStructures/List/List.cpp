#include "List.h"
#include <iostream>
#include <algorithm>


template<typename T>
Node<T>* SinglyLinkedList<T>::create_node(T data, Node<T>* next) {
	Node<T>* node = new Node<T>();
	node->data = data;
	node->next = next;
	return node;
}

template<typename T>
T SinglyLinkedList<T>::pop() {
	T data = head->data;
	head = head->next;
	_size--;
	return data;
}

template<typename T>
void SinglyLinkedList<T>::push(T data) {
	head = create_node(data, head);
	_size++;
}

template<typename T>
Node<T>* SinglyLinkedList<T>::find(T data) {
	if (_size == 0) return NULL;

	Node<T>* node = head;
	while (node) {
		if (node->data == data)
			break;
		node = node->next;
	}
	return node;
}

template<typename T>
void SinglyLinkedList<T>::replace(T data, T new_data) {
	Node<T>* node = find(data);
	node->data = new_data;
}

template<typename T>
int SinglyLinkedList<T>::count(T data) {
	Node<T>* node = head;
	int count = 0;

	while (node) {
		if (node->data == data)
			count++;
		node = node->next;
	}
	return count;
}

template<typename T>
void SinglyLinkedList<T>::swap(T left, T right) {
	Node<T>* l = find(left), *r = find(right);
	if (l && r)  // swap only if both values are present
		std::swap(l->data, r->data);
}

template<typename T>
void SinglyLinkedList<T>::remove(T data) {
	if (_size == 0) return;

	Node<T>* prev = NULL, *node = head;

	if (head->data == data) {
		pop();
		return;
	}

	while (node) {
		if (node->data == data) {
			if (prev)
				prev->next = node->next;
			
			node = node->next;
			_size--;
			break;
		}
		prev = node;
		node = node->next;
	}
}

template <typename T>
void SinglyLinkedList<T>::insert_after(T prev_data, T data) {
	if (_size == 0) return;

	Node<T>* prev = find(prev_data);

	if (!prev) return;  // if there is no such value as prev_data, then there is nowhere to insert after :)

	Node<T>* new_node = create_node(data, prev->next);
	prev->next = new_node;

	_size++;
}

template <typename T>
bool SinglyLinkedList<T>::is_empty() {
	return _size == 0;
}

template <typename T>
int SinglyLinkedList<T>::size() {
	return _size;
}

template <typename T>
void SinglyLinkedList<T>::print() {
	Node<T>* node = head;
	while (node) {
		std::cout << node->data << " ";
		node = node->next;
	};
	std::cout << std::endl;
}
