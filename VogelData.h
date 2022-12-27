#pragma once
#include <set>
#include "TransportationVariable.h";
#include "global.h"
using namespace std;

class VogelData
{
	vector<vector<int>>& costs;

	set<int> closedRows;
	set<int> closedColumns;

	vector<int> rowPriorities;
	vector<int> colPriorities;

	void updateRowPriority(int n);
	void updateColPriority(int n);

	void updateRowPriorities();
	void updateColPriorities();
	void updatePriorities();

	pair<DIRECTION, int> topPriority;
	void autoSetTopPriority();

	vector<pair<int, int>> rowMins;
	vector<pair<int, int>> colMins;

	void autoSetRowMins();
	void autoSetColMins();
	void autoSetMins();

	vector<int> rowWithoutClosed(int n);
	vector<int> colWithoutClosed(int n);

	void updateRowMin2(int n);
	void updateColMin2(int n);
public:
	VogelData(vector<vector<int>>& costs);

	void closeRow(int n);
	void closeColumn(int n);
	void close(pair<DIRECTION, int> toClose);

	void updateTopPriority();
	TransportationVariable topPriorityMinCost();
};

