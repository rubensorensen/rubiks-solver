#ifndef THISTLETHWAITE_SOLVER_HPP
#define THISTLETHWAITE_SOLVER_HPP

#include "graph_searcher.hpp"

class ThistlethwaiteSolver
{
    class G3Permutations;

  public:

    ThistlethwaiteSolver(std::shared_ptr<Cube> cube, GraphSearcher* searcher);
    ~ThistlethwaiteSolver();

    void SolveCube();

  private:

    std::shared_ptr<Cube> p_Cube;
    GraphSearcher* p_Searcher;

    static std::vector<Cube::MOVE> s_G0;
    static std::vector<Cube::MOVE> s_G1;
    static std::vector<Cube::MOVE> s_G2;
    static std::vector<Cube::MOVE> s_G3;
};

class ThistlethwaiteSolver::G3Permutations
{
  public:

    static void GenerateG3Permutations();
    static bool ContainsPermutation(const Cube& cube);

  private:

    G3Permutations() = default;

    static std::unordered_multimap<uint32_t, std::shared_ptr<GraphSearcher::Vertex>> s_Permutations;
};

#endif
