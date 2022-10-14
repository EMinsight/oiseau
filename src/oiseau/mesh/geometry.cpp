#include <array>
#include <vector>
#include "oiseau/mesh/cell.hpp"

namespace oiseau::mesh {
class Geometry {
 private:
  oiseau::mesh::CellType m_cell;
  std::vector<std::array<double, 3>> m_cell_vertices;
  std::vector<std::array<double, 3>> m_vertices;
};
}  // namespace oiseau::mesh
