#pragma once
#include <set>
#include "global.h"
#include "TransportationVariable.h"
using namespace std;

class VogelData
{
	vector<vector<pair<bool, int>>> costsWithoutClosed;

	set<int> closedRows;
	set<int> closedColumns;

	vector<int> rowPriorities;
	vector<int> colPriorities;

	int getColPriority(int n);
	int getRowPriority(int n);
	int getMinsDif(vector<pair<bool, int>> arr);

	vector<int> getColsPriorities();
	vector<int> getRowsPriorities();


public:
	VogelData(vector<vector<int>>& costs);



	void closeRow(int n);
	void closeColumn(int n);
	void close(pair<DIRECTION, int> toClose);

	pair<TransportationVariable, int> getBestRoute();
	
	vector<vector<string>> toTableData();
	void display();
};