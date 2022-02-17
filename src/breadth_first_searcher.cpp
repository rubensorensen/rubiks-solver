#include "../include/breadth_first_searcher.hpp"

#include <unordered_map>

#include <iostream>
#include <queue>
#include <stack>

BreadthFirstSearcher::BreadthFirstSearcher(const std::vector<Cube::MOVE>& moves,
                                           bool (*goal)(std::shared_ptr<CubeHandler> handler))
    : m_AllowedMoves(moves), GoalIsSatisfied(goal), m_Timer(Timer())
{}

void BreadthFirstSearcher::SearchForGoal(std::shared_ptr<CubeHandler> handler)
{
    uint64_t hashSz{ 1610612741 };

    std::cout << "BFS Started" << std::endl;
    uint64_t numVisited = 0;
    uint64_t level      = 0;
    m_Timer.Start();
    std::queue<std::shared_ptr<CubeHandler>> q;
    std::unordered_multimap<uint32_t, std::shared_ptr<CubeHandler>> umm;
    umm.insert({ handler->HashCube(hashSz), handler });
    q.push(handler);
    while (!q.empty())
    {
        std::shared_ptr<CubeHandler> h{ q.front() };
        q.pop();
        if (GoalIsSatisfied(h))
        {
            m_Timer.Stop();
            std::cout << "BFS: Found Goal!" << std::endl;
            std::cout << "Vertices Visited: " << numVisited << std::endl;
            std::cout << "Levels searched: " << level << std::endl;
            std::cout << "Multimap size: " << umm.size() << std::endl;
            std::cout << "Elapsed time: " << m_Timer.Seconds() << 's' << std::endl;

            std::stack<Cube::MOVE> s;
            while (h->m_Parent.first != nullptr)
            {
                s.push(h->m_Parent.second);
                h = h->m_Parent.first;
            }

            std::vector<Cube::MOVE> v;
            while (!s.empty())
            {
                v.push_back(s.top());
                s.pop();
            }

            const char* mv[] = { "U", "U'", "U2", "D", "D'", "D2", "F", "F'", "F2",
                                 "B", "B'", "B2", "R", "R'", "R2", "L", "L'", "L2" };

            for (auto& m : v)
                std::cout << mv[(uint32_t)m] << ' ';
            std::cout << std::endl;

            return;
        }
        std::vector<std::shared_ptr<CubeHandler>> neighbors{ h->GetNeighbors(m_AllowedMoves) };
        for (auto& n : neighbors)
        {
            bool visited{ false };
            auto iters{ umm.equal_range(n->HashCube(hashSz)) };
            for (auto it{ iters.first }; it != iters.second; ++it)
                if (n->GetCube() == it->second->GetCube())
                    visited = true;
            if (!visited)
            {
                ++numVisited;
                umm.insert({ n->HashCube(hashSz), n });
                q.push(n);
            }
        }
        ++level;
    }
    std::cerr << "[ERROR] BFS failed, queue empty" << std::endl;
}