#pragma once
#include <string>
using namespace std;

//class implementation in TransportationVariable.cpp
class TransportationVariable
{
public:
	int source;
	int destination;

	TransportationVariable(int source, int destination);
	string toString();
};

