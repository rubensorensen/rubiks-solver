#include <iostream>
#include <string>
#include "Cube.h"

int main(void) {
	Cube::showSolved();
	Cube* cube = new Cube();

	cube->printVals();

	return 0;
}