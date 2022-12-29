#include "VogelData.h"
#include "global.h"
#include "Cli.h"
using namespace std;

VogelData::VogelData(vector<vector<int>>& costs){
	for (int i = 0; i < costs.size(); i++) {
		vector<int> row = costs[i];
		costsWithoutClosed.push_back(vector<pair<bool,int>> ());
		for (int cost : row) {
			costsWithoutClosed[i].push_back(make_pair(true, cost));
		}
	}
}

int VogelData::getColPriority(int n) {
	vector<pair<bool, int>> col = getColumn(costsWithoutClosed, n);

	return getMinsDif(col);
}
int VogelData::getRowPriority(int n) {
	vector<pair<bool, int>> row = costsWithoutClosed[n];
	
	return getMinsDif(row);
}

vector<int> VogelData::getColsPriorities() {
	vector<int> colsPriorities;
	for (int i = 0; i < costsWithoutClosed[0].size(); i++) {
		//cout << "col" << i << ": ";
		colsPriorities.push_back(getColPriority(i));
	}
	return colsPriorities;
}
vector<int> VogelData::getRowsPriorities() {
	vector<int> rowsPriorities;
	for (int i = 0; i < costsWithoutClosed.size(); i++) {
		//cout << "row" << i << ": ";
		rowsPriorities.push_back(getRowPriority(i));
	}
	return rowsPriorities;
}

pair<TransportationVariable, int> VogelData::getBestRoute() {
	auto rowsPriorities = getRowsPriorities();
	auto colsPriorities = getColsPriorities();
	int rowMax = indexOfMax(rowsPriorities);
	int colMax = indexOfMax(colsPriorities);

	if (rowsPriorities[rowMax] < 0 && colsPriorities[colMax] < 0) return make_pair(TransportationVariable(-1, -1), -1);
	if (rowsPriorities[rowMax] > colsPriorities[colMax]) {
		int col = indexOfMin(costsWithoutClosed[rowMax]);
		return make_pair(TransportationVariable(rowMax, col), max(rowsPriorities[rowMax], colsPriorities[colMax]));
	} else {
		int row = indexOfMin(getColumn(costsWithoutClosed, rowMax));
		return make_pair(TransportationVariable(row, colMax), max(rowsPriorities[rowMax], colsPriorities[colMax]));
	}
}

int VogelData::getMinsDif(vector<pair<bool, int>> arr) {
	int smallest = INT_MAX, smallest2 = INT_MAX - 1;
	for (auto i : arr) {
		if (!i.first) continue;
		if (i.second < smallest) {
			smallest2 = smallest;
			smallest = i.second;
		}
		else if (i.second < smallest2) {
			smallest2 = i.second;
		}
	}
	if (smallest < INT_MAX && smallest2 == INT_MAX) {
		return 0;
	}
	//cout << smallest2 << " - " << smallest << endl;
	return smallest2 - smallest;
}

void VogelData::closeColumn(int n) {
	if (closedColumns.count(n)) cout << "closing a closed column" << endl;
	closedColumns.insert(n);
	for (int i = 0; i < costsWithoutClosed.size(); i++) {
		costsWithoutClosed[i][n].first = false;
	}
}
void VogelData::closeRow(int n) {
	if (closedRows.count(n)) cout << "closing a closed row" << endl;
	closedRows.insert(n);
	for (int i = 0; i < costsWithoutClosed[0].size(); i++) {
		costsWithoutClosed[n][i].first = false;
	}
}
void VogelData::close(pair<DIRECTION, int> toClose) {
	if (toClose.first == row) {
		closeRow(toClose.second);
	}
	else {
		closeColumn(toClose.second);
	}
}

vector<vector<string>> VogelData::toTableData() {
	const int height = costsWithoutClosed.size();
	const int width = costsWithoutClosed[0].size();
	vector<vector<string>> tableData;
	//header row
	vector<string> headerRow({""});
	for (int i = 0; i < width; i++) {
		headerRow.push_back("D" + to_string(i + 1));
	}
	headerRow.push_back("Difference");
	tableData.push_back(headerRow);
	//body rows
	for (int i = 0; i < height; i++) {
		vector<string> row;
		row.push_back("S" + to_string(i + 1));
		for (int j = 0; j < width; j++) {
			auto cost = costsWithoutClosed[i][j];
			row.push_back(cost.first ? to_string(cost.second) : "--");
		}
		row.push_back(to_string(getRowPriority(i)));
		tableData.push_back(row);
	}
	//footer row
	vector<string> footerRow({ "Difference" });
	for (int i = 0; i < width; i++) {
		footerRow.push_back(to_string(getColPriority(i)));
	}
	auto br = getBestRoute();
	footerRow.push_back( br.first.toString() + " " +to_string(br.second));
	tableData.push_back(footerRow);
	return tableData;
}
void VogelData::display() {
	Cli cli;
	cli.printHeader("vogel tableau");
	cli.printTable(toTableData());
}

