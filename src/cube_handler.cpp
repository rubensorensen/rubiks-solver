#include "../include/cube_handler.h"

CubeHandler::CubeHandler(std::shared_ptr<Cube> cube) : m_Cube(cube) {}

void CubeHandler::ShuffleCube(uint8_t n)
{
    std::vector<int32_t> moves(n);
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 18);
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
        case 1:
            m_Cube->F();
            break;
        case 2:
            m_Cube->Fprime();
            break;
        case 3:
            m_Cube->F2();
            break;
        case 4:
            m_Cube->B();
            break;
        case 5:
            m_Cube->Bprime();
            break;
        case 6:
            m_Cube->B2();
            break;
        case 7:
            m_Cube->U();
            break;
        case 8:
            m_Cube->Uprime();
            break;
        case 9:
            m_Cube->U2();
            break;
        case 10:
            m_Cube->D();
            break;
        case 11:
            m_Cube->Dprime();
            break;
        case 12:
            m_Cube->D2();
            break;
        case 13:
            m_Cube->R();
            break;
        case 14:
            m_Cube->Rprime();
            break;
        case 15:
            m_Cube->R2();
            break;
        case 16:
            m_Cube->L();
            break;
        case 17:
            m_Cube->Lprime();
            break;
        case 18:
            m_Cube->L2();
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
            m_Cube->F();
        else if (str == "F'")
            m_Cube->Fprime();
        else if (str == "F2")
            m_Cube->F2();

        else if (str == "B")
            m_Cube->B();
        else if (str == "B'")
            m_Cube->Bprime();
        else if (str == "B2")
            m_Cube->B2();

        else if (str == "U")
            m_Cube->U();
        else if (str == "U'")
            m_Cube->Uprime();
        else if (str == "U2")
            m_Cube->U2();

        else if (str == "D")
            m_Cube->D();
        else if (str == "D'")
            m_Cube->Dprime();
        else if (str == "D2")
            m_Cube->D2();

        else if (str == "R")
            m_Cube->R();
        else if (str == "R'")
            m_Cube->Rprime();
        else if (str == "R2")
            m_Cube->R2();

        else if (str == "L")
            m_Cube->L();
        else if (str == "L'")
            m_Cube->Lprime();
        else if (str == "L2")
            m_Cube->L2();

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
