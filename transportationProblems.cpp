// transportationProblems.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "global.h"
#include <iostream>
#include <vector>
#include <string>
#include "TransportationProblem.h"
using namespace std;

int main()
{
   TransportationProblem problem;
    problem.getUserInput();
    problem.display();

    problem.promptSolve();
}