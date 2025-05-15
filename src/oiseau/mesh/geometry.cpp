#include "oiseau/mesh/geometry.hpp"

#include <cstddef>
#include <span>
#include <utility>
#include <vector>

using namespace oiseau::mesh;

Geometry::Geometry() = default;
Geometry::~Geometry() = default;
std::span<double> Geometry::x() { return m_x; };
std::span<double> Geometry::x_at(std::size_t pos) { return {&m_x[pos * m_dim], 3}; };
Geometry::Geometry(std::vector<double> &&x, int dim) : m_x(std::move(x)), m_dim(dim) {};
