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
	bool dummySourceExists = false;
	bool dummyDestinationExists = false;

public:
	void getUserInput();

	vector<int> getSources();
	vector<int> getDestinations();
	vector<vector<int>> getCosts();

	void balanceProblem();
	void addDummyDestination(int demand);
	void addDummySource(int supply);

	TransportationProblemSolution solveWithNorthWest();
	TransportationProblemSolution solveWithVogelApproximation();

	vector<vector<string>> toTableData();
	void display();
};

