#ifndef CUBE_H
#define CUBE_H

#include "pch.h"

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
    Cube(uint32_t up = 0x00000000, uint32_t down = 0x11111111,
         uint32_t front = 0x22222222, uint32_t back = 0x33333333,
         uint32_t right = 0x44444444, uint32_t left = 0x55555555);

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

    bool IsSolved();
    void RotateByString(std::string str);
    void RotateFromFile(const char* filepath);

private:
    uint32_t m_Up;
    uint32_t m_Down;
    uint32_t m_Front;
    uint32_t m_Back;
    uint32_t m_Right;
    uint32_t m_Left;
};

#endif
