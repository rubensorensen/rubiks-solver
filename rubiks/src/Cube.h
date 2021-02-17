#pragma once

class Cube {
	
public:
	Cube() = default;

	static void showSolved();
	void printVals();
	

private:

	/*	COLOR SCHEME
	 *
	 *	YELLOW	:	0
	 *	WHITE	:	1
	 *	GREEN	:	2
	 *	BLUE	:	3
	 *	ORANGE	:	4
	 *	RED		:	5
	 */
	
	unsigned long up { 0x00000000 };
	unsigned long down { 0x11111111 };
	unsigned long front { 0x22222222 };
	unsigned long back { 0x33333333 };
	unsigned long right { 0x44444444 };
	unsigned long left { 0x55555555 };
	
};

