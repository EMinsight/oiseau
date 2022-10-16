#include "oiseau/mesh/mesh.hpp"
#include <iostream>
#include <oiseau/io/gmsh.hpp>
#include "oiseau/mesh/cell.hpp"

using namespace oiseau::mesh;
using namespace oiseau::io;
int main() {
  Topology topology;
  Geometry geometry;
  Mesh m(topology, geometry);
  gmsh_read("demo/mesh.msh", m);

  return 0;
}
