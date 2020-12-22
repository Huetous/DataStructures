#include "pch.h"
#include "AVL_Tree.h"
#include <algorithm>
#include <iostream>

template <typename T>
Node<T>::Node(T key) {
	this->key = key;
	left = NULL;
	right = NULL;
	height = 1;
}

template <typename T>
int get_height(Node<T>* node) {
	return node == NULL ? 0 : node->height;
}

template <typename T>
int get_diff(Node<T>* node) {
	return node == NULL ? 0 : get_height(node->left) - get_height(node->right);
}

template <typename T>
void Node<T>::update_height() {
	height = std::max(get_height(left), get_height(right)) + 1;
}

template <typename T>
AVL_Tree<T>::AVL_Tree() {
	head = NULL;
}

template <typename T>
T AVL_Tree<T>::min() {
	return min(head)->key;
}

template <typename T>
Node<T>* AVL_Tree<T>::min(Node<T>* node) {
	Node<T>* min = node;
	while (min->left != NULL)
		min = min->left;
	return min;
}

template <typename T>
T AVL_Tree<T>::max() {
	return max(head)->key;
}

template <typename T>
Node<T>* AVL_Tree<T>::max(Node<T>* node) {
	Node<T>* max = node;
	while (max->right != NULL)
		max = max->right;
	return max;
}

template <typename T>
Node<T>* AVL_Tree<T>::left_rotation(Node<T>* x) {
	Node<T>* y = x->right;
	x->right = y->left;
	y->left = x;

	x->update_height();
	y->update_height();

	return y;
}

template <typename T>
Node<T>* AVL_Tree<T>::right_rotation(Node<T>* y) {
	Node<T>* x = y->left;
	y->left = x->right;
	x->right = y;

	y->update_height();
	x->update_height();
	return x;
}

template <typename T>
void AVL_Tree<T>::insert(T key) {
	head = insert(head, key);
}

template <typename T>
Node<T>* AVL_Tree<T>::insert(Node<T>* node, T key) {
	if (node == NULL) {
		size_++;
		return new Node<T>(key);
	}

	if (key < node->key)
		node->left = insert(node->left, key);
	else if (key >= node->key)
		node->right = insert(node->right, key);
	else
		return node;

	node->update_height();

	int diff = get_diff(node);

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

template <typename T>
void AVL_Tree<T>::remove(T key) {
	head = remove(head, key);
}

template <typename T>
Node<T>* AVL_Tree<T>::remove(Node<T>* node, T key) {
	if (node == NULL) return node;

	if (key < node->key)
		node->left = remove(node->left, key);
	else if (key > node->key)
		node->right = remove(node->right, key);

	else if (node->left != NULL && node->right != NULL) {
		Node<T>* minimum = min(node->right);
		node->key = minimum->key;
		node->right = remove(node->right, minimum->key);
		size_--;
	}

	else {
		Node<T>* child = node->left ? node->left : node->right;
		if (child == NULL)
			node = NULL;
		else
			*node = *child;
		size_--;
	}

	if (node == NULL) return node;

	node->update_height();

	int diff = get_diff(node);

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

template <typename T>
void AVL_Tree<T>::traverse(int order) {
	traverse(head, order);
	std::cout << std::endl;
}

template <typename T>
void AVL_Tree<T>::traverse(Node<T>* node, int order) {
	if (node) {
		if (order == 0)
			std::cout << node->key << " ";

		traverse(node->left, order);

		if (order == 1)
			std::cout << node->key << " ";

		traverse(node->right, order);

		if (order == 2)
			std::cout << node->key << " ";
	}
}

template <typename T>
bool AVL_Tree<T>::is_empty() {
	return size_ == 0;
}

template <typename T>
int AVL_Tree<T>::size() {
	return size_;
}

template <typename T>
int AVL_Tree<T>::count(T key) {
	int count_ = 0;
	count(head, key, count_);
	return count_;
}

template <typename T>
void AVL_Tree<T>::count(Node<T>* node, T key, int& count_) {
	if (!node) return;
	if (node->key == key) count_++;
	if (node->right) count(node->right, key, count_);
	if (node->left) count(node->left, key, count_);
}