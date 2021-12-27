#include "../include/cube.h"
#include "../include/patterns.h"

uint32_t to_uint32(const char* str)
{
    return static_cast<uint32_t>(std::strtol(str, nullptr, 16));
}

int main(int argc, char* argv[])
{
    Cube cube;
    if (argc == 7)
        cube = Cube(to_uint32(argv[1]), to_uint32(argv[2]), to_uint32(argv[3]),
                    to_uint32(argv[4]), to_uint32(argv[5]), to_uint32(argv[6]));

    cube.ShowCube();
    Patterns::Checkerboard(cube);
    cube.ShowCube();
}
