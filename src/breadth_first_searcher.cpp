#include "../include/breadth_first_searcher.hpp"

#include <iostream>
#include <queue>

void BreadthFirstSearcher::SearchForGoal(const Cube& cube)
{
    m_Map.clear();
    std::shared_ptr<Vertex> vertex = std::make_shared<Vertex>(cube);
    uint64_t hashSz{ 12582917 };

    std::cout << "BFS Started" << std::endl;
    uint64_t numVisited = 0;
    uint64_t level      = 0;
    std::queue<std::shared_ptr<Vertex>> queue;
    queue.push(vertex);
    while (!queue.empty())
    {
        std::shared_ptr<Vertex> front = queue.front();
        queue.pop();
        ++numVisited;
        if (GoalIsSatisfied(front->GetCube()))
        {
            std::cout << "BFS: Found Goal!" << std::endl;
            std::cout << "Unique Vertices Visited: " << numVisited << std::endl;

            TraceMoves(front);
            return;
        }
        std::vector<std::shared_ptr<Vertex>> neighbors{ front->GetNeighbors(m_AllowedMoves) };
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
                queue.push(neighbor);
            }
        }
        ++level;
    }
    std::cerr << "BFS reached end of queue" << std::endl;
}