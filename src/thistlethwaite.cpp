#include "../include/thistlethwaite.hpp"

#include <iostream>

namespace tw
{
    void thistlethwaite(Cube& cube)
    {
        std::cout << "Initiating thistlethwaite solver" << std::endl;
        g02g1(cube);
    }

    void g02g1(Cube& cube) { std::cout << "G0 -> G1" << std::endl; }

}  // namespace tw
