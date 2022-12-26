#pragma once
#include <vector>
#include <string>
#include "TransportationProblemSolution.h"
using namespace std;

//class implementation in TransportationProblem.cpp
class TransportationProblem
{
	vector<int> sources;
	vector<int> destinations;

	vector<vector<int>> costs;
	int maxCostLength = 0;

public:
	void getUserInput();

	vector<int> getSources();
	vector<int> getDestinations();

	TransportationProblemSolution solveWithNorthWest();
	TransportationProblemSolution solveWithVogelApproximation();

	string toString();
	void display();
};

