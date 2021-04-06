#include "Cube.h"

//	Bitwise rotation Right
template <class N>
N ror(const N n, const uint8_t d)
{
	return n >> d | n << (sizeof(n) * 8 - d);
}

//	Bitwise rotation Left
template <class N>
N rol(const N n, const uint8_t d)
{
	return n << d | n >> (sizeof(n) * 8 - d);
}


Cube::Cube(uint32_t Up, uint32_t Down, uint32_t Front, uint32_t Back, uint32_t Right, uint32_t Left)
{
	this->Up = Up;
	this->Down = Down;
	this->Front = Front;
	this->Back = Back;
	this->Right = Right;
	this->Left = Left;
}



/****************************\
        CUBE ROTATIONS
\****************************/

//	Front Quarter-Turn Clockwise
void Cube::F()
{
	const uint32_t tmp{ Up };
	Up = (Up & 0xFFFF000F) | ror((Left & 0x00FFF000), 8);
	Left = (Left & 0xFF000FFF) | ror((Down & 0xFFF00000), 8);
	Down = (Down & 0x000FFFFF) | ror((Right & 0xF00000FF), 8);
	Right = (Right & 0x0FFFFF00) | ror((tmp & 0x0000FFF0), 8);
	Front = ror(Front, 8);
}

//	Front Quarter-Turn Anti-Clockwise
void Cube::Fprime()
{
	const uint32_t tmp{ Up };
	Up = (Up & 0xFFFF000F) | rol((Right & 0xF00000FF), 8);
	Right = (Right & 0x0FFFFF00) | rol((Down & 0xFFF00000), 8);
	Down = (Down & 0x000FFFFF) | rol((Left & 0x00FFF000), 8);
	Left = (Left & 0xFF000FFF) | rol((tmp & 0x0000FFF0), 8);
	Front = rol(Front, 8);
}

//	Front Half-Turn
void Cube::F2()
{
	uint32_t tmp{ Up };
	Up = (Up & 0xFFFF000F) | ror((Down & 0xFFF00000), 16);
	Down = (Down & 0x000FFFFF) | ror((tmp & 0x0000FFF0), 16);
	tmp = { Right };
	Right = (Right & 0x0FFFFF00) | ror((Left & 0x00FFF000), 16);
	Left = (Left & 0xFF000FFF) | ror((tmp & 0xF00000FF), 16);
	Front = ror(Front, 16);
}

//	Back Quarter-Turn Clockwise
void Cube::B()
{
	const uint32_t tmp{ Up };
	Up = (Up & 0x000FFFFF) | rol((Right & 0x00FFF000), 8);
	Right = (Right & 0xFF000FFF) | rol((Down & 0x0000FFF0), 8);
	Down = (Down & 0xFFFF000F) | rol((Left & 0xF00000FF), 8);
	Left = (Left & 0x0FFFFF00) | rol((tmp & 0xFFF00000), 8);
	Back = ror(Back, 8);
}

//	Back Quarter-Turn Anti-Clockwise
void Cube::Bprime()
{
	const uint32_t tmp{ Up };
	Up = (Up & 0x000FFFFF) | ror((Left & 0xF00000FF), 8);
	Left = (Left & 0x0FFFFF00) | ror((Down & 0x0000FFF0), 8);
	Down = (Down & 0xFFFF000F) | ror((Right & 0x00FFF000), 8);
	Right = (Right & 0xFF000FFF) | ror((tmp & 0xFFF00000), 8);
	Back = rol(Back, 8);
}

//	Back Half-Turn
void Cube::B2()
{
	uint32_t tmp{ Up };
	Up = (Up & 0x000FFFFF) | rol((Down & 0x0000FFF0), 16);
	Down = (Down & 0xFFFF000F) | rol((tmp & 0xFFF00000), 16);
	tmp = { Left };
	Left = (Left & 0x0FFFFF00) | rol((Right & 0x00FFF000), 16);
	Right = (Right & 0xFF000FFF) | rol((tmp & 0xF00000FF), 16);
	Back = ror(Back, 16);
}

//	Up Quarter-Turn Clockwise
void Cube::U()
{
	const uint32_t tmp{ Front };
	Front = (Front & 0x000FFFFF) | (Right & 0xFFF00000);
	Right = (Right & 0x000FFFFF) | (Back & 0xFFF00000);
	Back = (Back & 0x000FFFFF) | (Left & 0xFFF00000);
	Left = (Left & 0x000FFFFF) | (tmp & 0xFFF00000);
	Up = ror(Up, 8);
}

