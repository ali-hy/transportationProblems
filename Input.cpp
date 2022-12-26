#include <iostream>
#include "Input.h"
using namespace std;

int Input::getInt(string prompt) {
	int integer;
	cout << prompt << endl;
	cin >> integer;
	return integer;
}