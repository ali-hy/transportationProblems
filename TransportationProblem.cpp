#include "TransportationProblem.h"
#include "Cli.h"
#include <algorithm>
#include <math.h>
#include <iostream>
using namespace std;

void TransportationProblem::getUserInput() {
	Input input;
	//Get source details
	cout << "SOURCES" << endl << "--------" << endl;
	int numOfSources = input.getInt("Please enter the number of sources");
	for (int i = 0; i < numOfSources; i++) {
		int supply = input.getInt("Please enter the Source" + to_string(i + 1) + "'s supply");
		sources.push_back(supply);
	}
	system("cls");
	//Get destination details
	cout << "DESTINATIONS" << endl << "-------------" << endl;
	int numOfDestinations = input.getInt("Please enter the number of destinations");
	for (int i = 0; i < numOfDestinations; i++) {
		int demand = input.getInt("Please enter Destination" + to_string(i + 1) + "'s demand");
		destinations.push_back(demand);
	}
	system("cls");
	//Prepare costs array
	costs = vector<vector<int>>(numOfSources);
	//Get cost details
	cout << "COSTS" << endl << "------" << endl;
	for (int source = 0; source < numOfSources; source++) {
		for (int destination = 0; destination < numOfDestinations; destination++) {
			int cost = input.getInt("Please enter the cost of transportation from Source" + to_string(source + 1) + " to Destination" + to_string(destination + 1));
			costs[source].push_back(cost);
			maxCostLength = max(maxCostLength, (int)log10(cost));
		}
	}
}

string TransportationProblem::toString() {
	string result = "";
	int maxSourceLength = sources.size() + 1;
	int maxDestinationLength = destinations.size() + 1;

	for (int i = 0; i < sources.size(); i++) {
		result +=  "S" + to_string(i) + ": " + to_string(sources[i]) + " ";
	}

	return result;
}

void TransportationProblem::display() {
	cout << toString();
}