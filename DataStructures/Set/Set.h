#pragma once
#include "AVL_Tree.h"

template <typename T>
class Set {
public:
	void insert(T key);
	void contains(T key);

private:
	AVL_Tree<T>* tree;
};

