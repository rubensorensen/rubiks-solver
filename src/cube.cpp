#include "../include/cube.h"

//	Bitwise rotation m_Right
template <class N>
N ror(const N n, const uint8_t d)
{
    return n >> d | n << (sizeof(n) * 8 - d);
}

//	Bitwise rotation m_Left
template <class N>
N rol(const N n, const uint8_t d)
{
    return n << d | n >> (sizeof(n) * 8 - d);
}

Cube::Cube(uint32_t up, uint32_t down, uint32_t front, uint32_t back, uint32_t right,
           uint32_t left)
{
    m_Up = {up};
    m_Down = {down};
    m_Front = {front};
    m_Back = {back};
    m_Right = {right};
    m_Left = {left};
}

/****************************\
        CUBE ROTATIONS
\****************************/

//	Front Quarter-Turn Clockwise
void Cube::F()
{
    const uint32_t tmp{m_Up};
    m_Up = {(m_Up & 0xFFFF000F) | ror((m_Left & 0x00FFF000), 8)};
    m_Left = {(m_Left & 0xFF000FFF) | ror((m_Down & 0xFFF00000), 8)};
    m_Down = {(m_Down & 0x000FFFFF) | ror((m_Right & 0xF00000FF), 8)};
    m_Right = {(m_Right & 0x0FFFFF00) | ror((tmp & 0x0000FFF0), 8)};
    m_Front = {ror(m_Front, 8)};
}

//	Front Quarter-Turn Anti-Clockwise
void Cube::Fprime()
{
    const uint32_t tmp{m_Up};
    m_Up = {(m_Up & 0xFFFF000F) | rol((m_Right & 0xF00000FF), 8)};
    m_Right = {(m_Right & 0x0FFFFF00) | rol((m_Down & 0xFFF00000), 8)};
    m_Down = {(m_Down & 0x000FFFFF) | rol((m_Left & 0x00FFF000), 8)};
    m_Left = {(m_Left & 0xFF000FFF) | rol((tmp & 0x0000FFF0), 8)};
    m_Front = {rol(m_Front, 8)};
}

//	Front Half-Turn
void Cube::F2()
{
    uint32_t tmp{m_Up};
    m_Up = {(m_Up & 0xFFFF000F) | ror((m_Down & 0xFFF00000), 16)};
    m_Down = {(m_Down & 0x000FFFFF) | ror((tmp & 0x0000FFF0), 16)};
    tmp = {m_Right};
    m_Right = {(m_Right & 0x0FFFFF00) | ror((m_Left & 0x00FFF000), 16)};
    m_Left = {(m_Left & 0xFF000FFF) | ror((tmp & 0xF00000FF), 16)};
    m_Front = {ror(m_Front, 16)};
}

//	Back Quarter-Turn Clockwise
void Cube::B()
{
    const uint32_t tmp{m_Up};
    m_Up = {(m_Up & 0x000FFFFF) | rol((m_Right & 0x00FFF000), 8)};
    m_Right = {(m_Right & 0xFF000FFF) | rol((m_Down & 0x0000FFF0), 8)};
    m_Down = {(m_Down & 0xFFFF000F) | rol((m_Left & 0xF00000FF), 8)};
    m_Left = {(m_Left & 0x0FFFFF00) | rol((tmp & 0xFFF00000), 8)};
    m_Back = {ror(m_Back, 8)};
}

//	Back Quarter-Turn Anti-Clockwise
void Cube::Bprime()
{
    const uint32_t tmp{m_Up};
    m_Up = {(m_Up & 0x000FFFFF) | ror((m_Left & 0xF00000FF), 8)};
    m_Left = {(m_Left & 0x0FFFFF00) | ror((m_Down & 0x0000FFF0), 8)};
    m_Down = {(m_Down & 0xFFFF000F) | ror((m_Right & 0x00FFF000), 8)};
    m_Right = {(m_Right & 0xFF000FFF) | ror((tmp & 0xFFF00000), 8)};
    m_Back = {rol(m_Back, 8)};
}

//	Back Half-Turn
void Cube::B2()
{
    uint32_t tmp{m_Up};
    m_Up = {(m_Up & 0x000FFFFF) | rol((m_Down & 0x0000FFF0), 16)};
    m_Down = {(m_Down & 0xFFFF000F) | rol((tmp & 0xFFF00000), 16)};
    tmp = {m_Left};
    m_Left = {(m_Left & 0x0FFFFF00) | rol((m_Right & 0x00FFF000), 16)};
    m_Right = {(m_Right & 0xFF000FFF) | rol((tmp & 0xF00000FF), 16)};
    m_Back = {ror(m_Back, 16)};
}