//	Up Quarter-Turn Anti-Clockwise
void Cube::Uprime()
{
	const uint32_t tmp{ Front };
	Front = (Front & 0x000FFFFF) | (Left & 0xFFF00000);
	Left = (Left & 0x000FFFFF) | (Back & 0xFFF00000);
	Back = (Back & 0x000FFFFF) | (Right & 0xFFF00000);
	Right = (Right & 0x000FFFFF) | (tmp & 0xFFF00000);
	Up = rol(Up, 8);
}

//	Up Half-Turn
void Cube::U2()
{
	uint32_t tmp{ Front };
	Front = (Front & 0x000FFFFF) | (Back & 0xFFF00000);
	Back = (Back & 0x000FFFFF) | (tmp & 0xFFF00000);
	tmp = { Left };
	Left = (Left & 0x000FFFFF) | (Right & 0xFFF00000);
	Right = (Right & 0x000FFFFF) | (tmp & 0xFFF00000);
	Up = ror(Up, 16);
}

//	Down Quarter-Turn Clockwise
void Cube::D()
{
	const uint32_t tmp{ Front };
	Front = (Front & 0xFFFF000F) | (Left & 0x0000FFF0);
	Left = (Left & 0xFFFF000F) | (Back & 0x0000FFF0);
	Back = (Back & 0xFFFF000F) | (Right & 0x0000FFF0);
	Right = (Right & 0xFFFF000F) | (tmp & 0x0000FFF0);
	Down = ror(Down, 8);
}

//	Down Quarter-Turn Anti-Clockwise
void Cube::Dprime()
{
	const uint32_t tmp{ Front };
	Front = (Front & 0xFFFF000F) | (Right & 0x0000FFF0);
	Right = (Right & 0xFFFF000F) | (Back & 0x0000FFF0);
	Back = (Back & 0xFFFF000F) | (Left & 0x0000FFF0);
	Left = (Left & 0xFFFF000F) | (tmp & 0x0000FFF0);
	Down = rol(Down, 8);
}

//	Down Half-Turn
void Cube::D2()
{
	uint32_t tmp{ Front };
	Front = (Front & 0xFFFF000F) | (Back & 0x0000FFF0);
	Back = (Back & 0xFFFF000F) | (tmp & 0x0000FFF0);
	tmp = { Left };
	Left = (Left & 0xFFFF000F) | (Right & 0x0000FFF0);
	Right = (Right & 0xFFFF000F) | (tmp & 0x0000FFF0);
	Down = ror(Down, 16);
}

// Right Quarter-Turn Clockwise
void Cube::R()
{
	const uint32_t tmp{ Front };
	Front = (Front & 0xFF000FFF) | (Down & 0x00FFF000);
	Down = (Down & 0xFF000FFF) | ror((Back & 0xF00000FF), 16);
	Back = (Back & 0x0FFFFF00) | ror((Up & 0x00FFF000), 16);
	Up = (Up & 0xFF000FFF) | (tmp & 0x00FFF000);
	Right = ror(Right, 8);
}

//	Right Quarter-Turn Anti-Clockwise
void Cube::Rprime()
{
	const uint32_t tmp{ Front };
	Front = (Front & 0xFF000FFF) | (Up & 0x00FFF000);
	Up = (Up & 0xFF000FFF) | rol((Back & 0xF00000FF), 16);
	Back = (Back & 0x0FFFFF00) | rol((Down & 0x00FFF000), 16);
	Down = (Down & 0xFF000FFF) | (tmp & 0x00FFF000);
	Right = rol(Right, 8);
}

//	Right Half-Turn
void Cube::R2()
{
	uint32_t tmp{ Front };
	Front = (Front & 0xFF000FFF) | ror((Back & 0xF00000FF), 16);
	Back = (Back & 0x0FFFFF00) | ror((tmp & 0x00FFF000), 16);
	tmp = Up;
	Up = (Up & 0xFF000FFF) | (Down & 0x00FFF000);
	Down = (Down & 0xFF000FFF) | (tmp & 0x00FFF000);
	Right = ror(Right, 16);
}

//	Left Quarter-Turn Clockwise
void Cube::L()
{
	const uint32_t tmp{ Front };
	Front = (Front & 0x0FFFFF00) | (Up & 0xF00000FF);
	Up = (Up & 0x0FFFFF00) | ror((Back & 0x00FFF000), 16);
	Back = (Back & 0xFF000FFF) | ror((Down & 0xF00000FF), 16);
	Down = (Down & 0x0FFFFF00) | (tmp & 0xF00000FF);
	Left = ror(Left, 8);
}

// Left Quarter-Turn Anti-Clockwise
void Cube::Lprime()
{
	const uint32_t tmp{ Front };
	Front = (Front & 0x0FFFFF00) | (Down & 0xF00000FF);
	Down = (Down & 0x0FFFFF00) | rol((Back & 0x00FFF000), 16);
	Back = (Back & 0xFF000FFF) | rol((Up & 0xF00000FF), 16);
	Up = (Up & 0x0FFFFF00) | (tmp & 0xF00000FF);
	Left = rol(Left, 8);
}

