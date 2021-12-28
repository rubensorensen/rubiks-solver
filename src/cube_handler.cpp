#include "../include/cube_handler.h"

CubeHandler::CubeHandler(std::shared_ptr<Cube> cube) : m_Cube(cube) {}

void CubeHandler::ShuffleCube(uint8_t n)
{
    std::vector<int32_t> moves(n);
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 17);
    std::for_each(moves.begin(), moves.end(),
                  [&dist, &rng](int32_t& i) { i = dist(rng); });

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

void CubeHandler::PrintEdges()
{
    std::array<uint32_t, 4> upEdges{
        ((m_Cube->m_Up >> 24) & 0x0000000F), ((m_Cube->m_Up >> 16) & 0x0000000F),
        ((m_Cube->m_Up >> 8) & 0x0000000F), ((m_Cube->m_Up >> 0) & 0x0000000F)};

    std::array<uint32_t, 4> downEdges{
        ((m_Cube->m_Down >> 24) & 0x0000000F), ((m_Cube->m_Down >> 16) & 0x0000000F),
        ((m_Cube->m_Down >> 8) & 0x0000000F), ((m_Cube->m_Down >> 0) & 0x0000000F)};

    std::array<uint32_t, 4> frontEdges{
        ((m_Cube->m_Front >> 24) & 0x0000000F), ((m_Cube->m_Front >> 16) & 0x0000000F),
        ((m_Cube->m_Front >> 8) & 0x0000000F), ((m_Cube->m_Front >> 0) & 0x0000000F)};

    std::array<uint32_t, 4> backEdges{
        ((m_Cube->m_Back >> 24) & 0x0000000F), ((m_Cube->m_Back >> 16) & 0x0000000F),
        ((m_Cube->m_Back >> 8) & 0x0000000F), ((m_Cube->m_Back >> 0) & 0x0000000F)};

    std::array<uint32_t, 4> rightEdges{
        ((m_Cube->m_Right >> 24) & 0x0000000F), ((m_Cube->m_Right >> 16) & 0x0000000F),
        ((m_Cube->m_Right >> 8) & 0x0000000F), ((m_Cube->m_Right >> 0) & 0x0000000F)};

    std::array<uint32_t, 4> leftEdges{
        ((m_Cube->m_Left >> 24) & 0x0000000F), ((m_Cube->m_Left >> 16) & 0x0000000F),
        ((m_Cube->m_Left >> 8) & 0x0000000F), ((m_Cube->m_Left >> 0) & 0x0000000F)};

    std::array<std::array<uint32_t, 4>, 6> faces{upEdges,   downEdges,  frontEdges,
                                                 backEdges, rightEdges, leftEdges};
    for (auto& f : faces)
    {
        std::cout << "2: " << f[0] << std::endl;
        std::cout << "4: " << f[1] << std::endl;
        std::cout << "6: " << f[2] << std::endl;
        std::cout << "8: " << f[3] << std::endl;
        std::cout << std::endl;
    }
}

