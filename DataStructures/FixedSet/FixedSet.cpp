#include "pch.h"
#include "FixedSet.h"

HashFunction::HashFunction(int64_t size, std::mt19937& gen) {
	std::uniform_int_distribution<> uid_a(1, PRIME - 1);
	std::uniform_int_distribution<> uid_b(0, PRIME - 1);
	a = uid_a(gen);
	b = uid_b(gen);
	table_size = size;
}


void LocalTable::Initialize(const std::vector<int>& numbers, std::mt19937& gen) {
	if (numbers.empty())
		return;

	table.resize(numbers.size() * numbers.size());
	hash = get_hash_func(numbers, gen);

	table.assign(table.size(), EMPTY);
	for (auto &number : numbers)
		table[hash(number)] = number;
}

bool LocalTable::Contains(const int number) const {
	if (table.empty())
		return false;
	return table[hash(number)] == number;
}

bool LocalTable::is_suitable(const HashFunction& hash, const std::vector<int>& numbers) {
	std::vector<int> hash_table(table.size(), EMPTY);

	for (auto &number : numbers) {
		if (hash_table[hash(number)] == EMPTY)
			hash_table[hash(number)] = number;
		else
			return false;
	}

	return true;
}

HashFunction LocalTable::get_hash_func(const std::vector<int>& numbers, std::mt19937& gen) {
	hash = HashFunction(table.size(), gen);
	while (!is_suitable(hash, numbers))
		hash = HashFunction(table.size(), gen);

	return hash;
}


std::vector<int> FixedSet::shift_numbers(std::vector<int> numbers) {
	std::for_each(numbers.begin(), numbers.end(), [](int &number) {
		number += SHIFT;
	});
	return numbers;
}

void FixedSet::Initialize(const std::vector<int>& numbers) {
	if (numbers.empty())
		return;

	std::vector<int> shifted_numbers = shift_numbers(numbers);
	std::mt19937 gen(time(0));

	table.resize(shifted_numbers.size());
	hash = get_hash_func(shifted_numbers, gen);

	std::vector<std::vector<int>> subsets = fill_local_tables(shifted_numbers);

	for (size_t i = 0; i < shifted_numbers.size(); ++i)
		table[i].Initialize(subsets[i], gen);
}

bool FixedSet::Contains(int number) const {
	if (table.size() == 0)
		return false;

	number += SHIFT;
	return table[hash(number)].Contains(number);
}

bool FixedSet::is_suitable(const HashFunction& hash, const std::vector<int>& numbers) {
	std::vector<int> local_tables_sizes(numbers.size());

	for (auto &number : numbers)
		local_tables_sizes[hash(number)]++;

	int64_t squared_sum = 0;
	for (auto &table_size : local_tables_sizes)
		squared_sum += table_size * table_size;

	return squared_sum <= C * numbers.size();
}

HashFunction FixedSet::get_hash_func(const std::vector<int>& numbers, std::mt19937& gen) {
	hash = HashFunction(numbers.size(), gen);
	while (!is_suitable(hash, numbers))
		hash = HashFunction(numbers.size(), gen);

	return hash;
}

std::vector<std::vector<int>> FixedSet::fill_local_tables(const std::vector<int>& numbers) {
	std::vector<std::vector<int>> subsets(numbers.size());

	for (auto &number : numbers)
		subsets[hash(number)].push_back(number);

	return subsets;
}