//	Up Quarter-Turn Clockwise
void Cube::U()
{
    const uint32_t tmp{m_Front};
    m_Front = {(m_Front & 0x000FFFFF) | (m_Right & 0xFFF00000)};
    m_Right = {(m_Right & 0x000FFFFF) | (m_Back & 0xFFF00000)};
    m_Back = {(m_Back & 0x000FFFFF) | (m_Left & 0xFFF00000)};
    m_Left = {(m_Left & 0x000FFFFF) | (tmp & 0xFFF00000)};
    m_Up = {ror(m_Up, 8)};
}

//	Up Quarter-Turn Anti-Clockwise
void Cube::Uprime()
{
    const uint32_t tmp{m_Front};
    m_Front = {(m_Front & 0x000FFFFF) | (m_Left & 0xFFF00000)};
    m_Left = {(m_Left & 0x000FFFFF) | (m_Back & 0xFFF00000)};
    m_Back = {(m_Back & 0x000FFFFF) | (m_Right & 0xFFF00000)};
    m_Right = {(m_Right & 0x000FFFFF) | (tmp & 0xFFF00000)};
    m_Up = {rol(m_Up, 8)};
}

//	Up Half-Turn
void Cube::U2()
{
    uint32_t tmp{m_Front};
    m_Front = {(m_Front & 0x000FFFFF) | (m_Back & 0xFFF00000)};
    m_Back = {(m_Back & 0x000FFFFF) | (tmp & 0xFFF00000)};
    tmp = {m_Left};
    m_Left = {(m_Left & 0x000FFFFF) | (m_Right & 0xFFF00000)};
    m_Right = {(m_Right & 0x000FFFFF) | (tmp & 0xFFF00000)};
    m_Up = {ror(m_Up, 16)};
}

//	Down Quarter-Turn Clockwise
void Cube::D()
{
    const uint32_t tmp{m_Front};
    m_Front = {(m_Front & 0xFFFF000F) | (m_Left & 0x0000FFF0)};
    m_Left = {(m_Left & 0xFFFF000F) | (m_Back & 0x0000FFF0)};
    m_Back = {(m_Back & 0xFFFF000F) | (m_Right & 0x0000FFF0)};
    m_Right = {(m_Right & 0xFFFF000F) | (tmp & 0x0000FFF0)};
    m_Down = {ror(m_Down, 8)};
}

//	Down Quarter-Turn Anti-Clockwise
void Cube::Dprime()
{
    const uint32_t tmp{m_Front};
    m_Front = {(m_Front & 0xFFFF000F) | (m_Right & 0x0000FFF0)};
    m_Right = {(m_Right & 0xFFFF000F) | (m_Back & 0x0000FFF0)};
    m_Back = {(m_Back & 0xFFFF000F) | (m_Left & 0x0000FFF0)};
    m_Left = {(m_Left & 0xFFFF000F) | (tmp & 0x0000FFF0)};
    m_Down = {rol(m_Down, 8)};
}

//	Down Half-Turn
void Cube::D2()
{
    uint32_t tmp{m_Front};
    m_Front = {(m_Front & 0xFFFF000F) | (m_Back & 0x0000FFF0)};
    m_Back = {(m_Back & 0xFFFF000F) | (tmp & 0x0000FFF0)};
    tmp = {m_Left};
    m_Left = {(m_Left & 0xFFFF000F) | (m_Right & 0x0000FFF0)};
    m_Right = {(m_Right & 0xFFFF000F) | (tmp & 0x0000FFF0)};
    m_Down = {ror(m_Down, 16)};
}

// Right Quarter-Turn Clockwise
void Cube::R()
{
    const uint32_t tmp{m_Front};
    m_Front = {(m_Front & 0xFF000FFF) | (m_Down & 0x00FFF000)};
    m_Down = {(m_Down & 0xFF000FFF) | ror((m_Back & 0xF00000FF), 16)};
    m_Back = {(m_Back & 0x0FFFFF00) | ror((m_Up & 0x00FFF000), 16)};
    m_Up = {(m_Up & 0xFF000FFF) | (tmp & 0x00FFF000)};
    m_Right = {ror(m_Right, 8)};
}

