#include "TransportationVariable.h"
#include <string.h>
using namespace std;

TransportationVariable::TransportationVariable(int source, int destination) {
	this->source = source;
	this->destination = destination;
}

string TransportationVariable::toString() {
	return "(S" + to_string(source) + ", D" + to_string(destination) + ")";
}