bool CubeHandler::EdgesOriented()
{
    std::array<uint32_t, 4> upEdges{
        ((m_Cube->m_Up >> 24) & 0x0000000F), ((m_Cube->m_Up >> 16) & 0x0000000F),
        ((m_Cube->m_Up >> 8) & 0x0000000F), ((m_Cube->m_Up >> 0) & 0x0000000F)};

    std::array<uint32_t, 4> downEdges{
        ((m_Cube->m_Down >> 24) & 0x0000000F), ((m_Cube->m_Down >> 16) & 0x0000000F),
        ((m_Cube->m_Down >> 8) & 0x0000000F), ((m_Cube->m_Down >> 0) & 0x0000000F)};

    std::array<uint32_t, 4> frontEdges{
        ((m_Cube->m_Front >> 24) & 0x0000000F), ((m_Cube->m_Front >> 16) & 0x0000000F),
        ((m_Cube->m_Front >> 8) & 0x0000000F), ((m_Cube->m_Front >> 0) & 0x0000000F)};

    std::array<uint32_t, 4> backEdges{
        ((m_Cube->m_Back >> 24) & 0x0000000F), ((m_Cube->m_Back >> 16) & 0x0000000F),
        ((m_Cube->m_Back >> 8) & 0x0000000F), ((m_Cube->m_Back >> 0) & 0x0000000F)};

    std::array<uint32_t, 4> rightEdges{
        ((m_Cube->m_Right >> 24) & 0x0000000F), ((m_Cube->m_Right >> 16) & 0x0000000F),
        ((m_Cube->m_Right >> 8) & 0x0000000F), ((m_Cube->m_Right >> 0) & 0x0000000F)};

    std::array<uint32_t, 4> leftEdges{
        ((m_Cube->m_Left >> 24) & 0x0000000F), ((m_Cube->m_Left >> 16) & 0x0000000F),
        ((m_Cube->m_Left >> 8) & 0x0000000F), ((m_Cube->m_Left >> 0) & 0x0000000F)};

    for (size_t i{0}; i < 4; ++i)
    {
        // Are any orange or red stickers visible on edges on the up layer?
        if (upEdges[i] == Cube::COLOR::ORANGE || upEdges[i] == Cube::COLOR::RED)
            std::cout << "ORANGE/RED STICKER ON UP LAYER" << std::endl; // return false;
        // Are any green og blue stickers visible on edges on the up layer?
        if (upEdges[i] == Cube::COLOR::GREEN || upEdges[i] == Cube::COLOR::BLUE)
        {
            std::cout << "GREEN/BLUE STICKER ON UP LAYER" << std::endl;
            // Check other sticker of edge for a yellow or white sticker
            switch (i)
            {
            case 0:
                if (backEdges[0] == Cube::COLOR::YELLOW ||
                    backEdges[0] == Cube::COLOR::WHITE)
                    return false;
                break;
            case 1:
                if (rightEdges[0] == Cube::COLOR::YELLOW ||
                    rightEdges[0] == Cube::COLOR::WHITE)
                    return false;
                break;
            case 2:
                if (frontEdges[0] == Cube::COLOR::YELLOW ||
                    frontEdges[0] == Cube::COLOR::WHITE)
                    return false;
                break;
            case 3:
                if (leftEdges[0] == Cube::COLOR::YELLOW ||
                    leftEdges[0] == Cube::COLOR::WHITE)
                    return false;
                break;
            }
        }
    }

    for (size_t i{0}; i < 4; ++i)
    {
        // Are any orange or red stickers visible on edges on the down layer?
        if (downEdges[i] == Cube::COLOR::ORANGE || downEdges[i] == Cube::COLOR::RED)
            return false;
        // Are any green og blue stickers visible on edges on the down layer?
        if (downEdges[i] == Cube::COLOR::GREEN || downEdges[i] == Cube::COLOR::BLUE)
        {
            // Check other sticker of edge for a yellow or white sticker
            switch (i)
            {
            case 0:
                if (frontEdges[2] == Cube::COLOR::YELLOW ||
                    frontEdges[2] == Cube::COLOR::WHITE)
                    return false;
                break;
            case 1:
                if (rightEdges[2] == Cube::COLOR::YELLOW ||
                    rightEdges[2] == Cube::COLOR::WHITE)
                    return false;
                break;
            case 2:
                if (backEdges[2] == Cube::COLOR::YELLOW ||
                    backEdges[2] == Cube::COLOR::WHITE)
                    return false;
                break;
            case 3:
                if (leftEdges[2] == Cube::COLOR::YELLOW ||
                    leftEdges[2] == Cube::COLOR::WHITE)
                    return false;
                break;
            }
        }
    }

    // Check front side of the middle layer (E slice)
    for (size_t i{1}; i < 4; i += 2)
    {
        // Are any orange or red stickers visible on the front side of the middle layer?
        if (frontEdges[i] == Cube::COLOR::ORANGE || frontEdges[i] == Cube::COLOR::RED)
            return false;
        // Are any green or blue stickers visible on the front edges of the middle layer?
        if (frontEdges[i] == Cube::COLOR::GREEN || frontEdges[i] == Cube::COLOR::BLUE)
        {
            switch (i)
            {
            case 1:
                if (rightEdges[3] == Cube::COLOR::YELLOW ||
                    rightEdges[3] == Cube::COLOR::WHITE)
                    return false;
                break;
            case 3:
                if (leftEdges[1] == Cube::COLOR::YELLOW ||
                    leftEdges[1] == Cube::COLOR::WHITE)
                    return false;
                break;
            }
        }
    }

    // Check back side of the middle layer (E slice)
    for (size_t i{1}; i < 4; i += 2)
    {
        // Are any orange or red stickers visible on the front side of the middle layer?
        if (backEdges[i] == Cube::COLOR::ORANGE || backEdges[i] == Cube::COLOR::RED)
            return false;
        // Are any green or blue stickers visible on the front edges of the middle layer?
        if (backEdges[i] == Cube::COLOR::GREEN || backEdges[i] == Cube::COLOR::BLUE)
        {
            switch (i)
            {
            case 1:
                if (leftEdges[3] == Cube::COLOR::YELLOW ||
                    leftEdges[3] == Cube::COLOR::WHITE)
                    return false;
                break;
            case 3:
                if (rightEdges[1] == Cube::COLOR::YELLOW ||
                    rightEdges[1] == Cube::COLOR::WHITE)
                    return false;
                break;
            }
        }
    }

    // Passed all tests: All edges are oriented correctly
    return true;
}
