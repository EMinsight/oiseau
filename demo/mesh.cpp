#include "oiseau/mesh/cell.hpp"
#include <iostream>

using namespace oiseau::mesh;

int main() {
    auto tri = get_cell_type("triangle");
    std::cout << tri->name() << std::endl;
    std::cout << tri->dimension() << std::endl;
}
