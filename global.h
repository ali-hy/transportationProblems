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
inline int indexOfMax(vector<T> arr) {
	if (arr.empty()) return -1;
	int max = 0;
	for (int i = 1; i < arr.size(); i++) {
		max = arr[i] > arr[max] ? i : max;
	}
	return max;
}

template<class T>
inline int indexOfMin(vector<T> arr) {
	if (arr.empty()) return -1;
	int min = 0;
	for (int i = 1; i < arr.size(); i++) {
		min = arr[i] < arr[min] ? i : min;
	}
	return min;
}

template<class T>
inline vector<T> getColumn(vector<vector<T>>const& table, int colNumber) {
	vector<T> col;
	for (int i = 0; i < table.size(); i++) {
		col.push_back(table[i][colNumber]);
	}
	return col;
}

inline int sum(vector<int> arr) {
	int result = 0;
	for (int number : arr) {
		result += number;
	}
	return result;
}


inline pair<int, int> findMin2(vector<int> const& arr) {
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
	if (arr[min2.first] != INT_MAX && arr[min2.second] != INT_MAX) {
		return min2;
	}
	if (arr[min2.first] == INT_MAX && arr[min2.second] == INT_MAX) {
		return make_pair(-1, -1);
	}
	return arr[min2.first] == INT_MAX ? make_pair(min2.second, min2.second) : make_pair(min2.first, min2.first);
}