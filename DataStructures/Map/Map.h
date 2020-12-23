#pragma once
#include "../AVL_Tree/AVL_Tree.h"
#include "../AVL_Tree/AVL_Tree.cpp"

template <typename K, typename V>
class Map {
public:
	Map();

	void insert(K key, V value);
	void remove(K key);
	V find(K key);

	bool is_empty();
	int size();

protected:
	AVL_Tree<K, V>* tree;
};