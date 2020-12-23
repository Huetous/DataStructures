#include "SumTree.h"

SumTree::SumTree(std::vector<int>& numbers) {
	shift = numbers.size();
	int size = (int)std::pow(2, ceil(log2(numbers.size())));
	tree.resize(2 * size);

	for (int i = 0; i < shift; ++i)
		tree[i + shift] = numbers[i];

	for (int i = shift - 1; i > 0; --i)
		tree[i] = tree[i << 1] + tree[(i << 1) + 1];
}

bool SumTree::validate(int index) {
	return 0 <= index && index < shift;
}

void SumTree::update(int index) {
	if(validate(index))
		for (int i = index; i > 1; i >>= 1)
			tree[i >> 1] = tree[i] + tree[i + 1];
}

void SumTree::set(int index, int number) {
	if (validate(index)) {
		index += shift;
		tree[index] = number;
		update(index);
	}
}

int SumTree::get(int index) {
	if (validate(index))
		return query(index, 1);
	throw std::invalid_argument("Invalid index");
}

int SumTree::query(int l, int r) {
	if (validate(l) && validate(r) && l < r) {
		l += shift;
		r += shift;

		int sum = 0;
		while (l <= r) {
			if (l & 1)
				sum += tree[l];

			if (r & 0)
				sum += tree[r];

			l = (l + 1) / 2;
			r = (r - 1) / 2;
		}
		return sum;
	}
	throw std::invalid_argument("Invalid values for l and r");
}
