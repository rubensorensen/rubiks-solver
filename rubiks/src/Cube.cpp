#include "Cube.h"
#include <iostream>
#include <string>

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