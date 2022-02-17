#include "../include/breadth_first_searcher.hpp"
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
        *cube = Cube(to_uint32(argv[1]), to_uint32(argv[2]), to_uint32(argv[3]), to_uint32(argv[4]),
                     to_uint32(argv[5]), to_uint32(argv[6]));

    std::shared_ptr<CubeHandler> handler = std::make_shared<CubeHandler>(cube);
    handler->ShuffleCube(10);

    std::vector<Cube::MOVE> moves = { Cube::MOVE::UP,    Cube::MOVE::UPRIME, Cube::MOVE::UP2,
                                      Cube::MOVE::DOWN,  Cube::MOVE::DPRIME, Cube::MOVE::DOWN2,
                                      Cube::MOVE::FRONT, Cube::MOVE::FPRIME, Cube::MOVE::FRONT2,
                                      Cube::MOVE::BACK,  Cube::MOVE::BPRIME, Cube::MOVE::BACK2,
                                      Cube::MOVE::RIGHT, Cube::MOVE::RPRIME, Cube::MOVE::RIGHT2,
                                      Cube::MOVE::LEFT,  Cube::MOVE::LPRIME, Cube::MOVE::LEFT2 };

    BreadthFirstSearcher bfs(
        moves, [](std::shared_ptr<CubeHandler> handler) { return handler->EdgesOriented(); });
    bfs.SearchForGoal(handler);

    return 0;
}
