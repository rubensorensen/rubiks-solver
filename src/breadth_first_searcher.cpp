#include "../include/breadth_first_searcher.hpp"

#include <unordered_map>

#include <iostream>
#include <queue>
#include <stack>

BreadthFirstSearcher::BreadthFirstSearcher(const std::vector<Cube::MOVE>& moves,
                                           bool (*goal)(std::shared_ptr<Vertex> vertex))
    : m_AllowedMoves(moves), GoalIsSatisfied(goal), m_Timer(Timer())
{}

void BreadthFirstSearcher::FindMoves(std::shared_ptr<Vertex> vertex, std::vector<Cube::MOVE>& moves)
{
    std::stack<Cube::MOVE> stack;
    while (vertex->GetParent().first != nullptr)
    {
        stack.push(vertex->GetParent().second);
        vertex = vertex->GetParent().first;
    }

    while (!stack.empty())
    {
        moves.push_back(stack.top());
        stack.pop();
    }
}

void BreadthFirstSearcher::SearchForGoal(std::shared_ptr<Cube> cube, std::vector<Cube::MOVE>& moves)
{
    std::shared_ptr<Vertex> vertex = std::make_shared<Vertex>(cube);
    uint64_t hashSz{ 12582917 };

    std::cout << "BFS Started" << std::endl;
    uint64_t numVisited = 0;
    uint64_t level      = 0;
    m_Timer.Start();
    std::queue<std::shared_ptr<Vertex>> queue;
    std::unordered_multimap<uint32_t, std::shared_ptr<Vertex>> map;
    queue.push(vertex);
    while (!queue.empty())
    {
        std::shared_ptr<Vertex> front = queue.front();
        queue.pop();
        ++numVisited;
        if (GoalIsSatisfied(front))
        {
            m_Timer.Stop();
            std::cout << "BFS: Found Goal!" << std::endl;
            std::cout << "Unique Vertices Visited: " << numVisited << std::endl;
            std::cout << "Elapsed time: " << m_Timer.Seconds() << 's' << std::endl;

            FindMoves(front, moves);

            return;
        }
        std::vector<std::shared_ptr<Vertex>> neighbors{ front->GetNeighbors(m_AllowedMoves) };
        for (auto& neighbor : neighbors)
        {
            uint32_t hash = neighbor->GetKey(hashSz);
            bool visited{ false };
            auto iters{ map.equal_range(hash) };
            for (auto it{ iters.first }; it != iters.second; ++it)
                if (*(neighbor->GetCube()) == *(it->second->GetCube()))
                {
                    visited = true;
                    break;
                }
            if (!visited)
            {
                map.insert({ hash, neighbor });
                queue.push(neighbor);
            }
        }
        ++level;
    }
    std::cerr << "[ERROR] BFS failed, queue empty" << std::endl;
}

BreadthFirstSearcher::Vertex::Vertex(std::shared_ptr<Cube> cube)
    : m_Cube(cube), m_Parent({ nullptr, Cube::MOVE::UP })
{}

BreadthFirstSearcher::Vertex::~Vertex()
{
    m_Cube         = nullptr;
    m_Parent.first = nullptr;
}

std::vector<std::shared_ptr<BreadthFirstSearcher::Vertex>>
BreadthFirstSearcher::Vertex::GetNeighbors(std::vector<Cube::MOVE> moves)
{
    std::vector<std::shared_ptr<Vertex>> neighbors;
    for (auto move : moves)
    {
        std::shared_ptr<Vertex> vertex = std::make_shared<Vertex>(
            std::make_shared<Cube>(m_Cube->m_Up, m_Cube->m_Down, m_Cube->m_Front, m_Cube->m_Back,
                                   m_Cube->m_Right, m_Cube->m_Left));
        vertex->m_Cube->Twist(move);
        vertex->m_Parent = { shared_from_this(), move };
        neighbors.push_back(vertex);
    }
    return neighbors;
}

uint32_t BreadthFirstSearcher::Vertex::GetKey(uint32_t max)
{
    uint32_t faces[] = { m_Cube->m_Up,   m_Cube->m_Down,  m_Cube->m_Front,
                         m_Cube->m_Back, m_Cube->m_Right, m_Cube->m_Left };
    uint32_t x       = 1;

    for (int8_t i = 0; i < 6; ++i)
    {
        x = (x * faces[i]) % max;
        for (int8_t j = 28; j >= 0; --j)
        {
            x = (x * ((((faces[i]) >> j) & 0xf) + 1)) % max;
            // x ^= x << 13;
            // x ^= x >> 17;
            // x ^= x << 5;
        }
    }

    return x % max;

    // return (m_Cube->m_Up * m_Cube->m_Down * m_Cube->m_Front * m_Cube->m_Back * m_Cube->m_Right *
    //         m_Cube->m_Left) %
    //        max;
}