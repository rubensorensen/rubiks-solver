#include "../include/cube_handler.h"
#include "../include/thistlethwaite.h"

uint32_t to_uint32(const char* str)
{
    return static_cast<uint32_t>(std::strtol(str, nullptr, 16));
}

int main(int argc, char* argv[])
{
    std::shared_ptr<Cube> cube = std::make_shared<Cube>();
    if (argc == 7)
        cube = std::make_shared<Cube>(to_uint32(argv[1]), to_uint32(argv[2]),
                                      to_uint32(argv[3]), to_uint32(argv[4]),
                                      to_uint32(argv[5]), to_uint32(argv[6]));

    CubeHandler handler(cube);
    cube->ShowCube();
    handler.RotateFromFile("res/patterns/python");
    cube->ShowCube();
}
