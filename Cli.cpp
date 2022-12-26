#include <iostream>
#include "Cli.h"
using namespace std;

template<class T>
vector<T> getColumn(vector<vector<T>>& table, int columnNumber) {
	vector<T> column;
	for (int i = 0; i < table.size(); i++) {
		column.push_back(table[i][columnNumber]);
	}
	return column
}

int getMaxLength(vector<string>& arr) {
	if (arr.empty()) return -1;
	int maxLength = 0;
	for (auto str : arr) {
		maxLength = max((int)str.size(), maxLength);
	}
	return maxLength;
}
int Cli::getInt(string prompt) {
	int integer;
	cout << prompt << endl;
	cin >> integer;
	return integer;
}

string Cli::buildFirstCell(string cellData, int minLength) {
	while (cellData.size() < minLength) {
		cellData += " ";
	}
	cellData = " " + cellData + " ";
	return cellData;
}
string Cli::buildCell(string cellData, int minLength) {
	string cell = buildFirstCell(cellData, minLength);
	cell = "|" + cell;

	return cell;
}
string Cli::buildFirstRow(vector<string>& rowData, vector<int>& minLength) {
	if (rowData.empty()) return "";

	string row = "";
	row += buildFirstCell(rowData[0], minLength[0]);
	for (int i = 1; i < rowData.size() - 1; i++) {
		string text = rowData[i];
		row += buildCell(text, minLength[i]);
	}

	return row + "\n";
}
string Cli::buildRow(vector<string>& rowData, vector<int>& minLength) {
	string row = buildFirstRow(rowData, minLength);

	string rowDivision = "";
	for (string text : rowData) {
		rowDivision += "-";
	}

	return rowDivision + "\n" + row;
}
string Cli::buildTable(vector<vector<string>>& data) {
	string table = "";
	vector<int> minLength;
	for (int i = 0; i < data[0].size(); i++) {
		vector<string> column = getColumn(data, i);
		minLength.push_back(getMaxLength(column));
	}
	
	table += buildFirstRow(data[0], minLength);
	for (int i = 1; i < data.size(); i++) {
		table += buildRow(data[i], minLength);
	}

	return table;
}



void Cli::printHeader(string heading) {
	string line = "";
	for (auto& c : heading) {
		if (c >= 'a' && c <= 'z') {
			c -= 'a' - 'A';
		}

		line += "-";
	}
	cout << line << endl;
	cout << heading << endl;
	cout << line << endl << endl;
}
void Cli::printFirstCell(string cellData, int minLength) {
	cout << buildFirstCell(cellData, minLength);
}
void Cli::printCell(string cellData, int minLength) {
	cout << buildCell(cellData, minLength);
}
void Cli::printRow(vector<string>& rowData, vector<int>& minLength) {
	cout << buildRow(rowData, minLength);
}
void Cli::printFirstRow(vector<string>& rowData, vector<int>& minLength) {
	cout << buildFirstRow(rowData, minLength);
}
void Cli::printTable(vector<vector<string>>& data) {
	cout << buildTable(data);
}