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
	
	//TransportationProblemSolution vogelSolution;

public:
	void getUserInput();

	vector<int> getSources();
	vector<int> getDestinations();
	vector<vector<int>> getCosts();

	// Problem Preparation
	void balanceProblem();
	void addDummyDestination(int demand);
	void addDummySource(int supply);

	//North West
	TransportationProblemSolution solveWithNorthWest();

	//Vogel Approximation
	TransportationProblemSolution solveWithVogelApproximation();
	void vogelStep();

	vector<vector<string>> toTableData();
	void display();
};

