#ifndef DEPTH_FIRST_SEARCHER_HPP
#define DEPTH_FIRST_SEARCHER_HPP

#include "graph_searcher.hpp"

class DepthFirstSearcher : public GraphSearcher
{
  public:

    void SearchForGoal(const Cube& cube);
};

#endif  // DEPTH_FIRST_SEARCHER_HPP