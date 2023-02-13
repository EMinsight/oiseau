#include "oiseau/mesh/geometry.hpp"
#include <array>
#include <vector>

using namespace oiseau::mesh;

Geometry::Geometry(){};
Geometry::~Geometry(){};
std::span<double> Geometry::x() { return m_x; };
Geometry::Geometry(std::vector<double> &&x, int dim) : m_x(std::move(x)), m_dim(dim){};
