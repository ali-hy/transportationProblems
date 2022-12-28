#pragma once
#include "global.h"
using namespace std;

class Cli
{
public:
	void clear() {
		system("cls");
	}

	//Input
	int getInt(string prompt = "");
	char getChar(string prompt = "");

	//String building
	string buildFirstCell(string cellData, int minLength = 0);
	string buildCell(string cellData, int minLength = 0);
	string buildFirstRow(vector<string>const & rowData, vector<int>& minLength);
	string buildRow(vector<string>const & rowData, vector<int>& minLength);
	string buildTable(vector<vector<string>>const & data);

	//Output
	void printHeader(string heading);
	void printFirstCell(string cellData, int minLength = 0);
	void printCell(string cellData, int minLength = 0);
	void printFirstRow(vector<string>& rowData, vector<int>& minLength);
	void printRow(vector<string>& rowData, vector<int>& minLength);
	void printTable(vector<vector<string>>const & data);
};

