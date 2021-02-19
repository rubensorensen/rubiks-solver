#include <iostream>
#include <string>
#include <bitset>
#include "Cube.h"

//	Bitwise rotation Right
template <class N>
N Cube::Rotr(N n, unsigned int d) {
	return n >> d | n << (sizeof(n) * 8 - d);
}

//	Bitwise rotation Left
template <class N>
N Cube::Rotl(N n, unsigned int d) {
	return n << d | n >> (sizeof(n) * 8 - d);
}



/****************************\
 ****   CUBE ROTATIONS   ****
\****************************/

//	Front Quarter-Turn Clockwise
void Cube::F() {
	const unsigned long tmp{ this->Up };
	this->Up = (this->Up & 0xFFFF000F) | Rotr((this->Left & 0x00FFF000), 8);
	this->Left = (this->Left & 0xFF000FFF) | Rotr((this->Down & 0xFFF00000), 8);
	this->Down = (this->Down & 0x000FFFFF) | Rotr((this->Right & 0xF00000FF), 8);
	this->Right = (this->Right & 0x0FFFFF00) | Rotr((tmp & 0x0000FFF0), 8);
	this->Front = Rotr(this->Front, 8);
}

//	Front Quarter-Turn Anti-Clockwise
void Cube::Fprime() {
	const unsigned long tmp{ this->Up };
	this->Up = (this->Up & 0xFFFF000F) | Rotl((this->Right & 0xF00000FF), 8);
	this->Right = (this->Right & 0x0FFFFF00) | Rotl((this->Down & 0xFFF00000), 8);
	this->Down = (this->Down & 0x000FFFFF) | Rotl((this->Left & 0x00FFF000), 8);
	this->Left = (this->Left & 0xFF000FFF) | Rotl((tmp & 0x0000FFF0), 8);
	this->Front = Rotl(this->Front, 8);
}

//	Front Half-Turn
void Cube::F2() {
	unsigned long tmp{ this->Up };
	this->Up = (this->Up & 0xFFFF000F) | Rotr((this->Down & 0xFFF00000), 16);
	this->Down = (this->Down & 0x000FFFFF) | Rotr((tmp & 0x0000FFF0), 16);
	tmp = { this->Right };
	this->Right = (this->Right & 0x0FFFFF00) | Rotr((this->Left & 0x00FFF000), 16);
	this->Left = (this->Left & 0xFF000FFF) | Rotr((tmp & 0xF00000FF), 16);
	this->Front = Rotr(this->Front, 16);
}

//	Back Quarter-Turn Clockwise
void Cube::B() {
	const unsigned long tmp{ this->Up };
	this->Up = (this->Up & 0x000FFFFF) | Rotl((this->Right & 0x00FFF000), 8);
	this->Right = (this->Right & 0xFF000FFF) | Rotl((this->Down & 0x0000FFF0), 8);
	this->Down = (this->Down & 0xFFFF000F) | Rotl((this->Left & 0xF00000FF), 8);
	this->Left = (this->Left & 0x0FFFFF00) | Rotl((tmp & 0xFFF00000), 8);
	this->Back = Rotr(this->Back, 8);
}

//	Back Quarter-Turn Anti-Clockwise
void Cube::Bprime() {
	const unsigned long tmp{ this->Up };
	this->Up = (this->Up & 0x000FFFFF) | Rotr((this->Left & 0xF00000FF), 8);
	this->Left = (this->Left & 0x0FFFFF00) | Rotr((this->Down & 0x0000FFF0), 8);
	this->Down = (this->Down & 0xFFFF000F) | Rotr((this->Right & 0x00FFF000), 8);
	this->Right = (this->Right & 0xFF000FFF) | Rotr((tmp & 0xFFF00000), 8);
	this->Back = Rotl(this->Back, 8);
}

