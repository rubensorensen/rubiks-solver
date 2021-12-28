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

void CubeHandler::RotateByString(std::string& str)
{
    std::stringstream ss(str);
    while (getline(ss, str, ','))
    {
        if (str == "U")
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

        else if (str == "F")
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
