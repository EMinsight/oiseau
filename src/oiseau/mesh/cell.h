#pragma once

#include <array>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace {
template <typename K, typename V> std::unordered_map<V, K> reverse_map(const std::unordered_map<K, V> &m) {
    std::unordered_map<V, K> r;
    for (const auto &[k, v] : m)
        r[v] = k;
    return r;
}
} // namespace

namespace oiseau {
namespace mesh {

enum class CellType : int { point = 1, line = 2, triangle = 3, tetrahedron = 4 };
CellType &celltype_from_string(std::string &name);
std::string &celltype_to_string(CellType &type);

class Cell {
  protected:
    CellType m_type;
    int m_dim;
    std::string m_name;
    std::unique_ptr<Cell> m_facet;
    std::unique_ptr<Cell> m_edge;
    std::array<int, 4> m_entities_number;

  public:
    virtual std::string &name() { return m_name; }
    virtual int &dimension() { return m_dim; }
    virtual Cell *facet() { return m_facet.get(); }
    virtual Cell *edge() { return m_facet.get(); }
    virtual CellType &type() { return m_type; }
    virtual int num_entities(int dim) { return m_entities_number[dim]; }
};

class PointCell : public Cell {
  public:
    PointCell() {
        m_name = "Point";
        m_dim = 0;
        m_type = CellType::point;
        m_entities_number = {1, 0, 0, 0};
    };
};

class IntervalCell : public Cell {
  public:
    IntervalCell() {
        m_name = "Line";
        m_dim = 1;
        m_facet = std::unique_ptr<Cell>(new PointCell());
        m_type = CellType::line;
        m_entities_number = {2, 1, 0, 0};
    };
};

class TriangleCell : public Cell {
  public:
    TriangleCell() {
        m_name = "Triangle";
        m_dim = 2;
        m_facet = std::unique_ptr<Cell>(new IntervalCell());
        m_edge = std::unique_ptr<Cell>(new PointCell());
        m_type = CellType::triangle;
        m_entities_number = {2, 1, 0, 0};
    }
};

class TetrahedronCell : public Cell {
    TetrahedronCell() {
        m_name = "Tetrahedron";
        m_dim = 3;
        m_facet = std::unique_ptr<Cell>(new TriangleCell());
        m_edge = std::unique_ptr<Cell>(new IntervalCell());
        m_type = CellType::tetrahedron;
        m_entities_number = {4, 6, 4, 1};
    }
};

} // namespace mesh
} // namespace oiseau
