#ifndef BREADTH_FIRST_SEARCHER_HPP
#define BREADTH_FIRST_SEARCHER_HPP

#include "cube.hpp"
#include "timer.hpp"
#include <unordered_map>

#include <memory>
#include <vector>

class BreadthFirstSearcher
{
  public:

    class Vertex;

  public:

    BreadthFirstSearcher()  = default;
    ~BreadthFirstSearcher() = default;
    inline void SetAllowedMoves(const std::vector<Cube::MOVE>& moves) { m_AllowedMoves = moves; }
    inline void SetGoal(bool (*goal)(const Cube& cube)) { GoalIsSatisfied = goal; }
    inline const std::vector<Cube::MOVE>& GetSolution() const { return m_Solution; }
    void SearchForGoal(const Cube& cube);
    inline const std::unordered_multimap<uint32_t, std::shared_ptr<Vertex>>& GetMap() const
    {
        return m_Map;
    }

  private:

    void TraceMoves(std::shared_ptr<Vertex> vertex);
    bool (*GoalIsSatisfied)(const Cube& cube);

  private:

    std::unordered_multimap<uint32_t, std::shared_ptr<Vertex>> m_Map;
    std::vector<Cube::MOVE> m_AllowedMoves;
    std::vector<Cube::MOVE> m_Solution;
};

class BreadthFirstSearcher::Vertex : public std::enable_shared_from_this<Vertex>
{
  public:

    Vertex(const Cube& cube);
    ~Vertex();

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

  private:

    Cube m_Cube;
    std::pair<std::shared_ptr<BreadthFirstSearcher::Vertex>, Cube::MOVE> m_Parent;
};

#endif  // BREADTH_FIRST_SEARCHER_HPP