#include "../include/cube_handler.h"

CubeHandler::CubeHandler(std::shared_ptr<Cube> cube) : m_Cube(cube) {}

void CubeHandler::ShuffleCube(uint8_t n)
{
    std::vector<int32_t> moves(n);
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 18);
    std::for_each(moves.begin(), moves.end(),
                  [&dist, &rng](int32_t& i) { i = dist(rng); });

    std::cout << "Shuffling: ";
    for (auto& m : moves)
        std::cout << m << " ";
    std::cout << std::endl;

    for (auto& m : moves)
    {
        switch (m)
        {
        case 0:
            m_Cube->Twist(Cube::MOVE::UP);
            break;
        case 1:
            m_Cube->Twist(Cube::MOVE::UPRIME);
            break;
        case 2:
            m_Cube->Twist(Cube::MOVE::UP2);
            break;
        case 3:
            m_Cube->Twist(Cube::MOVE::DOWN);
            break;
        case 4:
            m_Cube->Twist(Cube::MOVE::DPRIME);
            break;
        case 5:
            m_Cube->Twist(Cube::MOVE::DOWN2);
            break;
        case 6:
            m_Cube->Twist(Cube::MOVE::FRONT);
            break;
        case 7:
            m_Cube->Twist(Cube::MOVE::FPRIME);
            break;
        case 8:
            m_Cube->Twist(Cube::MOVE::FRONT2);
            break;
        case 9:
            m_Cube->Twist(Cube::MOVE::BACK);
            break;
        case 10:
            m_Cube->Twist(Cube::MOVE::BPRIME);
            break;
        case 11:
            m_Cube->Twist(Cube::MOVE::BACK2);
            break;
        case 12:
            m_Cube->Twist(Cube::MOVE::RIGHT);
            break;
        case 13:
            m_Cube->Twist(Cube::MOVE::RPRIME);
            break;
        case 14:
            m_Cube->Twist(Cube::MOVE::RIGHT2);
            break;
        case 15:
            m_Cube->Twist(Cube::MOVE::LEFT);
            break;
        case 16:
            m_Cube->Twist(Cube::MOVE::LPRIME);
            break;
        case 17:
            m_Cube->Twist(Cube::MOVE::LEFT2);
            break;
        }
    }
}

void CubeHandler::RotateByString(std::string& str)
{
    std::stringstream ss(str);
    while (getline(ss, str, ','))
    {
        if (str == "F")
            m_Cube->Twist(Cube::MOVE::FRONT);
        else if (str == "F'")
            m_Cube->Twist(Cube::MOVE::FPRIME);
        else if (str == "F2")
            m_Cube->Twist(Cube::MOVE::FRONT2);

        else if (str == "B")
            m_Cube->Twist(Cube::MOVE::BACK);
        else if (str == "B'")
            m_Cube->Twist(Cube::MOVE::BPRIME);
        else if (str == "B2")
            m_Cube->Twist(Cube::MOVE::BACK2);

        else if (str == "U")
            m_Cube->Twist(Cube::MOVE::UP);
        else if (str == "U'")
            m_Cube->Twist(Cube::MOVE::UPRIME);
        else if (str == "U2")
            m_Cube->Twist(Cube::MOVE::UP2);

        else if (str == "D")
            m_Cube->Twist(Cube::MOVE::DOWN);
        else if (str == "D'")
            m_Cube->Twist(Cube::MOVE::DPRIME);
        else if (str == "D2")
            m_Cube->Twist(Cube::MOVE::DOWN2);

        else if (str == "R")
            m_Cube->Twist(Cube::MOVE::RIGHT);
        else if (str == "R'")
            m_Cube->Twist(Cube::MOVE::RPRIME);
        else if (str == "R2")
            m_Cube->Twist(Cube::MOVE::RIGHT2);

        else if (str == "L")
            m_Cube->Twist(Cube::MOVE::LEFT);
        else if (str == "L'")
            m_Cube->Twist(Cube::MOVE::LPRIME);
        else if (str == "L2")
            m_Cube->Twist(Cube::MOVE::LEFT2);

        else
            std::cerr << "[ERROR] UNKNOWN ROTATION: " << str << std::endl;
    }
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
