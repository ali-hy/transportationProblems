#include "TransportationProblemSolution.h"
#include "TransportationVariable.h"
#include "Cli.h"
#include "global.h"

//3 25 20 30 4 15 16 12 19 45 17 21 30 14 18 19 31 12 16 18 24

TransportationProblemSolution::TransportationProblemSolution(vector<vector<int>>& costs) : 
costs(costs) {
	cout << "constructing solution \n";
	quantities.resize(costs.size());
	for (auto& row : quantities) {
		row.resize(costs[0].size());
	}
}

void TransportationProblemSolution::autoSetBasicVariables() {
	basicVariables = vector<TransportationVariable>();
	for (int i = 0; i < quantities.size(); i++) {
		vector<int> row = quantities[i];
		for (int j = 0; j < row.size(); j++) {
			int quantity = row[j];
			if (quantity > 0) {
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
	int netCost = 0;
	for (auto var : basicVariables) {
		netCost += getQuantity(var) * getCost(var);
	}
	return netCost;
}

void TransportationProblemSolution::setQuantity(TransportationVariable route, int quantity) {
	quantities[route.source][route.destination] = quantity;
}

vector<vector<string>> TransportationProblemSolution::toTableData() {
	vector<vector<string>> tableData;
	//header row
	vector<string> headerRow({ "" });
	for (int i = 0; i < quantities[0].size(); i++) {
		headerRow.push_back("D" + to_string(i + 1));
	}
	tableData.push_back(headerRow);
	//body
	for (int i = 0; i < quantities.size(); i++) {
		vector<string> row;
		row.push_back("S" + to_string(i + 1));
		for (int j = 0; j < quantities[i].size(); j++) {
			row.push_back(to_string(quantities[i][j]));
		}
		tableData.push_back(row);
	}
	cout << "TABLE DATA GENERATED\n";
	return tableData;
}
void TransportationProblemSolution::display() {
	Cli cli;
	//cli.clear();
	cli.printHeader("solution");
	cli.printTable(toTableData());

	autoSetBasicVariables();
	cout << endl << "basic variables: " << endl;\
	for (auto bv : basicVariables) {
		cout << bv.toString() << endl;
	}
	cout << "NET cost: $" << getNetCost();
}
