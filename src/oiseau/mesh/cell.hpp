#pragma once

#include <array>
#include <string>

#define CellType oiseau::mesh::Cell const *

namespace oiseau {
namespace mesh {

enum class CellKind {
  Undefined = 0,  // Optional: A default/error value
  Point,
  Interval,
  Triangle,
  Quadrilateral,
  Tetrahedron
};

class Cell {
 protected:
  CellKind m_kind;
  std::string m_name;
  int m_dim;
  std::vector<std::vector<std::vector<std::vector<int>>>> m_topology;
  std::pair<std::vector<double>, std::array<std::size_t, 2>> m_geometry;

 public:
  virtual ~Cell() = default;
  virtual Cell *facet() = 0;
  virtual Cell *edge() = 0;
  std::string_view name() const;
  int dimension() const;
  int num_entities(int dim) const;
  std::vector<std::vector<int>> get_entity_vertices(int dim) const;
  std::vector<std::vector<int>> get_sub_entities(int dim0, int dim1) const;
  std::vector<std::vector<std::vector<std::vector<int>>>> topology() const { return m_topology; }
  int num_sub_entities(int dim) const;
  CellKind kind() const { return m_kind; }
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
 private:
  IntervalCell m_facet;
  PointCell m_edge;

 public:
  TriangleCell();
  Cell *facet() override { return &m_facet; }
  Cell *edge() override { return &m_edge; }
};

class QuadrilateralCell : public Cell {
 private:
  IntervalCell m_facet;
  PointCell m_edge;

 public:
  QuadrilateralCell();
  Cell *facet() override { return &m_facet; }
  Cell *edge() override { return &m_edge; }
};

class TetrahedronCell : public Cell {
 private:
  TriangleCell m_facet;
  IntervalCell m_edge;

 public:
  TetrahedronCell();
  Cell *facet() override { return &m_facet; }
  Cell *edge() override { return &m_edge; }
};

CellType get_cell_type(const std::string &cell);

}  // namespace mesh
}  // namespace oiseau
