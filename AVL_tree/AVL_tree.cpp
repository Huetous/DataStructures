#include "pch.h"
#include <iostream>
#include <algorithm>

template <typename T>
class AVLTree {
	void insert(T key);
	void remove(T key);
	T min();
	T max();

private:
	Node* head;
};

template <typename T>
void AVLTree<T>::insert(T key) {
	head = insert(head, key);
}

template <typename T>
void AVLTree<T>::remove(T key) {
	head = remove(head, key);
}

template <typename T>
T AVLTree<T>::min() {
	return find_min(head, key);
}

template <typename T>
T AVLTree<T>::max() {
	return find_max(head, key);
}

struct Node {
	int32_t key;
	Node* left;
	Node* right;
	uint16_t height;

	explicit Node(int32_t key);
	void update_height();
};

Node::Node(int32_t key) {
	this->key = key;
	left = NULL;
	right = NULL;
	height = 1;
}

int16_t get_height(Node* node) {
	return node == NULL ? 0 : node->height;
}

int16_t get_diff(Node* node) {
	return node == NULL ? 0 : get_height(node->left) - get_height(node->right);
}

void Node::update_height() {
	height = std::max(get_height(left), get_height(right)) + 1;
}

Node* find_min(Node* node) {
	Node* min = node;
	while (min->left != NULL)
		min = min->left;
	return min;
}

Node* find_max(Node* node) {
	Node* max = node;
	while (max->right != NULL)
		max = max->right;
	return max;
}

Node* left_rotation(Node* x) {
	Node* y = x->right;
	x->right = y->left;
	y->left = x;

	x->update_height();
	y->update_height();

	return y;
}

Node* right_rotation(Node* y) {
	Node* x = y->left;
	y->left = x->right;
	x->right = y;

	y->update_height();
	x->update_height();
	return x;
}

Node* insert(Node* node, int32_t key) {
	if (node == NULL) return new Node(key);

	if (key < node->key)
		node->left = insert(node->left, key);
	else if (key > node->key)
		node->right = insert(node->right, key);
	else
		return node;

	node->update_height();

	int16_t diff = get_diff(node);

	if (diff > 1) {
		if (key < node->left->key) {
			return right_rotation(node);
		}
		else {
			node->left = left_rotation(node->left);
			return right_rotation(node);
		}
	}

	if (diff < -1) {
		if (key < node->right->key) {
			node->right = right_rotation(node->right);
			return left_rotation(node);
		}
		else
			return left_rotation(node);
	}

	return node;
}

Node* remove(Node* node, int32_t key) {
	if (node == NULL) return node;

	if (key < node->key)
		node->left = remove(node->left, key);
	else if (key > node->key)
		node->right = remove(node->right, key);

	else if (node->left != NULL && node->right != NULL) {
		Node* min = find_min(node->right);
		node->key = min->key;
		node->right = remove(node->right, min->key);
	}

	else {
		Node* child = node->left ? node->left : node->right;
		if (child == NULL)
			node = NULL;
		else
			*node = *child;
	}

	if (node == NULL) return node;

	node->update_height();

	int16_t diff = get_diff(node);

	if (diff > 1) {
		if (get_diff(node->left) >= 0) {
			return right_rotation(node);
		}
		else {
			node->left = left_rotation(node->left);
			return right_rotation(node);
		}
	}

	if (diff < -1) {
		if (get_diff(node->right) > 0) {
			node->right = right_rotation(node->right);
			return left_rotation(node);
		}
		else
			return left_rotation(node);
	}

	return node;
}
