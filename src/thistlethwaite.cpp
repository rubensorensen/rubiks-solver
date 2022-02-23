#include "../include/thistlethwaite.hpp"

#include "../include/breadth_first_searcher.hpp"

#include <iostream>

std::vector<Cube::MOVE> ThistlethwaiteSolver::s_G0 = {
    Cube::MOVE::UP,     Cube::MOVE::UPRIME, Cube::MOVE::UP2,    Cube::MOVE::DOWN,
    Cube::MOVE::DPRIME, Cube::MOVE::DOWN2,  Cube::MOVE::FRONT,  Cube::MOVE::FPRIME,
    Cube::MOVE::FRONT2, Cube::MOVE::BACK,   Cube::MOVE::BPRIME, Cube::MOVE::BACK2,
    Cube::MOVE::RIGHT,  Cube::MOVE::RPRIME, Cube::MOVE::RIGHT2, Cube::MOVE::LEFT,
    Cube::MOVE::LPRIME, Cube::MOVE::LEFT2
};

std::vector<Cube::MOVE> ThistlethwaiteSolver::s_G1 = {
    Cube::MOVE::UP2,    Cube::MOVE::DOWN2,  Cube::MOVE::FRONT,  Cube::MOVE::FPRIME,
    Cube::MOVE::FRONT2, Cube::MOVE::BACK,   Cube::MOVE::BPRIME, Cube::MOVE::BACK2,
    Cube::MOVE::RIGHT,  Cube::MOVE::RPRIME, Cube::MOVE::RIGHT2, Cube::MOVE::LEFT,
    Cube::MOVE::LPRIME, Cube::MOVE::LEFT2
};

std::vector<Cube::MOVE> ThistlethwaiteSolver::s_G2 = { Cube::MOVE::UP2,    Cube::MOVE::DOWN2,
                                                       Cube::MOVE::FRONT2, Cube::MOVE::BACK2,
                                                       Cube::MOVE::RIGHT,  Cube::MOVE::RPRIME,
                                                       Cube::MOVE::RIGHT2, Cube::MOVE::LEFT,
                                                       Cube::MOVE::LPRIME, Cube::MOVE::LEFT2 };

std::vector<Cube::MOVE> ThistlethwaiteSolver::s_G3 = { Cube::MOVE::UP2,    Cube::MOVE::DOWN2,
                                                       Cube::MOVE::FRONT2, Cube::MOVE::BACK2,
                                                       Cube::MOVE::RIGHT2, Cube::MOVE::LEFT2 };

std::unordered_multimap<uint32_t, std::shared_ptr<BreadthFirstSearcher::Vertex>>
    ThistlethwaiteSolver::G3Permutations::s_Permutations;

ThistlethwaiteSolver::ThistlethwaiteSolver(std::shared_ptr<Cube> cube) : m_Cube(cube) {}

ThistlethwaiteSolver::~ThistlethwaiteSolver()
{
    m_Cube = nullptr;
}

void ThistlethwaiteSolver::SolveCube()
{
    std::cout << "THISTLETHWAITE'S ALGORITHM" << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "Initial cube state" << std::endl;
    m_Cube->Dump();
    m_Cube->Display();

    BreadthFirstSearcher bfs;

    // G0 -> G1
    std::cout << "G0 -> G1" << std::endl;
    std::cout
        << "Move space: { U, U', U2, D, D', D2, F, F', F2, B, B', B2, R, R', R2, L, L', L2 }\n"
        << std::endl;
    bfs.SetAllowedMoves(s_G0);
    bfs.SetGoal([](const Cube& cube) { return cube.EdgesOriented(); });
    bfs.SearchForGoal(*m_Cube);

    size_t solutionSize = bfs.GetSolution().size();
    for (size_t i = 0; i < solutionSize; ++i)
        m_Cube->Twist(bfs.GetSolution()[i]);
    std::cout << "Current cube state" << std::endl;
    m_Cube->Dump();
    m_Cube->Display();

    // G1 -> G2
    std::cout << "G1 -> G2" << std::endl;
    std::cout << "Move space: { U2, D2, F, F', F2, B, B', B2, R, R', R2, L, L', L2 }\n"
              << std::endl;

    bfs.SetAllowedMoves(s_G1);
    bfs.SetGoal([](const Cube& cube) {
        return cube.CornersOriented() && cube.CorrectEdgesInMiddleSlice();
    });
    bfs.SearchForGoal(*m_Cube);

    for (size_t i = solutionSize; i < bfs.GetSolution().size(); ++i)
        m_Cube->Twist(bfs.GetSolution()[i]);
    std::cout << "Current cube state" << std::endl;
    m_Cube->Dump();
    m_Cube->Display();
    solutionSize = bfs.GetSolution().size();

    // G2 -> G3
    std::cout << "G2 -> G3" << std::endl;
    std::cout << "Move space: { U2, D2, F2, B2, R, R', R2, L, L', L2 }\n" << std::endl;

    G3Permutations::GenerateG3Permutations();

    bfs.SetAllowedMoves(s_G2);
    bfs.SetGoal([](const Cube& cube) { return G3Permutations::ContainsPermutation(cube); });
    bfs.SearchForGoal(*m_Cube);

    for (size_t i = solutionSize; i < bfs.GetSolution().size(); ++i)
        m_Cube->Twist(bfs.GetSolution()[i]);
    std::cout << "Current cube state" << std::endl;
    m_Cube->Dump();
    m_Cube->Display();
    solutionSize = bfs.GetSolution().size();

    // G3 -> G4
    std::cout << "G3 -> G4" << std::endl;
    std::cout << "Move space: { U2, D2, F2, B2, R2, L2 }\n" << std::endl;

    bfs.SetAllowedMoves(s_G3);
    bfs.SetGoal([](const Cube& cube) { return cube.IsSolved(); });
    bfs.SearchForGoal(*m_Cube);

    for (size_t i = solutionSize; i < bfs.GetSolution().size(); ++i)
        m_Cube->Twist(bfs.GetSolution()[i]);
    std::cout << "Current cube state" << std::endl;
    m_Cube->Dump();
    solutionSize = bfs.GetSolution().size();

    // Thistlethwaite done - Show solution
    m_Cube->Display();
    const char* mv[] = { "U", "U'", "U2", "D", "D'", "D2", "F", "F'", "F2",
                         "B", "B'", "B2", "R", "R'", "R2", "L", "L'", "L2" };
    for (auto& m : bfs.GetSolution())
        std::cout << mv[(uint32_t)m] << ' ';
    std::cout << std::endl;
}

void ThistlethwaiteSolver::G3Permutations::GenerateG3Permutations()
{
    Cube cube;
    BreadthFirstSearcher bfs;
    bfs.SetAllowedMoves(s_G3);
    bfs.SetGoal([](const Cube&) { return false; });
    bfs.SearchForGoal(cube);
    s_Permutations = bfs.GetMap();
}

bool ThistlethwaiteSolver::G3Permutations::ContainsPermutation(const Cube& cube)
{
    BreadthFirstSearcher::Vertex vertex(cube);
    uint32_t key = vertex.GetKey(12582917);
    auto iters{ s_Permutations.equal_range(key) };
    for (auto it = iters.first; it != iters.second; ++it)
        if (it->second->GetCube() == cube)
            return true;

    return false;
}