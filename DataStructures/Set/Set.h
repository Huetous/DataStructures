#pragma once
#include "../AVL_Tree/AVL_Tree.h"
#include "../AVL_Tree/AVL_Tree.cpp"

template <typename K>
class Set {
public:
	Set();

	void insert(K key);
	void remove(K key);
	bool contains(K key);

	bool is_empty();
	int size();

private:
	AVL_Tree<K>* tree;
};