//	Right Quarter-Turn Anti-Clockwise
void Cube::Rprime()
{
    const uint32_t tmp{m_Front};
    m_Front = {(m_Front & 0xFF000FFF) | (m_Up & 0x00FFF000)};
    m_Up = {(m_Up & 0xFF000FFF) | rol((m_Back & 0xF00000FF), 16)};
    m_Back = {(m_Back & 0x0FFFFF00) | rol((m_Down & 0x00FFF000), 16)};
    m_Down = {(m_Down & 0xFF000FFF) | (tmp & 0x00FFF000)};
    m_Right = {rol(m_Right, 8)};
}

//	Right Half-Turn
void Cube::R2()
{
    uint32_t tmp{m_Front};
    m_Front = {(m_Front & 0xFF000FFF) | ror((m_Back & 0xF00000FF), 16)};
    m_Back = {(m_Back & 0x0FFFFF00) | ror((tmp & 0x00FFF000), 16)};
    tmp = {m_Up};
    m_Up = {(m_Up & 0xFF000FFF) | (m_Down & 0x00FFF000)};
    m_Down = {(m_Down & 0xFF000FFF) | (tmp & 0x00FFF000)};
    m_Right = {ror(m_Right, 16)};
}

//	Left Quarter-Turn Clockwise
void Cube::L()
{
    const uint32_t tmp{m_Front};
    m_Front = {(m_Front & 0x0FFFFF00) | (m_Up & 0xF00000FF)};
    m_Up = {(m_Up & 0x0FFFFF00) | ror((m_Back & 0x00FFF000), 16)};
    m_Back = {(m_Back & 0xFF000FFF) | ror((m_Down & 0xF00000FF), 16)};
    m_Down = {(m_Down & 0x0FFFFF00) | (tmp & 0xF00000FF)};
    m_Left = {ror(m_Left, 8)};
}

//  Left Quarter-Turn Anti-Clockwise
void Cube::Lprime()
{
    const uint32_t tmp{m_Front};
    m_Front = {(m_Front & 0x0FFFFF00) | (m_Down & 0xF00000FF)};
    m_Down = {(m_Down & 0x0FFFFF00) | rol((m_Back & 0x00FFF000), 16)};
    m_Back = {(m_Back & 0xFF000FFF) | rol((m_Up & 0xF00000FF), 16)};
    m_Up = {(m_Up & 0x0FFFFF00) | (tmp & 0xF00000FF)};
    m_Left = {rol(m_Left, 8)};
}

//  Left Half-Turn
void Cube::L2()
{
    uint32_t tmp{m_Front};
    m_Front = {(m_Front & 0x0FFFFF00) | ror((m_Back & 0x00FFF000), 16)};
    m_Back = {(m_Back & 0xFF000FFF) | ror((tmp & 0xF00000FF), 16)};
    tmp = {m_Up};
    m_Up = {(m_Up & 0x0FFFFF00) | (m_Down & 0xF00000FF)};
    m_Down = {(m_Down & 0x0FFFFF00) | (tmp & 0xF00000FF)};
    m_Left = {ror(m_Left, 16)};
}

