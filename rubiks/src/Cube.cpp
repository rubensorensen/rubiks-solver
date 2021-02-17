#include "Cube.h"
#include <iostream>
#include <string>
#include <bitset>

void Cube::showSolved() {
	const std::string sp = " ";
	std::cout << sp << "     " << sp << "Y Y Y" << sp << "     " << sp << "     " << std::endl;
	std::cout << sp << "     " << sp << "Y Y Y" << sp << "     " << sp << "     " << std::endl;
	std::cout << sp << "     " << sp << "Y Y Y" << sp << "     " << sp << "     " << std::endl;

	std::cout << sp << "B B B" << sp << "R R R" << sp << "G G G" << sp << "O O O" << std::endl;
	std::cout << sp << "B B B" << sp << "R R R" << sp << "G G G" << sp << "O O O" << std::endl;
	std::cout << sp << "B B B" << sp << "R R R" << sp << "G G G" << sp << "O O O" << std::endl;
	
	std::cout << sp << "     " << sp << "W W W" << sp << "     " << sp << "     " << std::endl;
	std::cout << sp << "     " << sp << "W W W" << sp << "     " << sp << "     " << std::endl;
	std::cout << sp << "     " << sp << "W W W" << sp << "     " << sp << "     " << std::endl;
}

void Cube::printVals() {
	std::cout << "Up:    " << std::bitset<32> (this->up) << std::endl;
	std::cout << "Down:  " << std::bitset<32> (this->down) << std::endl;
	std::cout << "Front: " << std::bitset<32> (this->front) << std::endl;
	std::cout << "Back:  " << std::bitset<32> (this->back) << std::endl;
	std::cout << "Right: " << std::bitset<32> (this->right) << std::endl;
	std::cout << "Left:  " << std::bitset<32> (this->left) << std::endl;
}