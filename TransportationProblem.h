#pragma once
#include <vector>
#include <string>
#include "VogelData.h"
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

	int getSupply(TransportationVariable route);
	int getDemand(TransportationVariable route);
	
	//TransportationProblemSolution vogelSolution;

public:
	void getUserInput();
	void promptSolve();

	//vector<int> getSources();
	//vector<int> getDestinations();
	//vector<vector<int>> getCosts();

	void reduceSupply(TransportationVariable route, int change);
	void reduceDemand(TransportationVariable route, int change);

	// Problem Preparation
	void balanceProblem();
	void addDummyDestination(int demand);
	void addDummySource(int supply);
	pair<DIRECTION, int> abuseRoute(TransportationVariable route, TransportationProblemSolution& solution);

	//North West
	TransportationProblemSolution solveWithNorthWest();

	//Vogel Approximation
	TransportationProblemSolution solveWithVogelApproximation();
	void vogelStep(TransportationProblemSolution& solution, VogelData& vogelData);

	vector<vector<string>> toTableData();
	void display();
};

