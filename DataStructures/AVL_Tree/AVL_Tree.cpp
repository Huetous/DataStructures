#include "AVL_Tree.h"
#include <algorithm>
#include <iostream>

template <typename K, typename V>
Node<K, V>::Node() {
	this->key = 0;
	this->value = 0;
	left = NULL;
	right = NULL;
	height = 1;
}

template <typename K, typename V>
Node<K, V>::Node(K key) : Node<K, V>() {
	this->key = key;
}

template <typename K, typename V>
Node<K, V>::Node(K key, V value) : Node<K, V>() {
	this->key = key;
	this->value = value;
}


template <typename K, typename V>
int get_height(Node<K, V>* node) {
	return node == NULL ? 0 : node->height;
}

template <typename K, typename V>
int get_diff(Node<K, V>* node) {
	return node == NULL ? 0 : get_height(node->left) - get_height(node->right);
}

template <typename K, typename V>
void Node<K, V>::update_height() {
	height = std::max(get_height(left), get_height(right)) + 1;
}




template <typename K, typename V>
AVL_Tree<K, V>::AVL_Tree() {
	head = NULL;
	allow_dups = false;
	size_ = 0;
}

template <typename K, typename V>
AVL_Tree<K, V>::AVL_Tree(bool allow_duplicates): AVL_Tree() {
	allow_dups = allow_duplicates;
}

template <typename K, typename V>
K AVL_Tree<K, V>::min() {
	return min(head)->key;
}

template <typename K, typename V>
K AVL_Tree<K, V>::max() {
	return max(head)->key;
}

template <typename K, typename V>
void AVL_Tree<K, V>::traverse(int order) {
	traverse(head, order);
	std::cout << std::endl;
}

template <typename K, typename V>
void AVL_Tree<K, V>::insert(K key, V value) {
	head = insert(head, key, value);
}

template <typename K, typename V>
void AVL_Tree<K, V>::insert(K key) {
	head = insert(head, key, 0);
}

template <typename K, typename V>
void AVL_Tree<K, V>::remove(K key) {
	head = remove(head, key, is_removed);
	if (is_removed) {
		size_--;
		is_removed = false;
	}
}

template <typename K, typename V>
bool AVL_Tree<K, V>::is_empty() {
	return size_ == 0;
}

template <typename K, typename V>
int AVL_Tree<K, V>::size() {
	return size_;
}

template <typename K, typename V>
int AVL_Tree<K, V>::count(K key) {
	if (!allow_dups) return find(head, key) != NULL;
	int count_ = 0;
	count(head, key, count_);
	return count_;
}

template <typename K, typename V>
V AVL_Tree<K, V>::find(K key) {
	return find(head, key)->value;
}

template <typename K, typename V>
bool AVL_Tree<K, V>::contains(K key) {
	return find(head, key) != NULL;
}

template <typename K, typename V>
Node<K, V>* AVL_Tree<K, V>::left_rotation(Node<K, V>* x) {
	Node<K, V>* y = x->right;
	x->right = y->left;
	y->left = x;

	x->update_height();
	y->update_height();

	return y;
}

template <typename K, typename V>
Node<K, V>* AVL_Tree<K, V>::right_rotation(Node<K, V>* y) {
	Node<K, V>* x = y->left;
	y->left = x->right;
	x->right = y;

	y->update_height();
	x->update_height();
	return x;
}

template <typename K, typename V>
Node<K, V>* AVL_Tree<K, V>::balance(Node<K, V>* node) {
	node->update_height();

	int diff = get_diff(node);

	if (diff > 1) {
		if (get_diff(node->left) < 0)
			node->left = left_rotation(node->left);
		return right_rotation(node);
	}

	if (diff < -1) {
		if (get_diff(node->right) > 0)
			node->right = right_rotation(node->right);
		return left_rotation(node);
	}

	return node;
}

template <typename K, typename V>
Node<K, V>* AVL_Tree<K, V>::insert(Node<K, V>* node, K key, V value) {
	if (node == NULL) {
		size_++;
		return new Node<K, V>(key, value);
	}

	if (key < node->key)
		node->left = insert(node->left, key, value);
	else if (key > node->key || (allow_dups && key == node->key))
		node->right = insert(node->right, key, value);
	else {
		if (!allow_dups) node->value = value;
		return node;
	}

	return balance(node);
}

template <typename K, typename V>
Node<K, V>* AVL_Tree<K, V>::remove(Node<K, V>* node, K key, bool& is_removed) {
	if (node == NULL) return node;

	if (key < node->key)
		node->left = remove(node->left, key, is_removed);
	else if (key > node->key)
		node->right = remove(node->right, key, is_removed);

	else if (node->left != NULL && node->right != NULL) {
		Node<K, V>* minimum = min(node->right);
		node->key = minimum->key;
		node->right = remove(node->right, minimum->key, is_removed);
	}

	else {
		Node<K, V>* child = node->left ? node->left : node->right;
		if (child == NULL)
			node = NULL;
		else
			*node = *child;
	}

	is_removed = true;
	return node == NULL ? node: balance(node);
}

template <typename K, typename V>
void AVL_Tree<K, V>::traverse(Node<K, V>* node, int order) {
	if (node != NULL) {
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

template <typename K, typename V>
void AVL_Tree<K, V>::count(Node<K, V>* node, K key, int& count_) {
	if (node == NULL) return;
	if (node->key == key) count_++;
	if (node->right) count(node->right, key, count_);
	if (node->left) count(node->left, key, count_);
}

template <typename K, typename V>
Node<K, V>* AVL_Tree<K, V>::find(Node<K, V>* node, K key) {
	if (node == NULL) return node;
	if (key < node->key)
		return find(node->left, key);
	else if (key > node->key)
		return find(node->right, key);
	else
		return node;
}

template <typename K, typename V>
Node<K, V>* AVL_Tree<K, V>::max(Node<K, V>* node) {
	Node<K, V>* max = node;
	while (max->right != NULL)
		max = max->right;
	return max;
}

template <typename K, typename V>
Node<K, V>* AVL_Tree<K, V>::min(Node<K, V>* node) {
	Node<K, V>* min = node;
	while (min->left != NULL)
		min = min->left;
	return min;
}