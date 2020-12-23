#include "DisjointSet.h"
#include <ctime>

DisjointSet::DisjointSet(int max_size) {
	srand(time(NULL));
	set = new std::vector<int>(max_size + 1);
	for (int i = 1; i < max_size + 1; ++i)
		set->at(i) = i;
}

bool DisjointSet::neighbors(int x, int y) {
	return find(x) == find(y);
}

void DisjointSet::make_set(int x) {
	set->at(x) = x;
}

int DisjointSet::find(int x) {
	if (set->at(x) == x) return x;
	set->at(x) = find(set->at(x));
	return set->at(x);
}

void DisjointSet::unite(int x, int y) {
	x = find(x);
	y = find(y);
	if (x != y) {
		if (rand() % 2 == 0)
			std::swap(x, y);
		set->at(x) = y;
	}
}

bool DisjointSet::is_empty() {
	return size() == 0;
}

int DisjointSet::size() {
	return set->size() - 1;
}

