#include "../include/cube.hpp"

#include <algorithm>
#include <bitset>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>

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

void Cube::Display() const
{
    using std::cout;
    using std::endl;

    const char* table = "YWGBOR";

    cout << "        " << table[m_Up >> 28] << " " << table[m_Up >> 24 & 0x0F] << " "
         << table[m_Up >> 20 & 0x00F] << endl;
    cout << "        " << table[m_Up & 0x0000000F] << " " << 'Y' << " "
         << table[m_Up >> 16 & 0x000F] << endl;
    cout << "        " << table[m_Up >> 4 & 0x000000F] << " " << table[m_Up >> 8 & 0x00000F] << " "
         << table[m_Up >> 12 & 0x0000F] << endl;

    cout << endl;

    cout << " " << table[m_Left >> 28] << " " << table[m_Left >> 24 & 0x0F] << " "
         << table[m_Left >> 20 & 0x00F] << "  " << table[m_Front >> 28] << " "
         << table[m_Front >> 24 & 0x0F] << " " << table[m_Front >> 20 & 0x00F] << "  "
         << table[m_Right >> 28] << " " << table[m_Right >> 24 & 0x0F] << " "
         << table[m_Right >> 20 & 0x00F] << "  " << table[m_Back >> 28] << " "
         << table[m_Back >> 24 & 0x0F] << " " << table[m_Back >> 20 & 0x00F] << endl;

    cout << " " << table[m_Left & 0x0000000F] << " " << 'R' << " " << table[m_Left >> 16 & 0x000F]
         << "  " << table[m_Front & 0x0000000F] << " " << 'G' << " "
         << table[m_Front >> 16 & 0x000F] << "  " << table[m_Right & 0x0000000F] << " " << 'O'
         << " " << table[m_Right >> 16 & 0x000F] << "  " << table[m_Back & 0x0000000F] << " " << 'B'
         << " " << table[m_Back >> 16 & 0x000F] << endl;

    cout << " " << table[m_Left >> 4 & 0x000000F] << " " << table[m_Left >> 8 & 0x00000F] << " "
         << table[m_Left >> 12 & 0x0000F] << "  " << table[m_Front >> 4 & 0x000000F] << " "
         << table[m_Front >> 8 & 0x00000F] << " " << table[m_Front >> 12 & 0x0000F] << "  "
         << table[m_Right >> 4 & 0x000000F] << " " << table[m_Right >> 8 & 0x00000F] << " "
         << table[m_Right >> 12 & 0x0000F] << "  " << table[m_Back >> 4 & 0x000000F] << " "
         << table[m_Back >> 8 & 0x00000F] << " " << table[m_Back >> 12 & 0x0000F] << endl;

    cout << endl;

    cout << "        " << table[m_Down >> 28] << " " << table[m_Down >> 24 & 0x0F] << " "
         << table[m_Down >> 20 & 0x00F] << endl;
    cout << "        " << table[m_Down & 0x0000000F] << " " << 'W' << " "
         << table[m_Down >> 16 & 0x000F] << endl;
    cout << "        " << table[m_Down >> 4 & 0x000000F] << " " << table[m_Down >> 8 & 0x00000F]
         << " " << table[m_Down >> 12 & 0x0000F] << endl;

    cout << endl;
}

void Cube::Dump() const
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

void Cube::Shuffle(uint8_t n)
{
    std::vector<int32_t> moves(n);
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 17);
    std::for_each(moves.begin(), moves.end(), [&dist, &rng](int32_t& i) { i = dist(rng); });
    const char* mv[] = { "U", "U'", "U2", "D", "D'", "D2", "F", "F'", "F2",
                         "B", "B'", "B2", "R", "R'", "R2", "L", "L'", "L2" };

    std::cout << "Shuffling: ";
    for (auto& m : moves)
        std::cout << mv[m] << " ";
    std::cout << std::endl;

    for (auto& m : moves)
        Twist(static_cast<Cube::MOVE>(m));
}

bool Cube::IsSolved()
{
    return m_Up == 0x000000 && m_Down == 0x11111111 && m_Front == 0x22222222 &&
           m_Back == 0x33333333 && m_Right == 0x44444444 && m_Left == 0x55555555;
}

