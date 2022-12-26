#pragma once
#include <string>
#include <vector>
using namespace std;

class Cli
{
public:
	//Input
	int getInt(string prompt = "");

	//String building
	string buildFirstCell(string cellData, int minLength = 0);
	string buildCell(string cellData, int minLength = 0);
	string buildFirstRow(vector<string>& rowData, vector<int>& minLength);
	string buildRow(vector<string>& rowData, vector<int>& minLength);
	string buildTable(vector<vector<string>>& data);

	//Output
	void printHeader(string heading);
	void printFirstCell(string cellData, int minLength = 0);
	void printCell(string cellData, int minLength = 0);
	void printFirstRow(vector<string>& rowData, vector<int>& minLength);
	void printRow(vector<string>& rowData, vector<int>& minLength);
	void printTable(vector<vector<string>>& data);
};