//	Back Half-Turn
void Cube::B2() {
	unsigned long tmp{ this->Up };
	this->Up = (this->Up & 0x000FFFFF) | Rotl((this->Down & 0x0000FFF0), 16);
	this->Down = (this->Down & 0xFFFF000F) | Rotl((tmp & 0xFFF00000), 16);
	tmp = { this->Left };
	this->Left = (this->Left & 0x0FFFFF00) | Rotl((this->Right & 0x00FFF000), 16);
	this->Right = (this->Right & 0xFF000FFF) | Rotl((tmp & 0xF00000FF), 16);
	this->Back = Rotr(this->Back, 16);
}

//	Up Quarter-Turn Clockwise
void Cube::U() {
	const unsigned long tmp{ this->Front };
	this->Front = (this->Front & 0x000FFFFF) | (this->Right & 0xFFF00000);
	this->Right = (this->Right & 0x000FFFFF) | (this->Back & 0xFFF00000);
	this->Back = (this->Back & 0x000FFFFF) | (this->Left & 0xFFF00000);
	this->Left = (this->Left & 0x000FFFFF) | (tmp & 0xFFF00000);
	this->Up = Rotr(this->Up, 8);
}

//	Up Quarter-Turn Anti-Clockwise
void Cube::Uprime() {
	const unsigned long tmp{ this->Front };
	this->Front = (this->Front & 0x000FFFFF) | (this->Left & 0xFFF00000);
	this->Left = (this->Left & 0x000FFFFF) | (this->Back & 0xFFF00000);
	this->Back = (this->Back & 0x000FFFFF) | (this->Right & 0xFFF00000);
	this->Right = (this->Right & 0x000FFFFF) | (tmp & 0xFFF00000);
	this->Up = Rotl(this->Up, 8);
}

//	Up Half-Turn
void Cube::U2() {
	unsigned long tmp{ this->Front };
	this->Front = (this->Front & 0x000FFFFF) | (this->Back & 0xFFF00000);
	this->Back = (this->Back & 0x000FFFFF) | (tmp & 0xFFF00000);
	tmp = { this->Left };
	this->Left = (this->Left & 0x000FFFFF) | (this->Right & 0xFFF00000);
	this->Right = (this->Right & 0x000FFFFF) | (tmp & 0xFFF00000);
	this->Up = Rotr(this->Up, 16);
}

//	Down Quarter-Turn Clockwise
void Cube::D() {
	const unsigned long tmp{ this->Front };
	this->Front = (this->Front & 0xFFFF000F) | (this->Left & 0x0000FFF0);
	this->Left = (this->Left & 0xFFFF000F) | (this->Back & 0x0000FFF0);
	this->Back = (this->Back & 0xFFFF000F) | (this->Right & 0x0000FFF0);
	this->Right = (this->Right & 0xFFFF000F) | (tmp & 0x0000FFF0);
	this->Down = Rotr(this->Down, 8);
}

//	Down Quarter-Turn Anti-Clockwise
void Cube::Dprime() {
	const unsigned long tmp{ this->Front };
	this->Front = (this->Front & 0xFFFF000F) | (this->Right & 0x0000FFF0);
	this->Right = (this->Right & 0xFFFF000F) | (this->Back & 0x0000FFF0);
	this->Back = (this->Back & 0xFFFF000F) | (this->Left & 0x0000FFF0);
	this->Left = (this->Left & 0xFFFF000F) | (tmp & 0x0000FFF0);
	this->Down = Rotl(this->Down, 8);
}

//	Down Half-Turn
void Cube::D2() {
	unsigned long tmp{ this->Front };
	this->Front = (this->Front & 0xFFFF000F) | (this->Back & 0x0000FFF0);
	this->Back = (this->Back & 0xFFFF000F) | (tmp & 0x0000FFF0);
	tmp = { this->Left };
	this->Left = (this->Left & 0xFFFF000F) | (this->Right & 0x0000FFF0);
	this->Right = (this->Right & 0xFFFF000F) | (tmp & 0x0000FFF0);
	this->Down = Rotr(this->Down, 16);
}