void Cube::RotateByString(std::string str)
{
    std::stringstream ss(str);
    while (getline(ss, str, ','))
        Twist(static_cast<Cube::MOVE>(stoi(str)));
}

void Cube::RotateFromFile(const char* filepath)
{
    std::string str;
    std::cerr << "[INFO] Opening file '" << filepath << "'->->->" << std::endl;
    std::ifstream file(filepath);
    if (file.is_open())
    {
        getline(file, str);
        file.close();
        RotateByString(str);
    }
    else
        std::cerr << "[ERROR] File path '" << filepath << "' not valid" << std::endl;
}

bool Cube::EdgesOriented() const
{
    std::array<uint32_t, 4> upEdges{ ((m_Up >> 24) & 0x0000000F), ((m_Up >> 16) & 0x0000000F),
                                     ((m_Up >> 8) & 0x0000000F), ((m_Up >> 0) & 0x0000000F) };

    std::array<uint32_t, 4> downEdges{ ((m_Down >> 24) & 0x0000000F), ((m_Down >> 16) & 0x0000000F),
                                       ((m_Down >> 8) & 0x0000000F), ((m_Down >> 0) & 0x0000000F) };

    std::array<uint32_t, 4> frontEdges{ ((m_Front >> 24) & 0x0000000F),
                                        ((m_Front >> 16) & 0x0000000F),
                                        ((m_Front >> 8) & 0x0000000F),
                                        ((m_Front >> 0) & 0x0000000F) };

    std::array<uint32_t, 4> backEdges{ ((m_Back >> 24) & 0x0000000F), ((m_Back >> 16) & 0x0000000F),
                                       ((m_Back >> 8) & 0x0000000F), ((m_Back >> 0) & 0x0000000F) };

    std::array<uint32_t, 4> rightEdges{ ((m_Right >> 24) & 0x0000000F),
                                        ((m_Right >> 16) & 0x0000000F),
                                        ((m_Right >> 8) & 0x0000000F),
                                        ((m_Right >> 0) & 0x0000000F) };

    std::array<uint32_t, 4> leftEdges{ ((m_Left >> 24) & 0x0000000F), ((m_Left >> 16) & 0x0000000F),
                                       ((m_Left >> 8) & 0x0000000F), ((m_Left >> 0) & 0x0000000F) };

    for (size_t i{ 0 }; i < 4; ++i)
    {
        // Are any orange or red stickers visible on edges on the front layer?
        if (frontEdges[i] == static_cast<uint8_t>(Cube::COLOR::ORANGE) ||
            frontEdges[i] == static_cast<uint8_t>(Cube::COLOR::RED))
            return false;
        // Are any yellow og white stickers visible on edges on the front layer?
        if (frontEdges[i] == static_cast<uint8_t>(Cube::COLOR::YELLOW) ||
            frontEdges[i] == static_cast<uint8_t>(Cube::COLOR::WHITE))
        {
            // Check other sticker of edge for a green or blue sticker
            switch (i)
            {
                case 0:
                    if (upEdges[2] == static_cast<uint8_t>(Cube::COLOR::GREEN) ||
                        upEdges[2] == static_cast<uint8_t>(Cube::COLOR::BLUE))
                        return false;
                    break;
                case 1:
                    if (rightEdges[3] == static_cast<uint8_t>(Cube::COLOR::GREEN) ||
                        rightEdges[3] == static_cast<uint8_t>(Cube::COLOR::BLUE))
                        return false;
                    break;
                case 2:
                    if (downEdges[0] == static_cast<uint8_t>(Cube::COLOR::GREEN) ||
                        downEdges[0] == static_cast<uint8_t>(Cube::COLOR::BLUE))
                        return false;
                    break;
                case 3:
                    if (leftEdges[1] == static_cast<uint8_t>(Cube::COLOR::GREEN) ||
                        leftEdges[1] == static_cast<uint8_t>(Cube::COLOR::BLUE))
                        return false;
                    break;
            }
        }
    }

    for (size_t i{ 0 }; i < 4; ++i)
    {
        // Are any orange or red stickers visible on edges on the back layer?
        if (backEdges[i] == static_cast<uint8_t>(Cube::COLOR::ORANGE) ||
            backEdges[i] == static_cast<uint8_t>(Cube::COLOR::RED))
            return false;
        // Are any yellow og white stickers visible on edges on the back layer?
        if (backEdges[i] == static_cast<uint8_t>(Cube::COLOR::YELLOW) ||
            backEdges[i] == static_cast<uint8_t>(Cube::COLOR::WHITE))
        {
            // Check other sticker of edge for a green or blue sticker
            switch (i)
            {
                case 0:
                    if (upEdges[0] == static_cast<uint8_t>(Cube::COLOR::GREEN) ||
                        upEdges[0] == static_cast<uint8_t>(Cube::COLOR::BLUE))
                        return false;
                    break;
                case 1:
                    if (leftEdges[3] == static_cast<uint8_t>(Cube::COLOR::GREEN) ||
                        leftEdges[3] == static_cast<uint8_t>(Cube::COLOR::BLUE))
                        return false;
                    break;
                case 2:
                    if (downEdges[2] == static_cast<uint8_t>(Cube::COLOR::GREEN) ||
                        downEdges[2] == static_cast<uint8_t>(Cube::COLOR::BLUE))
                        return false;
                    break;
                case 3:
                    if (rightEdges[1] == static_cast<uint8_t>(Cube::COLOR::GREEN) ||
                        rightEdges[1] == static_cast<uint8_t>(Cube::COLOR::BLUE))
                        return false;
                    break;
            }
        }
    }

    // Check up side of the S slice
    for (size_t i{ 1 }; i < 4; i += 2)
    {
        // Are any orange or red stickers visible on the up side of the S slice?
        if (upEdges[i] == static_cast<uint8_t>(Cube::COLOR::ORANGE) ||
            upEdges[i] == static_cast<uint8_t>(Cube::COLOR::RED))
            return false;
        // Are any yellow or white stickers visible on the up edges of the S slice?
        if (upEdges[i] == static_cast<uint8_t>(Cube::COLOR::YELLOW) ||
            upEdges[i] == static_cast<uint8_t>(Cube::COLOR::WHITE))
        {
            switch (i)
            {
                case 1:
                    if (rightEdges[0] == static_cast<uint8_t>(Cube::COLOR::GREEN) ||
                        rightEdges[0] == static_cast<uint8_t>(Cube::COLOR::BLUE))
                        return false;
                    break;
                case 3:
                    if (leftEdges[0] == static_cast<uint8_t>(Cube::COLOR::GREEN) ||
                        leftEdges[0] == static_cast<uint8_t>(Cube::COLOR::BLUE))
                        return false;
                    break;
            }
        }
    }

    // Check down side of the S slice
    for (size_t i{ 1 }; i < 4; i += 2)
    {
        // Are any orange or red stickers visible on the down side of the S slice?
        if (downEdges[i] == static_cast<uint8_t>(Cube::COLOR::ORANGE) ||
            downEdges[i] == static_cast<uint8_t>(Cube::COLOR::RED))
            return false;
        // Are any yellow or white stickers visible on the down edges of the middle layer?
        if (downEdges[i] == static_cast<uint8_t>(Cube::COLOR::YELLOW) ||
            downEdges[i] == static_cast<uint8_t>(Cube::COLOR::WHITE))
        {
            switch (i)
            {
                case 1:
                    if (rightEdges[2] == static_cast<uint8_t>(Cube::COLOR::GREEN) ||
                        rightEdges[2] == static_cast<uint8_t>(Cube::COLOR::BLUE))
                        return false;
                    break;
                case 3:
                    if (leftEdges[2] == static_cast<uint8_t>(Cube::COLOR::GREEN) ||
                        leftEdges[2] == static_cast<uint8_t>(Cube::COLOR::BLUE))
                        return false;
                    break;
            }
        }
    }

    // Passed all tests: All edges are oriented correctly
    return true;
}