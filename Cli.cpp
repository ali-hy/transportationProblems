#include <iostream>
#include "Cli.h"
#include "collectionManipulation.h"
using namespace std;


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
	cout << prompt << " ";
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
string Cli::buildFirstRow(vector<string>const & rowData, vector<int>& minLength) {
	if (rowData.empty()) return "";

	string row = "";
	row += buildFirstCell(rowData[0], minLength[0]);
	for (int i = 1; i < rowData.size(); i++) {
		string text = rowData[i];
		row += buildCell(text, minLength[i]);
	}

	return row + "\n";
}
string Cli::buildRow(vector<string>const & rowData, vector<int>& minLength) {
	string row = buildFirstRow(rowData, minLength);

	string rowDivision = "";
	for (auto text : row) {
		rowDivision += "-";
	}

	return rowDivision + "\n" + row;
}
string Cli::buildTable(vector<vector<string>>const & data) {
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
void Cli::printTable(vector<vector<string>>const &data) {
	cout << buildTable(data);
}