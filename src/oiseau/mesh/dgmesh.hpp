#pragma once

#include <utility>
#include "oiseau/mesh/mesh.hpp"

namespace oiseau::mesh {
class DGMesh {
 public:
  DGMesh() {};
  DGMesh(Mesh &mesh, std::size_t order) : _mesh(mesh), _order(mesh.topology().n_cells(), order) {};
  DGMesh(Mesh &mesh, std::vector<uint> order) : _mesh(mesh), _order(order) {};
  DGMesh &operator=(DGMesh &&) = default;
  DGMesh &operator=(const DGMesh &) = default;
  ~DGMesh() = default;

  Mesh &mesh() { return _mesh; }
  const Mesh &mesh() const { return _mesh; }
  std::span<uint> order() { return _order; }

  uint order_at (std::size_t pos) const {
    return _order[pos];
  }


 private:
  Mesh _mesh;
  std::vector<uint> _order;
};

}  // namespace oiseau::mesh
