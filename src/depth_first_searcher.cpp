#include "../include/depth_first_searcher.hpp"

#include <iostream>
#include <stack>

void DepthFirstSearcher::SearchForGoal(const Cube& cube)
{
    m_Map.clear();
    std::shared_ptr<Vertex> vertex = std::make_shared<Vertex>(cube);
    uint64_t hashSz{ 12582917 };

    std::cout << "DFS Started" << std::endl;
    uint64_t numVisited = 0;
    uint64_t level      = 0;
    std::stack<std::shared_ptr<Vertex>> stack;
    stack.push(vertex);
    while (!stack.empty())
    {
        std::shared_ptr<Vertex> top = stack.top();
        stack.pop();
        ++numVisited;
        if (GoalIsSatisfied(top->GetCube()))
        {
            std::cout << "DFS: Found Goal!" << std::endl;
            std::cout << "Unique Vertices Visited: " << numVisited << std::endl;

            TraceMoves(top);
            return;
        }
        std::vector<std::shared_ptr<Vertex>> neighbors{ top->GetNeighbors(m_AllowedMoves) };
        for (auto& neighbor : neighbors)
        {
            uint32_t hash = neighbor->GetKey(hashSz);
            bool visited{ false };
            auto iters{ m_Map.equal_range(hash) };
            for (auto it{ iters.first }; it != iters.second; ++it)
                if (neighbor->GetCube() == it->second->GetCube())
                {
                    visited = true;
                    break;
                }
            if (!visited)
            {
                m_Map.insert({ hash, neighbor });
                stack.push(neighbor);
            }
        }
        ++level;
    }
    std::cerr << "DFS reached end of stack" << std::endl;
}