#include "Set.h"


template <typename K>
Set<K>::Set() {
	tree = new AVL_Tree<K>();
}

template <typename K>
void Set<K>::insert(K key) {
	tree->insert(key);
}

template <typename K>
void Set<K>::remove(K key) {
	tree->remove(key);
}

template <typename K>
bool Set<K>::contains(K key) {
	return tree->contains(key); 
}

template <typename K>
bool Set<K>::is_empty() {
	return tree->is_empty();
}

template <typename K>
int Set<K>::size() {
	return tree->size();
}