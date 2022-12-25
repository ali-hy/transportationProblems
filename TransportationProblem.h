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

	void getUserInput();

	TransportationProblemSolution solveWithNorthWest();
	TransportationProblemSolution solveWithVogelApproximation();

	string toString();
};

