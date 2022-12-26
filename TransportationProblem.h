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

public:
	void getUserInput();

	vector<int> getSources();
	vector<int> getDestinations();
	vector<vector<int>> getCosts();

	void balanceProblem();
	TransportationProblemSolution solveWithNorthWest();
	TransportationProblemSolution solveWithVogelApproximation();

	vector<vector<string>> toTableData();
	void display();
};

