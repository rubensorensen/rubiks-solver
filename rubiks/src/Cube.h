#pragma once
#include "Face.h"

class Cube {
	
public:
	Cube() = default;

	static void showSolved();
	

private:
	Face* up = new Face(Face::Color::yellow);
	Face* down = new Face(Face::Color::white);
	Face* front = new Face(Face::Color::green);
	Face* back = new Face(Face::Color::blue);
	Face* right = new Face(Face::Color::orange);
	Face* left = new Face(Face::Color::red);
};

