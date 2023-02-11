#include "oiseau/mesh/cell.hpp"
#include <ranges>
#include <string>

namespace oiseau::mesh {

CellType get_cell_type(const std::string &cell) {
  static const PointCell point;
  static const IntervalCell interval;
  static const TriangleCell triangle;
  static const TetrahedronCell tetrahedron;
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

std::vector<std::vector<int>> Cell::get_sub_entities(int dim0, int dim1) {
  return m_topology[dim0][dim1];
};

std::vector<std::vector<int>> Cell::get_entity_vertices(int dim) {
  std::vector<std::vector<int>> slice;
  slice.reserve(m_topology[dim].size());
  for (const auto &s : m_topology[dim]) {
    slice.push_back(s[0]);
  }
  return slice;
}

int Cell::num_sub_entities(int dim) {
  if (dim <= m_dim) {
    return m_topology[dim].size();
  }
  return 0;
}

PointCell::PointCell() {
  m_name = "point";
  m_dim = 0;
  m_geometry = {
      {0.0},
      {1, 1},
  };
  m_topology = {
      {
          {{0}},
      },
  };
};

IntervalCell::IntervalCell() {
  m_name = "interval";
  m_dim = 1;
  m_geometry = {
      {0.0, 1.0},
      {2, 1},
  };
  m_topology = {
      {
          {{0}, {0}},
          {{1}, {0}},
      },
      {
          {{0, 1}, {0}},
      },
  };
};

TriangleCell::TriangleCell() {
  m_name = "triangle";
  m_dim = 2;
  m_geometry = {
      {0.0, 0.0, 1.0, 0.0, 0.0, 1.0},
      {3, 2},
  };
  m_topology = {
      {
          {{0}, {1, 2}, {0}},
          {{1}, {0, 2}, {0}},
          {{2}, {0, 1}, {0}},
      },
      {
          {{1, 2}, {0}, {0}},
          {{0, 2}, {1}, {0}},
          {{0, 1}, {2}, {0}},
      },
      {
          {{0, 1, 2}, {0, 1, 2}, {0}},
      },
  };
}

TetrahedronCell::TetrahedronCell() {
  m_name = "tetrahedron";
  m_dim = 3;
  m_geometry = {
      {0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0},
      {4, 3},
  };
  m_topology = {
      {
          {{0}, {3, 4, 5}, {1, 2, 3}, {0}},
          {{1}, {1, 2, 5}, {0, 2, 3}, {0}},
          {{2}, {0, 2, 4}, {0, 1, 3}, {0}},
          {{3}, {0, 1, 3}, {0, 1, 2}, {0}},
      },
      {
          {{2, 3}, {0}, {0, 1}, {0}},
          {{1, 3}, {1}, {0, 2}, {0}},
          {{1, 2}, {2}, {0, 3}, {0}},
          {{0, 3}, {3}, {1, 2}, {0}},
          {{0, 2}, {4}, {1, 3}, {0}},
          {{0, 1}, {5}, {2, 3}, {0}},
      },
      {
          {{1, 2, 3}, {0, 1, 2}, {0}, {0}},
          {{0, 2, 3}, {0, 3, 4}, {1}, {0}},
          {{0, 1, 3}, {1, 3, 5}, {2}, {0}},
          {{0, 1, 2}, {2, 4, 5}, {3}, {0}},
      },
      {
          {{0, 1, 2, 3}, {0, 1, 2, 3, 4, 5}, {0, 1, 2, 3}, {0}},
      },
  };
}

}  // namespace oiseau::mesh