// Right Quarter-Turn Clockwise
void Cube::R() {
	const unsigned long tmp{ this->Front };
	this->Front = (this->Front & 0xFF000FFF) | (this->Down & 0x00FFF000);
	this->Down = (this->Down & 0xFF000FFF) | Rotr((this->Back & 0xF00000FF), 16);
	this->Back = (this->Back & 0x0FFFFF00) | Rotr((this->Up & 0x00FFF000), 16);
	this->Up = (this->Up & 0xFF000FFF) | (tmp & 0x00FFF000);
	this->Right = Rotr(this->Right, 8);
}

//	Right Quarter-Turn Anti-Clockwise
void Cube::Rprime() {
	const unsigned long tmp{ this->Front };
	this->Front = (this->Front & 0xFF000FFF) | (this->Up & 0x00FFF000);
	this->Up = (this->Up & 0xFF000FFF) | Rotl((this->Back & 0xF00000FF), 16);
	this->Back = (this->Back & 0x0FFFFF00) | Rotl((this->Down & 0x00FFF000), 16);
	this->Down = (this->Down & 0xFF000FFF) | (tmp & 0x00FFF000);
	this->Right = Rotl(this->Right, 8);
}

//	Right Half-Turn
void Cube::R2() {
	unsigned long tmp{ this->Front };
	this->Front = (this->Front & 0xFF000FFF) | Rotr((this->Back & 0xF00000FF), 16);
	this->Back = (this->Back & 0x0FFFFF00) | Rotr((tmp & 0x00FFF000), 16);
	tmp = this->Up;
	this->Up = (this->Up & 0xFF000FFF) | (this->Down & 0x00FFF000);
	this->Down = (this->Down & 0xFF000FFF) | (tmp & 0x00FFF000);
	this->Right = Rotr(this->Right, 16);
}

//	Left Quarter-Turn Clockwise
void Cube::L() {
	const unsigned long tmp{ this->Front };
	this->Front = (this->Front & 0x0FFFFF00) | (this->Up & 0xF00000FF);
	this->Up = (this->Up & 0x0FFFFF00) | Rotr((this->Back & 0x00FFF000), 16);
	this->Back = (this->Back & 0xFF000FFF) | Rotr((this->Down & 0xF00000FF), 16);
	this->Down = (this->Down & 0x0FFFFF00) | (tmp & 0xF00000FF);
	this->Left = Rotr(this->Left, 8);
}

// Left Quarter-Turn Anti-Clockwise
void Cube::Lprime() {
	const unsigned long tmp{ this->Front };
	this->Front = (this->Front & 0x0FFFFF00) | (this->Down & 0xF00000FF);
	this->Down = (this->Down & 0x0FFFFF00) | Rotl((this->Back & 0x00FFF000), 16);
	this->Back = (this->Back & 0xFF000FFF) | Rotl((this->Up & 0xF00000FF), 16);
	this->Up = (this->Up & 0x0FFFFF00) | (tmp & 0xF00000FF);
	this->Left = Rotl(this->Left, 8);
}

//Left Half-Turn
void Cube::L2() {
	unsigned long tmp{ this->Front };
	this->Front = (this->Front & 0x0FFFFF00) | Rotr((this->Back & 0x00FFF000), 16);
	this->Back = (this->Back & 0xFF000FFF) | Rotr((tmp & 0xF00000FF), 16);
	tmp = { this->Up };
	this->Up = (this->Up & 0x0FFFFF00) | (this->Down & 0xF00000FF);
	this->Down = (this->Down & 0x0FFFFF00) | (tmp & 0xF00000FF);
	this->Left = Rotr(this->Left, 16);
}


