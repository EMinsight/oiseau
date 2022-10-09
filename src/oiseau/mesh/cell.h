#pragma once

#include <array>
#include <string>

namespace oiseau {
namespace mesh {

enum class CellType : int { point = 1, line = 2, triangle = 3, tetrahedron = 4 };

class Cell {
  protected:
    std::string m_name;
    CellType m_type;
    int m_dim;
    std::array<int, 4> m_entities_number;

  public:
    virtual Cell *facet() = 0;
    virtual Cell *edge() { return facet()->facet(); }
    std::string &name();
    int dimension();
    CellType &type();
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

CellType &celltype_from_string(std::string &name);
std::string &celltype_to_string(CellType &type);

} // namespace mesh
} // namespace oiseau
