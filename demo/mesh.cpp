#include "oiseau/mesh/cell.h"
#include <iostream>

using namespace oiseau::mesh;

int main() {
    TriangleCell tricell;
    std::cout << tricell.name() << std::endl;
    std::cout << tricell.dimension() << std::endl;
    std::cout << celltype_to_string(tricell.type()) << std::endl;
}
