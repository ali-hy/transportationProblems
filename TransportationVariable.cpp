#include "TransportationVariable.h"
#include <string>
using namespace std;

TransportationVariable::TransportationVariable(int source, int destination) {
	this->source = source;
	this->destination = destination;
}

string TransportationVariable::toString() {
	return "(S" + to_string(source + 1) + ", D" + to_string(destination + 1) + ")";
}