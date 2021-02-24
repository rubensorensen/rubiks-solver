#pragma once

class Cube {
	
public:
	Cube() = default;

	template <class N>
	N Rotr(N n, unsigned int d);
	
	template <class N>
	N Rotl(N n, unsigned int d);

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

	void PrintVals();
	void ShowCube();
	char GetColor(unsigned long num);

private:

	/*	COLOR SCHEME
	 *
	 *	YELLOW	:	0	0000
	 *	WHITE	:	1	0001
	 *	GREEN	:	2	0010
	 *	BLUE	:	3	0011
	 *	ORANGE	:	4	0100
	 *	RED		:	5	0101
	 */

	
	unsigned long Up { 0x00000000 };
	unsigned long Down { 0x11111111 };
	unsigned long Front { 0x22222222 };
	unsigned long Back { 0x33333333 };
	unsigned long Right { 0x44444444 };
	unsigned long Left { 0x55555555 };
	
};