void Cube::ShowCube() {
	std::cout << "        " << GetColor(this->Up >> 28) << " " << GetColor(this->Up >> 24 & 0x0F) << " " << GetColor(this->Up >> 20 & 0x00F) << "  " << std::endl;
	std::cout << "        " << GetColor(this->Up & 0x0000000F) << " " << 'Y' << " " << GetColor(this->Up >> 16 & 0x000F) << "  " << std::endl;
	std::cout << "        " << GetColor(this->Up >> 4 & 0x000000F) << " " << GetColor(this->Up >> 8 & 0x00000F) << " " << GetColor(this->Up >> 12 & 0x0000F) << "  " << std::endl;
	std::cout << std::endl;

	std::cout << " " << GetColor(this->Left >> 28) << " " << GetColor(this->Left >> 24 & 0x0F) << " " << GetColor(this->Left >> 20 & 0x00F) << "  " << GetColor(this->Front >> 28) << " " << GetColor(this->Front >> 24 & 0x0F) << " " << GetColor(this->Front >> 20 & 0x00F) << "  " << GetColor(this->Right >> 28) << " " << GetColor(this->Right >> 24 & 0x0F) << " " << GetColor(this->Right >> 20 & 0x00F) << "  " << GetColor(this->Back >> 28) << " " << GetColor(this->Back >> 24 & 0x0F) << " " << GetColor(this->Back >> 20 & 0x00F) << std::endl;

	std::cout << " " << GetColor(this->Left & 0x0000000F) << " " << 'R' << " " << GetColor(this->Left >> 16 & 0x000F) << "  " << GetColor(this->Front & 0x0000000F) << " " << 'G' << " " << GetColor(this->Front >> 16 & 0x000F) << "  " << GetColor(this->Right & 0x0000000F) << " " << 'O' << " " << GetColor(this->Right >> 16 & 0x000F) << "  " << GetColor(this->Back & 0x0000000F) << " " << 'B' << " " << GetColor(this->Back >> 16 & 0x000F) << std::endl;

	std::cout << " " << GetColor(this->Left >> 4 & 0x000000F) << " " << GetColor(this->Left >> 8 & 0x00000F) << " " << GetColor(this->Left >> 12 & 0x0000F) << "  " << GetColor(this->Front >> 4 & 0x000000F) << " " << GetColor(this->Front >> 8 & 0x00000F) << " " << GetColor(this->Front >> 12 & 0x0000F) << "  " << GetColor(this->Right >> 4 & 0x000000F) << " " << GetColor(this->Right >> 8 & 0x00000F) << " " << GetColor(this->Right >> 12 & 0x0000F) << "  " << GetColor(this->Back >> 4 & 0x000000F) << " " << GetColor(this->Back >> 8 & 0x00000F) << " " << GetColor(this->Back >> 12 & 0x0000F) << std::endl;
	std::cout << std::endl;

	std::cout << "        " << GetColor(this->Down >> 28) << " " << GetColor(this->Down >> 24 & 0x0F) << " " << GetColor(this->Down >> 20 & 0x00F) << "  " << std::endl;
	std::cout << "        " << GetColor(this->Down & 0x0000000F) << " " << 'W' << " " << GetColor(this->Down >> 16 & 0x000F) << "  " << std::endl;
	std::cout << "        " << GetColor(this->Down >> 4 & 0x000000F) << " " << GetColor(this->Down >> 8 & 0x00000F) << " " << GetColor(this->Down >> 12 & 0x0000F) << "  " << std::endl;
	std::cout << std::endl;
}

void Cube::PrintVals() {
	std::cout << "Up:    " << std::bitset<32>(this->Up) << std::endl;
	std::cout << "Down:  " << std::bitset<32>(this->Down) << std::endl;
	std::cout << "Front: " << std::bitset<32>(this->Front) << std::endl;
	std::cout << "Back:  " << std::bitset<32>(this->Back) << std::endl;
	std::cout << "Right: " << std::bitset<32>(this->Right) << std::endl;
	std::cout << "Left:  " << std::bitset<32>(this->Left) << std::endl;
	std::cout << std::endl;
}

char Cube::GetColor(unsigned long num) {
	switch (num) {
	case 0:
		return 'Y';
	case 1:
		return 'W';
	case 2:
		return 'G';
	case 3:
		return 'B';
	case 4:
		return 'O';
	case 5:
		return 'R';
	default:
		return '?';
	}
}
