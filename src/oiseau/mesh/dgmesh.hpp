#pragma once

#include <utility>
#include "oiseau/mesh/mesh.hpp"

namespace oiseau::mesh {
class DGMesh {
 public:
  DGMesh(){};
  DGMesh(Mesh &mesh) : _mesh(mesh){};
  DGMesh(Mesh &mesh, std::size_t order) : _mesh(mesh), _order(order){};
  DGMesh &operator=(DGMesh &&) = default;
  DGMesh &operator=(const DGMesh &) = default;
  ~DGMesh() = default;

 private:
  Mesh _mesh;
  std::size_t _order;
};

}  // namespace oiseau::mesh
