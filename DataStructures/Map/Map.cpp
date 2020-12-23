#include "Map.h"

template <typename K, typename V>
Map<K, V>::Map() {
	tree = new AVL_Tree<K, V>();
}

template <typename K, typename V>
void Map<K, V>::insert(K key, V value) {
	tree->insert(key, value);
}

template <typename K, typename V>
void Map<K, V>::remove(K key) {
	tree->remove(key);
}

template <typename K, typename V>
bool Map<K, V>::is_empty() {
	return tree->is_empty();
}

template <typename K, typename V>
int Map<K, V>::size() {
	return tree->size();
}

template <typename K, typename V>
V Map<K, V>::find(K key) {
	return tree->find(key);
}