#pragma once
#include "AVL_Tree.h"

template <typename K, typename V>
class Item : public Node<K> {
	V value;
};

template <typename K, typename V>
class Map {
public:
	void insert(K key, V value);
	void remove(K key);

private:
	AVL_Tree<K>* tree;
};