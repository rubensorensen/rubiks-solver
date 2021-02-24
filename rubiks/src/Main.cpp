#include <iostream>
#include <string>
#include <bitset>
#include "Cube.h"

int main(void) {
	Cube* cube = new Cube();
	cube->ShowCube();
	std::cout << "---------------------------\n" << std::endl;

	cube->R2();
	cube->L2();
	cube->F2();
	cube->B2();
	cube->U2();
	cube->D2();
	
	cube->ShowCube();

	std::cin.get();
	delete cube;
	
	return 0;
}