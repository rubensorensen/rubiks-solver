#include "../include/thistlethwaite_solver.hpp"

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

std::unordered_multimap<uint32_t, std::shared_ptr<GraphSearcher::Vertex>>
    ThistlethwaiteSolver::G3Permutations::s_Permutations;

ThistlethwaiteSolver::ThistlethwaiteSolver(std::shared_ptr<Cube> cube, GraphSearcher* searcher)
    : p_Cube(cube), p_Searcher(searcher)
{}

ThistlethwaiteSolver::~ThistlethwaiteSolver()
{
    p_Cube     = nullptr;
    p_Searcher = nullptr;
}

void ThistlethwaiteSolver::SolveCube()
{
    std::cout << "Initializing Thistlethwaite solver" << std::endl;
    G3Permutations::GenerateG3Permutations();
    std::cout << "Thistlethwaite solver initialized\n" << std::endl;

    std::cout << "THISTLETHWAITE'S ALGORITHM" << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "Initial cube state" << std::endl;
    p_Cube->Dump();
    p_Cube->Display();

    // G0 -> G1
    std::cout << "G0 -> G1" << std::endl;
    std::cout
        << "Move space: { U, U', U2, D, D', D2, F, F', F2, B, B', B2, R, R', R2, L, L', L2 }\n"
        << std::endl;
    p_Searcher->SetAllowedMoves(s_G0);
    p_Searcher->SetGoal([](const Cube& cube) { return cube.EdgesOriented(); });
    p_Searcher->SearchForGoal(*p_Cube);

    size_t solutionSize = p_Searcher->GetSolution().size();
    for (size_t i = 0; i < solutionSize; ++i)
        p_Cube->Twist(p_Searcher->GetSolution()[i]);
    std::cout << "Current cube state" << std::endl;
    p_Cube->Dump();
    p_Cube->Display();

    // G1 -> G2
    std::cout << "G1 -> G2" << std::endl;
    std::cout << "Move space: { U2, D2, F, F', F2, B, B', B2, R, R', R2, L, L', L2 }\n"
              << std::endl;

    p_Searcher->SetAllowedMoves(s_G1);
    p_Searcher->SetGoal([](const Cube& cube) {
        return cube.CornersOriented() && cube.CorrectEdgesInMiddleSlice();
    });
    p_Searcher->SearchForGoal(*p_Cube);

    for (size_t i = solutionSize; i < p_Searcher->GetSolution().size(); ++i)
        p_Cube->Twist(p_Searcher->GetSolution()[i]);
    std::cout << "Current cube state" << std::endl;
    p_Cube->Dump();
    p_Cube->Display();
    solutionSize = p_Searcher->GetSolution().size();

    // G2 -> G3
    std::cout << "G2 -> G3" << std::endl;
    std::cout << "Move space: { U2, D2, F2, B2, R, R', R2, L, L', L2 }\n" << std::endl;

    p_Searcher->SetAllowedMoves(s_G2);
    p_Searcher->SetGoal([](const Cube& cube) { return G3Permutations::ContainsPermutation(cube); });
    p_Searcher->SearchForGoal(*p_Cube);

    for (size_t i = solutionSize; i < p_Searcher->GetSolution().size(); ++i)
        p_Cube->Twist(p_Searcher->GetSolution()[i]);
    std::cout << "Current cube state" << std::endl;
    p_Cube->Dump();
    p_Cube->Display();
    solutionSize = p_Searcher->GetSolution().size();

    // G3 -> G4
    std::cout << "G3 -> G4" << std::endl;
    std::cout << "Move space: { U2, D2, F2, B2, R2, L2 }\n" << std::endl;

    p_Searcher->SetAllowedMoves(s_G3);
    p_Searcher->SetGoal([](const Cube& cube) { return cube.IsSolved(); });
    p_Searcher->SearchForGoal(*p_Cube);

    for (size_t i = solutionSize; i < p_Searcher->GetSolution().size(); ++i)
        p_Cube->Twist(p_Searcher->GetSolution()[i]);
    std::cout << "Current cube state" << std::endl;
    p_Cube->Dump();
    solutionSize = p_Searcher->GetSolution().size();

    // Thistlethwaite done - Show solution
    p_Cube->Display();
    std::cout << "Solution: ";
    const char* mv[] = { "U", "U'", "U2", "D", "D'", "D2", "F", "F'", "F2",
                         "B", "B'", "B2", "R", "R'", "R2", "L", "L'", "L2" };
    std::cout << "Solution size: " << p_Searcher->GetSolution().size() << std::endl;
    for (auto& m : p_Searcher->GetSolution())
        std::cout << mv[static_cast<uint32_t>(m)] << ' ';
    std::cout << std::endl;
}

#include "../include/breadth_first_searcher.hpp"
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