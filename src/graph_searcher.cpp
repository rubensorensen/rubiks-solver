#include "../include/graph_searcher.hpp"

#include <stack>

void GraphSearcher::TraceMoves(std::shared_ptr<GraphSearcher::Vertex> vertex)
{
    std::stack<Cube::MOVE> stack;
    while (vertex->GetParent().first != nullptr)
    {
        stack.push(vertex->GetParent().second);
        vertex = vertex->GetParent().first;
    }

    while (!stack.empty())
    {
        m_Solution.push_back(stack.top());
        stack.pop();
    }
}

GraphSearcher::Vertex::Vertex(const Cube& cube)
    : m_Cube(cube), m_Parent({ nullptr, Cube::MOVE::UP })
{}

GraphSearcher::Vertex::~Vertex()
{
    m_Parent.first = nullptr;
}

std::vector<std::shared_ptr<GraphSearcher::Vertex>>
GraphSearcher::Vertex::GetNeighbors(std::vector<Cube::MOVE> moves)
{
    std::vector<std::shared_ptr<Vertex>> neighbors;
    for (auto move : moves)
    {
        std::shared_ptr<Vertex> vertex = std::make_shared<Vertex>(m_Cube);
        vertex->m_Cube.Twist(move);
        vertex->m_Parent = { shared_from_this(), move };
        neighbors.push_back(vertex);
    }
    return neighbors;
}

uint32_t GraphSearcher::Vertex::GetKey(uint32_t max)
{
    uint32_t faces[] = { m_Cube.m_Up,   m_Cube.m_Down,  m_Cube.m_Front,
                         m_Cube.m_Back, m_Cube.m_Right, m_Cube.m_Left };
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