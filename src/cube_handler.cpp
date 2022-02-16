#include "../include/cube_handler.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

CubeHandler::CubeHandler(std::shared_ptr<Cube> cube) : m_Cube(cube) {}

void CubeHandler::ShuffleCube(uint8_t n)
{
    std::vector<int32_t>                                     moves(n);
    std::random_device                                       dev;
    std::mt19937                                             rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 17);
    std::for_each(moves.begin(), moves.end(), [&dist, &rng](int32_t& i) { i = dist(rng); });

    std::cout << "Shuffling: ";
    for (auto& m : moves)
        std::cout << m << " ";
    std::cout << std::endl;

    for (auto& m : moves)
        m_Cube->Twist(static_cast<Cube::MOVE>(m));
}

void CubeHandler::RotateByString(std::string str)
{
    std::stringstream ss(str);
    while (getline(ss, str, ','))
        m_Cube->Twist(static_cast<Cube::MOVE>(stoi(str)));
}

void CubeHandler::RotateFromFile(const char* filepath)
{
    std::string str;
    std::cerr << "[INFO] Opening file '" << filepath << "'..." << std::endl;
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

bool CubeHandler::EdgesOriented()
{
    std::array<uint32_t, 4> upEdges{ ((m_Cube->m_Up >> 24) & 0x0000000F), ((m_Cube->m_Up >> 16) & 0x0000000F), ((m_Cube->m_Up >> 8) & 0x0000000F), ((m_Cube->m_Up >> 0) & 0x0000000F) };

    std::array<uint32_t, 4> downEdges{ ((m_Cube->m_Down >> 24) & 0x0000000F), ((m_Cube->m_Down >> 16) & 0x0000000F), ((m_Cube->m_Down >> 8) & 0x0000000F), ((m_Cube->m_Down >> 0) & 0x0000000F) };

    std::array<uint32_t, 4> frontEdges{ ((m_Cube->m_Front >> 24) & 0x0000000F), ((m_Cube->m_Front >> 16) & 0x0000000F), ((m_Cube->m_Front >> 8) & 0x0000000F), ((m_Cube->m_Front >> 0) & 0x0000000F) };

    std::array<uint32_t, 4> backEdges{ ((m_Cube->m_Back >> 24) & 0x0000000F), ((m_Cube->m_Back >> 16) & 0x0000000F), ((m_Cube->m_Back >> 8) & 0x0000000F), ((m_Cube->m_Back >> 0) & 0x0000000F) };

    std::array<uint32_t, 4> rightEdges{ ((m_Cube->m_Right >> 24) & 0x0000000F), ((m_Cube->m_Right >> 16) & 0x0000000F), ((m_Cube->m_Right >> 8) & 0x0000000F), ((m_Cube->m_Right >> 0) & 0x0000000F) };

    std::array<uint32_t, 4> leftEdges{ ((m_Cube->m_Left >> 24) & 0x0000000F), ((m_Cube->m_Left >> 16) & 0x0000000F), ((m_Cube->m_Left >> 8) & 0x0000000F), ((m_Cube->m_Left >> 0) & 0x0000000F) };

    for (size_t i{ 0 }; i < 4; ++i)
    {
        // Are any orange or red stickers visible on edges on the front layer?
        if (frontEdges[i] == static_cast<uint8_t>(Cube::COLOR::ORANGE) || frontEdges[i] == static_cast<uint8_t>(Cube::COLOR::RED))
            return false;
        // Are any yellow og white stickers visible on edges on the front layer?
        if (frontEdges[i] == static_cast<uint8_t>(Cube::COLOR::YELLOW) || frontEdges[i] == static_cast<uint8_t>(Cube::COLOR::WHITE))
        {
            // Check other sticker of edge for a green or blue sticker
            switch (i)
            {
                case 0:
                    if (upEdges[2] == static_cast<uint8_t>(Cube::COLOR::GREEN) || upEdges[2] == static_cast<uint8_t>(Cube::COLOR::BLUE))
                        return false;
                    break;
                case 1:
                    if (rightEdges[3] == static_cast<uint8_t>(Cube::COLOR::GREEN) || rightEdges[3] == static_cast<uint8_t>(Cube::COLOR::BLUE))
                        return false;
                    break;
                case 2:
                    if (downEdges[0] == static_cast<uint8_t>(Cube::COLOR::GREEN) || downEdges[0] == static_cast<uint8_t>(Cube::COLOR::BLUE))
                        return false;
                    break;
                case 3:
                    if (leftEdges[1] == static_cast<uint8_t>(Cube::COLOR::GREEN) || leftEdges[1] == static_cast<uint8_t>(Cube::COLOR::BLUE))
                        return false;
                    break;
            }
        }
    }

    for (size_t i{ 0 }; i < 4; ++i)
    {
        // Are any orange or red stickers visible on edges on the back layer?
        if (backEdges[i] == static_cast<uint8_t>(Cube::COLOR::ORANGE) || backEdges[i] == static_cast<uint8_t>(Cube::COLOR::RED))
            return false;
        // Are any yellow og white stickers visible on edges on the back layer?
        if (backEdges[i] == static_cast<uint8_t>(Cube::COLOR::YELLOW) || backEdges[i] == static_cast<uint8_t>(Cube::COLOR::WHITE))
        {
            // Check other sticker of edge for a green or blue sticker
            switch (i)
            {
                case 0:
                    if (upEdges[0] == static_cast<uint8_t>(Cube::COLOR::GREEN) || upEdges[0] == static_cast<uint8_t>(Cube::COLOR::BLUE))
                        return false;
                    break;
                case 1:
                    if (leftEdges[3] == static_cast<uint8_t>(Cube::COLOR::GREEN) || leftEdges[3] == static_cast<uint8_t>(Cube::COLOR::BLUE))
                        return false;
                    break;
                case 2:
                    if (downEdges[2] == static_cast<uint8_t>(Cube::COLOR::GREEN) || downEdges[2] == static_cast<uint8_t>(Cube::COLOR::BLUE))
                        return false;
                    break;
                case 3:
                    if (rightEdges[1] == static_cast<uint8_t>(Cube::COLOR::GREEN) || rightEdges[1] == static_cast<uint8_t>(Cube::COLOR::BLUE))
                        return false;
                    break;
            }
        }
    }

    // Check up side of the S slice
    for (size_t i{ 1 }; i < 4; i += 2)
    {
        // Are any orange or red stickers visible on the up side of the S slice?
        if (upEdges[i] == static_cast<uint8_t>(Cube::COLOR::ORANGE) || upEdges[i] == static_cast<uint8_t>(Cube::COLOR::RED))
            return false;
        // Are any yellow or white stickers visible on the up edges of the S slice?
        if (upEdges[i] == static_cast<uint8_t>(Cube::COLOR::YELLOW) || upEdges[i] == static_cast<uint8_t>(Cube::COLOR::WHITE))
        {
            switch (i)
            {
                case 1:
                    if (rightEdges[0] == static_cast<uint8_t>(Cube::COLOR::GREEN) || rightEdges[0] == static_cast<uint8_t>(Cube::COLOR::BLUE))
                        return false;
                    break;
                case 3:
                    if (leftEdges[0] == static_cast<uint8_t>(Cube::COLOR::GREEN) || leftEdges[0] == static_cast<uint8_t>(Cube::COLOR::BLUE))
                        return false;
                    break;
            }
        }
    }

    // Check down side of the S slice
    for (size_t i{ 1 }; i < 4; i += 2)
    {
        // Are any orange or red stickers visible on the down side of the S slice?
        if (downEdges[i] == static_cast<uint8_t>(Cube::COLOR::ORANGE) || downEdges[i] == static_cast<uint8_t>(Cube::COLOR::RED))
            return false;
        // Are any yellow or white stickers visible on the down edges of the middle layer?
        if (downEdges[i] == static_cast<uint8_t>(Cube::COLOR::YELLOW) || downEdges[i] == static_cast<uint8_t>(Cube::COLOR::WHITE))
        {
            switch (i)
            {
                case 1:
                    if (rightEdges[2] == static_cast<uint8_t>(Cube::COLOR::GREEN) || rightEdges[2] == static_cast<uint8_t>(Cube::COLOR::BLUE))
                        return false;
                    break;
                case 3:
                    if (leftEdges[2] == static_cast<uint8_t>(Cube::COLOR::GREEN) || leftEdges[2] == static_cast<uint8_t>(Cube::COLOR::BLUE))
                        return false;
                    break;
            }
        }
    }

    // Passed all tests: All edges are oriented correctly
    return true;
}