//Left Half-Turn
void Cube::L2()
{
	uint32_t tmp{ Front };
	Front = (Front & 0x0FFFFF00) | ror((Back & 0x00FFF000), 16);
	Back = (Back & 0xFF000FFF) | ror((tmp & 0xF00000FF), 16);
	tmp = { Up };
	Up = (Up & 0x0FFFFF00) | (Down & 0xF00000FF);
	Down = (Down & 0x0FFFFF00) | (tmp & 0xF00000FF);
	Left = ror(Left, 16);
}


void Cube::ShowCube() const
{

	using std::cout, std::endl;

	PrintVals();
	
	cout << "        " << GetColor(Up >> 28) << " " << GetColor(Up >> 24 & 0x0F) << " " << GetColor(Up >> 20 & 0x00F) << "  " << endl;
	cout << "        " << GetColor(Up & 0x0000000F) << " " << 'Y' << " " << GetColor(Up >> 16 & 0x000F) << "  " << endl;
	cout << "        " << GetColor(Up >> 4 & 0x000000F) << " " << GetColor(Up >> 8 & 0x00000F) << " " << GetColor(Up >> 12 & 0x0000F) << "  " << endl;
	
	cout << endl;

	cout
	<< " " << GetColor(Left >> 28) << " " << GetColor(Left >> 24 & 0x0F) << " " << GetColor(Left >> 20 & 0x00F)
	<< "  " << GetColor(Front >> 28) << " " << GetColor(Front >> 24 & 0x0F) << " " << GetColor(Front >> 20 & 0x00F)
	<< "  " << GetColor(Right >> 28) << " " << GetColor(Right >> 24 & 0x0F) << " " << GetColor(Right >> 20 & 0x00F)
	<< "  " << GetColor(Back >> 28) << " " << GetColor(Back >> 24 & 0x0F) << " " << GetColor(Back >> 20 & 0x00F) << endl;

	cout
	<< " " << GetColor(Left & 0x0000000F) << " " << 'R' << " " << GetColor(Left >> 16 & 0x000F)
	<< "  " << GetColor(Front & 0x0000000F) << " " << 'G' << " " << GetColor(Front >> 16 & 0x000F)
	<< "  " << GetColor(Right & 0x0000000F) << " " << 'O' << " " << GetColor(Right >> 16 & 0x000F)
	<< "  " << GetColor(Back & 0x0000000F) << " " << 'B' << " " << GetColor(Back >> 16 & 0x000F) << endl; 

	cout
	<< " " << GetColor(Left >> 4 & 0x000000F) << " " << GetColor(Left >> 8 & 0x00000F) << " " << GetColor(Left >> 12 & 0x0000F)
	<< "  " << GetColor(Front >> 4 & 0x000000F) << " " << GetColor(Front >> 8 & 0x00000F) << " " << GetColor(Front >> 12 & 0x0000F)
	<< "  " << GetColor(Right >> 4 & 0x000000F) << " " << GetColor(Right >> 8 & 0x00000F) << " " << GetColor(Right >> 12 & 0x0000F)
	<< "  " << GetColor(Back >> 4 & 0x000000F) << " " << GetColor(Back >> 8 & 0x00000F) << " " << GetColor(Back >> 12 & 0x0000F) << endl;
	
	cout << endl;

	cout << "        " << GetColor(Down >> 28) << " " << GetColor(Down >> 24 & 0x0F) << " " << GetColor(Down >> 20 & 0x00F) << "  " << endl;
	cout << "        " << GetColor(Down & 0x0000000F) << " " << 'W' << " " << GetColor(Down >> 16 & 0x000F) << "  " << endl;
	cout << "        " << GetColor(Down >> 4 & 0x000000F) << " " << GetColor(Down >> 8 & 0x00000F) << " " << GetColor(Down >> 12 & 0x0000F) << "  " << endl;
	
	cout << endl;
}

void Cube::PrintVals() const
{

	using std::cout, std::endl;
	
	cout << "Up:    " << std::bitset<32>(Up) << endl;
	cout << "Down:  " << std::bitset<32>(Down) << endl;
	cout << "Front: " << std::bitset<32>(Front) << endl;
	cout << "Back:  " << std::bitset<32>(Back) << endl;
	cout << "Right: " << std::bitset<32>(Right) << endl;
	cout << "Left:  " << std::bitset<32>(Left) << endl;
	cout << endl;
}

char Cube::GetColor(uint32_t num) const
{
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
