#pragma once
#include <vector>

class DisjointSet {
public:
	DisjointSet(int size);

	void unite(int x, int y);
	void make_set(int x);
	bool neighbors(int x, int y);

	bool is_empty();
	int size();

private:
	std::vector<int>* set;
	int find(int x);
};

