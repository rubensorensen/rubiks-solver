#include "../include/cube.h"

#include <bitset>
#include <iostream>

//	Bitwise rotation m_Right
template<class N>
N ror(const N n, const uint8_t d)
{
    return n >> d | n << (sizeof(n) * 8 - d);
}

//	Bitwise rotation m_Left
template<class N>
N rol(const N n, const uint8_t d)
{
    return n << d | n >> (sizeof(n) * 8 - d);
}

Cube::Cube(uint32_t up, uint32_t down, uint32_t front, uint32_t back, uint32_t right, uint32_t left)
{
    m_Up    = { up };
    m_Down  = { down };
    m_Front = { front };
    m_Back  = { back };
    m_Right = { right };
    m_Left  = { left };
}

void Cube::Twist(MOVE mv)
{
    // U ROTATION
    if (mv == MOVE::UP)
    {
        const uint32_t tmp{ m_Front };
        m_Front = { (m_Front & 0x000FFFFF) | (m_Right & 0xFFF00000) };
        m_Right = { (m_Right & 0x000FFFFF) | (m_Back & 0xFFF00000) };
        m_Back  = { (m_Back & 0x000FFFFF) | (m_Left & 0xFFF00000) };
        m_Left  = { (m_Left & 0x000FFFFF) | (tmp & 0xFFF00000) };
        m_Up    = { ror(m_Up, 8) };
    }
    // U' ROTATION
    else if (mv == MOVE::UPRIME)
    {
        const uint32_t tmp{ m_Front };
        m_Front = { (m_Front & 0x000FFFFF) | (m_Left & 0xFFF00000) };
        m_Left  = { (m_Left & 0x000FFFFF) | (m_Back & 0xFFF00000) };
        m_Back  = { (m_Back & 0x000FFFFF) | (m_Right & 0xFFF00000) };
        m_Right = { (m_Right & 0x000FFFFF) | (tmp & 0xFFF00000) };
        m_Up    = { rol(m_Up, 8) };
    }
    // U2 ROTATION
    else if (mv == MOVE::UP2)
    {
        uint32_t tmp{ m_Front };
        m_Front = { (m_Front & 0x000FFFFF) | (m_Back & 0xFFF00000) };
        m_Back  = { (m_Back & 0x000FFFFF) | (tmp & 0xFFF00000) };
        tmp     = { m_Left };
        m_Left  = { (m_Left & 0x000FFFFF) | (m_Right & 0xFFF00000) };
        m_Right = { (m_Right & 0x000FFFFF) | (tmp & 0xFFF00000) };
        m_Up    = { ror(m_Up, 16) };
    }

    // D ROTATION
    else if (mv == MOVE::DOWN)
    {
        const uint32_t tmp{ m_Front };
        m_Front = { (m_Front & 0xFFFF000F) | (m_Left & 0x0000FFF0) };
        m_Left  = { (m_Left & 0xFFFF000F) | (m_Back & 0x0000FFF0) };
        m_Back  = { (m_Back & 0xFFFF000F) | (m_Right & 0x0000FFF0) };
        m_Right = { (m_Right & 0xFFFF000F) | (tmp & 0x0000FFF0) };
        m_Down  = { ror(m_Down, 8) };
    }
    // D' ROTATION
    else if (mv == MOVE::DPRIME)
    {
        const uint32_t tmp{ m_Front };
        m_Front = { (m_Front & 0xFFFF000F) | (m_Right & 0x0000FFF0) };
        m_Right = { (m_Right & 0xFFFF000F) | (m_Back & 0x0000FFF0) };
        m_Back  = { (m_Back & 0xFFFF000F) | (m_Left & 0x0000FFF0) };
        m_Left  = { (m_Left & 0xFFFF000F) | (tmp & 0x0000FFF0) };
        m_Down  = { rol(m_Down, 8) };
    }
    // D2 ROTATION
    else if (mv == MOVE::DOWN2)
    {
        uint32_t tmp{ m_Front };
        m_Front = { (m_Front & 0xFFFF000F) | (m_Back & 0x0000FFF0) };
        m_Back  = { (m_Back & 0xFFFF000F) | (tmp & 0x0000FFF0) };
        tmp     = { m_Left };
        m_Left  = { (m_Left & 0xFFFF000F) | (m_Right & 0x0000FFF0) };
        m_Right = { (m_Right & 0xFFFF000F) | (tmp & 0x0000FFF0) };
        m_Down  = { ror(m_Down, 16) };
    }

    // F ROTATION
    else if (mv == MOVE::FRONT)
    {
        const uint32_t tmp{ m_Up };
        m_Up    = { (m_Up & 0xFFFF000F) | ror((m_Left & 0x00FFF000), 8) };
        m_Left  = { (m_Left & 0xFF000FFF) | ror((m_Down & 0xFFF00000), 8) };
        m_Down  = { (m_Down & 0x000FFFFF) | ror((m_Right & 0xF00000FF), 8) };
        m_Right = { (m_Right & 0x0FFFFF00) | ror((tmp & 0x0000FFF0), 8) };
        m_Front = { ror(m_Front, 8) };
    }
    // F' ROTATION
    else if (mv == MOVE::FPRIME)
    {
        const uint32_t tmp{ m_Up };
        m_Up    = { (m_Up & 0xFFFF000F) | rol((m_Right & 0xF00000FF), 8) };
        m_Right = { (m_Right & 0x0FFFFF00) | rol((m_Down & 0xFFF00000), 8) };
        m_Down  = { (m_Down & 0x000FFFFF) | rol((m_Left & 0x00FFF000), 8) };
        m_Left  = { (m_Left & 0xFF000FFF) | rol((tmp & 0x0000FFF0), 8) };
        m_Front = { rol(m_Front, 8) };
    }
    // F2 ROTATION
    else if (mv == MOVE::FRONT2)
    {
        uint32_t tmp{ m_Up };
        m_Up    = { (m_Up & 0xFFFF000F) | ror((m_Down & 0xFFF00000), 16) };
        m_Down  = { (m_Down & 0x000FFFFF) | ror((tmp & 0x0000FFF0), 16) };
        tmp     = { m_Right };
        m_Right = { (m_Right & 0x0FFFFF00) | ror((m_Left & 0x00FFF000), 16) };
        m_Left  = { (m_Left & 0xFF000FFF) | ror((tmp & 0xF00000FF), 16) };
        m_Front = { ror(m_Front, 16) };
    }

    // B ROTATION
    else if (mv == MOVE::BACK)
    {
        const uint32_t tmp{ m_Up };
        m_Up    = { (m_Up & 0x000FFFFF) | rol((m_Right & 0x00FFF000), 8) };
        m_Right = { (m_Right & 0xFF000FFF) | rol((m_Down & 0x0000FFF0), 8) };
        m_Down  = { (m_Down & 0xFFFF000F) | rol((m_Left & 0xF00000FF), 8) };
        m_Left  = { (m_Left & 0x0FFFFF00) | rol((tmp & 0xFFF00000), 8) };
        m_Back  = { ror(m_Back, 8) };
    }
    // B' ROTATION
    else if (mv == MOVE::BPRIME)
    {
        const uint32_t tmp{ m_Up };
        m_Up    = { (m_Up & 0x000FFFFF) | ror((m_Left & 0xF00000FF), 8) };
        m_Left  = { (m_Left & 0x0FFFFF00) | ror((m_Down & 0x0000FFF0), 8) };
        m_Down  = { (m_Down & 0xFFFF000F) | ror((m_Right & 0x00FFF000), 8) };
        m_Right = { (m_Right & 0xFF000FFF) | ror((tmp & 0xFFF00000), 8) };
        m_Back  = { rol(m_Back, 8) };
    }
    // B2 ROTATION
    else if (mv == MOVE::BACK2)
    {
        uint32_t tmp{ m_Up };
        m_Up    = { (m_Up & 0x000FFFFF) | rol((m_Down & 0x0000FFF0), 16) };
        m_Down  = { (m_Down & 0xFFFF000F) | rol((tmp & 0xFFF00000), 16) };
        tmp     = { m_Left };
        m_Left  = { (m_Left & 0x0FFFFF00) | rol((m_Right & 0x00FFF000), 16) };
        m_Right = { (m_Right & 0xFF000FFF) | rol((tmp & 0xF00000FF), 16) };
        m_Back  = { ror(m_Back, 16) };
    }

    // R ROTATION
    else if (mv == MOVE::RIGHT)
    {
        const uint32_t tmp{ m_Front };
        m_Front = { (m_Front & 0xFF000FFF) | (m_Down & 0x00FFF000) };
        m_Down  = { (m_Down & 0xFF000FFF) | ror((m_Back & 0xF00000FF), 16) };
        m_Back  = { (m_Back & 0x0FFFFF00) | ror((m_Up & 0x00FFF000), 16) };
        m_Up    = { (m_Up & 0xFF000FFF) | (tmp & 0x00FFF000) };
        m_Right = { ror(m_Right, 8) };
    }
    // R' ROTATION
    else if (mv == MOVE::RPRIME)
    {
        const uint32_t tmp{ m_Front };
        m_Front = { (m_Front & 0xFF000FFF) | (m_Up & 0x00FFF000) };
        m_Up    = { (m_Up & 0xFF000FFF) | rol((m_Back & 0xF00000FF), 16) };
        m_Back  = { (m_Back & 0x0FFFFF00) | rol((m_Down & 0x00FFF000), 16) };
        m_Down  = { (m_Down & 0xFF000FFF) | (tmp & 0x00FFF000) };
        m_Right = { rol(m_Right, 8) };
    }
    // R2 ROTATION
    else if (mv == MOVE::RIGHT2)
    {
        uint32_t tmp{ m_Front };
        m_Front = { (m_Front & 0xFF000FFF) | ror((m_Back & 0xF00000FF), 16) };
        m_Back  = { (m_Back & 0x0FFFFF00) | ror((tmp & 0x00FFF000), 16) };
        tmp     = { m_Up };
        m_Up    = { (m_Up & 0xFF000FFF) | (m_Down & 0x00FFF000) };
        m_Down  = { (m_Down & 0xFF000FFF) | (tmp & 0x00FFF000) };
        m_Right = { ror(m_Right, 16) };
    }

    // L ROTATION
    else if (mv == MOVE::LEFT)
    {
        const uint32_t tmp{ m_Front };
        m_Front = { (m_Front & 0x0FFFFF00) | (m_Up & 0xF00000FF) };
        m_Up    = { (m_Up & 0x0FFFFF00) | ror((m_Back & 0x00FFF000), 16) };
        m_Back  = { (m_Back & 0xFF000FFF) | ror((m_Down & 0xF00000FF), 16) };
        m_Down  = { (m_Down & 0x0FFFFF00) | (tmp & 0xF00000FF) };
        m_Left  = { ror(m_Left, 8) };
    }
    // L' ROTATION
    else if (mv == MOVE::LPRIME)
    {
        const uint32_t tmp{ m_Front };
        m_Front = { (m_Front & 0x0FFFFF00) | (m_Down & 0xF00000FF) };
        m_Down  = { (m_Down & 0x0FFFFF00) | rol((m_Back & 0x00FFF000), 16) };
        m_Back  = { (m_Back & 0xFF000FFF) | rol((m_Up & 0xF00000FF), 16) };
        m_Up    = { (m_Up & 0x0FFFFF00) | (tmp & 0xF00000FF) };
        m_Left  = { rol(m_Left, 8) };
    }
    // L2 ROTATION
    else if (mv == MOVE::LEFT2)
    {
        uint32_t tmp{ m_Front };
        m_Front = { (m_Front & 0x0FFFFF00) | ror((m_Back & 0x00FFF000), 16) };
        m_Back  = { (m_Back & 0xFF000FFF) | ror((tmp & 0xF00000FF), 16) };
        tmp     = { m_Up };
        m_Up    = { (m_Up & 0x0FFFFF00) | (m_Down & 0xF00000FF) };
        m_Down  = { (m_Down & 0x0FFFFF00) | (tmp & 0xF00000FF) };
        m_Left  = { ror(m_Left, 16) };
    }
    else
        std::cerr << "Invalid rotation: " << static_cast<uint8_t>(mv) << std::endl;
}

