#include "TransportationProblem.h"
#include "Input.h"

void TransportationProblem::getUserInput() {
	Input input;
	//Get source details
	int numOfSources = input.getInt("Please enter the number of sources");
	for (int i = 0; i < numOfSources; i++) {
		int supply = input.getInt("Please enter the Source" + to_string(i + 1) + "'s supply");
		this->sources.push_back(supply);
	}
	//Get destination details
	int numOfDestinations = input.getInt("Please enter the number of destinations");
	for (int i = 0; i < numOfSources; i++) {
		int demand = input.getInt("Please enter Destination" + to_string(i + 1) + "'s demand");
		this->destinations.push_back(demand);
	}
	//Get cost details
	for (int source = 0; source < numOfSources; source++) {
		for (int destination = 0; destination < numOfDestinations; destination++) {
			int cost = input.getInt("Please enter the cost of transportation from Source" + to_string(source + 1) + " to Destination" + to_string(destination + 1));
			this->costs[source].push_back(cost);
		}
	}
}