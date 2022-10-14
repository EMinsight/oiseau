#include <array>
#include <vector>
#include "oiseau/mesh/cell.hpp"

namespace oiseau::mesh {
class Topology {
 private:
  std::vector<int> m_neighbors;
};
}  // namespace oiseau::mesh
