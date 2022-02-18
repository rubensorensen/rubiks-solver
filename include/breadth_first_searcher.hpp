#ifndef BREADTH_FIRST_SEARCHER_HPP
#define BREADTH_FIRST_SEARCHER_HPP

#include "cube.hpp"
#include "timer.hpp"

#include <memory>
#include <vector>

class BreadthFirstSearcher
{
  public:

    class Vertex;

  public:

    BreadthFirstSearcher(const std::vector<Cube::MOVE>& moves,
                         bool (*goal)(std::shared_ptr<Vertex> vertex));
    ~BreadthFirstSearcher() = default;
    void SearchForGoal(std::shared_ptr<Vertex> vertex, std::vector<Cube::MOVE>& moves);

  private:

    void FindMoves(std::shared_ptr<Vertex> vertex, std::vector<Cube::MOVE>& moves);

    std::vector<Cube::MOVE> m_AllowedMoves;
    bool (*GoalIsSatisfied)(std::shared_ptr<Vertex> vertex);
    Timer m_Timer;
};

class BreadthFirstSearcher::Vertex : public std::enable_shared_from_this<Vertex>
{
  public:

    Vertex(std::shared_ptr<Cube> cube);
    ~Vertex() = default;

    inline const std::shared_ptr<Cube> GetCube() const { return m_Cube; }
    inline const std::pair<std::shared_ptr<Vertex>, Cube::MOVE>& GetParent() const
    {
        return m_Parent;
    }
    std::vector<std::shared_ptr<Vertex>> GetNeighbors(std::vector<Cube::MOVE> moves);
    uint32_t GetKey(uint32_t max);

  private:

    std::shared_ptr<Cube> m_Cube;
    std::pair<std::shared_ptr<BreadthFirstSearcher::Vertex>, Cube::MOVE> m_Parent;
};

#endif  // BREADTH_FIRST_SEARCHER_HPP