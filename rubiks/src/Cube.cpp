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

void Cube::F() {
	const unsigned long tmp { this->Up };
	this->Up = (this->Up & 0xFFFF000F) | Rotr((this->Left & 0x00FFF000), 8);
	this->Left = (this->Left & 0xFF000FFF) | Rotr((this->Down & 0xFFF00000), 8);
	this->Down = (this->Down & 0x000FFFFF) | Rotr((this->Right & 0xF00000FF), 8);
	this->Right = (this->Right & 0x0FFFFF00) | Rotr((tmp & 0x0000FFF0), 8);
	this->Front = Rotr(this->Front, 8);
}

void Cube::Fp() {
	const unsigned long tmp { this->Up };
	this->Up = (this->Up & 0xFFFF000F) | Rotl((this->Right & 0xF00000FF), 8);
	this->Right = (this->Right & 0x0FFFFF00) | Rotl((this->Down & 0xFFF00000), 8);
	this->Down = (this->Down & 0x000FFFFF) | Rotl((this->Left & 0x00FFF000), 8);
	this->Left = (this->Left & 0xFF000FFF) | Rotl((tmp & 0x0000FFF0), 8);
	this->Front = Rotl(this->Front, 8);
}

void Cube::F2() {
	unsigned long tmp { this->Up };
	this->Up = (this->Up & 0xFFFF000F) | Rotr((this->Down & 0xFFF00000), 16);
	this->Down = (this->Down & 0x000FFFFF) | Rotr((tmp & 0x0000FFF0), 16);
	tmp = { this->Right };
	this->Right = (this->Right & 0x0FFFFF00) | Rotr((this->Left & 0x00FFF000), 16);
	this->Left = (this->Left & 0xFF000FFF) | Rotr((tmp & 0xF00000FF), 16);
	this->Front = Rotr(this->Front, 16);
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
