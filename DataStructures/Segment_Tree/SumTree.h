#pragma once
#include <vector>

class SumTree {
public:
	SumTree(std::vector<int>& numbers);
	void set(int index, int number);
	int query(int l, int r);
	int get(int index);

private:
	int shift;
	std::vector<int> tree;

	void update(int index);
	bool validate(int index);
};