void Cube::ShowCube() const
{
    using std::cout;
    using std::endl;

    PrintVals();

    cout << "        " << GetColor(m_Up >> 28) << " " << GetColor(m_Up >> 24 & 0x0F)
         << " " << GetColor(m_Up >> 20 & 0x00F) << endl;
    cout << "        " << GetColor(m_Up & 0x0000000F) << " " << 'Y' << " "
         << GetColor(m_Up >> 16 & 0x000F) << endl;
    cout << "        " << GetColor(m_Up >> 4 & 0x000000F) << " "
         << GetColor(m_Up >> 8 & 0x00000F) << " " << GetColor(m_Up >> 12 & 0x0000F)
         << endl;

    cout << endl;

    cout << " " << GetColor(m_Left >> 28) << " " << GetColor(m_Left >> 24 & 0x0F) << " "
         << GetColor(m_Left >> 20 & 0x00F) << "  " << GetColor(m_Front >> 28) << " "
         << GetColor(m_Front >> 24 & 0x0F) << " " << GetColor(m_Front >> 20 & 0x00F)
         << "  " << GetColor(m_Right >> 28) << " " << GetColor(m_Right >> 24 & 0x0F)
         << " " << GetColor(m_Right >> 20 & 0x00F) << "  " << GetColor(m_Back >> 28)
         << " " << GetColor(m_Back >> 24 & 0x0F) << " " << GetColor(m_Back >> 20 & 0x00F)
         << endl;

    cout << " " << GetColor(m_Left & 0x0000000F) << " " << 'R' << " "
         << GetColor(m_Left >> 16 & 0x000F) << "  " << GetColor(m_Front & 0x0000000F)
         << " " << 'G' << " " << GetColor(m_Front >> 16 & 0x000F) << "  "
         << GetColor(m_Right & 0x0000000F) << " " << 'O' << " "
         << GetColor(m_Right >> 16 & 0x000F) << "  " << GetColor(m_Back & 0x0000000F)
         << " " << 'B' << " " << GetColor(m_Back >> 16 & 0x000F) << endl;

    cout << " " << GetColor(m_Left >> 4 & 0x000000F) << " "
         << GetColor(m_Left >> 8 & 0x00000F) << " " << GetColor(m_Left >> 12 & 0x0000F)
         << "  " << GetColor(m_Front >> 4 & 0x000000F) << " "
         << GetColor(m_Front >> 8 & 0x00000F) << " " << GetColor(m_Front >> 12 & 0x0000F)
         << "  " << GetColor(m_Right >> 4 & 0x000000F) << " "
         << GetColor(m_Right >> 8 & 0x00000F) << " " << GetColor(m_Right >> 12 & 0x0000F)
         << "  " << GetColor(m_Back >> 4 & 0x000000F) << " "
         << GetColor(m_Back >> 8 & 0x00000F) << " " << GetColor(m_Back >> 12 & 0x0000F)
         << endl;

    cout << endl;

    cout << "        " << GetColor(m_Down >> 28) << " " << GetColor(m_Down >> 24 & 0x0F)
         << " " << GetColor(m_Down >> 20 & 0x00F) << endl;
    cout << "        " << GetColor(m_Down & 0x0000000F) << " " << 'W' << " "
         << GetColor(m_Down >> 16 & 0x000F) << endl;
    cout << "        " << GetColor(m_Down >> 4 & 0x000000F) << " "
         << GetColor(m_Down >> 8 & 0x00000F) << " " << GetColor(m_Down >> 12 & 0x0000F)
         << endl;

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
    return m_Up == 0x000000 && m_Down == 0x11111111 && m_Front == 0x22222222 &&
           m_Back == 0x33333333 && m_Right == 0x44444444 && m_Left == 0x55555555;
}

void Cube::RotateByString(std::string str)
{
    std::stringstream ss(str);
    while (getline(ss, str, ','))
    {
        if (str == "F")
            F();
        else if (str == "F'")
            Fprime();
        else if (str == "F2")
            F2();

        else if (str == "B")
            B();
        else if (str == "B'")
            Bprime();
        else if (str == "B2")
            B2();

        else if (str == "U")
            U();
        else if (str == "U'")
            Uprime();
        else if (str == "U2")
            U2();

        else if (str == "D")
            D();
        else if (str == "D'")
            Dprime();
        else if (str == "D2")
            D2();

        else if (str == "R")
            R();
        else if (str == "R'")
            Rprime();
        else if (str == "R2")
            R2();

        else if (str == "L")
            L();
        else if (str == "L'")
            Lprime();
        else if (str == "L2")
            L2();

        else
            std::cerr << "[ERROR] UNKNOWN ROTATION: " << str << std::endl;
    }
}

void Cube::RotateFromFile(const char* filepath)
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

void Cube::Shuffle(const uint8_t n)
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
            F();
            break;
        case 2:
            Fprime();
            break;
        case 3:
            F2();
            break;
        case 4:
            B();
            break;
        case 5:
            Bprime();
            break;
        case 6:
            B2();
            break;
        case 7:
            U();
            break;
        case 8:
            Uprime();
            break;
        case 9:
            U2();
            break;
        case 10:
            D();
            break;
        case 11:
            Dprime();
            break;
        case 12:
            D2();
            break;
        case 13:
            R();
            break;
        case 14:
            Rprime();
            break;
        case 15:
            R2();
            break;
        case 16:
            L();
            break;
        case 17:
            Lprime();
            break;
        case 18:
            L2();
            break;
        }
    }
}
