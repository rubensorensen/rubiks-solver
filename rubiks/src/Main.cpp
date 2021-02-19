#include <iostream>
#include <string>
#include <bitset>
#include "Cube.h"

int main(void) {
	Cube* cube = new Cube();
	cube->PrintVals();
	cube->ShowCube();
	cube->B();
	std::cout << std::endl;
	cube->PrintVals();
	cube->ShowCube();
	cube->B();
	std::cout << std::endl;
	cube->PrintVals();
	cube->ShowCube();
	cube->B();
	std::cout << std::endl;
	cube->PrintVals();
	cube->ShowCube();
	cube->B();
	std::cout << std::endl;
	cube->PrintVals();
	cube->ShowCube();
	
	std::cin.get();
	delete cube;
	return 0;
}