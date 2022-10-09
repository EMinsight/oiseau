#include "oiseau/mesh/cell.h"
#include "oiseau/utils.h"
#include <string>

namespace {
static std::unordered_map<oiseau::mesh::CellType, std::string> CELLTYPE_TO_STRING = {
    {oiseau::mesh::CellType::point, "point"},
    {oiseau::mesh::CellType::line, "line"},
    {oiseau::mesh::CellType::triangle, "triangle"},
    {oiseau::mesh::CellType::tetrahedron, "tetrahedron"},
};
static std::unordered_map<std::string, oiseau::mesh::CellType> CELLTYPE_FROM_STRING =
    oiseau::utils::reverse_map(CELLTYPE_TO_STRING);
} // namespace

namespace oiseau::mesh {

std::string &Cell::name() { return m_name; }
int Cell::dimension() { return m_dim; }
CellType &Cell::type() { return m_type; }
int Cell::num_entities(int dim) const { return m_entities_number[dim]; }

PointCell::PointCell() {
    m_name = "point";
    m_dim = 0;
    m_type = CellType::point;
    m_entities_number = {1, 0, 0, 0};
};

IntervalCell::IntervalCell() {
    m_name = "line";
    m_dim = 1;
    m_type = CellType::line;
    m_entities_number = {2, 1, 0, 0};
};

TriangleCell::TriangleCell() {
    m_name = "triangle";
    m_dim = 2;
    m_type = CellType::triangle;
    m_entities_number = {2, 1, 0, 0};
}

TetrahedronCell::TetrahedronCell() {
    m_name = "tetrahedron";
    m_dim = 3;
    m_type = CellType::tetrahedron;
    m_entities_number = {4, 6, 4, 1};
}
CellType &celltype_from_string(std::string &name) { return CELLTYPE_FROM_STRING[name]; }
std::string &celltype_to_string(CellType &type) { return CELLTYPE_TO_STRING[type]; }
} // namespace oiseau::mesh
