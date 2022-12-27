#pragma once
#include <vector>
#include <string>
#include "TransportationVariable.h"
using namespace std;

//class implementation in TransportationProblemSolution.cpp
class TransportationProblemSolution
{
	vector<vector<int>>& costs;
public: 
	vector<vector<int>> quantities;
	vector<TransportationVariable> basicVariables; //holds the position of the basic variables
	vector<TransportationVariable> nonBasicVariables;	//holds the position of the non-basic variables

	TransportationProblemSolution(vector<vector<int>>& costs);

	void autoSetBasicVariables();
	void autoSetNonBasicVariables();
	
	int getCost(TransportationVariable var);
	int getQuantity(TransportationVariable var);
	int getNetCost();

	void optimize();

	vector<vector<string>> toTableData();
};

