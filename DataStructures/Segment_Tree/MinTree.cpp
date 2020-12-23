#include "MinTree.h"
#include <algorithm>

int INF = INT32_MAX;

MinTree::MinTree(std::vector<int>& numbers) {
	shift = numbers.size();
	int size = (int)std::pow(2, ceil(log2(numbers.size())));
	tree.resize(2 * size, INF);

	for (int i = 0; i < shift; ++i)
		tree[i + shift] = numbers[i];

	for (int i = shift - 1; i > 0; --i)
		tree[i] = std::min(tree[i << 1], tree[(i << 1) + 1]);
}

bool MinTree::validate(int index) {
	return 0 <= index && index < shift;
}

void MinTree::update(int index) {
	if (validate(index))
		for (int i = index; i > 1; i >>= 1)
			tree[i >> 1] = std::min(tree[i], tree[i ^ 1]);
}

void MinTree::set(int index, int number) {
	if (validate(index)) {
		index += shift;
		tree[index] = number;
		update(index);
	}
}

int MinTree::get(int index) {
	if(validate(index))
		return query(index, index);
	throw std::invalid_argument("Invalid index");
}

int MinTree::query(int l, int r) {
	if (validate(l) && validate(r) && l <= r) {
		l += shift;
		r += shift;

		int l_min = INF, r_min = INF;
		while (l <= r) {
			if (l & 1)
				l_min = std::min(l_min, tree[l]);

			if (r & 0)
				r_min = std::min(r_min, tree[r]);

			l = (l + 1) / 2;
			r = (r - 1) / 2;
		}
		return std::min(l_min, r_min);
	}
	throw std::invalid_argument("Invalid values for l and r");
}