//void VogelData::closeRow(int n) {
//	closedRows.insert(n);
//	cout << "rowMins.size(): " << rowMins.size() << endl;
//	rowMins[n] = make_pair(-1, -1);
//	for (int i = 0; i < costsWithoutClosed[0].size(); i++) {
//		costsWithoutClosed[n][i] = INT_MAX;
//	}
//	updateRowPriority(n);
//	autoSetTopPriority();
//	for (int i = 0; i < colMins.size(); i++) {
//		pair<int, int> mins = colMins[i];
//		if (mins.first == n || mins.second == n) {
//			updateColMin2(i);
//			updateColPriority(i);
//		}
//	}
//}
//void VogelData::closeColumn(int n) {
//	closedColumns.insert(n);
//	colMins[n] = make_pair(-1, -1);
//	for (int i = 0; i < costsWithoutClosed.size(); i++) {
//		costsWithoutClosed[i][n] = INT_MAX;
//	}
//	updateColPriority(n);
//	autoSetTopPriority();
//	for (int i = 0; i < rowMins.size(); i++) {
//		pair<int, int> mins = rowMins[i];
//		if (mins.first == n || mins.second == n) {
//			updateRowMin2(i);
//		}
//	}
//}
//void VogelData::close(pair<DIRECTION, int> toClose) {
//	switch (toClose.first){
//	case row:
//		cout << "closing row" << endl;
//		closeRow(toClose.second);
//		break;
//	case col:
//		cout << "closing col " << toClose.second << endl;
//		closeColumn(toClose.second);
//		break;
//	default:
//		throw "ERORRRRRR: direction can only be row or col... wth???";
//	}
//}
//
//void VogelData::autoSetRowMins() {
//	if (!rowMins.empty()) throw "ERORR: rowMins has already been set";
//	for (auto& row : costsWithoutClosed) {
//		rowMins.push_back(findMin2(row));
//	}
//}
//void VogelData::autoSetColMins() {
//	if (!colMins.empty()) throw "ERORR: colMins has already been set";
//	for (int i = 0; i < costsWithoutClosed[0].size(); i++) {
//		vector<int> col = getColumn(costsWithoutClosed, i);
//		colMins.push_back(findMin2(col));
//	}
//}
//void VogelData::autoSetMins() {
//	try{
//		autoSetRowMins();
//		autoSetColMins();
//	}
//	catch (string error) {
//		cout << error << endl;
//	}
//}
//
//void VogelData::updateRowMin2(int n) {
//	rowMins[n] = findMin2(costsWithoutClosed[n]);
//}
//void VogelData::updateColMin2(int n) {
//	colMins[n] = findMin2(getColumn(costsWithoutClosed, n));
//}
//
//void VogelData::updateRowPriority(int n) {
//	if (rowMins[n].first < 0) {
//		rowPriorities[n] = -1; return; 
//	}
//	rowPriorities[n] = rowMins[n].second - rowMins[n].first;
//}
//void VogelData::updateColPriority(int n) {
//	if (colMins[n].first < 0) {
//		colPriorities[n] = 0;
//		return;
//	}
//	colPriorities[n] = colMins[n].second - colMins[n].first;
//}
//
//void VogelData::updateRowPriorities() {
//	if(rowPriorities.size() != rowMins.size()) rowPriorities.resize(rowMins.size());
//	for (int i = 0; i < rowPriorities.size(); i++) {
//		updateRowPriority(i);
//	}
//}
//void VogelData::updateColPriorities() {
//	if(colPriorities.size() != colMins.size()) colPriorities.resize(colMins.size());
//	for (int i = 0; i < colPriorities.size(); i++) {
//		updateColPriority(i);
//	}
//}
//void VogelData::updatePriorities() {
//	updateColPriorities();
//	updateRowPriorities();
//}
//
//void VogelData::autoSetTopPriority() {
//	int colsPriority = indexOfMax(colPriorities);
//	int rowsPriority = indexOfMax(rowPriorities);
//
//	if (colsPriority < 0 && rowsPriority >= 0) {
//		topPriority = make_pair(row, rowsPriority);
//		return;
//	}
//	if (rowsPriority < 0 && colsPriority >= 0) {
//		topPriority = make_pair(col, colsPriority);
//		return;
//	}
//
//	topPriority = colPriorities[colsPriority] > rowPriorities[rowsPriority] ? 
//		topPriority = make_pair(col, colsPriority) :
//		topPriority = make_pair(row, rowsPriority);
//}
//void VogelData::updateTopPriority() {
//	updatePriorities();
//	autoSetTopPriority();
//}
//TransportationVariable VogelData::topPriorityMinCost() {
//	if (topPriority.first == row) {
//		return TransportationVariable(topPriority.second, rowMins[topPriority.second].first);
//	}
//	else if (topPriority.first == col) {
//		return TransportationVariable(colMins[topPriority.second].first, topPriority.second);
//	}
//	else {
//		cout << "ERORR: direction can only be row or col" << endl;
//	}
//}
//
//int VogelData::getTopPriority(){
//	int n = topPriority.second;
//	if (topPriority.first == row) {
//		return rowPriorities[n];
//	}
//	else{
//		return colPriorities[n];
//	}
//}