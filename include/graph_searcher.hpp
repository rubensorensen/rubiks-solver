#ifndef GRAPH_SEARCHER_HPP
#define GRAPH_SEARCHER_HPP

#include "cube.hpp"
#include <unordered_map>

#include <memory>
#include <vector>

class GraphSearcher
{
  public:

    class Vertex;

  public:

    GraphSearcher()          = default;
    virtual ~GraphSearcher() = default;
    inline void SetAllowedMoves(const std::vector<Cube::MOVE>& moves) { m_AllowedMoves = moves; }
    inline void SetGoal(bool (*goal)(const Cube& cube)) { GoalIsSatisfied = goal; }
    inline const std::vector<Cube::MOVE>& GetSolution() const { return m_Solution; }
    inline const std::unordered_multimap<uint32_t, std::shared_ptr<Vertex>>& GetMap() const
    {
        return m_Map;
    }

    virtual void SearchForGoal(const Cube& cube) = 0;

  protected:

    void TraceMoves(std::shared_ptr<Vertex> vertex);
    bool (*GoalIsSatisfied)(const Cube& cube);

  protected:

    std::unordered_multimap<uint32_t, std::shared_ptr<Vertex>> m_Map;
    std::vector<Cube::MOVE> m_AllowedMoves;
    std::vector<Cube::MOVE> m_Solution;
};

class GraphSearcher::Vertex : virtual public std::enable_shared_from_this<Vertex>
{
  public:

    Vertex(const Cube& cube);
    virtual ~Vertex();

    inline const Cube& GetCube() const { return m_Cube; }
    inline const std::pair<std::shared_ptr<Vertex>, Cube::MOVE>& GetParent() const
    {
        return m_Parent;
    }
    inline void SetParent(std::shared_ptr<Vertex> parent, Cube::MOVE move)
    {
        m_Parent = { parent, move };
    }
    std::vector<std::shared_ptr<Vertex>> GetNeighbors(std::vector<Cube::MOVE> moves);
    uint32_t GetKey(uint32_t max);

  protected:

    Cube m_Cube;
    std::pair<std::shared_ptr<Vertex>, Cube::MOVE> m_Parent;
};

#endif  // GRAPH_SEARCHER_HPP