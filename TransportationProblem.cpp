#include "TransportationProblem.h"
#include "Cli.h"
#include <algorithm>
#include <math.h>
#include <iostream>
using namespace std;

int sum(vector<int> arr) {
	int result = 0;
	for (int number : arr) {
		result += number;
	}
	return result;
}


// INPUT AND OUTPUT
void TransportationProblem::getUserInput() {
	Cli cli;
	//Get source details
	cli.printHeader("Sources");
	int numOfSources = cli.getInt("Please enter the number of sources:");
	for (int i = 0; i < numOfSources; i++) {
		int supply = cli.getInt("Enter the Source" + to_string(i + 1) + "'s supply:");
		sources.push_back(supply);
	}
	system("cls");
	//Get destination details
	cli.printHeader("Destinations");
	int numOfDestinations = cli.getInt("Please enter the number of destinations:");
	for (int i = 0; i < numOfDestinations; i++) {
		int demand = cli.getInt("Enter Destination" + to_string(i + 1) + "'s demand:");
		destinations.push_back(demand);
	}
	system("cls");
	//Prepare costs array
	costs = vector<vector<int>>(numOfSources);
	//Get cost details
	for (int source = 0; source < numOfSources; source++) {
		cli.printHeader("Costs");
		cout << "Enter transportation cost from Source" << source + 1 << " to:" << endl;
		for (int destination = 0; destination < numOfDestinations; destination++) {
			int cost = cli.getInt("\tDestination" + to_string(destination + 1));
			costs[source].push_back(cost);
		}
		system("cls");
	}
}
vector<vector<string>> TransportationProblem::toTableData() {
	vector<vector<string>> tableData;

	//make header row
	vector<string> headerRow = {""};
	for (int i = 0; i < destinations.size(); i++) {
		headerRow.push_back("D" + to_string(i + 1));
	}
	headerRow.push_back("Supply");
	tableData.push_back(headerRow);

	//make rest of table
	for (int i = 0; i < sources.size(); i++) {
		vector<string> row;
		row.push_back("S" + to_string(i + 1));
		for (int cost : costs[i]) {
			row.push_back(to_string(cost));
		}
		row.push_back(to_string(sources[i]));
		tableData.push_back(row);
	}

	vector<string> demandRow;
	demandRow.push_back("Demand");
	for (int demand : destinations) {
		demandRow.push_back(to_string(demand));
	}
	demandRow.push_back("");
	tableData.push_back(demandRow);

	return tableData;
}
void TransportationProblem::display() {
	Cli cli;

	cli.printHeader("the problem");

	vector<vector<string>> tableData = toTableData();
	cli.printTable(toTableData());
}

//SOLVING
void TransportationProblem::balanceProblem() {
	
}
//TransportationProblemSolution TransportationProblem::solveWithNorthWest() {
//
//}
