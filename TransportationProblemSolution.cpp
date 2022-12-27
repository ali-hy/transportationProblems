#include "TransportationProblemSolution.h"
#include "TransportationVariable.h"
#include "global.h"

TransportationProblemSolution::TransportationProblemSolution(vector<vector<int>>& costs) : 
costs(costs) {
	quantities.resize(costs.size());
	for (auto& row : quantities) {
		row.resize(costs[0].size());
	}
}

void TransportationProblemSolution::autoSetBasicVariables() {
	basicVariables = vector<TransportationVariable>();
	for (int i = 0; i < costs.size(); i++) {
		vector<int> row = costs[i];
		for (int j = 0; j < row.size(); j++) {
			int quantity = row[j];
			if (quantity) {
				basicVariables.push_back(TransportationVariable(i, j));
			}
		}
	}
}
void TransportationProblemSolution::autoSetNonBasicVariables() {
	nonBasicVariables = vector<TransportationVariable>();
	for (int i = 0; i < costs.size(); i++) {
		vector<int> row = costs[i];
		for (int j = 0; j < row.size(); j++) {
			int quantity = row[j];
			if (!quantity) {
				nonBasicVariables.push_back(TransportationVariable(i, j));
			}
		}
	}
}

int TransportationProblemSolution::getCost(TransportationVariable route) {
	return costs[route.source][route.destination];
}
int TransportationProblemSolution::getQuantity(TransportationVariable route) {
	return quantities[route.source][route.destination];
}
int TransportationProblemSolution::getNetCost() {
	int sum = 0;
	for (auto var : basicVariables) {
		sum += getQuantity(var);
	}
	return sum;
}

void TransportationProblemSolution::setQuantity(TransportationVariable route, int quantity) {
	quantities[route.source][route.destination] = quantity;
}