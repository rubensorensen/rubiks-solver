#ifndef CUBE_HANDLER_H
#define CUBE_HANDLER_H

#include "cube.h"

class CubeHandler
{
public:
    CubeHandler(std::shared_ptr<Cube> cube);
    ~CubeHandler() = default;

    void ShuffleCube(uint8_t n);
    void RotateByString(std::string str);
    void RotateFromFile(const char* filepath);
    void PrintEdges();
    bool EdgesOriented();

private:
    std::shared_ptr<Cube> m_Cube;
};

#endif
