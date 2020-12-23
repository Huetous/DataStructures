#pragma once
#include "../pch.h"
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <iostream>

const int C = 4;
const int64_t PRIME = 2000000011;
const int SHIFT = 1000000000;
const int EMPTY = -1;

class HashFunction {
public:
	explicit HashFunction(int64_t table_size, std::mt19937& gen);
	HashFunction() : a(1), b(0), table_size(0) {};

	unsigned int operator() (const int number) const {
		return ((a * number + b) % PRIME) % table_size;
	}

private:
	int64_t a, b, table_size;
};


class LocalTable {
public:
	bool Contains(const int number) const;
	void Initialize(const std::vector<int>& numbers, std::mt19937& gen);

private:
	HashFunction hash;
	std::vector<int> table;

	HashFunction get_hash_func(const std::vector<int>& numbers, std::mt19937& gen);
	bool is_suitable(const HashFunction& hash, const std::vector<int>& numbers);
};


class FixedSet {
public:
	bool Contains(int number) const;
	void Initialize(const std::vector<int>& numbers);

private:
	HashFunction hash;
	std::vector<LocalTable> table;

	HashFunction get_hash_func(const std::vector<int>& numbers, std::mt19937& gen);
	bool is_suitable(const HashFunction& hash, const std::vector<int>& numbers);

	std::vector<int> shift_numbers(std::vector<int> numbers);
	std::vector<std::vector<int>> fill_local_tables(const std::vector<int>& numbers);
};




