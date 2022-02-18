#include "../include/thistlethwaite.hpp"

#include "../include/breadth_first_searcher.hpp"

#include <iostream>

ThistlethwaiteSolver::ThistlethwaiteSolver(std::shared_ptr<Cube> cube) : m_Cube(cube) {}

void ThistlethwaiteSolver::SolveCube()
{

    std::vector<Cube::MOVE> solution;

    std::vector<Cube::MOVE> g0 = { Cube::MOVE::UP,    Cube::MOVE::UPRIME, Cube::MOVE::UP2,
                                   Cube::MOVE::DOWN,  Cube::MOVE::DPRIME, Cube::MOVE::DOWN2,
                                   Cube::MOVE::FRONT, Cube::MOVE::FPRIME, Cube::MOVE::FRONT2,
                                   Cube::MOVE::BACK,  Cube::MOVE::BPRIME, Cube::MOVE::BACK2,
                                   Cube::MOVE::RIGHT, Cube::MOVE::RPRIME, Cube::MOVE::RIGHT2,
                                   Cube::MOVE::LEFT,  Cube::MOVE::LPRIME, Cube::MOVE::LEFT2 };

    std::vector<Cube::MOVE> g1 = { Cube::MOVE::UP2,    Cube::MOVE::DOWN2,  Cube::MOVE::FRONT,
                                   Cube::MOVE::FPRIME, Cube::MOVE::FRONT2, Cube::MOVE::BACK,
                                   Cube::MOVE::BPRIME, Cube::MOVE::BACK2,  Cube::MOVE::RIGHT,
                                   Cube::MOVE::RPRIME, Cube::MOVE::RIGHT2, Cube::MOVE::LEFT,
                                   Cube::MOVE::LPRIME, Cube::MOVE::LEFT2 };

    std::vector<Cube::MOVE> g2 = { Cube::MOVE::UP2,    Cube::MOVE::DOWN2, Cube::MOVE::FRONT2,
                                   Cube::MOVE::BACK2,  Cube::MOVE::RIGHT, Cube::MOVE::RPRIME,
                                   Cube::MOVE::RIGHT2, Cube::MOVE::LEFT,  Cube::MOVE::LPRIME,
                                   Cube::MOVE::LEFT2 };

    std::vector<Cube::MOVE> g3 = { Cube::MOVE::UP2,   Cube::MOVE::DOWN2,  Cube::MOVE::FRONT2,
                                   Cube::MOVE::BACK2, Cube::MOVE::RIGHT2, Cube::MOVE::LEFT2 };

    std::cout << "THISTLETHWAITE'S ALGORITHM" << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "Initial cube state" << std::endl;
    m_Cube->Dump();

    // G0 -> G1
    std::cout << "G0 -> G1" << std::endl;
    std::cout
        << "Move space: { U, U', U2, D, D', D2, F, F', F2, B, B', B2, R, R', R2, L, L', L2 }\n"
        << std::endl;

    BreadthFirstSearcher bfs(g0, [](std::shared_ptr<BreadthFirstSearcher::Vertex> vertex) {
        return vertex->GetCube()->EdgesOriented();
    });
    bfs.SearchForGoal(std::make_shared<BreadthFirstSearcher::Vertex>(m_Cube), solution);

    for (auto& m : solution)
        m_Cube->Twist(m);
    std::cout << "Current cube state" << std::endl;
    m_Cube->Dump();

    // G1 -> G2
    // G2 -> G3
    // G3 -> G4

    const char* mv[] = { "U", "U'", "U2", "D", "D'", "D2", "F", "F'", "F2",
                         "B", "B'", "B2", "R", "R'", "R2", "L", "L'", "L2" };
    for (auto& m : solution)
        std::cout << mv[(uint32_t)m] << ' ';
    std::cout << std::endl;
}