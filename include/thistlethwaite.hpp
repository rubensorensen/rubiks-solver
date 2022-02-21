#ifndef THISTLETHWAITE_HPP
#define THISTLETHWAITE_HPP

#include "cube.hpp"
#include "unordered_map"

#include <memory>

class ThistlethwaiteSolver
{
  public:

    ThistlethwaiteSolver(std::shared_ptr<Cube> cube);
    ~ThistlethwaiteSolver();

    void SolveCube();

  private:

    std::shared_ptr<Cube> m_Cube;
    std::unordered_multimap<uint32_t, Cube> m_G3Permutations;
};

#endif
