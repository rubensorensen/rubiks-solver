#ifndef BREADTH_FIRST_SEARCHER_HPP
#define BREADTH_FIRST_SEARCHER_HPP

#include "cube.hpp"
#include "cube_handler.hpp"
#include "timer.hpp"

#include <memory>
#include <vector>

class BreadthFirstSearcher
{
  public:

    BreadthFirstSearcher(const std::vector<Cube::MOVE>& moves,
                         bool (*goal)(std::shared_ptr<CubeHandler> handler));
    ~BreadthFirstSearcher() = default;
    void SearchForGoal(std::shared_ptr<CubeHandler> handler);

  private:

    std::vector<Cube::MOVE> m_AllowedMoves;
    bool (*GoalIsSatisfied)(std::shared_ptr<CubeHandler> Handler);
    Timer m_Timer;
};

#endif  // BREADTH_FIRST_SEARCHER_HPP