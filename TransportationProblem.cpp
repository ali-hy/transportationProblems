#include "TransportationProblem.h"
#include "Cli.h"
#include "VogelData.h"
#include "global.h"
using namespace std;

//3 25 20 30 4 15 16 12 19 45 17 21 30 14 18 19 31 12 16 18 24

//INPUT AND OUTPUT
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
void TransportationProblem::promptSolve() {
	Cli cli;
	cli.clear();
	cli.printHeader("solution");
	char chosenMethod = cli.getChar("Define the method you'd prefer for solving (n for north-west, v for vogel): ");
	TransportationProblemSolution* solution = NULL;
	if (chosenMethod == 'n') {
		solution = new TransportationProblemSolution(solveWithNorthWest());
		solution->display();
	}
	else if (chosenMethod == 'v') {
		solution = new TransportationProblemSolution(solveWithVogelApproximation());
		//cout << "vogel solution not implemented";
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
	//cli.clear();
	cli.printHeader("the problem");
	cli.printTable(toTableData());
	cout << endl;
}

//GETTERS AND GETTERS
int TransportationProblem::getSupply(TransportationVariable route) {
	return sources[route.source];
}
int TransportationProblem::getDemand(TransportationVariable route) {
	return destinations[route.destination];
}

void TransportationProblem::reduceSupply(TransportationVariable route, int change) {
	sources[route.source] -= change;
}
void TransportationProblem::reduceDemand(TransportationVariable route, int change) {
	destinations[route.destination] -= change;
}


//SOLVING
void TransportationProblem::balanceProblem() {
	int netSupply = sum(sources);
	int netDemand = sum(destinations);

	int difference = netSupply - netDemand;

	if (!difference) return;

	if (difference > 0) {
		addDummyDestination(difference);
	}
	else {
		addDummyDestination(-difference);
	}
}
void TransportationProblem::addDummyDestination(int demand) {
	destinations.push_back(demand);
	for (int i = 0; i < costs.size(); i++) {
		costs[i].push_back(0);
	}
	dummyDestinationExists = true;
}
void TransportationProblem::addDummySource(int supply) {
	sources.push_back(supply);
	costs.push_back(vector<int>(5));
	dummySourceExists = true;
}


// north-west
TransportationProblemSolution TransportationProblem::solveWithNorthWest() {
	balanceProblem();
	TransportationProblemSolution solution(costs);
	TransportationVariable currentRoute(0, 0);
	
	bool keepgoing = true;
	while (keepgoing) {
		auto doneWith = abuseRoute(currentRoute,solution);
		switch (doneWith.first) {
		case row:
			currentRoute.source++;
			break;
		case col:
			currentRoute.destination++;
			break;
		default:
			cout << "ouch";
		}
		keepgoing = currentRoute.source < sources.size() && currentRoute.destination < destinations.size();
	}

	return solution;
}

// vogel
TransportationProblemSolution TransportationProblem::solveWithVogelApproximation() {
	balanceProblem();

	TransportationProblemSolution solution(costs);
	VogelData vogelData(costs);

	display();
	vogelData.display();

	bool keepgoing = true;
	int n = 4;
	while (n--) {
		keepgoing = vogelStep(solution, vogelData);
		vogelData.display();
	}

	solution.display();
	display();

	return solution;
}

bool TransportationProblem::vogelStep(TransportationProblemSolution &solution, VogelData &vogelData){
	pair<TransportationVariable, int> bestRoute = vogelData.getBestRoute();
	if (bestRoute.second < 0) return false;
	pair<DIRECTION, int> toClose = abuseRoute(bestRoute.first, solution);
	vogelData.close(toClose);
	return true;
}


/* -------- FOR BOTH ALGORITHMS ------- */
pair<DIRECTION, int> TransportationProblem::abuseRoute(TransportationVariable route, TransportationProblemSolution& solution) {
	cout << "abusing " << route.toString() << endl;
	int quantity = min(getSupply(route), getDemand(route));

	reduceSupply(route, quantity);
	reduceDemand(route, quantity);

	solution.setQuantity(route, quantity);

	DIRECTION direction = row;
	int n = -1;

	if (!getSupply(route)) {
		n = route.source;
	}
	else {
		direction = col;
		n = route.destination;
	}

	return make_pair(direction, n);
}