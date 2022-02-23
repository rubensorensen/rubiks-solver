#ifndef THISTLETHWAITE_HPP
#define THISTLETHWAITE_HPP

#include "breadth_first_searcher.hpp"
#include "cube.hpp"
#include "unordered_map"

#include <memory>
#include <vector>

class ThistlethwaiteSolver
{
    class G3Permutations;

  public:

    ThistlethwaiteSolver(std::shared_ptr<Cube> cube);
    ~ThistlethwaiteSolver();

    void SolveCube();

  private:

    std::shared_ptr<Cube> m_Cube;

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

    static std::unordered_multimap<uint32_t, std::shared_ptr<BreadthFirstSearcher::Vertex>>
        s_Permutations;
};

#endif
