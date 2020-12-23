#pragma once
#include <algorithm>
#include <iostream>

template <typename K, typename V = int>
struct Node {
public:
	K key;
	V value;
	Node* left;
	Node* right;
	int height;

	Node();
	explicit Node(K key);
	Node(K key, V value);
	void update_height();
};

template <typename K, typename V = int>
class AVL_Tree {
public:
	AVL_Tree();
	AVL_Tree(bool allow_duplicates);

	void insert(K key, V value);
	void insert(K key);
	void remove(K key);

	K min();
	K max();

	V find(K key);
	bool contains(K key);

	int count(K key);

	void traverse(int order);

	bool is_empty();
	int size();

protected:
	Node<K, V>* head;
	int size_;
	bool allow_dups;
	bool is_removed;

	Node<K, V>* left_rotation(Node<K, V>* x);
	Node<K, V>* right_rotation(Node<K, V>* y);
	
	Node<K, V>* insert(Node<K, V>* node, K key, V value);
	Node<K, V>* remove(Node<K, V>* node, K key, bool &is_removed);

	Node<K, V>* max(Node<K, V>* node);
	Node<K, V>* min(Node<K, V>* node);

	Node<K, V>* find(Node<K, V>* node, K key);

	void count(Node<K, V>* node, K key, int& count);
	void traverse(Node<K, V>* node, int order);
};

