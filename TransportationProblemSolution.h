#pragma once
#include <vector>
#include <string>
#include "TransportationVariable.h"
using namespace std;

//class implementation in TransportationProblemSolution.cpp
class TransportationProblemSolution
{
public: 
	vector<vector<int>> quantities;
	vector<TransportationVariable> basicVariables; //holds the position of the basic variables
	vector<TransportationVariable> nonBasicVariables;	//holds the position of the non-basic variables

	TransportationProblemSolution(vector<vector<int>> quantities);

	void autoSetBasicVariables();	//
	void autoSetNonBasicVariables();

	void optimize();

	string toString();
};

