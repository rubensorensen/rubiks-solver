#ifndef CUBE_HANDLER_H
#define CUBE_HANDLER_H

#include "cube.hpp"

#include <memory>
#include <vector>

class CubeHandler : public std::enable_shared_from_this<CubeHandler>
{
  public:

    CubeHandler(std::shared_ptr<Cube> cube);
    ~CubeHandler() = default;

    inline const std::shared_ptr<Cube> GetCube() const { return m_Cube; }
    void ShuffleCube(uint8_t n);
    void RotateByString(std::string str);
    void RotateFromFile(const char* filepath);
    bool EdgesOriented() const;
    std::vector<std::shared_ptr<CubeHandler>> GetNeighbors(std::vector<Cube::MOVE> moves);
    uint32_t HashCube(uint32_t maxVal) const;

  private:

    std::shared_ptr<Cube> m_Cube;
    std::pair<std::shared_ptr<CubeHandler>, Cube::MOVE> m_Parent;

    friend class BreadthFirstSearcher;
};

#endif  // CUBE_HANDLER_HPP
