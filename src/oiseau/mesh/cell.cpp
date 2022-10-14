#include "oiseau/mesh/cell.hpp"
#include <string>

namespace oiseau::mesh {

CellType get_cell_type(const std::string &cell) {
  static PointCell point;
  static IntervalCell interval;
  static TriangleCell triangle;
  static TetrahedronCell tetrahedron;
  if (cell == "point")
    return &point;
  else if (cell == "interval") {
    return &interval;
  } else if (cell == "triangle") {
    return &triangle;
  } else if (cell == "tetrahedron") {
    return &tetrahedron;
  } else
    throw std::runtime_error("Unknown cell type (" + cell + ")");
}

std::string &Cell::name() { return m_name; }
int Cell::dimension() { return m_dim; }
int Cell::num_entities(int dim) const { return m_entities_number[dim]; }

PointCell::PointCell() {
  m_name = "point";
  m_dim = 0;
  m_entities_number = {1, 0, 0, 0};
};

IntervalCell::IntervalCell() {
  m_name = "interval";
  m_dim = 1;
  m_entities_number = {2, 1, 0, 0};
};

TriangleCell::TriangleCell() {
  m_name = "triangle";
  m_dim = 2;
  m_entities_number = {2, 1, 0, 0};
}

TetrahedronCell::TetrahedronCell() {
  m_name = "tetrahedron";
  m_dim = 3;
  m_entities_number = {4, 6, 4, 1};
}

}  // namespace oiseau::mesh
