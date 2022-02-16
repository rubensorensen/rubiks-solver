#ifndef CUBE_H
#define CUBE_H

#include <stdint.h>

class Cube
{
    /*		COLOR SCHEME
     *
     *  FACE    BIN DEC
     *  ----------------
     *	UP	     0  0000
     *	DOWN     1  0001
     *	FRONT    2  0010
     *	BACK     3  0011
     *	RIGHT    4  0100
     *	LEFT     5  0101
     */

  public:

    enum class FACE : uint8_t
    {
        UP = 0,
        DOWN,
        FRONT,
        BACK,
        RIGHT,
        LEFT
    };

    enum class COLOR : uint8_t
    {
        YELLOW = 0,
        WHITE,
        GREEN,
        BLUE,
        ORANGE,
        RED
    };

    enum class MOVE : uint8_t
    {
        UP = 0,
        UPRIME,
        UP2,

        DOWN,
        DPRIME,
        DOWN2,

        FRONT,
        FPRIME,
        FRONT2,

        BACK,
        BPRIME,
        BACK2,

        RIGHT,
        RPRIME,
        RIGHT2,

        LEFT,
        LPRIME,
        LEFT2
    };

    Cube(uint32_t up = 0x00000000, uint32_t down = 0x11111111, uint32_t front = 0x22222222, uint32_t back = 0x33333333, uint32_t right = 0x44444444, uint32_t left = 0x55555555);

    void Twist(MOVE mv);

    void PrintVals() const;
    void ShowCube() const;
    char GetColor(uint32_t num) const;

    bool IsSolved();

  private:

    uint32_t m_Up;
    uint32_t m_Down;
    uint32_t m_Front;
    uint32_t m_Back;
    uint32_t m_Right;
    uint32_t m_Left;

    friend class CubeHandler;
};

#endif
