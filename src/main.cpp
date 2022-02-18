#include "../include/breadth_first_searcher.hpp"
#include "../include/thistlethwaite.hpp"

#include <iostream>

uint32_t to_uint32(const char* str)
{
    return static_cast<uint32_t>(std::strtol(str, nullptr, 16));
}

int main(int argc, char* argv[])
{
    std::shared_ptr<Cube> cube = std::make_shared<Cube>();
    if (argc == 7)
        *cube = Cube(to_uint32(argv[1]), to_uint32(argv[2]), to_uint32(argv[3]), to_uint32(argv[4]),
                     to_uint32(argv[5]), to_uint32(argv[6]));

    cube->Shuffle(25);
    ThistlethwaiteSolver ts(cube);
    ts.SolveCube();

    return 0;
}
