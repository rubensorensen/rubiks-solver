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
