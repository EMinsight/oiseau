#include "oiseau/mesh/geometry.hpp"
#include <array>
#include <vector>

using namespace oiseau::mesh;

Geometry::Geometry(){};
Geometry::~Geometry(){};
std::span<double> Geometry::x() { return m_x; };
