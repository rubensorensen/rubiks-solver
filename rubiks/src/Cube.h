#pragma once

#include <cstdint>

class Cube
{

/*		COLOR SCHEME
 *
 *	YELLOW	:	0	0000
 *	WHITE	:	1	0001
 *	GREEN	:	2	0010
 *	BLUE	:	3	0011
 *	ORANGE	:	4	0100
 *	RED		:	5	0101
 */
	
public:
	Cube(
		uint32_t Up = 0x00000000,
		uint32_t Down = 0x11111111 ,
		uint32_t Front = 0x22222222,
		uint32_t Back = 0x33333333,
		uint32_t Right = 0x44444444,
		uint32_t Left = 0x55555555
	);

	void F();
	void Fprime();
	void F2();

	void B();
	void Bprime();
	void B2();

	void U();
	void Uprime();
	void U2();

	void D();
	void Dprime();
	void D2();

	void R();
	void Rprime();
	void R2();

	void L();
	void Lprime();
	void L2();

	void PrintVals() const;
	void ShowCube() const;
	char GetColor(uint32_t num) const;

private:

	uint32_t Up;
	uint32_t Down;
	uint32_t Front;
	uint32_t Back;
	uint32_t Right;
	uint32_t Left;
	
};

