#pragma once

#include <utility>
#include "oiseau/mesh/geometry.hpp"
#include "oiseau/mesh/topology.hpp"

namespace oiseau::mesh {
class Mesh {
 public:
  Mesh() : _topology(), _geometry() {}
  Mesh(Topology &topology, Geometry &geometry) : _topology(topology), _geometry(geometry) {}
  Mesh(Topology &&topology, Geometry &&geometry)
      : _topology(std::move(topology)), _geometry(std::move(geometry)) {}

  Mesh(Mesh &&) = delete;
  Mesh(const Mesh &) = delete;
  Mesh &operator=(Mesh &&) = delete;
  Mesh &operator=(const Mesh &) = delete;
  ~Mesh();

  Topology &topology();
  const Topology &topology() const;
  Geometry &geometry();
  const Geometry &geometry() const;

 private:
  Topology _topology;
  Geometry _geometry;
};

}  // namespace oiseau::mesh