void Cube::ShowCube() const
{
    using std::cout;
    using std::endl;

    PrintVals();

    cout << "        " << GetColor(m_Up >> 28) << " " << GetColor(m_Up >> 24 & 0x0F) << " " << GetColor(m_Up >> 20 & 0x00F) << endl;
    cout << "        " << GetColor(m_Up & 0x0000000F) << " " << 'Y' << " " << GetColor(m_Up >> 16 & 0x000F) << endl;
    cout << "        " << GetColor(m_Up >> 4 & 0x000000F) << " " << GetColor(m_Up >> 8 & 0x00000F) << " " << GetColor(m_Up >> 12 & 0x0000F) << endl;

    cout << endl;

    cout << " " << GetColor(m_Left >> 28) << " " << GetColor(m_Left >> 24 & 0x0F) << " " << GetColor(m_Left >> 20 & 0x00F) << "  " << GetColor(m_Front >> 28) << " " << GetColor(m_Front >> 24 & 0x0F)
         << " " << GetColor(m_Front >> 20 & 0x00F) << "  " << GetColor(m_Right >> 28) << " " << GetColor(m_Right >> 24 & 0x0F) << " " << GetColor(m_Right >> 20 & 0x00F) << "  "
         << GetColor(m_Back >> 28) << " " << GetColor(m_Back >> 24 & 0x0F) << " " << GetColor(m_Back >> 20 & 0x00F) << endl;

    cout << " " << GetColor(m_Left & 0x0000000F) << " " << 'R' << " " << GetColor(m_Left >> 16 & 0x000F) << "  " << GetColor(m_Front & 0x0000000F) << " " << 'G' << " "
         << GetColor(m_Front >> 16 & 0x000F) << "  " << GetColor(m_Right & 0x0000000F) << " " << 'O' << " " << GetColor(m_Right >> 16 & 0x000F) << "  " << GetColor(m_Back & 0x0000000F) << " " << 'B'
         << " " << GetColor(m_Back >> 16 & 0x000F) << endl;

    cout << " " << GetColor(m_Left >> 4 & 0x000000F) << " " << GetColor(m_Left >> 8 & 0x00000F) << " " << GetColor(m_Left >> 12 & 0x0000F) << "  " << GetColor(m_Front >> 4 & 0x000000F) << " "
         << GetColor(m_Front >> 8 & 0x00000F) << " " << GetColor(m_Front >> 12 & 0x0000F) << "  " << GetColor(m_Right >> 4 & 0x000000F) << " " << GetColor(m_Right >> 8 & 0x00000F) << " "
         << GetColor(m_Right >> 12 & 0x0000F) << "  " << GetColor(m_Back >> 4 & 0x000000F) << " " << GetColor(m_Back >> 8 & 0x00000F) << " " << GetColor(m_Back >> 12 & 0x0000F) << endl;

    cout << endl;

    cout << "        " << GetColor(m_Down >> 28) << " " << GetColor(m_Down >> 24 & 0x0F) << " " << GetColor(m_Down >> 20 & 0x00F) << endl;
    cout << "        " << GetColor(m_Down & 0x0000000F) << " " << 'W' << " " << GetColor(m_Down >> 16 & 0x000F) << endl;
    cout << "        " << GetColor(m_Down >> 4 & 0x000000F) << " " << GetColor(m_Down >> 8 & 0x00000F) << " " << GetColor(m_Down >> 12 & 0x0000F) << endl;

    cout << endl;
}

void Cube::PrintVals() const
{

    using std::cout;
    using std::endl;

    cout << "Up:    " << std::bitset<32>(m_Up) << endl;
    cout << "Down:  " << std::bitset<32>(m_Down) << endl;
    cout << "Front: " << std::bitset<32>(m_Front) << endl;
    cout << "Back:  " << std::bitset<32>(m_Back) << endl;
    cout << "Right: " << std::bitset<32>(m_Right) << endl;
    cout << "Left:  " << std::bitset<32>(m_Left) << endl;
    cout << endl;
}

char Cube::GetColor(uint32_t num) const
{
    switch (num)
    {
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

bool Cube::IsSolved()
{
    return m_Up == 0x000000 && m_Down == 0x11111111 && m_Front == 0x22222222 && m_Back == 0x33333333 && m_Right == 0x44444444 && m_Left == 0x55555555;
}