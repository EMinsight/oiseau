#pragma once

#include <array>
#include <stdexcept>
#include <string>

namespace oiseau {
namespace mesh {

#define CellType Cell const *

class Cell {
 protected:
  std::string m_name;
  int m_dim;
  std::array<int, 4> m_entities_number;

 public:
  virtual Cell *facet() = 0;
  virtual Cell *edge() { return facet()->facet(); }
  std::string &name();
  int dimension();
  int num_entities(int dim) const;
};

class PointCell : public Cell {
 public:
  PointCell();
  Cell *facet() override { return nullptr; }
  Cell *edge() override { return nullptr; }
};

class IntervalCell : public Cell {
 private:
  PointCell m_facet;

 public:
  IntervalCell();
  Cell *facet() override { return &m_facet; }
  Cell *edge() override { return nullptr; }
};

class TriangleCell : public Cell {
  IntervalCell m_facet;

 public:
  TriangleCell();
  Cell *facet() override { return &m_facet; }
};

class TetrahedronCell : public Cell {
  TriangleCell m_facet;

 public:
  TetrahedronCell();
  Cell *facet() override { return &m_facet; }
};

CellType get_cell_type(const std::string &cell);

}  // namespace mesh
}  // namespace oiseau
