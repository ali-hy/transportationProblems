#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum DIRECTION
{
	row,
	col
};

template<class T>
int indexOfMax(vector<T> arr) {
	if (arr.empty()) return -1;
	int max = 0;
	for (int i = 1; i < arr.size(); i++) {
		max = arr[i] > arr[max] ? i : max;
	}
	return max;
}

int sum(vector<int> arr) {
	int result = 0;
	for (int number : arr) {
		result += number;
	}
	return result;
}

template<class T>
vector<T> getColumn(vector<vector<T>>const& table, int colNumber) {
	vector<T> col;
	for (int i = 0; i < table.size(); i++) {
		col.push_back(table[i][colNumber]);
	}
	return col;
}

/// <summary>
/// Find the 2 smallest values in an array
/// </summary>
/// <param name="arr"> - vector of ints</param>
/// <returns>pair of the two smallest ints</returns>
pair<int, int> findMin2(vector<int> const& arr) {
	if (arr.empty()) { return make_pair(-1, -1); }
	if (arr.size() < 2) { return make_pair(0, 0); }
	pair<int, int> min2 = make_pair(0, 1);
	for (int i = 0; i < arr.size(); i++) {
		if (arr[i] < arr[min2.first]) {
			min2.second = min2.first;
			min2.first = i;
		}
		else if (arr[i] < arr[min2.second]) {
			min2.second = i;
		}
	}
	return min2;
}