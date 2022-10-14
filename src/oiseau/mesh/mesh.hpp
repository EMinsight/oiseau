#include "oiseau/mesh/geometry.h"
#include "oiseau/mesh/topology.h"

namespace oiseau::mesh {
class Mesh {
  public:
    Mesh();
    Mesh(Mesh &&) = default;
    Mesh(const Mesh &) = default;
    Mesh &operator=(Mesh &&) = default;
    Mesh &operator=(const Mesh &) = default;
    ~Mesh();

  private:
    Topology topology;
    Geometry geometry;
};

} // namespace oiseau::mesh
