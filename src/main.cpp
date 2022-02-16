#include "../include/cube_handler.hpp"
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
        cube = std::make_shared<Cube>(to_uint32(argv[1]), to_uint32(argv[2]), to_uint32(argv[3]), to_uint32(argv[4]), to_uint32(argv[5]), to_uint32(argv[6]));

    CubeHandler handler(cube);
    cube->Dump();
    cube->Display();
    std::cout << "\nAre all edges oriented correctly? " << handler.EdgesOriented() << std::endl;
    handler.RotateByString("8,11,12,10,6,17,8,16,10,8,9,13,12,6,13,6,14,8,14,16,10,13,9,6,11,17,14,9,16,"
                           "17,"
                           "12,6,17,11,16,7,9,7,13,12,10,9,13,8,14,11,6,9,10,15,11,7,14,6");
    cube->Dump();
    cube->Display();
    std::cout << "\nAre all edges oriented correctly? " << handler.EdgesOriented() << std::endl;

    return 0;
}
