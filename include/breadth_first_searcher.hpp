#ifndef BREADTH_FIRST_SEARCHER_HPP
#define BREADTH_FIRST_SEARCHER_HPP

#include "graph_searcher.hpp"

class BreadthFirstSearcher : public GraphSearcher
{
  public:

    void SearchForGoal(const Cube& cube);
};
#endif  // BREADTH_FIRST_SEARCHER_HPP